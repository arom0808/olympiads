cmake_minimum_required(VERSION 3.29)
project(K_C__)

set(CMAKE_CXX_STANDARD 20)

add_executable(K_C__ main.cpp)
target_compile_definitions(K_C__ PRIVATE LOCAL)