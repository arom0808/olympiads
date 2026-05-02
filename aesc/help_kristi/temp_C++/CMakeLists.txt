cmake_minimum_required(VERSION 3.29)
project(temp_C__)

set(CMAKE_CXX_STANDARD 20)

add_executable(temp_C__ main.cpp)
target_compile_definitions(temp_C__ PRIVATE LOCAL)