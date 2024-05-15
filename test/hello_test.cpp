//
// Created by mac on 2024/5/13.
//
#include <gtest/gtest.h>
#include <lib.h>

TEST(HelloTest, BasicAssertion) {
    EXPECT_STRNE("hello", "world");

    EXPECT_EQ(multiply(7, 6), 42);
}
