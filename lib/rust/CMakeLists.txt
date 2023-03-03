project(elephant-seal-rs-cxx CXX)
cmake_minimum_required(VERSION 3.5)

include(FindPkgConfig)

find_package(Qt5 COMPONENTS Core Gui REQUIRED)
find_package(OpenSSL REQUIRED)
pkg_search_module(SAILFISH sailfishapp)

corrosion_import_crate(MANIFEST_PATH Cargo.toml CRATES elephant-seal-ffi FLAGS -vv -j1)

if ("${SAILFISH_FOUND}")
    # We need to help Rust with OpenSSL and cross-compilation
    # And qmake detection is unsupported with old Qt
    corrosion_set_env_vars(elephant-seal-ffi
        "CMAKE_CURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}"
        "QMAKE=qmake"
        "OPENSSL_DIR=/usr"
        "OPENSSL_LIB_DIR=/usr/lib"
        "OPENSSL_INCLUDE_DIR=/usr/include"
        "ARMV7_UNKNOWN_LINUX_GNUEABIHF_OPENSSL_DIR=/usr"
        "ARMV7_UNKNOWN_LINUX_GNUEABIHF_OPENSSL_LIB_DIR=/usr/lib"
        "ARMV7_UNKNOWN_LINUX_GNUEABIHF_OPENSSL_INCLUDE_DIR=/usr/include"
        "AARCH64_UNKNOWN_LINUX_GNU_OPENSSL_DIR=/usr"
        "AARCH64_UNKNOWN_LINUX_GNU_OPENSSL_LIB_DIR=/usr/lib64"
        "AARCH64_UNKNOWN_LINUX_GNU_OPENSSL_INCLUDE_DIR=/usr/include"
    )
else()
    get_target_property(QMAKE Qt::qmake IMPORTED_LOCATION)
    corrosion_set_env_vars(elephant-seal-ffi
        "CMAKE_CURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}"
        "QMAKE=${QMAKE}"
    )
endif()

set(CMAKE_AUTOMOC ON)

include_directories(. "${CMAKE_CURRENT_BINARY_DIR}/cxxbridge/include")

add_library(${PROJECT_NAME} STATIC
    glue/glue.h
    glue/glue.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC .)
target_link_libraries(${PROJECT_NAME} elephant-seal-lib elephant-seal-ffi Qt5::Core Qt5::Gui ${OPENSSL_LIBRARIES})
