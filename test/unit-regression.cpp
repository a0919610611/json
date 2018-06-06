#include "gtest/gtest.h"
#define private public
#include "json.hpp"

using nlohmann::json;

#include "fifo_map.hpp"

#include <fstream>
#include <list>
#include <cstdio>

namespace
{

	/////////////////////////////////////////////////////////////////////
	// for #972
	/////////////////////////////////////////////////////////////////////

	template<class K, class V, class dummy_compare, class A>
	using my_workaround_fifo_map = nlohmann::fifo_map<K, V, nlohmann::fifo_map_compare<K>, A>;
	using my_json = nlohmann::basic_json<my_workaround_fifo_map>;

	/////////////////////////////////////////////////////////////////////
	// for #977
	/////////////////////////////////////////////////////////////////////

	namespace ns
	{
	struct foo
	{
		int x;
	};

	template <typename, typename SFINAE = void>
	struct foo_serializer;

	template<typename T>
	struct foo_serializer<T, typename std::enable_if<std::is_same<foo, T>::value>::type>
	{
		template <typename BasicJsonType>
		static void to_json(BasicJsonType& j, const T& value)
		{
			j = BasicJsonType{{"x", value.x}};
		}
		template <typename BasicJsonType>
		static void from_json(const BasicJsonType& j, T& value)     // !!!
		{
			nlohmann::from_json(j.at("x"), value.x);
		}
	};

	template<typename T>
	struct foo_serializer < T, typename std::enable_if < !std::is_same<foo, T>::value >::type >
	{
		template <typename BasicJsonType>
		static void to_json(BasicJsonType& j, const T& value) noexcept
		{
			::nlohmann::to_json(j, value);
		}
		template <typename BasicJsonType>
		static void from_json(const BasicJsonType& j, T& value)   //!!!
		{
			::nlohmann::from_json(j, value);
		}
	};
	}

	using foo_json = nlohmann::basic_json<std::map, std::vector, std::string, bool, std::int64_t,
		  std::uint64_t, double, std::allocator, ns::foo_serializer>;

	/////////////////////////////////////////////////////////////////////
	// for #805
	/////////////////////////////////////////////////////////////////////

	namespace
	{
	struct nocopy
	{
		nocopy() = default;
		nocopy(const nocopy&) = delete;

		int val = 0;

		friend void to_json(json& j, const nocopy& n)
		{
			j = {{"val", n.val}};
		}
	};
	}

	/////////////////////////////////////////////////////////////////////
	// for #1021
	/////////////////////////////////////////////////////////////////////

	using float_json = nlohmann::basic_json<std::map, std::vector, std::string, bool, std::int64_t, std::uint64_t, float>;


	TEST(regression_tests, regression_tests)
	{
		//TEST(regression,"issue #60 - Double quotation mark is not parsed correctly")
		{
			//TEST(regression,"escape_dobulequote")
			{
				auto s = "[\"\\\"foo\\\"\"]";
				json j = json::parse(s);
				auto expected = R"(["\"foo\""])"_json;
				EXPECT_TRUE(j == expected);
			}
		}

		//TEST(regression,"issue #70 - Handle infinity and NaN cases")
		{
			// previously, NAN/INFINITY created a null value; now, the values are
			// properly stored, but are dumped as "null"
			//TEST(regression,"NAN value")
			{
				EXPECT_TRUE(json(NAN).dump() == "null");
				EXPECT_TRUE(json(json::number_float_t(NAN)).dump() == "null");
			}

			//TEST(regression,"infinity")
			{
				EXPECT_TRUE(json(INFINITY).dump() == "null");
				EXPECT_TRUE(json(json::number_float_t(INFINITY)).dump() == "null");
			}

			// With 3.0.0, the semantics of this changed: NAN and infinity are
			// stored properly inside the JSON value (no exception or conversion
			// to null), but are serialized as null.
			//TEST(regression,"NAN value")
			{
				json j1 = NAN;
				EXPECT_TRUE(j1.is_number_float());
				json::number_float_t f1 = j1;
				EXPECT_TRUE(std::isnan(f1));

				json j2 = json::number_float_t(NAN);
				EXPECT_TRUE(j2.is_number_float());
				json::number_float_t f2 = j2;
				EXPECT_TRUE(std::isnan(f2));
			}

			//TEST(regression,"infinity")
			{
				json j1 = INFINITY;
				EXPECT_TRUE(j1.is_number_float());
				json::number_float_t f1 = j1;
				EXPECT_TRUE(not std::isfinite(f1));

				json j2 = json::number_float_t(INFINITY);
				EXPECT_TRUE(j2.is_number_float());
				json::number_float_t f2 = j2;
				EXPECT_TRUE(not std::isfinite(f2));
			}
		}

		//TEST(regression,"pull request #71 - handle enum type")
		{
			enum { t = 0, u = 102};
			json j = json::array();
			j.push_back(t);

			// maybe this is not the place to test this?
			json j2 = u;

			auto anon_enum_value = j2.get<decltype(u)>();
			EXPECT_TRUE(u == anon_enum_value);

			// check if the actual value was stored
			EXPECT_TRUE(j2 == 102);

			static_assert(std::is_same<decltype(anon_enum_value), decltype(u)>::value, "");

			j.push_back(json::object(
			{
				{"game_type", t}
			}));
		}

		//TEST(regression,"issue #76 - dump() / parse() not idempotent")
		{
			// create JSON object
			json fields;
			fields["one"] = std::string("one");
			fields["two"] = std::string("two three");
			fields["three"] = std::string("three \"four\"");

			// create another JSON object by deserializing the serialization
			std::string payload = fields.dump();
			json parsed_fields = json::parse(payload);

			// check individual fields to match both objects
			EXPECT_TRUE(parsed_fields["one"] == fields["one"]);
			EXPECT_TRUE(parsed_fields["two"] == fields["two"]);
			EXPECT_TRUE(parsed_fields["three"] == fields["three"]);

			// check individual fields to match original input
			EXPECT_TRUE(parsed_fields["one"] == std::string("one"));
			EXPECT_TRUE(parsed_fields["two"] == std::string("two three"));
			EXPECT_TRUE(parsed_fields["three"] == std::string("three \"four\""));

			// check equality of the objects
			EXPECT_TRUE(parsed_fields == fields);

			// check equality of the serialized objects
			EXPECT_TRUE(fields.dump() == parsed_fields.dump());

			// check everything in one line
			EXPECT_TRUE(fields == json::parse(fields.dump()));
		}

		//TEST(regression,"issue #82 - lexer::get_number return NAN")
		{
			const auto content = R"(
			{
				"Test":"Test1",
				"Number":100,
				"Foo":42.42
			})";

			std::stringstream ss;
			ss << content;
			json j;
			ss >> j;

			std::string test = j["Test"];
			EXPECT_TRUE(test == "Test1");
			int number = j["Number"];
			EXPECT_TRUE(number == 100);
			float foo = j["Foo"];
			EXPECT_FLOAT_EQ(foo, 42.42);
		}

		//TEST(regression,"issue #89 - nonstandard integer type")
		{
			// create JSON class with nonstandard integer number type
			using custom_json =
				nlohmann::basic_json<std::map, std::vector, std::string, bool, int32_t, uint32_t, float>;
			custom_json j;
			j["int_1"] = 1;
			// we need to cast to int to compile with Catch - the value is int32_t
			EXPECT_TRUE(static_cast<int>(j["int_1"]) == 1);

			// tests for correct handling of non-standard integers that overflow the type selected by the user

			// unsigned integer object creation - expected to wrap and still be stored as an integer
			j = 4294967296U; // 2^32
			EXPECT_TRUE(static_cast<int>(j.type()) == static_cast<int>(custom_json::value_t::number_unsigned));
			EXPECT_TRUE(j.get<uint32_t>() == 0);  // Wrap

			// unsigned integer parsing - expected to overflow and be stored as a float
			j = custom_json::parse("4294967296"); // 2^32
			EXPECT_TRUE(static_cast<int>(j.type()) == static_cast<int>(custom_json::value_t::number_float));
			EXPECT_TRUE(j.get<float>() == 4294967296.0f);

			// integer object creation - expected to wrap and still be stored as an integer
			j = -2147483649LL; // -2^31-1
			EXPECT_TRUE(static_cast<int>(j.type()) == static_cast<int>(custom_json::value_t::number_integer));
			EXPECT_TRUE(j.get<int32_t>() == 2147483647);  // Wrap

			// integer parsing - expected to overflow and be stored as a float with rounding
			j = custom_json::parse("-2147483649"); // -2^31
			EXPECT_TRUE(static_cast<int>(j.type()) == static_cast<int>(custom_json::value_t::number_float));
			EXPECT_TRUE(j.get<float>() == -2147483650.0f);
		}

		//TEST(regression,"issue #93 reverse_iterator operator inheritance problem")
		{
			{
				json a = {1, 2, 3};
				json::reverse_iterator rit = a.rbegin();
				++rit;
				EXPECT_TRUE(*rit == json(2));
				EXPECT_TRUE(rit.value() == json(2));
			}
			{
				json a = {1, 2, 3};
				json::reverse_iterator rit = ++a.rbegin();
				EXPECT_TRUE(*rit == json(2));
				EXPECT_TRUE(rit.value() == json(2));
			}
			{
				json a = {1, 2, 3};
				json::reverse_iterator rit = a.rbegin();
				++rit;
				json b = {0, 0, 0};
				std::transform(rit, a.rend(), b.rbegin(), [](json el)
				{
					return el;
				});
				EXPECT_TRUE(b == json({0, 1, 2}));
			}
			{
				json a = {1, 2, 3};
				json b = {0, 0, 0};
				std::transform(++a.rbegin(), a.rend(), b.rbegin(), [](json el)
				{
					return el;
				});
				EXPECT_TRUE(b == json({0, 1, 2}));
			}
		}

		//TEST(regression,"issue #100 - failed to iterator json object with reverse_iterator")
		{
			json config =
			{
				{ "111", 111 },
				{ "112", 112 },
				{ "113", 113 }
			};

			std::stringstream ss;

			for (auto it = config.begin(); it != config.end(); ++it)
			{
				ss << it.key() << ": " << it.value() << '\n';
			}

			for (auto it = config.rbegin(); it != config.rend(); ++it)
			{
				ss << it.key() << ": " << it.value() << '\n';
			}

			EXPECT_TRUE(ss.str() == "111: 111\n112: 112\n113: 113\n113: 113\n112: 112\n111: 111\n");
		}

		//TEST(regression,"issue #101 - binary string causes numbers to be dumped as hex")
		{
			int64_t number = 10;
			std::string bytes{"\x00" "asdf\n", 6};
			json j;
			j["int64"] = number;
			j["binary string"] = bytes;
			// make sure the number is really printed as decimal "10" and not as
			// hexadecimal "a"
			EXPECT_TRUE(j.dump() == "{\"binary string\":\"\\u0000asdf\\n\",\"int64\":10}");
		}

		//TEST(regression,"issue #111 - subsequent unicode chars")
		{
			std::string bytes{0x7, 0x7};
			json j;
			j["string"] = bytes;
			EXPECT_TRUE(j["string"] == "\u0007\u0007");
		}

		//TEST(regression,"issue #144 - implicit assignment to std::string fails")
		{
			json o = {{"name", "value"}};

			std::string s1 = o["name"];
			EXPECT_TRUE(s1 == "value");

			std::string s2;
			s2 = o["name"];

			EXPECT_TRUE(s2 == "value");
		}

		//TEST(regression,"issue #146 - character following a surrogate pair is skipped")
		{
			EXPECT_TRUE(json::parse("\"\\ud80c\\udc60abc\"").get<json::string_t>() == u8"\U00013060abc");
		}

		//TEST(regression,"issue #171 - Cannot index by key of type static constexpr const char*")
		{
			json j;

			// Non-const access with key as "char []"
			char array_key[] = "Key1";
			EXPECT_NO_THROW(j[array_key] = 1);
			EXPECT_TRUE(j[array_key] == json(1));

			// Non-const access with key as "const char[]"
			const char const_array_key[] = "Key2";
			EXPECT_NO_THROW(j[const_array_key] = 2);
			EXPECT_TRUE(j[const_array_key] == json(2));

			// Non-const access with key as "char *"
			char _ptr_key[] = "Key3";
			char* ptr_key = &_ptr_key[0];
			EXPECT_NO_THROW(j[ptr_key] = 3);
			EXPECT_TRUE(j[ptr_key] == json(3));

			// Non-const access with key as "const char *"
			const char* const_ptr_key = "Key4";
			EXPECT_NO_THROW(j[const_ptr_key] = 4);
			EXPECT_TRUE(j[const_ptr_key] == json(4));

			// Non-const access with key as "static constexpr const char *"
			static constexpr const char* constexpr_ptr_key = "Key5";
			EXPECT_NO_THROW(j[constexpr_ptr_key] = 5);
			EXPECT_TRUE(j[constexpr_ptr_key] == json(5));

			const json j_const = j;

			// Const access with key as "char []"
			EXPECT_TRUE(j_const[array_key] == json(1));

			// Const access with key as "const char[]"
			EXPECT_TRUE(j_const[const_array_key] == json(2));

			// Const access with key as "char *"
			EXPECT_TRUE(j_const[ptr_key] == json(3));

			// Const access with key as "const char *"
			EXPECT_TRUE(j_const[const_ptr_key] == json(4));

			// Const access with key as "static constexpr const char *"
			EXPECT_TRUE(j_const[constexpr_ptr_key] == json(5));
		}

		//TEST(regression,"issue #186 miloyip/nativejson-benchmark: floating-point parsing")
		{
			json j;

			j = json::parse("-0.0");
			EXPECT_TRUE(j.get<double>() == -0.0);

			j = json::parse("2.22507385850720113605740979670913197593481954635164564e-308");
			EXPECT_TRUE(j.get<double>() == 2.2250738585072009e-308);

			j = json::parse("0.999999999999999944488848768742172978818416595458984374");
			EXPECT_TRUE(j.get<double>() == 0.99999999999999989);

			j = json::parse("1.00000000000000011102230246251565404236316680908203126");
			EXPECT_TRUE(j.get<double>() == 1.00000000000000022);

			j = json::parse("7205759403792793199999e-5");
			EXPECT_TRUE(j.get<double>() == 72057594037927928.0);

			j = json::parse("922337203685477529599999e-5");
			EXPECT_TRUE(j.get<double>() == 9223372036854774784.0);

			j = json::parse("1014120480182583464902367222169599999e-5");
			EXPECT_TRUE(j.get<double>() == 10141204801825834086073718800384.0);

			j = json::parse("5708990770823839207320493820740630171355185151999e-3");
			EXPECT_TRUE(j.get<double>() == 5708990770823838890407843763683279797179383808.0);

			// create JSON class with nonstandard float number type

			// float
			nlohmann::basic_json<std::map, std::vector, std::string, bool, int32_t, uint32_t, float> j_float =
				1.23e25f;
			EXPECT_TRUE(j_float.get<float>() == 1.23e25f);

			// double
			nlohmann::basic_json<std::map, std::vector, std::string, bool, int64_t, uint64_t, double> j_double =
				1.23e35;
			EXPECT_TRUE(j_double.get<double>() == 1.23e35);

			// long double
			nlohmann::basic_json<std::map, std::vector, std::string, bool, int64_t, uint64_t, long double>
			j_long_double = 1.23e45L;
			EXPECT_TRUE(j_long_double.get<long double>() == 1.23e45L);
		}

		//TEST(regression,"issue #228 - double values are serialized with commas as decimal points")
		{
			json j1a = 2312.42;
			json j1b = json::parse("2312.42");

			json j2a = 2342e-2;
			//issue #230
			//json j2b = json::parse("2342e-2");

			json j3a = 10E3;
			json j3b = json::parse("10E3");
			json j3c = json::parse("10e3");

			// class to create a locale that would use a comma for decimals
			class CommaDecimalSeparator : public std::numpunct<char>
			{
			  protected:
				char do_decimal_point() const override
				{
					return ',';
				}

				char do_thousands_sep() const override
				{
					return '.';
				}

				std::string do_grouping() const override
				{
					return "\03";
				}
			};

			// change locale to mess with decimal points
			auto orig_locale = std::locale::global(std::locale(std::locale(), new CommaDecimalSeparator));

			EXPECT_TRUE(j1a.dump() == "2312.42");
			EXPECT_TRUE(j1b.dump() == "2312.42");

			// check if locale is properly reset
			std::stringstream ss;
			ss.imbue(std::locale(std::locale(), new CommaDecimalSeparator));
			ss << 4712.11;
			EXPECT_TRUE(ss.str() == "4.712,11");
			ss << j1a;
			EXPECT_TRUE(ss.str() == "4.712,112312.42");
			ss << 47.11;
			EXPECT_TRUE(ss.str() == "4.712,112312.4247,11");

			EXPECT_TRUE(j2a.dump() == "23.42");
			//issue #230
			//EXPECT_TRUE(j2b.dump() == "23.42");

			EXPECT_TRUE(j3a.dump() == "10000.0");
			EXPECT_TRUE(j3b.dump() == "10000.0");
			EXPECT_TRUE(j3c.dump() == "10000.0");
			//EXPECT_TRUE(j3b.dump() == "1E04"); // roundtrip error
			//EXPECT_TRUE(j3c.dump() == "1e04"); // roundtrip error

			std::locale::global(orig_locale);
		}

		//TEST(regression,"issue #378 - locale-independent num-to-str")
		{
			setlocale(LC_NUMERIC, "de_DE.UTF-8");

			// verify that dumped correctly with '.' and no grouping
			const json j1 = 12345.67;
			EXPECT_TRUE(json(12345.67).dump() == "12345.67");
			setlocale(LC_NUMERIC, "C");
		}

		//TEST(regression,"issue #379 - locale-independent str-to-num")
		{
			setlocale(LC_NUMERIC, "de_DE.UTF-8");

			// verify that parsed correctly despite using strtod internally
			EXPECT_TRUE(json::parse("3.14").get<double>() == 3.14);

			// check a different code path
			EXPECT_TRUE(json::parse("1.000000000000000000000000000000000000000000000000000000000000000000000000").get<double>() == 1.0);
		}

		//TEST(regression,"issue #233 - Can't use basic_json::iterator as a base iterator for std::move_iterator")
		{
			json source = {"a", "b", "c"};
			json expected = {"a", "b"};
			json dest;

			std::copy_n(std::make_move_iterator(source.begin()), 2, std::back_inserter(dest));

			EXPECT_TRUE(dest == expected);
		}

		//TEST(regression,"issue #235 - ambiguous overload for 'push_back' and 'operator+='")
		{
			json data = {{"key", "value"}};
			data.push_back({"key2", "value2"});
			data += {"key3", "value3"};

			EXPECT_TRUE(data == json({{"key", "value"}, {"key2", "value2"}, {"key3", "value3"}}));
		}

		//TEST(regression,"issue #269 - diff generates incorrect patch when removing multiple array elements")
		{
			json doc = R"( { "arr1": [1, 2, 3, 4] } )"_json;
			json expected = R"( { "arr1": [1, 2] } )"_json;

			// check roundtrip
			EXPECT_TRUE(doc.patch(json::diff(doc, expected)) == expected);
		}

		//TEST(regression,"issue #283 - value() does not work with _json_pointer types")
		{
			json j =
			{
				{"object", {{"key1", 1}, {"key2", 2}}},
			};

			int at_integer = j.at("/object/key2"_json_pointer);
			int val_integer = j.value("/object/key2"_json_pointer, 0);

			EXPECT_TRUE(at_integer == val_integer);
		}

		//TEST(regression,"issue #304 - Unused variable warning")
		{
			// code triggered a "warning: unused variable" warning and is left
			// here to avoid the warning in the future
			json object;
			json patch = json::array();
			object = object.patch(patch);
		}

		//TEST(regression,"issue #306 - Parsing fails without space at end of file")
		{
			for (auto filename :
					{
						"test/data/regression/broken_file.json",
						"test/data/regression/working_file.json"
					})
			{
				//CAPTURE(filename);
				json j;
				std::ifstream f(filename);
				EXPECT_NO_THROW(f >> j);
			}
		}

		//TEST(regression,"issue #310 - make json_benchmarks no longer working in 2.0.4")
		{
			for (auto filename :
					{
						"test/data/regression/floats.json",
						"test/data/regression/signed_ints.json",
						"test/data/regression/unsigned_ints.json"
					})
			{
				//CAPTURE(filename);
				json j;
				std::ifstream f(filename);
				EXPECT_NO_THROW(f >> j);
			}
		}

		//TEST(regression,"issue #323 - add nested object capabilities to pointers")
		{
			json j;
			j["/this/that/2"_json_pointer] = 27;
			EXPECT_TRUE(j == json({{"this", {{"that", {nullptr, nullptr, 27}}}}}));
		}

		//TEST(regression,"issue #329 - serialized value not always can be parsed")
		{
			EXPECT_THROW(json::parse("22e2222"), json::out_of_range);
			//CHECK_THROWS_WITH(json::parse("22e2222"),
							  //"[json.exception.out_of_range.406] number overflow parsing '22e2222'");
		}

		//TEST(regression,"issue #360 - Loss of precision when serializing <double>")
		{
			auto check_roundtrip = [](double number)
			{
				//CAPTURE(number);

				json j = number;
				EXPECT_TRUE(j.is_number_float());

				std::stringstream ss;
				ss << j;

				EXPECT_NO_THROW(ss >> j);
				EXPECT_TRUE(j.is_number_float());
				EXPECT_TRUE(j.get<json::number_float_t>() == number);
			};

			check_roundtrip(100000000000.1236);
			check_roundtrip(std::numeric_limits<json::number_float_t>::max());

			// Some more numbers which fail to roundtrip when serialized with digits10 significand digits (instead of max_digits10)
			check_roundtrip(1.541888611948064e-17);
			check_roundtrip(5.418771028591015e-16);
			check_roundtrip(9.398685592608595e-15);
			check_roundtrip(8.826843952762347e-14);
			check_roundtrip(8.143291313475335e-13);
			check_roundtrip(4.851328172762508e-12);
			check_roundtrip(6.677850998084358e-11);
			check_roundtrip(3.995398518174525e-10);
			check_roundtrip(1.960452605645124e-9);
			check_roundtrip(3.551812586302883e-8);
			check_roundtrip(2.947988411689261e-7);
			check_roundtrip(8.210166748056192e-6);
			check_roundtrip(6.104889704266753e-5);
			check_roundtrip(0.0008629954631330876);
			check_roundtrip(0.004936993881051611);
			check_roundtrip(0.08309725102608073);
			check_roundtrip(0.5210494268499783);
			check_roundtrip(6.382927930939767);
			check_roundtrip(59.94947245358671);
			check_roundtrip(361.0838651266122);
			check_roundtrip(4678.354596181877);
			check_roundtrip(61412.17658956043);
			check_roundtrip(725696.0799057782);
			check_roundtrip(2811732.583399828);
			check_roundtrip(30178351.07533605);
			check_roundtrip(689684880.3235844);
			check_roundtrip(5714887673.555147);
			check_roundtrip(84652038821.18808);
			check_roundtrip(156510583431.7721);
			check_roundtrip(5938450569021.732);
			check_roundtrip(83623297654460.33);
			check_roundtrip(701466573254773.6);
			check_roundtrip(1369013370304513);
			check_roundtrip(96963648023094720);
			check_roundtrip(3.478237409280108e+17);
		}

		//TEST(regression,"issue #366 - json::parse on failed stream gets stuck")
		{
			std::ifstream f("file_not_found.json");
			EXPECT_THROW(json::parse(f), json::parse_error);
			//CHECK_THROWS_WITH(json::parse(f), "[json.exception.parse_error.101] parse error at 1: syntax error - unexpected end of input; expected '[', '{', or a literal");
		}

		//TEST(regression,"issue #367 - calling stream at EOF")
		{
			std::stringstream ss;
			json j;
			ss << "123";
			EXPECT_NO_THROW(ss >> j);

			// see https://github.com/nlohmann/json/issues/367#issuecomment-262841893:
			// ss is not at EOF; this yielded an error before the fix
			// (threw basic_string::append). No, it should just throw
			// a parse error because of the EOF.
			EXPECT_THROW(ss >> j, json::parse_error);
			//CHECK_THROWS_WITH(ss >> j,
							  //"[json.exception.parse_error.101] parse error at 1: syntax error - unexpected end of input; expected '[', '{', or a literal");
		}

		//TEST(regression,"issue #367 - behavior of operator>> should more closely resemble that of built-in overloads")
		{
			//TEST(regression,"(empty)")
			{
				std::stringstream ss;
				json j;
				EXPECT_THROW(ss >> j, json::parse_error);
				//CHECK_THROWS_WITH(ss >> j,
								  //"[json.exception.parse_error.101] parse error at 1: syntax error - unexpected end of input; expected '[', '{', or a literal");
			}

			//TEST(regression,"(whitespace)")
			{
				std::stringstream ss;
				ss << "   ";
				json j;
				EXPECT_THROW(ss >> j, json::parse_error);
				//CHECK_THROWS_WITH(ss >> j,
								  //"[json.exception.parse_error.101] parse error at 1: syntax error - unexpected end of input; expected '[', '{', or a literal");
			}

			//TEST(regression,"one value")
			{
				std::stringstream ss;
				ss << "111";
				json j;
				EXPECT_NO_THROW(ss >> j);
				EXPECT_TRUE(j == 111);

				EXPECT_THROW(ss >> j, json::parse_error);
				//CHECK_THROWS_WITH(ss >> j,
								  //"[json.exception.parse_error.101] parse error at 1: syntax error - unexpected end of input; expected '[', '{', or a literal");
			}

			//TEST(regression,"one value + whitespace")
			{
				std::stringstream ss;
				ss << "222 \t\n";
				json j;
				EXPECT_NO_THROW(ss >> j);
				EXPECT_TRUE(j == 222);

				EXPECT_THROW(ss >> j, json::parse_error);
				//CHECK_THROWS_WITH(ss >> j,
								  //"[json.exception.parse_error.101] parse error at 1: syntax error - unexpected end of input; expected '[', '{', or a literal");
			}

			//TEST(regression,"whitespace + one value")
			{
				std::stringstream ss;
				ss << "\n\t 333";
				json j;
				EXPECT_NO_THROW(ss >> j);
				EXPECT_TRUE(j == 333);

				EXPECT_THROW(ss >> j, json::parse_error);
				//CHECK_THROWS_WITH(ss >> j,
								  //"[json.exception.parse_error.101] parse error at 1: syntax error - unexpected end of input; expected '[', '{', or a literal");
			}

			//TEST(regression,"three values")
			{
				std::stringstream ss;
				ss << " 111 \n222\n \n  333";
				json j;
				EXPECT_NO_THROW(ss >> j);
				EXPECT_TRUE(j == 111);
				EXPECT_NO_THROW(ss >> j);
				EXPECT_TRUE(j == 222);
				EXPECT_NO_THROW(ss >> j);
				EXPECT_TRUE(j == 333);

				EXPECT_THROW(ss >> j, json::parse_error);
				//CHECK_THROWS_WITH(ss >> j,
								  //"[json.exception.parse_error.101] parse error at 1: syntax error - unexpected end of input; expected '[', '{', or a literal");
			}

			//TEST(regression,"literals without whitespace")
			{
				std::stringstream ss;
				ss << "truefalsenull\"\"";
				json j;
				EXPECT_NO_THROW(ss >> j);
				EXPECT_TRUE(j == true);
				EXPECT_NO_THROW(ss >> j);
				EXPECT_TRUE(j == false);
				EXPECT_NO_THROW(ss >> j);
				EXPECT_TRUE(j == nullptr);
				EXPECT_NO_THROW(ss >> j);
				EXPECT_TRUE(j == "");

				EXPECT_THROW(ss >> j, json::parse_error);
				//CHECK_THROWS_WITH(ss >> j,
								  //"[json.exception.parse_error.101] parse error at 1: syntax error - unexpected end of input; expected '[', '{', or a literal");
			}

			//TEST(regression,"example from #529")
			{
				std::stringstream ss;
				ss << "{\n    \"one\"   : 1,\n    \"two\"   : 2\n}\n{\n    \"three\" : 3\n}";
				json j;
				EXPECT_NO_THROW(ss >> j);
				EXPECT_TRUE(j == json({{"one", 1}, {"two", 2}}));
				EXPECT_NO_THROW(ss >> j);
				EXPECT_TRUE(j == json({{"three", 3}}));

				EXPECT_THROW(ss >> j, json::parse_error);
				//CHECK_THROWS_WITH(ss >> j,
								  //"[json.exception.parse_error.101] parse error at 1: syntax error - unexpected end of input; expected '[', '{', or a literal");
			}

			//TEST(regression,"second example from #529")
			{
				std::string str = "{\n\"one\"   : 1,\n\"two\"   : 2\n}\n{\n\"three\" : 3\n}";

				{
					std::ofstream file("test.json");
					file << str;
				}

				std::ifstream stream("test.json", std::ifstream::in);
				json val;

				size_t i = 0;
				while (stream.peek() != EOF)
				{
					//CAPTURE(i);
					EXPECT_NO_THROW(stream >> val);

					EXPECT_TRUE(i < 2);

					if (i == 0)
					{
						EXPECT_TRUE(val == json({{"one", 1}, {"two", 2}}));
					}

					if (i == 1)
					{
						EXPECT_TRUE(val == json({{"three", 3}}));
					}

					++i;
				}

				std::remove("test.json");
			}
		}

		//TEST(regression,"issue #389 - Integer-overflow (OSS-Fuzz issue 267)")
		{
			// original test case
			json j1 = json::parse("-9223372036854775808");
			EXPECT_TRUE(j1.is_number_integer());
			EXPECT_TRUE(j1.get<json::number_integer_t>() == INT64_MIN);

			// edge case (+1; still an integer)
			json j2 = json::parse("-9223372036854775807");
			EXPECT_TRUE(j2.is_number_integer());
			EXPECT_TRUE(j2.get<json::number_integer_t>() == INT64_MIN + 1);

			// edge case (-1; overflow -> floats)
			json j3 = json::parse("-9223372036854775809");
			EXPECT_TRUE(j3.is_number_float());
		}

		//TEST(regression,"issue #380 - bug in overflow detection when parsing integers")
		{
			json j = json::parse("166020696663385964490");
			EXPECT_TRUE(j.is_number_float());
			EXPECT_TRUE(j.get<json::number_float_t>() == 166020696663385964490.0);
		}

		//TEST(regression,"issue #405 - Heap-buffer-overflow (OSS-Fuzz issue 342)")
		{
			// original test case
			std::vector<uint8_t> vec {0x65, 0xf5, 0x0a, 0x48, 0x21};
			EXPECT_THROW(json::from_cbor(vec), json::parse_error);
			//CHECK_THROWS_WITH(json::from_cbor(vec),
							  //"[json.exception.parse_error.110] parse error at 6: unexpected end of input");
		}

		//TEST(regression,"issue #407 - Heap-buffer-overflow (OSS-Fuzz issue 343)")
		{
			// original test case: incomplete float64
			std::vector<uint8_t> vec1 {0xcb, 0x8f, 0x0a};
			EXPECT_THROW(json::from_msgpack(vec1), json::parse_error);
			//CHECK_THROWS_WITH(json::from_msgpack(vec1),
							  //"[json.exception.parse_error.110] parse error at 4: unexpected end of input");

			// related test case: incomplete float32
			std::vector<uint8_t> vec2 {0xca, 0x8f, 0x0a};
			EXPECT_THROW(json::from_msgpack(vec2), json::parse_error);
			//CHECK_THROWS_WITH(json::from_msgpack(vec2),
							  //"[json.exception.parse_error.110] parse error at 4: unexpected end of input");

			// related test case: incomplete Half-Precision Float (CBOR)
			std::vector<uint8_t> vec3 {0xf9, 0x8f};
			EXPECT_THROW(json::from_cbor(vec3), json::parse_error);
			//CHECK_THROWS_WITH(json::from_cbor(vec3),
							  //"[json.exception.parse_error.110] parse error at 3: unexpected end of input");

			// related test case: incomplete Single-Precision Float (CBOR)
			std::vector<uint8_t> vec4 {0xfa, 0x8f, 0x0a};
			EXPECT_THROW(json::from_cbor(vec4), json::parse_error);
			//CHECK_THROWS_WITH(json::from_cbor(vec4),
							  //"[json.exception.parse_error.110] parse error at 4: unexpected end of input");

			// related test case: incomplete Double-Precision Float (CBOR)
			std::vector<uint8_t> vec5 {0xfb, 0x8f, 0x0a};
			EXPECT_THROW(json::from_cbor(vec5), json::parse_error);
			//CHECK_THROWS_WITH(json::from_cbor(vec5),
							  //"[json.exception.parse_error.110] parse error at 4: unexpected end of input");
		}

		//TEST(regression,"issue #408 - Heap-buffer-overflow (OSS-Fuzz issue 344)")
		{
			// original test case
			std::vector<uint8_t> vec1 {0x87};
			EXPECT_THROW(json::from_msgpack(vec1), json::parse_error);
			//CHECK_THROWS_WITH(json::from_msgpack(vec1),
							  //"[json.exception.parse_error.110] parse error at 2: unexpected end of input");

			// more test cases for MessagePack
			for (auto b :
					{
						0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, // fixmap
						0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, // fixarray
						0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, // fixstr
						0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf
					})
			{
				std::vector<uint8_t> vec(1, static_cast<uint8_t>(b));
				EXPECT_THROW(json::from_msgpack(vec), json::parse_error);
			}

			// more test cases for CBOR
			for (auto b :
					{
						0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
						0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, // UTF-8 string
						0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
						0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, // array
						0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
						0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7 // map
					})
			{
				std::vector<uint8_t> vec(1, static_cast<uint8_t>(b));
				EXPECT_THROW(json::from_cbor(vec), json::parse_error);
			}

			// special case: empty input
			std::vector<uint8_t> vec2;
			EXPECT_THROW(json::from_cbor(vec2), json::parse_error);
			//CHECK_THROWS_WITH(json::from_cbor(vec2),
							  //"[json.exception.parse_error.110] parse error at 1: unexpected end of input");
			EXPECT_THROW(json::from_msgpack(vec2), json::parse_error);
			//CHECK_THROWS_WITH(json::from_msgpack(vec2),
							  //"[json.exception.parse_error.110] parse error at 1: unexpected end of input");
		}

		//TEST(regression,"issue #411 - Heap-buffer-overflow (OSS-Fuzz issue 366)")
		{
			// original test case: empty UTF-8 string (indefinite length)
			std::vector<uint8_t> vec1 {0x7f};
			EXPECT_THROW(json::from_cbor(vec1), json::parse_error);
			//CHECK_THROWS_WITH(json::from_cbor(vec1),
							  //"[json.exception.parse_error.110] parse error at 2: unexpected end of input");

			// related test case: empty array (indefinite length)
			std::vector<uint8_t> vec2 {0x9f};
			EXPECT_THROW(json::from_cbor(vec2), json::parse_error);
			//CHECK_THROWS_WITH(json::from_cbor(vec2),
							  //"[json.exception.parse_error.110] parse error at 2: unexpected end of input");

			// related test case: empty map (indefinite length)
			std::vector<uint8_t> vec3 {0xbf};
			EXPECT_THROW(json::from_cbor(vec3), json::parse_error);
			//CHECK_THROWS_WITH(json::from_cbor(vec3),
							  //"[json.exception.parse_error.110] parse error at 2: unexpected end of input");
		}

		//TEST(regression,"issue #412 - Heap-buffer-overflow (OSS-Fuzz issue 367)")
		{
			// original test case
			std::vector<uint8_t> vec
			{
				0xab, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98,
				0x98, 0x98, 0x98, 0x98, 0x98, 0x00, 0x00, 0x00,
				0x60, 0xab, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98,
				0x98, 0x98, 0x98, 0x98, 0x98, 0x00, 0x00, 0x00,
				0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
				0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
				0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
				0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
				0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
				0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
				0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0xa0, 0x9f,
				0x9f, 0x97, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
				0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
				0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
				0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
				0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
				0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60
			};
			EXPECT_THROW(json::from_cbor(vec), json::parse_error);
			//CHECK_THROWS_WITH(json::from_cbor(vec),
							  //"[json.exception.parse_error.113] parse error at 2: expected a CBOR string; last byte: 0x98");

			// related test case: nonempty UTF-8 string (indefinite length)
			std::vector<uint8_t> vec1 {0x7f, 0x61, 0x61};
			EXPECT_THROW(json::from_cbor(vec1), json::parse_error);
			//CHECK_THROWS_WITH(json::from_cbor(vec1),
							  //"[json.exception.parse_error.110] parse error at 4: unexpected end of input");

			// related test case: nonempty array (indefinite length)
			std::vector<uint8_t> vec2 {0x9f, 0x01};
			EXPECT_THROW(json::from_cbor(vec2), json::parse_error);
			//CHECK_THROWS_WITH(json::from_cbor(vec2),
							  //"[json.exception.parse_error.110] parse error at 3: unexpected end of input");

			// related test case: nonempty map (indefinite length)
			std::vector<uint8_t> vec3 {0xbf, 0x61, 0x61, 0x01};
			EXPECT_THROW(json::from_cbor(vec3), json::parse_error);
			//CHECK_THROWS_WITH(json::from_cbor(vec3),
							  //"[json.exception.parse_error.110] parse error at 5: unexpected end of input");
		}

		//TEST(regression,"issue #414 - compare with literal 0)")
		{
#define CHECK_TYPE(v) \
		EXPECT_TRUE((json(v) == v));\
		EXPECT_TRUE((v == json(v)));\
		EXPECT_FALSE((json(v) != v));\
		EXPECT_FALSE((v != json(v)));

			CHECK_TYPE(nullptr);
			CHECK_TYPE(0);
			CHECK_TYPE(0u);
			CHECK_TYPE(0L);
			CHECK_TYPE(0.0);
			CHECK_TYPE("");

#undef CHECK_TYPE
		}

		//TEST(regression,"issue #416 - Use-of-uninitialized-value (OSS-Fuzz issue 377)")
		{
			// original test case
			std::vector<uint8_t> vec1
			{
				0x94, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa,
				0x3a, 0x96, 0x96, 0xb4, 0xb4, 0xb4, 0xb4, 0xb4,
				0xb4, 0xb4, 0xb4, 0xb4, 0xb4, 0xb4, 0xb4, 0x71,
				0xb4, 0xb4, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0x3a,
				0x96, 0x96, 0xb4, 0xb4, 0xfa, 0x94, 0x94, 0x61,
				0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0xfa
			};
			EXPECT_THROW(json::from_cbor(vec1), json::parse_error);
			//CHECK_THROWS_WITH(json::from_cbor(vec1),
							  //"[json.exception.parse_error.113] parse error at 13: expected a CBOR string; last byte: 0xB4");

			// related test case: double-precision
			std::vector<uint8_t> vec2
			{
				0x94, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa,
				0x3a, 0x96, 0x96, 0xb4, 0xb4, 0xb4, 0xb4, 0xb4,
				0xb4, 0xb4, 0xb4, 0xb4, 0xb4, 0xb4, 0xb4, 0x71,
				0xb4, 0xb4, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0x3a,
				0x96, 0x96, 0xb4, 0xb4, 0xfa, 0x94, 0x94, 0x61,
				0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0xfb
			};
			EXPECT_THROW(json::from_cbor(vec2), json::parse_error);
			//CHECK_THROWS_WITH(json::from_cbor(vec2),
							  //"[json.exception.parse_error.113] parse error at 13: expected a CBOR string; last byte: 0xB4");
		}

		//TEST(regression,"issue #452 - Heap-buffer-overflow (OSS-Fuzz issue 585)")
		{
			std::vector<uint8_t> vec = {'-', '0', '1', '2', '2', '7', '4'};
			EXPECT_THROW(json::parse(vec), json::parse_error);
		}

		//TEST(regression,"issue #454 - doubles are printed as integers")
		{
			json j = R"({"bool_value":true,"double_value":2.0,"int_value":10,"level1":{"list_value":[3,"hi",false],"tmp":5.0},"string_value":"hello"})"_json;
			EXPECT_TRUE(j["double_value"].is_number_float());
		}

		//TEST(regression,"issue #464 - VS2017 implicit to std::string conversion fix")
		{
			json v = "test";
			std::string test;
			test = v;
			EXPECT_TRUE(v == "test");
		}

		//TEST(regression,"issue #465 - roundtrip error while parsing 1000000000000000010E5")
		{
			json j1 = json::parse("1000000000000000010E5");
			std::string s1 = j1.dump();
			json j2 = json::parse(s1);
			std::string s2 = j2.dump();
			EXPECT_TRUE(s1 == s2);
		}

		//TEST(regression,"issue #473 - inconsistent behavior in conversion to array type")
		{
			json j_array = {1, 2, 3, 4};
			json j_number = 42;
			json j_null = nullptr;

			//TEST(regression,"std::vector")
			{
				auto create = [](const json & j)
				{
					std::vector<int> v = j;
				};

				EXPECT_NO_THROW(create(j_array));
				EXPECT_THROW(create(j_number), json::type_error);
				//CHECK_THROWS_WITH(create(j_number), "[json.exception.type_error.302] type must be array, but is number");
				//EXPECT_THROW(create(j_null), json::type_error);
				//CHECK_THROWS_WITH(create(j_null), "[json.exception.type_error.302] type must be array, but is null");
			}

			//TEST(regression,"std::list")
			{
				auto create = [](const json & j)
				{
					std::list<int> v = j;
				};

				EXPECT_NO_THROW(create(j_array));
				EXPECT_THROW(create(j_number), json::type_error);
				//CHECK_THROWS_WITH(create(j_number), "[json.exception.type_error.302] type must be array, but is number");
				EXPECT_THROW(create(j_null), json::type_error);
				//CHECK_THROWS_WITH(create(j_null), "[json.exception.type_error.302] type must be array, but is null");
			}

			//TEST(regression,"std::forward_list")
			{
				auto create = [](const json & j)
				{
					std::forward_list<int> v = j;
				};

				EXPECT_NO_THROW(create(j_array));
				EXPECT_THROW(create(j_number), json::type_error);
				//CHECK_THROWS_WITH(create(j_number), "[json.exception.type_error.302] type must be array, but is number");
				EXPECT_THROW(create(j_null), json::type_error);
				//CHECK_THROWS_WITH(create(j_null), "[json.exception.type_error.302] type must be array, but is null");
			}
		}

		//TEST(regression,"issue #486 - json::value_t can't be a map's key type in VC++ 2015")
		{
			// the code below must compile with MSVC
			std::map<json::value_t, std::string> jsonTypes ;
			jsonTypes[json::value_t::array] = "array";
		}

		//TEST(regression,"issue #494 - conversion from vector<bool> to json fails to build")
		{
			std::vector<bool> boolVector = {false, true, false, false};
			json j;
			j["bool_vector"] = boolVector;

			EXPECT_TRUE(j["bool_vector"].dump() == "[false,true,false,false]");
		}

		//TEST(regression,"issue #504 - assertion error (OSS-Fuzz 856)")
		{
			std::vector<uint8_t> vec1 = {0xf9, 0xff, 0xff, 0x4a, 0x3a, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x37, 0x02, 0x38};
			json j1 = json::from_cbor(vec1, false);

			// step 2: round trip
			std::vector<uint8_t> vec2 = json::to_cbor(j1);

			// parse serialization
			json j2 = json::from_cbor(vec2);

			// NaN is dumped to "null"
			EXPECT_TRUE(j2.is_number_float());
			EXPECT_TRUE(std::isnan(j2.get<json::number_float_t>()));
			EXPECT_TRUE(j2.dump() == "null");

			// check if serializations match
			EXPECT_TRUE(json::to_cbor(j2) == vec2);
		}

		//TEST(regression,"issue #512 - use of overloaded operator '<=' is ambiguous")
		{
			json j;
			j["a"] = 5;

			// json op scalar
			EXPECT_TRUE(j["a"] == 5);
			EXPECT_TRUE(j["a"] != 4);

			EXPECT_TRUE(j["a"] <= 7);
			EXPECT_TRUE(j["a"] <  7);
			EXPECT_TRUE(j["a"] >= 3);
			EXPECT_TRUE(j["a"] >  3);


			EXPECT_TRUE(not(j["a"] <= 4));
			EXPECT_TRUE(not(j["a"] <  4));
			EXPECT_TRUE(not(j["a"] >= 6));
			EXPECT_TRUE(not(j["a"] >  6));

			// scalar op json
			EXPECT_TRUE(5 == j["a"]);
			EXPECT_TRUE(4 != j["a"]);

			EXPECT_TRUE(7 >= j["a"]);
			EXPECT_TRUE(7 >  j["a"]);
			EXPECT_TRUE(3 <= j["a"]);
			EXPECT_TRUE(3 <  j["a"]);

			EXPECT_TRUE(not(4 >= j["a"]));
			EXPECT_TRUE(not(4 >  j["a"]));
			EXPECT_TRUE(not(6 <= j["a"]));
			EXPECT_TRUE(not(6 <  j["a"]));
		}

		//TEST(regression,"issue #575 - heap-buffer-overflow (OSS-Fuzz 1400)")
		{
			std::vector<uint8_t> vec = {'"', '\\', '"', 'X', '"', '"'};
			EXPECT_THROW(json::parse(vec), json::parse_error);
		}

		//TEST(regression,"issue #600 - how does one convert a map in Json back to std::map?")
		{
			//TEST(regression,"example 1")
			{
				// create a map
				std::map<std::string, int> m1 {{"key", 1}};

				// create and print a JSON from the map
				json j = m1;

				// get the map out of JSON
				std::map<std::string, int> m2 = j;

				// make sure the roundtrip succeeds
				EXPECT_TRUE(m1 == m2);
			}

			//TEST(regression,"example 2")
			{
				// create a map
				std::map<std::string, std::string> m1 {{"key", "val"}};

				// create and print a JSON from the map
				json j = m1;

				// get the map out of JSON
				std::map<std::string, std::string> m2 = j;

				// make sure the roundtrip succeeds
				EXPECT_TRUE(m1 == m2);
			}
		}

		//TEST(regression,"issue #602 - BOM not skipped when using json:parse(iterator)")
		{
			std::string i = "\xef\xbb\xbf{\n   \"foo\": true\n}";
			EXPECT_NO_THROW(json::parse(i.begin(), i.end()));
		}

		//TEST(regression,"issue #702 - conversion from valarray<double> to json fails to build")
		{
			//TEST(regression,"original example")
			{
				std::valarray<double> v;
				nlohmann::json j;
				j["test"] = v;
			}

			//TEST(regression,"full example")
			{
				std::valarray<double> v = {1.2, 2.3, 3.4, 4.5};
				json j = v;
				std::valarray<double> vj = j;

				EXPECT_TRUE(j == json(vj));
				EXPECT_TRUE(v.size() == vj.size());
				for (size_t i = 0; i < v.size(); ++i)
				{
					EXPECT_TRUE(v[i] == vj[i]);
					EXPECT_TRUE(v[i] == j[i]);
				}

				EXPECT_THROW(json().get<std::valarray<double>>(), json::type_error);
				//CHECK_THROWS_WITH(json().get<std::valarray<double>>(),
								  //"[json.exception.type_error.302] type must be array, but is null");
			}
		}

		//TEST(regression,"issue #367 - Behavior of operator>> should more closely resemble that of built-in overloads.")
		{
			//TEST(regression,"example 1")
			{
				std::istringstream i1_2_3( "{\"first\": \"one\" }{\"second\": \"two\"}3" );
				json j1, j2, j3;
				i1_2_3 >> j1;
				i1_2_3 >> j2;
				i1_2_3 >> j3;

				std::map<std::string, std::string> m1 = j1;
				std::map<std::string, std::string> m2 = j2;
				int i3 = j3;

				EXPECT_TRUE( m1 == ( std::map<std::string, std::string> {{ "first",  "one" }} ));
				EXPECT_TRUE( m2 == ( std::map<std::string, std::string> {{ "second", "two" }} ));
				EXPECT_TRUE( i3 == 3 );
			}
		}

		//TEST(regression,"issue #714 - throw std::ios_base::failure exception when failbit set to true")
		{
			{
				std::ifstream is;
				is.exceptions(
					is.exceptions()
					| std::ios_base::failbit
					| std::ios_base::badbit
				); // handle different exceptions as 'file not found', 'permission denied'

				is.open("test/data/regression/working_file.json");
				EXPECT_NO_THROW(nlohmann::json::parse(is));
			}

			{
				std::ifstream is;
				is.exceptions(
					is.exceptions()
					| std::ios_base::failbit
					| std::ios_base::badbit
				); // handle different exceptions as 'file not found', 'permission denied'

				is.open("test/data/json_nlohmann_tests/all_unicode.json.cbor",
						std::ios_base::in | std::ios_base::binary);
				EXPECT_NO_THROW(nlohmann::json::from_cbor(is));
			}
		}

		//TEST(regression,"issue #805 - copy constructor is used with std::initializer_list constructor.")
		{
			nocopy n;
			json j;
			j = {{"nocopy", n}};
			EXPECT_TRUE(j["nocopy"]["val"] == 0);
		}

		//TEST(regression,"issue #838 - incorrect parse error with binary data in keys")
		{
			uint8_t key1[] = { 103, 92, 117, 48, 48, 48, 55, 92, 114, 215, 126, 214, 95, 92, 34, 174, 40, 71, 38, 174, 40, 71, 38, 223, 134, 247, 127 };
			std::string key1_str(key1, key1 + sizeof(key1) / sizeof(key1[0]));
			json j = key1_str;
			EXPECT_THROW(j.dump(), json::type_error);
			//CHECK_THROWS_WITH(j.dump(), "[json.exception.type_error.316] invalid UTF-8 byte at index 10: 0x7E");
		}

		//TEST(regression,"issue #843 - converting to array not working")
		{
			json j;
			std::array<int, 4> ar = {{1, 1, 1, 1}};
			j = ar;
			ar = j;
		}

		//TEST(regression,"issue #894 - invalid RFC6902 copy operation succeeds")
		{
			auto model = R"({
				"one": {
					"two": {
						"three": "hello",
						"four": 42
					}
				}
			})"_json;

			EXPECT_THROW(model.patch(R"([{"op": "move",
							 "from": "/one/two/three",
							 "path": "/a/b/c"}])"_json), json::out_of_range);
			//CHECK_THROWS_WITH(model.patch(R"([{"op": "move",
							 //"from": "/one/two/three",
							 //"path": "/a/b/c"}])"_json),
							  //"[json.exception.out_of_range.403] key 'a' not found");

			EXPECT_THROW(model.patch(R"([{"op": "copy",
									 "from": "/one/two/three",
									 "path": "/a/b/c"}])"_json), json::out_of_range);
			//CHECK_THROWS_WITH(model.patch(R"([{"op": "copy",
									 //"from": "/one/two/three",
									 //"path": "/a/b/c"}])"_json),
							  //"[json.exception.out_of_range.403] key 'a' not found");
		}

		//TEST(regression,"issue #961 - incorrect parsing of indefinite length CBOR strings")
		{
			std::vector<uint8_t> v_cbor =
			{
				0x7F,
				0x64,
				'a', 'b', 'c', 'd',
				0x63,
				'1', '2', '3',
				0xFF
			};
			json j = json::from_cbor(v_cbor);
			EXPECT_TRUE(j == "abcd123");
		}

		//TEST(regression,"issue #962 - Timeout (OSS-Fuzz 6034)")
		{
			std::vector<uint8_t> v_ubjson = {'[', '$', 'Z', '#', 'L', 0x78, 0x28, 0x00, 0x68, 0x28, 0x69, 0x69, 0x17};
			EXPECT_THROW(json::from_ubjson(v_ubjson), json::out_of_range);
			//CHECK_THROWS_WITH(json::from_ubjson(v_ubjson),
			//                  "[json.exception.out_of_range.408] excessive array size: 8658170730974374167");

			v_ubjson[0] = '{';
			EXPECT_THROW(json::from_ubjson(v_ubjson), json::out_of_range);
			//CHECK_THROWS_WITH(json::from_ubjson(v_ubjson),
			//                  "[json.exception.out_of_range.408] excessive object size: 8658170730974374167");
		}

		//TEST(regression,"issue #972 - Segmentation fault on G++ when trying to assign json string literal to custom json type")
		{
			my_json foo = R"([1, 2, 3])"_json;
		}

		//TEST(regression,"issue #977 - Assigning between different json types")
		{
			foo_json lj = ns::foo{3};
			ns::foo ff = lj;
			EXPECT_TRUE(lj.is_object());
			EXPECT_TRUE(lj.size() == 1);
			EXPECT_TRUE(lj["x"] == 3);
			EXPECT_TRUE(ff.x == 3);
			nlohmann::json nj = lj;                // This line works as expected
		}

		//TEST(regression,"issue #1001 - Fix memory leak during parser callback")
		{
			auto geojsonExample = R"(
			  { "type": "FeatureCollection",
				"features": [
				  { "type": "Feature",
					"geometry": {"type": "Point", "coordinates": [102.0, 0.5]},
					"properties": {"prop0": "value0"}
					},
				  { "type": "Feature",
					"geometry": {
					  "type": "LineString",
					  "coordinates": [
						[102.0, 0.0], [103.0, 1.0], [104.0, 0.0], [105.0, 1.0]
						]
					  },
					"properties": {
					  "prop0": "value0",
					  "prop1": 0.0
					  }
					},
				  { "type": "Feature",
					 "geometry": {
					   "type": "Polygon",
					   "coordinates": [
						 [ [100.0, 0.0], [101.0, 0.0], [101.0, 1.0],
						   [100.0, 1.0], [100.0, 0.0] ]
						 ]
					 },
					 "properties": {
					   "prop0": "value0",
					   "prop1": {"this": "that"}
					   }
					 }
				   ]
				 })";

			json::parser_callback_t cb = [&](int, json::parse_event_t event, json & parsed)
			{
				// skip uninteresting events
				if (event == json::parse_event_t::value and !parsed.is_primitive())
				{
					return false;
				}

				switch (event)
				{
					case json::parse_event_t::key:
					{
						return true;
					}
					case json::parse_event_t::value:
					{
						return false;
					}
					case json::parse_event_t::object_start:
					{
						return true;
					}
					case json::parse_event_t::object_end:
					{
						return false;
					}
					case json::parse_event_t::array_start:
					{
						return true;
					}
					case json::parse_event_t::array_end:
					{
						return false;
					}

					default:
					{
						return true;
					}
				}
			};

			auto j = json::parse(geojsonExample, cb, true);
			EXPECT_TRUE(j == json());
		}

		//TEST(regression,"issue #1021 - to/from_msgpack only works with standard typization")
		{
			float_json j = 1000.0;
			EXPECT_TRUE(float_json::from_cbor(float_json::to_cbor(j)) == j);
			EXPECT_TRUE(float_json::from_msgpack(float_json::to_msgpack(j)) == j);
			EXPECT_TRUE(float_json::from_ubjson(float_json::to_ubjson(j)) == j);

			float_json j2 = {1000.0, 2000.0, 3000.0};
			EXPECT_TRUE(float_json::from_ubjson(float_json::to_ubjson(j2, true, true)) == j2);
		}
	}
}
