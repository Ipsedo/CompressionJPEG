//
// Created by samuel on 06/01/19.
//

#include "test.h"
#include "../bmp/read_bmp.h"
#include "../bmp/write_bmp.h"
#include "../img/img_misc.h"
#include "../dct/fdct.h"
#include "../dct/idct.h"
#include "../quant/quantization.h"
#include "../enc/zig_zag.h"
#include "../enc/rle.h"
#include "../enc/huffman.h"
#include "../quant/de_quantization.h"
#include "../quant/quant_matrix.h"
#include <vector>
#include <iostream>
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
	std::vector<std::vector<double>> r = {{139, 144, 149, 153, 155, 155, 155, 155},
										  {144, 151, 153, 156, 159, 156, 156, 156},
										  {150, 155, 160, 163, 158, 156, 156, 156},
										  {159, 161, 162, 160, 160, 159, 159, 159},
										  {159, 160, 161, 162, 162, 155, 155, 155},
										  {161, 161, 161, 161, 160, 157, 157, 157},
										  {162, 162, 161, 163, 162, 157, 157, 157},
										  {162, 162, 161, 161, 163, 158, 158, 158}};

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
		std::cout << "[0x" << std::setfill('0') << std::setw(2) << std::hex
				  << static_cast<unsigned int>(std::get<0>(rle_res[i])) << std::dec << ", " << std::get<1>(rle_res[i])
				  << "] ";
	std::cout << std::endl << std::endl;

	std::vector<pair_dc_ac> pre_coded_dc_ac = write_dc_acs(rle_res);

	std::cout << "Pre coded DC and AC" << std::endl;
	for (int i = 0; i < pre_coded_dc_ac.size(); i++)
		std::cout << "[0x" << std::setfill('0') << std::setw(2) << std::hex
				  << static_cast<unsigned int>(std::get<0>(pre_coded_dc_ac[i])) << std::dec << ", "
				  << std::get<1>(pre_coded_dc_ac[i]) << "] ";
	std::cout << std::endl << std::endl;

	std::cout << "Binary string repre" << std::endl;
	auto huff = encode_huffman(pre_coded_dc_ac, DC1_LENGTH, AC_CODE);
	std::cout << huff << std::endl << std::endl;

	rev_huff_tbl DC1_LENGTH_REV = reverse_huffman_table(DC1_LENGTH);
	rev_huff_tbl AC_CODE_REV = reverse_huffman_table(AC_CODE);

	std::cout << "Decoded huffman" << std::endl;
	auto decoded_huffman = decode_huffman(huff, DC1_LENGTH_REV, AC_CODE_REV);
	for (int i = 0; i < decoded_huffman[0].size(); i++)
		std::cout << "[0x" << std::setfill('0') << std::setw(2) << std::hex
				  << static_cast<unsigned int>(std::get<0>(decoded_huffman[0][i])) << std::dec << ", "
				  << std::get<1>(decoded_huffman[0][i]) << "] ";
	std::cout << std::endl << std::endl;

	std::cout << "De DC AC" << std::endl;
	auto de_dc_acs = convert_dc_ac_to_rle(decoded_huffman[0]);
	for (int i = 0; i < de_dc_acs.size(); i++)
		std::cout << "[0x" << std::setfill('0') << std::setw(2) << std::hex
				  << static_cast<unsigned int>(std::get<0>(de_dc_acs[i])) << std::dec << ", "
				  << std::get<1>(de_dc_acs[i]) << "] ";
	std::cout << std::endl << std::endl;

	std::cout << "de RLE" << std::endl;
	auto inv_rle = de_rle(de_dc_acs);

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