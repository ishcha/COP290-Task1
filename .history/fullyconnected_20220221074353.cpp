#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<omp.h>

#include"helper.h"

std::vector<std::vector<float> > matmul(std::vector<std::vector<float> > imatrix, std::vector<std::vector<float> > wmatrix) {
    int r1 = imatrix.size(), c1 = imatrix[0].size();
    int r2 = wmatrix.size(), c2 = wmatrix[0].size();
    std::vector<std::vector<float> > omatrix;
    if (r2 != c1) {
        // dimensions of wmat and inputmat do not align
        // raise error
        printf("Dimensions of weight matrix and input matrix do not align.\n");
        exit(1);
    }
    else {
        for(int i=0; i<r1; i++) {
            std::vector<float> r;
            for(int j=0; j<c2; j++) {
                double res=0;
                for(int k=0; k<c1; k++) {
                    res += (imatrix[i][k] * wmatrix[k][j]);
                }
                r.push_back((float)res);
            }
            omatrix.push_back(r);
        }
    }
    return omatrix;
}

void matadd(std::vector<std::vector<float> > &omatrix, std::vector<std::vector<float> > bmatrix) {
    int r1 = omatrix.size(), c1 = omatrix[0].size();
    int r2 = bmatrix.size(), c2 = bmatrix[0].size();
    if (r1 != r2 || c1 != c2) {
        // raise error
        printf("Dimensions of bias matrix and input matrix do not align.\n");
        exit(1);
    }
    else {
        for(int i=0; i<r1; i++) {
            for(int j=0; j<c1; j++) {
                omatrix[i][j] += bmatrix[i][j];
            }
        }
    }
    return;
}

void fc(char* im, char* wm, char* bm, char* om) {
    std::vector<std::vector<float> > imatrix = readmatrix(im);
    std::vector<std::vector<float> > wmatrix = readmatrix(wm);
    std::vector<std::vector<float> > bmatrix = readmatrix(bm);
    std::vector<std::vector<float> > omatrix;
    omatrix = matmul(imatrix, wmatrix);
    matadd(omatrix, bmatrix);
    if (omatrix.empty()) {
        printf("Output matrix not generated.\n");
        exit(1);
    }
    printmatrix(omatrix);
    tofile(omatrix, om);
}