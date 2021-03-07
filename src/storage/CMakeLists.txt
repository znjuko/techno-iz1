set(STORAGE_SRC storage.h storage.c)

add_library(storage STATIC ${STORAGE_SRC})

target_include_directories(storage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})