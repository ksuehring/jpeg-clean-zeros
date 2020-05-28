#minimal CMake file
cmake_minimum_required(VERSION 3.10)
project (JPEG_ZERO_CLEAN)

add_subdirectory (src)

install(TARGETS jpeg-zero-clean DESTINATION bin)
