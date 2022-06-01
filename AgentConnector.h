/*
 * AgentConnector.h
 *
 *  Created on: Apr 12, 2022
 *      Author: user
 */

#ifndef AGENTCONNECTOR_H_
#define AGENTCONNECTOR_H_

#include <string>
#include <map>
#include <utility>
#include <vector>
#include "types.h"
#include "globals.h"
#include <winsock2.h>

using namespace std;

class AgentConnector {

    SOCKET _sock;

public:
    AgentConnector();
    virtual ~AgentConnector();

    map<EdgePair, PathProportions>
    fetchEdgePathProportions(
        const vector<int>& aggrFlowThroughputs,
        const vector<vector<char>>& pathUtilizations
    );
};

#endif /* AGENTCONNECTOR_H_ */
