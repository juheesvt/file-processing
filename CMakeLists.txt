cmake_minimum_required(VERSION 3.13)
project(file_processing)

set(CMAKE_CXX_STANDARD 14)

add_executable(file_processing
        binary-search-tree/bst.hpp
        binary-search-tree/main.cpp)