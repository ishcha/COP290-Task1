#include "audioAPI.h"
#include <iostream>

using namespace std;
int main(int argc, char const *argv[]) {
    if (argc < 3) {
        cout << "Insufficient number of arguments. Need 3 arguments to proceed. Aborting... \n";
        exit(1);
    }
    if (argc > 3) {
        cout << "Too many arguments"
    }
    return 0;
}
