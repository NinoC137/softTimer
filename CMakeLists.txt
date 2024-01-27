cmake_minimum_required(VERSION 3.25)
project(SoftTimer C)

set(CMAKE_C_STANDARD 11)

add_executable(SoftTimer main.c softTimer.c)
