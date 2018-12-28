//
// Created by samuel on 24/12/18.
//

#ifndef COMPRESSIONJPEG_REPR_H
#define COMPRESSIONJPEG_REPR_H

#include <vector>
#include <tuple>

typedef std::tuple<int, int, int> color;

struct imgRGB {
	int width;
	int height;
	std::vector<std::vector<color>> pixels;
};

#endif //COMPRESSIONJPEG_REPR_H
