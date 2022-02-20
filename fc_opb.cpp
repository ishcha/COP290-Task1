// #include "../headerfiles/fc_opb.h"
#include "fc_opb.h"
#include <iomanip>

using namespace std;


void fc_blas( char* inputm, char* weightm, char* biasm, char* outputm) {
    ifstream fin, fw, fb;
    fin.open(inputm);
    ofstream fout;
    fout.open(outputm);
    fw.open(weightm);
    fb.open(biasm);
    if (!fin) {
        cout << "Unable to open file " << inputm << '\n';
        exit(1); 
    }
    if (!fout) {
        cout << "Unable to open file " << outputm << '\n';
        exit(1); 
    }
    if (!fw) {
        cout << "Unable to open file " << weightm << '\n';
        exit(1); 
    }
    if (!fb) {
        cout << "Unable to open file " << biasm << '\n';
        exit(1); 
    }

    // read inputs from files
    int nin, minp, nw, mw, nb, mb; // dimensions of input, weight, bias matrices
    if (!(fin >> nin)) {
        cout << "Error! Input file does not have input matrix column dimensions\n";
        exit(1);
    }
    if (!(fin >> minp)) {
        cout << "Error! Input file does not have input matrix row dimensions\n";
        exit(1);
    }
    if (!(fw >> nw)) {
        cout << "Error! Weight file does not have input matrix column dimensions\n";
        exit(1);
    }
    if (!(fw >> mw)) {
        cout << "Error! Weight file does not have input matrix row dimensions\n";
        exit(1);
    }
    if (!(fb >> nb)) {
        cout << "Error! Bias file does not have input matrix column dimensions\n";
        exit(1);
    }
    if (!(fb >> mb)) {
        cout << "Error! Bias file does not have input matrix row dimensions\n";
        exit(1);
    }

    double inmatrix[minp*nin], wmatrix[mw*nw], bmatrix[mb*nb], outmatrix[mb*nb];


    // taking input for input matrix
    for (int i = 0; i < nin; i++) {
        for (int j = 0; j < minp; j++) {
            if(!(fin >> inmatrix[j*nin+i])) {
                cout << "Error! Input file does not have enough matrix entries\n";
                exit(1);
            }
        }
    }

    // taking input for weight matrix
    for (int i = 0; i < nw; i++) {
        for (int j = 0; j < mw; j++) {
            if(!(fw >> wmatrix[j*nw+i])) {
                cout << "Error! Weight file does not have enough matrix entries\n";
                exit(1);
            }
        }
    }

    // taking input for bias matrix
    for (int i = 0; i < nb; i++) {
        for (int j = 0; j < mb; j++) {
            if(!(fb >> bmatrix[j*nb+i])) {
                cout << "Error! Bias file does not have enough matrix entries\n";
                exit(1);
            }
        }
    }

    // multiplying inmatrix and wmatrix, making vector of column vectors in outmatrix
    if (nin != mw) {
        cout << "Input matrix and weight matrix dimensions are not compatible. Aborting...\n";
        exit(1);
    }
    

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans , minp, nw , nin , 1.0 , inmatrix , nin , wmatrix , nw , 0.0 , outmatrix , nb);

    // adding bias matrix to outmatrix
    if ((nb != nw) || (mb != minp)) {
        cout << "Bias dimensions are not compatible. Aborting...\n";
        exit(1);
    }

    if (!(fout << nw)) {
        cout << "Error sending output to output file\n";
        exit(1);
    }

    if (!(fout << '\n')) {
        cout << "Error sending output to output file\n";
        exit(1);
    }

    if (!(fout << minp)) {
        cout << "Error sending output to output file\n";
        exit(1);
    }

    if (!(fout << '\n')) {
        cout << "Error sending output to output file\n";
        exit(1);
    }
    
    for (int j = 0; j < nw; j++) {
        for (int i = 0; i < minp; i++) {
            if (!(fout << std::fixed << std::setprecision(7) << (outmatrix[i*nw+j] + bmatrix[i*nw+j]))) {
                cout << "Error sending output to output file\n";
                exit(1);
            }
            if (!(fout << '\n')) {
                cout << "Error sending output to output file\n";
                exit(1);
            }
        }
    }

    // cout << "Fully connected lay    er implementation complete successfully. Output is at " << outputm <<'\n';    

    fout.close();
    fw.close();
    fb.close();
    fin.close();
}