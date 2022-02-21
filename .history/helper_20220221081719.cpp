#include<fstream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<iomanip>

#include"helper.h"


std::vector<std::vector<float> > readmatrix(char* input) {
    // check eof reached in case of wrong input
    std::fstream file;
    file.open(input, std::ios::in);
    if (file) {
        int row, col;
        file >> col;
        file >> row;
        std::vector<std::vector<float> > matrix(row , std::vector<float> (col, 0));
        for(int i=0; i<col; i++) {
            for(int j=0; j<row; j++) {
                file >> matrix[j][i];
            }
        }
        return matrix;
    }
    else {
        printf("File: %s does not exist.\n", input);
        exit(1);
    }
}

void tofile(std::vector<std::vector<float> > omatrix, char* output) {
    std::fstream file;
    file.open(output, std::ios::out);
    int r1 = omatrix.size(), c1 = omatrix[0].size();
    file << std::fixed << std::setprecision(7) << c1 << "\n" << r1 << "\n";
    for(int i=0; i<c1; i++){
        for(int j=0; j<r1; j++){
            file << omatrix[j][i] << "\n";
        }
    }
    return;
}

void printmatrix(std::vector<std::vector<float> > matrix) {
    int r1 = matrix.size(), c1 = matrix[0].size();
    for(int i=0; i<r1; i++){
        for(int j=0; j<c1; j++){
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

std::vector<float> readvector(char* input) {
    std::fstream file;
    file.open(input, std::ios::in);
    if (file) {
        int size;
        file >> size;
        std::vector<float> vec(size,0);
        for(int i=0; i<size; i++) {
            file >> vec[i];
        }
        return vec;
    }
    else {
        printf("File: %s does not exist.\n", input);
        exit(1);
    }
}

void tofilevector(std::vector<float> ovector, char* output) {
    std::fstream file;
    file.open(output, std::ios::out);
    int size = ovector.size();
    file << size << "\n";
    for(int i=0; i<size; i++){
        file << ovector[i] << "\n";
    }
    return;
}

void printvector(std::vector<float> vec) {
    int size = vec.size();
    for(int j=0; j<size; j++){
        printf("%f ", vec[j]);
    }
    printf("\n");
}