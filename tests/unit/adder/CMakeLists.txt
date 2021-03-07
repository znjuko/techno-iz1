file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(adder_test ${SRCS})

TARGET_LINK_LIBRARIES(adder_test
        adder
        gtest
        )

add_test(NAME adder_test
        COMMAND adder_test)