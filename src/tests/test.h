//
// Created by samuel on 06/01/19.
//

#ifndef COMPRESSIONJPEG_TEST_H
#define COMPRESSIONJPEG_TEST_H

#include <string>

/**
 * Test de lecture d'image BMP
 * @param file_name
 */
void test_bmp(std::string file_name);

/**
 * Test de l'enchainement des étapes
 */
void test_all();

/**
 * Test de l'encodage zig zag
 */
void test_zig_zag();

#endif //COMPRESSIONJPEG_TEST_H
