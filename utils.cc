/*
 * utils.cc
 *
 *  Created on: Mar 31, 2022
 *      Author: user
 */

#include "utils.h"
#include "globals.h"
#include <math.h>

std::string makeNodeName(NodeTypes type, int index, int pod) {
    std::string result;
    if (type == NodeTypes::Core) result = "core";
    else if (type == NodeTypes::Aggr) result = "aggr";
    else if (type == NodeTypes::Edge) result = "edge";
    if (type != NodeTypes::Core) result += std::to_string(pod);
    result += std::to_string(index);
    return result;
}

bool dblEquals(double x, double y, double eps) {
    return std::abs(x - y) < eps;
}
