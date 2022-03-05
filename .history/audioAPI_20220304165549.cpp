#include <fstream>
#include <iostream>
#include "audioAPI.h" // remove this later

using namespace std;
pred_t* libaudioAPI(const char* audiofeatures, pred_t* pred) {
    ifstream fin;
    fin.open(audiofeatures);
    if(!fin) {
        cout << "Unable to open file "<< audiofeatures << ". Please check the file path and try again. Aborting.. " << '\n';
        exit(1);
    }
    float* input[250];
}