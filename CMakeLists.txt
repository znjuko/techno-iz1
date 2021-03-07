cmake_minimum_required(VERSION 3.10.2)

option(test "Build all tests." OFF)

project(techno_iz1 C CXX)

enable_testing()

add_subdirectory(main)
add_subdirectory(src)

if(test)
    add_subdirectory(tests)
    add_subdirectory(vendor/googletest)
endif(test)
