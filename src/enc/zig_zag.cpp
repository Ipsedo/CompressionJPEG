//
// Created by samuel on 28/12/18.
//

#include "zig_zag.h"
#include <math.h>

std::vector<int> zig_zag_encodage(std::vector<std::vector<int>> to_encode) {
	std::vector<int> res;

	auto N = to_encode.size();

	int x, y;
	x = y = 0;

	/*
	 * indéxé comme ça (début en haut à gauche) :
	 *
	 * 	  X ----->
	 *  Y
	 *  |
	 *  |
	 *  V
	 *
	 * step == true -> diagonale qui monte vers la droite (sinon celle qui descend vers la gauche)
	 */
	bool step = true;

	auto lgt = N * N;
	int added = 0;
	int curr_diag = 0;

	while (added < lgt) {
		for (; x >= 0 && x < N && y >= 0 && y < N; added++) {
			res.push_back(to_encode[y][x]);

			if (step) { x++; y--; } // diagonale haut droit
			else { x--; y++; }      // diagonale bas gauche
		}

		curr_diag++;

		// On progresse en x y pour commencer au début de la nouvelle diagonale
		if (curr_diag < N) {
			/*
			 * Premier triangle de la matrice
			 * ____
			 * |  /
			 * |/
			 */
			if (step) y++;
			else x++;
		} else {
			/*
			 * Deuxième triangle de la matrice
			 *
			 *    / |
			 * 	/___|
			 */
			if (step) {
				x--;
				y += 2;
			} else {
				y--;
				x += 2;
			}
		}

		step = !step;
	}

	return res;
}


std::vector<std::vector<int>> zig_zag_decodage(std::vector<int> to_decode) {
	auto N = sqrt(to_decode.size());

	std::vector<std::vector<int>> res(N, std::vector<int>(N, 0));

	int x, y;
	x = y = 0;

	bool step = true;

	auto lgt = N * N;
	int added = 0;
	int curr_diag = 0;

	while (added < lgt) {
		for (; x >= 0 && x < N && y >= 0 && y < N; added++) {
			res[y][x] = to_decode[added];

			if (step) { x++; y--; }
			else { x--; y++; }
		}

		curr_diag++;

		if (curr_diag < N) {

			if (step) y++;
			else x++;

		} else {

			if (step) {
				x--;
				y += 2;
			} else {
				y--;
				x += 2;
			}
		}

		step = !step;
	}

	return res;
}
