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

#include "node.h"
#include <omnetpp.h>
#include "globals.h"
#include <stdio.h>
#include <string>
#include "packet_m.h"
#include "utils.h"
#include "nodeRouter.h"
#include <map>
#include "trafficGenerator.h"
#include <cmath>
#include "timePacket_m.h"
#include "statePacket_m.h"


Define_Module(Node);



void Node::initialize()
{
    _type = (NodeTypes)par("type").intValue();
    _index = par("number").intValue();
    _pod = par("pod").intValue();
    _router = new NodeRouter(*this);

    _f.open(std::string("log/") + getName() + ".txt");

    scheduleAt(simTime() + TACT_S, new cMessage("tact"));

    // Init link states
    if (_type == NodeTypes::Core) {
        for (int p = 0; p < POD_COUNT; ++p) {
            for (int a = 0; a < AGGR_PER_POD; ++a) {
                _linkStates[makeNodeName(NodeTypes::Aggr, a, p)] = new LinkState();
            }
        }
    } else if (_type == NodeTypes::Aggr) {
        for (int e = 0; e < EDGE_PER_POD; ++e) {
            _linkStates[makeNodeName(NodeTypes::Edge, e, _pod)] = new LinkState();
        }
        for (int c = 0; c < CORE_COUNT; ++c) {
            _linkStates[makeNodeName(NodeTypes::Core, c)] = new LinkState();
        }
    } else if (_type == NodeTypes::Edge) {
        for (int a = 0; a < AGGR_PER_POD; ++a) {
            _linkStates[makeNodeName(NodeTypes::Aggr, a, _pod)] = new LinkState();
        }
    }

    // Launch traffic generator
    if (_type == NodeTypes::Edge) {
        _trafficGenerator = new TrafficGenerator(*this);
        _trafficGenerator->launch();
        // Set tact finish time through controller from edge00
        if (_pod == 0 && _index == 0) {
            TimePacket* timePkt = new TimePacket("tact-finish-time");
            timePkt->setTime(_trafficGenerator->getFinishTime().dbl());
            this->send(timePkt, "controller$o");
        }
    }
}

void Node::processTact() {
    // Log utilizations
    StatePacket* statePkt = new StatePacket("node-state");
    statePkt->setTargetNode(getName());
    statePkt->setSourceNodesArraySize(_linkStates.size());
    statePkt->setNodeUtilizationsArraySize(_linkStates.size());
    int index = 0;
    for (auto it = _linkStates.begin(); it != _linkStates.end(); ++it, ++index) {
        it->second->refreshUtilization();
        statePkt->setSourceNodes(index, it->first.c_str());
        statePkt->setNodeUtilizations(index, it->second->getUtilization());
    }
    send(statePkt, "controller$o");
}

void Node::handleMessage(cMessage *msg)
{
    // Time set
    if (msg->isName("tact-finish-time")) {
        TimePacket* timePkt = (TimePacket*)msg;
        _tactFinishTime = timePkt->getTime();
        delete msg;
        return;
    }

    // Tact
    if (msg->isName("tact")) {
        processTact();
        if (simTime() < _tactFinishTime) {
            scheduleAt(simTime() + TACT_S, msg);
        } else {
            delete msg;
        }
        return;
    }

    // Traffic
    _lastPacketArrival = simTime();
    Packet* pkt = (Packet*)msg;
    if (_type == NodeTypes::Edge && pkt->isSelfMessage()) {
        _router->sendTo(pkt, pkt->getDestEdge());
    } else {
        std::string sender(msg->getSenderModule()->getName());
        _linkStates[sender]->processPacket(pkt);
        _router->sendNext(pkt);
    }
}

void Node::finish() {
    _f.close();
}

int Node::getIndex() {
    return _index;
}

int Node::getPod() {
    return _pod;
}

NodeTypes Node::getType() {
    return _type;
}

NodeRouter* Node::getRouter() {
    return _router;
}
