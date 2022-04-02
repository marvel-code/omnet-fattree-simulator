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

class LinkState {

    double UTILIZATION_INTERVAL_S = 0.1;
    int CAPACITY_BPS = 100 * 1024 * 1024;

    int _utilization; // from 0 to 100

    /** Queue of received packet time stamps in UTILIZATION_INTERVAL_MS */
    std::queue<simtime_t> _intervalTimestamps;

public:
    LinkState();
    virtual ~LinkState();

    void refreshUtilization();
    void processPacket(Packet* pkt);
    int getUtilization();
};

#endif /* LINKSTATE_H_ */
