//
// Created by Черных Никита Алекандрович on 3/6/21.
//

#include <gtest/gtest.h>

extern "C" {
#include "adder.h"
}

TEST(initialize, ok) {
    EXPECT_TRUE(true);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}