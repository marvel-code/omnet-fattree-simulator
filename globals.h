

#ifndef GLOBALS_H_
#define GLOBALS_H_

const int K = 4;
const int POD_COUNT = K;
const int CORE_COUNT = K * K / 4;
const int AGGR_PER_POD = K / 2;
const int EDGE_PER_POD = AGGR_PER_POD;

const double TACT_S = 0.1; // Tact duration in seconds
const double TACT_IDLE_OFF_S = 1; // After TACT_IDLE_OFF_S seconds after last packet arrival, tact cycle is off
const int PACKET_SIZE_BITS = 64 * 1024 * 8;

#endif

