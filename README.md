# LWZ-decompressor
Lempel–Ziv–Welch decompressor from fixed 12-bit codes. I used C++14 version with CLion IDE.

[All decoded files are in the decompressed folder.](https://github.com/timaslt/LWZ-decompressor/tree/main/decompressed)

[Created a static library.](https://github.com/timaslt/LWZ-decompressor/tree/main/lib)
## Implemented edge cases
* Addressed uncommon edge case with code pattern 'cScSc'.
* The algorithm recognises if there are an odd number of codes in total and encode last code accordingly to the padding.
* When all possible 4096 entries in the dictionary are used it resets current dictionary pointer. (Algorithm rewrites the values, no need to clear/delete the whole dictionary).
* The decompressor is capable of decoding very large files since it does not hold data and works locally. It reads and decodes each code from the input stream and writes it to the output stream.
