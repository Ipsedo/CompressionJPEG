//
// Created by samuel on 28/12/18.
//

#ifndef COMPRESSIONJPEG_ZIG_ZAG_H
#define COMPRESSIONJPEG_ZIG_ZAG_H

#include <vector>

/**
 *
 * @param to_encode the square matrix to encode
 * @return the zig-zag encoded vector
 */
std::vector<double> zig_zag_encodage(std::vector<std::vector<double>> to_encode);

#endif //COMPRESSIONJPEG_ZIG_ZAG_H
