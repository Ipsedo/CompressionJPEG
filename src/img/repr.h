//
// Created by samuel on 24/12/18.
//

#ifndef COMPRESSIONJPEG_REPR_H
#define COMPRESSIONJPEG_REPR_H

#include <vector>
struct imgRGB {
    int width;
    int height;
    std::vector<std::vector<char>> pixels;
};

#endif //COMPRESSIONJPEG_REPR_H
