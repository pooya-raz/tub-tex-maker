//
// Created by pooya on 4/25/22.
//
#include <gtest/gtest.h>
#include "../TubJson.h"
#include <fstream>
#include "./entry_manager.h"
#include <iterator>
#include <algorithm>

class EntryBuilderTest : public ::testing::Test {
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
            std::ifstream file("/Users/pooya/Developer/sandbox/cpp/tub-tex-maker/tests/1000response.json");
            std::string json_string((std::istreambuf_iterator<char>(file)),
                                    (std::istreambuf_iterator<char>()));
            tubJson.parse(json_string);
            auto results = tubJson.at("query").at("results");
            EntryManager entryManager;
            entryManager.add_entries(results);


            std::ifstream fileManuscript(
                    "/Users/pooya/Developer/sandbox/cpp/tub-tex-maker/tests/response-manuscript.json");
            std::string json_string_manuscript((std::istreambuf_iterator<char>(fileManuscript)),
                                               (std::istreambuf_iterator<char>()));
            TubJson tubManuscriptJson;
            tubManuscriptJson.parse(json_string_manuscript);
            auto manu_results = tubManuscriptJson.at("query").at("results");
            entryManager.add_manuscripts(manu_results);

            std::ifstream file_editions(
                    "/Users/pooya/Developer/sandbox/cpp/tub-tex-maker/tests/response-editions.json");
            std::string json_string_editions((std::istreambuf_iterator<char>(file_editions)),
                                             (std::istreambuf_iterator<char>()));
            TubJson tubEditionJson;
            tubEditionJson.parse(json_string_editions);
            auto edition_results = tubEditionJson.at("query").at("results");
            entryManager.add_editions(edition_results);

            /*
             * Add authors
             */
            std::ifstream file_authors("/Users/pooya/Developer/sandbox/cpp/tub-tex-maker/tests/authors.json");
            std::string json_string_authors((std::istreambuf_iterator<char>(file_authors)),
                                            (std::istreambuf_iterator<char>()));
            TubJson tubAuthors;
            tubAuthors.parse(json_string_authors);
            auto authors = tubAuthors.at("query").at("results");
            entryManager.add_authors(authors);

            entryManager.sort_all();
            entryMap = entryManager.getEntryMap();
        }
    }

    // Some expensive resource shared by all tests.
    static EntryMap &entryMap;
};

EntryMap emptyMap;
EntryMap &EntryBuilderTest::entryMap = emptyMap;


auto find_by_id = [](const std::vector<std::shared_ptr<Entry>> &entryMap, const std::string &id) {
    auto by_id = [&](const std::shared_ptr<Entry> &entry) {
        return entry->getId() == id;
    };
    const auto &entryIterator = std::find_if(begin(entryMap), end(entryMap), by_id);
    return entryIterator->get();
};

TEST_F(EntryBuilderTest, NoDatesNoDescription) {
    /*
     * Test to see if I can get a single title, and that it is in UTF-8
     */
    Category category{ManuscriptOnly};
    TitleType title_type{Treatise};
    const auto entryMap = EntryBuilderTest::entryMap[title_type];
    auto entry = find_by_id(entryMap, "(Bahth fī) uṣūl al-fiqh");
    EXPECT_EQ("بحث في) أصول الفقه)", entry->getTitleArabic());
    EXPECT_EQ("(Bahth fī) uṣūl al-fiqh", entry->getTitleTransliterated());
    EXPECT_EQ("(Bahth fī) uṣūl al-fiqh", entry->getId());
    EXPECT_EQ("NO DATA", entry->getDescription());
    EXPECT_EQ(category, entry->getCategory());
    EXPECT_EQ(title_type, entry->getTitleType());

    std::vector<CorrectionsRequired> correctionsRequired{CheckDates};
    EXPECT_EQ(correctionsRequired, entry->getCorrectionsRequired());

    EXPECT_EQ("Murtaḍā al-Ḥusaynī", entry->getAuthor().getName());
    EXPECT_EQ(0, entry->getAuthor().getMDeathHijri());
    EXPECT_EQ("NO DATA", entry->getAuthor().getMDeathHijriText());
    EXPECT_EQ(0, entry->getAuthor().getMDeathGregorian());
    EXPECT_EQ("NO DATA", entry->getAuthor().getMDeathGregorianText());

    EXPECT_EQ("(d. NO DATA/NO DATA)", entry->getAuthor().getDeathDates())
                        << "Didn't make the correct death dates string";
}


TEST_F(EntryBuilderTest, WithDatesAndDescription) {
    /*
     * Test to see if I can get a single title, and that it is in UTF-8
     */
    Category category{Edited};
    TitleType title_type{Summary};
    const auto entryMap = EntryBuilderTest::entryMap[title_type];
    auto entry = find_by_id(entryMap, "(Mukhtaṣar) al-Tadhkira bi-uṣul al-fiqh");
    EXPECT_EQ("مختصر) التذكرة بأصول الفقه)", entry->getTitleArabic());
    EXPECT_EQ("(Mukhtaṣar) al-Tadhkira bi-uṣul al-fiqh", entry->getTitleTransliterated());
    EXPECT_EQ("(Mukhtaṣar) al-Tadhkira bi-uṣul al-fiqh", entry->getId());
    EXPECT_EQ("This is a summary of al-Tadhkira bi-uṣūl al-fiqh.", entry->getDescription());
    EXPECT_EQ(category, entry->getCategory());
    std::vector<CorrectionsRequired> correctionsRequired{};
    EXPECT_EQ(correctionsRequired, entry->getCorrectionsRequired());

    EXPECT_EQ(title_type, entry->getTitleType());

    EXPECT_EQ("al-Karājukī/al-Karājakī al-Ṭarāblūsī", entry->getAuthor().getName());
    EXPECT_EQ(449, entry->getAuthor().getMDeathHijri());
    EXPECT_EQ("NO DATA", entry->getAuthor().getMDeathHijriText());
    EXPECT_EQ(1057, entry->getAuthor().getMDeathGregorian());
    EXPECT_EQ("NO DATA", entry->getAuthor().getMDeathGregorianText());
    EXPECT_EQ("(d. 449/1057)", entry->getAuthor().getDeathDates()) << "Didn't make the correct death dates string";

    //Test manuscripts
    EXPECT_EQ(1, entry->manuscripts.size());
    EXPECT_EQ("(Mukhtaṣar) al-Tadhkira bi-uṣul al-fiqh", entry->manuscripts[0].getManuscriptOfTitle());

    EXPECT_EQ(3, entry->editions.size());
}