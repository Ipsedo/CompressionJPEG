//
// Created by samuel on 06/01/19.
//

#include <sstream>
#include "split_str.h"

std::vector<std::string> split_str(std::string str, char c) {
	std::stringstream ss(str);
	std::string item;
	std::vector<std::string> elems;
	while (getline(ss, item, c)) {
		//elems.push_back(item);
		elems.push_back(move(item)); // if C++11 (based on comment from @mchiasson)
	}
	return elems;
}
