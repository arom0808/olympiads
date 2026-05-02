cmake_minimum_required(VERSION 3.29)
project(H_C__)

set(CMAKE_CXX_STANDARD 20)

add_executable(H_C__ main.cpp)
target_compile_definitions(H_C__ PRIVATE LOCAL)
