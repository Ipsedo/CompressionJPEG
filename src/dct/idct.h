//
// Created by samuel on 26/12/18.
//

#ifndef COMPRESSIONJPEG_IDCT_H
#define COMPRESSIONJPEG_IDCT_H

#include <vector>

double idct(std::vector<std::vector<double>> blockDCT, int x, int y, int N);

#endif //COMPRESSIONJPEG_IDCT_H
