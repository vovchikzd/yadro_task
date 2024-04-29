cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

project(fsort
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

# only for ninja and only from 24 version
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.24
    AND CMAKE_GENERATOR STREQUAL "Ninja")
  set(CMAKE_COLOR_DIAGNOSTICS On) 
endif()

set(PRJ_INCLUDE_DIR "include")

add_executable(fsort)
target_sources(fsort
                PUBLIC main.cpp)
target_include_directories(fsort
                            PRIVATE ${PRJ_INCLUDE_DIR})

# target_sources(result PRIVATE
#                FILE_SET modules TYPE CXX_MODULES
#                FILES
#                  ${PROJECT_MODULE_DIR}/module.cppm)
