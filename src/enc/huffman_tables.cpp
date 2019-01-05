//
// Created by samuel on 05/01/19.
//

#include "huffman_tables.h"

rev_huff_tbl reverse_huffman_table(huff_tbl tbl) {
	rev_huff_tbl res;
	for (auto p : tbl)
		res[std::get<1>(p)] = std::get<0>(p);
	return res;
}
