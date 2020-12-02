cmake_minimum_required(VERSION 3.17)
project(IMS)

set(CMAKE_CXX_STANDARD 17)

add_executable(IMS main.cpp main.h CellularAutomaton.cpp CellularAutomaton.h Matrix.h Cell.h)