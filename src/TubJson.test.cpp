//
// Created by pooya on 4/28/22.
//
#include <gtest/gtest.h>
#include "TubJson.h"

TEST(TubJsonTest, BASIC) {
    TubJson tubJson;
    tubJson.parse(R"({"name":"John", "age":30, "car":null})");
    EXPECT_EQ("John",tubJson.get("name"));
}

TEST(TubJsonTest, NO_VALUE) {
    TubJson tubJson;
    tubJson.parse(R"({"age":30, "car":null})");
    EXPECT_EQ("NO DATA",tubJson.get("name"));
}

TEST(TubJsonTest, Nested) {
    TubJson tubJson;
    tubJson.parse(R"({"isbn": "123-456-222",
 "author":
    {
      "lastname": "Doe",
      "firstname": "Jane"
    },
"editor":
    {
      "lastname": "Smith",
      "firstname": "Jane"
    },
  "title": "The Ultimate Database Study Guide",
  "category": ["Non-Fiction", "Technology"]
 })");
    EXPECT_EQ("Doe",tubJson.at("author").get("lastname"));
    EXPECT_EQ("Smith",tubJson.at("editor").get("lastname"));

}

TEST(TubJsonTest, NestedArray) {
    TubJson tubJson;
    tubJson.parse(R"({"isbn": "123-456-222",
 "author":
    ["Doe"],
"editor":
    [ "Smith", "Jane" ],
  "title": "The Ultimate Database Study Guide",
  "category": ["Non-Fiction", "Technology"]
 })");
    EXPECT_EQ("Doe",tubJson.at("author").get(0));
    EXPECT_EQ("Jane",tubJson.at("editor").get(1));
}

TEST(TubJsonTest, ObjectArrayObject) {
    TubJson tubJson;
    tubJson.parse(R"({ "author": [ { "lastname":"Doe" } ] })");
    EXPECT_EQ("Doe",tubJson.at("author").at(0).get("lastname"));


}