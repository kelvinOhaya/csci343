cmake_minimum_required(VERSION 4.0)
project(Sequence)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(Sequence
        Sequence.cpp
        Sequence.h)
