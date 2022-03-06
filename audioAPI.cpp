#include <fstream>
#include <iostream>
#include "audioAPI.h" // remove this later
#include "utility.h"
#include <cstdalign>

pred_t* libaudioAPI(const char* audiofeatures, pred_t* pred) {
    std::ifstream fin;
    fin.open(audiofeatures);
    if(!fin) {
        std::cout << "Unable to open file "<< audiofeatures << ". Please check the file path and try again. Aborting.. " << '\n';
        exit(1);
    }
    alignas(32) float input[250];
    // take input
    for (int i = 0; i < 250; i++) {
        if (!(fin >> input[i])) {
            std::cout << "Error reading input file " << audiofeatures <<". Please check file type and try again. Aborting.. " << '\n';
            exit(1);
        }
    }
    // apply mkl
    alignas(32) float out1[144];
    if (out1 == NULL) {
        std::cout << "\n ERROR: Can't allocate memory for matrix. Exiting...\n";
        exit(1);
    }

    fc_mkl(input, 1, 250, wt1, 144, b1, out1);
    myrelu(out1, 144);

    // FC2
    alignas(32) float out2[144];
    if (out2 == NULL) {
        std::cout << "\n ERROR: Can't allocate memory for matrix. Exiting...\n";
        exit(1);
    }
    fc_mkl(out1, 1, 144, wt2, 144, b2, out2);
    myrelu(out2, 144);

    // FC3
    alignas(32) float out3[144];
    if (out3 == NULL) {
        std::cout << "\n ERROR: Can't allocate memory for matrix. Exiting...\n";
        exit(1);
    }
    fc_mkl(out2, 1, 144, wt3, 144, b3, out3);
    myrelu(out3, 144);

    //FC4
    alignas(32) float out4[12];
    if (out4 == NULL) {
        std::cout << "\n ERROR: Can't allocate memory for matrix. Exiting...\n";
        exit(1);
    }
    fc_mkl(out3, 1, 144, wt4, 12, b4, out4);

    mysoftmax(out4, 12);

    for(int i=0; i<12; i++)
        std::cout<<out4[i]<<" ";

    // after softmax, pick the highest 3 prob and populate pred_t*

    float maxa[3] = {-1.0};
    int idx[3];
    for (int i = 0; i < 12; i++) {
        float val = out4[i];
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
        pred[i].label = idx[i];
        pred[i].prob = maxa[i];
    }
    return pred;
}
