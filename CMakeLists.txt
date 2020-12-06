cmake_minimum_required(VERSION 3.17)
project(IMS)

set(CMAKE_CXX_STANDARD 17)

add_executable(covid main.cpp main.h my_string.cpp my_string.h CellularAutomaton.cpp CellularAutomaton.h Matrix.h Cell.h Person.h)