cmake_minimum_required(VERSION 3.28)
project(D_C__)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_DEBUG")

add_executable(D_C__ main.cpp)
