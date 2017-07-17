cmake_minimum_required(VERSION 3.7)

# Project's name

project(libprometheus C)
# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

#Check for libmicrohttpd

find_package(PkgConfig)
pkg_check_modules(PC_LIBMICROHTTPD QUIET libmicrohttpd-0.9.44)
set(LIBMICROHTTPD_DEFINITIONS ${PC_LIBMICROHTTPD_CFLAGS_OTHER})

# Setup the include folders

set(PROJECT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_INCLUDE_DIR}")

# Grab all the src files 

file(GLOB libprometheus_SRC
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

# Setup output

add_library(libprometheus "${libprometheus_SRC}")

# Some versioning stuffs

set (libprometheus_VERSION_MAJOR 0)
set (libprometheus_VERSION_MINOR 0)
set (libprometheus_VERSION_PATCH 1)

configure_file (
  "${PROJECT_SOURCE_DIR}/include/config.h.in"
  "${PROJECT_SOURCE_DIR}/include/config.h"
  )

