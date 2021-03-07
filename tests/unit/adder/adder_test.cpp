//
// Created by Черных Никита Алекандрович on 3/7/21.
//

#include "gtest/gtest.h"
using testing::Test;

extern "C" {
    #include "adder.h"
}

TEST(initialize, ok) {
    EXPECT_TRUE(adder(1,2)==4);
}

TEST(initialize, nah) {
    EXPECT_TRUE(adder(1,2)!=4);
}
