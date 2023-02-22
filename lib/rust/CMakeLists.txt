project(elephant-seal-rs-cxx CXX)
cmake_minimum_required(VERSION 3.5)

corrosion_import_crate(MANIFEST_PATH Cargo.toml CRATES elephant-seal-rs FLAGS -vv)

find_package (Qt5 COMPONENTS Core)

set(CMAKE_AUTOMOC ON)

add_library(${PROJECT_NAME} STATIC
    glue/glue.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC .)
target_link_libraries(${PROJECT_NAME} elephant-seal-lib elephant-seal-rs)


