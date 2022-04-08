

#ifndef GLOBALS_H_
#define GLOBALS_H_

// Common
const double EPS = 1e-5;

// Topology
const int K = 4;
const int POD_COUNT = K;
const int CORE_COUNT = K * K / 4;
const int AGGR_PER_POD = K / 2;
const int EDGE_PER_POD = AGGR_PER_POD;
const int NODE_COUNT = K * K * 5 / 4;

// Simulation
const double TACT_S = 0.1; // Tact duration in seconds

// Traffic balancer
const double MTBS_MS = 50; // Minimum Time Before Switch-ability in seconds
const double TOKENS_RESET_INTERVAL_S = 100; // ~0.5

#endif
