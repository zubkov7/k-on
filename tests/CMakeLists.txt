cmake_minimum_required(VERSION 3.14)
project(k_on_tests CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-std=c++0x")

find_package(GTest REQUIRED)
find_package(Threads)

find_library(CONCPP_LIB NAMES mysqlcppconn  PATHS "${CONCPP_LIB_DIR}")

include_directories(../project/include)
include_directories(${GTEST_INCLUDE_DIRS})

set (SRC_FILES
        ./test_user.cpp
        ../project/src/db_worker_user.cpp
        ../project/src/db_wrapper.cpp
        ../project/src/user_system.cpp
        ../project/src/db_entities.cpp)

add_executable(k_on_tests ${SRC_FILES})
target_link_libraries(k_on_tests ${GTEST_BOTH_LIBRARIES} gtest ${CONCPP_LIB} pthread)
