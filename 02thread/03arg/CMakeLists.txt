cmake_minimum_required(VERSION 3.2)
project(03arg C)

set(CMAKE_C_STANDARD 11)

add_executable(03arg main.c)

target_link_libraries(03arg m)

