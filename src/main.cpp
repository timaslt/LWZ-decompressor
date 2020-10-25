#include <iostream>
#include <fstream>
#include "lwz_decompressor.h"

int main() {
  std::ifstream compFile("../compressed/compressedfile1.z", std::ios::binary);
  std::ofstream decompFile("../decompressed/decompressedfile1.txt");
  LWZDecompressor lwzDecoder;
  lwzDecoder.Decompress(compFile, decompFile);
  compFile.close();
  decompFile.close();
  std::cout << "Hello, World!" << std::endl;
  return 0;
}
