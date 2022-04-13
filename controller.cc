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

#include "controller.h"
#include "globals.h"
#include "timePacket_m.h"
#include "statePacket_m.h"
#include <string>
#include <vector>
#include <utility>
#include "utils.h"

Define_Module(Controller);

void Controller::initialize()
{
    // Init edge pair infos
    for (int pod = 0; pod < POD_COUNT; ++pod) {
        for (int index = 0; index < EDGE_PER_POD; ++index) {
            std::string source = makeNodeName(NodeTypes::Edge, index, pod);
            for (int p = 0; p < POD_COUNT; ++p) {
                for (int e = 0; e < EDGE_PER_POD; ++e) {
                    if (e == index && p == pod)
                        continue;
                    std::string target = makeNodeName(NodeTypes::Edge, e, p);
                    EdgePairInfo epi(source, target);
                    std::string path;
                    if (p == pod) {
                        // Edge on the same pod (10 for K=4)
                        for (int a1 = 0; a1 < AGGR_PER_POD; ++a1) {
                            for (int a2 = 0; a2 < AGGR_PER_POD; ++a2) {
                                if (a1 == a2)
                                    continue;
                                for (int c = 0; c < CORE_COUNT; ++c) {
                                    path = source;
                                    path += makeNodeName(NodeTypes::Aggr, a1, pod);
                                    path += makeNodeName(NodeTypes::Core, c);
                                    path += makeNodeName(NodeTypes::Aggr, a2, p);
                                    path += target;
                                    epi.addPath(path);
                                }
                            }
                            path = source;
                            path += makeNodeName(NodeTypes::Aggr, a1, pod);
                            path += target;
                            epi.addPath(path);
                        }
                    } else {
                        // Edge on the other pod (16 for K=4)
                        for (int a1 = 0; a1 < AGGR_PER_POD; ++a1) {
                            for (int a2 = 0; a2 < AGGR_PER_POD; ++a2) {
                                for (int c = 0; c < CORE_COUNT; ++c) {
                                    path = source;
                                    path += makeNodeName(NodeTypes::Aggr, a1, pod);
                                    path += makeNodeName(NodeTypes::Core, c);
                                    path += makeNodeName(NodeTypes::Aggr, a2, p);
                                    path += target;
                                    epi.addPath(path);
                                }
                            }
                        }
                    }
                    _edgePairInfos.push_back(epi);
                }
            }
        }
    }

    // Init tact
    scheduleAt(TACT_S * 1.5, new cMessage("tact")); // 1.5, because at 1. network state is initialized
}

void Controller::handleMessage(cMessage *msg)
{
    // Tact
    if (msg->isName("tact") && simTime() < _tactFinishTime) {
        scheduleAt(simTime() + TACT_S, msg);

        // Update path proportions from agent
        auto aft = getPairsAggrFlowThoughputs();
        auto pu = getPairsPathUtilizations();
        auto newProps = _agentConnector.fetchEdgePathProportions(aft, pu);
        updateEdgeProps(newProps);

        // Reset _edgePairInfos for next update
        for (auto epi: _edgePairInfos) {
            epi.reset();
        }
        return;
    }

    // Time set
    if (msg->isName("tact-finish-time")) {
        // Controller
        TimePacket* timePkt = (TimePacket*)msg;
        _tactFinishTime = timePkt->getTime();
        // Fat-tree nodes
        for (int i = 0; i < NODE_COUNT; ++i) {
            cMessage* dupMsg = msg->dup();
            send(dupMsg, "down$o", i);
        }

        delete msg;
        return;
    }

    // Node state
    if (msg->isName("node-state")) {
        StatePacket* statePkt = (StatePacket*)msg;

        // Update _edgePairInfos
        std::string targetNode = statePkt->getTargetNode();
        std::vector<std::pair<std::string, int>> utilizations;
        for (int i = 0; i < statePkt->getSourceNodesArraySize(); ++i) {
            std::string sourceNode = statePkt->getSourceNodes(i);
            int utilization = statePkt->getNodeUtilizations(i);
            for (auto epi: _edgePairInfos) {
                epi.processUtilization(sourceNode, targetNode, utilization);
            }
        }

        delete msg;
        return;
    }

    delete msg;
}

EdgePairInfo
Controller::findEdgePairInfo(std::string source, std::string target) {
    for (auto epi: _edgePairInfos) {
        if (epi.source == source && epi.target == target)
            return epi;
    }
    throw "No epi found for " + source + ", " + target;
}

vector<vector<char>>
Controller::getPairsPathUtilizations() {
    vector<vector<char>> pairsPathUtilizations;
    for (int i = 0; i < _edgePairInfos.size(); ++i) {
        pairsPathUtilizations.push_back(_edgePairInfos[i].pathUtilizations);
    }
    return pairsPathUtilizations;
}

vector<int>
Controller::getPairsAggrFlowThoughputs() {
    vector<int> allAft;
    for (int i = 0; i < _edgePairInfos.size(); ++i) {
        allAft.push_back(_edgePairInfos[i].aggrFlowThroughput);
    }
    return allAft;
}

void Controller::updateEdgeProps(map<EdgePair, PathProportions> props) {
    //  ...
}
