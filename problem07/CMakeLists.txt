cmake_minimum_required(VERSION 3.5)
project(problem07)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(problem07-tests problem07_tests.cpp Database.hpp Database.cpp catch.hpp)

enable_testing()

add_test(test-problem07 problem07-tests)

add_custom_target(submission COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/problem07.zip" --format=zip
       problem07_tests.cpp Database.hpp Database.cpp
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})  




