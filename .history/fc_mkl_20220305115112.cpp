#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "utility.h"
// #include <fstream>
// #include <iomanip>
#include "mkl.h"

float min(float x, float y) {
  if (x<y)
    return x;
  return y;
}

float* fc_mkl(float* im, int m, int k, float* wm, int n, float* bm) {
  // im -> mxk  wm-> kxn  bm -> mxn
  // check for the correct dimensions before hand when reading from file.
  // row major representations

  // int m=0,n=0,k=0,i=0;
  float *A, *B;
  // std::fstream file;
  // file.open(im, std::ios::in);
  // if (file) {
  //   file >> k;
  //   file >> m;
    A = (float*) mkl_malloc(m*k*sizeof(float), 32);
    if (A == NULL) {
      printf( "\n ERROR: Can't allocate memory for matrix. Exiting...\n");
      mkl_free(A);
      exit(1);
    // }
    for (int i = 0; i < (m*k); i++) {
        A[i] = im[i];
    }
  // }
  // else {
  //     printf("File: %s does not exist.\n", im);
  //     exit(1);
  // }
  // file.close();
  // int k1;
  // file.open(wm, std::ios::in);
  // if (file) {
  //   file >> n;
  //   file >> k1;
  //   if (k1 != k) {
  //     printf( "\n ERROR: Matrix dimensions do not align. Exiting...\n");
  //     exit(1);
  //   }
    B = (float*) mkl_malloc(n*k*sizeof(float), 32);
    if (B == NULL) {
      printf( "\n ERROR: Can't allocate memory for matrix. Exiting...\n");
      mkl_free(B);
      exit(1);
    }
    for (int i = 0; i < (k*n); i++) {
        B[i] = wm[i];
    }
  // }
  // else {
  //     printf("File: %s does not exist.\n", wm);
  //     exit(1);
  // }
  // file.close();

  // int m1,n1;
  // file.open(bm, std::ios::in);
  // if (file) {
  //   file >> n1;
  //   file >> m1;
  //   if (m1 != m && n1 != n) {
  //     printf( "\n ERROR: Matrix dimensions do not align. Exiting...\n");
  //     exit(1);
  //   }
    // C = (float*) mkl_malloc(m*n*sizeof(float), 32);
    // if (C == NULL) {
    //   printf( "\n ERROR: Can't allocate memory for matrix. Exiting...\n");
    //   mkl_free(C);
    //   exit(1);
    // }
    // for (i = 0; i < (m*n); i++) {
    //     C[i] = bm[i];
    // }
  // }
  // else {
  //     printf("File: %s does not exist.\n", bm);
  //     exit(1);
  // }
  // file.close();

  float* omatrix = (float*) mkl_malloc(m*n*sizeof(float), 32);
  if (omatrix == NULL) {
    printf( "\n ERROR: Can't allocate memory for matrix. Aborting... \n\n");
    mkl_free(omatrix);
    exit(1);
  }

  for (int i = 0; i < (m*n); i++) {
    omatrix[i] = bm[i];
  }

  // rowmajor and dimensions change
  cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
              m, n, k, 1.0, A, k, B, n, 1.0, omatrix, n);

  mkl_free(A);
  mkl_free(B);
  // mkl_free(C);
  float* res = new float[m*n];
  for(int i=0; i<n*m; i++)
    res[i] = omatrix[i];
  mkl_free(omatrix);
  return res;
}