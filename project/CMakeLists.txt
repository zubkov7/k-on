cmake_minimum_required(VERSION 3.13)
project(k-on)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        include
)

add_executable(main src/main.cpp include)
