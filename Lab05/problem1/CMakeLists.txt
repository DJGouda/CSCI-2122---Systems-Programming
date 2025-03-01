cmake_minimum_required(VERSION 3.18)
project(problem1 C)

set(CMAKE_C_STANDARD 99)

add_executable(problem1 main.c
        linked_list.h
        linked_list.c)
