cmake_minimum_required(VERSION 3.13)
project(k-on)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.71.0 REQUIRED)
find_library(CONCPP_LIB NAMES mysqlcppconn PATHS "${CONCPP_LIB_DIR}")
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(RECOMMENDATION_SYSTEM_SRC
        src/db_entities.cpp
        src/db_wrapper.cpp
        src/db_worker.cpp
        src/db_worker_recommendations.cpp
        src/recommendation_system.cpp
        src/db_recommendation_system.cpp
        src/tcp_server.cpp
        src/tcp_server_recommendations.cpp
        src/json.cpp
        )

include_directories(${Boost_INCLUDE_DIRS})
include_directories(project/include)

add_executable(main src/main.cpp)
target_link_libraries(main ${RECOMMENDATION_SYSTEM_SRC} ${CONCPP_LIB} ${Boost_LIBRARIES})

add_executable(tests ../tests/tests.cpp)
target_link_libraries(tests ${RECOMMENDATION_SYSTEM_SRC} ${CONCPP_LIB} ${GTEST_LIBRARIES} Threads::Threads)
