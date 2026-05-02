cmake_minimum_required(VERSION 3.29)
project(G_C__)

set(CMAKE_CXX_STANDARD 20)

add_executable(G_C__ main.cpp)
target_compile_definitions(G_C__ PRIVATE LOCAL)