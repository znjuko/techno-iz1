cmake_minimum_required(VERSION 3.10.2)

project(techno_iz1 C CXX)

enable_testing()

add_subdirectory(main)
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(lib/googletest)
