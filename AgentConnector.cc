/*
 * AgentConnector.cpp
 *
 *  Created on: Apr 12, 2022
 *      Author: user
 */

#include "AgentConnector.h"
#include <stdio.h>
#include <omnetpp.h>
#include <string>
#include "utils.h"
#include "types.h"
#include <numeric>
#include <iostream>

using namespace omnetpp;

const char* DC_HOST = "127.0.0.1";
const int   DC_PORT = 50123;

const int AFT_MSG_LEN = 4 * EDGE_PAIRS;
const int REWARD_MSG_LEN = 0;
const int PAIRSPATHUTILIZATIONS_MSG_LEN = PATH_COUNT;

const int SEND_MSG_LEN = AFT_MSG_LEN + REWARD_MSG_LEN + PAIRSPATHUTILIZATIONS_MSG_LEN;
const int RECV_MSG_LEN = PATH_COUNT_PER_EDGE * EDGE_COUNT;

AgentConnector::AgentConnector() {
    WORD ver = MAKEWORD(2,2);
    WSADATA wsaData;
    int retVal=0;

    WSAStartup(ver,(LPWSADATA)&wsaData);

    LPHOSTENT hostEnt;

    hostEnt = gethostbyname(DC_HOST);

    if(!hostEnt)
    {
        printf("Unable to collect gethostbyname\n");
        WSACleanup();
        throw 1;
    }

    // Создаем сокет
    _sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(_sock == SOCKET_ERROR)
    {
        printf("Unable to create socket\n");
        WSACleanup();
        throw 2;
    }

    SOCKADDR_IN serverInfo;

    serverInfo.sin_family = PF_INET;
    serverInfo.sin_addr = *((LPIN_ADDR)*hostEnt->h_addr_list);
    serverInfo.sin_port = htons(DC_PORT);

    retVal=connect(_sock,(LPSOCKADDR)&serverInfo, sizeof(serverInfo));
    if(retVal==SOCKET_ERROR)
    {
        printf("Unable to connect\n");
        WSACleanup();
        throw 3;
    }

    printf("Connection made sucessfully\n");
}

AgentConnector::~AgentConnector() {
    closesocket(_sock);
    WSACleanup();
}

map<EdgePair, PathProportions>
AgentConnector::fetchEdgePathProportions(
        const vector<int>& aggrFlowThroughputs,
        const vector<vector<char>>& pairsPathUtilizations
) {

    //
    // Send network state
    //
    char request[SEND_MSG_LEN];
    int offset = 0;

    // Put aft
    int i = -1;
    for (int p1 = 0; p1 < POD_COUNT; ++p1) {
        for (int e1 = 0; e1 < EDGE_PER_POD; ++e1) {
            std::string edge1 = makeNodeName(NodeTypes::Edge, e1, p1);
            for (int p2 = 0; p2 < POD_COUNT; ++p2) {
                for (int e2 = 0; e2 < EDGE_PER_POD; ++e2) {
                    if (p1 == p2 && e1 == e2)
                        continue;
                    std::string edge2 = makeNodeName(NodeTypes::Edge, e2, p2);
                    EdgePair pair = EdgePair(edge1, edge2);
                    offset += put(request, offset, aggrFlowThroughputs[++i]);
                }
            }
        }
    }

    // Put reward
//    double reward = 0;
//    for (int i = 0; i < pairsPathUtilizations.size(); ++i) {
//        auto v = pairsPathUtilizations[i];
//        if (v.size() == 0) {
//            std::cout << std::string("No path utilizations found on ") + std::to_string(i) << std::endl;
//            throw -1;
//        }
//        int sum = std::accumulate(v.begin(), v.end(), 0);
//        int mean_utilization = sum / v.size();
//        int distance_to_mean = 0;
//        for (auto utilization: v) {
//            distance_to_mean += abs(utilization - mean_utilization);
//        }
//        reward += 1 - 0.01 * distance_to_mean / v.size();
//    }
//    int intReward = (int)reward;
//    offset += put(request, offset, intReward);

    // Put utilizations
    for (auto v: pairsPathUtilizations) {
        for (auto u: v) {
            request[offset++] = u;
        }
    }


    if (offset != SEND_MSG_LEN) {
        std::cout << string("Offset is not SEND_MSG_LEN: ") + to_string(offset) + string(" != ") + to_string(SEND_MSG_LEN) << std::endl;
        throw -1;
    }

    send(_sock, request, SEND_MSG_LEN, 0);

    //
    // Receive proportions
    //
    char response[RECV_MSG_LEN];
    int retVal = recv(_sock, response, RECV_MSG_LEN, 0);
    if(retVal == SOCKET_ERROR)
    {
        printf("Unable to recv\n");
        WSACleanup();
        throw 5;
    }

    // Prepare proportions and helpers
    map<EdgePair, PathProportions> proportions;
    int propIndex = -1;
    auto addProp = [&propIndex, &proportions, &response](EdgePair pair, int propCount) mutable {
        vector<double> props;
        for (int i = 0; i < propCount; ++i) {
            double prop = 0.01 * response[++i];
            props.push_back(prop);
        }
        proportions[pair] = props;
    };

    // Go through response
    for (int p1 = 0; p1 < POD_COUNT; ++p1) {
        for (int e1 = 0; e1 < EDGE_PER_POD; ++e1) {
            std::string edge1 = makeNodeName(NodeTypes::Edge, e1, p1);
            for (int p2 = 0; p2 < POD_COUNT; ++p2) {
                for (int e2 = 0; e2 < EDGE_PER_POD; ++e2) {
                    if (p1 == p2 && e1 == e2)
                        continue;
                    std::string edge2 = makeNodeName(NodeTypes::Edge, e2, p2);
                    EdgePair pair = EdgePair(edge1, edge2);
                    if (p1 == p2)
                        addProp(pair, PATH_COUNT_TO_SAME_POD_EDGE);
                    else
                        addProp(pair, PATH_COUNT_TO_OTHER_POD_EDGE);
                }
            }
        }
    }

    return proportions;
}




