cmake_minimum_required(VERSION 3.7)

# Project's name

project(prometheus C)
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

file(GLOB prometheus_SRC
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

# Setup output

add_library(prometheus SHARED "${prometheus_SRC}" )
install(TARGETS prometheus
     RUNTIME DESTINATION bin COMPONENT libraries
     LIBRARY DESTINATION lib COMPONENT libraries
     ARCHIVE DESTINATION lib COMPONENT libraries)



# Setup 'testing' binary
add_executable(testing EXCLUDE_FROM_ALL "${PROJECT_SOURCE_DIR}/test/main.c")
target_link_libraries(testing prometheus microhttpd)

# Some versioning stuffs

set (prometheus_VERSION_MAJOR 0)
set (prometheus_VERSION_MINOR 0)
set (prometheus_VERSION_PATCH 1)

configure_file (
  "${PROJECT_SOURCE_DIR}/include/config.h.in"
  "${PROJECT_SOURCE_DIR}/include/config.h"
)


