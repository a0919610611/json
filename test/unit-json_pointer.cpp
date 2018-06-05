#include "gtest/gtest.h"
#define private public
#include "json.hpp"

using nlohmann::json;

namespace
{
	TEST(JSONpointers, JSONpointers)
	{
		//TEST(constructors,"errors")
		{
			EXPECT_THROW(json::json_pointer("foo"), json::parse_error);
			//CHECK_THROWS_WITH(json::json_pointer("foo"),
							  //"[json.exception.parse_error.107] parse error at 1: JSON pointer must be empty or begin with '/' - was: 'foo'");

			EXPECT_THROW(json::json_pointer("/~~"), json::parse_error);
			//CHECK_THROWS_WITH(json::json_pointer("/~~"),
							  //"[json.exception.parse_error.108] parse error: escape character '~' must be followed with '0' or '1'");

			EXPECT_THROW(json::json_pointer("/~"), json::parse_error);
			//CHECK_THROWS_WITH(json::json_pointer("/~"),
							  //"[json.exception.parse_error.108] parse error: escape character '~' must be followed with '0' or '1'");

			json::json_pointer p;
			EXPECT_THROW(p.top(), json::out_of_range);
			//CHECK_THROWS_WITH(p.top(),
							  //"[json.exception.out_of_range.405] JSON pointer has no parent");
			EXPECT_THROW(p.pop_back(), json::out_of_range);
			//CHECK_THROWS_WITH(p.pop_back(),
							  //"[json.exception.out_of_range.405] JSON pointer has no parent");

			//TEST(constructors,"array index error")
			{
				json v = {1, 2, 3, 4};
				json::json_pointer ptr("/10e");
				EXPECT_THROW(v[ptr], json::out_of_range);
				//CHECK_THROWS_WITH(v[ptr],
								  //"[json.exception.out_of_range.404] unresolved reference token '10e'");
			}
		}

		//TEST(constructors,"examples from RFC 6901")
		{
			//TEST(constructors,"nonconst access")
			{
				json j = R"(
				{
					"foo": ["bar", "baz"],
					"": 0,
					"a/b": 1,
					"c%d": 2,
					"e^f": 3,
					"g|h": 4,
					"i\\j": 5,
					"k\"l": 6,
					" ": 7,
					"m~n": 8
				}
				)"_json;

				// the whole document
				EXPECT_TRUE(j[json::json_pointer()] == j);
				EXPECT_TRUE(j[json::json_pointer("")] == j);

				// array access
				EXPECT_TRUE(j[json::json_pointer("/foo")] == j["foo"]);
				EXPECT_TRUE(j[json::json_pointer("/foo/0")] == j["foo"][0]);
				EXPECT_TRUE(j[json::json_pointer("/foo/1")] == j["foo"][1]);
				EXPECT_TRUE(j["/foo/1"_json_pointer] == j["foo"][1]);

				// checked array access
				EXPECT_TRUE(j.at(json::json_pointer("/foo/0")) == j["foo"][0]);
				EXPECT_TRUE(j.at(json::json_pointer("/foo/1")) == j["foo"][1]);

				// empty string access
				EXPECT_TRUE(j[json::json_pointer("/")] == j[""]);

				// other cases
				EXPECT_TRUE(j[json::json_pointer("/ ")] == j[" "]);
				EXPECT_TRUE(j[json::json_pointer("/c%d")] == j["c%d"]);
				EXPECT_TRUE(j[json::json_pointer("/e^f")] == j["e^f"]);
				EXPECT_TRUE(j[json::json_pointer("/g|h")] == j["g|h"]);
				EXPECT_TRUE(j[json::json_pointer("/i\\j")] == j["i\\j"]);
				EXPECT_TRUE(j[json::json_pointer("/k\"l")] == j["k\"l"]);

				// checked access
				EXPECT_TRUE(j.at(json::json_pointer("/ ")) == j[" "]);
				EXPECT_TRUE(j.at(json::json_pointer("/c%d")) == j["c%d"]);
				EXPECT_TRUE(j.at(json::json_pointer("/e^f")) == j["e^f"]);
				EXPECT_TRUE(j.at(json::json_pointer("/g|h")) == j["g|h"]);
				EXPECT_TRUE(j.at(json::json_pointer("/i\\j")) == j["i\\j"]);
				EXPECT_TRUE(j.at(json::json_pointer("/k\"l")) == j["k\"l"]);

				// escaped access
				EXPECT_TRUE(j[json::json_pointer("/a~1b")] == j["a/b"]);
				EXPECT_TRUE(j[json::json_pointer("/m~0n")] == j["m~n"]);

				// unescaped access
				// access to nonexisting values yield object creation
				EXPECT_NO_THROW(j[json::json_pointer("/a/b")] = 42);
				EXPECT_TRUE(j["a"]["b"] == json(42));
				EXPECT_NO_THROW(j[json::json_pointer("/a/c/1")] = 42);
				EXPECT_TRUE(j["a"]["c"] == json({nullptr, 42}));
				EXPECT_NO_THROW(j[json::json_pointer("/a/d/-")] = 42);
				EXPECT_TRUE(j["a"]["d"] == json::array({42}));
				// "/a/b" works for JSON {"a": {"b": 42}}
				EXPECT_TRUE(json({{"a", {{"b", 42}}}})[json::json_pointer("/a/b")] == json(42));

				// unresolved access
				json j_primitive = 1;
				EXPECT_THROW(j_primitive["/foo"_json_pointer], json::out_of_range);
				//CHECK_THROWS_WITH(j_primitive["/foo"_json_pointer],
								  //"[json.exception.out_of_range.404] unresolved reference token 'foo'");
				EXPECT_THROW(j_primitive.at("/foo"_json_pointer), json::out_of_range);
				//CHECK_THROWS_WITH(j_primitive.at("/foo"_json_pointer),
								  //"[json.exception.out_of_range.404] unresolved reference token 'foo'");
			}

			//TEST(constructors,"const access")
			{
				const json j = R"(
				{
					"foo": ["bar", "baz"],
					"": 0,
					"a/b": 1,
					"c%d": 2,
					"e^f": 3,
					"g|h": 4,
					"i\\j": 5,
					"k\"l": 6,
					" ": 7,
					"m~n": 8
				}
				)"_json;

				// the whole document
				EXPECT_TRUE(j[json::json_pointer()] == j);
				EXPECT_TRUE(j[json::json_pointer("")] == j);

				// array access
				EXPECT_TRUE(j[json::json_pointer("/foo")] == j["foo"]);
				EXPECT_TRUE(j[json::json_pointer("/foo/0")] == j["foo"][0]);
				EXPECT_TRUE(j[json::json_pointer("/foo/1")] == j["foo"][1]);
				EXPECT_TRUE(j["/foo/1"_json_pointer] == j["foo"][1]);

				// checked array access
				EXPECT_TRUE(j.at(json::json_pointer("/foo/0")) == j["foo"][0]);
				EXPECT_TRUE(j.at(json::json_pointer("/foo/1")) == j["foo"][1]);

				// empty string access
				EXPECT_TRUE(j[json::json_pointer("/")] == j[""]);

				// other cases
				EXPECT_TRUE(j[json::json_pointer("/ ")] == j[" "]);
				EXPECT_TRUE(j[json::json_pointer("/c%d")] == j["c%d"]);
				EXPECT_TRUE(j[json::json_pointer("/e^f")] == j["e^f"]);
				EXPECT_TRUE(j[json::json_pointer("/g|h")] == j["g|h"]);
				EXPECT_TRUE(j[json::json_pointer("/i\\j")] == j["i\\j"]);
				EXPECT_TRUE(j[json::json_pointer("/k\"l")] == j["k\"l"]);

				// checked access
				EXPECT_TRUE(j.at(json::json_pointer("/ ")) == j[" "]);
				EXPECT_TRUE(j.at(json::json_pointer("/c%d")) == j["c%d"]);
				EXPECT_TRUE(j.at(json::json_pointer("/e^f")) == j["e^f"]);
				EXPECT_TRUE(j.at(json::json_pointer("/g|h")) == j["g|h"]);
				EXPECT_TRUE(j.at(json::json_pointer("/i\\j")) == j["i\\j"]);
				EXPECT_TRUE(j.at(json::json_pointer("/k\"l")) == j["k\"l"]);

				// escaped access
				EXPECT_TRUE(j[json::json_pointer("/a~1b")] == j["a/b"]);
				EXPECT_TRUE(j[json::json_pointer("/m~0n")] == j["m~n"]);

				// unescaped access
				EXPECT_THROW(j.at(json::json_pointer("/a/b")), json::out_of_range);
				//CHECK_THROWS_WITH(j.at(json::json_pointer("/a/b")),
								  //"[json.exception.out_of_range.403] key 'a' not found");

				// unresolved access
				const json j_primitive = 1;
				EXPECT_THROW(j_primitive["/foo"_json_pointer], json::out_of_range);
				//CHECK_THROWS_WITH(j_primitive["/foo"_json_pointer],
								  //"[json.exception.out_of_range.404] unresolved reference token 'foo'");
				EXPECT_THROW(j_primitive.at("/foo"_json_pointer), json::out_of_range);
				//CHECK_THROWS_WITH(j_primitive.at("/foo"_json_pointer),
								  //"[json.exception.out_of_range.404] unresolved reference token 'foo'");
			}

			//TEST(constructors,"user-defined string literal")
			{
				json j = R"(
				{
					"foo": ["bar", "baz"],
					"": 0,
					"a/b": 1,
					"c%d": 2,
					"e^f": 3,
					"g|h": 4,
					"i\\j": 5,
					"k\"l": 6,
					" ": 7,
					"m~n": 8
				}
				)"_json;

				// the whole document
				EXPECT_TRUE(j[""_json_pointer] == j);

				// array access
				EXPECT_TRUE(j["/foo"_json_pointer] == j["foo"]);
				EXPECT_TRUE(j["/foo/0"_json_pointer] == j["foo"][0]);
				EXPECT_TRUE(j["/foo/1"_json_pointer] == j["foo"][1]);
			}
		}

		//TEST(constructors,"array access")
		{
			//TEST(constructors,"nonconst access")
			{
				json j = {1, 2, 3};
				const json j_const = j;

				// check reading access
				EXPECT_TRUE(j["/0"_json_pointer] == j[0]);
				EXPECT_TRUE(j["/1"_json_pointer] == j[1]);
				EXPECT_TRUE(j["/2"_json_pointer] == j[2]);

				// assign to existing index
				j["/1"_json_pointer] = 13;
				EXPECT_TRUE(j[1] == json(13));

				// assign to nonexisting index
				j["/3"_json_pointer] = 33;
				EXPECT_TRUE(j[3] == json(33));

				// assign to nonexisting index (with gap)
				j["/5"_json_pointer] = 55;
				EXPECT_TRUE(j == json({1, 13, 3, 33, nullptr, 55}));

				// error with leading 0
				EXPECT_THROW(j["/01"_json_pointer], json::parse_error);
				//CHECK_THROWS_WITH(j["/01"_json_pointer],
								  //"[json.exception.parse_error.106] parse error: array index '01' must not begin with '0'");
				EXPECT_THROW(j_const["/01"_json_pointer], json::parse_error);
				//CHECK_THROWS_WITH(j_const["/01"_json_pointer],
								  //"[json.exception.parse_error.106] parse error: array index '01' must not begin with '0'");
				EXPECT_THROW(j.at("/01"_json_pointer), json::parse_error);
				//CHECK_THROWS_WITH(j.at("/01"_json_pointer),
								  //"[json.exception.parse_error.106] parse error: array index '01' must not begin with '0'");
				EXPECT_THROW(j_const.at("/01"_json_pointer), json::parse_error);
				//CHECK_THROWS_WITH(j_const.at("/01"_json_pointer),
								  //"[json.exception.parse_error.106] parse error: array index '01' must not begin with '0'");

				// error with incorrect numbers
				EXPECT_THROW(j["/one"_json_pointer] = 1, json::parse_error);
				//CHECK_THROWS_WITH(j["/one"_json_pointer] = 1,
								  //"[json.exception.parse_error.109] parse error: array index 'one' is not a number");
				EXPECT_THROW(j_const["/one"_json_pointer] == 1, json::parse_error);
				//CHECK_THROWS_WITH(j_const["/one"_json_pointer] == 1,
								  //"[json.exception.parse_error.109] parse error: array index 'one' is not a number");

				EXPECT_THROW(j.at("/one"_json_pointer) = 1, json::parse_error);
				//CHECK_THROWS_WITH(j.at("/one"_json_pointer) = 1,
								  //"[json.exception.parse_error.109] parse error: array index 'one' is not a number");
				EXPECT_THROW(j_const.at("/one"_json_pointer) == 1, json::parse_error);
				//CHECK_THROWS_WITH(j_const.at("/one"_json_pointer) == 1,
								  //"[json.exception.parse_error.109] parse error: array index 'one' is not a number");

				EXPECT_THROW(json({{"/list/0", 1}, {"/list/1", 2}, {"/list/three", 3}}).unflatten(), json::parse_error);
				//CHECK_THROWS_WITH(json({{"/list/0", 1}, {"/list/1", 2}, {"/list/three", 3}}).unflatten(),
				//"[json.exception.parse_error.109] parse error: array index 'three' is not a number");

				// assign to "-"
				j["/-"_json_pointer] = 99;
				EXPECT_TRUE(j == json({1, 13, 3, 33, nullptr, 55, 99}));

				// error when using "-" in const object
				EXPECT_THROW(j_const["/-"_json_pointer], json::out_of_range);
				//CHECK_THROWS_WITH(j_const["/-"_json_pointer],
								  //"[json.exception.out_of_range.402] array index '-' (3) is out of range");

				// error when using "-" with at
				EXPECT_THROW(j.at("/-"_json_pointer), json::out_of_range);
				//CHECK_THROWS_WITH(j.at("/-"_json_pointer),
								  //"[json.exception.out_of_range.402] array index '-' (7) is out of range");
				EXPECT_THROW(j_const.at("/-"_json_pointer), json::out_of_range);
				//CHECK_THROWS_WITH(j_const.at("/-"_json_pointer),
								  //"[json.exception.out_of_range.402] array index '-' (3) is out of range");
			}

			//TEST(constructors,"const access")
			{
				const json j = {1, 2, 3};

				// check reading access
				EXPECT_TRUE(j["/0"_json_pointer] == j[0]);
				EXPECT_TRUE(j["/1"_json_pointer] == j[1]);
				EXPECT_TRUE(j["/2"_json_pointer] == j[2]);

				// assign to nonexisting index
				EXPECT_THROW(j.at("/3"_json_pointer), json::out_of_range);
				//CHECK_THROWS_WITH(j.at("/3"_json_pointer),
								  //"[json.exception.out_of_range.401] array index 3 is out of range");

				// assign to nonexisting index (with gap)
				EXPECT_THROW(j.at("/5"_json_pointer), json::out_of_range);
				//CHECK_THROWS_WITH(j.at("/5"_json_pointer),
								  //"[json.exception.out_of_range.401] array index 5 is out of range");

				// assign to "-"
				EXPECT_THROW(j["/-"_json_pointer], json::out_of_range);
				//CHECK_THROWS_WITH(j["/-"_json_pointer],
								  //"[json.exception.out_of_range.402] array index '-' (3) is out of range");
				EXPECT_THROW(j.at("/-"_json_pointer), json::out_of_range);
				//CHECK_THROWS_WITH(j.at("/-"_json_pointer),
								  //"[json.exception.out_of_range.402] array index '-' (3) is out of range");
			}

		}

		//TEST(constructors,"flatten")
		{
			json j =
			{
				{"pi", 3.141},
				{"happy", true},
				{"name", "Niels"},
				{"nothing", nullptr},
				{
					"answer", {
						{"everything", 42}
					}
				},
				{"list", {1, 0, 2}},
				{
					"object", {
						{"currency", "USD"},
						{"value", 42.99},
						{"", "empty string"},
						{"/", "slash"},
						{"~", "tilde"},
						{"~1", "tilde1"}
					}
				}
			};

			json j_flatten =
			{
				{"/pi", 3.141},
				{"/happy", true},
				{"/name", "Niels"},
				{"/nothing", nullptr},
				{"/answer/everything", 42},
				{"/list/0", 1},
				{"/list/1", 0},
				{"/list/2", 2},
				{"/object/currency", "USD"},
				{"/object/value", 42.99},
				{"/object/", "empty string"},
				{"/object/~1", "slash"},
				{"/object/~0", "tilde"},
				{"/object/~01", "tilde1"}
			};

			// check if flattened result is as expected
			EXPECT_TRUE(j.flatten() == j_flatten);

			// check if unflattened result is as expected
			EXPECT_TRUE(j_flatten.unflatten() == j);

			// error for nonobjects
			EXPECT_THROW(json(1).unflatten(), json::type_error);
			//CHECK_THROWS_WITH(json(1).unflatten(),
							  //"[json.exception.type_error.314] only objects can be unflattened");

			// error for nonprimitve values
			EXPECT_THROW(json({{"/1", {1, 2, 3}}}).unflatten(), json::type_error);
			//CHECK_THROWS_WITH(json({{"/1", {1, 2, 3}}}).unflatten(),
			//"[json.exception.type_error.315] values in object must be primitive");

			// error for conflicting values
			json j_error = {{"", 42}, {"/foo", 17}};
			EXPECT_THROW(j_error.unflatten(), json::type_error);
			//CHECK_THROWS_WITH(j_error.unflatten(),
							  //"[json.exception.type_error.313] invalid value to unflatten");

			// explicit roundtrip check
			EXPECT_TRUE(j.flatten().unflatten() == j);

			// roundtrip for primitive values
			json j_null;
			EXPECT_TRUE(j_null.flatten().unflatten() == j_null);
			json j_number = 42;
			EXPECT_TRUE(j_number.flatten().unflatten() == j_number);
			json j_boolean = false;
			EXPECT_TRUE(j_boolean.flatten().unflatten() == j_boolean);
			json j_string = "foo";
			EXPECT_TRUE(j_string.flatten().unflatten() == j_string);

			// roundtrip for empty structured values (will be unflattened to null)
			json j_array(json::value_t::array);
			EXPECT_TRUE(j_array.flatten().unflatten() == json());
			json j_object(json::value_t::object);
			EXPECT_TRUE(j_object.flatten().unflatten() == json());
		}

		//TEST(constructors,"string representation")
		{
			for (auto ptr :
					{"", "/foo", "/foo/0", "/", "/a~1b", "/c%d", "/e^f", "/g|h", "/i\\j", "/k\"l", "/ ", "/m~0n"
					})
			{
				EXPECT_TRUE(json::json_pointer(ptr).to_string() == ptr);
			}
		}

		//TEST(constructors,"conversion")
		{
			//TEST(constructors,"array")
			{
				json j;
				// all numbers -> array
				j["/12"_json_pointer] = 0;
				EXPECT_TRUE(j.is_array());
			}

			//TEST(constructors,"object")
			{
				json j;
				// contains a number, but is not a number -> object
				j["/a12"_json_pointer] = 0;
				EXPECT_TRUE(j.is_object());
			}
		}
	}
}
