#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include "mkl.h"

float min(float x, float y) {
  if (x<y)
    return x;
  return y;
}

void fc_mkl(char* im, char* wm, char* bm, char* om) {
  int m=0,n=0,k=0,i=0;
  float *A, *B, *C;
  std::fstream file;
  file.open(im, std::ios::in);
  if (file) {
    file >> k;
    file >> m;
    A = (float*) mkl_malloc(m*k*sizeof(float), 32);
    if (A == NULL) {
      printf( "\n ERROR: Can't allocate memory for matrix. Exiting...\n");
      mkl_free(A);
      exit(1);
    }
    for (i = 0; i < (m*k); i++) {
        file >> A[i];
    }
  }
  else {
      printf("File: %s does not exist.\n", im);
      exit(1);
  }
  file.close();
  int k1;
  file.open(wm, std::ios::in);
  if (file) {
    file >> n;
    file >> k1;
    if (k1 != k) {
      printf( "\n ERROR: Matrix dimensions do not align. Exiting...\n");
      exit(1);
    }
    B = (float*) mkl_malloc(n*k*sizeof(float), 32);
    if (B == NULL) {
      printf( "\n ERROR: Can't allocate memory for matrix. Exiting...\n");
      mkl_free(B);
      exit(1);
    }
    for (i = 0; i < (n*k); i++) {
        file >> B[i];
    }
  }
  else {
      printf("File: %s does not exist.\n", wm);
      exit(1);
  }
  file.close();

  int m1,n1;
  file.open(bm, std::ios::in);
  if (file) {
    file >> n1;
    file >> m1;
    if (m1 != m && n1 != n) {
      printf( "\n ERROR: Matrix dimensions do not align. Exiting...\n");
      exit(1);
    }
    C = (float*) mkl_malloc(m*n*sizeof(float), 32);
    if (C == NULL) {
      printf( "\n ERROR: Can't allocate memory for matrix. Exiting...\n");
      mkl_free(C);
      exit(1);
    }
    for (i = 0; i < (m*n); i++) {
        file >> C[i];
    }
  }
  else {
      printf("File: %s does not exist.\n", bm);
      exit(1);
  }
  file.close();

  float* omatrix = (float*) mkl_malloc(m*n*sizeof(float), 32);
  if (omatrix == NULL) {
    printf( "\n ERROR: Can't allocate memory for matrix. Aborting... \n\n");
    mkl_free(omatrix);
    exit(1);
  }

  for (i = 0; i < (m*n); i++) {
    omatrix[i] = 0.0;
  }

  cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, 
              m, n, k, 1.0, A, m, B, k, 0.0, omatrix, m);

  for(i=0; i<m*n; i++) {
    omatrix[i] += C[i];
  }

  file.open(om, std::ios::out);

  file << n << "\n" << m << "\n";
  for(i=0; i<m*n; i++) {
    file << std::fixed << std::setprecision(7) << omatrix[i] << "\n";
  }

  file.close();

  mkl_free(A);
  mkl_free(B);
  mkl_free(C);
  mkl_free(omatrix);
}