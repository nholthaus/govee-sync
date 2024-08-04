cmake_minimum_required(VERSION 3.21)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${DIR} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    set(Qt6_DIR $ENV{Qt6_DIR})
    list(APPEND CMAKE_PREFIX_PATH ${Qt6_DIR})
    message(STATUS "Qt6 DIR: ${Qt6_DIR}")
endif (WIN32)

find_package(Qt6 6.2.4 REQUIRED COMPONENTS Core Widgets Network)
if (Qt6Core_VERSION VERSION_GREATER_EQUAL 6.3.0)
    qt_standard_project_setup()
else ()
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
endif ()

add_subdirectory(3rdParty)
add_subdirectory(src)