#include "lwz_decompressor.h"

#include <iostream>
#include <map>
#include <cmath>

void LWZDecompressor::Decompress(std::istream &input, std::ostream &output) {
  if (input.fail()) {
    std::cout << "Error with input." << std::endl;
    return;
  }
  if (output.fail()) {
    std::cout << "Error with output." << std::endl;
    return;
  }

  int dictionary_size = 256; //1 byte
  int max_dict_size = dictionary_size * pow(2, 4); //4 bits are left to extend the dictionary
  std::map<int, std::string> dictionary;
  for (int i = 0; i < dictionary_size; i++) {
    dictionary[i] = i;
  }

  bool is_even_pos = true;
  bool is_first_code = true;
  std::string w = "";

  while (input.peek() != EOF) {
    int code = ReadCode(input, is_even_pos);
    is_even_pos = !is_even_pos;

    if (code == dictionary_size) {
      //Rare case "cScSc" when code is not yet in the dictionary.
      w += w.at(0);
      output << w;
      if (dictionary_size == max_dict_size) {
        dictionary_size = 256; //Initial size
      }
      dictionary[dictionary_size] = w;
      dictionary_size++;
    } else if (dictionary.count(code) > 0) {
      output << dictionary[code];
      w += dictionary[code].at(0);
      if (is_first_code) {
        is_first_code = false;
      } else {
        if (dictionary_size == max_dict_size) {
          dictionary_size = 256; //Initial size
        }
        dictionary[dictionary_size] = w;
        dictionary_size++;
      }
      w = dictionary[code];
    } else {
      std::cout << "Error: invalid code found." << std::endl;
      return;
    }
  }
}

int LWZDecompressor::ReadCode(std::istream &input, bool is_even_pos) {
  int code;
  if (is_even_pos) {
    int c1 = input.get();
    int c2 = input.get();
    if (input.peek() != EOF) {
      code = (c1 << 4) + (c2 >> 4);
      input.seekg(-1, std::ios::cur); //Shifting pointer back by 1 char.
    } else {
      //Found the last code in the file.
      code = ((c1 & 15) << 8) + c2; // 15 = 0b00001111
    }
  } else {
    int c1 = input.get();
    int c2 = input.get();
    code = ((c1 & 15) << 8) + c2; // 15 = 0b00001111
  }
  return code;
}