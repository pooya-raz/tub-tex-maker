//
// Created by Christopher Razavian on 10/07/2022.
//
#include <gtest/gtest.h>
#include "author.h"
#include <fstream>

TEST(AuthorIntDeathDates, BasicTest) {

    Author author = Author(
            "Name Transliterated",
            700,
            1300,
            "NO DATA",
            "NO DATA");
    auto expected = "(d. 700/1300)";
    EXPECT_EQ(expected, author.getDeathDates());
}

TEST(AuthorTextDeathDates, BasicTest) {

    Author author = Author(
            "Name Transliterated",
            0,
            0,
            "8th century",
            "14th century");
    auto expected = "(d. 8th century/14th century)";
    EXPECT_EQ(expected, author.getDeathDates());
}