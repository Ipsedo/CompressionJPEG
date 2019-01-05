//
// Created by samuel on 05/01/19.
//

#include "rle.h"
#include "../jpeg/markers.h"
#include <math.h>
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
			i = quantized_block.size();
			res.push_back(pair_rle(EOB, 0));
		} else {
			int zero_restant = nb_zero;
			if (zero_restant >= 16) {
				res.push_back(pair_rle(ZRL,0));
				zero_restant -= 16;
				i += 16;
			}

			if (zero_restant > 16) {
				std::cout << "pb all zero > 16" << std::endl;
				exit(1);
			}

			unsigned char to_write = zero_restant << 4;
			i += zero_restant;
			to_write |= (unsigned char) ceil(log(abs(quantized_block[i]) + 1) / log(2.0));
			res.push_back(pair_rle(to_write, quantized_block[i]));
		}
	}


	return res;
}
