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

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Architecture label for installation directories (x32/x64)
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

# Create shared library (plugin)
add_library(pawn-ini SHARED ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(pawn-ini PRIVATE
    ${CMAKE_SOURCE_DIR}/sdk
    ${CMAKE_SOURCE_DIR}/sdk/amx
    ${CMAKE_SOURCE_DIR}/source
)

# Compiler flags
if(MSVC)
    # Visual Studio
    target_compile_options(pawn-ini PRIVATE /W4 /O2)
    target_compile_definitions(pawn-ini PRIVATE _CRT_SECURE_NO_WARNINGS HAVE_STDINT_H)
else()
    # GCC/Clang
    target_compile_options(pawn-ini PRIVATE -Wall -Wextra -O3 -fPIC)
    
    if(UNIX)
        target_compile_options(pawn-ini PRIVATE -m32)
        target_link_options(pawn-ini PRIVATE -m32)
    endif()
endif()

# Set output name
set_target_properties(pawn-ini PROPERTIES
    PREFIX ""
    OUTPUT_NAME "pawn-ini"
    SUFFIX ${PLUGIN_EXTENSION}
)

# Installation
install(TARGETS pawn-ini
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/output/${PAWN_INI_ARCH}
    LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/output/${PAWN_INI_ARCH}
)

# Locate pawn-ini.inc for installation (prefer repo root, fallback to dist package)
set(PAWN_INI_INC "${CMAKE_SOURCE_DIR}/pawn-ini.inc")
if(NOT EXISTS "${PAWN_INI_INC}")
    if(EXISTS "${CMAKE_SOURCE_DIR}/dist/pawn-ini-v1.0.0/pawn-ini.inc")
        set(PAWN_INI_INC "${CMAKE_SOURCE_DIR}/dist/pawn-ini-v1.0.0/pawn-ini.inc")
    else()
        set(PAWN_INI_INC "")
    endif()
endif()

if(PAWN_INI_INC)
    install(FILES ${PAWN_INI_INC}
        DESTINATION ${CMAKE_SOURCE_DIR}/output
    )
endif()

# Print build information
message(STATUS "==============================================")
message(STATUS "pawn-ini Plugin Configuration")
message(STATUS "==============================================")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Plugin Extension: ${PLUGIN_EXTENSION}")
message(STATUS "Output Directory: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message(STATUS "==============================================")
