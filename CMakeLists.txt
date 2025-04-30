cmake_minimum_required(VERSION 3.10)
project(WojnaGra)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(wojna tp_projekt2.cpp)

add_executable(tests test_tp_projekt2.cpp)