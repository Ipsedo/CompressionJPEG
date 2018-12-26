//
// Created by samuel on 26/12/18.
//

#ifndef COMPRESSIONJPEG_FDCT_H
#define COMPRESSIONJPEG_FDCT_H

// Forward Discrete Cosinus Transform

#include <vector>

/**
 *
 * @param pixelBlock the block of N * N pixels (normalized in range [0;1]
 * @param i the pixel height to compute dct
 * @param j the pixel width to compute dct
 * @param N the size of the pixel block
 * @return The DCT value of pixel {i, j}
 */
double fdct(std::vector<std::vector<double>> pixelBlock, int i, int j, int N);

#endif //COMPRESSIONJPEG_FDCT_H