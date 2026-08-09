cmake_minimum_required(VERSION 3.20)

project(ChessEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Single-config generators (Ninja, Unix Makefiles -- what VS Code / the CLI
# typically use) need CMAKE_BUILD_TYPE set explicitly. Multi-config
# generators (Visual Studio, Ninja Multi-Config) ignore this and instead
# use CMAKE_CONFIGURATION_TYPES + --config at build time.
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "Dist")
endif()

if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES Debug Release Dist CACHE STRING "Available configurations" FORCE)
endif()

# "Dist" is a custom configuration -- CMake only knows optimization flags
# for its built-in configs (Release, RelWithDebInfo, MinSizeRel), so without
# this, a Dist build would silently compile UNOPTIMIZED, which matters a lot
# for search speed in a chess engine. Reuse Release's flags for Dist.
set(CMAKE_CXX_FLAGS_DIST "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "Flags used by the C++ compiler during Dist builds." FORCE)
set(CMAKE_EXE_LINKER_FLAGS_DIST "${CMAKE_EXE_LINKER_FLAGS_RELEASE}" CACHE STRING "Flags used by the linker during Dist builds." FORCE)
mark_as_advanced(CMAKE_CXX_FLAGS_DIST CMAKE_EXE_LINKER_FLAGS_DIST)

add_subdirectory(Core)
add_subdirectory(App)
