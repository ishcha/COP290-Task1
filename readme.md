# Contents

- [Contents](#contents)
- [Introduction](#introduction)
- [Description of main functionality](#description-of-main-functionality)
  - [Forward pass of a pre-trained deep neural network](#forward-pass-of-a-pre-trained-deep-neural-network)
- [Helper functions which assist the main forward pass functionality](#helper-functions-which-assist-the-main-forward-pass-functionality)
  - [Fully connected forward computation using MKL library](#fully-connected-forward-computation-using-mkl-library)
  - [ReLU activation function](#relu-activation-function)
  - [Softmax probability operation](#softmax-probability-operation)

# Introduction

Welcome to **Audio Processing Library Version 1.3**.

V1.3 supports the following functionality:

- End-to-end deep neural network forward pass implementation using fully connected layer computation, ReLU activation, and softmax function to compute the final probability of the given sample belonging to a given class.

What's new in V1.3?

- Forward pass of a pre-trained deep neural network.
- Minor changes in helper functions' signatures. The new signatures are described in [Helper functions which assist the main forward pass functionality](#helper-functions-which-assist-the-main-forward-pass-functionality)

# Description of main functionality

## Forward pass of a pre-trained deep neural network

- Implementation using a shared library containing the audio recognition API
- **Environment setup**: Before using this audio processing library through its main.cpp file, make sure to set the following environment variable as given.
  - ```LD_LIBRARY_PATH=$cwd:$LD_LIBRARY_PATH``` where cwd is the current working directory
  - ```MKL_BLAS_PATH=${path-of-MKL-installation}``` E.g. The path of our MKL installation- ```MKL_BLAS_PATH = /opt/intel/compilers_and_libraries_2018.2.199/linux/mkl```
- **How to invoke?**: ./yourcode.out audiosamplefile outputfile. Here, yourcode.out is the executable created to run the shared library, audiosamplefile is the path of the file which contains the extracted audio features (1x250 dimensional vectors). outputfile is the path of the file into which the output of the forward pass computation is written. The output provided informs about the three highest probability labels for the given audio sample features. Each sample's output is organized in the format: <input-file-path> <highest-probability-label> <second-highest-probability-label> <third-highest-probability-label> <highest-probability> <second-highest-probability> <third-highest-probability>

# Helper functions which assist the main forward pass functionality

## Fully connected forward computation using MKL library
- **Reason for using MKL**: MKL gave us the best run times in subtask 2 in comparison to OpenBlas and our pthreads implementation.
- **Functionality implemented**: output_matrix = input_matrix*weight_matrix + bias_matrix
- **Name of the function**: fc_mkl; defined in fc_mkl.cpp
- **Inputs**: (float*im, int m, int k, float* wm, int n, float*bm, float* res) pointer to input matrix im (mxk dimensions) with 32-bit floats, pointer to weight matrix, wm (kxn dimensions) with 32-bit floats, pointer to bias matrix, bm (mxn dimensions) with 32-bit floats, pointer to output matrix, res (mxn dimensions) with 32-bit floats

## ReLU activation function

- **Name of function**: myrelu; defined in activation.cpp
- **Inputs**: (float* im, int isize) pointer to input vector _im_ with 32-bit floats, number of elements in input vector _isize_
- **Functionality implemented**: output_matrix = element_wise_max(0, input_matrix)

## Softmax probability operation

- **Name of function**: mysoftmax; defined in probability.cpp
- **Inputs**: (float* ivector, int isize) pointer to input vector _im_ with 32-bit floats, number of elements in input vector _isize_
- **Functionality implemented**: output_vector = softmax(input_vector), where softmax(x) = $\left[\frac{e^{x_i}}{\sum_{j\in \{1,..,|x|\}} e^{x_j}}\right]$
