#include "gtest/gtest.h"
#define private public
#include "json.hpp"

using nlohmann::json;

namespace
{
	// shortcut to scan a string literal
	json::lexer::token_type scan_string(const char* s);
	json::lexer::token_type scan_string(const char* s)
	{
		return json::lexer(nlohmann::detail::input_adapter(s)).scan();
	}

	TEST(lexer_class, lexer_class_test)
	{
		//TEST(lexer_class,"scan")
		{
			//TEST(lexer_class,"structural characters")
			{
				EXPECT_TRUE((scan_string("[") == json::lexer::token_type::begin_array));
				EXPECT_TRUE((scan_string("]") == json::lexer::token_type::end_array));
				EXPECT_TRUE((scan_string("{") == json::lexer::token_type::begin_object));
				EXPECT_TRUE((scan_string("}") == json::lexer::token_type::end_object));
				EXPECT_TRUE((scan_string(",") == json::lexer::token_type::value_separator));
				EXPECT_TRUE((scan_string(":") == json::lexer::token_type::name_separator));
			}

			//TEST(lexer_class,"literal names")
			{
				EXPECT_TRUE((scan_string("null") == json::lexer::token_type::literal_null));
				EXPECT_TRUE((scan_string("true") == json::lexer::token_type::literal_true));
				EXPECT_TRUE((scan_string("false") == json::lexer::token_type::literal_false));
			}

			//TEST(lexer_class,"numbers")
			{
				EXPECT_TRUE((scan_string("0") == json::lexer::token_type::value_unsigned));
				EXPECT_TRUE((scan_string("1") == json::lexer::token_type::value_unsigned));
				EXPECT_TRUE((scan_string("2") == json::lexer::token_type::value_unsigned));
				EXPECT_TRUE((scan_string("3") == json::lexer::token_type::value_unsigned));
				EXPECT_TRUE((scan_string("4") == json::lexer::token_type::value_unsigned));
				EXPECT_TRUE((scan_string("5") == json::lexer::token_type::value_unsigned));
				EXPECT_TRUE((scan_string("6") == json::lexer::token_type::value_unsigned));
				EXPECT_TRUE((scan_string("7") == json::lexer::token_type::value_unsigned));
				EXPECT_TRUE((scan_string("8") == json::lexer::token_type::value_unsigned));
				EXPECT_TRUE((scan_string("9") == json::lexer::token_type::value_unsigned));

				EXPECT_TRUE((scan_string("-0") == json::lexer::token_type::value_integer));
				EXPECT_TRUE((scan_string("-1") == json::lexer::token_type::value_integer));

				EXPECT_TRUE((scan_string("1.1") == json::lexer::token_type::value_float));
				EXPECT_TRUE((scan_string("-1.1") == json::lexer::token_type::value_float));
				EXPECT_TRUE((scan_string("1E10") == json::lexer::token_type::value_float));
			}

			//TEST(lexer_class,"whitespace")
			{
				// result is end_of_input, because not token is following
				EXPECT_TRUE((scan_string(" ") == json::lexer::token_type::end_of_input));
				EXPECT_TRUE((scan_string("\t") == json::lexer::token_type::end_of_input));
				EXPECT_TRUE((scan_string("\n") == json::lexer::token_type::end_of_input));
				EXPECT_TRUE((scan_string("\r") == json::lexer::token_type::end_of_input));
				EXPECT_TRUE((scan_string(" \t\n\r\n\t ") == json::lexer::token_type::end_of_input));
			}
		}

		//TEST(lexer_class,"token_type_name")
		{
			EXPECT_TRUE((std::string(json::lexer::token_type_name(json::lexer::token_type::uninitialized)) == "<uninitialized>"));
			EXPECT_TRUE((std::string(json::lexer::token_type_name(json::lexer::token_type::literal_true)) == "true literal"));
			EXPECT_TRUE((std::string(json::lexer::token_type_name(json::lexer::token_type::literal_false)) == "false literal"));
			EXPECT_TRUE((std::string(json::lexer::token_type_name(json::lexer::token_type::literal_null)) == "null literal"));
			EXPECT_TRUE((std::string(json::lexer::token_type_name(json::lexer::token_type::value_string)) == "string literal"));
			EXPECT_TRUE((std::string(json::lexer::token_type_name(json::lexer::token_type::value_unsigned)) == "number literal"));
			EXPECT_TRUE((std::string(json::lexer::token_type_name(json::lexer::token_type::value_integer)) == "number literal"));
			EXPECT_TRUE((std::string(json::lexer::token_type_name(json::lexer::token_type::value_float)) == "number literal"));
			EXPECT_TRUE((std::string(json::lexer::token_type_name(json::lexer::token_type::begin_array)) == "'['"));
			EXPECT_TRUE((std::string(json::lexer::token_type_name(json::lexer::token_type::begin_object)) == "'{'"));
			EXPECT_TRUE((std::string(json::lexer::token_type_name(json::lexer::token_type::end_array)) == "']'"));
			EXPECT_TRUE((std::string(json::lexer::token_type_name(json::lexer::token_type::end_object)) == "'}'"));
			EXPECT_TRUE((std::string(json::lexer::token_type_name(json::lexer::token_type::name_separator)) == "':'"));
			EXPECT_TRUE((std::string(json::lexer::token_type_name(json::lexer::token_type::value_separator)) == "','"));
			EXPECT_TRUE((std::string(json::lexer::token_type_name(json::lexer::token_type::parse_error)) == "<parse error>"));
			EXPECT_TRUE((std::string(json::lexer::token_type_name(json::lexer::token_type::end_of_input)) == "end of input"));
		}

		//TEST(lexer_class,"parse errors on first character")
		{
			for (int c = 1; c < 128; ++c)
			{
				// create string from the ASCII code
				const auto s = std::string(1, static_cast<char>(c));
				// store scan() result
				const auto res = scan_string(s.c_str());

				switch (c)
				{
					// single characters that are valid tokens
					case ('['):
					case (']'):
					case ('{'):
					case ('}'):
					case (','):
					case (':'):
					case ('0'):
					case ('1'):
					case ('2'):
					case ('3'):
					case ('4'):
					case ('5'):
					case ('6'):
					case ('7'):
					case ('8'):
					case ('9'):
					{
						EXPECT_TRUE((res != json::lexer::token_type::parse_error));
						break;
					}

					// whitespace
					case (' '):
					case ('\t'):
					case ('\n'):
					case ('\r'):
					{
						EXPECT_TRUE((res == json::lexer::token_type::end_of_input));
						break;
					}

					// anything else is not expected
					default:
					{
						EXPECT_TRUE((res == json::lexer::token_type::parse_error));
						break;
					}
				}
			}
		}

		//TEST(lexer_class,"very large string")
		{
			// strings larger than 1024 bytes yield a resize of the lexer's yytext buffer
			std::string s("\"");
			s += std::string(2048, 'x');
			s += "\"";
			EXPECT_TRUE((scan_string(s.c_str()) == json::lexer::token_type::value_string));
		}
	}
}
