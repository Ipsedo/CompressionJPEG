//
// Created by samuel on 05/01/19.
//

#include "huffman.h"

std::string encode_huffman(std::vector<pair_dc_ac> to_encode, huff_tbl dc_table, huff_tbl ac_table) {
	auto dc = to_encode[0];
	auto magn = std::get<0>(dc);
	auto dc_bits_coeff_str = std::get<1>(dc);

	if (magn == EOB)
		return dc_table[magn];

	std::string res;
	res += dc_table[magn] + dc_bits_coeff_str;

	for (int i = 1; i < to_encode.size(); i++) {
		auto ac = to_encode[i];
		auto zero_n_magn = std::get<0>(ac);
		auto ac_bits_coeff_str = std::get<1>(ac);

		if (zero_n_magn == EOB)
			return res += ac_table[EOB];

		if (zero_n_magn == ZRL) {
			res += ac_table[ZRL];
			continue;
		}

		res += ac_table[zero_n_magn] + ac_bits_coeff_str;
	}

	return res;
}

std::vector<std::vector<pair_dc_ac>>
decode_huffman(std::string code, rev_huff_tbl rev_dc_tbl, rev_huff_tbl rev_ac_tbl) {
	std::vector<pair_dc_ac> tmp;
	int inf = 0;
	int i = 1;

	bool dc = true;

	while (inf < code.length()) {
		std::string sub = code.substr((unsigned long) inf, (unsigned long) i);

		if (dc && rev_dc_tbl.find(sub) != rev_dc_tbl.end()) {
			inf += i;
			i = 1;

			auto magn = rev_dc_tbl[sub];

			tmp.emplace_back(pair_dc_ac(magn, code.substr((unsigned long) inf, magn)));
			inf += magn;

			dc = false;
			if (magn == EOB)
				dc = true;
		} else if (!dc && rev_ac_tbl.find(sub) != rev_ac_tbl.end()) {
			inf += i;
			i = 1;

			auto zero_n_magn = rev_ac_tbl[sub];
			auto magn = zero_n_magn & 0x0F;

			if (zero_n_magn == EOB) {
				tmp.emplace_back(pair_dc_ac(EOB, ""));
				dc = true;
				continue;
			} else if (zero_n_magn == ZRL) {
				tmp.emplace_back(pair_dc_ac(ZRL, ""));
				continue;
			}

			tmp.emplace_back(pair_dc_ac(zero_n_magn, code.substr((unsigned long) inf, (unsigned long) magn)));
			inf += magn;
		}

		i++;
	}

	std::vector<std::vector<pair_dc_ac>> res;
	std::vector<pair_dc_ac> tmp2;

	for (int i = 0; i < tmp.size(); i++) {
		for (int j = i; j < tmp.size(); j++) {
			tmp2.emplace_back(tmp[j]);
			if (std::get<0>(tmp[j]) == EOB) {
				i = j;
				res.emplace_back(tmp2);
				tmp2.clear();
				break;
			}
		}
	}
	return res;
}
