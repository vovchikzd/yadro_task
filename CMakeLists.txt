cmake_minimum_required(VERSION 3.12)

project(ext-sort
          LANGUAGES CXX)
set(PRJ_INCLUDE_DIR "include")
set(PRJ_SRC_DIR "src")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)
add_compile_options(-Wall -Wextra -Wpedantic)

# only for ninja and only from 24 version
if(CMAKE_GENERATOR STREQUAL "Ninja"
     AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.24)
  set(CMAKE_COLOR_DIAGNOSTICS On) 
endif()

add_executable(ext-sort main.cpp)
target_sources(ext-sort
                 PRIVATE
                  ${PRJ_SRC_DIR}/init.cpp
                  ${PRJ_SRC_DIR}/tape.cpp)
target_include_directories(ext-sort
                             PRIVATE ${PRJ_INCLUDE_DIR})

# target_sources(result
#                  PRIVATE
#                  FILE_SET modules
#                  TYPE CXX_MODULES
#                  FILES
#                    ${PROJECT_MODULE_DIR}/module.cppm)
