# Copyright (C) 2016-2017 Jonathan Müller <jonathanmueller.dev@gmail.com>
# This file is subject to the license terms in the LICENSE file
# found in the top-level directory of this distribution.

cmake_minimum_required(VERSION 3.1)
project(STANDARDESE VERSION 0.5.2)

option(STANDARDESE_BUILD_TOOL "Build the standardese binary" ON)
option(STANDARDESE_BUILD_TEST "Build the standardese test suite" ON)
option(BUILD_SHARED_LIBS "Build shared libraries (.dll/.so/.dylib) instead of static ones (.lib/.a)" ON)

include(GNUInstallDirs)
set(lib_dest "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/standardese" CACHE PATH "")
set(include_dest "${CMAKE_INSTALL_INCLUDEDIR}" CACHE PATH "")
set(tool_dest "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}" CACHE PATH "")

# add external libraries
include(external/external.cmake)

if (MSVC)
    add_compile_options(
        # Disable warnings
        -D_CRT_SECURE_NO_WARNINGS
        -D_SCL_SECURE_NO_WARNINGS
        /wd4503 # decorated name length exceeded, name was truncated
        /MP # Multi-processor compilation
        )
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "" FORCE)

# subdirectories
add_subdirectory(src)
if(STANDARDESE_BUILD_TOOL)
    add_subdirectory(tool)
endif()
if (STANDARDESE_BUILD_TEST)
    add_subdirectory(test)
endif()

# install configuration
install(EXPORT standardese DESTINATION "${lib_dest}")
install(FILES standardese-config.cmake LICENSE DESTINATION "${lib_dest}")
