//
// Created by samuel on 26/12/18.
//

#ifndef COMPRESSIONJPEG_IDCT_H
#define COMPRESSIONJPEG_IDCT_H

#include <vector>

/**
 *	Applique une transformé cosinus discrète inverse sur le pixel x y
 *	à partir de la matrice blockDCT
 * @param blockDCT The N * N DCT block result
 * @param x the freq height to compute inverse DCT
 * @param y the freq width to compute inverse DCT
 * @param N the block size
 * @return the pixels value
 */
double idct(std::vector<std::vector<double>> blockDCT, int x, int y, int N);

/**
 * Applique une transformé cosinus discrète inverse sur tout un block
 * @param blockDCT Le block de fréquence issu d'une DCT à inverser
 * @return La matrice de DCT inverse
 */
std::vector<std::vector<double>> idct_block(std::vector<std::vector<double>> blockDCT);

#endif //COMPRESSIONJPEG_IDCT_H
