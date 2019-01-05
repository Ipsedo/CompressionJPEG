//
// Created by samuel on 05/01/19.
//

#ifndef COMPRESSIONJPEG_RLE_H
#define COMPRESSIONJPEG_RLE_H

#include <vector>
#include <tuple>

typedef std::tuple<unsigned char, int> pair_rle;

std::vector<pair_rle> rle(std::vector<int> quantized_block);

#endif //COMPRESSIONJPEG_RLE_H
