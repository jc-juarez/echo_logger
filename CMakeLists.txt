# *************************************
# Astra Cache Server
# Build
# 'CMakeLists.txt'
# Author: jcjuarez
# *************************************

cmake_minimum_required(VERSION 3.0)

project(AstraCachingServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_FILES
    main.cc
    src/logger/logger.cc
    src/logger/logging_engine.cc
    src/logger/filesystem_writer.cc
    src/utils/uuid_utilities.cc
)

add_executable(astra ${SOURCE_FILES})

target_link_libraries(astra)