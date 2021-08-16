cmake_minimum_required(VERSION 3.8)
project(amiibo)

include_directories(
        PUBLIC mbedtls/include
        amiitool-src/include
)

set(ENABLE_PROGRAMS OFF CACHE BOOL "" FORCE)
set(ENABLE_TESTING OFF CACHE BOOL "" FORCE)

add_subdirectory(mbedtls)

add_library(amiibo
        amiitool-src/amiibo.c
        amiitool-src/drbg.c
        amiitool-src/keygen.c
        amiitool-src/util.c
        )
if (MSVC)
    target_compile_options(amiibo PRIVATE "/wd4996")
endif (MSVC)

target_link_libraries(amiibo mbedcrypto)

add_executable(amiitool amiitool.c)
target_link_libraries(amiitool amiibo)