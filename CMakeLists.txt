cmake_minimum_required(VERSION 3.10)
project(pawn-ini VERSION 0.1.0 LANGUAGES CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Platform detection
if(WIN32)
    set(PLUGIN_EXTENSION ".dll")
    add_definitions(-DWIN32 -D_WIN32)
elseif(UNIX)
    set(PLUGIN_EXTENSION ".so")
    add_definitions(-DLINUX)
endif()

# Output directories (build only, not install)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Architecture folder label
if(NOT DEFINED PAWN_INI_ARCH OR PAWN_INI_ARCH STREQUAL "")
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(PAWN_INI_ARCH "x64")
    else()
        set(PAWN_INI_ARCH "x32")
    endif()
endif()

# Source files
set(SOURCES
    source/main.cpp
    source/handler.cpp
    source/natives.cpp
    sdk/amxplugin.cpp
)

# Headers
set(HEADERS
    source/handler.hpp
    source/natives.hpp
    source/constants.hpp
    sdk/amx/amx.h
    sdk/plugincommon.h
    sdk/plugin.h
)

# Create plugin library
add_library(pawn-ini SHARED ${SOURCES} ${HEADERS})

# Includes
target_include_directories(pawn-ini PRIVATE
    ${CMAKE_SOURCE_DIR}/sdk
    ${CMAKE_SOURCE_DIR}/sdk/amx
    ${CMAKE_SOURCE_DIR}/source
)

# Compiler flags
if(MSVC)
    target_compile_options(pawn-ini PRIVATE /W4 /O2)
    target_compile_definitions(pawn-ini PRIVATE _CRT_SECURE_NO_WARNINGS HAVE_STDINT_H)
else()
    target_compile_options(pawn-ini PRIVATE -Wall -Wextra -O3 -fPIC)
    if(UNIX)
        target_compile_options(pawn-ini PRIVATE -m32)
        target_link_options(pawn-ini PRIVATE -m32)
    endif()
endif()

# Output name
set_target_properties(pawn-ini PROPERTIES
    PREFIX ""
    OUTPUT_NAME "pawn-ini"
    SUFFIX ${PLUGIN_EXTENSION}
)

#
# INSTALLATION — 100% FIXED
#
install(TARGETS pawn-ini
    RUNTIME DESTINATION ${PAWN_INI_ARCH}
    LIBRARY DESTINATION ${PAWN_INI_ARCH}
)

# Install .inc
if(PAWN_INI_INC)
    install(FILES ${PAWN_INI_INC}
        DESTINATION ${PAWN_INI_ARCH}
    )
endif()

# Info
message(STATUS "==============================================")
message(STATUS "pawn-ini Plugin Configuration")
message(STATUS "Architecture: ${PAWN_INI_ARCH}")
message(STATUS "Plugin Extension: ${PLUGIN_EXTENSION}")
message(STATUS "==============================================")
