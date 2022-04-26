//
// Created by pooya on 4/25/22.
//
#include <gtest/gtest.h>
#include "../src/tub_json.h"
#include <fstream>
#include "../src/entry_builder.h"

class EntryBuilderTest : public ::testing::Test
{
protected:
    // Per-test-suite set-up.
    // Called before the first test in this test suite.
    // Can be omitted if not needed.
    static void SetUpTestSuite() {
        // Avoid reallocating static objects if called in subclasses of FooTest.
        if (json.empty()) {

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
            json = tubJson.parse(json_string);
        }
    }

    // Some expensive resource shared by all tests.
    static nlohmann::json json;
};

nlohmann::json EntryBuilderTest::json = nlohmann::json::value_t::array;



TEST_F(EntryBuilderTest, BasicEntry) {
    /*
     * Test to see if I can get a single title, and that it is in UTF-8
     */
    auto results = EntryBuilderTest::json["query"]["results"];
    entry_builder entryBuilder;
    std::vector<Entry> entries = entryBuilder.build_entries(results);
    EXPECT_EQ(5, entries.size());
    EXPECT_EQ("بحث في) أصول الفقه)", entries.at(0).getTitleArabic());
    EXPECT_EQ("(Bahth fī) uṣūl al-fiqh", entries.at(0).getTitleTransliterated());
    EXPECT_EQ("(Bahth fī) uṣūl al-fiqh", entries.at(0).getId());
    EXPECT_EQ("Sample description", entries.at(0).getDescription());

    EXPECT_EQ("Murtaḍā al-Ḥusaynī", entries.at(0).getAuthor().getName());
    EXPECT_EQ(111,entries.at(0).getAuthor().getMDeathHijri());
    EXPECT_EQ("111",entries.at(0).getAuthor().getMDeathHijriText());
    EXPECT_EQ(222,entries.at(0).getAuthor().getMDeathGregorian());
    EXPECT_EQ("222",entries.at(0).getAuthor().getMDeathGregorianText());




}