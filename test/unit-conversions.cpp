#include "gtest/gtest.h"
#define private public
#include "json.hpp"

using nlohmann::json;

#include <deque>
#include <forward_list>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <valarray>

namespace
{
	TEST(conversion, conversion)
	{
		//TEST(constructors,"get an object (explicit)")
		{
			json::object_t o_reference = {{"object", json::object()}, {"array", {1, 2, 3, 4}}, {"number", 42}, {"boolean", false}, {"null", nullptr}, {"string", "Hello world"} };
			json j(o_reference);

			//TEST(constructors,"json::object_t")
			{
				json::object_t o = j.get<json::object_t>();
				EXPECT_TRUE(json(o) == j);
			}

			//TEST(constructors,"std::map<json::string_t, json>")
			{
				std::map<json::string_t, json> o = j.get<std::map<json::string_t, json>>();
				EXPECT_TRUE(json(o) == j);
			}

			//TEST(constructors,"std::multimap<json::string_t, json>")
			{
				std::multimap<json::string_t, json> o = j.get<std::multimap<json::string_t, json>>();
				EXPECT_TRUE(json(o) == j);
			}

			//TEST(constructors,"std::unordered_map<json::string_t, json>")
			{
				std::unordered_map<json::string_t, json> o = j.get<std::unordered_map<json::string_t, json>>();
				EXPECT_TRUE(json(o) == j);
			}

			//TEST(constructors,"std::unordered_multimap<json::string_t, json>")
			{
				std::unordered_multimap<json::string_t, json> o =
					j.get<std::unordered_multimap<json::string_t, json>>();
				EXPECT_TRUE(json(o) == j);
			}

			//TEST(constructors,"exception in case of a non-object type")
			{
				EXPECT_THROW(json(json::value_t::null).get<json::object_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::array).get<json::object_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::string).get<json::object_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::boolean).get<json::object_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::number_integer).get<json::object_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::number_unsigned).get<json::object_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::number_float).get<json::object_t>(), json::type_error);

				//CHECK_THROWS_WITH(json(json::value_t::null).get<json::object_t>(),
								  //"[json.exception.type_error.302] type must be object, but is null");
				//CHECK_THROWS_WITH(json(json::value_t::array).get<json::object_t>(),
								  //"[json.exception.type_error.302] type must be object, but is array");
				//CHECK_THROWS_WITH(json(json::value_t::string).get<json::object_t>(),
								  //"[json.exception.type_error.302] type must be object, but is string");
				//CHECK_THROWS_WITH(json(json::value_t::boolean).get<json::object_t>(),
								  //"[json.exception.type_error.302] type must be object, but is boolean");
				//CHECK_THROWS_WITH(json(json::value_t::number_integer).get<json::object_t>(),
								  //"[json.exception.type_error.302] type must be object, but is number");
				//CHECK_THROWS_WITH(json(json::value_t::number_unsigned).get<json::object_t>(),
								  //"[json.exception.type_error.302] type must be object, but is number");
				//CHECK_THROWS_WITH(json(json::value_t::number_float).get<json::object_t>(),
								  //"[json.exception.type_error.302] type must be object, but is number");
			}
		}

		//TEST(constructors,"get an object (implicit)")
		{
			json::object_t o_reference = {{"object", json::object()}, {"array", {1, 2, 3, 4}}, {"number", 42}, {"boolean", false}, {"null", nullptr}, {"string", "Hello world"} };
			json j(o_reference);

			//TEST(constructors,"json::object_t")
			{
				json::object_t o = j;
				EXPECT_TRUE(json(o) == j);
			}

			//TEST(constructors,"std::map<json::string_t, json>")
			{
				std::map<json::string_t, json> o = j;
				EXPECT_TRUE(json(o) == j);
			}

			//TEST(constructors,"std::multimap<json::string_t, json>")
			{
				std::multimap<json::string_t, json> o = j;
				EXPECT_TRUE(json(o) == j);
			}

			//TEST(constructors,"std::unordered_map<json::string_t, json>")
			{
				std::unordered_map<json::string_t, json> o = j;
				EXPECT_TRUE(json(o) == j);
			}

			//TEST(constructors,"std::unordered_multimap<json::string_t, json>")
			{
				std::unordered_multimap<json::string_t, json> o = j;
				EXPECT_TRUE(json(o) == j);
			}
		}

		//TEST(constructors,"get an array (explicit)")
		{
			json::array_t a_reference {json(1), json(1u), json(2.2), json(false), json("string"), json()};
			json j(a_reference);

			//TEST(constructors,"json::array_t")
			{
				json::array_t a = j.get<json::array_t>();
				EXPECT_TRUE(json(a) == j);
			}

			//TEST(constructors,"std::list<json>")
			{
				std::list<json> a = j.get<std::list<json>>();
				EXPECT_TRUE(json(a) == j);
			}

			//TEST(constructors,"std::forward_list<json>")
			{
				std::forward_list<json> a = j.get<std::forward_list<json>>();
				EXPECT_TRUE(json(a) == j);

				EXPECT_THROW(json(json::value_t::null).get<std::forward_list<json>>(), json::type_error);
				//CHECK_THROWS_WITH(json(json::value_t::null).get<std::forward_list<json>>(),
								  //"[json.exception.type_error.302] type must be array, but is null");
			}

			//TEST(constructors,"std::vector<json>")
			{
				std::vector<json> a = j.get<std::vector<json>>();
				EXPECT_TRUE(json(a) == j);

				EXPECT_THROW(json(json::value_t::null).get<std::vector<json>>(), json::type_error);
				//CHECK_THROWS_WITH(json(json::value_t::null).get<std::vector<json>>(),
								  //"[json.exception.type_error.302] type must be array, but is null");

#if not defined(JSON_NOEXCEPTION)
				//TEST(constructors,"reserve is called on containers that supports it")
				{
					// making the call to from_json throw in order to check capacity
					std::vector<float> v;
					EXPECT_THROW(nlohmann::from_json(j, v), json::type_error);
					EXPECT_TRUE(v.capacity() == j.size());

					// make sure all values are properly copied
					std::vector<int> v2 = json({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
					EXPECT_TRUE(v2.size() == 10);
				}
#endif
			}

			//TEST(constructors,"built-in arrays")
			{
				const char str[] = "a string";
				const int nbs[] = {0, 1, 2};

				json j2 = nbs;
				json j3 = str;

				auto v = j2.get<std::vector<int>>();
				auto s = j3.get<std::string>();
				EXPECT_TRUE(std::equal(v.begin(), v.end(), std::begin(nbs)));
				EXPECT_TRUE(s == str);
			}

			//TEST(constructors,"std::deque<json>")
			{
				std::deque<json> a = j.get<std::deque<json>>();
				EXPECT_TRUE(json(a) == j);
			}

			//TEST(constructors,"exception in case of a non-array type")
			{
				EXPECT_THROW(json(json::value_t::null).get<json::array_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::object).get<json::array_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::string).get<json::array_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::boolean).get<json::array_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::number_integer).get<json::array_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::number_unsigned).get<json::array_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::number_float).get<json::array_t>(), json::type_error);

				//CHECK_THROWS_WITH(json(json::value_t::object).get<std::vector<int>>(),
								  //"[json.exception.type_error.302] type must be array, but is object");
				//CHECK_THROWS_WITH(json(json::value_t::null).get<json::array_t>(),
								  //"[json.exception.type_error.302] type must be array, but is null");
				//CHECK_THROWS_WITH(json(json::value_t::object).get<json::array_t>(),
								  //"[json.exception.type_error.302] type must be array, but is object");
				//CHECK_THROWS_WITH(json(json::value_t::string).get<json::array_t>(),
								  //"[json.exception.type_error.302] type must be array, but is string");
				//CHECK_THROWS_WITH(json(json::value_t::boolean).get<json::array_t>(),
								  //"[json.exception.type_error.302] type must be array, but is boolean");
				//CHECK_THROWS_WITH(json(json::value_t::number_integer).get<json::array_t>(),
								  //"[json.exception.type_error.302] type must be array, but is number");
				//CHECK_THROWS_WITH(json(json::value_t::number_unsigned).get<json::array_t>(),
								  //"[json.exception.type_error.302] type must be array, but is number");
				//CHECK_THROWS_WITH(json(json::value_t::number_float).get<json::array_t>(),
								  //"[json.exception.type_error.302] type must be array, but is number");
			}
		}

		//TEST(constructors,"get an array (implicit)")
		{
			json::array_t a_reference {json(1), json(1u), json(2.2), json(false), json("string"), json()};
			json j(a_reference);

			//TEST(constructors,"json::array_t")
			{
				json::array_t a = j;
				EXPECT_TRUE(json(a) == j);
			}

			//TEST(constructors,"std::list<json>")
			{
				std::list<json> a = j;
				EXPECT_TRUE(json(a) == j);
			}

			//TEST(constructors,"std::forward_list<json>")
			{
				std::forward_list<json> a = j;
				EXPECT_TRUE(json(a) == j);
			}

			//TEST(constructors,"std::vector<json>")
			{
				std::vector<json> a = j;
				EXPECT_TRUE(json(a) == j);
			}

			//TEST(constructors,"std::deque<json>")
			{
				std::deque<json> a = j;
				EXPECT_TRUE(json(a) == j);
			}
		}

		//TEST(constructors,"get a string (explicit)")
		{
			json::string_t s_reference {"Hello world"};
			json j(s_reference);

			//TEST(constructors,"string_t")
			{
				json::string_t s = j.get<json::string_t>();
				EXPECT_TRUE(json(s) == j);
			}

			//TEST(constructors,"std::string")
			{
				std::string s = j.get<std::string>();
				EXPECT_TRUE(json(s) == j);
			}

			//TEST(constructors,"exception in case of a non-string type")
			{
				EXPECT_THROW(json(json::value_t::null).get<json::string_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::object).get<json::string_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::array).get<json::string_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::boolean).get<json::string_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::number_integer).get<json::string_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::number_unsigned).get<json::string_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::number_float).get<json::string_t>(), json::type_error);

				//CHECK_THROWS_WITH(json(json::value_t::null).get<json::string_t>(),
								  //"[json.exception.type_error.302] type must be string, but is null");
				//CHECK_THROWS_WITH(json(json::value_t::object).get<json::string_t>(),
								  //"[json.exception.type_error.302] type must be string, but is object");
				//CHECK_THROWS_WITH(json(json::value_t::array).get<json::string_t>(),
								  //"[json.exception.type_error.302] type must be string, but is array");
				//CHECK_THROWS_WITH(json(json::value_t::boolean).get<json::string_t>(),
								  //"[json.exception.type_error.302] type must be string, but is boolean");
				//CHECK_THROWS_WITH(json(json::value_t::number_integer).get<json::string_t>(),
								  //"[json.exception.type_error.302] type must be string, but is number");
				//CHECK_THROWS_WITH(json(json::value_t::number_unsigned).get<json::string_t>(),
								  //"[json.exception.type_error.302] type must be string, but is number");
				//CHECK_THROWS_WITH(json(json::value_t::number_float).get<json::string_t>(),
								  //"[json.exception.type_error.302] type must be string, but is number");
			}
		}

		//TEST(constructors,"get a string (implicit)")
		{
			json::string_t s_reference {"Hello world"};
			json j(s_reference);

			//TEST(constructors,"string_t")
			{
				json::string_t s = j;
				EXPECT_TRUE(json(s) == j);
			}

			//TEST(constructors,"std::string")
			{
				std::string s = j;
				EXPECT_TRUE(json(s) == j);
			}
		}

		//TEST(constructors,"get a boolean (explicit)")
		{
			json::boolean_t b_reference {true};
			json j(b_reference);

			//TEST(constructors,"boolean_t")
			{
				json::boolean_t b = j.get<json::boolean_t>();
				EXPECT_TRUE(json(b) == j);
			}

			//TEST(constructors,"bool")
			{
				bool b = j.get<bool>();
				EXPECT_TRUE(json(b) == j);
			}

			//TEST(constructors,"exception in case of a non-string type")
			{
				EXPECT_THROW(json(json::value_t::null).get<json::boolean_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::object).get<json::boolean_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::array).get<json::boolean_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::string).get<json::boolean_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::number_integer).get<json::boolean_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::number_unsigned).get<json::boolean_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::number_float).get<json::boolean_t>(), json::type_error);

				//CHECK_THROWS_WITH(json(json::value_t::null).get<json::boolean_t>(),
								  //"[json.exception.type_error.302] type must be boolean, but is null");
				//CHECK_THROWS_WITH(json(json::value_t::object).get<json::boolean_t>(),
								  //"[json.exception.type_error.302] type must be boolean, but is object");
				//CHECK_THROWS_WITH(json(json::value_t::array).get<json::boolean_t>(),
								  //"[json.exception.type_error.302] type must be boolean, but is array");
				//CHECK_THROWS_WITH(json(json::value_t::string).get<json::boolean_t>(),
								  //"[json.exception.type_error.302] type must be boolean, but is string");
				//CHECK_THROWS_WITH(json(json::value_t::number_integer).get<json::boolean_t>(),
								  //"[json.exception.type_error.302] type must be boolean, but is number");
				//CHECK_THROWS_WITH(json(json::value_t::number_unsigned).get<json::boolean_t>(),
								  //"[json.exception.type_error.302] type must be boolean, but is number");
				//CHECK_THROWS_WITH(json(json::value_t::number_float).get<json::boolean_t>(),
								  //"[json.exception.type_error.302] type must be boolean, but is number");
			}
		}

		//TEST(constructors,"get a boolean (implicit)")
		{
			json::boolean_t b_reference {true};
			json j(b_reference);

			//TEST(constructors,"boolean_t")
			{
				json::boolean_t b = j;
				EXPECT_TRUE(json(b) == j);
			}

			//TEST(constructors,"bool")
			{
				bool b = j;
				EXPECT_TRUE(json(b) == j);
			}
		}

		//TEST(constructors,"get an integer number (explicit)")
		{
			json::number_integer_t n_reference {42};
			json j(n_reference);
			json::number_unsigned_t n_unsigned_reference {42u};
			json j_unsigned(n_unsigned_reference);

			//TEST(constructors,"number_integer_t")
			{
				json::number_integer_t n = j.get<json::number_integer_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"number_unsigned_t")
			{
				json::number_unsigned_t n = j_unsigned.get<json::number_unsigned_t>();
				EXPECT_TRUE(json(n) == j_unsigned);
			}

			//TEST(constructors,"short")
			{
				short n = j.get<short>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"unsigned short")
			{
				unsigned short n = j.get<unsigned short>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int")
			{
				int n = j.get<int>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"unsigned int")
			{
				unsigned int n = j.get<unsigned int>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"long")
			{
				long n = j.get<long>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"unsigned long")
			{
				unsigned long n = j.get<unsigned long>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"long long")
			{
				long long n = j.get<long long>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"unsigned long long")
			{
				unsigned long long n = j.get<unsigned long long>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int8_t")
			{
				int8_t n = j.get<int8_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int16_t")
			{
				int16_t n = j.get<int16_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int32_t")
			{
				int32_t n = j.get<int32_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int64_t")
			{
				int64_t n = j.get<int64_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int8_fast_t")
			{
				int_fast8_t n = j.get<int_fast8_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int16_fast_t")
			{
				int_fast16_t n = j.get<int_fast16_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int32_fast_t")
			{
				int_fast32_t n = j.get<int_fast32_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int64_fast_t")
			{
				int_fast64_t n = j.get<int_fast64_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int8_least_t")
			{
				int_least8_t n = j.get<int_least8_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int16_least_t")
			{
				int_least16_t n = j.get<int_least16_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int32_least_t")
			{
				int_least32_t n = j.get<int_least32_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int64_least_t")
			{
				int_least64_t n = j.get<int_least64_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"uint8_t")
			{
				uint8_t n = j.get<uint8_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"uint16_t")
			{
				uint16_t n = j.get<uint16_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"uint32_t")
			{
				uint32_t n = j.get<uint32_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"uint64_t")
			{
				uint64_t n = j.get<uint64_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"uint8_fast_t")
			{
				uint_fast8_t n = j.get<uint_fast8_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"uint16_fast_t")
			{
				uint_fast16_t n = j.get<uint_fast16_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"uint32_fast_t")
			{
				uint_fast32_t n = j.get<uint_fast32_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"uint64_fast_t")
			{
				uint_fast64_t n = j.get<uint_fast64_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"uint8_least_t")
			{
				uint_least8_t n = j.get<uint_least8_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"uint16_least_t")
			{
				uint_least16_t n = j.get<uint_least16_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"uint32_least_t")
			{
				uint_least32_t n = j.get<uint_least32_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"uint64_least_t")
			{
				uint_least64_t n = j.get<uint_least64_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"exception in case of a non-number type")
			{
				EXPECT_THROW(json(json::value_t::null).get<json::number_integer_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::object).get<json::number_integer_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::array).get<json::number_integer_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::string).get<json::number_integer_t>(), json::type_error);
				EXPECT_THROW(json(json::value_t::boolean).get<json::number_integer_t>(), json::type_error);

				//CHECK_THROWS_WITH(json(json::value_t::null).get<json::number_integer_t>(),
								  //"[json.exception.type_error.302] type must be number, but is null");
				//CHECK_THROWS_WITH(json(json::value_t::object).get<json::number_integer_t>(),
								  //"[json.exception.type_error.302] type must be number, but is object");
				//CHECK_THROWS_WITH(json(json::value_t::array).get<json::number_integer_t>(),
								  //"[json.exception.type_error.302] type must be number, but is array");
				//CHECK_THROWS_WITH(json(json::value_t::string).get<json::number_integer_t>(),
								  //"[json.exception.type_error.302] type must be number, but is string");
				//CHECK_THROWS_WITH(json(json::value_t::boolean).get<json::number_integer_t>(),
								  //"[json.exception.type_error.302] type must be number, but is boolean");

				EXPECT_NO_THROW(json(json::value_t::number_float).get<json::number_integer_t>());
				EXPECT_NO_THROW(json(json::value_t::number_float).get<json::number_unsigned_t>());
			}
		}

		//TEST(constructors,"get an integer number (implicit)")
		{
			json::number_integer_t n_reference {42};
			json j(n_reference);
			json::number_unsigned_t n_unsigned_reference {42u};
			json j_unsigned(n_unsigned_reference);

			//TEST(constructors,"number_integer_t")
			{
				json::number_integer_t n = j.get<json::number_integer_t>();
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"number_unsigned_t")
			{
				json::number_unsigned_t n = j_unsigned.get<json::number_unsigned_t>();
				EXPECT_TRUE(json(n) == j_unsigned);
			}

			//TEST(constructors,"short")
			{
				short n = j;
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"unsigned short")
			{
				unsigned short n = j_unsigned;
				EXPECT_TRUE(json(n) == j_unsigned);
			}

			//TEST(constructors,"int")
			{
				int n = j;
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"unsigned int")
			{
				unsigned int n = j_unsigned;
				EXPECT_TRUE(json(n) == j_unsigned);
			}

			//TEST(constructors,"long")
			{
				long n = j;
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"unsigned long")
			{
				unsigned long n = j_unsigned;
				EXPECT_TRUE(json(n) == j_unsigned);
			}

			//TEST(constructors,"long long")
			{
				long long n = j;
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"unsigned long long")
			{
				unsigned long long n = j_unsigned;
				EXPECT_TRUE(json(n) == j_unsigned);
			}

			//TEST(constructors,"int8_t")
			{
				int8_t n = j;
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int16_t")
			{
				int16_t n = j;
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int32_t")
			{
				int32_t n = j;
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int64_t")
			{
				int64_t n = j;
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int8_fast_t")
			{
				int_fast8_t n = j;
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int16_fast_t")
			{
				int_fast16_t n = j;
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int32_fast_t")
			{
				int_fast32_t n = j;
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int64_fast_t")
			{
				int_fast64_t n = j;
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int8_least_t")
			{
				int_least8_t n = j;
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int16_least_t")
			{
				int_least16_t n = j;
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int32_least_t")
			{
				int_least32_t n = j;
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"int64_least_t")
			{
				int_least64_t n = j;
				EXPECT_TRUE(json(n) == j);
			}

			//TEST(constructors,"uint8_t")
			{
				uint8_t n = j_unsigned;
				EXPECT_TRUE(json(n) == j_unsigned);
			}

			//TEST(constructors,"uint16_t")
			{
				uint16_t n = j_unsigned;
				EXPECT_TRUE(json(n) == j_unsigned);
			}

			//TEST(constructors,"uint32_t")
			{
				uint32_t n = j_unsigned;
				EXPECT_TRUE(json(n) == j_unsigned);
			}

			//TEST(constructors,"uint64_t")
			{
				uint64_t n = j_unsigned;
				EXPECT_TRUE(json(n) == j_unsigned);
			}

			//TEST(constructors,"uint8_fast_t")
			{
				uint_fast8_t n = j_unsigned;
				EXPECT_TRUE(json(n) == j_unsigned);
			}

			//TEST(constructors,"uint16_fast_t")
			{
				uint_fast16_t n = j_unsigned;
				EXPECT_TRUE(json(n) == j_unsigned);
			}

			//TEST(constructors,"uint32_fast_t")
			{
				uint_fast32_t n = j_unsigned;
				EXPECT_TRUE(json(n) == j_unsigned);
			}

			//TEST(constructors,"uint64_fast_t")
			{
				uint_fast64_t n = j_unsigned;
				EXPECT_TRUE(json(n) == j_unsigned);
			}

			//TEST(constructors,"uint8_least_t")
			{
				uint_least8_t n = j_unsigned;
				EXPECT_TRUE(json(n) == j_unsigned);
			}

			//TEST(constructors,"uint16_least_t")
			{
				uint_least16_t n = j_unsigned;
				EXPECT_TRUE(json(n) == j_unsigned);
			}

			//TEST(constructors,"uint32_least_t")
			{
				uint_least32_t n = j_unsigned;
				EXPECT_TRUE(json(n) == j_unsigned);
			}

			//TEST(constructors,"uint64_least_t")
			{
				uint_least64_t n = j_unsigned;
				EXPECT_TRUE(json(n) == j_unsigned);
			}
		}

		//TEST(constructors,"get a floating-point number (explicit)")
		{
			json::number_float_t n_reference {42.23};
			json j(n_reference);

			//TEST(constructors,"number_float_t")
			{
				json::number_float_t n = j.get<json::number_float_t>();
				EXPECT_FLOAT_EQ(json(n).m_value.number_float, j.m_value.number_float);
			}

			//TEST(constructors,"float")
			{
				float n = j.get<float>();
				EXPECT_FLOAT_EQ(json(n).m_value.number_float, j.m_value.number_float);
			}

			//TEST(constructors,"double")
			{
				double n = j.get<double>();
				EXPECT_FLOAT_EQ(json(n).m_value.number_float, j.m_value.number_float);
			}

			//TEST(constructors,"exception in case of a non-string type")
			{
				//CHECK_THROWS_AS(json(json::value_t::null).get<json::number_float_t>(), json::type_error&);
				//CHECK_THROWS_AS(json(json::value_t::object).get<json::number_float_t>(), json::type_error&);
				//CHECK_THROWS_AS(json(json::value_t::array).get<json::number_float_t>(), json::type_error&);
				//CHECK_THROWS_AS(json(json::value_t::string).get<json::number_float_t>(), json::type_error&);
				//CHECK_THROWS_AS(json(json::value_t::boolean).get<json::number_float_t>(), json::type_error&);

				//CHECK_THROWS_WITH(json(json::value_t::null).get<json::number_float_t>(),
								  //"[json.exception.type_error.302] type must be number, but is null");
				//CHECK_THROWS_WITH(json(json::value_t::object).get<json::number_float_t>(),
								  //"[json.exception.type_error.302] type must be number, but is object");
				//CHECK_THROWS_WITH(json(json::value_t::array).get<json::number_float_t>(),
								  //"[json.exception.type_error.302] type must be number, but is array");
				//CHECK_THROWS_WITH(json(json::value_t::string).get<json::number_float_t>(),
								  //"[json.exception.type_error.302] type must be number, but is string");
				//CHECK_THROWS_WITH(json(json::value_t::boolean).get<json::number_float_t>(),
								  //"[json.exception.type_error.302] type must be number, but is boolean");

				EXPECT_NO_THROW(json(json::value_t::number_integer).get<json::number_float_t>());
				EXPECT_NO_THROW(json(json::value_t::number_unsigned).get<json::number_float_t>());
			}
		}

		//TEST(constructors,"get a floating-point number (implicit)")
		{
			json::number_float_t n_reference {42.23};
			json j(n_reference);

			//TEST(constructors,"number_float_t")
			{
				json::number_float_t n = j;
				EXPECT_FLOAT_EQ(json(n).m_value.number_float, j.m_value.number_float);
			}

			//TEST(constructors,"float")
			{
				float n = j;
				EXPECT_FLOAT_EQ(json(n).m_value.number_float, j.m_value.number_float);
			}

			//TEST(constructors,"double")
			{
				double n = j;
				EXPECT_FLOAT_EQ(json(n).m_value.number_float, j.m_value.number_float);
			}
		}

		//TEST(constructors,"get an enum")
		{
			enum c_enum { value_1, value_2 };
			enum class cpp_enum { value_1, value_2 };

			EXPECT_TRUE(json(value_1).get<c_enum>() == value_1);
			EXPECT_TRUE(json(cpp_enum::value_1).get<cpp_enum>() == cpp_enum::value_1);
		}

		//TEST(constructors,"more involved conversions")
		{
			//TEST(constructors,"object-like STL containers")
			{
				json j1 = {{"one", 1}, {"two", 2}, {"three", 3}};
				json j2 = {{"one", 1u}, {"two", 2u}, {"three", 3u}};
				json j3 = {{"one", 1.1}, {"two", 2.2}, {"three", 3.3}};
				json j4 = {{"one", true}, {"two", false}, {"three", true}};
				json j5 = {{"one", "eins"}, {"two", "zwei"}, {"three", "drei"}};

				//TEST(constructors,"std::map")
				{
					j1.get<std::map<std::string, int>>();
					j2.get<std::map<std::string, unsigned int>>();
					j3.get<std::map<std::string, double>>();
					j4.get<std::map<std::string, bool>>();
					j5.get<std::map<std::string, std::string>>();
				}

				//TEST(constructors,"std::unordered_map")
				{
					j1.get<std::unordered_map<std::string, int>>();
					j2.get<std::unordered_map<std::string, unsigned int>>();
					j3.get<std::unordered_map<std::string, double>>();
					j4.get<std::unordered_map<std::string, bool>>();
					j5.get<std::unordered_map<std::string, std::string>>();
					//EXPECT_TRUE(m5["one"] == "eins");
				}

				//TEST(constructors,"std::multimap")
				{
					j1.get<std::multimap<std::string, int>>();
					j2.get<std::multimap<std::string, unsigned int>>();
					j3.get<std::multimap<std::string, double>>();
					j4.get<std::multimap<std::string, bool>>();
					j5.get<std::multimap<std::string, std::string>>();
					//EXPECT_TRUE(m5["one"] == "eins");
				}

				//TEST(constructors,"std::unordered_multimap")
				{
					j1.get<std::unordered_multimap<std::string, int>>();
					j2.get<std::unordered_multimap<std::string, unsigned int>>();
					j3.get<std::unordered_multimap<std::string, double>>();
					j4.get<std::unordered_multimap<std::string, bool>>();
					j5.get<std::unordered_multimap<std::string, std::string>>();
					//EXPECT_TRUE(m5["one"] == "eins");
				}

				//TEST(constructors,"exception in case of a non-object type")
				{
					EXPECT_THROW((json().get<std::map<std::string, int>>()), json::type_error);
					//CHECK_THROWS_WITH((json().get<std::map<std::string, int>>()), "[json.exception.type_error.302] type must be object, but is null");
				}
			}

			//TEST(constructors,"array-like STL containers")
			{
				json j1 = {1, 2, 3, 4};
				json j2 = {1u, 2u, 3u, 4u};
				json j3 = {1.2, 2.3, 3.4, 4.5};
				json j4 = {true, false, true};
				json j5 = {"one", "two", "three"};

				//TEST(constructors,"std::list")
				{
					j1.get<std::list<int>>();
					j2.get<std::list<unsigned int>>();
					j3.get<std::list<double>>();
					j4.get<std::list<bool>>();
					j5.get<std::list<std::string>>();
				}

				//TEST(constructors,"std::forward_list")
				{
					j1.get<std::forward_list<int>>();
					j2.get<std::forward_list<unsigned int>>();
					j3.get<std::forward_list<double>>();
					j4.get<std::forward_list<bool>>();
					j5.get<std::forward_list<std::string>>();
				}

				//TEST(constructors,"std::array")
				{
					j1.get<std::array<int, 4>>();
					j2.get<std::array<unsigned int, 3>>();
					j3.get<std::array<double, 4>>();
					j4.get<std::array<bool, 3>>();
					j5.get<std::array<std::string, 3>>();

					//TEST(constructors,"std::array is larger than JSON")
					{
						std::array<int, 6> arr6 = {{1, 2, 3, 4, 5, 6}};
						EXPECT_THROW(arr6 = j1, json::out_of_range);
						//CHECK_THROWS_WITH(arr6 = j1, "[json.exception.out_of_range.401] array index 4 is out of range");
					}

					//TEST(constructors,"std::array is smaller than JSON")
					{
						std::array<int, 2> arr2 = {{8, 9}};
						arr2 = j1;
						EXPECT_TRUE(arr2[0] == 1);
						EXPECT_TRUE(arr2[1] == 2);
					}
				}

				//TEST(constructors,"std::valarray")
				{
					j1.get<std::valarray<int>>();
					j2.get<std::valarray<unsigned int>>();
					j3.get<std::valarray<double>>();
					j4.get<std::valarray<bool>>();
					j5.get<std::valarray<std::string>>();
				}

				//TEST(constructors,"std::vector")
				{
					j1.get<std::vector<int>>();
					j2.get<std::vector<unsigned int>>();
					j3.get<std::vector<double>>();
					j4.get<std::vector<bool>>();
					j5.get<std::vector<std::string>>();
				}

				//TEST(constructors,"std::deque")
				{
					j1.get<std::deque<int>>();
					j2.get<std::deque<unsigned int>>();
					j2.get<std::deque<double>>();
					j4.get<std::deque<bool>>();
					j5.get<std::deque<std::string>>();
				}

				//TEST(constructors,"std::set")
				{
					j1.get<std::set<int>>();
					j2.get<std::set<unsigned int>>();
					j3.get<std::set<double>>();
					j4.get<std::set<bool>>();
					j5.get<std::set<std::string>>();
				}

				//TEST(constructors,"std::unordered_set")
				{
					j1.get<std::unordered_set<int>>();
					j2.get<std::unordered_set<unsigned int>>();
					j3.get<std::unordered_set<double>>();
					j4.get<std::unordered_set<bool>>();
					j5.get<std::unordered_set<std::string>>();
				}

				//TEST(constructors,"std::map (array of pairs)")
				{
					std::map<int, int> m{{0, 1}, {1, 2}, {2, 3}};
					json j6 = m;

					auto m2 = j6.get<std::map<int, int>>();
					EXPECT_TRUE(m == m2);

					json j7 = {0, 1, 2, 3};
					EXPECT_THROW((j7.get<std::map<int, int>>()), json::type_error);
					//CHECK_THROWS_WITH((j7.get<std::map<int, int>>()), "[json.exception.type_error.302] type must be array, but is number");

					//TEST(constructors,"superfluous entries")
					{
					  json j8 = {{0, 1, 2}, {1, 2, 3}, {2, 3, 4}};
					  m2 = j8.get<std::map<int, int>>();
					  EXPECT_TRUE(m == m2);
					}
				}

				//TEST(constructors,"exception in case of a non-object type")
				{
					EXPECT_THROW((json().get<std::list<int>>()), json::type_error);
					EXPECT_THROW((json().get<std::vector<int>>()), json::type_error);
					EXPECT_THROW((json().get<std::vector<json>>()), json::type_error);
					EXPECT_THROW((json().get<std::list<json>>()), json::type_error);
					EXPECT_THROW((json().get<std::valarray<int>>()), json::type_error);

					// does type really must be an array? or it rather must not be null?
					// that's what I thought when other test like this one broke
					//CHECK_THROWS_WITH((json().get<std::list<int>>()), "[json.exception.type_error.302] type must be array, but is null");
					//CHECK_THROWS_WITH((json().get<std::vector<int>>()), "[json.exception.type_error.302] type must be array, but is null");
					//CHECK_THROWS_WITH((json().get<std::vector<json>>()), "[json.exception.type_error.302] type must be array, but is null");
					//CHECK_THROWS_WITH((json().get<std::list<json>>()), "[json.exception.type_error.302] type must be array, but is null");
					//CHECK_THROWS_WITH((json().get<std::valarray<int>>()), "[json.exception.type_error.302] type must be array, but is null");
					//CHECK_THROWS_WITH((json().get<std::map<int, int>>()), "[json.exception.type_error.302] type must be array, but is null");
				}
			}
		}
	}
}
