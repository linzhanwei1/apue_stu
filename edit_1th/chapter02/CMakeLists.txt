cmake_minimum_required(VERSION 3.10)
project(chapter02 VERSION 1.0.0 LANGUAGES C)

# add lib
add_library(lib STATIC ${CMAKE_CURRENT_LIST_DIR}/../lib/error.c)
target_include_directories(lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../lib/include)

# 编译应用程序
function(add_app name)
    list(SUBLIST ARGV 1 ${ARGC} src)
    # message("SUBLIST ${src}")
    
    add_executable(${name} ${src})
    target_link_libraries(${name} PUBLIC lib)

endfunction()

add_app(2-1 2-1conf.c)