project(harbour-elephant-seal)
cmake_minimum_required(VERSION 3.5)

add_subdirectory(cmake/corrosion)
add_subdirectory(lib)

# Allows developing in standard Linux without SFOS SDK
include(FindPkgConfig)
pkg_search_module(SAILFISH sailfishapp)

if ("${SAILFISH_FOUND}")

message("Building for Sailfish OS")

add_subdirectory(bin)

add_custom_target(distfiles
    SOURCES
    rpm/harbour-elephant-seal.changes.in
    rpm/harbour-elephant-seal.changes.run.in
    rpm/harbour-elephant-seal.spec
    rpm/harbour-elephant-seal.yaml
)

# Tell Qt Creator where the application executable(s) would be located on the
# device.
#
# It is not necessary to list other deployables than executables (runtime
# targets) here. The deployment process of Sailfish OS projects is opaque to
# Qt Creator and the information contained in QtCreatorDeployment.txt is only
# used to locate the executable associated with the active run configuration
# on the device in order to run it.
#
# Search the Qt Creator Manual to learn about the QtCreatorDeployment.txt file
# format.
file(WRITE "${CMAKE_BINARY_DIR}/QtCreatorDeployment.txt"
    "${CMAKE_INSTALL_PREFIX}
${CMAKE_BINARY_DIR}/harbour-elephant-seal:bin
")

else()
message("Building without Sailfish OS support")
endif()
