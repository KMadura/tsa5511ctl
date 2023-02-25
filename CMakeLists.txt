cmake_minimum_required(VERSION 3.18)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

project(rpiTsa5511Control C)

set(CMAKE_C_STANDARD 11)

add_executable(tsa5511ctl main.c)
