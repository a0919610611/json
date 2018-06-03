#include "json.hpp"
#include "gtest/gtest.h"

using json = nlohmann::json;

TEST(meta,version_information)
{
    json j = json::meta();

    EXPECT_EQ(j["name"], "JSON for Modern C++");
    EXPECT_EQ(j["copyright"] , "(C) 2013-2017 Niels Lohmann");
    EXPECT_EQ(j["url"] , "https://github.com/nlohmann/json");
    EXPECT_EQ(j["version"] , json(
    {
        {"string", "3.1.2"},
        {"major", 3},
        {"minor", 1},
        {"patch", 2}
    }));

    EXPECT_NE(j.find("platform"), j.end());
    EXPECT_NE(j.at("compiler").find("family") , j.at("compiler").end());
    EXPECT_NE(j.at("compiler").find("version") , j.at("compiler").end());
    EXPECT_NE(j.at("compiler").find("c++") , j.at("compiler").end());
}
