cmake_minimum_required(VERSION 3.10)
project(http_server)

set(CMAKE_CXX_STANDARD 11)
find_package(Threads)
file(GLOB SOURCES "src/*.cpp")
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} src/utils.h src/server.h src/constants.h src/http.h src/render.h)
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})