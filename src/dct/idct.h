//
// Created by samuel on 26/12/18.
//

#ifndef COMPRESSIONJPEG_IDCT_H
#define COMPRESSIONJPEG_IDCT_H

#include <vector>

/**
 *
 * @param blockDCT The N * N DCT block result
 * @param x the freq height to compute inverse DCT
 * @param y the freq width to compute inverse DCT
 * @param N the block size
 * @return the pixels value
 */
double idct(std::vector<std::vector<double>> blockDCT, int x, int y, int N);

std::vector<std::vector<double>> idct_block(std::vector<std::vector<double>> blockDCT);

#endif //COMPRESSIONJPEG_IDCT_H
