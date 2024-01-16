cmake_minimum_required(VERSION 3.24)
project(SubwaySurfers)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall)

add_executable(SubwaySurfers src/main.c)

if(CMAKE_HOST_SYSTEM MATCHES "Linux")
    target_link_libraries(SubwaySurfers pthread m dl)
endif()