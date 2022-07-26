//
// Created by Christopher Razavian on 10/07/2022.
//
#include <gtest/gtest.h>
#include "author.h"

TEST(Author, IntAndTextDates) {

    Author author = Author(
            "Name Transliterated",
            700,
            1300,
            "8th century",
            "14th century");
    auto expected = "(d. 8th century/14th century)";
    EXPECT_EQ(expected, author.getDeathDates());
}

TEST(Author, IntDatesOnly) {

    Author author = Author(
            "Name Transliterated",
            700,
            1300,
            "NO DATA",
            "NO DATA");
    auto expected = "(d. 700/1300)";
    EXPECT_EQ(expected, author.getDeathDates());
}

TEST(Author, NoIntDates) {

    Author author = Author(
            "Name Transliterated",
            0,
            0,
            "8th century",
            "14th century");
    auto expected = "(d. 8th century/14th century)";
    EXPECT_EQ(expected, author.getDeathDates());
}

TEST(Author, DontAddD) {

    Author author = Author(
            "Name Transliterated",
            0,
            0,
            "fl. 553",
            "fl. 1158");
    auto expected = "(fl. 553/1158)";
    EXPECT_EQ(expected, author.getDeathDates());
}

TEST(Author, After) {

    Author author = Author(
            "Name Transliterated",
            0,
            0,
            "after 1129",
            "after 1716");
    auto expected = "(d. after 1129/1716)";
    EXPECT_EQ(expected, author.getDeathDates());
}