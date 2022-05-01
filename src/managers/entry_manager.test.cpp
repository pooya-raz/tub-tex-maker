//
// Created by pooya on 4/25/22.
//
#include <gtest/gtest.h>
#include "../TubJson.h"
#include <fstream>
#include "./entry_manager.h"
class EntryBuilderTest : public ::testing::Test
{
protected:
    // Per-test-suite set-up.
    // Called before the first test in this test suite.
    // Can be omitted if not needed.
    static void SetUpTestSuite() {
        // Avoid reallocating static objects if called in subclasses of FooTest.
        if (entryMap.empty()) {

            /*
             * Create Json from Text file
             *
             * This will create a json object that can repeatedly be used in tests
             */
            TubJson tubJson;
            // Read from the text file
            std::ifstream file("/Users/pooya/Developer/sandbox/cpp/tub-pdf-maker/tests/1000response.json");
            std::string json_string( (std::istreambuf_iterator<char>(file) ),
                                     (std::istreambuf_iterator<char>()    ) );
            tubJson.parse(json_string);
            auto results = tubJson.at("query").at("results");
            EntryManager entryManager;
            entryManager.add_entries(results);
            entryMap = entryManager.getEntryMap();
        }
    }

    // Some expensive resource shared by all tests.
    static EntryMap& entryMap;
};
EntryMap emptyMap;
EntryMap& EntryBuilderTest::entryMap = emptyMap;



TEST_F(EntryBuilderTest, NoDatesNoDescription) {
    /*
     * Test to see if I can get a single title, and that it is in UTF-8
     */
    Category category {ManuscriptOnly};
    TitleType title_type {Treatise};
    const auto entryMap = EntryBuilderTest::entryMap[title_type];
    const auto& entry = entryMap.at(0);

    EXPECT_EQ("بحث في) أصول الفقه)", entry->getTitleArabic());
    EXPECT_EQ("(Bahth fī) uṣūl al-fiqh", entry->getTitleTransliterated());
    EXPECT_EQ("(Bahth fī) uṣūl al-fiqh", entry->getId());
    EXPECT_EQ("NO DATA", entry->getDescription());
    EXPECT_EQ(category,entry->getCategory());
    EXPECT_EQ(title_type,entry->getTitleType());

    std::vector<CorrectionsRequired> correctionsRequired {CheckDates};
    EXPECT_EQ(correctionsRequired,entry->getCorrectionsRequired());

    EXPECT_EQ("Murtaḍā al-Ḥusaynī", entry->getAuthor().getName());
    EXPECT_EQ(0,entry->getAuthor().getMDeathHijri());
    EXPECT_EQ("NO DATA",entry->getAuthor().getMDeathHijriText());
    EXPECT_EQ(0,entry->getAuthor().getMDeathGregorian());
    EXPECT_EQ("NO DATA",entry->getAuthor().getMDeathGregorianText());

    EXPECT_EQ("(d. NO DATA/NO DATA)",entry->getAuthor().getDeathDates()) << "Didn't make the correct death dates string";
}

TEST_F(EntryBuilderTest, WithDatesAndDescription) {
    /*
     * Test to see if I can get a single title, and that it is in UTF-8
     */
    Category category {Edited};
    TitleType title_type {Summary};
    const auto entryMap = EntryBuilderTest::entryMap[title_type];
    const auto& entry = entryMap.at(0);
    EXPECT_EQ("مختصر) التذكرة بأصول الفقه)", entry->getTitleArabic());
    EXPECT_EQ("(Mukhtaṣar) al-Tadhkira bi-uṣul al-fiqh", entry->getTitleTransliterated());
    EXPECT_EQ("(Mukhtaṣar) al-Tadhkira bi-uṣul al-fiqh", entry->getId());
    EXPECT_EQ( "This is a summary of al-Tadhkira bi-uṣūl al-fiqh.", entry->getDescription());
    EXPECT_EQ(category,entry->getCategory());
    std::vector<CorrectionsRequired> correctionsRequired {};
    EXPECT_EQ(correctionsRequired,entry->getCorrectionsRequired());

    EXPECT_EQ(title_type,entry->getTitleType());

    EXPECT_EQ("Abū l-Fatḥ Muḥammad b. ʿAlī b.ʿUthmān al-Ṭarāblūsī al-Karājukī", entry->getAuthor().getName());
    EXPECT_EQ(449,entry->getAuthor().getMDeathHijri());
    EXPECT_EQ("NO DATA",entry->getAuthor().getMDeathHijriText());
    EXPECT_EQ(1057,entry->getAuthor().getMDeathGregorian());
    EXPECT_EQ("NO DATA",entry->getAuthor().getMDeathGregorianText());
    EXPECT_EQ("(d. 449/1057)",entry->getAuthor().getDeathDates()) << "Didn't make the correct death dates string";

}