//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef TRAFFICBALANCER_H_
#define TRAFFICBALANCER_H_

#include <string>
#include <vector>
#include "packet_m.h"
#include <omnetpp.h>

using namespace omnetpp;

/** Балансировщик трафика до определенного edge-узла. Находится на одном из edge-узлов. */
class TrafficBalancer {
    /** Destination edge name */
    std::string _destEdge;

    /** Path count */
    int _pathCount;
    /** Path proportions */
    std::vector<double> _props;
    /** Tokens */
    std::vector<int> _tokens;

    /** Last packet arrival time */
    simtime_t _lastArrivalTime;
    /** Current path index */
    int _currentPathIndex;

    /** Last tokens reset */
    simtime_t _lastTokensResetTime;

public:
    TrafficBalancer(const std::string& destEdge, int pathCount);
    void updateProps(const std::vector<double>& props);
    void resetTokens();
    int computePacketPathIndex(Packet* pkt);
};

#endif /* TRAFFICBALANCER_H_ */
