#include <pthread.h>
#include <iomanip>
#include "fc_pthread.h"

using namespace std;

struct argss {
    int i;
    int minp;
    int nin;
    float **a;
    float **b;
    float **bias;
    float **outm;
};

void* multiply_vectors(void* arguments) {
    struct argss* args = (struct argss*) arguments;
    // cout << "In thread!!" << pthread_self() <<'\n';  
    // float* a = new float[args->minp];  
    // cout << "reached " << pthread_self() <<'\n';
    for(int j = 0; j < args->minp; j++) {
        args->outm[args->i][j] = 0.0;
        // cout << "For outm " << args->i <<' ' << j <<'\n';
        for(int k = 0; k < args->nin; k++) {
            // cout << pthread_self() << " " << j << " " << k <<'\n';
            
            float x = 0.0;
            x = (args->a[k][j] * args->b[args->i][k]);
            // cout << "For outm " << args->i <<' ' << j << ' ' << k << ' '<< args->a[k][j] << ' ' << args->b[args->i][k] << " earlier " << args->outm[args->i][j] <<'\n';
            args->outm[args->i][j] += x;
            // cout << "For outm " << args->i <<' ' << j << ' ' << k << ' '<< args->a[k][j] << ' ' << args->b[args->i][k] << " later " << args->outm[args->i][j] <<'\n';
        }
        // cout << "For outm " << args->i <<' ' << j << ' '<< " earlier " << args->outm[args->i][j] <<'\n';
        args->outm[args->i][j] += args->bias[args->i][j];
        // cout << "For outm " << args->i <<' ' << j << ' '<< " later " << args->outm[args->i][j] <<'\n';
    }
    // cout << "Bye-Bye " << pthread_self() <<'\n';
    pthread_exit(NULL);
    return NULL;
}

void fc_pthread(char* inputm, char* weightm, char* biasm, char* outputm) {
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
    float **inmatrix, **wmatrix, **bmatrix, **outmatrix;
    inmatrix = new float*[nin];
    for (int u = 0; u < nin; u++) {
        inmatrix[u] = new float[minp];
    }
    wmatrix = new float*[nw];
    for (int u = 0; u < nw; u++) {
        wmatrix[u] = new float[mw];
    }
    bmatrix = new float*[nb];
    for (int u = 0; u < nb; u++) {
        bmatrix[u] = new float[mb];
    }
    outmatrix = new float*[nb];
    for (int u = 0; u < nb; u++) {
        outmatrix[u] = new float[mb];
    }

    // taking input for input matrix
    for (int i = 0; i < nin; i++) {
        for (int j = 0; j < minp; j++) {
            // float x;
            if(!(fin >> inmatrix[i][j])) {
                cout << "Error! Input file does not have enough matrix entries\n";
                exit(1);
            }
        }
    }

    // taking input for weight matrix
    for (int i = 0; i < nw; i++) {
        for (int j = 0; j < mw; j++) {
            // float x;
            if(!(fw >> wmatrix[i][j])) {
                cout << "Error! Weight file does not have enough matrix entries\n";
                exit(1);
            }
        }
    }

    // taking input for bias matrix
    for (int i = 0; i < nb; i++) {
        for (int j = 0; j < mb; j++) {
            // float x;
            if(!(fb >> bmatrix[i][j])) {
                cout << "Error! Bias file does not have enough matrix entries\n";
                exit(1);
            }
        }
    }

    // for (int i = 0; i < nin; i++) {
    //     for (int j = 0; j < minp; j++) {
    //         cout << i << " " << j << " " << inmatrix[i][j] <<'\n';
    //     }
    // }

    // multiplying inmatrix and wmatrix, making vector of column vectors in outmatrix
    if (nin != mw) {
        cout << "Input matrix and weight matrix dimensions are not compatible. Aborting...\n";
        exit(1);
    }
    if ((nb != nw) || (mb != minp)) {
        std::cout << "Bias dimensions are not compatible. Aborting...\n";
        exit(1);
    }
    // cout << "Inputs done!" << '\n';

    struct argss arg[nw];

    pthread_t tarr[nw];
    for (int i = 0; i < nw; i++) {        
        arg[i].a = inmatrix;
        arg[i].b = wmatrix;
        arg[i].bias = bmatrix;
        arg[i].outm = outmatrix;
        arg[i].minp = minp;
        arg[i].i = i;
        arg[i].nin = nin;
        pthread_create(&tarr[i], NULL, &multiply_vectors, &arg[i]);
    }
    // cout << "pthreads created\n";

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
    
    for (int i = 0; i < nw; i++) {
        pthread_join(tarr[i], NULL);
        // cout << "thread joined " << i << '\n';
        // float* oans = (float*) ans;
        for (int j = 0; j < minp; j++) {
            // file << std::fixed << std::setprecision(5) << omatrix[i] << "\n";
            if (!(fout << std::fixed << std::setprecision(7) << outmatrix[i][j])) {
                std::cout << "Error sending output to output file\n";
                exit(1);
            }
            if (!(fout << '\n')) {
                std::cout << "Error sending output to output file\n";
                exit(1);
            }            
        }
    }

    // cout << "Fully connected layer implementation complete successfully. Output is at " << outputm <<'\n';    

    fout.close();
    fw.close();
    fb.close();
    fin.close();
}