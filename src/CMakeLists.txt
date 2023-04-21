cmake_minimum_required(VERSION 3.25)
project(dictionary_program)

set(CMAKE_CXX_STANDARD 11)

add_executable(dictionary_program main.cpp dictionary.cpp dictionary.h)
