//
// Created by Christopher Razavian on 10/07/2022.
//
#include <gtest/gtest.h>
#include "manuscript.h"

TEST(ManuscriptTestAllFields, BasicTest) {

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

TEST(ManuscriptGregorianOnly, BasicTest) {

    Manuscript manuscript = Manuscript(
            "Location",
            0,
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
