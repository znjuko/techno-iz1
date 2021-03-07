cmake_minimum_required(VERSION 3.10.2)

add_subdirectory(storage)

target_include_directories(${PROJECT_NAME} PUBLIC storage)

target_link_directories(${PROJECT_NAME} PUBLIC storage)

