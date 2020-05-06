cmake_minimum_required(VERSION 2.8.12)
project(example)

include_directories(./)
link_directories(./)

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Os -g ${CMAKE_CXX_FLAGS}")
    message("CMAKE_COMPILER_IS_GNUCXX is True")
    message("option is: ${CMAKE_CXX_FLAGS}")
endif (CMAKE_COMPILER_IS_GNUCXX)

add_executable(main try.cpp)
target_link_libraries(main PRIVATE tcmalloc)

add_library(fun SHARED func.cpp)
    set_target_properties(fun
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib"
    )
