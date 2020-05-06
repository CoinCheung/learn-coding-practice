cmake_minimum_required(VERSION 2.8.12)
project(example)


if (CMAKE_COMPILER_IS_GNUCXX)
    set (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
    message ("CMAKE_CXX_FLAGS is: ${CMAKE_CXX_FLAGS}")
endif (CMAKE_COMPILER_IS_GNUCXX)

add_executable(main io.cpp)
target_link_libraries(main PRIVATE tcmalloc)

