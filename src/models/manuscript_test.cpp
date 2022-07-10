//
// Created by Christopher Razavian on 10/07/2022.
//
#include <gtest/gtest.h>
#include "manuscript.h"

TEST(Manuscript, BasicTest) {

    Manuscript manuscript = Manuscript(
            "Location",
            700,
            1300,
            "NO DATA",
            "NO DATA",
            "City",
            "Manuscript Number",
            "Manuscript of Title"
    );

    auto expected = "\\item Location, City (\\#Manuscript Number), dated 700/1300\n";
    EXPECT_EQ(expected, manuscript.to_latex());
}

TEST(Manuscript, GregorianOnly) {

    Manuscript manuscript = Manuscript(
            "Location",
            9999,
            1940,
            "NO DATA",
            "NO DATA",
            "City",
            "Manuscript Number",
            "Manuscript of Title"
    );

    auto expected = "\\item Location, City (\\#Manuscript Number), dated 1940\n";
    EXPECT_EQ(expected, manuscript.to_latex());
}

TEST(Manuscript, UndatedManuscript) {

    Manuscript manuscript = Manuscript(
            "Location",
            9999,
            0,
            "NO DATA",
            "NO DATA",
            "City",
            "Manuscript Number",
            "Manuscript of Title"
    );

    auto expected = "\\item Location, City (\\#Manuscript Number), undated manuscript\n";
    EXPECT_EQ(expected, manuscript.to_latex());
}
