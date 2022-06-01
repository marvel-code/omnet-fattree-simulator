

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
const int EDGE_COUNT = K * K / 2;

const int PATH_COUNT_TO_OTHER_POD_EDGE = CORE_COUNT * AGGR_PER_POD * AGGR_PER_POD;
const int PATH_COUNT_TO_SAME_POD_EDGE = CORE_COUNT * AGGR_PER_POD * (AGGR_PER_POD - 1) + AGGR_PER_POD;
const int PATH_COUNT_PER_EDGE = PATH_COUNT_TO_OTHER_POD_EDGE * (K - 1) * EDGE_PER_POD + PATH_COUNT_TO_SAME_POD_EDGE * (EDGE_PER_POD - 1);

const int EDGE_PAIRS = EDGE_COUNT * (EDGE_COUNT - 1);
const int SAME_POD_EDGE_PAIRS = K*K * (K - 2) / 4;
const int OTHER_POD_EDGE_PAIRS = K*K*K * (K  - 1) / 4;
const int PATH_COUNT = SAME_POD_EDGE_PAIRS * PATH_COUNT_TO_SAME_POD_EDGE + OTHER_POD_EDGE_PAIRS * PATH_COUNT_TO_OTHER_POD_EDGE;
const int PROPS_COUNT = PATH_COUNT;

// Simulation
const double TACT_S = 0.1; // Tact duration in seconds

// Traffic balancer
const double MTBS_MS = 50; // Minimum Time Before Switch-ability in seconds
const double TOKENS_RESET_INTERVAL_S = 100; // ~0.5

// Link state
const double UTILIZATION_INTERVAL_S = TACT_S;
const int CAPACITY_BPS = 100 * 1024 * 1024;

#endif
