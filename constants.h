#include "dnn_weights.h"
#include <cstdalign>

alignas(32) float wt1[250*144] = IP1_WT;
alignas(32) float b1[144] = IP1_BIAS;
alignas(32) float wt2[144*144] = IP2_WT;
alignas(32) float b2[144] = IP2_BIAS;
alignas(32) float wt3[144*144] = IP3_WT;
alignas(32) float b3[144] = IP3_BIAS;
alignas(32) float wt4[144*12] = IP4_WT;
alignas(32) float b4[12] = IP4_BIAS;