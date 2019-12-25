cmake_minimum_required(VERSION 3.14)
project(k-on CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-std=c++0x")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
find_package(Boost 1.71.0 REQUIRED)
find_package(OpenSSL REQUIRED)
find_library(CONCPP_LIB NAMES mysqlcppconn PATHS "${CONCPP_LIB_DIR}" REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(../project/include)

set(RECOMMENDATION_SYSTEM_SRC
        ../project/src/db_worker_recommendations.cpp
        ../project/src/db_worker.cpp
        ../project/src/recommendation_system.cpp
        ../project/src/db_recommendation_system.cpp
        ../project/src/tcp_server.cpp
        ../project/src/tcp_server_recommendations.cpp
        ../project/src/json.cpp
        ../project/src/db_entities.cpp
        ../project/src/db_wrapper.cpp
        test_recommendation_system.cpp)

add_executable(tests ${RECOMMENDATION_SYSTEM_SRC})
target_link_libraries(tests ${GTEST_LIBRARIES} Threads::Threads ${CONCPP_LIB})
