#include "json.hpp"
#include "gtest/gtest.h"

using json = nlohmann::json;

TEST(serialization, operator_in) {
  {
    std::stringstream ss;
    json j = {"foo", 1, 2, 3, false, {{"one", 1}}};
    ss << j;
    EXPECT_EQ(ss.str(), "[\"foo\",1,2,3,false,{\"one\":1}]");
  }
  {
    std::stringstream ss;
    json j = {"foo", 1, 2, 3, false, {{"one", 1}}};
    ss << std::setw(4) << j;
    EXPECT_EQ(ss.str(),
              "[\n    \"foo\",\n    1,\n    2,\n    3,\n    false,\n   "
              " {\n        \"one\": 1\n    }\n]");
  }
  {
    std::stringstream ss;
    json j = {"foo", 1, 2, 3, false, {{"one", 1}}};
    ss << std::setw(1) << std::setfill('\t') << j;
    EXPECT_EQ(ss.str(), "[\n\t\"foo\",\n\t1,\n\t2,\n\t3,\n\tfalse,\n\t{"
                        "\n\t\t\"one\": 1\n\t}\n]");
  }
}
TEST(serialization, operator_out) {
  {
    std::stringstream ss;
    json j = {"foo", 1, 2, 3, false, {{"one", 1}}};
    j >> ss;
    EXPECT_EQ(ss.str(), "[\"foo\",1,2,3,false,{\"one\":1}]");
  }

  {
    std::stringstream ss;
    json j = {"foo", 1, 2, 3, false, {{"one", 1}}};
    ss.width(4);
    j >> ss;
    EXPECT_EQ(ss.str(),
              "[\n    \"foo\",\n    1,\n    2,\n    3,\n    false,\n   "
              " {\n        \"one\": 1\n    }\n]");
  }

  {
    std::stringstream ss;
    json j = {"foo", 1, 2, 3, false, {{"one", 1}}};
    ss.width(1);
    ss.fill('\t');
    j >> ss;
    EXPECT_EQ(ss.str(), "[\n\t\"foo\",\n\t1,\n\t2,\n\t3,\n\tfalse,\n\t{"
                        "\n\t\t\"one\": 1\n\t}\n]");
  }
}
