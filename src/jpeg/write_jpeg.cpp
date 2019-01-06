//
// Created by samuel on 01/01/19.
//

#include "write_jpeg.h"
#include "markers.h"
#include <fstream>

void write_jpeg(std::string output_file_name) {
	std::ofstream file(output_file_name);

	unsigned char header[2]{0xFF, SOI};
	file.write((char *) header, 2);

	unsigned char quant_table[4]{0xFF, DQT,
								 0x80, 0x00}; // une seule table + Big Endian
}
