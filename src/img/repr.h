//
// Created by samuel on 24/12/18.
//

#ifndef COMPRESSIONJPEG_REPR_H
#define COMPRESSIONJPEG_REPR_H

#include <vector>
#include <tuple>

/**
 * Définition du type color
 * comme un triplet d'entier
 */
typedef std::tuple<int, int, int> color;

/**
 * Structure pour une image en couleur RGB
 * contenant sa lergeur, sa hauteur et
 * sa matrice de pixels
 */
struct imgRGB {
	int width;
	int height;
	std::vector<std::vector<color>> pixels;
};

/**
 * Structure pour une image en nuance de gris
 * contenant sa lergeur, sa hauteur
 * et sa matrice de pixels
 */
struct imgGreyScale {
	int width;
	int height;
	std::vector<std::vector<int>> pixels;
};

#endif //COMPRESSIONJPEG_REPR_H
