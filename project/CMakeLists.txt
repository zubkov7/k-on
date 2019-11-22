cmake_minimum_required(VERSION 3.9)
project(k-on CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-std=c++0x")

SET(SRC_FILES
        src/user.cpp
        src/db_worker_user.cpp)

include_directories(./include)

add_executable(k-on ${SRC_FILES})