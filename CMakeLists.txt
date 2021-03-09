cmake_minimum_required(VERSION 3.10.2)

option(test "Build all tests." ON)

project(techno_iz1 C CXX)

add_subdirectory(cmd)
add_subdirectory(src)

if(test)
    set(CMAKE_CXX_FLAGS         "-Wall -Wno-unknown-pragmas -Wno-sign-compare -Woverloaded-virtual -Wwrite-strings -Wno-unused -Werror -Wpedantic")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")

    set(CMAKE_C_FLAGS "--coverage")
    enable_testing()

    add_subdirectory(vendor/googletest)

    add_subdirectory(tests)
endif(test)
