#include<cstdio>
#include<cstring>
#include<vector>
#include<cmath>
#include "utility.h"
#include"helper.h"

// float Sigmoid(float x) {
//     return 1.0/(1+exp(-1.0*x));
// }

// void mysigmoid(std::vector<float>& ivector) {
//     int size = ivector.size();
//     for(int i=0; i<size; i++) {
//         ivector[i] = Sigmoid(ivector[i]);
//     }
// }

void mysoftmax(float* ivector, int isize) {
    double norm = 0.0;
    float val;
    std::vector<float> res(size,0);
    for(int i=0; i<size; i++) {
        val = exp(ivector[i]);
        norm += val;
        res[i] = val;
    }
    for(int i=0; i<size; i++) {
        ivector[i] = (float)((1.0*res[i])/norm);
    }
}

// void prob(char* type, char* iv, char* ov) {
//     std::vector<float> ivector = readvector(iv);
//     if (!strcmp(type, "softmax")) {
//         mysoftmax(ivector);
//     }
//     else if (!strcmp(type, "sigmoid")) {
//         mysigmoid(ivector);
//     }
//     else {
//         // invalid activation function
//         printf("Invalid probability function. Choose either softmax or sigmoid.\n");
//         exit(1);
//     }
//     if (ivector.empty()) {
//         printf("Output vector not generated. \n");
//         exit(1);
//     }
//     printvector(ivector);
//     tofilevector(ivector, ov);
// }