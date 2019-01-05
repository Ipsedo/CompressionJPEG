//
// Created by samuel on 05/01/19.
//

#ifndef COMPRESSIONJPEG_HUFFMAN_H
#define COMPRESSIONJPEG_HUFFMAN_H

#include <string>
#include <vector>
#include "rle.h"
#include "huffman_tables.h"

std::string encode_huffman(std::vector<pair_dc_ac> to_encode, huff_tbl dc_table, huff_tbl ac_table);

std::vector<std::vector<pair_dc_ac>> decode_huffman(std::string code, rev_huff_tbl rev_dc_tbl, rev_huff_tbl rev_ac_tbl);

#endif //COMPRESSIONJPEG_HUFFMAN_H
