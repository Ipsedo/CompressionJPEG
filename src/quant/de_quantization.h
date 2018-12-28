//
// Created by samuel on 28/12/18.
//

#ifndef COMPRESSIONJPEG_DE_QUANTIZATION_H
#define COMPRESSIONJPEG_DE_QUANTIZATION_H

#include <vector>

std::vector<std::vector<double>>
de_quantize(std::vector<std::vector<double>> F_prime, std::vector<std::vector<double>> Q);

#endif //COMPRESSIONJPEG_DE_QUANTIZATION_H
