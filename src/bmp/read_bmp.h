//
// Created by samuel on 24/12/18.
//

#ifndef COMPRESSIONJPEG_READ_BMP_H
#define COMPRESSIONJPEG_READ_BMP_H

#include "../img/repr.h"
#include <string>

imgRGB readBMP(std::string fileName) {
    //TODO https://stackoverflow.com/questions/9296059/read-pixel-value-in-bmp-file
    return {0, 0, std::vector<std::vector<char>>()};
}

#endif //COMPRESSIONJPEG_READ_BMP_H
