cmake_minimum_required(VERSION 4.1.1)

project(LowLevelCppDesigns VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#main entry point
add_subdirectory(src)
