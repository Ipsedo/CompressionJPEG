//
// Created by samuel on 05/01/19.
//

#include "rle.h"
#include "../jpeg/markers.h"
#include <cmath>
#include <iostream>

std::vector<pair_rle> rle(std::vector<int> quantized_zig_zag_block) {
	std::vector<pair_rle> res;

	// Parcourt de tout les coefficient
	for (int i = 0; i < quantized_zig_zag_block.size(); i++) {
		bool all_zero = true;
		int nb_zero = 0;

		// On compte le nombre de zeros et on verifie
		// si le block ne se termine pas que par des zeros
		for (int j = i; j < quantized_zig_zag_block.size(); j++) {
			if (abs(quantized_zig_zag_block[j]) != 0) {
				all_zero = false;
				break;
			} else
				nb_zero++;
		}

		if (all_zero) {
			// Si que des zeros :
			// on place EOB et on sort de la boucle principale
			res.emplace_back(pair_rle(EOB, 0));
			break;
		} else {
			// Sinon :
			int zero_restant = nb_zero;
			// On ajoute ZRL si il ya plus de 15 zeros
			// (on incremente i dans le même temps
			// et on décrémente le nombre de 0 restant)
			if (zero_restant >= 16) {
				res.emplace_back(pair_rle(ZRL,0));
				zero_restant -= 16;
				i += 16;
			}

			// TODO prévoir le cas de + de 32 zeros d'affilé
			if (zero_restant > 16) {
				std::cout << "pb all zero > 16" << std::endl;
				exit(1);
			}

			// On indique le nombre de 0 sur les 4 premier bit de l'octet to_write
			auto to_write = (unsigned char) zero_restant << 4;
			// On incrémente i en fonction du nombre de zeros restant
			i += zero_restant;
			// On calcule la magnitude du prochain coefficient et on l'ajoute au 4 derniers
			// bits de l'octet to_write
			to_write |= (unsigned char) ceil(log(abs(quantized_zig_zag_block[i]) + 1) / log(2.0));
			// On enregistre l'octet et la valeur du coefficient suivant
			res.emplace_back(pair_rle(to_write, quantized_zig_zag_block[i]));
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
	res.emplace_back(pair_dc_ac(magn_dc, write_bits<11>(magn_dc, coeff_dc)));

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
	// Parcourt des pair_rle
	// On s'arrête avant le dernier (EOB)
	for (int i = 0; i < rle_values.size() - 1; i++, added++) {
		// On récupère la paire courrante
		auto p = rle_values[i];
		// Le nombre de 0 et la magnitude sur le même octet
		auto zero_n_magn = std::get<0>(p);
		// La valeur du coefficient suivant
		int coeff = std::get<1>(p);

		// On récupère le nombre de 0 (4 premiers bits)
		int nb_zero = zero_n_magn >> 4;
		// On ajoute autant de 0 que nécéssaire
		for (int j = 0; j < nb_zero; j++, added++)
			res.emplace_back(0);
		// On ajoute enfin le coefficient
		res.emplace_back(coeff);
	}

	// Dans le cas où on a lu EOB
	// On ajoute les 0 nécéssaires
	for (int i = added; i < 64; i++) {
		res.emplace_back(0);
	}

	return res;
}
