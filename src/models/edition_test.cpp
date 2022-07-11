//
// Created by Christopher Razavian on 10/07/2022.
//
#include <gtest/gtest.h>
#include "edition.h"

TEST(Edition, BasicTest) {

    Edition edition = Edition("Title Transliterated",
                              "Title Arabic",
                              "Editor",
                              "Lithograph",
                              "Publisher",
                              "City",
                              700,
                              1300,
                              "NO DATA",
                              "NO DATA",
                              "",
                              "Published edition of title");

    auto expected = "\\item \\emph{Title Transliterated}, ed. Editor, Lithograph, Publisher, City, 700/1300\n";
    EXPECT_EQ(expected, edition.to_latex());
}

TEST(Edition, ModernPrintTest) {

    Edition edition = Edition("Title Transliterated",
                              "Title Arabic",
                              "Editor",
                              "Modern print",
                              "Publisher",
                              "City",
                              700,
                              1300,
                              "NO DATA",
                              "NO DATA",
                              "",
                              "Published edition of title");

    auto expected = "\\item \\emph{Title Transliterated}, ed. Editor, Publisher, City, 700/1300\n";
    EXPECT_EQ(expected, edition.to_latex());
}

TEST(Edition, OnlyShowGregorian) {

    Edition edition = Edition("Title Transliterated",
                              "Title Arabic",
                              "Editor",
                              "Modern print",
                              "Publisher",
                              "City",
                              0,
                              1940,
                              "NO DATA",
                              "NO DATA",
                              "",
                              "Published edition of title");

    auto expected = "\\item \\emph{Title Transliterated}, ed. Editor, Publisher, City, 1940\n";
    EXPECT_EQ(expected, edition.to_latex());
}
