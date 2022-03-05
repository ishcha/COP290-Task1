#include "audioAPI.h"
#include <iostream>
#include <fstream>
#include <iomanip>

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
    pred_t* myoutput = new pred_t();
    myoutput = libaudioAPI(argv[1], myoutput);
    ofstream fout;
    fout.open(argv[2]);
    if (!fout) {
        cout << "Unable to open file "<< argv[2] << ". Please check the file path and try again. Aborting.. " << '\n';
        exit(1); 
    }
    if (!(fout << argv[1])) {
        cout << "Error sending output to output file. Please check the file path and try again. Aborting.. \n";
        exit(1);
    }
    if (!(fout << " ")) { // remember it is int; don't forget to convert to string of label name
        cout << "Error sending output to output file. Please check the file path and try again. Aborting.. \n";
        exit(1);
    }
    const char* labels[12];
    labels[0] = "silence";
    labels[1] = "unknown";
    labels[2] = "yes";
    
    for (int i = 0; i < 3; i++) {
        int label = (myoutput+i)->label;
        float prob = (myoutput+i)->prob;
        if (!(fout << label)) { // remember it is int; don't forget to convert to string of label name
            cout << "Error sending output to output file. Please check the file path and try again. Aborting.. \n";
            exit(1);
        }
        if (!(fout << " ")) { // remember it is int; don't forget to convert to string of label name
            cout << "Error sending output to output file. Please check the file path and try again. Aborting.. \n";
            exit(1);
        }
        if (!(fout << setprecision(5) << prob)) {
            cout << "Error sending output to output file. Please check the file path and try again. Aborting.. \n";
            exit(1);
        }
        if (!(fout << " ")) { // remember it is int; don't forget to convert to string of label name
            cout << "Error sending output to output file. Please check the file path and try again. Aborting.. \n";
            exit(1);
        }
    }
    cout << "Execution completed. Output is at " << argv[2] << '\n';
    fout.close();
    return 0;
}
