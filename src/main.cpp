#include <iostream>
#include "bmp/read_bmp.h"
#include "img/img_misc.h"
#include "dct/idct.h"
#include "dct/fdct.h"
#include "quant/quantization.h"
#include "quant/quant_matrix.h"
#include "quant/de_quantization.h"
#include "enc/zig_zag.h"
#include "enc/huffman_tables.h"
#include "enc/rle.h"
#include "bmp/write_bmp.h"
#include <vector>
#include <iomanip>

void test_bmp(std::string file_name) {
	imgRGB img = readBMP(file_name);

	std::cout << "Img width : " << img.width << std::endl;
	std::cout << "Img height : " << img.height << std::endl;

	//printImg(img, img.width, img.height);

	imgGreyScale imgGS = toGreyScale(img);

	write_grey_scale(imgGS, "out_original.bmp");

	auto blocks = splitImg(imgGS);

	auto desplitted = deSplitImg(blocks, imgGS.width, imgGS.height);

	std::cout << blocks.size() << std::endl;

	std::cout << imgGS.width << ", " << img.height << std::endl;

	write_grey_scale(desplitted, "out_desplitted.bmp");
}

void test_all() {
	int N = 8;

	// from wikipedia https://fr.wikipedia.org/wiki/JPEG
	std::vector<std::vector<double>> r = { {139,144,149,153,155,155,155,155},
										   {144,151,153,156,159,156,156,156},
										   {150,155,160,163,158,156,156,156},
										   {159,161,162,160,160,159,159,159},
										   {159,160,161,162,162,155,155,155},
										   {161,161,161,161,160,157,157,157},
										   {162,162,161,163,162,157,157,157},
										   {162,162,161,161,163,158,158,158} };

	std::cout << "Original : " << std::endl;
	std::vector<std::vector<double>> dct;
	for (int i = 0; i < N; i++) {
		std::vector<double> tmp;
		for (int j = 0; j < N; j++) {
			std::cout << r[i][j] << ", ";
			tmp.emplace_back(fdct(r, i, j, N));
		}
		std::cout << std::endl;
		dct.emplace_back(tmp);
	}
	std::cout << std::endl;

	std::cout << "DCT : " << std::endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			std::cout << dct[i][j] << ", ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Inverse DCT : " << std::endl;
	std::vector<std::vector<double>> invdct;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			std::cout << idct(dct, i, j, N) << ", ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::vector<std::vector<double>> quantized = quantize(dct, Q1);

	std::cout << "Quantized DCT : " << std::endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			std::cout << quantized[i][j] << ", ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::vector<std::vector<double>> de_quantized = de_quantize(quantized, Q1);

	std::cout << "Inverse Quantized (lossy...) :" << std::endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			std::cout << de_quantized[i][j] << ", ";
		}
		std::cout << std::endl;
	}


	std::vector<std::vector<int>> quantized_converted;
	for (int i = 0; i < quantized.size(); i++)
		quantized_converted.emplace_back(std::vector<int>(quantized[i].begin(), quantized[i].end()));

	std::vector<int> zig_zag_res = zig_zag_encodage(quantized_converted);

	std::cout << "zig zag" << std::endl;
	for (int i = 0; i < zig_zag_res.size(); i++)
		std::cout << zig_zag_res[i] << ", ";
	std::cout << std::endl << std::endl;

	std::vector<pair_rle> rle_res = rle(zig_zag_res);

	std::cout << "RLE" << std::endl;

	for (int i = 0; i < rle_res.size(); i++)
		std::cout << "[0x" << std::setfill('0') << std::setw(2)<< std::hex << static_cast<unsigned int>(std::get<0>(rle_res[i])) << std::dec << ", " << std::get<1>(rle_res[i]) <<"] ";
	std::cout << std::endl << std::endl;

	/*std::vector<pair_dc_ac> pre_coded_dc_ac = write_dc_acs(rle_res);

	std::cout << "Pre coded DC and AC" << std::endl;
	for (int i = 0; i < pre_coded_dc_ac.size(); i++)
		std::cout << "[0x" << std::setfill('0') << std::setw(2)<< std::hex << static_cast<unsigned int>(std::get<0>(pre_coded_dc_ac[i])) << std::dec << ", " << std::get<1>(pre_coded_dc_ac[i]) <<"] ";
	std::cout << std::endl << std::endl;*/

	std::cout << "de RLE" << std::endl;
	auto inv_rle = de_rle(rle_res);

	for (int i : inv_rle)
		std::cout << i << ", ";
	std::cout << std::endl;
}

void test_zig_zag() {
	int N = 8;

	int curr = 0;
	std::vector<std::vector<int>> v;

	std::cout << "Original :" << std::endl;
	for (int i = 0; i < N; i++) {
		std::vector<int> line;
		for (int j = 0; j < N; j++) {
			line.emplace_back(curr);
			std::cout << std::setfill(' ') << std::setw(2) << curr << ", ";
			curr++;
		}
		std::cout << std::endl;
		v.emplace_back(line);
	}
	std::cout << std::endl;

	std::vector<int> res = zig_zag_encodage(v);

	for (int i = 0; i < res.size(); i++)
		std::cout << res[i] << ", ";
	std::cout << std::endl;

	std::cout << "De zig zag" << std::endl;
	auto de_zig_zag = zig_zag_decodage(res);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			std::cout << std::setfill(' ') << std::setw(2) << de_zig_zag[i][j] << ", ";
			curr++;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void final_test(int argc, char **argv) {
	/*if (argc < 2) {
		std::cout << "arg 1 must be the bmp file name to convert" << std::endl;
	}*/

	imgRGB img = readBMP("res/hibiscus.bmp");

	std::cout << "Img width : " << img.width << std::endl;
	std::cout << "Img height : " << img.height << std::endl;

	//printImg(img, img.width, img.height);

	imgGreyScale imgGS = toGreyScale(img);

	write_grey_scale(imgGS, "original.bmp");

	auto blocks = splitImg(imgGS);

	std::vector<std::vector<std::vector<double>>> dct;

	for (int bl = 0; bl < blocks.size(); bl++) {
		std::vector<std::vector<double>> tmp;
		for (int j = 0; j < blocks[bl].size(); j++)
			tmp.emplace_back(std::vector<double>(blocks[bl][j].begin(), blocks[bl][j].end()));
		dct.emplace_back(tmp);
	}

	for (int bl = 0; bl < dct.size(); bl++)
		dct[bl] = fdct_block(dct[bl]);

	std::vector<std::vector<std::vector<double>>> quant;

	for (int bl = 0; bl < dct.size(); bl++)
		quant.emplace_back(quantize(dct[bl], Q1));

	std::vector<std::vector<std::vector<int>>> quant_converted;
	for (int bl = 0; bl < quant.size(); bl++) {
		std::vector<std::vector<int>> tmp;
		for (int i = 0; i < quant[bl].size(); i++)
			tmp.emplace_back(std::vector<int>(quant[bl][i].begin(), quant[bl][i].end()));
		quant_converted.emplace_back(tmp);
	}

	std::vector<std::vector<int>> zig_zag;
	for (int bl = 0; bl < quant_converted.size(); bl++) {
		zig_zag.emplace_back(zig_zag_encodage(quant_converted[bl]));
	}

	std::vector<std::vector<pair_rle>> rle_blocks;
	for (int bl = 0; bl < zig_zag.size(); bl++)
		rle_blocks.emplace_back(rle(zig_zag[bl]));

	std::vector<pair_rle> concatenated;
	for (int bl = 0; bl < rle_blocks.size(); bl++) {
		for (int i = 0; i < rle_blocks[bl].size(); i++)
			concatenated.emplace_back(rle_blocks[bl][i]);
	}

	long nb_bits = 0;
	for (int i = 0; i < concatenated.size(); i++) {
		unsigned char rle_marker = std::get<0>(concatenated[i]);
		nb_bits += 8 + (rle_marker | 0x0F); // Un octet pour la balise rle + le nombre de bit pour la magnitude
	}
	std::cout<< "(compressé / original) : " << nb_bits / 8 << " / " << imgGS.width * imgGS.height << " octets" << std::endl;

	/**
	 * Décompression
	 */

	std::vector<std::vector<int>> inv_rle;
	for (int bl = 0; bl < rle_blocks.size(); bl++)
		inv_rle.emplace_back(de_rle(rle_blocks[bl]));

	std::vector<std::vector<std::vector<int>>> de_zig_zag;
	for (int bl = 0; bl < inv_rle.size(); bl++)
		de_zig_zag.emplace_back(zig_zag_decodage(inv_rle[bl]));

	std::vector<std::vector<std::vector<double>>> de_zig_zag_converted;
	for (int bl = 0; bl < de_zig_zag.size(); bl++) {
		std::vector<std::vector<double>> tmp;
		for (int i = 0; i < de_zig_zag[bl].size(); i++)
			tmp.emplace_back(std::vector<double>(de_zig_zag[bl][i].begin(), de_zig_zag[bl][i].end()));
		de_zig_zag_converted.emplace_back(tmp);
	}

	std::vector<std::vector<std::vector<double>>> de_quantified;
	for (int bl = 0; bl < de_zig_zag_converted.size(); bl++)
		de_quantified.emplace_back(de_quantize(de_zig_zag_converted[bl], Q1));

	std::vector<std::vector<std::vector<double>>> inv_dct;
	for (int bl = 0; bl < de_quantified.size(); bl++)
		inv_dct.emplace_back(idct_block(de_quantified[bl]));

	std::vector<std::vector<std::vector<int>>> inv_dct_converted;
	for (int bl = 0; bl < inv_dct.size(); bl++) {
		std::vector<std::vector<int>> tmp;
		for (int i = 0; i < inv_dct[bl].size(); i++)
			tmp.emplace_back(std::vector<int>(inv_dct[bl][i].begin(), inv_dct[bl][i].end()));
		inv_dct_converted.emplace_back(tmp);
	}

	auto img_compressed = deSplitImg(inv_dct_converted, img.width, img.height);
	write_grey_scale(img_compressed, "compressed.bmp");
}

int main(int argc, char **argv) {

	/*if (argc < 2) {
	  std::cout << "arg 1 must be the bmp file name to convert" << std::endl;
	}*/

	//test_bmp("res/hibiscus.bmp");

	//test_all();

	/*huff_tbl dc_tbl1 = DC1_LENGTH;
	std::cout << dc_tbl1[EOB] << std::endl;*/

	//test_zig_zag();

	final_test(argc, argv);

	return 0;
}
