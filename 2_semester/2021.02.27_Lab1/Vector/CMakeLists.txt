cmake_minimum_required(VERSION 3.17)
project(Vector)

set(CMAKE_CXX_STANDARD 20)

add_executable(Vector main.cpp Vector.cpp Vector.h VectorIterator.h)