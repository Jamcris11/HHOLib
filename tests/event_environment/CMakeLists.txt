cmake_minimum_required(VERSION 3.17)

project(event_environment)

add_executable(${CMAKE_PROJECT_NAME}
        src/main.cpp
)

include_directories(include/)

message(${CMAKE_CXX_COMPILER_ID} " " ${CMAKE_CXX_COMPILER_VERSION})

set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)