cmake_minimum_required(VERSION 3.8)
project(Dijkstra)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES src/main.c include/dijkstra.h src/dijkstra.c include/IO_dijkstra.h src/IO_dijkstra.c)
add_executable(Dijkstra ${SOURCE_FILES})