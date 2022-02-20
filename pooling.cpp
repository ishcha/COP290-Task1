#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<sstream>

#include"helper.h"

float mpool(int si, int sj, int ei, int ej, std::vector<std::vector<float> > im ) {
    float M = im[si][sj];
    for(int i=si; i<ei; i++) {
        for(int j=sj; j<ej; j++) {
            M = std::max(M,im[i][j]);
        }
    }
    return M;
}

float apool(int si, int sj, int ei, int ej, std::vector<std::vector<float> > im ) {
    double M = 0.0;
    int size = (ei-si)*(ej-sj);
    for(int i=si; i<ei; i++) {
        for(int j=sj; j<ej; j++) {
            M += (1.0*im[i][j])/size;
        }
    }
    return (float)M;
}

std::vector<std::vector<float> > maxpool(std::vector<std::vector<float> > im, int stride) {
    int r1 = im.size(), c1 = im[0].size();
    std::vector<std::vector<float> > omatrix;
    if ((r1%stride != 0) || (c1%stride != 0)) {
        // stride is not a multiple of size of matrix
        printf("Invalid value of stride. It should be a multiple of size of the matrix.\n");
        exit(1);
    }
    else {
        float val;
        for(int i=0; i<r1; i+=stride) {
            std::vector<float> res;
            for(int j=0; j<c1; j+=stride) {
                val = mpool(i,j,i+stride,j+stride,im);
                res.push_back(val);
            }
            omatrix.push_back(res);
        }
    }
    return omatrix;
}

std::vector<std::vector<float> > avgpool(std::vector<std::vector<float> > im, int stride) {
    int r1 = im.size(), c1 = im[0].size();
    std::vector<std::vector<float> > omatrix;
    if ((r1%stride != 0) || (c1%stride != 0)) {
        // stride is not a multiple of size of matrix
        printf("Invalid value of stride. It should be a multiple of size of the matrix.\n");
    }
    else {
        float val;
        for(int i=0; i<r1; i+=stride) {
            std::vector<float> res;
            for(int j=0; j<c1; j+=stride) {
                val = apool(i,j,i+stride,j+stride,im);
                res.push_back(val);
            }
            omatrix.push_back(res);
        }
    }
    return omatrix;
}

void pool(char* type, char* im, char* stride, char* om) {
    std::vector<std::vector<float> > imatrix = readmatrix(im);
    std::vector<std::vector<float> > omatrix;
    std::stringstream ss(stride);
    int st;
    if (ss >> st) {
        if(!strcmp(type, "max")) {
            omatrix = maxpool(imatrix, st);
        }
        else if(!strcmp(type,"average")) {
            omatrix = avgpool(imatrix, st);
        }
        else {
            // invalid type
            printf("Invalid type of pooling. Choose either max or average.\n");
            exit(1);
        }
    }
    else {
        printf("Invalid input for stride. Stride should be an integer.\n");
        exit(1);
    }
    if (omatrix.empty()) {
        printf("Output matrix not generated. \n");
        exit(1);
    }
    printmatrix(omatrix);
    tofile(omatrix, om);
}