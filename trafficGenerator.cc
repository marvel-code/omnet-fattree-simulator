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
    _finishTime = simTime() + readTM(0);
    //readTMPipeline();
}

simtime_t TrafficGenerator::getFinishTime() {
    return _finishTime;
}

/** Reads all TM{i}.txt for i=0... */
double TrafficGenerator::readTMPipeline() {
    double startTime = 0;
    for (int i = 0; ; ++i) {
        double duration = readTM(i, startTime);
        if (duration < 0)
            break;
        startTime += duration;
    }
    double pipelineDuration = startTime;
    return pipelineDuration;
}

/** Returns TM duration in s. */
double TrafficGenerator::readTM(int index, double offset) {
    std::string path = "datasets/TM" + std::to_string(index) + ".txt";
    std::ifstream f(path);
    double duration_s = -1;
    if (f.is_open()) {
        std::string line;

        // Line 1
        std::getline(f, line);
        int interval_ms;
        std::stringstream(line) >> interval_ms;
        duration_s = (double)interval_ms / 1000;

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
            while (time - startTime < duration_s) {
                Packet* pkt = new Packet();
                pkt->setByteLength(packetSize);
                pkt->setDestEdge(edge2.c_str());
                time += (double)d(gen) / 1000;
                _node.scheduleAt(time, pkt);
            }
        }
        f.close();
    }
    return duration_s;
}




