cmake_minimum_required(VERSION 3.10.2)

project(techno_iz1 C)

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME} main.c tests/unit/storage/storage.cpp src/adder/adder.c src/adder/adder.h)

add_subdirectory(src)

target_link_directories(${PROJECT_NAME} PUBLIC src)

target_link_libraries(${PROJECT_NAME} PUBLIC storage)

target_include_directories(${PROJECT_NAME} PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/src"
        )

