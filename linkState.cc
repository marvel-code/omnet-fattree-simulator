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
    _packetInfos.push(PacketInfo(pkt->getArrivalTime(), pkt->getByteLength()));
    _trafficBytes += pkt->getByteLength();
    popStalePacketInfos();
}

void LinkState::popStalePacketInfos() {
    simtime_t currentTime = simTime();
    while (_packetInfos.size() > 0 && currentTime - _packetInfos.front().arrivalTime > UTILIZATION_INTERVAL_S) {
        _trafficBytes -= _packetInfos.front().bytes;
        _packetInfos.pop();
    }
}

void LinkState::refreshUtilization() {
    popStalePacketInfos();
    double currentCapacity = _trafficBytes * 8 / UTILIZATION_INTERVAL_S;
    _utilization = currentCapacity / CAPACITY_BPS * 100;
}

int LinkState::getUtilization() {
    return _utilization;
}


