cmake_minimum_required(VERSION 3.17)
project(Hashtable C)

set(CMAKE_C_STANDARD 11)
include_directories(include/)
file(GLOB src src/*)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -O0")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=undefined")

add_executable(Hashtable main.c ${src})

add_executable(test test/test.c ${src})

add_executable(benchmark test/benchmark.c ${src})

add_executable(unit_test test/unit_tests.c ${src})

