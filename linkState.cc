/*
 * linkState.cpp
 *
 *  Created on: Apr 2, 2022
 *      Author: user
 */

#include "linkState.h"
#include "globals.h"

LinkState::LinkState() {}

LinkState::~LinkState() {}

void LinkState::processPacket(Packet* pkt) {
    // Refresh _intervalTimestamps
    simtime_t currentTime = simTime();
    _intervalTimestamps.push(currentTime);
    while (currentTime - _intervalTimestamps.front() > UTILIZATION_INTERVAL_S) {
        _intervalTimestamps.pop();
    }
}

void LinkState::refreshUtilization() {
    simtime_t currentTime = simTime();
    while (_intervalTimestamps.size() > 0 && currentTime - _intervalTimestamps.front() > UTILIZATION_INTERVAL_S) {
        _intervalTimestamps.pop();
    }
    double currentCapacity = _intervalTimestamps.size() * PACKET_SIZE_BITS * 100 / UTILIZATION_INTERVAL_S;
    _utilization = currentCapacity / CAPACITY_BPS;
}

int LinkState::getUtilization() {
    return _utilization;
}


