cmake_minimum_required(VERSION 2.8.12)
project(example)

add_library(play SHARED play.cpp)
include_directories(./)
link_directories(./)

add_subdirectory(pybind11)
pybind11_add_module(main SHARED main.cpp fun.cpp)
target_link_libraries(main PRIVATE play)
