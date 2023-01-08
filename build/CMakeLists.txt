cmake_minimum_required(VERSION 3.0)

set (CMAKE_C_COMPILER "gcc")

project(api_annuaire)

set(SRCS
    ../main.c
    ../functions.c
    )

set(HEADERS
    ../functions.h
    )

add_executable(api_annuaire ${SRCS} ${HEADERS})