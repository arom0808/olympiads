cmake_minimum_required(VERSION 3.29)
project(I_C__)

set(CMAKE_CXX_STANDARD 20)

add_executable(I_C__ main.cpp)
target_compile_definitions(I_C__ PRIVATE LOCAL)
