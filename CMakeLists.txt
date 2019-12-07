cmake_minimum_required(VERSION 3.5)
project(k-on)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.71.0 COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(project/server.h)

set(LIB_SOURCE_FILES
        project/server.cpp
        )

add_library(study_std_lib STATIC ${LIB_SOURCE_FILES})

add_subdirectory(Gtest/googletest-master)
include_directories(Gtest/googletest-master/googletest/include Gtest/googletest-master/googletest/src )

add_executable(Web_server project/main_web_server.cpp project/server.cpp)

target_link_libraries(Web_server gtest gtest_main study_std_lib Boost::program_options)


