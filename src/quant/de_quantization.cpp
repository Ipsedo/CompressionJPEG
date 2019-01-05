//
// Created by samuel on 28/12/18.
//

#include "de_quantization.h"


std::vector<std::vector<double>>
de_quantize(std::vector<std::vector<double>> F_prime, std::vector<std::vector<double>> Q) {
	std::vector<std::vector<double>> res;

	for (int u = 0; u < F_prime.size(); u++) {
		std::vector<double> line;
		for (int v = 0; v < F_prime[u].size(); v++) {
			line.emplace_back(F_prime[u][v] * Q[u][v]);
		}
		res.emplace_back(line);
	}

	return res;
}
