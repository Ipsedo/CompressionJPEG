//
// Created by samuel on 05/01/19.
//

#ifndef COMPRESSIONJPEG_WRITE_BMP_H
#define COMPRESSIONJPEG_WRITE_BMP_H

#include "../img/repr.h"
#include <string>

/**
 * Ecrit une image en nuance de gris vers une fichier
 * de sortie de nom output_file
 * @param img La structure représentant l'image en nuance de gris (définie dans src/img/repr.h)
 * @param output_file Le nom de l'image bmp qui contiendra l'image img
 */
void write_grey_scale(imgGreyScale img, std::string output_file);

#endif //COMPRESSIONJPEG_WRITE_BMP_H
