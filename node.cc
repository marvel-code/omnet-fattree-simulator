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

Define_Module(Node);



void Node::initialize()
{
    _type = (NodeTypes)par("type").intValue();
    _index = par("number").intValue();
    _pod = par("pod").intValue();
    _router = new NodeRouter(*this);

    if (_type == NodeTypes::Edge) {
        _trafficGenerator = new TrafficGenerator(*this);
        _trafficGenerator->launch();
    }
}

void Node::handleMessage(cMessage *msg)
{
    Packet* pkt = (Packet*)msg;
    if (_type == NodeTypes::Edge && pkt->isSelfMessage()) {
        _router->sendTo(pkt, pkt->getDestEdge());
    } else {
        _router->sendNext(pkt);
    }
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
