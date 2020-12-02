cmake_minimum_required(VERSION 3.17)
project(IMS)

set(CMAKE_CXX_STANDARD 17)

add_executable(IMS main.cpp main.h CelluarAtomaton.cpp CelluarAtomaton.h Matrix.cpp Matrix.h Cell.cpp Cell.h)