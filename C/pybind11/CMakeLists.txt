cmake_minimum_required(VERSION 2.8.12)
project(example)

set(install_dir ..)

add_library(play SHARED play.cpp)
include_directories(./)
link_directories(./)

add_subdirectory(pybind11)
pybind11_add_module(main SHARED main.cpp fun.cpp)
target_link_libraries(main PRIVATE play tcmalloc)


set_target_properties( main play
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
)
