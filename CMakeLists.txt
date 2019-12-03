cmake_minimum_required(VERSION 3.5)
project(k-on)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.71.0 COMPONENTS program_options REQUIRED)



set(LIB_SOURCE_FILES
        project/server.cpp
        )

add_library(study_std_lib STATIC ${LIB_SOURCE_FILES})



add_subdirectory(Gtest/googletest-master)
include_directories(Gtest/googletest-master/googletest/include Gtest/googletest-master/googletest/src )

add_executable(Gtest_test project/test_server.cpp)


target_link_libraries(Gtest_test study_std_lib)
target_link_libraries(Gtest_test gtest gtest_main)
target_link_libraries(Gtest_test Boost::program_options)
