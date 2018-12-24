//
// Created by samuel on 24/12/18.
//

#ifndef COMPRESSIONJPEG_READ_BMP_H
#define COMPRESSIONJPEG_READ_BMP_H

#include "../img/repr.h"
#include <string>
#include <fstream>

imgRGB readBMP(std::string fileName) {
    //TODO https://stackoverflow.com/questions/9296059/read-pixel-value-in-bmp-file
    std::ifstream file(fileName.c_str());

    long length = file.tellg();

    int headerSize = 54;
    char header[54];

    file.seekg(0, std::ios::beg);
    file.read(header, headerSize);

    // On récupère l'adresse du 18e octets de l'entête
    // On le convertit le pointeur de char en pointeur de int
    // On récupère le int contenu à l'adresse précédente
    int width = abs(*(int *) &header[18]);
    // Même chose pour la hauteur
    int height = abs(*(int *) & header[22]);

    int width_padded = width * 3;
    width_padded += (4 - width_padded % 4) % 4;

    std::vector<std::vector<color>> pixels;

    for (int i = 0; i < height; i++) {
        std::vector<color> row;

        auto *tmp = new char[width_padded];
        file.read(tmp, width_padded);

        for (int j = 0; j < width * 3; j += 3) {
            color c((unsigned char) tmp[j + 2], (unsigned char) tmp[j + 1], (unsigned char) tmp[j]);
            row.push_back(c);
        }

        pixels.push_back(row);
        delete[] tmp;
    }

    return {width, height, pixels};
}

#endif //COMPRESSIONJPEG_READ_BMP_H
