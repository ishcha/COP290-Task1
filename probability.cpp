#include<cmath>
#include "utility.h"

void mysoftmax(float* ivector, int isize) {
    double norm = 0.0;
    for(int i=0; i<isize; i++) {
        ivector[i] = exp(ivector[i]);
        norm += ivector[i];
    }
    for(int i=0; i<isize; i++) {
        ivector[i] = (float)((1.0*ivector[i])/norm);
    }
}