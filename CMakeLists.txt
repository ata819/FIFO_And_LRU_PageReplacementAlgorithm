cmake_minimum_required(VERSION 3.17)
project(prog4 C)

set(CMAKE_C_STANDARD 99)

add_executable(prog4 main.c testvm.c vmalgorithm.c vmalgorithm.h)