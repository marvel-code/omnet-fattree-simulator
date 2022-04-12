
/*
 * nodeRouter.h
 *
 *  Created on: Mar 30, 2022
 *      Author: user
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <vector>
#include <utility>
#include <string>

enum NodeTypes {
    Core = 0,
    Aggr = 1,
    Edge = 2,
};

using NodePair = std::pair<std::string, std::string>;
using EdgePair = NodePair;
using PathProportions = std::vector<double>;


#endif
