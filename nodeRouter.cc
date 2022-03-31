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
using namespace omnetpp;

NodeRouter::NodeRouter(Node& node): _node{node} {
    // Initialize _neighbors
    if (node.getType() == NodeTypes::Core) {
        for (int i = 0; i < POD_COUNT; ++i) {
            for (int j = 0; j < AGGR_PER_POD; ++j) {
                _neighbors["aggr" + std::to_string(i) + std::to_string(j)] = new Gate("down", AGGR_PER_POD * i + j);
            }
        }
    }
    else if (node.getType() == NodeTypes::Aggr) {
        for (int i = 0; i < CORE_COUNT; ++i) {
            _neighbors["core" + std::to_string(i)] = new Gate("up", i);
        }
        int pod = node.getPod();
        for (int i = 0; i < EDGE_PER_POD; ++i) {
            _neighbors["edge" + std::to_string(pod) + std::to_string(i)] = new Gate("down", i);
        }
    }
    else if (node.getType() == NodeTypes::Edge) {
        int pod = node.getPod();
        for (int i = 0; i < AGGR_PER_POD; ++i) {
            _neighbors["aggr" + std::to_string(pod) + std::to_string(i)] = new Gate("up", i);
        }
    }
    // Initialize routes to other edges
    if (node.getType() == NodeTypes::Edge) {
        int index = node.getIndex();
        int pod = node.getPod();
        // Edge on the same pod
        for (int e = 0; e < EDGE_PER_POD; ++e) {
            if (e == index)
                continue;
            std::string edge = makeNodeName(NodeTypes::Edge, e, pod);
            _paths[edge] = std::vector<std::vector<std::string>>();
            for (int a1 = 0; a1 < AGGR_PER_POD; ++a1) {
                std::vector<std::string> path;
                path.push_back(makeNodeName(NodeTypes::Aggr, a1, pod));
                path.push_back(edge);
                _paths[edge].push_back(path);
                for (int a2 = 0; a2 < AGGR_PER_POD; ++a2) {
                    if (a1 == a2)
                        continue;
                    for (int c = 0; c < CORE_COUNT; ++c) {
                        path = std::vector<std::string>();
                        path.push_back(makeNodeName(NodeTypes::Aggr, a1, pod));
                        path.push_back(makeNodeName(NodeTypes::Core, c));
                        path.push_back(makeNodeName(NodeTypes::Aggr, a2, pod));
                        path.push_back(edge);
                    }
                }
            }
        }
        // Edge on other pods
        for (int p = 0; p < POD_COUNT; ++p) {
            if (p == pod)
                continue;
            for (int e = 0; e < EDGE_PER_POD; ++e) {
                std::string edge = makeNodeName(NodeTypes::Edge, e, p);
                _paths[edge] = std::vector<std::vector<std::string>>();
                for (int a1 = 0; a1 < AGGR_PER_POD; ++a1) {
                    for (int a2 = 0; a2 < AGGR_PER_POD; ++a2) {
                        for (int c = 0; c < CORE_COUNT; ++c) {
                            std::vector<std::string> path;
                            path.push_back(makeNodeName(NodeTypes::Aggr, a1, pod));
                            path.push_back(makeNodeName(NodeTypes::Core, c));
                            path.push_back(makeNodeName(NodeTypes::Aggr, a2, p));
                            path.push_back(edge);
                            _paths[edge].push_back(path);
                        }
                    }
                }
            }
        }
    }
}

int NodeRouter::getRoutesCount(std::string destName) {
    return _paths[destName].size();
}

void NodeRouter::setRoute(Packet* pkt, std::string destEdge, int routeIndex) {
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
}

void NodeRouter::sendNext(Packet* pkt) {
    if (pkt->getRouteArraySize() > 0) {
        std::string next = pkt->getRoute(pkt->getRouteArraySize() - 1);
        pkt->setRouteArraySize(pkt->getRouteArraySize() - 1);
        Gate* gate = _neighbors[next];
        _node.send(pkt, gate->direction.c_str(), gate->index);
    }
}



