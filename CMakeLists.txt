cmake_minimum_required(VERSION 3.3)

set(ProjectName utfstring)
project(${ProjectName} CXX)

add_library(utfstr SHARED utfstring.cc)

add_executable(utfstr_test utfstring_test.cc)

set(CMAKE_CXX_STANDARD 11)

if (MSVC)
  include(GenerateExportHeader)
  GENERATE_EXPORT_HEADER(utfstr
             BASE_NAME UTFSTF
             EXPORT_MACRO_NAME UTFSTR_EXPORT
             EXPORT_FILE_NAME UTFSTR_EXPORTS.h
             STATIC_DEFINE UTFSTR_EXPORTS_BUILT_AS_STATIC)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
  target_compile_options(utfstr PUBLIC /Zi /EHsc /Wall /c)
  target_compile_definitions(utfstr PUBLIC WIN_EXPORT)
  target_compile_options(utfstr_test PUBLIC /Zi /EHsc /Wall)
else()
  set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")
  set(CMAKE_CXX_FLAGS_RELEASE "-Wall -pedantic -O2")
endif() 

target_link_libraries(utfstr_test PUBLIC utfstr)
