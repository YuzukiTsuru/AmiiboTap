cmake_minimum_required(VERSION 3.8)
project(AmiiboTap)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/libnfc)

add_executable(AmiiboTap src/amiibo-tap.cpp)