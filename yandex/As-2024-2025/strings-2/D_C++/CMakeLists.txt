cmake_minimum_required(VERSION 3.29)
project(D_C__)

set(CMAKE_CXX_STANDARD 20)

add_executable(D_C__ main.cpp)
target_compile_definitions(D_C__ PRIVATE LOCAL)