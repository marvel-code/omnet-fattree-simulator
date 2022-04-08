/*
 * DataCollectorConnector.cpp
 *
 *  Created on: Apr 8, 2022
 *      Author: user
 */

#include "DataCollectorConnector.h"
#include <stdio.h>
#include <omnetpp.h>
#include <string>

using namespace omnetpp;

const char* DC_HOST = "127.0.0.1";
const int   DC_PORT = 50123;

DataCollectorConnector::DataCollectorConnector() {
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

    //Создаем сокет
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

//    const char *pBuf = "Request";
//
//    printf("Sending request from client\n");
//    retVal = send(_sock, pBuf, strlen(pBuf), 0);
//
//    if(retVal == SOCKET_ERROR)
//    {
//        printf("Unable to send\n");
//        WSACleanup();
//        throw 4;
//    }

//    char szResponse[9];
//    retVal = recv(_sock, szResponse, 9, 0);
//
//    if(retVal == SOCKET_ERROR)
//    {
//        printf("Unable to recv\n");
//        WSACleanup();
//        throw 5;
//    }
//
//    printf("Got the response from server\n%s\n",szResponse);
}

void DataCollectorConnector::sendStateFromNode(std::string& node, std::vector<std::pair<std::string, int>>& utilizations) {
    std::string message;
    message += std::to_string(simTime().dbl()) + ",";
    message += node;
    for (auto u: utilizations) {
        message += "," + u.first;
        message += "=" + std::to_string(u.second);
    }
    message += '\0';

    send(_sock, message.c_str(), message.size(), 0);

    char szResponse[10];
    int retVal = recv(_sock, szResponse, 9, 0);
    if(retVal == SOCKET_ERROR)
    {
        printf("Unable to recv\n");
        WSACleanup();
        throw 5;
    }
}

DataCollectorConnector::~DataCollectorConnector() {
    closesocket(_sock);
    WSACleanup();
}

