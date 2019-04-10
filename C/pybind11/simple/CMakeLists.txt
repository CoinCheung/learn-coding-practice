cmake_minimum_required(VERSION 2.8.12)
project(parse_with_cpp)


add_subdirectory(pybind11)
pybind11_add_module(main SHARED main.cpp)


