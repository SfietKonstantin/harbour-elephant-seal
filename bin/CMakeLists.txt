project(harbour-elephant-seal CXX)
cmake_minimum_required(VERSION 3.5)

find_package (Qt5 COMPONENTS Core Network Qml Gui Quick REQUIRED)

include(FindPkgConfig)
pkg_search_module(SAILFISH sailfishapp REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${PROJECT_NAME} main.cpp)
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)
target_include_directories(${PROJECT_NAME} PRIVATE
    $<BUILD_INTERFACE:
    ${SAILFISH_INCLUDE_DIRS}
>)
target_link_libraries(${PROJECT_NAME}
    Qt5::Quick
    ${SAILFISH_LDFLAGS}
    elephant-seal-lib
    elephant-seal-rs-cxx
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
install(DIRECTORY qml
    DESTINATION share/harbour-elephant-seal
)
install(DIRECTORY translations
    DESTINATION share/harbour-elephant-seal
    FILES_MATCHING PATTERN "*.qm"
)
install(FILES harbour-elephant-seal.desktop
    DESTINATION share/applications
)
install(FILES icons/86x86/harbour-elephant-seal.png
    DESTINATION share/icons/hicolor/86x86/apps
)
install(FILES icons/108x108/harbour-elephant-seal.png
    DESTINATION share/icons/hicolor/108x108/apps
)
install(FILES icons/128x128/harbour-elephant-seal.png
    DESTINATION share/icons/hicolor/128x128/apps
)
install(FILES icons/172x172/harbour-elephant-seal.png
    DESTINATION share/icons/hicolor/172x172/apps
)

# Get the other files reachable from the project tree in Qt Creator
FILE(GLOB TsFiles "translations/*.ts")
add_custom_target(otherfiles SOURCES
    harbour-elephant-seal.desktop

    qml/harbour-elephant-seal.qml
    qml/cover/CoverPage.qml
    qml/pages/FirstPage.qml
    qml/pages/SecondPage.qml
    qml/pages/LoginPage.qml
    qml/pages/LoginCodePage.qml

    ${TsFiles}
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

