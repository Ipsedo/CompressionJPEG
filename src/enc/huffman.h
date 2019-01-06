//
// Created by samuel on 05/01/19.
//

#ifndef COMPRESSIONJPEG_HUFFMAN_H
#define COMPRESSIONJPEG_HUFFMAN_H

#include <string>
#include <vector>
#include "rle.h"
#include "huffman_tables.h"

/**
 * Applique le codage d'Huffman pour la DC et les AC selon deux tables données
 * @param to_encode Le block à encoder
 * @param dc_table La table de huffman pour les DC
 * @param ac_table La table de huffman pour les AC
 * @return Le block encodé sous forme de chain de caractère contenant les bits
 */
std::string encode_huffman(std::vector<pair_dc_ac> to_encode, huff_tbl dc_table, huff_tbl ac_table);

/**
 * Décode une image entière selon deux tables de huffman inversées
 * @param code Le code de tout les blocks de l'image
 * @param rev_dc_tbl La table de Huffman inversé pour les DC
 * @param rev_ac_tbl La table de Huffman inversée pour les AC
 * @return Un vecteur de blocks (chaque block étant un vecteur de pair_dc_ac)
 */
std::vector<std::vector<pair_dc_ac>> decode_huffman(std::string code, rev_huff_tbl rev_dc_tbl, rev_huff_tbl rev_ac_tbl);

#endif //COMPRESSIONJPEG_HUFFMAN_H
