//
// Created by samuel on 26/12/18.
//

#include "fdct.h"
#include <math.h>

double fdct(std::vector<std::vector<double>> pixelBlock, int i, int j, int N) {
	double sum = 0.0;
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			sum += pixelBlock[x][y] * cos((2.0 * x + 1.0) * i * M_PI / (2.0 * N)) *
				   cos((2.0 * y + 1.0) * j * M_PI / (2.0 * N));
		}
	}
	double c_i = i == 0.0 ? 1.0 / sqrt(2.0) : 1.0;
	double c_j = j == 0.0 ? 1.0 / sqrt(2.0) : 1.0;
	return 2 * c_i * c_j * sum / N;
}

std::vector<std::vector<double>> fdct_block(std::vector<std::vector<double>> pixelBlock) {
	int N = pixelBlock.size();
	std::vector<std::vector<double>> res(N, std::vector<double>(N, 0));
	for (int i = 0; i < N; i ++)
		for (int j = 0; j < N; j++)
			res[i][j] = fdct(pixelBlock, i, j, N);

	return res;
}
