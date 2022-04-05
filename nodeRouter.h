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


/** Кастомное описание cGate */
struct Gate {
    std::string direction; // up, down
    int index;
    Gate(std::string d, int i) : direction{d}, index{i} {}
    cGate* getOutputGate(Node& node) {
        return node.gate((direction + "$o").c_str(), index);
    }
    cGate* getInputGate(Node& node) {
        return node.gate((direction + "$i").c_str(), index);
    }
};


class NodeRouter {
    Node& _node;
    std::map<std::string, Gate*> _neighbors; // neighbor node -> Gate
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
};

#endif /* NODEROUTER_H_ */
