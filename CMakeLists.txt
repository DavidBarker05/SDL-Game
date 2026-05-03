cmake_minimum_required(VERSION 3.20)

project(SDL-Game)

# 14 is what I use in vs2022 but this might work with 11 it's hard to tell when all the functions I use were added
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug-${CMAKE_SYSTEM_PROCESSOR}/vendor)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release-${CMAKE_SYSTEM_PROCESSOR}/vendor)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug-${CMAKE_SYSTEM_PROCESSOR}/vendor)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release-${CMAKE_SYSTEM_PROCESSOR}/vendor)

add_subdirectory(vendor/SDL3)
add_subdirectory(Engine)
add_subdirectory(SDL-Game)

set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SDL-Game)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(cpptrace-lib SDL_uclibc SDL3_test SDL3-shared PROPERTIES FOLDER "vendor")