cmake_minimum_required(VERSION 2.8.12)
project(example)

include_directories(../)
link_directories(./)

if (CMAKE_COMPILER_IS_GNUCXX)
    set (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
    message ("CMAKE_CXX_FLAGS is: ${CMAKE_CXX_FLAGS}")
endif (CMAKE_COMPILER_IS_GNUCXX)

# add_executable(main PCA.cpp)
add_executable(main play.cpp)
target_link_libraries(main PRIVATE tcmalloc glog)
target_include_directories(main PRIVATE ./)
target_compile_options(main PRIVATE -O2)
