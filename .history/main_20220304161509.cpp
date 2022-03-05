#include "audioAPI.h"
#include <iostream>

using namespace std;
int main(int argc, char const *argv[]) {
    if (argc < 3) {
        cout << "Insufficient number of arguments. Please check the command syntax. Aborting... \n";
        exit(1);
    }
    if (argc > 3) {
        cout << "Too many arguments. Please check the command syntax. Aborting... \n";
        exit(1);
    }
    pred_t* myoutput = new pred_t
    libaudioAPI(argv[1], pred_t* pred);
    return 0;
}
