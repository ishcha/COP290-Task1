#include "dnn_weights.h"

float wt1[250*144] = IP1_WT;
float b1[144] = IP1_BIAS;
float wt2[144*144] = IP2_WT;
float b2[144] = IP2_BIAS;
float wt3[144*144] = IP3_WT;
float b3[144] = IP3_BIAS;
float wt4[144*12] = IP4_WT;
float b4[12] = IP4_BIAS;

typedef struct {
    int label;
    float prob;
} pred_t;

extern pred_t* libaudioAPI(const char* audiofeatures, pred_t* pred); 
// audiofeatures is the file name containing the audio features
