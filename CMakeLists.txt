cmake_minimum_required(VERSION 3.26)
project(SSEM)

set(CMAKE_CXX_STANDARD 17)

add_executable(SSEM main.cpp
        Processor.cpp
        Processor.h
        Util.cpp
        Util.h
        Store.cpp
        Store.h
)
