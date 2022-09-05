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
                              0,
                              "NO DATA",
                              "NO DATA",
                              "NO DATA",
                              "",
                              "Published edition of title",
                              700);

    auto expected = "\\item \\emph{Title Transliterated}, ed. Editor, Lithograph (City: Publisher, 700/1300)\n";
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
                              0,
                              "NO DATA",
                              "NO DATA",
                              "NO DATA",
                              "",
                              "Published edition of title",
                              700);

    auto expected = "\\item \\emph{Title Transliterated}, ed. Editor (City: Publisher, 700/1300)\n";
    EXPECT_EQ(expected, edition.to_latex());
}

TEST(Edition, OnlyShowGregorian) {

    Edition edition = Edition("Title Transliterated",
                              "Title Arabic",
                              "Editor",
                              "Modern print",
                              "Publisher",
                              "City",
                              9999,
                              1940,
                              0,
                              "NO DATA",
                              "NO DATA",
                              "NO DATA",
                              "",
                              "Published edition of title",
                              700);

    auto expected = "\\item \\emph{Title Transliterated}, ed. Editor (City: Publisher, 1940)\n";
    EXPECT_EQ(expected, edition.to_latex());
}

TEST(Edition, Shamsi) {

    Edition edition = Edition("Title Transliterated",
                              "Title Arabic",
                              "Editor",
                              "Modern print",
                              "Publisher",
                              "City",
                              9999,
                              1300,
                              678,
                              "NO DATA",
                              "NO DATA",
                              "NO DATA",
                              "",
                              "Published edition of title",
                              700);

    auto expected = "\\item \\emph{Title Transliterated}, ed. Editor (City: Publisher, 678Sh/1300)\n";
    EXPECT_EQ(expected, edition.to_latex());
}

TEST(Edition, ShamsiOnly) {

    Edition edition = Edition("Title Transliterated",
                              "Title Arabic",
                              "Editor",
                              "Modern print",
                              "Publisher",
                              "City",
                              9999,
                              0,
                              678,
                              "NO DATA",
                              "NO DATA",
                              "NO DATA",
                              "",
                              "Published edition of title",
                              700);

    auto expected = "\\item \\emph{Title Transliterated}, ed. Editor (City: Publisher, 678Sh)\n";
    EXPECT_EQ(expected, edition.to_latex());
}

TEST(Edition, NoPublisher) {

    Edition edition = Edition("Title Transliterated",
                              "Title Arabic",
                              "Editor",
                              "Lithograph",
                              "NO DATA",
                              "City",
                              700,
                              1300,
                              0,
                              "NO DATA",
                              "NO DATA",
                              "NO DATA",
                              "",
                              "Published edition of title",
                              700);

    auto expected = "\\item \\emph{Title Transliterated}, ed. Editor, Lithograph (City: n.pub., 700/1300)\n";
    EXPECT_EQ(expected, edition.to_latex());
}

TEST(Edition, NoCity) {

    Edition edition = Edition("Title Transliterated",
                              "Title Arabic",
                              "Editor",
                              "Lithograph",
                              "Publisher",
                              "NO DATA",
                              700,
                              1300,
                              0,
                              "NO DATA",
                              "NO DATA",
                              "NO DATA",
                              "",
                              "Published edition of title",
                              700);

    auto expected = "\\item \\emph{Title Transliterated}, ed. Editor, Lithograph (n.plac., Publisher, 700/1300)\n";
    EXPECT_EQ(expected, edition.to_latex());
}

TEST(Edition, NoEditorModernPrint) {

    Edition edition = Edition("Title Transliterated",
                              "Title Arabic",
                              "NO DATA",
                              "Modern print",
                              "Publisher",
                              "City",
                              700,
                              1300,
                              0,
                              "NO DATA",
                              "NO DATA",
                              "NO DATA",
                              "",
                              "Published edition of title",
                              700);

    auto expected = "\\item \\emph{Title Transliterated} (City: Publisher, 700/1300)\n";
    EXPECT_EQ(expected, edition.to_latex());
}

TEST(Edition, NoEditorNoEditionType) {

    Edition edition = Edition("Title Transliterated",
                              "Title Arabic",
                              "NO DATA",
                              "NO DATA",
                              "Publisher",
                              "City",
                              700,
                              1300,
                              0,
                              "NO DATA",
                              "NO DATA",
                              "NO DATA",
                              "",
                              "Published edition of title",
                              700);

    auto expected = "\\item \\emph{Title Transliterated} (City: Publisher, 700/1300)\n";
    EXPECT_EQ(expected, edition.to_latex());
}