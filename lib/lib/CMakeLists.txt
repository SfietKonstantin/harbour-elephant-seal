project(elephant-seal-lib CXX)
cmake_minimum_required(VERSION 3.5)

find_package (Qt5 COMPONENTS Core)

set(CMAKE_AUTOMOC ON)

add_library(${PROJECT_NAME} STATIC
    lib/hooks.h
    lib/lib.h
    lib/lib.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC .)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
