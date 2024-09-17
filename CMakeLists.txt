cmake_minimum_required(VERSION 3.10)

# Project name
project(csv-reader VERSION 1.0)

# Setting the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#include directories for header files
include_directories(include)

#source files
file(GLOB SOURCES "src/*.c")

# Executables
add_executable(App src/main.c)

# Libraries
target_link_libraries(App m)
