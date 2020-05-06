cmake_minimum_required(VERSION 2.8.12)
project(example)

include_directories(./)
link_directories(./)

if (CMAKE_COMPILER_IS_GNUCXX)
    set (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
    message ("CMAKE_CXX_FLAGS is: ${CMAKE_CXX_FLAGS}")
endif (CMAKE_COMPILER_IS_GNUCXX)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE )
target_compile_options(main PRIVATE -O2)

