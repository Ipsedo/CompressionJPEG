//
// Created by samuel on 06/01/19.
//

#ifndef COMPRESSIONJPEG_COEFF_H
#define COMPRESSIONJPEG_COEFF_H

#include <string>
#include <cmath>
#include <bitset>

/**
 * Marche ?
 * @tparam Max_Magn La magintude maximum
 * @param magn La magintude effective du coefficient
 * @param to_code Le coefficient à coder
 * @return La chaine de caractère composée de 0 et 1 représentant la valeur binaire de to_code et de longueur magn
 */
template<int Max_Magn>
std::string write_bits(int magn, int to_code) {
	std::string res;

	unsigned long long num;

	if (to_code < pow(2, magn - 1))
		num = (unsigned long long) (to_code + pow(2, magn) - 1); // OK
	else {
		auto diff = -pow(2, magn - 1) + pow(2, magn);
		num = (unsigned long long) (to_code - pow(2, magn - 1) + diff);
	}
	std::bitset<Max_Magn> tmp(num);
	res = tmp.to_string().substr((unsigned long) (Max_Magn - magn), (unsigned long) Max_Magn);

	return res;
}

/**
 * Décode un entier converti avec la fonction write_bits
 * @param coded_coeff La représentation binaire sous forme de chaine de caractère
 * @param magn La magintude du coefficient
 * @return Le coefficient associé
 */
int decode_bits(std::string coded_coeff, int magn);

#endif //COMPRESSIONJPEG_COEFF_H
