#ifndef LZW_DECOMPRESSOR_SRC_LWZ_DECOMPRESSOR_H_
#define LZW_DECOMPRESSOR_SRC_LWZ_DECOMPRESSOR_H_

class LWZDecompressor {
 public:
  void Decompress(std::istream &input, std::ostream &output);
};

#endif //LZW_DECOMPRESSOR_SRC_LWZ_DECOMPRESSOR_H_
