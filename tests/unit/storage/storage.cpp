//
// Created by Черных Никита Алекандрович on 3/6/21.
//

#include "gtest/gtest.h"

extern "C" {
#include "storage.h"
}

TEST(initialize, ok) {
    EXPECT_TRUE(true);
}

int main() {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}