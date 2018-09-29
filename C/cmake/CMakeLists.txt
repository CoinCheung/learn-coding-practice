cmake_minimum_required (VERSION 2.8.12)
project (example)

set (CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/..)
set (SRCS main.cpp fun.cpp)

add_library (play SHARED play.cpp)

include_directories (./)
link_directories (./)

add_executable (main ${SRCS})
# add_library(prt SHARED main.cpp fun.cpp)
target_link_libraries (main play)


install (TARGETS main play
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/lib
        ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)

set_target_properties (main play
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)
