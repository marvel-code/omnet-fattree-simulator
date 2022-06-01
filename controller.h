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

#ifndef __MYNETWORK_CONTROLLER_H_
#define __MYNETWORK_CONTROLLER_H_

#include <omnetpp.h>
#include "AgentConnector.h"
#include <map>
#include "types.h"
#include <string>
#include <vector>
#include <iostream>

using namespace omnetpp;

/** Edge ordered pair information */
struct EdgePairInfo {

    /** Source edge */
    std::string source;
    /** Target edge */
    std::string target;

    /** Paths */
    std::vector<std::string> paths;
    /** Path utilizations */
    std::vector<char> pathUtilizations;

    /** Aggregation flow throughput */
    int aggrFlowThroughput = 0;


    EdgePairInfo(std::string source, std::string target): source{source}, target{target} {}

    int getPathCount() {
        return paths.size();
    }

    void addPath(std::string path) {
        paths.push_back(path);
        pathUtilizations.push_back(0);
    }

    void reset() {
        for (int i = 0; i < pathUtilizations.size(); ++i) {
            pathUtilizations[i] = 0;
        }
        aggrFlowThroughput = 0;
    }

    void processUtilization(std::string node1, std::string node2, char utilization) {
        std::string link = node1 + node2;
        for (int i = 0; i < paths.size(); ++i) {
            bool hasLink = paths[i].find(link) != std::string::npos;
            if (hasLink && pathUtilizations[i] < utilization) {
                pathUtilizations[i] = utilization;
            }
        }
    }
};

class Controller : public cSimpleModule
{
    simtime_t _tactFinishTime;
    AgentConnector _agentConnector;
    std::vector<EdgePairInfo> _edgePairInfos;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    EdgePairInfo& findEdgePairInfo(const std::string& source, const std::string& target);
    vector<vector<char>> getPairsPathUtilizations();
    vector<int> getPairsAggrFlowThoughputs();

    void updateEdgeProps(map<EdgePair, PathProportions> props);
};

#endif
