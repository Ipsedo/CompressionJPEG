//
// Created by samuel on 03/01/19.
//

#ifndef COMPRESSIONJPEG_HUFFMAN_TABLES_H
#define COMPRESSIONJPEG_HUFFMAN_TABLES_H

#include <unordered_map>
#include <string>
#include "../jpeg/markers.h"

typedef std::unordered_map<unsigned char, std::string> huff_tbl;

// https://www.impulseadventure.com/photo/jpeg-huffman-coding.html
// Table 1
#define DC1_LENGTH huff_tbl ({ \
{0x04, "000"}, \
{0x05, "001"}, \
{0x03, "010"}, \
{0x02, "011"}, \
{0x06, "100"}, \
{0x01, "101"}, \
{EOB, "110"},  \
{0x07, "1110"}, \
{0x08, "11110"}, \
{0x09, "111110"}, \
{0x0A, "1111110"}, \
{0x0B, "11111110"} \
})

#endif //COMPRESSIONJPEG_HUFFMAN_TABLES_H
