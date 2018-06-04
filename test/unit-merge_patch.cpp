#include "json.hpp"
#include "gtest/gtest.h"

using json = nlohmann::json;

TEST(JSON_Merge_Patch,SomeTest)
{
        {
            json document = R"({
                "a": "b",
                "c": {
                    "d": "e",
                    "f": "g"
                }
            })"_json;

            json patch = R"({
                "a": "z",
                "c": {
                    "f": null
                }
            })"_json;

            json expected = R"({
                "a": "z",
                "c": {
                    "d": "e"
                }
            })"_json;

            document.merge_patch(patch);
            EXPECT_EQ(document , expected);
        }

        {
            json document = R"({
                "title": "Goodbye!",
                "author": {
                    "givenName": "John",
                    "familyName": "Doe"
                },
                "tags": [
                    "example",
                    "sample"
                ],
                "content": "This will be unchanged"
            })"_json;

            json patch = R"({
                "title": "Hello!",
                "phoneNumber": "+01-123-456-7890",
                "author": {
                    "familyName": null
                },
                "tags": [
                    "example"
                ]
            })"_json;

            json expected = R"({
                "title": "Hello!",
                "author": {
                    "givenName": "John"
                },
                "tags": [
                    "example"
                ],
                "content": "This will be unchanged",
                "phoneNumber": "+01-123-456-7890"
            })"_json;

            document.merge_patch(patch);
            EXPECT_EQ(document ,expected);
        }

        {
            {
                json original = R"({"a":"b"})"_json;
                json patch = R"({"a":"c"})"_json;
                json result = R"({"a":"c"})"_json;

                original.merge_patch(patch);
                EXPECT_EQ(original , result);
            }

            {
                json original = R"({"a":"b"})"_json;
                json patch = R"({"b":"c"})"_json;
                json result = R"({"a":"b", "b":"c"})"_json;

                original.merge_patch(patch);
                EXPECT_EQ(original , result);
            }

            {
                json original = R"({"a":"b"})"_json;
                json patch = R"({"a":null})"_json;
                json result = R"({})"_json;

                original.merge_patch(patch);
                EXPECT_EQ(original , result);
            }

            {
                json original = R"({"a":"b","b":"c"})"_json;
                json patch = R"({"a":null})"_json;
                json result = R"({"b":"c"})"_json;

                original.merge_patch(patch);
                EXPECT_EQ(original , result);
            }

            {
                json original = R"({"a":["b"]})"_json;
                json patch = R"({"a":"c"})"_json;
                json result = R"({"a":"c"})"_json;

                original.merge_patch(patch);
                EXPECT_EQ(original , result);
            }

            {
                json original = R"({"a":"c"})"_json;
                json patch = R"({"a":["b"]})"_json;
                json result = R"({"a":["b"]})"_json;

                original.merge_patch(patch);
                EXPECT_EQ(original , result);
            }

            {
                json original = R"({"a":{"b": "c"}})"_json;
                json patch = R"({"a":{"b":"d","c":null}})"_json;
                json result = R"({"a": {"b": "d"}})"_json;

                original.merge_patch(patch);
                EXPECT_EQ(original , result);
            }

            {
                json original = R"({"a":[{"b":"c"}]})"_json;
                json patch = R"({"a":[1]})"_json;
                json result = R"({"a":[1]})"_json;

                original.merge_patch(patch);
                EXPECT_EQ(original , result);
            }

            {
                json original = R"(["a","b"])"_json;
                json patch = R"(["c","d"])"_json;
                json result = R"(["c","d"])"_json;

                original.merge_patch(patch);
                EXPECT_EQ(original , result);
            }

            {
                json original = R"({"a":"b"})"_json;
                json patch = R"(["c"])"_json;
                json result = R"(["c"])"_json;

                original.merge_patch(patch);
                EXPECT_EQ(original , result);
            }

            {
                json original = R"({"a":"foo"})"_json;
                json patch = R"(null)"_json;
                json result = R"(null)"_json;

                original.merge_patch(patch);
                EXPECT_EQ(original , result);
            }

            {
                json original = R"({"a":"foo"})"_json;
                json patch = R"("bar")"_json;
                json result = R"("bar")"_json;

                original.merge_patch(patch);
                EXPECT_EQ(original , result);
            }

            {
                json original = R"({"e":null})"_json;
                json patch = R"({"a":1})"_json;
                json result = R"({"e":null,"a":1})"_json;

                original.merge_patch(patch);
                EXPECT_EQ(original , result);
            }

            {
                json original = R"([1,2])"_json;
                json patch = R"({"a":"b","c":null})"_json;
                json result = R"({"a":"b"})"_json;

                original.merge_patch(patch);
                EXPECT_EQ(original , result);
            }

            {
                json original = R"({})"_json;
                json patch = R"({"a":{"bb":{"ccc":null}}})"_json;
                json result = R"({"a":{"bb":{}}})"_json;

                original.merge_patch(patch);
                EXPECT_EQ(original , result);
            }
        }
}
