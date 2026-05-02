cmake_minimum_required(VERSION 3.29)
project(B_C__)

set(CMAKE_CXX_STANDARD 20)

add_executable(B_C__ main.cpp)
target_compile_definitions(B_C__ PRIVATE LOCAL)