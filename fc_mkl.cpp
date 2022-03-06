#include "utility.h"
#include "mkl.h"

float min(float x, float y) {
  if (x<y)
    return x;
  return y;
}

void fc_mkl(float* im, int m, int k, float* wm, int n, float* bm, float* res) {
  // im -> mxk  wm-> kxn  bm -> mxn
  // check for the correct dimensions before hand when reading from file.
  // row major representations

  for(int i=0; i<n*m; i++)
    res[i] = bm[i];

  // 32 byte aligned data as input
  cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, 1.0, im, k, wm, n, 1.0, res, n);
}