#include "lwz_decompressor.h"

#include <iostream>
#include <map>
#include <cmath>

// TO DO:
//reset dictionary
//sTsTs decoding
void LWZDecompressor::Decompress(std::istream &input, std::ostream &output) {
  if (input.fail()) {
    std::cout << "Error with input." << std::endl;
    return;
  }
  if (output.fail()) {
    std::cout << "Error with output." << std::endl;
    return;
  }
  std::map<int, std::string> dictionary;
  for (int i = 0; i < 256; i++) {
    dictionary[i] = i;
  }
  int dictionarySize = 256; //1 byte
  int maxDictSize = dictionarySize * pow(2, 4); //4 bits are left to extend the dictionary
  bool evenPos = true;
  bool isFirstCode = true;
  std::string w = "";
  while (input.peek() != EOF) {
    int code;
    if (evenPos) {
//      std::cout << "even ";
      int c1 = input.get();
      if (input.peek() == EOF) {
        std::cout << "STOP c1 " << c1 << " kk" << std::endl;
      }
      int c2 = input.get();
      if (input.peek() != EOF) {
        code = (c1 << 4) + (c2 >> 4);
        input.seekg(-1, std::ios::cur); //Shifting pointer back by 1 char.
        evenPos = false;
      } else {
        code = ((c1 & 15) << 8) + c2; // 15 = 0b00001111
      }

    } else {
//      std::cout << "odd ";
      int c1 = input.get();
      if (input.peek() == EOF) {
        std::cout << "STOP c1 " << c1 << " kk" << std::endl;
      }
      int c2 = input.get();
      code = ((c1 & 15) << 8) + c2; // 15 = 0b00001111
      evenPos = true;
    }
    if (dictionary.count(code) > 0) { //
      output << dictionary[code];
      w += dictionary[code].at(0);
//      std::cout << dictionary[code] << "  got:" << code << ", add new to dict " << dictionarySize << ": " << w << std::endl;
      if (isFirstCode) {
        isFirstCode = false;
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
      std::cout << "aaaaam  got:" << code << ", add new to dict " << dictionarySize << ": " << w << std::endl;
      std::cout << " code > dictionarySize" << std::endl;
    }
  }
}