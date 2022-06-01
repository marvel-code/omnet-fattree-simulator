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
    Node& _node;
    simtime_t _finishTime;

public:
    TrafficGenerator(Node& node);
    void launch();
    double readTM(int index, double offset = 0);
    double readTMPipeline();
    simtime_t getFinishTime();
};

#endif /* TRAFFICGENERATOR_H_ */
