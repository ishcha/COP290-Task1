#include "audioAPI.h"
#include <iostream>
#include <fstream>
#include <iomanip>

int main(int argc, const char *argv[]) {
    if (argc < 3) {
        std::cout << "Insufficient number of arguments. Please check the command syntax. Aborting... \n";
        exit(1);
    }
    if (argc > 3) {
        std::cout << "Too many arguments. Please check the command syntax. Aborting... \n";
        exit(1);
    }
    pred_t* myoutput = new pred_t[3];
    if (myoutput == NULL) {
        std::cout << "\n ERROR: Can't allocate memory for matrix. Exiting...\n";
        exit(1);
    }

    myoutput = libaudioAPI(argv[1], myoutput);
    std::ofstream fout;
    fout.open(argv[2]);
    if (!fout) {
        std::cout << "Unable to open file "<< argv[2] << ". Please check the file path and try again. Aborting.. " << '\n';
        exit(1); 
    }
    if (!(fout << argv[1])) {
        std::cout << "Error sending output to output file. Please check the file path and try again. Aborting.. \n";
        exit(1);
    }
    if (!(fout << " ")) { // remember it is int; don't forget to convert to string of label name
        std::cout << "Error sending output to output file. Please check the file path and try again. Aborting.. \n";
        exit(1);
    }
    const char* labels[12];
    labels[0] = "silence";
    labels[1] = "unknown";
    labels[2] = "yes";
    labels[3] = "no";
    labels[4] = "up";
    labels[5] = "down";
    labels[6] = "left";
    labels[7] = "right";
    labels[8] = "on";
    labels[9] = "off";
    labels[10] = "stop";
    labels[11] = "go";

    for (int i = 0; i < 3; i++) {
        int label = myoutput[i].label;
        if (!(fout << labels[label])) { // remember it is int; don't forget to convert to string of label name
            std::cout << "Error sending output to output file. Please check the file path and try again. Aborting.. \n";
            exit(1);
        }
        if (!(fout << " ")) { // remember it is int; don't forget to convert to string of label name
            std::cout << "Error sending output to output file. Please check the file path and try again. Aborting.. \n";
            exit(1);
        }
    }
    for (int i = 0; i < 3; i++) {
        float prob = myoutput[i].prob;
        if (!(fout << std::setprecision(6) << prob)) {
            std::cout << "Error sending output to output file. Please check the file path and try again. Aborting.. \n";
            exit(1);
        }
        if (!(fout << " ")) { // remember it is int; don't forget to convert to string of label name
            std::cout << "Error sending output to output file. Please check the file path and try again. Aborting.. \n";
            exit(1);
        }
    }
    std::cout << "Execution completed. Output is at " << argv[2] << '\n';
    fout.close();
    delete[] myoutput;
    return 0;
}
