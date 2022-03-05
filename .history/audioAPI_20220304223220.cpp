#include <fstream>
#include <iostream>
#include "audioAPI.h" // remove this later
#include "utility.h"
#include "dnn_weights.h"


using namespace std;
pred_t* libaudioAPI(const char* audiofeatures, pred_t* pred) {
    ifstream fin;
    fin.open(audiofeatures);
    if(!fin) {
        cout << "Unable to open file "<< audiofeatures << ". Please check the file path and try again. Aborting.. " << '\n';
        exit(1);
    }
    float* input;
    // take input
    for (int i = 0; i < 250; i++) {
        if (!(fin >> *(input+i))) {
            cout << "Unable to read input file " << audiofeatures <<". Please check file type and try again. Aborting.. " << '\n';
            exit(1);
        }
    }
    // apply mkl
    float wt1[250*144] = IP1_WT;
    float b1[144] = IP1_BIAS;
    float* out1 = fc_mkl(input, 1, 250, wt1, 144, b1);
    // apply the func seq
    myrelu(out1, 144);
    // FC2
    float wt2[144*144] = IP2_WT;
    float b2[144] = IP2_BIAS;
    float* out2 = fc_mkl(out1, 1, 144, wt2, 144, b2);
    myrelu(out2, 144);

    // FC3
    float wt3[144*144] = IP3_WT;
    float b3[144] = IP3_BIAS;
    float* out3 = fc_mkl(out2, 1, 144, wt3, 144, b3);
    myrelu(out3, 144);

    //FC4
    float wt4[144*12] = IP4_WT;
    float b4[12] = IP4_BIAS;
    float* out3 = fc_mkl(out2, 1, 144, wt3, 12, b3);
    //softmax
    mysoftmax(out3, 12);
    // after softmax, pick the highest 3 prob and populate pred_t*
    int maxa[3] = {-1}, idx[3];
    for (int i = 0; i < 12; i++) {
        float val = out3[i];
        if (val > maxa[0]) {
            maxa[2] = maxa[1];
            maxa[1] = maxa[0];
            maxa[0] = val;
            idx[2] = idx[1];
            idx[1] = idx[0];
            idx[0] = i;
        }
        else if (val > maxa[1]) {
            maxa[2] = maxa[1];
            maxa[1] = val;
            idx[2] = idx[1];
            idx[1] = i;
        }
        else if (val > maxa[2]) {
            maxa[2] = val;
            idx[2] = i;
        }
    }
    for (int i = 0; i < 3; i++) {
        pred
    }
    
}