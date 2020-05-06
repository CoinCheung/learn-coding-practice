cmake_minimum_required(VERSION 2.8.12)
project(example)

add_compile_options(-std=c++11 -Wall)

add_executable(vector vector.cpp)
target_link_libraries(vector PRIVATE tcmalloc)

add_executable(tuple tuple.cpp)
target_link_libraries(tuple PRIVATE tcmalloc)

add_executable(try try.cpp)
target_link_libraries(try PRIVATE tcmalloc)
