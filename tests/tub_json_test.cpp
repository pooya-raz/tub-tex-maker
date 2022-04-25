//
// Created by pooya on 4/25/22.
//
#include <gtest/gtest.h>
#include "../src/tub_json.h"
#include <fstream>

class TubJsonTest : public ::testing::Test
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

nlohmann::json TubJsonTest::json = nlohmann::json::value_t::array;

TEST_F(TubJsonTest, BasicAssertions) {
    /*
     * Test to see if I can get a single title, and that it is in UTF-8
     */

    auto results = TubJsonTest::json["query"]["results"];
    std::string result = "";
    for(nlohmann::json entry: results)
    {
        result += entry["printouts"]["Title (Arabic)"][0];
    }
    std::string expected = "بحث في) أصول الفقه)";
    EXPECT_EQ(expected, result);
}