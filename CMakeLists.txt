cmake_minimum_required(VERSION 3.28)

project(ext-sort
          LANGUAGES CXX)

# check compilers
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang"
   AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 17)
  message(FATAL_ERROR "Requires at least clang 17")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU"
       AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 14)
  message(FATAL_ERROR "Requires at least g++ 14")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC"
       AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.34)
  message(FATAL_ERROR "Requires at least MSVC 19.34")
endif()

# check generators
if(NOT CMAKE_GENERATOR STREQUAL "Ninja"
   AND NOT "Visual Studio" STRLESS_EQUAL CMAKE_GENERATOR)
  message(FATAL_ERROR "Requires Ninja 1.11 or Visual Studio 17 2022 generator")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)
set(CMAKE_COLOR_DIAGNOSTICS On)
add_compile_options(-Wall -Wextra -Wpedantic)

set(PRJ_INCLUDE_DIR "include")
set(PRJ_MODULE_DIR "modules")

add_executable(ext-sort main.cpp)
target_sources(ext-sort PRIVATE
               FILE_SET modules TYPE CXX_MODULES
               BASE_DIRS ${PRJ_MODULE_DIR}
               FILES
                 ${PRJ_MODULE_DIR}/init.cppm
                 ${PRJ_MODULE_DIR}/tape.cppm
                 ${PRJ_MODULE_DIR}/tape_head.cppm
                 ${PRJ_MODULE_DIR}/tape_sort.cppm)

target_include_directories(ext-sort
                             PRIVATE ${PRJ_INCLUDE_DIR})
