//
// Created by samuel on 05/01/19.
//

#include "rle.h"
#include "../jpeg/markers.h"
#include <cmath>
#include <iostream>

std::vector<pair_rle> rle(std::vector<int> quantized_block) {
	std::vector<pair_rle> res;

	for (int i = 0; i < quantized_block.size(); i++) {
		bool all_zero = true;
		int nb_zero = 0;

		for (int j = i; j < quantized_block.size(); j++) {
			if (abs(quantized_block[j]) != 0) {
				all_zero = false;
				break;
			} else
				nb_zero++;
		}
		if (all_zero) {
			i = (int) quantized_block.size();
			res.emplace_back(pair_rle(EOB, 0));
		} else {
			int zero_restant = nb_zero;
			if (zero_restant >= 16) {
				res.emplace_back(pair_rle(ZRL,0));
				zero_restant -= 16;
				i += 16;
			}

			if (zero_restant > 16) {
				std::cout << "pb all zero > 16" << std::endl;
				exit(1);
			}

			auto to_write = (unsigned char) zero_restant << 4;
			i += zero_restant;
			to_write |= (unsigned char) ceil(log(abs(quantized_block[i]) + 1) / log(2.0));
			res.emplace_back(pair_rle(to_write, quantized_block[i]));
		}
	}


	return res;
}


std::vector<pair_dc_ac> write_dc_acs(std::vector<pair_rle> rle) {
	std::vector<pair_dc_ac> res;

	if (std::get<0>(rle[0]) == EOB)
		res.emplace_back(pair_dc_ac(EOB, ""));

	pair_rle dc = rle[0];
	unsigned char magn_dc = std::get<0>(dc);
	int coeff_dc = std::get<1>(dc);
	res.emplace_back(pair_dc_ac(magn_dc, write_bits<11>(10, 1020)));

	for (int i = 1; i < rle.size(); i++) {
		pair_rle ac = rle[i];
		auto zero_n_magn = std::get<0>(ac);
		int coeff = std::get<1>(ac);

		int magn = zero_n_magn & 0x0F;

		res.emplace_back(pair_dc_ac(zero_n_magn, write_bits<10>(magn, coeff)));
	}

	return res;
}

std::vector<int> de_rle(std::vector<pair_rle> rle_values) {
	std::vector<int> res;

	int added = 0;
	for (int i = 0; i < rle_values.size() - 1; i++, added++) {
		auto p = rle_values[i];
		auto zero_n_magn = std::get<0>(p);
		int coeff = std::get<1>(p);

		int nb_zero = zero_n_magn >> 4;
		for (int j = 0; j < nb_zero; j++, added++)
			res.emplace_back(0);
		res.emplace_back(coeff);
	}
	for (int i = added; i < 64; i++) {
		res.emplace_back(0);
	}

	return res;
}
