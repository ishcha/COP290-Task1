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

  float *A, *B;
  A = (float*) mkl_malloc(m*k*sizeof(float), 32);

  if (A == NULL) {
    printf( "\n ERROR: Can't allocate memory for matrix. Exiting...\n");
    mkl_free(A);
    exit(1);
  // }

  for (int i = 0; i < (m*k); i++) {
      A[i] = im[i];
  }
  
  B = (float*) mkl_malloc(n*k*sizeof(float), 32);
  if (B == NULL) {
    printf( "\n ERROR: Can't allocate memory for matrix. Exiting...\n");
    mkl_free(B);
    exit(1);
  }
  for (int i = 0; i < (k*n); i++) {
      B[i] = wm[i];
  }
  
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
  float* res = new float[m*n];
  for(int i=0; i<n*m; i++)
    res[i] = omatrix[i];
  mkl_free(omatrix);
  return res;
}