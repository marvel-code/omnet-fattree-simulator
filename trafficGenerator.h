/*
 * trafficGenerator.h
 *
 *  Created on: Apr 1, 2022
 *      Author: user
 */

#ifndef TRAFFICGENERATOR_H_
#define TRAFFICGENERATOR_H_


class TrafficGenerator {

    int _packetSizeKb;
    std::map<std::string, std::pair<std::string, int>> _TM;
    simtime_t _interval;

    Node& _node;

public:
    TrafficGenerator(Node& node) : _node{node} {}
    void launch() {

    }

};

#endif /* TRAFFICGENERATOR_H_ */
