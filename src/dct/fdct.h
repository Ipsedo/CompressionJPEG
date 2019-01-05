//
// Created by samuel on 26/12/18.
//

#ifndef COMPRESSIONJPEG_FDCT_H
#define COMPRESSIONJPEG_FDCT_H

// Forward Discrete Cosinus Transform

#include <vector>

/**
 * Applique une transformée cosinus dicrète (DCT) au pixel i j
 * sur la matrice 2D pixelBlock
 * @param pixelBlock the block of N * N pixels
 * @param i the pixel height to compute dct
 * @param j the pixel width to compute dct
 * @param N the size of the pixel block
 * @return The DCT value of pixel {i, j}
 */
double fdct(std::vector<std::vector<double>> pixelBlock, int i, int j, int N);

/**
 * Applique une transformée cosinus discrète sur tout les pixels d'un block
 * @param pixelBlock Le block où applique la DCT
 * @return La matrice de fréquences de la DCT
 */
std::vector<std::vector<double>> fdct_block(std::vector<std::vector<double>> pixelBlock);

#endif //COMPRESSIONJPEG_FDCT_H
