//
// Created by samuel on 24/12/18.
//

#include "img_misc.h"
#include <cmath>

void printImg(imgRGB img, int widthLimit, int heightLimit) {
	if (widthLimit > img.width) {
		std::cout << "Width limit cannot be greater than image width ! (" << widthLimit << " > " << img.width << ")"
				  << std::endl;
	}
	if (heightLimit > img.height) {
		std::cout << "Height limit cannot be greater than image width ! (" << heightLimit << " > " << img.height << ")"
				  << std::endl;
	}


	for (int i = 0; i < heightLimit; i++) {
		std::string line;
		for (int j = 0; j < widthLimit; j++) {
			color pixel = img.pixels[i][j];
			int r = std::get<0>(pixel);
			int g = std::get<1>(pixel);
			int b = std::get<2>(pixel);
			if (r > g && r > b)
				line += RED + "# " + RESET;
			else if (g > b && g > r)
				line += GREEN + "# " + RESET;
			else
				line += BLUE + "# " + RESET;
		}
		std::cout << line << std::endl;
	}
}

imgGreyScale toGreyScale(imgRGB img) {
	imgGreyScale res;
	res.width = img.width;
	res.height = img.height;

	for (int i = 0; i < res.height; i++) {
		std::vector<int> tmp;
		for (int j = 0; j < res.width; j++) {
			// Moyenne des 3 composantes
			auto c = (std::get<0>(img.pixels[i][j]) + std::get<1>(img.pixels[i][j]) + std::get<2>(img.pixels[i][j]))
					 / 3;
			tmp.emplace_back(c);
		}
		res.pixels.emplace_back(tmp);
	}
	return res;
}

std::vector<std::vector<std::vector<int>>> splitImg(imgGreyScale img) {
	std::vector<std::vector<std::vector<int>>> res;

	for (int y = 0; y < img.height; y += 8) {
		for (int x = 0; x < img.width; x += 8) {
			res.emplace_back(makeBlock(img, x, y));
		}
	}

	return res;
}


std::vector<std::vector<int>> makeBlock(imgGreyScale img, int x, int y) {
	std::vector<std::vector<int>> res;

	for (int i = 0; i < 8; i++) {
		std::vector<int> tmp(8, 0);
		for (int j = 0; j < 8; j++) {
			if (i + y < img.height && j + x < img.width)
				// Dans l'image
				tmp[j] = img.pixels[i + y][j + x];
			else {
				// En dehors de l'image : padding Symétrique
				int symJ = img.width - (j + x) - 1;
				int symI = img.height - (i + y) - 1;
				tmp[j] = img.pixels[symI + y][symJ + x];
			}
		}
		res.emplace_back(tmp);
	}

	return res;
}


imgGreyScale deSplitImg(std::vector<std::vector<std::vector<int>>> to_de_split, int width, int height) {
	imgGreyScale res;
	res.width = width;
	res.height = height;

	res.pixels = std::vector<std::vector<int>>((unsigned long) res.height, std::vector<int>(res.width, 0));

	// Deux premières boucles pour le parcourt des blocks
	for (int y = 0; y < height; y += 8) {
		for (int x = 0; x < width; x += 8) {
			int tmpY = y / 8;
			int tmpX = x / 8;
			int nb_block_per_row = (int) ceil(width / 8.0);
			int index_block = tmpY * nb_block_per_row + tmpX;

			// On récupère les valeur du block
			for (int i = 0; i < 8 && i + y < height; i++) {
				for (int j = 0; j < 8 && j + x < width; j++) {
					res.pixels[y + i][x + j] = to_de_split[index_block][i][j];
				}
			}
		}
	}

	return res;
}
