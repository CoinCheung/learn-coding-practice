cmake_minimum_required(VERSION 2.8.12)
project(try)

add_executable(run source.cpp)
target_link_libraries(run PRIVATE tcmalloc)

