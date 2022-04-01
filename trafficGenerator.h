/*
 * trafficGenerator.h
 *
 *  Created on: Apr 1, 2022
 *      Author: user
 */

#ifndef TRAFFICGENERATOR_H_
#define TRAFFICGENERATOR_H_

#include <map>
#include <omnetpp.h>
#include "node.h"

using namespace omnetpp;

class TrafficGenerator {

    /** Traffic matrix */
    std::map<std::string, std::pair<std::string, int>> _TM;
    /** Traffic matrix interval in ms */
    simtime_t _interval;
    /** Packet size in bytes */
    int _packetSize;

    Node& _node;

public:
    TrafficGenerator(Node& node);
    void launch();
    void readTM(int index);
};

#endif /* TRAFFICGENERATOR_H_ */
