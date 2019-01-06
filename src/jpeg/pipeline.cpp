//
// Created by samuel on 06/01/19.
//

#include "pipeline.h"
#include "../bmp/write_bmp.h"
#include "../img/img_misc.h"
#include "../dct/fdct.h"
#include "../quant/quantization.h"
#include "../enc/zig_zag.h"
#include "../enc/rle.h"
#include "../enc/huffman.h"
#include "../quant/de_quantization.h"
#include "../dct/idct.h"

std::string make_compressed_blocks(imgGreyScale imgGS, jpeg_tools tools) {
	// Découpage de l'image en blocks
	auto blocks = splitImg(imgGS);

	std::vector<std::vector<std::vector<double>>> dct;

	// Conversion int vers double
	for (int bl = 0; bl < blocks.size(); bl++) {
		std::vector<std::vector<double>> tmp;
		for (int j = 0; j < blocks[bl].size(); j++)
			tmp.emplace_back(std::vector<double>(blocks[bl][j].begin(), blocks[bl][j].end()));
		dct.emplace_back(tmp);
	}

	// On applique la DCT
	for (int bl = 0; bl < dct.size(); bl++)
		dct[bl] = fdct_block(dct[bl]);

	std::vector<std::vector<std::vector<double>>> quant;

	// Puis la quantifiction
	for (int bl = 0; bl < dct.size(); bl++)
		quant.emplace_back(quantize(dct[bl], tools.quant_mat));

	// Il faut convertir : double vers int
	std::vector<std::vector<std::vector<int>>> quant_converted;
	for (int bl = 0; bl < quant.size(); bl++) {
		std::vector<std::vector<int>> tmp;
		for (int i = 0; i < quant[bl].size(); i++)
			tmp.emplace_back(std::vector<int>(quant[bl][i].begin(), quant[bl][i].end()));
		quant_converted.emplace_back(tmp);
	}

	// On applique ensuite l'encodage zig-zag
	std::vector<std::vector<int>> zig_zag;
	for (int bl = 0; bl < quant_converted.size(); bl++) {
		zig_zag.emplace_back(zig_zag_encodage(quant_converted[bl]));
	}

	// Puis la compression RLE
	std::vector<std::vector<pair_rle>> rle_blocks;
	for (int bl = 0; bl < zig_zag.size(); bl++)
		rle_blocks.emplace_back(rle(zig_zag[bl]));


	std::vector<std::vector<pair_dc_ac>> dc_ac_blocks;
	for (int bl = 0; bl < rle_blocks.size(); bl++)
		dc_ac_blocks.push_back(write_dc_acs(rle_blocks[bl]));


	std::string compressed_huffman;
	int cpt = 0;
	std::string max(64, 'a');
	for (int bl = 0; bl < rle_blocks.size(); bl++, cpt++) {
		auto tmp = encode_huffman(dc_ac_blocks[bl], tools.DC_code, tools.AC_code);
		max = max.length() > tmp.length() ? tmp : max;
		compressed_huffman += tmp;
	}

	return compressed_huffman;
}

imgGreyScale decompress_blocks(std::string compressed_blocks, int width, int height, jpeg_tools tools) {
	rev_huff_tbl DC1_LENGTH_REV = reverse_huffman_table(tools.DC_code);
	rev_huff_tbl AC_CODE_REV = reverse_huffman_table(tools.AC_code);

	// Decodage de Huffman
	std::vector<std::vector<pair_dc_ac>> de_huffman = decode_huffman(move(compressed_blocks), DC1_LENGTH_REV,
																	 AC_CODE_REV);

	// Conversion coeff : string binary repr vers int
	std::vector<std::vector<pair_rle>> de_dc_acs;
	for (int bl = 0; bl < de_huffman.size(); bl++)
		de_dc_acs.emplace_back(convert_dc_ac_to_rle(de_huffman[bl]));

	// Décodage RLE
	std::vector<std::vector<int>> inv_rle;
	for (int bl = 0; bl < de_dc_acs.size(); bl++)
		inv_rle.emplace_back(de_rle(de_dc_acs[bl]));

	// Décodage zig zag
	std::vector<std::vector<std::vector<int>>> de_zig_zag;
	for (int bl = 0; bl < inv_rle.size(); bl++)
		de_zig_zag.emplace_back(zig_zag_decodage(inv_rle[bl]));

	// Conversion int vers double
	std::vector<std::vector<std::vector<double>>> de_zig_zag_converted;
	for (int bl = 0; bl < de_zig_zag.size(); bl++) {
		std::vector<std::vector<double>> tmp;
		for (int i = 0; i < de_zig_zag[bl].size(); i++)
			tmp.emplace_back(std::vector<double>(de_zig_zag[bl][i].begin(), de_zig_zag[bl][i].end()));
		de_zig_zag_converted.emplace_back(tmp);
	}

	// De-quantification
	std::vector<std::vector<std::vector<double>>> de_quantified;
	for (int bl = 0; bl < de_zig_zag_converted.size(); bl++)
		de_quantified.emplace_back(de_quantize(de_zig_zag_converted[bl], tools.quant_mat));

	// DCT inverse
	std::vector<std::vector<std::vector<double>>> inv_dct;
	for (int bl = 0; bl < de_quantified.size(); bl++)
		inv_dct.emplace_back(idct_block(de_quantified[bl]));

	// Conversion double vers int
	std::vector<std::vector<std::vector<int>>> inv_dct_converted;
	for (int bl = 0; bl < inv_dct.size(); bl++) {
		std::vector<std::vector<int>> tmp;
		for (int i = 0; i < inv_dct[bl].size(); i++)
			tmp.emplace_back(std::vector<int>(inv_dct[bl][i].begin(), inv_dct[bl][i].end()));
		inv_dct_converted.emplace_back(tmp);
	}

	// Re-assemblage des block pour obtenir l'image dé-compréssée
	auto img_compressed = deSplitImg(inv_dct_converted, width, height);
	return img_compressed;
}

