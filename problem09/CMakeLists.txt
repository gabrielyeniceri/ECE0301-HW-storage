cmake_minimum_required(VERSION 3.5)
project(problem09)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test_image test_image.cpp bitmap.hpp Image.hpp Image.cpp catch.hpp)

enable_testing()

add_test(test_image test_image)

add_custom_target(submission COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/problem09.zip" --format=zip
       test_image.cpp Image.hpp Image.cpp
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})  




