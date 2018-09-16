cmake_minimum_required(VERSION 2.8.12)
project(example)

# include_directories(SYSTEM "${PROJECT_SOURCE_DIR}/")
# link_directories("${PROJECT_SOURCE_DIR}/")
# add_library(fun fun.cpp)

add_subdirectory(pybind11)
pybind11_add_module(main SHARED main.cpp)
# target_link_libraries(main libfun.a)
