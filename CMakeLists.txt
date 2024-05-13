cmake_minimum_required(VERSION 3.12)

project(ext-sort
          LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

set(PRJ_INCLUDE_DIR "include")
set(PRJ_SRC_DIR "src")

# only for ninja and only from 24 version
if(CMAKE_GENERATOR STREQUAL "Ninja"
     AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.24)
  set(CMAKE_COLOR_DIAGNOSTICS On) 
endif()

add_executable(ext-sort main.cpp)
target_sources(ext-sort
                 PRIVATE
                  ${PRJ_SRC_DIR}/init.cpp
                  ${PRJ_SRC_DIR}/tape.cpp
                  ${PRJ_SRC_DIR}/tape_head.cpp
                  ${PRJ_SRC_DIR}/tape_sort.cpp)
target_include_directories(ext-sort
                             PRIVATE ${PRJ_INCLUDE_DIR})
