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
#include <random>
#include <sstream>

using namespace omnetpp;


TrafficGenerator::TrafficGenerator(Node& node) : _node{node} {}

void TrafficGenerator::launch() {
    readTM(0);
    //readTMPipeline();
}

/** Reads all TM{i}.txt for i=0... */
void TrafficGenerator::readTMPipeline() {
    double startTime = 0;
    for (int i = 0; ; ++i) {
        int interval = readTM(i, startTime);
        if (interval == -1)
            break;
        startTime += (double)interval / 1000;
    }
}

/** Returns interval in milliseconds. */
int TrafficGenerator::readTM(int index, double offset) {
    std::string path = "datasets/TM" + std::to_string(index) + ".txt";
    std::ifstream f(path);
    int interval_ms = -1;
    if (f.is_open()) {
        std::string line;

        // Line 1
        std::getline(f, line);
        std::stringstream(line) >> interval_ms;

        // Line 2
        std::getline(f, line);
        int packetSize;
        int packetDelayMean;
        int packetDelayStdDev;
        std::stringstream(line) >> packetSize >> packetDelayMean >> packetDelayStdDev;

        // Random generator
        std::random_device rd{};
        std::mt19937 gen{rd()};
        std::normal_distribution<double> d(packetDelayMean, packetDelayStdDev);

        // Lines ...
        while (std::getline(f, line)) {
            // Pair settings
            std::string edge1;
            std::string edge2;
            int packetCount;
            std::stringstream(line) >> edge1 >> edge2 >> packetCount;
            if (edge1 != _node.getName())
                continue;

            // Schedule
            simtime_t startTime = simTime().dbl() + offset;
            simtime_t time = startTime;
            while (time - startTime < (double)interval_ms / 1000) {
                Packet* pkt = new Packet();
                pkt->setByteLength(packetSize);
                pkt->setDestEdge(edge2.c_str());
                time += (double)d(gen) / 1000;
                _node.scheduleAt(time, pkt);
            }
        }
        f.close();
    }
    return interval_ms;
}




