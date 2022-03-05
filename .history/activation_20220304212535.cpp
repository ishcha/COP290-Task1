#include<cstdio>
#include<cstring>
#include<vector>
#include<cmath>
#include "utility.h"

#include"helper.h"

// float Tanh(float x) {
//     return 2.0/(exp(-2.0*x) + 1) - 1.0;
// }

float Relu(float x) {
    return std::max((float)0.0, x);
}

// void mytanh (std::vector<std::vector<float> > &im) {
//     int r = im.size(), c = im[0].size();
//     for(int i=0; i<r; i++) {
//         for(int j=0; j<c; j++) {
//             im[i][j] = Tanh(im[i][j]);
//         }
//     }
// }

float* myrelu (float* im, int isize) {
    for(int i=0; i<isize; i++) {
        im[i][j] = Relu(im[i]);
    }
}

// void act(char* type, char* im, char* om) {
//     std::vector<std::vector<float> > imatrix = readmatrix(im);
//     if (!strcmp(type, "tanh")) {
//         mytanh(imatrix);
//     }
//     else if (!strcmp(type, "relu")) {
//         myrelu(imatrix);
//     }
//     else {
//         // invalid activation function
//         printf("Invalid activation function. Choose either tanh or relu.\n");
//         exit(1);
//     }
//     if (imatrix.empty()) {
//         printf("Output matrix not generated. \n");
//         exit(1);
//     }
//     printmatrix(imatrix);
//     tofile(imatrix, om);
// }