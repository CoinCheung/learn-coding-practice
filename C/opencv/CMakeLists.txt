cmake_minimum_required(VERSION 2.8.12)
project(example)

## pkg-config
# include_directories(./ /opt/opnecv/include/opencv4/)
# link_directories(/opt/opencv/lib64)
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(OPENCV REQUIRED opencv4)
#
# if (CMAKE_COMPILER_IS_GNUCXX)
#     set (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
#     message ("CMAKE_CXX_FLAGS is: ${CMAKE_CXX_FLAGS}")
# endif (CMAKE_COMPILER_IS_GNUCXX)
#
# add_executable(main main.cpp ConnectedDomain.cpp grayscale.cpp)
# target_link_libraries(main PRIVATE tcmalloc ${OPENCV_LIBRARIES})
# target_include_directories(main PRIVATE ${OPENCV_INCLUDE_DIRS})
# target_compile_options(main PRIVATE ${OPENCV_CFLAGS_OTHER})


### find package
set (OpenCV_DIR /opt/opnecv/lib/cmake/opencv4/)
find_package (OpenCV REQUIRED)

add_executable(main main.cpp ConnectedDomain.cpp grayscale.cpp)
target_link_libraries(main PRIVATE tcmalloc ${OpenCV_LIBS})
target_include_directories(main PRIVATE ${OpenCV_INCLUDE_DIR})
