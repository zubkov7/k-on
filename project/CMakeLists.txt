cmake_minimum_required(VERSION 3.14)
project(k-on CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-std=c++0x")

find_package (Threads REQUIRED)
find_package(Boost 1.71.0 REQUIRED)

find_library(CONCPP_LIB NAMES mysqlcppconn  PATHS "${CONCPP_LIB_DIR}")

include_directories(${Boost_INCLUDE_DIRS})
include_directories(./include)

set(USER_SERVER_SRC
        src/main_user_server.cpp
        src/tcp_server.cpp
        src/tcp_server_user.cpp
        src/user.cpp
        src/db_worker_user.cpp
        src/db_wrapper.cpp)

add_executable(user_server ${USER_SERVER_SRC})
target_link_libraries(user_server ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${CONCPP_LIB})

add_executable(recommendation_server ./src/main_recommendation_server.cpp)
target_link_libraries(recommendation_server ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(web_server src/main_web_server.cpp src/tcp_client.cpp)
target_link_libraries(web_server ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
