cmake_minimum_required(VERSION 3.29)
project(threadpool)

set(CMAKE_CXX_STANDARD 20)

add_executable(threadpool main.cpp thread_pool.cpp)
