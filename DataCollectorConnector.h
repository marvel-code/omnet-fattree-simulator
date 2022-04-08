/*
 * DataCollectorConnector.h
 *
 *  Created on: Apr 8, 2022
 *      Author: user
 */

#ifndef DATACOLLECTORCONNECTOR_H_
#define DATACOLLECTORCONNECTOR_H_

#include <winsock2.h>
#include <vector>
#include <string>
#include <utility>

class DataCollectorConnector {

    SOCKET _sock;

public:
    DataCollectorConnector();
    ~DataCollectorConnector();
    void sendStateFromNode(std::string& node, std::vector<std::pair<std::string, int>>& utilizations);
};

#endif /* DATACOLLECTORCONNECTOR_H_ */
