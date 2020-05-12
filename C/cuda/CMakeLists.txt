CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(cuda)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CUDA_NVCC_FLAGS "-std=c++11 -arch=sm_60")
set(CUDA_NVCC_FLAGS_DEBUG "-G -O0")
set(CUDA_NVCC_FLAGS_RELEASE "-O2")

message (${CMAKE_BUILD_TYPE})


# link_directories(/usr/local/cuda/lib64)

find_package(CUDA REQUIRED)

##TODO: different of add_executable and cuda_add_executable
cuda_add_executable(main main.cu)
target_include_directories(
    main PUBLIC ${CUDA_INCLUDE_DIRS} ${CUDNN_INCLUDE_DIRS})
target_link_libraries(
    main ${CUDA_LIBRARIES})

# cuda_add_library(demo SHARED main.cu)
# target_include_directories(
#     demo PUBLIC ${CUDA_INCLUDE_DIRS} ${CUDNN_INCLUDE_DIRS})
# target_link_libraries(
#     demo ${CUDA_LIBRARIES})
