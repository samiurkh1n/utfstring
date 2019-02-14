cmake_minimum_required(VERSION 3.3)

set(ProjectName utfstring)
project(${ProjectName} CXX)

add_library(utfstr SHARED utfstring.cc)

add_executable(utfstr_test utfstring_test.cc)

include(GenerateExportHeader)
generate_export_header(utfstr)

set(CMAKE_CXX_STANDARD 11)

if (MSVC)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
  target_compile_options(utfstr PUBLIC /EHsc /Wall /c)
  target_compile_definitions(utfstr PUBLIC WIN_EXPORT)
  target_compile_options(utfstr_test PUBLIC /EHsc /Wall)
else()
  set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")
  set(CMAKE_CXX_FLAGS_RELEASE "-Wall -pedantic -O2")
endif() 

target_link_libraries(utfstr_test PUBLIC utfstr)
