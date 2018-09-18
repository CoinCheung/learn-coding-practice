cmake_minimum_required(VERSION 2.8.12)
project(example)

add_library(play SHARED play.cpp)

include_directories(./)
link_directories(./)

# add_executable(main main.cpp fun.cpp)
add_library(prt SHARED main.cpp fun.cpp)
target_link_libraries(prt play)
