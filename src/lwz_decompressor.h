#ifndef LZW_DECOMPRESSOR_SRC_LWZ_DECOMPRESSOR_H_
#define LZW_DECOMPRESSOR_SRC_LWZ_DECOMPRESSOR_H_
#include <iostream>

class LWZDecompressor {
 public:
  void Decompress(std::istream &input, std::ostream &output);
 private:
  int ReadCode(std::istream &input, bool is_even_pos);
};

#endif //LZW_DECOMPRESSOR_SRC_LWZ_DECOMPRESSOR_H_
