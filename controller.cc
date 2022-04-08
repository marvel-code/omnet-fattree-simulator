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

Define_Module(Controller);

void Controller::initialize()
{
    scheduleAt(TACT_S * 1.5, new cMessage("tact")); // 1.5, because at 1. network state is initialized
}

void Controller::handleMessage(cMessage *msg)
{
    // Tact
    if (msg->isName("tact") && simTime() < _tactFinishTime) {
        scheduleAt(simTime() + TACT_S, msg); // 1.5, because at 1. network state is initialized
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

    if (msg->isName("node-state")) {
        StatePacket* statePkt = (StatePacket*)msg;

        // send to DataController

        delete msg;
        return;
    }

    delete msg;
}
