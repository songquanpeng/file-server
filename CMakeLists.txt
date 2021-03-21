cmake_minimum_required(VERSION 3.10)
project(file-server)

set(CMAKE_CXX_STANDARD 11)
find_package(Threads)
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "src/*.h")
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})