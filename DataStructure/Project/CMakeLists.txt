cmake_minimum_required(VERSION 3.21)
project(Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project main.cpp Users.cpp Users.h Friends.cpp Friends.h User.cpp User.h)
