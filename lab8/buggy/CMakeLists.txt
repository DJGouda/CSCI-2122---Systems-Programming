cmake_minimum_required(VERSION 3.18)
project(buggy C)

set(CMAKE_C_STANDARD 99)

add_executable(buggy main.c
        str_list.c)
