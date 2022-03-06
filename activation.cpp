#include<cmath>
#include "utility.h"

void myrelu (float* im, int isize) {
    for(int i=0; i<isize; i++) {
        im[i] = fmax((float)0.0, im[i]);
    }
}