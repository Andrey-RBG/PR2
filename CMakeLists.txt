cmake_minimum_required(VERSION 3.10)
project(PR2 C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(PR2 
    src/main.c 
    src/users.c 
    src/processes.c 
    src/logger.c 
    src/errors.c
)