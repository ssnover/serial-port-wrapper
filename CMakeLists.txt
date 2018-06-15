cmake_minimum_required(VERSION 3.10)
project(serial_port_wrapper)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        serial-port-wrapper.cpp)
set(INCLUDE_FILES
        serial-port-wrapper.hpp
        serial-port-wrapper-intf.hpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -funsigned-char")

add_executable(serial_port_wrapper_test main.cpp ${SOURCE_FILES} ${INCLUDE_FILES})

add_library(serial_port_wrapper ${SOURCE_FILES} ${INCLUDE_FILES})