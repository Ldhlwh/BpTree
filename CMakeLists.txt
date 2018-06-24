cmake_minimum_required(VERSION 3.10)
project(DatabaseCode)

set(CMAKE_CXX_STANDARD 17)

add_executable(DatabaseCode bpt.cc bpt.h BpTree.hpp main.cpp predefined.h)
