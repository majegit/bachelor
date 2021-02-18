# cmake_minimum_required(VERSION <specify CMake version here>)
project(chboecaspnBachelor C)

set(CMAKE_C_STANDARD 99)

add_executable(chboecaspnBachelor main.c FlexBison/Tree.c)