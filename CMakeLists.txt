cmake_minimum_required(VERSION 3.5)
project(k-on)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.71.0 COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(project/include)

set(LIB_SOURCE_FILES
        project/src/web_server.cpp
        project/src/client.cpp
        )

add_library(study_std_lib STATIC ${LIB_SOURCE_FILES})

add_subdirectory(Gtest/googletest-master)
include_directories(Gtest/googletest-master/googletest/include Gtest/googletest-master/googletest/src )

add_executable(Web_server project/src/main_web_server.cpp project/src/web_server.cpp project/src/client.cpp)

target_link_libraries(Web_server gtest gtest_main study_std_lib Boost::program_options)


