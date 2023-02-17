project(elephant-seal-rs-cxx CXX)
cmake_minimum_required(VERSION 3.5)

find_package (Qt5 COMPONENTS Core)

set(CMAKE_AUTOMOC ON)

add_library(${PROJECT_NAME} STATIC
    shim.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC .)
target_link_libraries(${PROJECT_NAME} elephant-seal-lib)
