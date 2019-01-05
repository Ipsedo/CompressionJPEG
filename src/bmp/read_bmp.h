//
// Created by samuel on 24/12/18.
//

#ifndef COMPRESSIONJPEG_READ_BMP_H
#define COMPRESSIONJPEG_READ_BMP_H

#include "../img/repr.h"
#include <string>

/**
 * Lit une image au format bmp et renvoie
 * une structure du type imgRGB (definie dans src/img/repr.h)
 * @param fileName le nom du fichier bmp
 * @return une structure imgRGB représentant l'image fileName
 */
imgRGB readBMP(std::string fileName);

#endif //COMPRESSIONJPEG_READ_BMP_H
