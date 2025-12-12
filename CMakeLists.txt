cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(uart)

target_sources(app PRIVATE
    src/main.cpp
    src/uart.cpp
    src/frames.cpp
    src/sensors.cpp)

target_include_directories(app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)


