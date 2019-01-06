#include <iostream>
#include "bmp/read_bmp.h"
#include "bmp/write_bmp.h"
#include "enc/huffman.h"
#include "quant/quant_matrix.h"
#include "jpeg/pipeline.h"
#include "img/img_misc.h"
#include "tests/test.h"
#include "enc/coeff.h"
#include <vector>
#include <iomanip>


/**
 * Test de compression puis de de-compression
 * Résultats écrits sur des images bmp
 */
void final_test() {

	// Lecture de l'image bmp non compressée
	imgRGB img = readBMP("./res/MARBLES.BMP");

	std::cout << "Img width : " << img.width << std::endl;
	std::cout << "Img height : " << img.height << std::endl;

	// Conversion vers une image en nuance de gris
	imgGreyScale imgGS = toGreyScale(img);

	// Ecriture de l'image témoin dans un fichier "original.bmp"
	write_grey_scale(imgGS, "original.bmp");

	jpeg_tools tools = {Q1, DC1_LENGTH, AC_CODE};
	std::string huffman_blocks = make_compressed_blocks(imgGS, tools);

	std::cout << "(compressé / original) : " << huffman_blocks.length() / 8 << " / " << imgGS.width * imgGS.height
			  << " octets" << std::endl;

	auto img_compressed = decompress_blocks(huffman_blocks, imgGS.width, imgGS.height, tools);

	// Ecriture de l'image dé-compressé vers le fichier "decompressed.bmp"
	write_grey_scale(img_compressed, "decompressed.bmp");
}

int main(int argc, char **argv) {

	//test_bmp("res/hibiscus.bmp");

	//test_all();

	/*huff_tbl dc_tbl1 = DC1_LENGTH;
	std::cout << dc_tbl1[EOB] << std::endl;*/

	//test_zig_zag();

	final_test();

	/*auto str = write_bits<10>(4, -15);
	std::cout << -15 << " " << str << std::endl;
	auto i = decode_bits(str, 4);
	std::cout << i << std::endl;*/

	return 0;
}
