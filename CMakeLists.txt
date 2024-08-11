cmake_minimum_required(VERSION 3.28)

project(ext-sort
          LANGUAGES CXX)

# check compilers
if((CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
   AND (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 17))
  message(FATAL_ERROR "Requires at least clang v17")
elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
       AND (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 14))
  message(FATAL_ERROR "Requires at least gcc v14")
elseif((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
       AND (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.34))
  message(FATAL_ERROR "Requires at least MSVC v19.34")
endif()

# check generators
if(UNIX AND (CMAKE_GENERATOR STREQUAL "Unix Makefiles"))
  message(FATAL_ERROR "\nC++ modules aren't supported by Unix Makefiles."
                      "\nModules are supported by Ninja for v1.11 and newer.")
elseif((CMAKE_GENERATOR MATCHES "Visual Studio")
       AND (MSVC_TOOLSET_VERSION LESS 143))
  message(FATAL_ERROR "Requires at least MSVC toolset v14.34 (Visual Studio v17.4 2022) generator")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)
set(CMAKE_COLOR_DIAGNOSTICS On)
add_compile_options(-Wall -Wextra -Wpedantic)

set(PRJ_MODULE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules)

add_executable(ext-sort main.cpp)

add_subdirectory(${PRJ_MODULE_DIR})
