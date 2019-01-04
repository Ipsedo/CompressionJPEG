//
// Created by samuel on 24/12/18.
//

#include "img_misc.h"

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
			tmp.push_back((std::get<0>(img.pixels[i][j]) + std::get<1>(img.pixels[i][j]) + std::get<2>(img.pixels[i][j])) / 3);
		}
		res.pixels.push_back(tmp);
	}
	return res;
}

std::vector<std::vector<std::vector<int>>> splitImg(imgGreyScale img) {
	std::vector<std::vector<std::vector<int>>> res;

	for (int y = 0; y < img.height; y += 8) {
		for (int x = 0; x < img.width; x += 8) {
			res.push_back(makeBlock(img, x, y));
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
				tmp[j] = img.pixels[i + y][j + x];
			else
				tmp[j] = PADDING;
		}
		res.push_back(tmp);
	}

	return res;
}
