#include "gtest/gtest.h"
#define private public
#include "json.hpp"

using nlohmann::json;

#include <valarray>

namespace
{
	class SaxEventLogger : public nlohmann::json::json_sax_t
	{
	  public:
		bool null() override
		{
			events.push_back("null()");
			return true;
		}

		bool boolean(bool val) override
		{
			events.push_back(val ? "boolean(true)" : "boolean(false)");
			return true;
		}

		bool number_integer(json::number_integer_t val) override
		{
			events.push_back("number_integer(" + std::to_string(val) + ")");
			return true;
		}

		bool number_unsigned(json::number_unsigned_t val) override
		{
			events.push_back("number_unsigned(" + std::to_string(val) + ")");
			return true;
		}

		bool number_float(json::number_float_t, const std::string& s) override
		{
			events.push_back("number_float(" + s + ")");
			return true;
		}

		bool string(std::string& val) override
		{
			events.push_back("string(" + val + ")");
			return true;
		}

		bool start_object(std::size_t elements) override
		{
			if (elements == no_limit)
			{
				events.push_back("start_object()");
			}
			else
			{
				events.push_back("start_object(" + std::to_string(elements) + ")");
			}
			return true;
		}

		bool key(std::string& val) override
		{
			events.push_back("key(" + val + ")");
			return true;
		}

		bool end_object() override
		{
			events.push_back("end_object()");
			return true;
		}

		bool start_array(std::size_t elements) override
		{
			if (elements == no_limit)
			{
				events.push_back("start_array()");
			}
			else
			{
				events.push_back("start_array(" + std::to_string(elements) + ")");
			}
			return true;
		}

		bool end_array() override
		{
			events.push_back("end_array()");
			return true;
		}

		bool parse_error(std::size_t position, const std::string&, const json::exception&) override
		{
			errored = true;
			events.push_back("parse_error(" + std::to_string(position) + ")");
			return false;
		}

		std::vector<std::string> events;
		bool errored = false;
	};

	class SaxCountdown : public nlohmann::json::json_sax_t
	{
	  public:
		explicit SaxCountdown(const int count) : events_left(count)
		{}

		bool null() override
		{
			return events_left-- > 0;
		}

		bool boolean(bool) override
		{
			return events_left-- > 0;
		}

		bool number_integer(json::number_integer_t) override
		{
			return events_left-- > 0;
		}

		bool number_unsigned(json::number_unsigned_t) override
		{
			return events_left-- > 0;
		}

		bool number_float(json::number_float_t, const std::string&) override
		{
			return events_left-- > 0;
		}

		bool string(std::string&) override
		{
			return events_left-- > 0;
		}

		bool start_object(std::size_t) override
		{
			return events_left-- > 0;
		}

		bool key(std::string&) override
		{
			return events_left-- > 0;
		}

		bool end_object() override
		{
			return events_left-- > 0;
		}

		bool start_array(std::size_t) override
		{
			return events_left-- > 0;
		}

		bool end_array() override
		{
			return events_left-- > 0;
		}

		bool parse_error(std::size_t, const std::string&, const json::exception&) override
		{
			return false;
		}

	  private:
		int events_left = 0;
	};

	json parser_helper(const std::string& s);
	bool accept_helper(const std::string& s);

	json parser_helper(const std::string& s)
	{
		json j;
		json::parser(nlohmann::detail::input_adapter(s)).parse(true, j);

		// if this line was reached, no exception ocurred
		// -> check if result is the same without exceptions
		json j_nothrow;
		EXPECT_NO_THROW(json::parser(nlohmann::detail::input_adapter(s), nullptr, false).parse(true, j_nothrow));
		EXPECT_EQ(j_nothrow, j);

		json j_sax;
		nlohmann::detail::json_sax_dom_parser<json> sdp(j_sax);
		json::sax_parse(s, &sdp);
		EXPECT_EQ(j_sax, j);

		return j;
	}

	bool accept_helper(const std::string& s)
	{
		//CAPTURE(s);

		// 1. parse s without exceptions
		json j;
		EXPECT_NO_THROW(json::parser(nlohmann::detail::input_adapter(s), nullptr, false).parse(true, j));
		const bool ok_noexcept = not j.is_discarded();

		// 2. accept s
		const bool ok_accept = json::parser(nlohmann::detail::input_adapter(s)).accept(true);

		// 3. check if both approaches come to the same result
		EXPECT_EQ(ok_noexcept, ok_accept);

		// 4. parse with SAX (compare with relaxed accept result)
		SaxEventLogger el;
		EXPECT_NO_THROW(json::sax_parse(s, &el, json::input_format_t::json, false));
		EXPECT_EQ(json::parser(nlohmann::detail::input_adapter(s)).accept(false), not el.errored);

		// 5. parse with simple callback
		json::parser_callback_t cb = [](int, json::parse_event_t, json&)
		{
			return true;
		};
		json j_cb = json::parse(s, cb, false);
		const bool ok_noexcept_cb = not j_cb.is_discarded();

		// 6. check if this approach came to the same result
		EXPECT_EQ(ok_noexcept, ok_noexcept_cb);

		// 7. return result
		return ok_accept;
	}

	TEST(parser_class, parser_class_test)
	{
		//TEST(class_parser,"parse")
		{
			//TEST(class_parser,"null")
			{
				EXPECT_EQ(parser_helper("null"), json(nullptr));
			}

			//TEST(class_parser,"true")
			{
				EXPECT_EQ(parser_helper("true"), json(true));
			}

			//TEST(class_parser,"false")
			{
				EXPECT_EQ(parser_helper("false"), json(false));
			}

			//TEST(class_parser,"array")
			{
				//TEST(class_parser,"empty array")
				{
					EXPECT_EQ(parser_helper("[]"), json(json::value_t::array));
					EXPECT_EQ(parser_helper("[ ]"), json(json::value_t::array));
				}

				//TEST(class_parser,"nonempty array")
				{
					EXPECT_EQ(parser_helper("[true, false, null]"), json({true, false, nullptr}));
				}
			}

			//TEST(class_parser,"object")
			{
				//TEST(class_parser,"empty object")
				{
					EXPECT_EQ(parser_helper("{}"), json(json::value_t::object));
					EXPECT_EQ(parser_helper("{ }"), json(json::value_t::object));
				}

				//TEST(class_parser,"nonempty object")
				{
					EXPECT_EQ(parser_helper("{\"\": true, \"one\": 1, \"two\": null}"), json({{"", true}, {"one", 1}, {"two", nullptr}}));
				}
			}

			//TEST(class_parser,"string")
			{
				// empty string
				EXPECT_EQ(parser_helper("\"\""), json(json::value_t::string));

				//TEST(class_parser,"errors")
				{
					// error: tab in string
					EXPECT_THROW(parser_helper("\"\t\""), json::parse_error);
					//CHECK_THROWS_WITH(parser_helper("\"\t\""),
									  //"[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+0009>'");
					// error: newline in string
					EXPECT_THROW(parser_helper("\"\n\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\r\""), json::parse_error);
					//CHECK_THROWS_WITH(parser_helper("\"\n\""),
									  //"[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+000A>'");
					//CHECK_THROWS_WITH(parser_helper("\"\r\""),
									  //"[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+000D>'");
					// error: backspace in string
					EXPECT_THROW(parser_helper("\"\b\""), json::parse_error);
					//CHECK_THROWS_WITH(parser_helper("\"\b\""),
									  //"[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+0008>'");
					// improve code coverage
					EXPECT_THROW(parser_helper("\uFF01"), json::parse_error);
					EXPECT_THROW(parser_helper("[-4:1,]"), json::parse_error);
					// unescaped control characters
					EXPECT_THROW(parser_helper("\"\x00\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x01\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x02\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x03\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x04\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x05\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x06\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x07\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x08\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x09\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x0a\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x0b\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x0c\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x0d\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x0e\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x0f\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x10\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x11\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x12\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x13\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x14\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x15\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x16\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x17\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x18\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x19\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x1a\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x1b\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x1c\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x1d\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x1e\""), json::parse_error);
					EXPECT_THROW(parser_helper("\"\x1f\""), json::parse_error);
					//CHECK_THROWS_WITH(parser_helper("\"\x00\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: missing closing quote; last read: '\"'");
					//CHECK_THROWS_WITH(parser_helper("\"\x01\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+0001>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x02\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+0002>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x03\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+0003>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x04\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+0004>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x05\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+0005>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x06\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+0006>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x07\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+0007>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x08\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+0008>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x09\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+0009>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x0a\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+000A>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x0b\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+000B>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x0c\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+000C>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x0d\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+000D>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x0e\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+000E>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x0f\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+000F>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x10\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+0010>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x11\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+0011>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x12\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+0012>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x13\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+0013>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x14\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+0014>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x15\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+0015>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x16\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+0016>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x17\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+0017>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x18\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+0018>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x19\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+0019>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x1a\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+001A>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x1b\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+001B>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x1c\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+001C>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x1d\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+001D>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x1e\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+001E>'");
					//CHECK_THROWS_WITH(parser_helper("\"\x1f\""), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+001F>'");

					//TEST(class_parser,"additional test for null byte")
					{
						// The test above for the null byte is wrong, because passing
						// a string to the parser only reads int until it encounters
						// a null byte. This test inserts the null byte later on and
						// uses an iterator range.
						std::string s = "\"1\"";
						s[1] = '\0';
						EXPECT_THROW(json::parse(s.begin(), s.end()), json::parse_error);
						//CHECK_THROWS_WITH(json::parse(s.begin(), s.end()), "[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: control character must be escaped; last read: '\"<U+0000>'");
					}
				}

				//TEST(class_parser,"escaped")
				{
					// quotation mark "\""
					auto r1 = R"("\"")"_json;
					EXPECT_EQ(parser_helper("\"\\\"\""), r1);
					// reverse solidus "\\"
					auto r2 = R"("\\")"_json;
					EXPECT_EQ(parser_helper("\"\\\\\""), r2);
					// solidus
					EXPECT_EQ(parser_helper("\"\\/\""), R"("/")"_json);
					// backspace
					EXPECT_EQ(parser_helper("\"\\b\""), json("\b"));
					// formfeed
					EXPECT_EQ(parser_helper("\"\\f\""), json("\f"));
					// newline
					EXPECT_EQ(parser_helper("\"\\n\""), json("\n"));
					// carriage return
					EXPECT_EQ(parser_helper("\"\\r\""), json("\r"));
					// horizontal tab
					EXPECT_EQ(parser_helper("\"\\t\""), json("\t"));

					EXPECT_EQ(parser_helper("\"\\u0001\"").get<json::string_t>(), "\x01");
					EXPECT_EQ(parser_helper("\"\\u000a\"").get<json::string_t>(), "\n");
					EXPECT_EQ(parser_helper("\"\\u00b0\"").get<json::string_t>(), "°");
					EXPECT_EQ(parser_helper("\"\\u0c00\"").get<json::string_t>(), "ఀ");
					EXPECT_EQ(parser_helper("\"\\ud000\"").get<json::string_t>(), "퀀");
					EXPECT_EQ(parser_helper("\"\\u000E\"").get<json::string_t>(), "\x0E");
					EXPECT_EQ(parser_helper("\"\\u00F0\"").get<json::string_t>(), "ð");
					EXPECT_EQ(parser_helper("\"\\u0100\"").get<json::string_t>(), "Ā");
					EXPECT_EQ(parser_helper("\"\\u2000\"").get<json::string_t>(), " ");
					EXPECT_EQ(parser_helper("\"\\uFFFF\"").get<json::string_t>(), "￿");
					EXPECT_EQ(parser_helper("\"\\u20AC\"").get<json::string_t>(), "€");
					EXPECT_EQ(parser_helper("\"€\"").get<json::string_t>(), "€");
					EXPECT_EQ(parser_helper("\"🎈\"").get<json::string_t>(), "🎈");

					EXPECT_EQ(parser_helper("\"\\ud80c\\udc60\"").get<json::string_t>(), u8"\U00013060");
					EXPECT_EQ(parser_helper("\"\\ud83c\\udf1e\"").get<json::string_t>(), "🌞");
				}
			}

			//TEST(class_parser,"number")
			{
				//TEST(class_parser,"integers")
				{
					//TEST(class_parser,"without exponent")
					{
						EXPECT_EQ(parser_helper("-128"), json(-128));
						EXPECT_EQ(parser_helper("-0"), json(-0));
						EXPECT_EQ(parser_helper("0"), json(0));
						EXPECT_EQ(parser_helper("128"), json(128));
					}

					//TEST(class_parser,"with exponent")
					{
						EXPECT_EQ(parser_helper("0e1"), json(0e1));
						EXPECT_EQ(parser_helper("0E1"), json(0e1));

						EXPECT_TRUE(parser_helper("10000E-4") == json(10000e-4));
						EXPECT_TRUE(parser_helper("10000E-3") == json(10000e-3));
						EXPECT_TRUE(parser_helper("10000E-2") == json(10000e-2));
						EXPECT_TRUE(parser_helper("10000E-1") == json(10000e-1));
						EXPECT_TRUE(parser_helper("10000E0") == json(10000e0));
						EXPECT_TRUE(parser_helper("10000E1") == json(10000e1));
						EXPECT_TRUE(parser_helper("10000E2") == json(10000e2));
						EXPECT_TRUE(parser_helper("10000E3") == json(10000e3));
						EXPECT_TRUE(parser_helper("10000E4") == json(10000e4));

						EXPECT_TRUE(parser_helper("10000e-4") == json(10000e-4));
						EXPECT_TRUE(parser_helper("10000e-3") == json(10000e-3));
						EXPECT_TRUE(parser_helper("10000e-2") == json(10000e-2));
						EXPECT_TRUE(parser_helper("10000e-1") == json(10000e-1));
						EXPECT_TRUE(parser_helper("10000e0") == json(10000e0));
						EXPECT_TRUE(parser_helper("10000e1") == json(10000e1));
						EXPECT_TRUE(parser_helper("10000e2") == json(10000e2));
						EXPECT_TRUE(parser_helper("10000e3") == json(10000e3));
						EXPECT_TRUE(parser_helper("10000e4") == json(10000e4));

						EXPECT_TRUE(parser_helper("-0e1") == json(-0e1));
						EXPECT_TRUE(parser_helper("-0E1") == json(-0e1));
						EXPECT_TRUE(parser_helper("-0E123") == json(-0e123));

						// numbers after exponent
						EXPECT_TRUE(parser_helper("10E0") == json(10e0));
						EXPECT_TRUE(parser_helper("10E1") == json(10e1));
						EXPECT_TRUE(parser_helper("10E2") == json(10e2));
						EXPECT_TRUE(parser_helper("10E3") == json(10e3));
						EXPECT_TRUE(parser_helper("10E4") == json(10e4));
						EXPECT_TRUE(parser_helper("10E5") == json(10e5));
						EXPECT_TRUE(parser_helper("10E6") == json(10e6));
						EXPECT_TRUE(parser_helper("10E7") == json(10e7));
						EXPECT_TRUE(parser_helper("10E8") == json(10e8));
						EXPECT_TRUE(parser_helper("10E9") == json(10e9));
						EXPECT_TRUE(parser_helper("10E+0") == json(10e0));
						EXPECT_TRUE(parser_helper("10E+1") == json(10e1));
						EXPECT_TRUE(parser_helper("10E+2") == json(10e2));
						EXPECT_TRUE(parser_helper("10E+3") == json(10e3));
						EXPECT_TRUE(parser_helper("10E+4") == json(10e4));
						EXPECT_TRUE(parser_helper("10E+5") == json(10e5));
						EXPECT_TRUE(parser_helper("10E+6") == json(10e6));
						EXPECT_TRUE(parser_helper("10E+7") == json(10e7));
						EXPECT_TRUE(parser_helper("10E+8") == json(10e8));
						EXPECT_TRUE(parser_helper("10E+9") == json(10e9));
						EXPECT_TRUE(parser_helper("10E-1") == json(10e-1));
						EXPECT_TRUE(parser_helper("10E-2") == json(10e-2));
						EXPECT_TRUE(parser_helper("10E-3") == json(10e-3));
						EXPECT_TRUE(parser_helper("10E-4") == json(10e-4));
						EXPECT_TRUE(parser_helper("10E-5") == json(10e-5));
						EXPECT_TRUE(parser_helper("10E-6") == json(10e-6));
						EXPECT_TRUE(parser_helper("10E-7") == json(10e-7));
						EXPECT_TRUE(parser_helper("10E-8") == json(10e-8));
						EXPECT_TRUE(parser_helper("10E-9") == json(10e-9));
					}

					//TEST(class_parser,"edge cases")
					{
						// From RFC7159, Section 6:
						// Note that when such software is used, numbers that are
						// integers and are in the range [-(2**53)+1, (2**53)-1]
						// are interoperable in the sense that implementations will
						// agree exactly on their numeric values.

						// -(2**53)+1
						EXPECT_TRUE(parser_helper("-9007199254740991").get<int64_t>() == -9007199254740991);
						// (2**53)-1
						EXPECT_TRUE(parser_helper("9007199254740991").get<int64_t>() == 9007199254740991);
					}

					//TEST(class_parser,"over the edge cases")  // issue #178 - Integer conversion to unsigned (incorrect handling of 64 bit integers)
					{
						// While RFC7159, Section 6 specifies a preference for support
						// for ranges in range of IEEE 754-2008 binary64 (double precision)
						// this does not accommodate 64 bit integers without loss of accuracy.
						// As 64 bit integers are now widely used in software, it is desirable
						// to expand support to to the full 64 bit (signed and unsigned) range
						// i.e. -(2**63) -> (2**64)-1.

						// -(2**63)    ** Note: compilers see negative literals as negated positive numbers (hence the -1))
						EXPECT_TRUE(parser_helper("-9223372036854775808").get<int64_t>() == -9223372036854775807 - 1);
						// (2**63)-1
						EXPECT_TRUE(parser_helper("9223372036854775807").get<int64_t>() == 9223372036854775807);
						// (2**64)-1
						EXPECT_TRUE(parser_helper("18446744073709551615").get<uint64_t>() == 18446744073709551615u);
					}
				}

				//TEST(class_parser,"floating-point")
				{
					//TEST(class_parser,"without exponent")
					{
						EXPECT_TRUE(parser_helper("-128.5") == json(-128.5));
						EXPECT_TRUE(parser_helper("0.999") == json(0.999));
						EXPECT_TRUE(parser_helper("128.5") == json(128.5));
						EXPECT_TRUE(parser_helper("-0.0") == json(-0.0));
					}

					//TEST(class_parser,"with exponent")
					{
						EXPECT_TRUE(parser_helper("-128.5E3") == json(-128.5E3));
						EXPECT_TRUE(parser_helper("-128.5E-3") == json(-128.5E-3));
						EXPECT_TRUE(parser_helper("-0.0e1") == json(-0.0e1));
						EXPECT_TRUE(parser_helper("-0.0E1") == json(-0.0e1));
					}
				}

				//TEST(class_parser,"overflow")
				{
					// overflows during parsing yield an exception
					EXPECT_THROW(parser_helper("1.18973e+4932") == json(), json::out_of_range);
					//CHECK_THROWS_WITH(parser_helper("1.18973e+4932") == json(),
									  //"[json.exception.out_of_range.406] number overflow parsing '1.18973e+4932'");
				}

				//TEST(class_parser,"invalid numbers")
				{
					EXPECT_THROW(parser_helper("01"),      json::parse_error);
					EXPECT_THROW(parser_helper("--1"),     json::parse_error);
					EXPECT_THROW(parser_helper("1."),      json::parse_error);
					EXPECT_THROW(parser_helper("1E"),      json::parse_error);
					EXPECT_THROW(parser_helper("1E-"),     json::parse_error);
					EXPECT_THROW(parser_helper("1.E1"),    json::parse_error);
					EXPECT_THROW(parser_helper("-1E"),     json::parse_error);
					EXPECT_THROW(parser_helper("-0E#"),    json::parse_error);
					EXPECT_THROW(parser_helper("-0E-#"),   json::parse_error);
					EXPECT_THROW(parser_helper("-0#"),     json::parse_error);
					EXPECT_THROW(parser_helper("-0.0:"),   json::parse_error);
					EXPECT_THROW(parser_helper("-0.0Z"),   json::parse_error);
					EXPECT_THROW(parser_helper("-0E123:"), json::parse_error);
					EXPECT_THROW(parser_helper("-0e0-:"),  json::parse_error);
					EXPECT_THROW(parser_helper("-0e-:"),   json::parse_error);
					EXPECT_THROW(parser_helper("-0f"),     json::parse_error);

					// numbers must not begin with "+"
					EXPECT_THROW(parser_helper("+1"), json::parse_error);
					EXPECT_THROW(parser_helper("+0"), json::parse_error);

					//CHECK_THROWS_WITH(parser_helper("01"),
									  //"[json.exception.parse_error.101] parse error at 2: syntax error - unexpected number literal; expected end of input");
					//CHECK_THROWS_WITH(parser_helper("-01"),
									  //"[json.exception.parse_error.101] parse error at 3: syntax error - unexpected number literal; expected end of input");
					//CHECK_THROWS_WITH(parser_helper("--1"),
									  //"[json.exception.parse_error.101] parse error at 2: syntax error - invalid number; expected digit after '-'; last read: '--'");
					//CHECK_THROWS_WITH(parser_helper("1."),
									  //"[json.exception.parse_error.101] parse error at 3: syntax error - invalid number; expected digit after '.'; last read: '1.'");
					//CHECK_THROWS_WITH(parser_helper("1E"),
									  //"[json.exception.parse_error.101] parse error at 3: syntax error - invalid number; expected '+', '-', or digit after exponent; last read: '1E'");
					//CHECK_THROWS_WITH(parser_helper("1E-"),
									  //"[json.exception.parse_error.101] parse error at 4: syntax error - invalid number; expected digit after exponent sign; last read: '1E-'");
					//CHECK_THROWS_WITH(parser_helper("1.E1"),
									  //"[json.exception.parse_error.101] parse error at 3: syntax error - invalid number; expected digit after '.'; last read: '1.E'");
					//CHECK_THROWS_WITH(parser_helper("-1E"),
									  //"[json.exception.parse_error.101] parse error at 4: syntax error - invalid number; expected '+', '-', or digit after exponent; last read: '-1E'");
					//CHECK_THROWS_WITH(parser_helper("-0E#"),
									  //"[json.exception.parse_error.101] parse error at 4: syntax error - invalid number; expected '+', '-', or digit after exponent; last read: '-0E#'");
					//CHECK_THROWS_WITH(parser_helper("-0E-#"),
									  //"[json.exception.parse_error.101] parse error at 5: syntax error - invalid number; expected digit after exponent sign; last read: '-0E-#'");
					//CHECK_THROWS_WITH(parser_helper("-0#"),
									  //"[json.exception.parse_error.101] parse error at 3: syntax error - invalid literal; last read: '-0#'; expected end of input");
					//CHECK_THROWS_WITH(parser_helper("-0.0:"),
									  //"[json.exception.parse_error.101] parse error at 5: syntax error - unexpected ':'; expected end of input");
					//CHECK_THROWS_WITH(parser_helper("-0.0Z"),
									  //"[json.exception.parse_error.101] parse error at 5: syntax error - invalid literal; last read: '-0.0Z'; expected end of input");
					//CHECK_THROWS_WITH(parser_helper("-0E123:"),
									  //"[json.exception.parse_error.101] parse error at 7: syntax error - unexpected ':'; expected end of input");
					//CHECK_THROWS_WITH(parser_helper("-0e0-:"),
									  //"[json.exception.parse_error.101] parse error at 6: syntax error - invalid number; expected digit after '-'; last read: '-:'; expected end of input");
					//CHECK_THROWS_WITH(parser_helper("-0e-:"),
									  //"[json.exception.parse_error.101] parse error at 5: syntax error - invalid number; expected digit after exponent sign; last read: '-0e-:'");
					//CHECK_THROWS_WITH(parser_helper("-0f"),
									  //"[json.exception.parse_error.101] parse error at 4: syntax error - invalid literal; last read: '-0f'; expected end of input");
				}
			}
		}

		//TEST(class_parser,"accept")
		{
			//TEST(class_parser,"null")
			{
				EXPECT_TRUE(accept_helper("null"));
			}

			//TEST(class_parser,"true")
			{
				EXPECT_TRUE(accept_helper("true"));
			}

			//TEST(class_parser,"false")
			{
				EXPECT_TRUE(accept_helper("false"));
			}

			//TEST(class_parser,"array")
			{
				//TEST(class_parser,"empty array")
				{
					EXPECT_TRUE(accept_helper("[]"));
					EXPECT_TRUE(accept_helper("[ ]"));
				}

				//TEST(class_parser,"nonempty array")
				{
					EXPECT_TRUE(accept_helper("[true, false, null]"));
				}
			}

			//TEST(class_parser,"object")
			{
				//TEST(class_parser,"empty object")
				{
					EXPECT_TRUE(accept_helper("{}"));
					EXPECT_TRUE(accept_helper("{ }"));
				}

				//TEST(class_parser,"nonempty object")
				{
					EXPECT_TRUE(accept_helper("{\"\": true, \"one\": 1, \"two\": null}"));
				}
			}

			//TEST(class_parser,"string")
			{
				// empty string
				EXPECT_TRUE(accept_helper("\"\""));

				//TEST(class_parser,"errors")
				{
					// error: tab in string
					EXPECT_EQ(accept_helper("\"\t\""), false);
					// error: newline in string
					EXPECT_EQ(accept_helper("\"\n\""), false);
					EXPECT_EQ(accept_helper("\"\r\""), false);
					// error: backspace in string
					EXPECT_EQ(accept_helper("\"\b\""), false);
					// improve code coverage
					EXPECT_EQ(accept_helper("\uFF01"), false);
					EXPECT_EQ(accept_helper("[-4:1,]"), false);
					// unescaped control characters
					EXPECT_EQ(accept_helper("\"\x00\""), false);
					EXPECT_EQ(accept_helper("\"\x01\""), false);
					EXPECT_EQ(accept_helper("\"\x02\""), false);
					EXPECT_EQ(accept_helper("\"\x03\""), false);
					EXPECT_EQ(accept_helper("\"\x04\""), false);
					EXPECT_EQ(accept_helper("\"\x05\""), false);
					EXPECT_EQ(accept_helper("\"\x06\""), false);
					EXPECT_EQ(accept_helper("\"\x07\""), false);
					EXPECT_EQ(accept_helper("\"\x08\""), false);
					EXPECT_EQ(accept_helper("\"\x09\""), false);
					EXPECT_EQ(accept_helper("\"\x0a\""), false);
					EXPECT_EQ(accept_helper("\"\x0b\""), false);
					EXPECT_EQ(accept_helper("\"\x0c\""), false);
					EXPECT_EQ(accept_helper("\"\x0d\""), false);
					EXPECT_EQ(accept_helper("\"\x0e\""), false);
					EXPECT_EQ(accept_helper("\"\x0f\""), false);
					EXPECT_EQ(accept_helper("\"\x10\""), false);
					EXPECT_EQ(accept_helper("\"\x11\""), false);
					EXPECT_EQ(accept_helper("\"\x12\""), false);
					EXPECT_EQ(accept_helper("\"\x13\""), false);
					EXPECT_EQ(accept_helper("\"\x14\""), false);
					EXPECT_EQ(accept_helper("\"\x15\""), false);
					EXPECT_EQ(accept_helper("\"\x16\""), false);
					EXPECT_EQ(accept_helper("\"\x17\""), false);
					EXPECT_EQ(accept_helper("\"\x18\""), false);
					EXPECT_EQ(accept_helper("\"\x19\""), false);
					EXPECT_EQ(accept_helper("\"\x1a\""), false);
					EXPECT_EQ(accept_helper("\"\x1b\""), false);
					EXPECT_EQ(accept_helper("\"\x1c\""), false);
					EXPECT_EQ(accept_helper("\"\x1d\""), false);
					EXPECT_EQ(accept_helper("\"\x1e\""), false);
					EXPECT_EQ(accept_helper("\"\x1f\""), false);
				}

				//TEST(class_parser,"escaped")
				{
					// quotation mark "\""
					auto r1 = R"("\"")"_json;
					EXPECT_TRUE(accept_helper("\"\\\"\""));
					// reverse solidus "\\"
					auto r2 = R"("\\")"_json;
					EXPECT_TRUE(accept_helper("\"\\\\\""));
					// solidus
					EXPECT_TRUE(accept_helper("\"\\/\""));
					// backspace
					EXPECT_TRUE(accept_helper("\"\\b\""));
					// formfeed
					EXPECT_TRUE(accept_helper("\"\\f\""));
					// newline
					EXPECT_TRUE(accept_helper("\"\\n\""));
					// carriage return
					EXPECT_TRUE(accept_helper("\"\\r\""));
					// horizontal tab
					EXPECT_TRUE(accept_helper("\"\\t\""));

					EXPECT_TRUE(accept_helper("\"\\u0001\""));
					EXPECT_TRUE(accept_helper("\"\\u000a\""));
					EXPECT_TRUE(accept_helper("\"\\u00b0\""));
					EXPECT_TRUE(accept_helper("\"\\u0c00\""));
					EXPECT_TRUE(accept_helper("\"\\ud000\""));
					EXPECT_TRUE(accept_helper("\"\\u000E\""));
					EXPECT_TRUE(accept_helper("\"\\u00F0\""));
					EXPECT_TRUE(accept_helper("\"\\u0100\""));
					EXPECT_TRUE(accept_helper("\"\\u2000\""));
					EXPECT_TRUE(accept_helper("\"\\uFFFF\""));
					EXPECT_TRUE(accept_helper("\"\\u20AC\""));
					EXPECT_TRUE(accept_helper("\"€\""));
					EXPECT_TRUE(accept_helper("\"🎈\""));

					EXPECT_TRUE(accept_helper("\"\\ud80c\\udc60\""));
					EXPECT_TRUE(accept_helper("\"\\ud83c\\udf1e\""));
				}
			}

			//TEST(class_parser,"number")
			{
				//TEST(class_parser,"integers")
				{
					//TEST(class_parser,"without exponent")
					{
						EXPECT_TRUE(accept_helper("-128"));
						EXPECT_TRUE(accept_helper("-0"));
						EXPECT_TRUE(accept_helper("0"));
						EXPECT_TRUE(accept_helper("128"));
					}

					//TEST(class_parser,"with exponent")
					{
						EXPECT_TRUE(accept_helper("0e1"));
						EXPECT_TRUE(accept_helper("0E1"));

						EXPECT_TRUE(accept_helper("10000E-4"));
						EXPECT_TRUE(accept_helper("10000E-3"));
						EXPECT_TRUE(accept_helper("10000E-2"));
						EXPECT_TRUE(accept_helper("10000E-1"));
						EXPECT_TRUE(accept_helper("10000E0"));
						EXPECT_TRUE(accept_helper("10000E1"));
						EXPECT_TRUE(accept_helper("10000E2"));
						EXPECT_TRUE(accept_helper("10000E3"));
						EXPECT_TRUE(accept_helper("10000E4"));

						EXPECT_TRUE(accept_helper("10000e-4"));
						EXPECT_TRUE(accept_helper("10000e-3"));
						EXPECT_TRUE(accept_helper("10000e-2"));
						EXPECT_TRUE(accept_helper("10000e-1"));
						EXPECT_TRUE(accept_helper("10000e0"));
						EXPECT_TRUE(accept_helper("10000e1"));
						EXPECT_TRUE(accept_helper("10000e2"));
						EXPECT_TRUE(accept_helper("10000e3"));
						EXPECT_TRUE(accept_helper("10000e4"));

						EXPECT_TRUE(accept_helper("-0e1"));
						EXPECT_TRUE(accept_helper("-0E1"));
						EXPECT_TRUE(accept_helper("-0E123"));
					}

					//TEST(class_parser,"edge cases")
					{
						// From RFC7159, Section 6:
						// Note that when such software is used, numbers that are
						// integers and are in the range [-(2**53)+1, (2**53)-1]
						// are interoperable in the sense that implementations will
						// agree exactly on their numeric values.

						// -(2**53)+1
						EXPECT_TRUE(accept_helper("-9007199254740991"));
						// (2**53)-1
						EXPECT_TRUE(accept_helper("9007199254740991"));
					}

					//TEST(class_parser,"over the edge cases")  // issue #178 - Integer conversion to unsigned (incorrect handling of 64 bit integers)
					{
						// While RFC7159, Section 6 specifies a preference for support
						// for ranges in range of IEEE 754-2008 binary64 (double precision)
						// this does not accommodate 64 bit integers without loss of accuracy.
						// As 64 bit integers are now widely used in software, it is desirable
						// to expand support to to the full 64 bit (signed and unsigned) range
						// i.e. -(2**63) -> (2**64)-1.

						// -(2**63)    ** Note: compilers see negative literals as negated positive numbers (hence the -1))
						EXPECT_TRUE(accept_helper("-9223372036854775808"));
						// (2**63)-1
						EXPECT_TRUE(accept_helper("9223372036854775807"));
						// (2**64)-1
						EXPECT_TRUE(accept_helper("18446744073709551615"));
					}
				}

				//TEST(class_parser,"floating-point")
				{
					//TEST(class_parser,"without exponent")
					{
						EXPECT_TRUE(accept_helper("-128.5"));
						EXPECT_TRUE(accept_helper("0.999"));
						EXPECT_TRUE(accept_helper("128.5"));
						EXPECT_TRUE(accept_helper("-0.0"));
					}

					//TEST(class_parser,"with exponent")
					{
						EXPECT_TRUE(accept_helper("-128.5E3"));
						EXPECT_TRUE(accept_helper("-128.5E-3"));
						EXPECT_TRUE(accept_helper("-0.0e1"));
						EXPECT_TRUE(accept_helper("-0.0E1"));
					}
				}

				//TEST(class_parser,"overflow")
				{
					// overflows during parsing
					EXPECT_TRUE(not accept_helper("1.18973e+4932"));
				}

				//TEST(class_parser,"invalid numbers")
				{
					EXPECT_TRUE(accept_helper("01") == false);
					EXPECT_TRUE(accept_helper("--1") == false);
					EXPECT_TRUE(accept_helper("1.") == false);
					EXPECT_TRUE(accept_helper("1E") == false);
					EXPECT_TRUE(accept_helper("1E-") == false);
					EXPECT_TRUE(accept_helper("1.E1") == false);
					EXPECT_TRUE(accept_helper("-1E") == false);
					EXPECT_TRUE(accept_helper("-0E#") == false);
					EXPECT_TRUE(accept_helper("-0E-#") == false);
					EXPECT_TRUE(accept_helper("-0#") == false);
					EXPECT_TRUE(accept_helper("-0.0:") == false);
					EXPECT_TRUE(accept_helper("-0.0Z") == false);
					EXPECT_TRUE(accept_helper("-0E123:") == false);
					EXPECT_TRUE(accept_helper("-0e0-:") == false);
					EXPECT_TRUE(accept_helper("-0e-:") == false);
					EXPECT_TRUE(accept_helper("-0f") == false);

					// numbers must not begin with "+"
					EXPECT_TRUE(accept_helper("+1") == false);
					EXPECT_TRUE(accept_helper("+0") == false);
				}
			}
		}

		//TEST(class_parser,"parse errors")
		{
			// unexpected end of number
			EXPECT_THROW(parser_helper("0."),  json::parse_error);
			EXPECT_THROW(parser_helper("-"),   json::parse_error);
			EXPECT_THROW(parser_helper("--"),  json::parse_error);
			EXPECT_THROW(parser_helper("-0."), json::parse_error);
			EXPECT_THROW(parser_helper("-."),  json::parse_error);
			EXPECT_THROW(parser_helper("-:"),  json::parse_error);
			EXPECT_THROW(parser_helper("0.:"), json::parse_error);
			EXPECT_THROW(parser_helper("e."),  json::parse_error);
			EXPECT_THROW(parser_helper("1e."), json::parse_error);
			EXPECT_THROW(parser_helper("1e/"), json::parse_error);
			EXPECT_THROW(parser_helper("1e:"), json::parse_error);
			EXPECT_THROW(parser_helper("1E."), json::parse_error);
			EXPECT_THROW(parser_helper("1E/"), json::parse_error);
			EXPECT_THROW(parser_helper("1E:"), json::parse_error);
			//CHECK_THROWS_WITH(parser_helper("0."),
							  //"[json.exception.parse_error.101] parse error at 3: syntax error - invalid number; expected digit after '.'; last read: '0.'");
			//CHECK_THROWS_WITH(parser_helper("-"),
							  //"[json.exception.parse_error.101] parse error at 2: syntax error - invalid number; expected digit after '-'; last read: '-'");
			//CHECK_THROWS_WITH(parser_helper("--"),
							  //"[json.exception.parse_error.101] parse error at 2: syntax error - invalid number; expected digit after '-'; last read: '--'");
			//CHECK_THROWS_WITH(parser_helper("-0."),
							  //"[json.exception.parse_error.101] parse error at 4: syntax error - invalid number; expected digit after '.'; last read: '-0.'");
			//CHECK_THROWS_WITH(parser_helper("-."),
							  //"[json.exception.parse_error.101] parse error at 2: syntax error - invalid number; expected digit after '-'; last read: '-.'");
			//CHECK_THROWS_WITH(parser_helper("-:"),
							  //"[json.exception.parse_error.101] parse error at 2: syntax error - invalid number; expected digit after '-'; last read: '-:'");
			//CHECK_THROWS_WITH(parser_helper("0.:"),
							  //"[json.exception.parse_error.101] parse error at 3: syntax error - invalid number; expected digit after '.'; last read: '0.:'");
			//CHECK_THROWS_WITH(parser_helper("e."),
							  //"[json.exception.parse_error.101] parse error at 1: syntax error - invalid literal; last read: 'e'");
			//CHECK_THROWS_WITH(parser_helper("1e."),
							  //"[json.exception.parse_error.101] parse error at 3: syntax error - invalid number; expected '+', '-', or digit after exponent; last read: '1e.'");
			//CHECK_THROWS_WITH(parser_helper("1e/"),
							  //"[json.exception.parse_error.101] parse error at 3: syntax error - invalid number; expected '+', '-', or digit after exponent; last read: '1e/'");
			//CHECK_THROWS_WITH(parser_helper("1e:"),
							  //"[json.exception.parse_error.101] parse error at 3: syntax error - invalid number; expected '+', '-', or digit after exponent; last read: '1e:'");
			//CHECK_THROWS_WITH(parser_helper("1E."),
							  //"[json.exception.parse_error.101] parse error at 3: syntax error - invalid number; expected '+', '-', or digit after exponent; last read: '1E.'");
			//CHECK_THROWS_WITH(parser_helper("1E/"),
							  //"[json.exception.parse_error.101] parse error at 3: syntax error - invalid number; expected '+', '-', or digit after exponent; last read: '1E/'");
			//CHECK_THROWS_WITH(parser_helper("1E:"),
							  //"[json.exception.parse_error.101] parse error at 3: syntax error - invalid number; expected '+', '-', or digit after exponent; last read: '1E:'");

			// unexpected end of null
			EXPECT_THROW(parser_helper("n"), json::parse_error);
			EXPECT_THROW(parser_helper("nu"), json::parse_error);
			EXPECT_THROW(parser_helper("nul"), json::parse_error);
			EXPECT_THROW(parser_helper("nulk"), json::parse_error);
			EXPECT_THROW(parser_helper("nulm"), json::parse_error);
			//CHECK_THROWS_WITH(parser_helper("n"),
							  //"[json.exception.parse_error.101] parse error at 2: syntax error - invalid literal; last read: 'n'");
			//CHECK_THROWS_WITH(parser_helper("nu"),
							  //"[json.exception.parse_error.101] parse error at 3: syntax error - invalid literal; last read: 'nu'");
			//CHECK_THROWS_WITH(parser_helper("nul"),
							  //"[json.exception.parse_error.101] parse error at 4: syntax error - invalid literal; last read: 'nul'");
			//CHECK_THROWS_WITH(parser_helper("nulk"),
							  //"[json.exception.parse_error.101] parse error at 4: syntax error - invalid literal; last read: 'nulk'");
			//CHECK_THROWS_WITH(parser_helper("nulm"),
							  //"[json.exception.parse_error.101] parse error at 4: syntax error - invalid literal; last read: 'nulm'");

			// unexpected end of true
			EXPECT_THROW(parser_helper("t"), json::parse_error);
			EXPECT_THROW(parser_helper("tr"), json::parse_error);
			EXPECT_THROW(parser_helper("tru"), json::parse_error);
			EXPECT_THROW(parser_helper("trud"), json::parse_error);
			EXPECT_THROW(parser_helper("truf"), json::parse_error);
			//CHECK_THROWS_WITH(parser_helper("t"),
							  //"[json.exception.parse_error.101] parse error at 2: syntax error - invalid literal; last read: 't'");
			//CHECK_THROWS_WITH(parser_helper("tr"),
							  //"[json.exception.parse_error.101] parse error at 3: syntax error - invalid literal; last read: 'tr'");
			//CHECK_THROWS_WITH(parser_helper("tru"),
							  //"[json.exception.parse_error.101] parse error at 4: syntax error - invalid literal; last read: 'tru'");
			//CHECK_THROWS_WITH(parser_helper("trud"),
							  //"[json.exception.parse_error.101] parse error at 4: syntax error - invalid literal; last read: 'trud'");
			//CHECK_THROWS_WITH(parser_helper("truf"),
							  //"[json.exception.parse_error.101] parse error at 4: syntax error - invalid literal; last read: 'truf'");

			// unexpected end of false
			EXPECT_THROW(parser_helper("f"), json::parse_error);
			EXPECT_THROW(parser_helper("fa"), json::parse_error);
			EXPECT_THROW(parser_helper("fal"), json::parse_error);
			EXPECT_THROW(parser_helper("fals"), json::parse_error);
			EXPECT_THROW(parser_helper("falsd"), json::parse_error);
			EXPECT_THROW(parser_helper("falsf"), json::parse_error);
			//CHECK_THROWS_WITH(parser_helper("f"),
							  //"[json.exception.parse_error.101] parse error at 2: syntax error - invalid literal; last read: 'f'");
			//CHECK_THROWS_WITH(parser_helper("fa"),
							  //"[json.exception.parse_error.101] parse error at 3: syntax error - invalid literal; last read: 'fa'");
			//CHECK_THROWS_WITH(parser_helper("fal"),
							  //"[json.exception.parse_error.101] parse error at 4: syntax error - invalid literal; last read: 'fal'");
			//CHECK_THROWS_WITH(parser_helper("fals"),
							  //"[json.exception.parse_error.101] parse error at 5: syntax error - invalid literal; last read: 'fals'");
			//CHECK_THROWS_WITH(parser_helper("falsd"),
							  //"[json.exception.parse_error.101] parse error at 5: syntax error - invalid literal; last read: 'falsd'");
			//CHECK_THROWS_WITH(parser_helper("falsf"),
							  //"[json.exception.parse_error.101] parse error at 5: syntax error - invalid literal; last read: 'falsf'");

			// missing/unexpected end of array
			EXPECT_THROW(parser_helper("["), json::parse_error);
			EXPECT_THROW(parser_helper("[1"), json::parse_error);
			EXPECT_THROW(parser_helper("[1,"), json::parse_error);
			EXPECT_THROW(parser_helper("[1,]"), json::parse_error);
			EXPECT_THROW(parser_helper("]"), json::parse_error);
			//CHECK_THROWS_WITH(parser_helper("["),
							  //"[json.exception.parse_error.101] parse error at 2: syntax error - unexpected end of input; expected '[', '{', or a literal");
			//CHECK_THROWS_WITH(parser_helper("[1"),
							  //"[json.exception.parse_error.101] parse error at 3: syntax error - unexpected end of input; expected ']'");
			//CHECK_THROWS_WITH(parser_helper("[1,"),
							  //"[json.exception.parse_error.101] parse error at 4: syntax error - unexpected end of input; expected '[', '{', or a literal");
			//CHECK_THROWS_WITH(parser_helper("[1,]"),
							  //"[json.exception.parse_error.101] parse error at 4: syntax error - unexpected ']'; expected '[', '{', or a literal");
			//CHECK_THROWS_WITH(parser_helper("]"),
							  //"[json.exception.parse_error.101] parse error at 1: syntax error - unexpected ']'; expected '[', '{', or a literal");

			// missing/unexpected end of object
			EXPECT_THROW(parser_helper("{"), json::parse_error);
			EXPECT_THROW(parser_helper("{\"foo\""), json::parse_error);
			EXPECT_THROW(parser_helper("{\"foo\":"), json::parse_error);
			EXPECT_THROW(parser_helper("{\"foo\":}"), json::parse_error);
			EXPECT_THROW(parser_helper("{\"foo\":1,}"), json::parse_error);
			EXPECT_THROW(parser_helper("}"), json::parse_error);
			//CHECK_THROWS_WITH(parser_helper("{"),
							  //"[json.exception.parse_error.101] parse error at 2: syntax error - unexpected end of input; expected string literal");
			//CHECK_THROWS_WITH(parser_helper("{\"foo\""),
							  //"[json.exception.parse_error.101] parse error at 7: syntax error - unexpected end of input; expected ':'");
			//CHECK_THROWS_WITH(parser_helper("{\"foo\":"),
							  //"[json.exception.parse_error.101] parse error at 8: syntax error - unexpected end of input; expected '[', '{', or a literal");
			//CHECK_THROWS_WITH(parser_helper("{\"foo\":}"),
							  //"[json.exception.parse_error.101] parse error at 8: syntax error - unexpected '}'; expected '[', '{', or a literal");
			//CHECK_THROWS_WITH(parser_helper("{\"foo\":1,}"),
							  //"[json.exception.parse_error.101] parse error at 10: syntax error - unexpected '}'; expected string literal");
			//CHECK_THROWS_WITH(parser_helper("}"),
							  //"[json.exception.parse_error.101] parse error at 1: syntax error - unexpected '}'; expected '[', '{', or a literal");

			// missing/unexpected end of string
			EXPECT_THROW(parser_helper("\""), json::parse_error);
			EXPECT_THROW(parser_helper("\"\\\""), json::parse_error);
			EXPECT_THROW(parser_helper("\"\\u\""), json::parse_error);
			EXPECT_THROW(parser_helper("\"\\u0\""), json::parse_error);
			EXPECT_THROW(parser_helper("\"\\u01\""), json::parse_error);
			EXPECT_THROW(parser_helper("\"\\u012\""), json::parse_error);
			EXPECT_THROW(parser_helper("\"\\u"), json::parse_error);
			EXPECT_THROW(parser_helper("\"\\u0"), json::parse_error);
			EXPECT_THROW(parser_helper("\"\\u01"), json::parse_error);
			EXPECT_THROW(parser_helper("\"\\u012"), json::parse_error);
			//CHECK_THROWS_WITH(parser_helper("\""),
							  //"[json.exception.parse_error.101] parse error at 2: syntax error - invalid string: missing closing quote; last read: '\"'");
			//CHECK_THROWS_WITH(parser_helper("\"\\\""),
							  //"[json.exception.parse_error.101] parse error at 4: syntax error - invalid string: missing closing quote; last read: '\"\\\"'");
			//CHECK_THROWS_WITH(parser_helper("\"\\u\""),
							  //"[json.exception.parse_error.101] parse error at 4: syntax error - invalid string: '\\u' must be followed by 4 hex digits; last read: '\"\\u\"'");
			//CHECK_THROWS_WITH(parser_helper("\"\\u0\""),
							  //"[json.exception.parse_error.101] parse error at 5: syntax error - invalid string: '\\u' must be followed by 4 hex digits; last read: '\"\\u0\"'");
			//CHECK_THROWS_WITH(parser_helper("\"\\u01\""),
							  //"[json.exception.parse_error.101] parse error at 6: syntax error - invalid string: '\\u' must be followed by 4 hex digits; last read: '\"\\u01\"'");
			//CHECK_THROWS_WITH(parser_helper("\"\\u012\""),
							  //"[json.exception.parse_error.101] parse error at 7: syntax error - invalid string: '\\u' must be followed by 4 hex digits; last read: '\"\\u012\"'");
			//CHECK_THROWS_WITH(parser_helper("\"\\u"),
							  //"[json.exception.parse_error.101] parse error at 4: syntax error - invalid string: '\\u' must be followed by 4 hex digits; last read: '\"\\u'");
			//CHECK_THROWS_WITH(parser_helper("\"\\u0"),
							  //"[json.exception.parse_error.101] parse error at 5: syntax error - invalid string: '\\u' must be followed by 4 hex digits; last read: '\"\\u0'");
			//CHECK_THROWS_WITH(parser_helper("\"\\u01"),
							  //"[json.exception.parse_error.101] parse error at 6: syntax error - invalid string: '\\u' must be followed by 4 hex digits; last read: '\"\\u01'");
			//CHECK_THROWS_WITH(parser_helper("\"\\u012"),
							  //"[json.exception.parse_error.101] parse error at 7: syntax error - invalid string: '\\u' must be followed by 4 hex digits; last read: '\"\\u012'");

			// invalid escapes
			for (int c = 1; c < 128; ++c)
			{
				auto s = std::string("\"\\") + std::string(1, static_cast<char>(c)) + "\"";

				switch (c)
				{
					// valid escapes
					case ('"'):
					case ('\\'):
					case ('/'):
					case ('b'):
					case ('f'):
					case ('n'):
					case ('r'):
					case ('t'):
					{
						EXPECT_NO_THROW(parser_helper(s.c_str()));
						break;
					}

					// \u must be followed with four numbers, so we skip it here
					case ('u'):
					{
						break;
					}

					// any other combination of backslash and character is invalid
					default:
					{
						EXPECT_THROW(parser_helper(s.c_str()), json::parse_error);
						// only check error message if c is not a control character
						if (c > 0x1f)
						{
							//CHECK_THROWS_WITH(parser_helper(s.c_str()),
											  //"[json.exception.parse_error.101] parse error at 3: syntax error - invalid string: forbidden character after backslash; last read: '\"\\" + std::string(1, static_cast<char>(c)) + "'");
						}
						break;
					}
				}
			}

			// invalid \uxxxx escapes
			{
				// check whether character is a valid hex character
				const auto valid = [](int c)
				{
					switch (c)
					{
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
						case ('a'):
						case ('b'):
						case ('c'):
						case ('d'):
						case ('e'):
						case ('f'):
						case ('A'):
						case ('B'):
						case ('C'):
						case ('D'):
						case ('E'):
						case ('F'):
						{
							return true;
						}

						default:
						{
							return false;
						}
					}
				};

				for (int c = 1; c < 128; ++c)
				{
					std::string s = "\"\\u";

					// create a string with the iterated character at each position
					auto s1 = s + "000" + std::string(1, static_cast<char>(c)) + "\"";
					auto s2 = s + "00" + std::string(1, static_cast<char>(c)) + "0\"";
					auto s3 = s + "0" + std::string(1, static_cast<char>(c)) + "00\"";
					auto s4 = s + std::string(1, static_cast<char>(c)) + "000\"";

					if (valid(c))
					{
						//CAPTURE(s1);
						EXPECT_NO_THROW(parser_helper(s1.c_str()));
						//CAPTURE(s2);
						EXPECT_NO_THROW(parser_helper(s2.c_str()));
						//CAPTURE(s3);
						EXPECT_NO_THROW(parser_helper(s3.c_str()));
						//CAPTURE(s4);
						EXPECT_NO_THROW(parser_helper(s4.c_str()));
					}
					else
					{
						//CAPTURE(s1);
						EXPECT_THROW(parser_helper(s1.c_str()), json::parse_error);
						// only check error message if c is not a control character
						if (c > 0x1f)
						{
							//CHECK_THROWS_WITH(parser_helper(s1.c_str()),
											  //"[json.exception.parse_error.101] parse error at 7: syntax error - invalid string: '\\u' must be followed by 4 hex digits; last read: '" + s1.substr(0, 7) + "'");
						}

						//CAPTURE(s2);
						EXPECT_THROW(parser_helper(s2.c_str()), json::parse_error);
						// only check error message if c is not a control character
						if (c > 0x1f)
						{
							//CHECK_THROWS_WITH(parser_helper(s2.c_str()),
											  //"[json.exception.parse_error.101] parse error at 6: syntax error - invalid string: '\\u' must be followed by 4 hex digits; last read: '" + s2.substr(0, 6) + "'");
						}

						//CAPTURE(s3);
						EXPECT_THROW(parser_helper(s3.c_str()), json::parse_error);
						// only check error message if c is not a control character
						if (c > 0x1f)
						{
							//CHECK_THROWS_WITH(parser_helper(s3.c_str()),
											  //"[json.exception.parse_error.101] parse error at 5: syntax error - invalid string: '\\u' must be followed by 4 hex digits; last read: '" + s3.substr(0, 5) + "'");
						}

						//CAPTURE(s4);
						EXPECT_THROW(parser_helper(s4.c_str()), json::parse_error);
						// only check error message if c is not a control character
						if (c > 0x1f)
						{
							//CHECK_THROWS_WITH(parser_helper(s4.c_str()),
											  //"[json.exception.parse_error.101] parse error at 4: syntax error - invalid string: '\\u' must be followed by 4 hex digits; last read: '" + s4.substr(0, 4) + "'");
						}
					}
				}
			}

			// missing part of a surrogate pair
			EXPECT_THROW(json::parse("\"\\uD80C\""), json::parse_error);
			//CHECK_THROWS_WITH(json::parse("\"\\uD80C\""),
							  //"[json.exception.parse_error.101] parse error at 8: syntax error - invalid string: surrogate U+DC00..U+DFFF must be followed by U+DC00..U+DFFF; last read: '\"\\uD80C\"'");
			// invalid surrogate pair
			EXPECT_THROW(json::parse("\"\\uD80C\\uD80C\""), json::parse_error);
			EXPECT_THROW(json::parse("\"\\uD80C\\u0000\""), json::parse_error);
			EXPECT_THROW(json::parse("\"\\uD80C\\uFFFF\""), json::parse_error);
			//CHECK_THROWS_WITH(json::parse("\"\\uD80C\\uD80C\""),
							  //"[json.exception.parse_error.101] parse error at 13: syntax error - invalid string: surrogate U+DC00..U+DFFF must be followed by U+DC00..U+DFFF; last read: '\"\\uD80C\\uD80C'");
			//CHECK_THROWS_WITH(json::parse("\"\\uD80C\\u0000\""),
							  //"[json.exception.parse_error.101] parse error at 13: syntax error - invalid string: surrogate U+DC00..U+DFFF must be followed by U+DC00..U+DFFF; last read: '\"\\uD80C\\u0000'");
			//CHECK_THROWS_WITH(json::parse("\"\\uD80C\\uFFFF\""),
							  //"[json.exception.parse_error.101] parse error at 13: syntax error - invalid string: surrogate U+DC00..U+DFFF must be followed by U+DC00..U+DFFF; last read: '\"\\uD80C\\uFFFF'");
		}

		//TEST(class_parser,"parse errors (accept)")
		{
			// unexpected end of number
			EXPECT_TRUE(accept_helper("0.") == false);
			EXPECT_TRUE(accept_helper("-") == false);
			EXPECT_TRUE(accept_helper("--") == false);
			EXPECT_TRUE(accept_helper("-0.") == false);
			EXPECT_TRUE(accept_helper("-.") == false);
			EXPECT_TRUE(accept_helper("-:") == false);
			EXPECT_TRUE(accept_helper("0.:") == false);
			EXPECT_TRUE(accept_helper("e.") == false);
			EXPECT_TRUE(accept_helper("1e.") == false);
			EXPECT_TRUE(accept_helper("1e/") == false);
			EXPECT_TRUE(accept_helper("1e:") == false);
			EXPECT_TRUE(accept_helper("1E.") == false);
			EXPECT_TRUE(accept_helper("1E/") == false);
			EXPECT_TRUE(accept_helper("1E:") == false);

			// unexpected end of null
			EXPECT_TRUE(accept_helper("n") == false);
			EXPECT_TRUE(accept_helper("nu") == false);
			EXPECT_TRUE(accept_helper("nul") == false);

			// unexpected end of true
			EXPECT_TRUE(accept_helper("t") == false);
			EXPECT_TRUE(accept_helper("tr") == false);
			EXPECT_TRUE(accept_helper("tru") == false);

			// unexpected end of false
			EXPECT_TRUE(accept_helper("f") == false);
			EXPECT_TRUE(accept_helper("fa") == false);
			EXPECT_TRUE(accept_helper("fal") == false);
			EXPECT_TRUE(accept_helper("fals") == false);

			// missing/unexpected end of array
			EXPECT_TRUE(accept_helper("[") == false);
			EXPECT_TRUE(accept_helper("[1") == false);
			EXPECT_TRUE(accept_helper("[1,") == false);
			EXPECT_TRUE(accept_helper("[1,]") == false);
			EXPECT_TRUE(accept_helper("]") == false);

			// missing/unexpected end of object
			EXPECT_TRUE(accept_helper("{") == false);
			EXPECT_TRUE(accept_helper("{\"foo\"") == false);
			EXPECT_TRUE(accept_helper("{\"foo\":") == false);
			EXPECT_TRUE(accept_helper("{\"foo\":}") == false);
			EXPECT_TRUE(accept_helper("{\"foo\":1,}") == false);
			EXPECT_TRUE(accept_helper("}") == false);

			// missing/unexpected end of string
			EXPECT_TRUE(accept_helper("\"") == false);
			EXPECT_TRUE(accept_helper("\"\\\"") == false);
			EXPECT_TRUE(accept_helper("\"\\u\"") == false);
			EXPECT_TRUE(accept_helper("\"\\u0\"") == false);
			EXPECT_TRUE(accept_helper("\"\\u01\"") == false);
			EXPECT_TRUE(accept_helper("\"\\u012\"") == false);
			EXPECT_TRUE(accept_helper("\"\\u") == false);
			EXPECT_TRUE(accept_helper("\"\\u0") == false);
			EXPECT_TRUE(accept_helper("\"\\u01") == false);
			EXPECT_TRUE(accept_helper("\"\\u012") == false);

			// invalid escapes
			for (int c = 1; c < 128; ++c)
			{
				auto s = std::string("\"\\") + std::string(1, static_cast<char>(c)) + "\"";

				switch (c)
				{
					// valid escapes
					case ('"'):
					case ('\\'):
					case ('/'):
					case ('b'):
					case ('f'):
					case ('n'):
					case ('r'):
					case ('t'):
					{
						EXPECT_TRUE(json::parser(nlohmann::detail::input_adapter(std::string(s.c_str()))).accept());
						break;
					}

					// \u must be followed with four numbers, so we skip it here
					case ('u'):
					{
						break;
					}

					// any other combination of backslash and character is invalid
					default:
					{
						EXPECT_TRUE(json::parser(nlohmann::detail::input_adapter(std::string(s.c_str()))).accept() == false);
						break;
					}
				}
			}

			// invalid \uxxxx escapes
			{
				// check whether character is a valid hex character
				const auto valid = [](int c)
				{
					switch (c)
					{
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
						case ('a'):
						case ('b'):
						case ('c'):
						case ('d'):
						case ('e'):
						case ('f'):
						case ('A'):
						case ('B'):
						case ('C'):
						case ('D'):
						case ('E'):
						case ('F'):
						{
							return true;
						}

						default:
						{
							return false;
						}
					}
				};

				for (int c = 1; c < 128; ++c)
				{
					std::string s = "\"\\u";

					// create a string with the iterated character at each position
					auto s1 = s + "000" + std::string(1, static_cast<char>(c)) + "\"";
					auto s2 = s + "00" + std::string(1, static_cast<char>(c)) + "0\"";
					auto s3 = s + "0" + std::string(1, static_cast<char>(c)) + "00\"";
					auto s4 = s + std::string(1, static_cast<char>(c)) + "000\"";

					if (valid(c))
					{
						//CAPTURE(s1);
						EXPECT_TRUE(json::parser(nlohmann::detail::input_adapter(std::string(s1.c_str()))).accept());
						//CAPTURE(s2);
						EXPECT_TRUE(json::parser(nlohmann::detail::input_adapter(std::string(s2.c_str()))).accept());
						//CAPTURE(s3);
						EXPECT_TRUE(json::parser(nlohmann::detail::input_adapter(std::string(s3.c_str()))).accept());
						//CAPTURE(s4);
						EXPECT_TRUE(json::parser(nlohmann::detail::input_adapter(std::string(s4.c_str()))).accept());
					}
					else
					{
						//CAPTURE(s1);
						EXPECT_TRUE(json::parser(nlohmann::detail::input_adapter(std::string(s1.c_str()))).accept() == false);

						//CAPTURE(s2);
						EXPECT_TRUE(json::parser(nlohmann::detail::input_adapter(std::string(s2.c_str()))).accept() == false);

						//CAPTURE(s3);
						EXPECT_TRUE(json::parser(nlohmann::detail::input_adapter(std::string(s3.c_str()))).accept() == false);

						//CAPTURE(s4);
						EXPECT_TRUE(json::parser(nlohmann::detail::input_adapter(std::string(s4.c_str()))).accept() == false);
					}
				}
			}

			// missing part of a surrogate pair
			EXPECT_TRUE(accept_helper("\"\\uD80C\"") == false);
			// invalid surrogate pair
			EXPECT_TRUE(accept_helper("\"\\uD80C\\uD80C\"") == false);
			EXPECT_TRUE(accept_helper("\"\\uD80C\\u0000\"") == false);
			EXPECT_TRUE(accept_helper("\"\\uD80C\\uFFFF\"") == false);
		}

		//TEST(class_parser,"tests found by mutate++")
		{
			// test case to make sure no comma preceeds the first key
			EXPECT_THROW(parser_helper("{,\"key\": false}"), json::parse_error);
			//CHECK_THROWS_WITH(parser_helper("{,\"key\": false}"),
							  //"[json.exception.parse_error.101] parse error at 2: syntax error - unexpected ','; expected string literal");
			// test case to make sure an object is properly closed
			EXPECT_THROW(parser_helper("[{\"key\": false true]"), json::parse_error);
			//CHECK_THROWS_WITH(parser_helper("[{\"key\": false true]"),
							  //"[json.exception.parse_error.101] parse error at 19: syntax error - unexpected true literal; expected '}'");

			// test case to make sure the callback is properly evaluated after reading a key
			{
				json::parser_callback_t cb = [](int, json::parse_event_t event, json&)
				{
					if (event == json::parse_event_t::key)
					{
						return false;
					}
					else
					{
						return true;
					}
				};

				json x = json::parse("{\"key\": false}", cb);
				EXPECT_TRUE(x == json::object());
			}
		}

		//TEST(class_parser,"callback function")
		{
			auto s_object = R"(
				{
					"foo": 2,
					"bar": {
						"baz": 1
					}
				}
			)";

			auto s_array = R"(
				[1,2,[3,4,5],4,5]
			)";

			//TEST(class_parser,"filter nothing")
			{
				json j_object = json::parse(s_object, [](int, json::parse_event_t, const json&)
				{
					return true;
				});

				EXPECT_TRUE(j_object == json({{"foo", 2}, {"bar", {{"baz", 1}}}}));

				json j_array = json::parse(s_array, [](int, json::parse_event_t, const json&)
				{
					return true;
				});

				EXPECT_TRUE(j_array == json({1, 2, {3, 4, 5}, 4, 5}));
			}

			//TEST(class_parser,"filter everything")
			{
				json j_object = json::parse(s_object, [](int, json::parse_event_t, const json&)
				{
					return false;
				});

				// the top-level object will be discarded, leaving a null
				EXPECT_TRUE(j_object.is_null());

				json j_array = json::parse(s_array, [](int, json::parse_event_t, const json&)
				{
					return false;
				});

				// the top-level array will be discarded, leaving a null
				EXPECT_TRUE(j_array.is_null());
			}

			//TEST(class_parser,"filter specific element")
			{
				json j_object = json::parse(s_object, [](int, json::parse_event_t, const json & j)
				{
					// filter all number(2) elements
					if (j == json(2))
					{
						return false;
					}
					else
					{
						return true;
					}
				});

				EXPECT_TRUE(j_object == json({{"bar", {{"baz", 1}}}}));

				json j_array = json::parse(s_array, [](int, json::parse_event_t, const json & j)
				{
					if (j == json(2))
					{
						return false;
					}
					else
					{
						return true;
					}
				});

				EXPECT_TRUE(j_array == json({1, {3, 4, 5}, 4, 5}));
			}

			//TEST(class_parser,"filter specific events")
			{
				//TEST(class_parser,"first closing event")
				{
					{
						json j_object = json::parse(s_object, [](int, json::parse_event_t e, const json&)
						{
							static bool first = true;
							if (e == json::parse_event_t::object_end and first)
							{
								first = false;
								return false;
							}
							else
							{
								return true;
							}
						});

						// the first completed object will be discarded
						EXPECT_TRUE(j_object == json({{"foo", 2}}));
					}

					{
						json j_array = json::parse(s_array, [](int, json::parse_event_t e, const json&)
						{
							static bool first = true;
							if (e == json::parse_event_t::array_end and first)
							{
								first = false;
								return false;
							}
							else
							{
								return true;
							}
						});

						// the first completed array will be discarded
						EXPECT_TRUE(j_array == json({1, 2, 4, 5}));
					}
				}
			}

			//TEST(class_parser,"special cases")
			{
				// the following test cases cover the situation in which an empty
				// object and array is discarded only after the closing character
				// has been read

				json j_empty_object = json::parse("{}", [](int, json::parse_event_t e, const json&)
				{
					if (e == json::parse_event_t::object_end)
					{
						return false;
					}
					else
					{
						return true;
					}
				});
				EXPECT_TRUE(j_empty_object == json());

				json j_empty_array = json::parse("[]", [](int, json::parse_event_t e, const json&)
				{
					if (e == json::parse_event_t::array_end)
					{
						return false;
					}
					else
					{
						return true;
					}
				});
				EXPECT_TRUE(j_empty_array == json());
			}
		}

		//TEST(class_parser,"constructing from contiguous containers")
		{
			//TEST(class_parser,"from std::vector")
			{
				std::vector<uint8_t> v = {'t', 'r', 'u', 'e'};
				json j;
				json::parser(nlohmann::detail::input_adapter(std::begin(v), std::end(v))).parse(true, j);
				EXPECT_TRUE(j == json(true));
			}

			//TEST(class_parser,"from std::array")
			{
				std::array<uint8_t, 5> v { {'t', 'r', 'u', 'e'} };
				json j;
				json::parser(nlohmann::detail::input_adapter(std::begin(v), std::end(v))).parse(true, j);
				EXPECT_TRUE(j == json(true));
			}

			//TEST(class_parser,"from array")
			{
				uint8_t v[] = {'t', 'r', 'u', 'e'};
				json j;
				json::parser(nlohmann::detail::input_adapter(std::begin(v), std::end(v))).parse(true, j);
				EXPECT_TRUE(j == json(true));
			}

			//TEST(class_parser,"from char literal")
			{
				EXPECT_TRUE(parser_helper("true") == json(true));
			}

			//TEST(class_parser,"from std::string")
			{
				std::string v = {'t', 'r', 'u', 'e'};
				json j;
				json::parser(nlohmann::detail::input_adapter(std::begin(v), std::end(v))).parse(true, j);
				EXPECT_TRUE(j == json(true));
			}

			//TEST(class_parser,"from std::initializer_list")
			{
				std::initializer_list<uint8_t> v = {'t', 'r', 'u', 'e'};
				json j;
				json::parser(nlohmann::detail::input_adapter(std::begin(v), std::end(v))).parse(true, j);
				EXPECT_TRUE(j == json(true));
			}

			//TEST(class_parser,"from std::valarray")
			{
				std::valarray<uint8_t> v = {'t', 'r', 'u', 'e'};
				json j;
				json::parser(nlohmann::detail::input_adapter(std::begin(v), std::end(v))).parse(true, j);
				EXPECT_TRUE(j == json(true));
			}
		}

		//TEST(class_parser,"improve test coverage")
		{
			//TEST(class_parser,"parser with callback")
			{
				json::parser_callback_t cb = [](int, json::parse_event_t, json&)
				{
					return true;
				};

				EXPECT_TRUE(json::parse("{\"foo\": true:", cb, false).is_discarded());

				EXPECT_THROW(json::parse("{\"foo\": true:", cb), json::parse_error);
				//CHECK_THROWS_WITH(json::parse("{\"foo\": true:", cb),
								  //"[json.exception.parse_error.101] parse error at 13: syntax error - unexpected ':'; expected '}'");

				EXPECT_THROW(json::parse("1.18973e+4932", cb), json::out_of_range);
				//CHECK_THROWS_WITH(json::parse("1.18973e+4932", cb),
								  //"[json.exception.out_of_range.406] number overflow parsing '1.18973e+4932'");
			}

			//TEST(class_parser,"SAX parser")
			{
				//TEST(class_parser,"} without value")
				{
					SaxCountdown s(1);
					EXPECT_TRUE(json::sax_parse("{}", &s) == false);
				}

				//TEST(class_parser,"} with value")
				{
					SaxCountdown s(3);
					EXPECT_TRUE(json::sax_parse("{\"k1\": true}", &s) == false);
				}

				//TEST(class_parser,"second key")
				{
					SaxCountdown s(3);
					EXPECT_TRUE(json::sax_parse("{\"k1\": true, \"k2\": false}", &s) == false);
				}

				//TEST(class_parser,"] without value")
				{
					SaxCountdown s(1);
					EXPECT_TRUE(json::sax_parse("[]", &s) == false);
				}

				//TEST(class_parser,"] with value")
				{
					SaxCountdown s(2);
					EXPECT_TRUE(json::sax_parse("[1]", &s) == false);
				}

				//TEST(class_parser,"float")
				{
					SaxCountdown s(0);
					EXPECT_TRUE(json::sax_parse("3.14", &s) == false);
				}

				//TEST(class_parser,"false")
				{
					SaxCountdown s(0);
					EXPECT_TRUE(json::sax_parse("false", &s) == false);
				}

				//TEST(class_parser,"null")
				{
					SaxCountdown s(0);
					EXPECT_TRUE(json::sax_parse("null", &s) == false);
				}

				//TEST(class_parser,"true")
				{
					SaxCountdown s(0);
					EXPECT_TRUE(json::sax_parse("true", &s) == false);
				}

				//TEST(class_parser,"unsigned")
				{
					SaxCountdown s(0);
					EXPECT_TRUE(json::sax_parse("12", &s) == false);
				}

				//TEST(class_parser,"integer")
				{
					SaxCountdown s(0);
					EXPECT_TRUE(json::sax_parse("-12", &s) == false);
				}

				//TEST(class_parser,"string")
				{
					SaxCountdown s(0);
					EXPECT_TRUE(json::sax_parse("\"foo\"", &s) == false);
				}
			}
		}
	}
}
