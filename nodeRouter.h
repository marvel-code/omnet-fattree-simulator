/*
 * nodeRouter.h
 *
 *  Created on: Mar 30, 2022
 *      Author: user
 */


#ifndef NODEROUTER_H_
#define NODEROUTER_H_

#include <omnetpp.h>
using namespace omnetpp;
#include <string>
#include <node.h>
#include "packet_m.h"
#include <map>
#include <vector>
#include <math.h>
#include "utils.h"
#include <algorithm>
#include "TrafficBalancer.h"
#include <omnetpp.h>

using namespace omnetpp;

class NodeRouter {
    Node& _node;
    std::map<std::string, std::pair<cGate*, cGate*>> _neighbors; // neighbor node -> cGate
    std::map<std::string, std::vector<std::vector<std::string>>> _paths; // edge -> paths

    std::map<std::string, TrafficBalancer*> _trafficBalancers; // Destination edge name -> edge traffic router

public:
    NodeRouter(Node& node);
    void setRoute(Packet* pkt, const std::string& destName, int routeIndex);
    void setCalculatedRoute(Packet* pkt, const std::string& destName);
    int getRoutesCount(const std::string& destName);
    void sendNext(Packet* pkt);
    void sendTo(Packet* pkt, const std::string& destName);
    int calcRouteIndex(Packet* pkt, const std::string& destName);
    std::map<std::string, std::pair<cGate*, cGate*>> getNeighbors();
};

#endif /* NODEROUTER_H_ */
