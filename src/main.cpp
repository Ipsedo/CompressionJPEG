#include <iostream>
#include "bmp/read_bmp.h"
#include "img/img_misc.h"
#include "dct/idct.h"
#include "dct/fdct.h"
#include <vector>

int main(int argc, char **argv) {
  /*if (argc < 2) {
    std::cout << "arg 1 must be the bmp file name to convert" << std::endl;
  }

  std::string fileName = argv[1];
  imgRGB img = readBMP(fileName);

  std::cout << "Img width : " << img.width << std::endl;
  std::cout << "Img height : " << img.height << std::endl;

  printImg(img, img.width, img.height);*/

  std::vector<std::vector<double>> r;
  for (int i = 0; i < 10; i++) {
      std::vector<double> tmp;
      for (int j = 0; j < 10; j++) {
          tmp.push_back(i * j);
      }
      r.push_back(tmp);
  }

  std::vector<std::vector<double>> dct;
  for (int i = 0; i < 10; i++) {
      std::vector<double> tmp;
      for (int j = 0; j < 10; j++) {
          std::cout << r[i][j] << ", ";
          tmp.push_back(fdct(r, i, j, 10));
      }
      std::cout << std::endl;
      dct.push_back(tmp);
  }
  std::cout << std::endl;

  std::vector<std::vector<double>> invdct;
  for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
          std::cout << idct(dct, i, j, 10) << ", ";
      }
      std::cout << std::endl;
  }


  return 0;
}
