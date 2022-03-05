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
    
    // float* out1 = fc_mkl(input, 1, 250, IP1_WT, 144, &IP1_BIAS);
    // apply the func seq
    // after softmax, pick the highest 3 prob and populate pred_t*
}