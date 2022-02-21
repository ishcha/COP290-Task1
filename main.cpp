#include<cstdio>
#include<cstring>
#include<iostream>
// #include<chrono>
// #include<cmath>

#include"main.h"

int main(int argc, char** argv){

    // int num = 11;
    // while(num) {
        // auto begin = std::chrono::high_resolution_clock::now();
        if (argc == 1)
            printf("No subtask given. Choose one from fullyconnected, activation, pooling or probability.\n");
        else {
            char* subtask = argv[1];
            printf("Subtask chosen is %s\n", subtask);
            if (!strcmp(subtask, "fullyconnected")) {
                if (argc == 7) {
                    // argv[2] -> mkl/openblas/pthreads/normal
                    printf("Performing matrix multiplication using %s\n", argv[2]);
                    if (!strcmp(argv[2], "mkl")) {
                        fc_mkl(argv[3],argv[4],argv[5],argv[6]);
                    } 
                    else if (!strcmp(argv[2], "blas")) {

                        fc_blas(argv[3],argv[4],argv[5],argv[6]);
                    }
                    else if (!strcmp(argv[2], "pthread")) {
                        fc_pthread(argv[3],argv[4],argv[5],argv[6]);
                    }
                    else{
                        printf("Undefined matrix multiplication parameter. Choose one from mkl, blas, pthread\n");
                    }
                }
                else if (argc == 6) {
                    // normal fullyconnected
                    printf("Performing conventional matrix multiplication \n");
                    fc_mkl(argv[2],argv[3],argv[4],argv[5]);
                }
                else {
                    // raise error
                    printf("Invalid number of input arguments.\n");
                    printf("Give name of file containing input matrix, weight matrix, bias matrix, and name of output file to be written to as input.\n");
                }
            }
            else if(!strcmp(subtask, "activation")) {
                if (argc == 5) {
                    act(argv[2],argv[3],argv[4]);
                }
                else {
                    // raise error
                    printf("Invalid number of input arguments.\n");
                    printf("Give name of activation function (tanh or relu), name of file containing input matrix, and name of output file to be written to as input.\n");
                }
            }
            else if(!strcmp(subtask, "probability")) {
                if (argc == 5) {
                    prob(argv[2],argv[3],argv[4]);
                }
                else {
                    // raise error
                    printf("Invalid number of input arguments.\n");
                    printf("Give probability function (sigmoid or softmax), name of file containing input vector, and name of output file to be written to as input.\n");
                }
            }
            else if(!strcmp(subtask, "pooling")) {
                if (argc == 6) {
                    pool(argv[2],argv[3],argv[4], argv[5]);
                }
                else {
                    // raise error
                    printf("Invalid number of input arguments.\n");
                    printf("Give type of pooling (max or average), name of file containing input matrix, value of stride (integer), and name of output file to be written to as input.\n");
                }
            }
            else {
                // raise error
                printf("Invalid subtask chosen. Choose one of fullyconnected, activation, pooling or probability.\n");
            }
        }
        // auto end = std::chrono::high_resolution_clock::now();
        // auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        // double duration = (1e-6 * (std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)).count());
        // num--;
        // std::cout<<duration <<"\n";
    // }
    // avg = avg/10.0;
    // std::cout<<"Mean time taken is: "<< avg <<"\n";
    // double std = 0.0;
    // for(int i=0; i<10; i++) {
    //     std += (arr[i]-avg)*(arr[i]-avg);
    // }
    // std::cout<<"Standard deviation is "<< sqrt(std/10.0) << "\n";
    // file << std::fixed << std::setprecision(5) << avg << "\t" << std::fixed << std::setprecision(5)<< sqrt(std/10.0) << "\n";
    // file.close();
    return 0;
}
