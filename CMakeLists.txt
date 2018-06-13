cmake_minimum_required(VERSION 3.10)
project(serial_port_wrapper)

set(CMAKE_CXX_STANDARD 11)

add_executable(serial_port_wrapper main.cpp serial-port-wrapper.hpp serial-port-wrapper.cpp)