//
// Created by samuel on 28/12/18.
//

#ifndef COMPRESSIONJPEG_DE_QUANTIZATION_H
#define COMPRESSIONJPEG_DE_QUANTIZATION_H

#include <vector>

/**
 * De-quantifie la matrice de fréquence selon une matrice de quantification
 * @param F_prime La matrice de fréquence à de-quantifier
 * @param Q La matrice de quantification
 * @return La matrice  de fréquence de-quantifié
 */
std::vector<std::vector<double>>
de_quantize(std::vector<std::vector<double>> F_prime, std::vector<std::vector<double>> Q);

#endif //COMPRESSIONJPEG_DE_QUANTIZATION_H
