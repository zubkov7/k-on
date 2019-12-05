cmake_minimum_required(VERSION 3.14)
project(k-on CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-std=c++0x")

find_package (Threads REQUIRED)
find_package(Boost 1.71.0 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(./include)

add_executable(user_server ./src/main_user_server.cpp src/TcpServer.cpp ./src/Client.cpp ./src/Tcp_server_user.cpp)
target_link_libraries(user_server ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(recommendation_server ./src/main_recommendation_server.cpp)
target_link_libraries(recommendation_server ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(web_server ./src/Web_server.cpp src/TcpClient.cpp)
target_link_libraries(web_server ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
