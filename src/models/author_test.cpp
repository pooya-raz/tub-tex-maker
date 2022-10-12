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
			0,
            "8th century",
            "14th century",
			"NO DATA");
    auto expected = "(d. 8th century/14th century)";
    EXPECT_EQ(expected, author.getDeathDates());
}

TEST(Author, IntDatesOnly) {

    Author author = Author(
            "Name Transliterated",
            700,
            1300,
			0,
            "NO DATA",
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
			0,
            "8th century",
            "14th century",
			"NO DATA");
    auto expected = "(d. 8th century/14th century)";
    EXPECT_EQ(expected, author.getDeathDates());
}

TEST(Author, DontAddD) {

    Author author = Author(
            "Name Transliterated",
            0,
            0,
			0,
            "fl. 553",
            "fl. 1158",
			"NO DATA");
    auto expected = "(fl. 553/1158)";
    EXPECT_EQ(expected, author.getDeathDates());
}

TEST(Author, After) {

    Author author = Author(
            "Name Transliterated",
            0,
            0,
			0,
            "after 1129",
            "after 1716",
			"NO DATA");
    auto expected = "(d. after 1129/1716)";
    EXPECT_EQ(expected, author.getDeathDates());
}

TEST(Author, WithC) {

    Author author = Author(
            "Name Transliterated",
            0,
            0,
			0,
            "c. 1129",
            "c. 1716",
			"NO DATA");
    auto expected = "(d. c. 1129/1716)";
    EXPECT_EQ(expected, author.getDeathDates());
}

TEST(Author, Before) {

    Author author = Author(
            "Name Transliterated",
            0,
            0,
			0,
            "before 1129",
            "before 1716",
			"NO DATA");
    auto expected = "(d. before 1129/1716)";
    EXPECT_EQ(expected, author.getDeathDates());
}

TEST(Author, ShamsiDate) {

    Author author = Author(
            "Name Transliterated",
            700,
            0,
			1200,
            "NO DATA",
            "NO DATA",
			"NO DATA");
    auto expected = "(d. 700/1200 SH)";
    EXPECT_EQ(expected, author.getDeathDates());
}

TEST(Author, ShamsiDateText) {

    Author author = Author(
            "Name Transliterated",
            700,
            0,
			1200,
            "NO DATA",
            "NO DATA",
			"NO DATA");
    auto expected = "(d. 700/1200 SH)";
    EXPECT_EQ(expected, author.getDeathDates());
}

TEST(Author, ShamsiAndGregorianDate) {

    Author author = Author(
            "Name Transliterated",
            9999,
            1700,
			1200,
            "NO DATA",
            "NO DATA",
			"NO DATA");
    auto expected = "(d. 1200 SH/1700)";
    EXPECT_EQ(expected, author.getDeathDates());
}
