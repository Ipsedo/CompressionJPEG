#include <iostream>
#include "bmp/read_bmp.h"
#include "img/img_misc.h"
#include "dct/idct.h"
#include "dct/fdct.h"
#include "quant/quantization.h"
#include "quant/quant_matrix.h"
#include "quant/de_quantization.h"
#include <vector>

int main(int argc, char **argv) {
	/*if (argc < 2) {
	  std::cout << "arg 1 must be the bmp file name to convert" << std::endl;
	}

	std::string fileName = argv[1];
	imgRGB img = readBMP(fileName);

	std::cout << "Img width : " << img.width << std::endl;
	std::cout << "Img height : " << img.height << std::endl;

	printImg(img, img.width, img.height);*/

	int N = 8;

	std::vector<std::vector<double>> r;
	for (int i = 0; i < N; i++) {
		std::vector<double> tmp;
		for (int j = 0; j < N; j++) {
			tmp.push_back(i * j);
		}
		r.push_back(tmp);
	}

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

	return 0;
}
