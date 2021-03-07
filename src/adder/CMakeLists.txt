set(ADDER_SRC adder.h adder.c)

add_library(adder STATIC ${ADDER_SRC})

target_include_directories(adder PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})