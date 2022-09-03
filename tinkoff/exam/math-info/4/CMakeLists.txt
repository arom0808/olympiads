cmake_minimum_required(VERSION 3.23)
project(4)

find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(4 main.cpp)
#
#target_link_libraries(4 Threads::Threads)
#set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 -lpthread ${CMAKE_CSS_STANDARD_LIBRARIES}")
