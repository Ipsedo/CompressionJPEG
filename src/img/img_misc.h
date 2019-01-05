//
// Created by samuel on 24/12/18.
//

#ifndef COMPRESSIONJPEG_IMG_MISC_H
#define COMPRESSIONJPEG_IMG_MISC_H

#include "repr.h"
#include <iostream>
#include <string>

/**
 * Color print stuff
 */
#define RESET   std::string("\033[0m")
#define RED     std::string("\033[31m")      /* Red */
#define GREEN   std::string("\033[32m")      /* Green */
#define BLUE    std::string("\033[34m")      /* Blue */

/**
 * Affiche une image (pour debug)
 * @param img
 * @param widthLimit La limite en largeur à afficher
 * @param heightLimit La limite en hauteur à afficher
 */
void printImg(imgRGB img, int widthLimit, int heightLimit);

/**
 * Transform une image en couleur RGB vers une image en nuances de gris
 * @param img La structure imgRGB représentant l'image couleur
 * @return L'image en nuances de gris associée
 */
imgGreyScale toGreyScale(imgRGB img);

/**
 * Découpe une image en sous block de 8 * 8 pixels
 * @param img La structure d'image en nuance de gris
 * @return Un vecteur contenant tout les sous blocks (matrice 8 * 8) de l'image img
 */
std::vector<std::vector<std::vector<int>>> splitImg(imgGreyScale img);

/**
 * Reconstruit l'image en nuance de gris depuis un vecteur de block (matrice 8 * 8)
 * @param to_de_split Le vecteur de block 8 * 8
 * @param width La largeur originel de l'image (pour le padding)
 * @param height La hauteur originel de l'image (pour le padding)
 * @return L'image en nuance de gris
 */
imgGreyScale deSplitImg(std::vector<std::vector<std::vector<int>>> to_de_split, int width, int height);

/**
 * On applique du padding avec de 0
 */
#define PADDING 0

/**
 * Créer un block 8 * 8 à partir de la position x y sur l'image img
 * et ajoute du padding si besoin
 * @param img L'image en nuance de gris
 * @param x L'abscisse gauche du block
 * @param y L'orfonnée haut du block
 * @return Le block commencant en [x, y]
 */
std::vector<std::vector<int>> makeBlock(imgGreyScale img, int x, int y);

#endif //COMPRESSIONJPEG_IMG_MISC_H
