cmake_minimum_required(VERSION 2.8.12)
project(example)

add_executable(run try.cpp)
target_link_libraries(run PRIVATE tcmalloc)
