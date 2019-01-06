//
// Created by samuel on 06/01/19.
//

#ifndef COMPRESSIONJPEG_PIPELINE_H
#define COMPRESSIONJPEG_PIPELINE_H

#include <string>
#include "../img/repr.h"
#include "../enc/huffman_tables.h"

/**
 * Une structure pour les information / outils
 * nécéssaires à la compression jpeg :
 * - Une matrice de quantification
 * - Une table de Huffman pour les DC
 * - Une table de Huffman pour les AC
 */
struct jpeg_tools {
	std::vector<std::vector<double>> quant_mat;
	huff_tbl DC_code;
	huff_tbl AC_code;
};

/**
 * Compresse une image
 * @param img L'image en nuance de gris à compresser
 * @param tools Les outils pour la compression
 * @return L'image compréssé sous format chain de caractère (représentant les bits de l'image)
 */
std::string make_compressed_blocks(imgGreyScale img, jpeg_tools tools);

/**
 * Décompresse une image
 * @param compressed_blocks Les blocks de l'image sous représentation binaire
 * @param width La largeur de l'image
 * @param height La hauteur de l'image
 * @param tools Les outils nécéssaires pour la décompression
 * @return L'image en nuance de gris
 */
imgGreyScale decompress_blocks(std::string compressed_blocks, int width, int height, jpeg_tools tools);

#endif //COMPRESSIONJPEG_PIPELINE_H
