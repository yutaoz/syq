# CMake minimum required version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(syq VERSION 0.1)

# Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add the executable
add_executable(syq src/main.c src/query.c src/services/winutil.c)
