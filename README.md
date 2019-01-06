# Compression JPEG

Projet de l'UE TC5 du M2 AIC 2018-2019

_David Biard, Samuel Berrien_

## Informations
Usage :
```renderscript
$ git clone https://github.com/Ipsedo/CompressionJPEG.git
$ cd CompressionJPEG
$ ./build.sh
$ ./build/CompressionJPEG ./res/hibiscus.bmp
```

## Decription
Structure du projet :

```
root
 |-- res/           : images de test
 |-- build.sh       : script de compilation
 |-- CMakeLists.txt : fichier CMake
 |-- src/
      |-- bmp/     : écriture / lecture bmp
      |-- dct/     : DCT (forward et inverse)
      |-- enc/     : Encodage de l'image
      |              (Zig-Zag, RLE, Huffman)
      |-- img/     : Définitions structure image
      |              (+ split image)
      |-- jpeg/    : Pipeline de compression /
      |              décompression JPEG
      |-- quant/   : Quantification
      |-- tests/   : Différent tests
      |-- utils/   : Optional / pas nécéssaire
      |-- main.cpp : Fonction principale         

```
