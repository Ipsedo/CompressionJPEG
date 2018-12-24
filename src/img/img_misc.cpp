//
// Created by samuel on 24/12/18.
//

#include "img_misc.h"

void printImg(imgRGB img, int widthLimit, int heightLimit) {
    if (widthLimit > img.width) {
        std::cout << "Width limit cannot be greater than image width ! (" << widthLimit << " > " << img.width << ")" << std::endl;
    }
    if (heightLimit > img.height) {
        std::cout << "Height limit cannot be greater than image width ! (" << heightLimit << " > " << img.height << ")" << std::endl;
    }


    for (int i = 0; i < heightLimit; i++) {
        std::string line = "";
        for (int j = 0; j < widthLimit; j++) {
            color pixel = img.pixels[i][j];
            int r = std::get<0>(pixel);
            int g = std::get<1>(pixel);
            int b = std::get<2>(pixel);
            int mean = g;//(r + g + b) / 3;
            line += mean > 122 ? "# " : ". ";
        }
        std::cout << line << std::endl;
    }
}