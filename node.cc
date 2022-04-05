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

    if (_type == NodeTypes::Edge) {
        _trafficGenerator = new TrafficGenerator(*this);
        _trafficGenerator->launch();
    }
}

void Node::processTact() {
    // Log utilizations
    for (auto it = _linkStates.begin(); it != _linkStates.end(); ++it) {
        it->second->refreshUtilization();
        _f << std::round(simTime().dbl() * 1000) << "\t" << it->first << "\t" << it->second->getUtilization() << "\n";
    }
}

void Node::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage() && std::string(msg->getName()) == "tact") {
        processTact();
        if (simTime() - _lastPacketArrival < TACT_IDLE_OFF_S) {
            scheduleAt(simTime() + TACT_S, msg);
        }
        return;
    }

    _lastPacketArrival = simTime();
    Packet* pkt = (Packet*)msg;
    if (_type == NodeTypes::Edge && pkt->isSelfMessage()) {
        _router->sendTo(pkt, pkt->getDestEdge());
    } else {
        std::string sender(msg->getSenderModule()->getName());
        LinkState* linkState = _linkStates[sender];
        linkState->processPacket(pkt);
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
