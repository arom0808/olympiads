cmake_minimum_required(VERSION 3.29)
project(theory_games_C__)

set(CMAKE_CXX_STANDARD 20)

add_executable(theory_games_C__ main.cpp)
target_compile_definitions(theory_games_C__ PRIVATE LOCAL)