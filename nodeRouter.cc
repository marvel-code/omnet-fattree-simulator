/*
 * nodeRouter.cc
 *
 *  Created on: Mar 30, 2022
 *      Author: user
 */

#include "nodeRouter.h"
#include <omnetpp.h>
#include <string>
#include "types.h"
#include "globals.h"
#include "utils.h"
#include <random>
#include <utility>

using namespace omnetpp;

/** Returns: first is input, second is output */
std::pair<cGate*, cGate*> makeIOPair(Node& node, const char* name, int index) {
    return std::pair<cGate*, cGate*>(
            node.gate((name + std::string("$i")).c_str(), index),
            node.gate((name + std::string("$o")).c_str(), index)
        );
}

NodeRouter::NodeRouter(Node& node): _node{node} {
    // Initialize _neighbors
    if (node.getType() == NodeTypes::Core) {
        for (int i = 0; i < POD_COUNT; ++i) {
            for (int j = 0; j < AGGR_PER_POD; ++j) {
                _neighbors["aggr" + std::to_string(i) + std::to_string(j)] = makeIOPair(node, "down", AGGR_PER_POD * i + j);

            }
        }
    }
    else if (node.getType() == NodeTypes::Aggr) {
        for (int i = 0; i < CORE_COUNT; ++i) {
            _neighbors["core" + std::to_string(i)] = makeIOPair(node, "up", i);
        }
        int pod = node.getPod();
        for (int i = 0; i < EDGE_PER_POD; ++i) {
            _neighbors["edge" + std::to_string(pod) + std::to_string(i)] = makeIOPair(node, "down", i);
        }
    }
    else if (node.getType() == NodeTypes::Edge) {
        int pod = node.getPod();
        for (int i = 0; i < AGGR_PER_POD; ++i) {
            _neighbors["aggr" + std::to_string(pod) + std::to_string(i)] = makeIOPair(node, "up", i);
        }
    }

    // Initialize routes to other edges
    std::map<std::string, int> destEdgePathCounts;
    if (node.getType() == NodeTypes::Edge) {
        int index = node.getIndex();
        int pod = node.getPod();
        // Edge on the same pod
        for (int e = 0; e < EDGE_PER_POD; ++e) {
            if (e == index)
                continue;
            std::string edge = makeNodeName(NodeTypes::Edge, e, pod);
            _paths[edge] = std::vector<std::vector<std::string>>();
            destEdgePathCounts[edge] = 0;
            for (int a1 = 0; a1 < AGGR_PER_POD; ++a1) {
                std::vector<std::string> path;
                for (int a2 = 0; a2 < AGGR_PER_POD; ++a2) {
                    if (a1 == a2)
                        continue;
                    for (int c = 0; c < CORE_COUNT; ++c) {
                        path = std::vector<std::string>();
                        path.push_back(makeNodeName(NodeTypes::Aggr, a1, pod));
                        path.push_back(makeNodeName(NodeTypes::Core, c));
                        path.push_back(makeNodeName(NodeTypes::Aggr, a2, pod));
                        path.push_back(edge);
                        _paths[edge].push_back(path);
                        destEdgePathCounts[edge] += 1;
                    }
                }
                path = std::vector<std::string>();
                path.push_back(makeNodeName(NodeTypes::Aggr, a1, pod));
                path.push_back(edge);
                _paths[edge].push_back(path);
                destEdgePathCounts[edge] += 1;
            }
        }
        // Edge on other pods
        for (int p = 0; p < POD_COUNT; ++p) {
            if (p == pod)
                continue;
            for (int e = 0; e < EDGE_PER_POD; ++e) {
                std::string edge = makeNodeName(NodeTypes::Edge, e, p);
                _paths[edge] = std::vector<std::vector<std::string>>();
                destEdgePathCounts[edge] = 0;
                for (int a1 = 0; a1 < AGGR_PER_POD; ++a1) {
                    for (int a2 = 0; a2 < AGGR_PER_POD; ++a2) {
                        for (int c = 0; c < CORE_COUNT; ++c) {
                            std::vector<std::string> path;
                            path.push_back(makeNodeName(NodeTypes::Aggr, a1, pod));
                            path.push_back(makeNodeName(NodeTypes::Core, c));
                            path.push_back(makeNodeName(NodeTypes::Aggr, a2, p));
                            path.push_back(edge);
                            _paths[edge].push_back(path);
                            destEdgePathCounts[edge] += 1;
                        }
                    }
                }
            }
        }
    }

    // Initialize traffic balancers
    if (node.getType() == NodeTypes::Edge) {
        for (auto dep: destEdgePathCounts) {
            _trafficBalancers[dep.first] = new TrafficBalancer(dep.first, dep.second);
        }
    }
}

int NodeRouter::getRoutesCount(const std::string& destName) {
    return _paths[destName].size();
}

void NodeRouter::setRoute(Packet* pkt, const std::string& destEdge, int routeIndex) {
    if (_paths.find(destEdge) == _paths.end())
        return;
    auto paths = _paths[destEdge];
    if (routeIndex >= paths.size() || routeIndex < 0)
        return;

    std::vector<std::string> route = paths[routeIndex];
    pkt->setRouteArraySize(route.size());
    for (int i = 0; i < route.size(); ++i) {
        pkt->setRoute(route.size() - 1 - i, route[i].c_str());
    }
    pkt->setDestEdge(destEdge.c_str());
}

void NodeRouter::sendNext(Packet* pkt) {
    if (pkt->getRouteArraySize() > 0) {
        // Calc Gate
        std::string next = pkt->getRoute(pkt->getRouteArraySize() - 1);
        pkt->setRouteArraySize(pkt->getRouteArraySize() - 1);
        cGate* cGate = _neighbors[next].second;
        // Send delayed
        double delay = cGate->getTransmissionChannel()->getTransmissionFinishTime().dbl() - simTime().dbl();
        _node.sendDelayed(pkt, delay > 0 ? delay : 0, cGate);
    } else {
        delete pkt;
    }
}

void NodeRouter::sendTo(Packet* pkt, const std::string& destEdge) {
    setCalculatedRoute(pkt, destEdge);
    sendNext(pkt);
}

int NodeRouter::calcRouteIndex(Packet* pkt, const std::string& destEdge) {
    if (_paths.find(destEdge) == _paths.end())
        return 0;
    return _trafficBalancers[destEdge]->computePacketPathIndex(pkt);
}

void NodeRouter::setCalculatedRoute(Packet* pkt, const std::string& destEdge) {
    int routeIndex = calcRouteIndex(pkt, destEdge);
    setRoute(pkt, destEdge, routeIndex);
}

std::map<std::string, std::pair<cGate*, cGate*>> NodeRouter::getNeighbors() {
    return _neighbors;
}




