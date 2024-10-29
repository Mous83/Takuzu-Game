cmake_minimum_required(VERSION 3.21)
project(projet C)

set(CMAKE_C_STANDARD 99)

add_executable(projet main.c takuzu.c takuzu.h 4x4.c 8x8.c)
