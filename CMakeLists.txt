cmake_minimum_required(VERSION 3.25.2)

project(Modern_CPP)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -v")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.82.0)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(Polynomial main.cpp BasisFunctionsSets.h SparseFunctionStruct.h SparseFunction.h Polynomial.h Timer.h)
    target_link_libraries(Polynomial ${Boost_LIBRARIES})
endif()



