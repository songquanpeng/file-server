cmake_minimum_required(VERSION 3.15)
project(http_server)

set(CMAKE_CXX_STANDARD 11)
include_directories(include)
aux_source_directory(src extra_source_code)
add_library(extra ${extra_source_code})
add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} extra)