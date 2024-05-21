cmake_minimum_required(VERSION 3.2)
project(lib VERSION 1.0.0 LANGUAGES C)

# add the Common_fun library
add_library(${PROJECT_NAME} STATIC error.c)
target_include_directories(${PROJECT_NAME} PUBLIC "./include")