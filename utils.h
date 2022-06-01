/*
 * utils.h
 *
 *  Created on: Mar 31, 2022
 *      Author: user
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include "types.h"
#include "globals.h"

std::string makeNodeName(NodeTypes type, int index, int pod = -1);
bool dblEquals(double x, double y, double eps = EPS);
int put(char* buffer, int offset, unsigned x);


#endif /* UTILS_H_ */
