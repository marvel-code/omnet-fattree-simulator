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

#ifndef __MYNETWORK_NODE_H_
#define __MYNETWORK_NODE_H_

#include <omnetpp.h>
#include "types.h"
#include <string>

class NodeRouter;
class TrafficGenerator;

using namespace omnetpp;

class Node : public cSimpleModule
{
    NodeTypes _type;
    int _pod;
    int _index;
    NodeRouter* _router;
    TrafficGenerator* _trafficGenerator;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  public:
    int getIndex();
    NodeTypes getType();
    int getPod();
    NodeRouter* getRouter();
};

#endif
