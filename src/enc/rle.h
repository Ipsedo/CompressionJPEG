//
// Created by samuel on 05/01/19.
//

#ifndef COMPRESSIONJPEG_RLE_H
#define COMPRESSIONJPEG_RLE_H

#include <vector>
#include <cmath>
#include <bitset>
#include <tuple>
#include <iostream>

typedef std::tuple<unsigned char, int> pair_rle;

std::vector<pair_rle> rle(std::vector<int> quantized_block);

std::vector<int> de_rle(std::vector<pair_rle> rle_values);

typedef std::tuple<unsigned char, std::string> pair_dc_ac;

template<int Max_Magn>
std::string write_bits(int magn, int to_code) {
	std::string res;

	// TODO ligne suivante marche pas
	auto num = (unsigned long long) (to_code + pow(2, magn) - 1 - (to_code > 0 ? ((pow(2, magn-1) - 1) * 2) : 0));
	std::bitset<Max_Magn> tmp(num);
	std::cout << tmp.to_ulong() << std::endl;
	res = tmp.to_string().substr((unsigned long) (Max_Magn - magn), (unsigned long) Max_Magn);

	return res;
}

std::vector<pair_dc_ac> write_dc_acs(std::vector<pair_rle> rle);

#endif //COMPRESSIONJPEG_RLE_H
