cmake_minimum_required(VERSION 3.17)
project(Matrix)

set(CMAKE_CXX_STANDARD 14)

add_executable(Matrix main.cpp Matrix.cpp Matrix.h mainFunctions.cpp)