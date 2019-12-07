cmake_minimum_required(VERSION 3.13)
project(k-on)

set(CMAKE_CXX_STANDARD 17)

find_library(CONCPP_LIB
        NAMES mysqlcppconn
        PATHS "${CONCPP_LIB_DIR}")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

set(SOURCE_FILES
        src/db_entities.cpp
        src/db_wrapper.cpp
        src/db_worker.cpp
        src/db_worker_recommendations.cpp
        src/recommendation_system.cpp
        src/db_recommendation_system.cpp
        )

include_directories(
        include
)

add_library(db_work_lib STATIC ${SOURCE_FILES})

add_executable(main src/main.cpp)
target_link_libraries(main db_work_lib ${CONCPP_LIB})

add_executable(tests tests/tests.cpp)
target_link_libraries(tests db_work_lib ${CONCPP_LIB} ${GTEST_LIBRARIES} Threads::Threads)
