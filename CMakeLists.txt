cmake_minimum_required(VERSION 3.24)
project(ConsoleRunners)

set(CMAKE_C_STANDARD 11)

add_executable(ConsoleRunners src/main.c)

if(CMAKE_HOST_SYSTEM MATCHES "Linux")
    target_link_libraries(ConsoleRunners m)
endif()
