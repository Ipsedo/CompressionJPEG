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
#include <vector>
#include <iomanip>

void test_bmp(std::string file_name) {
	imgRGB img = readBMP(file_name);

	std::cout << "Img width : " << img.width << std::endl;
	std::cout << "Img height : " << img.height << std::endl;

	//printImg(img, img.width, img.height);

	imgGreyScale imgGS = toGreyScale(img);

	auto blocks = splitImg(imgGS);

	std::cout << blocks.size() << std::endl;

	std::cout << imgGS.width << ", " << img.height << std::endl;
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
			tmp.push_back(fdct(r, i, j, N));
		}
		std::cout << std::endl;
		dct.push_back(tmp);
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
		quantized_converted.push_back(std::vector<int>(quantized[i].begin(), quantized[i].end()));

	std::vector<int> zig_zag_res = zig_zag_encodage(quantized_converted);

	std::cout << "zig zag" << std::endl;
	for (int i = 0; i < zig_zag_res.size(); i++)
		std::cout << zig_zag_res[i] << ", ";
	std::cout << std::endl << std::endl;

	std::vector<char> rle_res = rle(zig_zag_res);

	std::cout << "RLE" << std::endl;

	for (int i = 0; i < rle_res.size(); i++)
		std::cout << std::hex << static_cast<int>(rle_res[i]) << std::dec << ", ";
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
			line.push_back(curr);
			std::cout << std::setfill(' ') << std::setw(2) << curr << ", ";
			curr++;
		}
		std::cout << std::endl;
		v.push_back(line);
	}
	std::cout << std::endl;

	std::vector<int> res = zig_zag_encodage(v);

	for (int i = 0; i < res.size(); i++)
		std::cout << res[i] << ", ";
	std::cout << std::endl;
}

int main(int argc, char **argv) {

	/*if (argc < 2) {
	  std::cout << "arg 1 must be the bmp file name to convert" << std::endl;
	}

	test_bmp(argv[1]);*/

	test_all();

	/*huff_tbl dc_tbl1 = DC1_LENGTH;
	std::cout << dc_tbl1[EOB] << std::endl;*/

	//test_zig_zag();

	return 0;
}
