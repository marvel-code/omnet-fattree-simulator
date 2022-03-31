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

struct Gate {
    std::string direction; // up, down
    int index;
    Gate(std::string d, int i) : direction{d + "$o"}, index{i} {}
};

class NodeRouter {
    Node& _node;
    std::map<std::string, Gate*> _neighbors; // neighbor node -> Gate
    std::map<std::string, std::vector<std::vector<std::string>>> _paths; // edge -> paths

public:
    NodeRouter(Node& node);
    void setRoute(Packet* pkt, std::string destName, int routeIndex);
    int getRoutesCount(std::string destName);
    void sendNext(Packet* pkt);
};

#endif /* NODEROUTER_H_ */
