cmake_minimum_required(VERSION 3.10)
project(chapter08 VERSION 1.0.0 LANGUAGES C)

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

add_app(8-1 8-1.c)
add_app(8-2 8-2.c)
