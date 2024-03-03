cmake_minimum_required(VERSION 3.21)

get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${DIR} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Qt6_DIR $ENV{Qt6_DIR})
list(APPEND CMAKE_PREFIX_PATH ${Qt6_DIR})
message(STATUS "Qt6 DIR: ${Qt6_DIR}")

find_package(Qt6 6.2.4 REQUIRED COMPONENTS Core Widgets)
if (Qt6Core_VERSION VERSION_GREATER_EQUAL 6.3.0)
    qt_standard_project_setup()
else()
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
endif()

add_subdirectory(src)