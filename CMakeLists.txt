cmake_minimum_required(VERSION 3.16)
project(AmiiboTap)

if (CMAKE_BUILD_TYPE STREQUAL Release)
    ADD_DEFINITIONS(-DRELEASE)
endif ()

# subproject for amiitool
add_subdirectory(lib/amiitool)

set(CMAKE_CXX_STANDARD 17)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets SerialPort)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::SerialPort)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (CMAKE_HOST_WIN32)
    find_package(libnfc)
    add_definitions(${LIBNFC_DEFINITIONS})
    include_directories(${LIBNFC_INCLUDE_DIRS})
    link_directories(${LIBNFC_LIBRARY_DIRS})
elseif (CMAKE_HOST_APPLE)
    find_path(LibNFC_FIND nfc.h "/usr/local/Cellar/libnfc/1.8.0/include/nfc" NO_SYSTEM_ENVIRONMENT_PATH)
    if (LibNFC_FIND)
        include_directories(/usr/local/Cellar/libnfc/1.8.0/include)
        link_directories(/usr/local/Cellar/libnfc/1.8.0/lib)
    else ()
        message(FATAL_ERROR "LibNFC not found, please use 'brew install libnfc' or macport to download this required library.")
    endif ()
else ()
    message("Use system libnfc")
endif ()

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

include_directories(
        lib/amiitool/amiitool-src/include
        lib/ColorCout/includes
        )

add_executable(${PROJECT_NAME}
        src/amiitool.cpp
        src/amiibo.cpp
        src/nfchandler.cpp
        src/amibo-tap.cpp
        )
target_link_libraries(${PROJECT_NAME} amiibo ${REQUIRED_LIBS_QUALIFIED} nfc)

add_executable(uint8_t_test test/uint8_t.cpp)
target_link_libraries(uint8_t_test ${REQUIRED_LIBS_QUALIFIED})

if (WIN32)
    set(DEBUG_SUFFIX)
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB ${REQUIRED_LIBS})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt${QT_VERSION}${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
