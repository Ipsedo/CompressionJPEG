//
// Created by samuel on 05/01/19.
//

#include "rle.h"
#include "../jpeg/markers.h"
#include <math.h>
#include <iostream>

std::vector<unsigned char> rle(std::vector<int> quantized_block) {
	std::vector<unsigned char> res;

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
			i = quantized_block.size();
			res.push_back(EOB);
		} else {
			int zero_restant = nb_zero;
			if (zero_restant >= 16) {
				res.push_back(ZRL);
				zero_restant -= 16;
				i += 16;
			}
			if (zero_restant > 16) {
				std::cout << "pb all zero > 16" << std::endl;
				exit(1);
			}
			if (zero_restant > 0) {
				// TODO 5 zeros suivi d'un 2 -> 0x52
				// TODO Marche pas
				auto z = (unsigned char) zero_restant;
				unsigned char to_write = 0 | z >> 4;
				i += zero_restant;
				to_write |= (unsigned char) quantized_block[i];
				res.push_back(to_write);
			} else {
				res.push_back((unsigned char) quantized_block[i]);
			}
		}
	}

	return res;
}
