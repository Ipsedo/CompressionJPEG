//
// Created by samuel on 05/01/19.
//

#ifndef COMPRESSIONJPEG_RLE_H
#define COMPRESSIONJPEG_RLE_H

#include <vector>
#include <cmath>
#include <bitset>
#include <tuple>
#include <iostream>

/**
 * On définit le type pair_rle :
 * unsigned char, un octet dont :
 * 	- les 4 premier bits représentent le nombre de 0 (Codage RLE sur 0)
 * 	- les 4 dernier bits représentent la magnitude du prochain coefficient non-nul
 * int, le prochain coefficient non-nul
 */
typedef std::tuple<unsigned char, int> pair_rle;

/**
 * Applique le codage RLE (sur 0) à un block encodé en zig-zag
 * @param quantized_zig_zag_block La sortie de l'encodage zig zag de la matrice de fréquences quantifiée
 * @return Un vecteur de pair_rle représentant le block encodé via RLE sur 0
 */
std::vector<pair_rle> rle(std::vector<int> quantized_zig_zag_block);

/**
 * Reconstruit la suite de fréquences originale
 * @param rle_values La suite de pair_rle consituant un block
 * @return Le block décodé sous forme zig-zag
 */
std::vector<int> de_rle(std::vector<pair_rle> rle_values);

/**
 * On définit un type pair_dc_ac
 * unsigned char : idem que pour pair_rle
 * std::string : la représentation binaire du coefficient DC ou AC
 */
typedef std::tuple<unsigned char, std::string> pair_dc_ac;

/**
 * Transform la sortie de RLE pour y associer la forme binaire des cofficients DC et AC
 * @param rle Le vecteur de pair_rle à transformer
 * @return Un vecteur de pair_dc_ac
 */
std::vector<pair_dc_ac> write_dc_acs(std::vector<pair_rle> rle);

/**
 * Convertit la représentation binaire en format string du coefficient vers une valeur entière
 * @param dc_acs
 * @return
 */
std::vector<pair_rle> convert_dc_ac_to_rle(std::vector<pair_dc_ac> dc_acs);

#endif //COMPRESSIONJPEG_RLE_H
