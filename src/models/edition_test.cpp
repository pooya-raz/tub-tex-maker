//
// Created by Christopher Razavian on 10/07/2022.
//
#include <gtest/gtest.h>
#include "edition.h"

TEST(EditionTestAllFields, BasicTest) {

    Edition edition = Edition("Title Transliterated",
                              "Title Arabic",
                              "Editor",
                              "Lithograph",
                              "Publisher",
                              "City",
                              700,
                              1300, "NO DATA", "NO DATA", "", "Published edition of title");

    auto expected = "\\item \\emph{Title Transliterated}, Editor, Lithograph, Publisher, City, 700/1300\n";
    EXPECT_EQ(expected, edition.to_latex());
}

TEST(EditionModernPrintTest, BasicTest) {

    Edition edition = Edition("Title Transliterated",
                              "Title Arabic",
                              "Editor",
                              "Modern Print",
                              "Publisher",
                              "City",
                              700,
                              1300, "NO DATA", "NO DATA", "", "Published edition of title");

    auto expected = "\\item \\emph{Title Transliterated}, Editor, Publisher, City, 700/1300\n";
    EXPECT_EQ(expected, edition.to_latex());
}
