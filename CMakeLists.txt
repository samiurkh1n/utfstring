cmake_minimum_required(VERSION 3.3)

set(ProjectName utfstring)
project(${ProjectName} CXX)

set(CMAKE_CXX_STANDARD 11)

add_library(utfstr SHARED utfstring.cc)

add_executable(utfstr_test utfstring_test.cc)

target_link_libraries(utfstr_test PUBLIC utfstr)
