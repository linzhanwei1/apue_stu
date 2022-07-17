cmake_minimum_required(VERSION 3.2)
project(myls VERSION 1.0.0 LANGUAGES C)

# set variable

# add the Common_fun library
add_library(apue_lib STATIC ../../lib/error.c)

add_executable(myls myls.c)
add_executable(mycopy mycopy.c)
add_executable(mycopy_std mycopy_std.c)
add_executable(program program.c)
add_executable(myerror myerror.c)
add_executable(myuid myuid.c)
add_executable(signal signal.c)

target_link_libraries(myls PUBLIC apue_lib)
target_link_libraries(mycopy PUBLIC apue_lib)
target_link_libraries(mycopy_std PUBLIC apue_lib)
target_link_libraries(program PUBLIC apue_lib)
target_link_libraries(myerror PUBLIC apue_lib)
target_link_libraries(myuid PUBLIC apue_lib)
target_link_libraries(signal PUBLIC apue_lib)

# include paths
include_directories(myls 
                    "../../include" 
                    "../../lib"
                    )