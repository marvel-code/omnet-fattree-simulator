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

#include "TrafficBalancer.h"
#include "globals.h"
#include <algorithm>

TrafficBalancer::TrafficBalancer(const std::string& destEdge, int pathCount)
    : _destEdge{destEdge},
      _pathCount{pathCount},
      _props(pathCount),
      _tokens(pathCount)
{
  resetTokens();

  for (int i = 0; i < pathCount; ++i) {
      _props[i] = 1. / pathCount;
  }
//  _props[2] = 1.;
}

/** Update path proportions */
void TrafficBalancer::updateProps(const std::vector<double>& props) {
    if (props.size() != _pathCount) {
        throw -123;
    }

    _props = props;
}

/** Assigns tokens to 0 */
void TrafficBalancer::resetTokens() {
    for (int i = 0; i < _tokens.size(); ++i) {
        _tokens[i] = 0;
    }
    _lastTokensResetTime = simTime();
}

/** Updates tokens. Returns path index to route. */
int TrafficBalancer::computePacketPathIndex(Packet* pkt) {
    // Reset tokens if time is up
    simtime_t pktArrivalTime = pkt->getArrivalTime();
    if (pktArrivalTime - _lastTokensResetTime > TOKENS_RESET_INTERVAL_S) {
        resetTokens();
    }

    // Increase tokens
    int pktSize = pkt->getByteLength();
    for (int i = 0; i < _pathCount; ++i) {
        _tokens[i] += _props[i] * pktSize;
    }

    // Path switch
    if (_lastArrivalTime == 0 || pktArrivalTime - _lastArrivalTime > MTBS_MS / 1000) {
        /** Choose path that is respective to max token  */
        _currentPathIndex = std::max_element(_tokens.begin(), _tokens.end()) - _tokens.begin();
    }
    _lastArrivalTime = pktArrivalTime;

    // Decrease token respective to current path
    _tokens[_currentPathIndex] -= pktSize;

    return _currentPathIndex;
}

