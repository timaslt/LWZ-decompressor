#include "lwz_decompressor.h"

#include <iostream>
#include <map>
#include <cmath>

// TO DO:
//reset dictionary
//sTsTs decoding
//fix reading the end bytes
void LWZDecompressor::Decompress(std::istream &input, std::ostream &output) {
  if (input.fail()) {
    std::cout << "Error opening the input file" << std::endl;
    return;
  }
  if (output.fail()) {
    std::cout << "Error opening the output file" << std::endl;
    return;
  }
  std::map<int, std::string> dictionary;
  for (int i = 0; i < 256; i++) {
    dictionary[i] = i;
  }
  int dictionarySize = 256; //1 byte
  int maxDictSize = dictionarySize * pow(2, 4); //4 bits are left to extend the dictionary
  bool evenPos = true;
  bool first = true;
  std::string w = "";
  while (!input.eof()) {
    int code;
    if (evenPos) {
      int c1 = input.get();
      int c2 = input.peek();
      code = (c1 << 4) + (c2 >> 4);
      evenPos = false;
    } else {
      int c1 = input.get();
      int c2 = input.get();
      code = ((c1 & 15) << 8) + c2; // 15d = 00001111b
      evenPos = true;
    }
    if (dictionary.count(code) > 0) { //
      output << dictionary[code];
//      std::cout << dictionary[code];
      w += dictionary[code].at(0);
//      std::cout << "  got:" << code << ", add new to dict " << dictionarySize << ": " << w << std::endl;
      if (first) {
        first = false;
      } else {
        if (dictionarySize == maxDictSize) {
          dictionarySize = 256; //Initial size + 1
        }
        dictionary[dictionarySize] = w;
        dictionarySize++;
      }
      w = dictionary[code];
    } else if (code == dictionarySize) {
      std::cout << " code == dictionarySize" << std::endl;
    } else {
//      std::cout << "aaaaam  got:" << code << ", add new to dict " << dictionarySize << ": " << w << std::endl;
      std::cout << " code > dictionarySize" << std::endl;
    }
  }
}