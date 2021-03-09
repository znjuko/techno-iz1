cmake_minimum_required(VERSION 3.10.2)

option(test "Build all tests." ON)

project(techno_iz1 C CXX)

set(CMAKE_CXX_FLAGS --coverage)

add_subdirectory(cmd)
add_subdirectory(src)

#if(test)
    enable_testing()

    add_subdirectory(vendor/googletest)

    add_subdirectory(tests)
#endif(test)
