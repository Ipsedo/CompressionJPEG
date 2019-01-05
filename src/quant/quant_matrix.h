//
// Created by samuel on 28/12/18.
//

#ifndef COMPRESSIONJPEG_QUANT_MATRIX_H
#define COMPRESSIONJPEG_QUANT_MATRIX_H

#include <vector>

// From wikipedia https://fr.wikipedia.org/wiki/JPEG#Quantification
/**
 * Une matrice de quantification suggérée
 */
#define Q1 std::vector<std::vector<double>> { {16,11,10,16,24,40,51,61}, \
                                              {12,12,14,19,26,58,60,55}, \
                                              {14,13,16,24,40,57,69,56}, \
                                              {14,17,22,29,51,87,80,62}, \
                                              {18,22,37,56,68,109,103,77}, \
                                              {24,35,55,64,81,104,113,92}, \
                                              {49,64,78,87,103,121,120,101}, \
                                              {72,92,95,98,112,100,103,99} }

#endif //COMPRESSIONJPEG_QUANT_MATRIX_H
