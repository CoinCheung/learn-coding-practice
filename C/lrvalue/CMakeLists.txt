cmake_minimum_required(VERSION 2.8.12)
project(example)

# add_compile_options(-std=c++11 -Wall -O0)
add_compile_options(-std=c++11 -Wall -O2)

add_executable(main try_return.cpp)
target_link_libraries(main PRIVATE tcmalloc)

