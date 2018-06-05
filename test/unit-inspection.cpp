#include "gtest/gtest.h"
#include <fstream>
#include "json.hpp"

using nlohmann::json;

namespace
{
	TEST(inspection, inspection)
	{
		//TEST(constructors,"convenience type checker")
		{
			//TEST(constructors,"object")
			{
				json j {{"foo", 1}, {"bar", false}};
				EXPECT_TRUE(not j.is_null());
				EXPECT_TRUE(not j.is_boolean());
				EXPECT_TRUE(not j.is_number());
				EXPECT_TRUE(not j.is_number_integer());
				EXPECT_TRUE(not j.is_number_unsigned());
				EXPECT_TRUE(not j.is_number_float());
				EXPECT_TRUE(j.is_object());
				EXPECT_TRUE(not j.is_array());
				EXPECT_TRUE(not j.is_string());
				EXPECT_TRUE(not j.is_discarded());
				EXPECT_TRUE(not j.is_primitive());
				EXPECT_TRUE(j.is_structured());
			}

			//TEST(constructors,"array")
			{
				json j {"foo", 1, 1u, 42.23, false};
				EXPECT_TRUE(not j.is_null());
				EXPECT_TRUE(not j.is_boolean());
				EXPECT_TRUE(not j.is_number());
				EXPECT_TRUE(not j.is_number_integer());
				EXPECT_TRUE(not j.is_number_unsigned());
				EXPECT_TRUE(not j.is_number_float());
				EXPECT_TRUE(not j.is_object());
				EXPECT_TRUE(j.is_array());
				EXPECT_TRUE(not j.is_string());
				EXPECT_TRUE(not j.is_discarded());
				EXPECT_TRUE(not j.is_primitive());
				EXPECT_TRUE(j.is_structured());
			}

			//TEST(constructors,"null")
			{
				json j(nullptr);
				EXPECT_TRUE(j.is_null());
				EXPECT_TRUE(not j.is_boolean());
				EXPECT_TRUE(not j.is_number());
				EXPECT_TRUE(not j.is_number_integer());
				EXPECT_TRUE(not j.is_number_unsigned());
				EXPECT_TRUE(not j.is_number_float());
				EXPECT_TRUE(not j.is_object());
				EXPECT_TRUE(not j.is_array());
				EXPECT_TRUE(not j.is_string());
				EXPECT_TRUE(not j.is_discarded());
				EXPECT_TRUE(j.is_primitive());
				EXPECT_TRUE(not j.is_structured());
			}

			//TEST(constructors,"boolean")
			{
				json j(true);
				EXPECT_TRUE(not j.is_null());
				EXPECT_TRUE(j.is_boolean());
				EXPECT_TRUE(not j.is_number());
				EXPECT_TRUE(not j.is_number_integer());
				EXPECT_TRUE(not j.is_number_unsigned());
				EXPECT_TRUE(not j.is_number_float());
				EXPECT_TRUE(not j.is_object());
				EXPECT_TRUE(not j.is_array());
				EXPECT_TRUE(not j.is_string());
				EXPECT_TRUE(not j.is_discarded());
				EXPECT_TRUE(j.is_primitive());
				EXPECT_TRUE(not j.is_structured());
			}

			//TEST(constructors,"string")
			{
				json j("Hello world");
				EXPECT_TRUE(not j.is_null());
				EXPECT_TRUE(not j.is_boolean());
				EXPECT_TRUE(not j.is_number());
				EXPECT_TRUE(not j.is_number_integer());
				EXPECT_TRUE(not j.is_number_unsigned());
				EXPECT_TRUE(not j.is_number_float());
				EXPECT_TRUE(not j.is_object());
				EXPECT_TRUE(not j.is_array());
				EXPECT_TRUE(j.is_string());
				EXPECT_TRUE(not j.is_discarded());
				EXPECT_TRUE(j.is_primitive());
				EXPECT_TRUE(not j.is_structured());
			}

			//TEST(constructors,"number (integer)")
			{
				json j(42);
				EXPECT_TRUE(not j.is_null());
				EXPECT_TRUE(not j.is_boolean());
				EXPECT_TRUE(j.is_number());
				EXPECT_TRUE(j.is_number_integer());
				EXPECT_TRUE(not j.is_number_unsigned());
				EXPECT_TRUE(not j.is_number_float());
				EXPECT_TRUE(not j.is_object());
				EXPECT_TRUE(not j.is_array());
				EXPECT_TRUE(not j.is_string());
				EXPECT_TRUE(not j.is_discarded());
				EXPECT_TRUE(j.is_primitive());
				EXPECT_TRUE(not j.is_structured());
			}

			//TEST(constructors,"number (unsigned)")
			{
				json j(42u);
				EXPECT_TRUE(not j.is_null());
				EXPECT_TRUE(not j.is_boolean());
				EXPECT_TRUE(j.is_number());
				EXPECT_TRUE(j.is_number_integer());
				EXPECT_TRUE(j.is_number_unsigned());
				EXPECT_TRUE(not j.is_number_float());
				EXPECT_TRUE(not j.is_object());
				EXPECT_TRUE(not j.is_array());
				EXPECT_TRUE(not j.is_string());
				EXPECT_TRUE(not j.is_discarded());
				EXPECT_TRUE(j.is_primitive());
				EXPECT_TRUE(not j.is_structured());
			}

			//TEST(constructors,"number (floating-point)")
			{
				json j(42.23);
				EXPECT_TRUE(not j.is_null());
				EXPECT_TRUE(not j.is_boolean());
				EXPECT_TRUE(j.is_number());
				EXPECT_TRUE(not j.is_number_integer());
				EXPECT_TRUE(not j.is_number_unsigned());
				EXPECT_TRUE(j.is_number_float());
				EXPECT_TRUE(not j.is_object());
				EXPECT_TRUE(not j.is_array());
				EXPECT_TRUE(not j.is_string());
				EXPECT_TRUE(not j.is_discarded());
				EXPECT_TRUE(j.is_primitive());
				EXPECT_TRUE(not j.is_structured());
			}

			//TEST(constructors,"discarded")
			{
				json j(json::value_t::discarded);
				EXPECT_TRUE(not j.is_null());
				EXPECT_TRUE(not j.is_boolean());
				EXPECT_TRUE(not j.is_number());
				EXPECT_TRUE(not j.is_number_integer());
				EXPECT_TRUE(not j.is_number_unsigned());
				EXPECT_TRUE(not j.is_number_float());
				EXPECT_TRUE(not j.is_object());
				EXPECT_TRUE(not j.is_array());
				EXPECT_TRUE(not j.is_string());
				EXPECT_TRUE(j.is_discarded());
				EXPECT_TRUE(not j.is_primitive());
				EXPECT_TRUE(not j.is_structured());
			}
		}

		//TEST(constructors,"serialization")
		{
			json j {{"object", json::object()}, {"array", {1, 2, 3, 4}}, {"number", 42}, {"boolean", false}, {"null", nullptr}, {"string", "Hello world"} };

			//TEST(constructors,"no indent / indent=-1")
			{
				EXPECT_TRUE(j.dump() ==
					  "{\"array\":[1,2,3,4],\"boolean\":false,\"null\":null,\"number\":42,\"object\":{},\"string\":\"Hello world\"}");

				EXPECT_TRUE(j.dump() == j.dump(-1));
			}

			//TEST(constructors,"indent=0")
			{
				EXPECT_TRUE(j.dump(0) ==
					  "{\n\"array\": [\n1,\n2,\n3,\n4\n],\n\"boolean\": false,\n\"null\": null,\n\"number\": 42,\n\"object\": {},\n\"string\": \"Hello world\"\n}");
			}

			//TEST(constructors,"indent=1, space='\t'")
			{
				EXPECT_TRUE(j.dump(1, '\t') ==
					  "{\n\t\"array\": [\n\t\t1,\n\t\t2,\n\t\t3,\n\t\t4\n\t],\n\t\"boolean\": false,\n\t\"null\": null,\n\t\"number\": 42,\n\t\"object\": {},\n\t\"string\": \"Hello world\"\n}");
			}

			//TEST(constructors,"indent=4")
			{
				EXPECT_TRUE(j.dump(4) ==
					  "{\n    \"array\": [\n        1,\n        2,\n        3,\n        4\n    ],\n    \"boolean\": false,\n    \"null\": null,\n    \"number\": 42,\n    \"object\": {},\n    \"string\": \"Hello world\"\n}");
			}

			//TEST(constructors,"indent=x")
			{
				EXPECT_TRUE(j.dump().size() == 94);
				EXPECT_TRUE(j.dump(1).size() == 127);
				EXPECT_TRUE(j.dump(2).size() == 142);
				EXPECT_TRUE(j.dump(512).size() == 7792);

				// important test, because it yields a resize of the indent_string
				// inside the dump() function
				EXPECT_TRUE(j.dump(1024).size() == 15472);
			}

			//TEST(constructors,"dump and floating-point numbers")
			{
				auto s = json(42.23).dump();
				EXPECT_TRUE(s.find("42.23") != std::string::npos);
			}

			//TEST(constructors,"dump and small floating-point numbers")
			{
				auto s = json(1.23456e-78).dump();
				EXPECT_TRUE(s.find("1.23456e-78") != std::string::npos);
			}

			//TEST(constructors,"dump and non-ASCII characters")
			{
				EXPECT_TRUE(json("ä").dump() == "\"ä\"");
				EXPECT_TRUE(json("Ö").dump() == "\"Ö\"");
				EXPECT_TRUE(json("❤️").dump() == "\"❤️\"");
			}

			//TEST(constructors,"dump with ensure_ascii and non-ASCII characters")
			{
				EXPECT_TRUE(json("ä").dump(-1, ' ', true) == "\"\\u00e4\"");
				EXPECT_TRUE(json("Ö").dump(-1, ' ', true) == "\"\\u00d6\"");
				EXPECT_TRUE(json("❤️").dump(-1, ' ', true) == "\"\\u2764\\ufe0f\"");
			}

			//TEST(constructors,"full Unicode escaping to ASCII")
			{
				//TEST(constructors,"parsing yields the same JSON value")
				{
					std::ifstream f_escaped("test/data/json_nlohmann_tests/all_unicode_ascii.json");
					std::ifstream f_unescaped("test/data/json_nlohmann_tests/all_unicode.json");

					json j1 = json::parse(f_escaped);
					json j2 = json::parse(f_unescaped);
					EXPECT_TRUE(j1 == j2);
				}

				//TEST(constructors,"dumping yields the same JSON text")
				{
					std::ifstream f_escaped("test/data/json_nlohmann_tests/all_unicode_ascii.json");
					std::ifstream f_unescaped("test/data/json_nlohmann_tests/all_unicode.json");

					json value = json::parse(f_unescaped);
					std::string text = value.dump(4, ' ', true);

					std::string expected((std::istreambuf_iterator<char>(f_escaped)),
										 std::istreambuf_iterator<char>());
					EXPECT_TRUE(text == expected);
				}
			}

			//TEST(constructors,"serialization of discarded element")
			{
				json j_discarded(json::value_t::discarded);
				EXPECT_TRUE(j_discarded.dump() == "<discarded>");
			}

			//TEST(constructors,"check that precision is reset after serialization")
			{
				// create stringstream and set precision
				std::stringstream ss;
				ss.precision(3);
				ss << 3.141592653589793 << std::fixed;
				EXPECT_TRUE(ss.str() == "3.14");

				// reset stringstream
				ss.str(std::string());

				// use stringstream for JSON serialization
				json j_number = 3.14159265358979;
				ss << j_number;

				// check that precision has been overridden during serialization
				EXPECT_TRUE(ss.str() == "3.14159265358979");

				// check that precision has been restored
				EXPECT_TRUE(ss.precision() == 3);
			}
		}

		//TEST(constructors,"round trips")
		{
			for (const auto& s :
					{"3.141592653589793", "1000000000000000010E5"
					})
			{
				json j1 = json::parse(s);
				std::string s1 = j1.dump();
				json j2 = json::parse(s1);
				std::string s2 = j2.dump();
				EXPECT_TRUE(s1 == s2);
			}
		}

		//TEST(constructors,"return the type of the object (explicit)")
		{
			//TEST(constructors,"null")
			{
				json j = nullptr;
				EXPECT_TRUE(j.type() == json::value_t::null);
			}

			//TEST(constructors,"object")
			{
				json j = {{"foo", "bar"}};
				EXPECT_TRUE(j.type() == json::value_t::object);
			}

			//TEST(constructors,"array")
			{
				json j = {1, 2, 3, 4};
				EXPECT_TRUE(j.type() == json::value_t::array);
			}

			//TEST(constructors,"boolean")
			{
				json j = true;
				EXPECT_TRUE(j.type() == json::value_t::boolean);
			}

			//TEST(constructors,"string")
			{
				json j = "Hello world";
				EXPECT_TRUE(j.type() == json::value_t::string);
			}

			//TEST(constructors,"number (integer)")
			{
				json j = 23;
				EXPECT_TRUE(j.type() == json::value_t::number_integer);
			}

			//TEST(constructors,"number (unsigned)")
			{
				json j = 23u;
				EXPECT_TRUE(j.type() == json::value_t::number_unsigned);
			}

			//TEST(constructors,"number (floating-point)")
			{
				json j = 42.23;
				EXPECT_TRUE(j.type() == json::value_t::number_float);
			}
		}

		//TEST(constructors,"return the type of the object (implicit)")
		{
			//TEST(constructors,"null")
			{
				json j = nullptr;
				json::value_t t = j;
				EXPECT_TRUE(t == j.type());
			}

			//TEST(constructors,"object")
			{
				json j = {{"foo", "bar"}};
				json::value_t t = j;
				EXPECT_TRUE(t == j.type());
			}

			//TEST(constructors,"array")
			{
				json j = {1, 2, 3, 4};
				json::value_t t = j;
				EXPECT_TRUE(t == j.type());
			}

			//TEST(constructors,"boolean")
			{
				json j = true;
				json::value_t t = j;
				EXPECT_TRUE(t == j.type());
			}

			//TEST(constructors,"string")
			{
				json j = "Hello world";
				json::value_t t = j;
				EXPECT_TRUE(t == j.type());
			}

			//TEST(constructors,"number (integer)")
			{
				json j = 23;
				json::value_t t = j;
				EXPECT_TRUE(t == j.type());
			}

			//TEST(constructors,"number (unsigned)")
			{
				json j = 23u;
				json::value_t t = j;
				EXPECT_TRUE(t == j.type());
			}

			//TEST(constructors,"number (floating-point)")
			{
				json j = 42.23;
				json::value_t t = j;
				EXPECT_TRUE(t == j.type());
			}
		}
	}
}
