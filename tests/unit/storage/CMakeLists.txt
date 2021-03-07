file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(storage_test ${SRCS})

TARGET_LINK_LIBRARIES(storage_test
        storage
        libgtest
        )

add_test(NAME storage_test
        COMMAND storage_test)