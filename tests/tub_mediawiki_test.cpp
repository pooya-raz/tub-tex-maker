//
// Created by pooya on 4/25/22.
//
#include <gtest/gtest.h>
#include "../src/services/tub_mediawiki_service.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    tub_mediawiki_service tub;
    std::string result = tub.getQuery("[[Category:Title]][[Book type::Monograph]][[Has number of commentaries::>>0]]|?Title (Arabic)|?Title (transliterated)|?Has author(s)|?Has author(s).Death (Hijri)|?Has author(s).Death (Gregorian)|?Has author(s).Death (Hijri) text|?Has author(s).Death (Gregorian) text|?Has a catalogue description|limit=1|sort=Has author(s).Death (Hijri)");
    std::string hi = "hi";
    EXPECT_EQ(hi, result);
}
