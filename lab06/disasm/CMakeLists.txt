cmake_minimum_required(VERSION 3.18)
project(disasm C)

set(CMAKE_C_STANDARD 99)

add_executable(disasm main.c
        line.c
        line.h
        min.c
        min.h
        max3.c
        max3.h
        sum.c
        sum.h)
