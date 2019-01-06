//
// Created by samuel on 06/01/19.
//

#include "coeff.h"
#include <iostream>

int decode_bits(std::string coded_coeff, int magn) {
	int i = (int) strtol(coded_coeff.c_str(), NULL, 2);

	int limit = int(-pow(2.0, magn-1) + (pow(2.0, magn) - 1));
	int coeff;

	if (i > limit) {
		coeff = int(i - pow(2.0, magn) - 1 + (pow(2, magn - 1) * 2 + 1));
	} else {
		coeff = int(i - pow(2.0, magn) + 1);
	}
	return coeff;
}
