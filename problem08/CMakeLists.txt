cmake_minimum_required(VERSION 3.5)
project(problem08)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test_signal test_signal.cpp Signal.hpp Signal.cpp catch.hpp)

enable_testing()

add_test(test-signal test_signal)

add_custom_target(submission COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/problem08.zip" --format=zip
       test_signal.cpp Signal.hpp Signal.cpp
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})  




