//
// Created by samuel on 24/12/18.
//

#ifndef COMPRESSIONJPEG_IMG_MISC_H
#define COMPRESSIONJPEG_IMG_MISC_H

#include "repr.h"
#include <iostream>
#include <string>

#define RESET   std::string("\033[0m")
#define RED     std::string("\033[31m")      /* Red */
#define GREEN   std::string("\033[32m")      /* Green */
#define BLUE    std::string("\033[34m")      /* Blue */

void printImg(imgRGB img, int widthLimit, int heightLimit);

imgGreyScale toGreyScale(imgRGB img);

#endif //COMPRESSIONJPEG_IMG_MISC_H
