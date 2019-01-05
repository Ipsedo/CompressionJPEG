//
// Created by samuel on 28/12/18.
//

#ifndef COMPRESSIONJPEG_ZIG_ZAG_H
#define COMPRESSIONJPEG_ZIG_ZAG_H

#include <vector>

/**
 *	Applique le codage en zig zag comme spécifié dans le standart de JPEG
 * @param to_encode the square matrix to encode
 * @return the zig-zag encoded vector
 */
std::vector<int> zig_zag_encodage(std::vector<std::vector<int>> to_encode);

/**
 * Reconstruit un block à partir d'un vecteur encodé en zig-zag
 * @param to_decode La matrice encodé en zig-zag
 * @return La block décodé
 */
std::vector<std::vector<int>> zig_zag_decodage(std::vector<int> to_decode);

#endif //COMPRESSIONJPEG_ZIG_ZAG_H
