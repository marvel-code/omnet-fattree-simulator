/*
 * trafficGenerator.cc
 *
 *  Created on: Apr 1, 2022
 *      Author: user
 */


#include "trafficGenerator.h"
#include <fstream>
#include <string>
#include "packet_m.h"
#include "utils.h"
#include "nodeRouter.h"
#include <stdio.h>
#include <omnetpp.h>
#include "globals.h"

using namespace omnetpp;


TrafficGenerator::TrafficGenerator(Node& node) : _node{node} {}

void TrafficGenerator::launch() {
    readTM(0);
}

void TrafficGenerator::readTM(int index) {
    std::string path = "datasets/TM" + std::to_string(index) + ".txt";
    std::ifstream f(path);
    if (f.is_open()) {
        std::string line;
        std::getline(f, line);
        _interval = stoi(line);
        //std::getline(f, line);
        //_packetSize = stoi(line) * 1024;
        _packetSize = PACKET_SIZE_BITS;
        while (std::getline(f, line)) {
            // Read
            char e1[16];
            char e2[16];
            int packetCount;
            sscanf(line.c_str(), "%s %s %d", e1, e2, &packetCount);
            std::string edge1(e1);
            std::string edge2(e2);
            if (edge1 != _node.getName())
                continue;

            // Schedule
            for (int i = 0; i < packetCount; ++i) {
                Packet* pkt = new Packet();
                pkt->setBitLength(_packetSize);
                pkt->setDestEdge(e2);
                _node.scheduleAt(simTime().dbl() + ((double)i + 0.5) / packetCount * (_interval / 1000), pkt);
            }
        }
        f.close();
    }
}




