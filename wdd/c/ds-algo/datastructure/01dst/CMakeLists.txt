cmake_minimum_required(VERSION 3.2)
project(01dst C)

set(CMAKE_C_STANDARD 11)

add_executable(01dst main.c
        dst.h
        dst.c
        student.h
        student.c)
