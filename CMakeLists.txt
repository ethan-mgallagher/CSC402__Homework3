cmake_minimum_required(VERSION 3.6)
project(homework3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Patient.cpp Patient.h Hospital.cpp Hospital.h Logger.cpp Logger.h Tokens.h)
add_executable(homework3 ${SOURCE_FILES})