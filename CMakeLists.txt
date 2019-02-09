cmake_minimum_required(VERSION 3.3)

set(ProjectName utfstring)
project(${ProjectName} CXX)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -pedantic -O2")

add_library(utfstr SHARED utfstring.cc)

add_executable(utfstr_test utfstring_test.cc)

target_link_libraries(utfstr_test PUBLIC utfstr)
