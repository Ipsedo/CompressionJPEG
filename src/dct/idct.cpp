//
// Created by samuel on 26/12/18.
//

#include "idct.h"
#include <cmath>

double idct(std::vector<std::vector<double>> blockDCT, int x, int y, int N) {
	double sum = 0.0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			double c_i = i == 0.0 ? 1.0 / sqrt(2.0) : 1.0;
			double c_j = j == 0.0 ? 1.0 / sqrt(2.0) : 1.0;
			sum += c_i * c_j * blockDCT[i][j] * cos((2.0 * x + 1.0) * i * M_PI / (2.0 * N)) *
				   cos((2.0 * y + 1.0) * j * M_PI / (2.0 * N));
		}
	}
	return 2.0 * sum / N;
}


std::vector<std::vector<double>> idct_block(std::vector<std::vector<double>> blockDCT) {
	auto N = blockDCT.size();
	std::vector<std::vector<double>> res(N, std::vector<double>(N, 0));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			res[i][j] = idct(blockDCT, i, j, N);

	return res;
}
