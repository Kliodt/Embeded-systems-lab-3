cmake_minimum_required(VERSION 3.10)

project(EmbededLab2 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

include_directories(
    ${PROJECT_SOURCE_DIR}/include 
    ${PROJECT_SOURCE_DIR}/libs
)

file(GLOB SOURCES 
    ${PROJECT_SOURCE_DIR}/src/*.c
    ${PROJECT_SOURCE_DIR}/src/game/*.c
    # add other paths here
)

add_library(cthreads ${CMAKE_SOURCE_DIR}/libs/CThreads/cthreads.c)

set(EXECUTABLE_NAME ${PROJECT_NAME})

add_executable(${EXECUTABLE_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE cthreads)