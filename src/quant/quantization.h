//
// Created by samuel on 28/12/18.
//

#ifndef COMPRESSIONJPEG_QUANTIZATION_H
#define COMPRESSIONJPEG_QUANTIZATION_H

#include <vector>

/**
 * Quantifie une matrice selon une matrice de quantification
 * @param F La matrice de fréquences à quantifier
 * @param Q La matrice de quantification
 * @return La matrice de fréquences quantifiée
 */
std::vector<std::vector<double>> quantize(std::vector<std::vector<double>> F, std::vector<std::vector<double>> Q);

#endif //COMPRESSIONJPEG_QUANTIZATION_H
