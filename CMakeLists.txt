cmake_minimum_required(VERSION 3.28)

project(ext-sort
          LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
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
