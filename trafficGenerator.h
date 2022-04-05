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

public:
    TrafficGenerator(Node& node);
    void launch();
    int readTM(int index, double offset = 0);
    void readTMPipeline();
};

#endif /* TRAFFICGENERATOR_H_ */
