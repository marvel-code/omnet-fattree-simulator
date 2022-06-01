/*
 * linkState.h
 *
 *  Created on: Apr 2, 2022
 *      Author: user
 */

#ifndef LINKSTATE_H_
#define LINKSTATE_H_

#include "packet_m.h"
#include <queue>
#include <fstream>

using namespace omnetpp;

struct PacketInfo {
    simtime_t arrivalTime;
    int bytes;
    PacketInfo(simtime_t arrivalTime, int bytes)
        : arrivalTime{arrivalTime},
          bytes{bytes}
    {}
};

class LinkState {

    int _utilization; // from 0 to 100

    /** Queue of received packet time stamps in UTILIZATION_INTERVAL_MS */
    std::queue<PacketInfo> _packetInfos;
    int _trafficBytes = 0;

public:
    LinkState();
    virtual ~LinkState();

    void refreshUtilization();
    void processPacket(Packet* pkt);
    int getUtilization();
    void popStalePacketInfos();
};

#endif /* LINKSTATE_H_ */
