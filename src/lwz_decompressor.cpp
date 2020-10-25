#include "lwz_decompressor.h"

#include <iostream>
#include <map>
#include <cmath>

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
  for (int i = 1; i <= 256; i++) {
    dictionary[i] = i;
  }
  int dictionarySize = 256; //1 byte
  int maxDictSize = dictionarySize * pow(2, 4); //4 bits are left to extend the dictionary
  bool evenPos = true;
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
//      w += char(code);
    } else if (code == dictionarySize) {
      std::cout << " code == dictionarySize" << std::endl;
    } else {
      std::cout << " code > dictionarySize" << std::endl;
    }
//    input.get();
  }
//  int byte1 = input.get();
//  int byte2 = input.get();
//  int test1 = 1;
//  int byte2real = byte2 >> 4;
//  int code = (byte1 << 4) + byte2real;
//  std::cout << byte1 << " and " << byte2 << std::endl;
//  std::cout << "byte2 code part : " << byte2real << std::endl;
//  std::cout << "CODE : " << char(code) << std::endl;
//  output << char(code);
}