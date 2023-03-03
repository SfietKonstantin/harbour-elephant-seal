project(elephant-seal-lib CXX)
cmake_minimum_required(VERSION 3.5)

find_package (Qt5 COMPONENTS Core Gui)

set(CMAKE_AUTOMOC ON)

add_library(${PROJECT_NAME} STATIC
    lib/errors.h
    lib/errors.cpp
    lib/eventbus.h
    lib/eventbus.cpp
    lib/mastodon.h
    lib/mastodon.cpp
    lib/mastodonhook.h
    lib/mastodonhook.cpp
    lib/mastodonlogin.h
    lib/mastodonlogin.cpp
    lib/task.h
    lib/task.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC .)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui)
