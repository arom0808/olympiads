cmake_minimum_required(VERSION 3.29)
project(A_C__)

set(CMAKE_CXX_STANDARD 20)

add_executable(A_C__ main.cpp)
target_compile_definitions(A_C__ PRIVATE LOCAL)