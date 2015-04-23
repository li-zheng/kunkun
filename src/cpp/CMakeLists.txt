cmake_minimum_required (VERSION 2.8)
project (libTest)

set(CMAKE_CXX_FLAGS "-Wall")

add_subdirectory(gtest-1.7.0)
add_subdirectory(test)
