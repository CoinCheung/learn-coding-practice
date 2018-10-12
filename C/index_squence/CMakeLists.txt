cmake_minimum_required(VERSION 2.8.12)
project(example)

add_compile_options(-std=c++14 -Wall)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE tcmalloc)

