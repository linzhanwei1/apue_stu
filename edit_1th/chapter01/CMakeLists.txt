cmake_minimum_required(VERSION 3.10)
project(chapter01 VERSION 1.0.0 LANGUAGES C)

# add lib
add_library(lib STATIC ${CMAKE_CURRENT_LIST_DIR}/../lib/error.c)
target_include_directories(lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../lib/include)

# 编译应用程序
function(add_app name)
    list(SUBLIST ARGV 1 ${ARGC} src)
    # message("SUBLIST ${src}")
    
    add_executable(${name} ${src})
    target_link_libraries(${name} PUBLIC lib)

endfunction(add_app abc)


add_app(ls1 ls1.c)
add_app(1-2 1-2.c)
add_app(1-3 1-3.c)
add_app(1-4 1-4.c)
add_app(1-5 1-5.c)
add_app(1-6 1-6.c)
add_app(1-7 1-7.c)
add_app(1-8 1-8.c)

# add_executable(myls myls.c)
# add_executable(mycopy mycopy.c)
# add_executable(mycopy_std mycopy_std.c)
# add_executable(program program.c)
# add_executable(myerror myerror.c)
# add_executable(myuid myuid.c)
# add_executable(signal signal.c)

# target_link_libraries(myls PUBLIC lib)
# target_link_libraries(mycopy PUBLIC apue_lib)
# target_link_libraries(mycopy_std PUBLIC apue_lib)
# target_link_libraries(program PUBLIC apue_lib)
# target_link_libraries(myerror PUBLIC apue_lib)
# target_link_libraries(myuid PUBLIC apue_lib)
# target_link_libraries(signal PUBLIC apue_lib)
