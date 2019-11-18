cmake_minimum_required(VERSION 3.13)
project(k-on)

set(CMAKE_CXX_STANDARD 17)

find_library(CONCPP_LIB
        NAMES mysqlcppconn
        PATHS "${CONCPP_LIB_DIR}")

set(SOURCE_FILES
        src/db_wrapper.cpp)

include_directories(
        include
)

add_library(db_work_lib STATIC ${SOURCE_FILES})

add_executable(main src/main.cpp)
target_link_libraries(main db_work_lib ${CONCPP_LIB})
