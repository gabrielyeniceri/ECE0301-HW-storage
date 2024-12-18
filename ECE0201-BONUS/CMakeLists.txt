cmake_minimum_required(VERSION 3.5)
project(ECE0201-BONUS)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BONUS BONUS.cpp)

enable_testing()

add_test(test-ECE0201-BONUS BONUS)

