//
// Created by pooya on 4/25/22.
//
#include <gtest/gtest.h>
#include "../tub_json.h"
#include <fstream>
#include "./entry_builder.h"

class EntryBuilderTest : public ::testing::Test
{
protected:
    // Per-test-suite set-up.
    // Called before the first test in this test suite.
    // Can be omitted if not needed.
    static void SetUpTestSuite() {
        // Avoid reallocating static objects if called in subclasses of FooTest.
        if (entries.empty()) {

            /*
             * Create Json from Text file
             *
             * This will create a json object that can repeatedly be used in tests
             */
            tub_json tubJson;
            // Read from the text file
            std::ifstream file("/Users/pooya/Developer/sandbox/cpp/tub-pdf-maker/tests/response.json");
            std::string json_string( (std::istreambuf_iterator<char>(file) ),
                                     (std::istreambuf_iterator<char>()    ) );

            auto json = tubJson.parse(json_string);
            auto results = json["query"]["results"];
            entry_builder entryBuilder;
            entries = entryBuilder.build_entries(results);
        }
    }

    // Some expensive resource shared by all tests.
    static std::vector<Entry> entries;
};

std::vector<Entry> EntryBuilderTest::entries = {};



TEST_F(EntryBuilderTest, NoDatesNoDescription) {
    /*
     * Test to see if I can get a single title, and that it is in UTF-8
     */

    auto entries = EntryBuilderTest::entries;
    EXPECT_EQ(5, entries.size());
    auto entry = entries.at(0);
    Category category {ManuscriptOnly};
    EXPECT_EQ("بحث في) أصول الفقه)", entry.getTitleArabic());
    EXPECT_EQ("(Bahth fī) uṣūl al-fiqh", entry.getTitleTransliterated());
    EXPECT_EQ("(Bahth fī) uṣūl al-fiqh", entry.getId());
    EXPECT_EQ("NO DATA", entry.getDescription());
    EXPECT_EQ(category,entry.getCategory());

    EXPECT_EQ("Murtaḍā al-Ḥusaynī", entry.getAuthor().getName());
    EXPECT_EQ(0,entry.getAuthor().getMDeathHijri());
    EXPECT_EQ("NO DATA",entry.getAuthor().getMDeathHijriText());
    EXPECT_EQ(0,entry.getAuthor().getMDeathGregorian());
    EXPECT_EQ("NO DATA",entry.getAuthor().getMDeathGregorianText());

    EXPECT_EQ("(d. NO DATA/NO DATA)",entry.getAuthor().getDeathDates()) << "Didn't make the correct death dates string";

}

TEST_F(EntryBuilderTest, WithDatesAndDescription) {
    /*
     * Test to see if I can get a single title, and that it is in UTF-8
     */

    auto entries = EntryBuilderTest::entries;
    auto entry = entries.at(1);
    Category category {Edited};
    EXPECT_EQ("مختصر) التذكرة بأصول الفقه)", entry.getTitleArabic());
    EXPECT_EQ("(Mukhtaṣar) al-Tadhkira bi-uṣul al-fiqh", entry.getTitleTransliterated());
    EXPECT_EQ("(Mukhtaṣar) al-Tadhkira bi-uṣul al-fiqh", entry.getId());
    EXPECT_EQ( "This is a summary of al-Tadhkira bi-uṣūl al-fiqh.", entry.getDescription());
    EXPECT_EQ(category,entry.getCategory());

    EXPECT_EQ("Abū l-Fatḥ Muḥammad b. ʿAlī b.ʿUthmān al-Ṭarāblūsī al-Karājukī", entry.getAuthor().getName());
    EXPECT_EQ(449,entry.getAuthor().getMDeathHijri());
    EXPECT_EQ("NO DATA",entry.getAuthor().getMDeathHijriText());
    EXPECT_EQ(1057,entry.getAuthor().getMDeathGregorian());
    EXPECT_EQ("NO DATA",entry.getAuthor().getMDeathGregorianText());
    EXPECT_EQ("(d. 449/1057)",entry.getAuthor().getDeathDates()) << "Didn't make the correct death dates string";

}