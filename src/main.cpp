#include <iostream>
#include <fstream>
#include "lwz_decompressor.h"

int main() {
  LWZDecompressor lwzDecoder;
  for (int i = 1; i <= 4; i++) {
    std::string comp_file_path = std::string("../compressed/compressedfile") + std::to_string(i) + std::string(".z");
    std::string decomp_file_path = std::string("../decompressed/decompressedfile") + std::to_string(i) + std::string(".txt");
    std::ifstream comp_file(comp_file_path, std::ios::binary);
    std::ofstream decomp_file(decomp_file_path);
    lwzDecoder.Decompress(comp_file, decomp_file);
    comp_file.close();
    decomp_file.close();
  }
  return 0;
}
