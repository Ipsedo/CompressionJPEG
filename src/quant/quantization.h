//
// Created by samuel on 28/12/18.
//

#ifndef COMPRESSIONJPEG_QUANTIZATION_H
#define COMPRESSIONJPEG_QUANTIZATION_H

#include <vector>

/**
 *
 * @param F the forward DCT output
 * @param Q the quantization matrix
 * @return the quantized FDCT
 */
std::vector<std::vector<double>> quantize(std::vector<std::vector<double>> F, std::vector<std::vector<double>> Q);

#endif //COMPRESSIONJPEG_QUANTIZATION_H
