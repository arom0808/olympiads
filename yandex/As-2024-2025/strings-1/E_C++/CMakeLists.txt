cmake_minimum_required(VERSION 3.29)
project(E_C__)

set(CMAKE_CXX_STANDARD 20)

add_executable(E_C__ main.cpp)
target_compile_definitions(E_C__ PRIVATE LOCAL)