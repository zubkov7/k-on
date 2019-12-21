cmake_minimum_required(VERSION 3.13)
project(k-on)

set(CMAKE_CXX_STANDARD 17)

find_library(CONCPP_LIB NAMES mysqlcppconn PATHS "${CONCPP_LIB_DIR}")
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

set(RECOMMENDATION_SYSTEM_SRC
        project/src/db_entities.cpp
        project/src/db_wrapper.cpp
        project/src/db_worker.cpp
        project/src/db_worker_recommendations.cpp
        project/src/recommendation_system.cpp
        project/src/db_recommendation_system.cpp
        project/src/tcp_server.cpp
        project/src/tcp_server_recommendations.cpp
        project/src/json.cpp
        )

include_directories(${Boost_INCLUDE_DIRS})
include_directories(project/include)

add_executable(main project/src/main.cpp)
target_link_libraries(main ${RECOMMENDATION_SYSTEM_SRC} ${CONCPP_LIB} ${Boost_LIBRARIES})

add_executable(tests tests/tests.cpp)
target_link_libraries(tests ${RECOMMENDATION_SYSTEM_SRC} ${CONCPP_LIB} ${GTEST_LIBRARIES} Threads::Threads)
