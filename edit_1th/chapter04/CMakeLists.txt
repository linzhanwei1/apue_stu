cmake_minimum_required(VERSION 3.10)
project(chapter04 VERSION 1.0.0 LANGUAGES C)

# add lib
aux_source_directory("${CMAKE_CURRENT_LIST_DIR}/../lib/" LIB_SRC)
add_library(lib STATIC ${LIB_SRC})
target_include_directories(lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../lib/include)

# 编译应用程序
function(add_app name)
    list(SUBLIST ARGV 1 ${ARGC} src)
    # message("SUBLIST ${src}")
    
    add_executable(${name} ${src})
    target_link_libraries(${name} PUBLIC lib)

endfunction()

add_app(4-1 4-1.c)
add_app(4-2 4-2.c)
add_app(4-3 4-3.c)
add_app(4-4 4-4.c)
add_app(4-5 4-5.c)
add_app(4-6 4-6.c)
add_app(4-7 4-7.c)
add_app(4-8 4-8.c)
add_app(4-9 4-9.c)
add_app(4-10 4-10.c)