#include <iostream>
#include "bmp/read_bmp.h"
#include "img/img_misc.h"


int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "arg 1 must be the bmp file name to convert" << std::endl;
  }

  std::string fileName = argv[1];
  imgRGB img = readBMP(fileName);

  std::cout << "Img width : " << img.width << std::endl;
  std::cout << "Img height : " << img.height << std::endl;

  printImg(img, img.width, img.height);

  return 0;
}
