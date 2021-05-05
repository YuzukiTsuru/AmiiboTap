cmake_minimum_required(VERSION 3.8)
project(amiibo)

include_directories(
        PUBLIC mbedtls/include/
        amiitool-src/include/
)
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
target_link_libraries(amiibo mbedtls)