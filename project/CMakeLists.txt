cmake_minimum_required(VERSION 3.14)
project(k-on CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-std=c++0x")

find_package (Threads REQUIRED)
find_package(Boost 1.71.0 REQUIRED)
find_package(OpenSSL REQUIRED)
find_library(CONCPP_LIB NAMES mysqlcppconn PATHS "${CONCPP_LIB_DIR}" REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(./include)

set(USER_SERVER_SRC
        src/main_user_server.cpp
        src/tcp_server.cpp
        src/tcp_server_user.cpp
        src/user_system.cpp
        src/db_worker_user.cpp
        src/db_wrapper.cpp
        src/json.cpp
        src/utils.cpp)

add_executable(user_server ${USER_SERVER_SRC})
target_link_libraries(user_server ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${CONCPP_LIB} OpenSSL::Crypto)

add_executable(recommendation_server ./src/main_recommendation_server.cpp)
target_link_libraries(recommendation_server ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

set(WEB_SERVER_SRC
        src/main_web_server.cpp
        src/client.cpp
        src/web_server.cpp
        src/tcp_client.cpp
        src/manager.cpp
        src/url_parser.cpp
        src/json.cpp)

add_executable(web_server ${WEB_SERVER_SRC})
target_link_libraries(web_server ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
