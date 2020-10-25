cmake_minimum_required(VERSION 3.17)
project(LZW_decompressor)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp src/lwz_decompressor.h src/lwz_decompressor.cpp)

add_executable(LZW_decompressor ${SOURCE_FILES})