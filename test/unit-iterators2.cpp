#include "gtest/gtest.h"
#include "json.hpp"

using nlohmann::json;

namespace
{
	TEST(iterators2, iterators2)
	{
		//TEST(constructors,"iterator comparisons")
		{
			json j_values = {nullptr, true, 42, 42u, 23.23, {{"one", 1}, {"two", 2}}, {1, 2, 3, 4, 5}, "Hello, world"};

			for (json& j : j_values)
			{
				auto it1 = j.begin();
				auto it2 = j.begin();
				auto it3 = j.begin();
				++it2;
				++it3;
				++it3;
				auto it1_c = j.cbegin();
				auto it2_c = j.cbegin();
				auto it3_c = j.cbegin();
				++it2_c;
				++it3_c;
				++it3_c;

				// comparison: equal
				{
					EXPECT_TRUE(it1 == it1);
					EXPECT_TRUE(not (it1 == it2));
					EXPECT_TRUE(not (it1 == it3));
					EXPECT_TRUE(not (it2 == it3));
					EXPECT_TRUE(it1_c == it1_c);
					EXPECT_TRUE(not (it1_c == it2_c));
					EXPECT_TRUE(not (it1_c == it3_c));
					EXPECT_TRUE(not (it2_c == it3_c));
				}

				// comparison: not equal
				{
					// check definition
					EXPECT_TRUE( (it1 != it1) == not(it1 == it1) );
					EXPECT_TRUE( (it1 != it2) == not(it1 == it2) );
					EXPECT_TRUE( (it1 != it3) == not(it1 == it3) );
					EXPECT_TRUE( (it2 != it3) == not(it2 == it3) );
					EXPECT_TRUE( (it1_c != it1_c) == not(it1_c == it1_c) );
					EXPECT_TRUE( (it1_c != it2_c) == not(it1_c == it2_c) );
					EXPECT_TRUE( (it1_c != it3_c) == not(it1_c == it3_c) );
					EXPECT_TRUE( (it2_c != it3_c) == not(it2_c == it3_c) );
				}

				// comparison: smaller
				{
					if (j.type() == json::value_t::object)
					{
						EXPECT_THROW(it1 < it1, json::invalid_iterator);
						EXPECT_THROW(it1 < it2, json::invalid_iterator);
						EXPECT_THROW(it2 < it3, json::invalid_iterator);
						EXPECT_THROW(it1 < it3, json::invalid_iterator);
						EXPECT_THROW(it1_c < it1_c, json::invalid_iterator);
						EXPECT_THROW(it1_c < it2_c, json::invalid_iterator);
						EXPECT_THROW(it2_c < it3_c, json::invalid_iterator);
						EXPECT_THROW(it1_c < it3_c, json::invalid_iterator);
						//CHECK_THROWS_WITH(it1 < it1, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1 < it2, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it2 < it3, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1 < it3, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c < it1_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c < it2_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it2_c < it3_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c < it3_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
					}
					else
					{
						EXPECT_TRUE(not (it1 < it1));
						EXPECT_TRUE(it1 < it2);
						EXPECT_TRUE(it1 < it3);
						EXPECT_TRUE(it2 < it3);
						EXPECT_TRUE(not (it1_c < it1_c));
						EXPECT_TRUE(it1_c < it2_c);
						EXPECT_TRUE(it1_c < it3_c);
						EXPECT_TRUE(it2_c < it3_c);
					}
				}

				// comparison: less than or equal
				{
					if (j.type() == json::value_t::object)
					{
						EXPECT_THROW(it1 <= it1, json::invalid_iterator);
						EXPECT_THROW(it1 <= it2, json::invalid_iterator);
						EXPECT_THROW(it2 <= it3, json::invalid_iterator);
						EXPECT_THROW(it1 <= it3, json::invalid_iterator);
						EXPECT_THROW(it1_c <= it1_c, json::invalid_iterator);
						EXPECT_THROW(it1_c <= it2_c, json::invalid_iterator);
						EXPECT_THROW(it2_c <= it3_c, json::invalid_iterator);
						EXPECT_THROW(it1_c <= it3_c, json::invalid_iterator);
						//CHECK_THROWS_WITH(it1 <= it1, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1 <= it2, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it2 <= it3, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1 <= it3, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c <= it1_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c <= it2_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it2_c <= it3_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c <= it3_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
					}
					else
					{
						// check definition
						EXPECT_TRUE( (it1 <= it1) == not(it1 < it1) );
						EXPECT_TRUE( (it1 <= it2) == not(it2 < it1) );
						EXPECT_TRUE( (it1 <= it3) == not(it3 < it1) );
						EXPECT_TRUE( (it2 <= it3) == not(it3 < it2) );
						EXPECT_TRUE( (it1_c <= it1_c) == not(it1_c < it1_c) );
						EXPECT_TRUE( (it1_c <= it2_c) == not(it2_c < it1_c) );
						EXPECT_TRUE( (it1_c <= it3_c) == not(it3_c < it1_c) );
						EXPECT_TRUE( (it2_c <= it3_c) == not(it3_c < it2_c) );
					}
				}

				// comparison: greater than
				{
					if (j.type() == json::value_t::object)
					{
						EXPECT_THROW(it1 > it1, json::invalid_iterator);
						EXPECT_THROW(it1 > it2, json::invalid_iterator);
						EXPECT_THROW(it2 > it3, json::invalid_iterator);
						EXPECT_THROW(it1 > it3, json::invalid_iterator);
						EXPECT_THROW(it1_c > it1_c, json::invalid_iterator);
						EXPECT_THROW(it1_c > it2_c, json::invalid_iterator);
						EXPECT_THROW(it2_c > it3_c, json::invalid_iterator);
						EXPECT_THROW(it1_c > it3_c, json::invalid_iterator);
						//CHECK_THROWS_WITH(it1 > it1, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1 > it2, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it2 > it3, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1 > it3, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c > it1_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c > it2_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it2_c > it3_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c > it3_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
					}
					else
					{
						// check definition
						EXPECT_TRUE( (it1 > it1) == (it1 < it1) );
						EXPECT_TRUE( (it1 > it2) == (it2 < it1) );
						EXPECT_TRUE( (it1 > it3) == (it3 < it1) );
						EXPECT_TRUE( (it2 > it3) == (it3 < it2) );
						EXPECT_TRUE( (it1_c > it1_c) == (it1_c < it1_c) );
						EXPECT_TRUE( (it1_c > it2_c) == (it2_c < it1_c) );
						EXPECT_TRUE( (it1_c > it3_c) == (it3_c < it1_c) );
						EXPECT_TRUE( (it2_c > it3_c) == (it3_c < it2_c) );
					}
				}

				// comparison: greater than or equal
				{
					if (j.type() == json::value_t::object)
					{
						EXPECT_THROW(it1 >= it1, json::invalid_iterator);
						EXPECT_THROW(it1 >= it2, json::invalid_iterator);
						EXPECT_THROW(it2 >= it3, json::invalid_iterator);
						EXPECT_THROW(it1 >= it3, json::invalid_iterator);
						EXPECT_THROW(it1_c >= it1_c, json::invalid_iterator);
						EXPECT_THROW(it1_c >= it2_c, json::invalid_iterator);
						EXPECT_THROW(it2_c >= it3_c, json::invalid_iterator);
						EXPECT_THROW(it1_c >= it3_c, json::invalid_iterator);
						//CHECK_THROWS_WITH(it1 >= it1, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1 >= it2, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it2 >= it3, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1 >= it3, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c >= it1_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c >= it2_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it2_c >= it3_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c >= it3_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
					}
					else
					{
						// check definition
						EXPECT_TRUE( (it1 >= it1) == not(it1 < it1) );
						EXPECT_TRUE( (it1 >= it2) == not(it1 < it2) );
						EXPECT_TRUE( (it1 >= it3) == not(it1 < it3) );
						EXPECT_TRUE( (it2 >= it3) == not(it2 < it3) );
						EXPECT_TRUE( (it1_c >= it1_c) == not(it1_c < it1_c) );
						EXPECT_TRUE( (it1_c >= it2_c) == not(it1_c < it2_c) );
						EXPECT_TRUE( (it1_c >= it3_c) == not(it1_c < it3_c) );
						EXPECT_TRUE( (it2_c >= it3_c) == not(it2_c < it3_c) );
					}
				}
			}

			// check exceptions if different objects are compared
			for (auto j : j_values)
			{
				for (auto k : j_values)
				{
					if (j != k)
					{
						EXPECT_THROW(j.begin() == k.begin(), json::invalid_iterator);
						EXPECT_THROW(j.cbegin() == k.cbegin(), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.begin() == k.begin(), "[json.exception.invalid_iterator.212] cannot compare iterators of different containers");
						//CHECK_THROWS_WITH(j.cbegin() == k.cbegin(), "[json.exception.invalid_iterator.212] cannot compare iterators of different containers");

						EXPECT_THROW(j.begin() < k.begin(), json::invalid_iterator);
						EXPECT_THROW(j.cbegin() < k.cbegin(), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.begin() < k.begin(), "[json.exception.invalid_iterator.212] cannot compare iterators of different containers");
						//CHECK_THROWS_WITH(j.cbegin() < k.cbegin(), "[json.exception.invalid_iterator.212] cannot compare iterators of different containers");
					}
				}
			}
		}

		//TEST(constructors,"iterator arithmetic")
		{
			json j_object = {{"one", 1}, {"two", 2}, {"three", 3}};
			json j_array = {1, 2, 3, 4, 5, 6};
			json j_null = nullptr;
			json j_value = 42;

			//TEST(constructors,"addition and subtraction")
			{
				//TEST(constructors,"object")
				{
					{
						auto it = j_object.begin();
						EXPECT_THROW(it += 1, json::invalid_iterator);
						//CHECK_THROWS_WITH(it += 1, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.cbegin();
						EXPECT_THROW(it += 1, json::invalid_iterator);
						//CHECK_THROWS_WITH(it += 1, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.begin();
						EXPECT_THROW(it + 1, json::invalid_iterator);
						//CHECK_THROWS_WITH(it + 1, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.cbegin();
						EXPECT_THROW(it + 1, json::invalid_iterator);
						//CHECK_THROWS_WITH(it + 1, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.begin();
						EXPECT_THROW(1 + it, json::invalid_iterator);
						//CHECK_THROWS_WITH(1 + it, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.cbegin();
						EXPECT_THROW(1 + it, json::invalid_iterator);
						//CHECK_THROWS_WITH(1 + it, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.begin();
						EXPECT_THROW(it -= 1, json::invalid_iterator);
						//CHECK_THROWS_WITH(it -= 1, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.cbegin();
						EXPECT_THROW(it -= 1, json::invalid_iterator);
						//CHECK_THROWS_WITH(it -= 1, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.begin();
						EXPECT_THROW(it - 1, json::invalid_iterator);
						//CHECK_THROWS_WITH(it - 1, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.cbegin();
						EXPECT_THROW(it - 1, json::invalid_iterator);
						//CHECK_THROWS_WITH(it - 1, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.begin();
						EXPECT_THROW(it - it, json::invalid_iterator);
						//CHECK_THROWS_WITH(it - it, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.cbegin();
						EXPECT_THROW(it - it, json::invalid_iterator);
						//CHECK_THROWS_WITH(it - it, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
				}

				//TEST(constructors,"array")
				{
					{
						auto it = j_array.begin();
						it += 3;
						EXPECT_TRUE((j_array.begin() + 3) == it);
						EXPECT_TRUE((3 + j_array.begin()) == it);
						EXPECT_TRUE((it - 3) == j_array.begin());
						EXPECT_TRUE((it - j_array.begin()) == 3);
						EXPECT_TRUE(*it == json(4));
						it -= 2;
						EXPECT_TRUE(*it == json(2));
					}
					{
						auto it = j_array.cbegin();
						it += 3;
						EXPECT_TRUE((j_array.cbegin() + 3) == it);
						EXPECT_TRUE((3 + j_array.cbegin()) == it);
						EXPECT_TRUE((it - 3) == j_array.cbegin());
						EXPECT_TRUE((it - j_array.cbegin()) == 3);
						EXPECT_TRUE(*it == json(4));
						it -= 2;
						EXPECT_TRUE(*it == json(2));
					}
				}

				//TEST(constructors,"null")
				{
					{
						auto it = j_null.begin();
						it += 3;
						EXPECT_TRUE((j_null.begin() + 3) == it);
						EXPECT_TRUE((3 + j_null.begin()) == it);
						EXPECT_TRUE((it - 3) == j_null.begin());
						EXPECT_TRUE((it - j_null.begin()) == 3);
						EXPECT_TRUE(it != j_null.end());
						it -= 3;
						EXPECT_TRUE(it == j_null.end());
					}
					{
						auto it = j_null.cbegin();
						it += 3;
						EXPECT_TRUE((j_null.cbegin() + 3) == it);
						EXPECT_TRUE((3 + j_null.cbegin()) == it);
						EXPECT_TRUE((it - 3) == j_null.cbegin());
						EXPECT_TRUE((it - j_null.cbegin()) == 3);
						EXPECT_TRUE(it != j_null.cend());
						it -= 3;
						EXPECT_TRUE(it == j_null.cend());
					}
				}

				//TEST(constructors,"value")
				{
					{
						auto it = j_value.begin();
						it += 3;
						EXPECT_TRUE((j_value.begin() + 3) == it);
						EXPECT_TRUE((3 + j_value.begin()) == it);
						EXPECT_TRUE((it - 3) == j_value.begin());
						EXPECT_TRUE((it - j_value.begin()) == 3);
						EXPECT_TRUE(it != j_value.end());
						it -= 3;
						EXPECT_TRUE(*it == json(42));
					}
					{
						auto it = j_value.cbegin();
						it += 3;
						EXPECT_TRUE((j_value.cbegin() + 3) == it);
						EXPECT_TRUE((3 + j_value.cbegin()) == it);
						EXPECT_TRUE((it - 3) == j_value.cbegin());
						EXPECT_TRUE((it - j_value.cbegin()) == 3);
						EXPECT_TRUE(it != j_value.cend());
						it -= 3;
						EXPECT_TRUE(*it == json(42));
					}
				}
			}

			//TEST(constructors,"subscript operator")
			{
				//TEST(constructors,"object")
				{
					{
						auto it = j_object.begin();
						EXPECT_THROW(it[0], json::invalid_iterator);
						EXPECT_THROW(it[1], json::invalid_iterator);
						//CHECK_THROWS_WITH(it[0], "[json.exception.invalid_iterator.208] cannot use operator[] for object iterators");
						//CHECK_THROWS_WITH(it[1], "[json.exception.invalid_iterator.208] cannot use operator[] for object iterators");
					}
					{
						auto it = j_object.cbegin();
						EXPECT_THROW(it[0], json::invalid_iterator);
						EXPECT_THROW(it[1], json::invalid_iterator);
						//CHECK_THROWS_WITH(it[0], "[json.exception.invalid_iterator.208] cannot use operator[] for object iterators");
						//CHECK_THROWS_WITH(it[1], "[json.exception.invalid_iterator.208] cannot use operator[] for object iterators");
					}
				}

				//TEST(constructors,"array")
				{
					{
						auto it = j_array.begin();
						EXPECT_TRUE(it[0] == json(1));
						EXPECT_TRUE(it[1] == json(2));
						EXPECT_TRUE(it[2] == json(3));
						EXPECT_TRUE(it[3] == json(4));
						EXPECT_TRUE(it[4] == json(5));
						EXPECT_TRUE(it[5] == json(6));
					}
					{
						auto it = j_array.cbegin();
						EXPECT_TRUE(it[0] == json(1));
						EXPECT_TRUE(it[1] == json(2));
						EXPECT_TRUE(it[2] == json(3));
						EXPECT_TRUE(it[3] == json(4));
						EXPECT_TRUE(it[4] == json(5));
						EXPECT_TRUE(it[5] == json(6));
					}
				}

				//TEST(constructors,"null")
				{
					{
						auto it = j_null.begin();
						EXPECT_THROW(it[0], json::invalid_iterator);
						EXPECT_THROW(it[1], json::invalid_iterator);
						//CHECK_THROWS_WITH(it[0], "[json.exception.invalid_iterator.214] cannot get value");
						//CHECK_THROWS_WITH(it[1], "[json.exception.invalid_iterator.214] cannot get value");
					}
					{
						auto it = j_null.cbegin();
						EXPECT_THROW(it[0], json::invalid_iterator);
						EXPECT_THROW(it[1], json::invalid_iterator);
						//CHECK_THROWS_WITH(it[0], "[json.exception.invalid_iterator.214] cannot get value");
						//CHECK_THROWS_WITH(it[1], "[json.exception.invalid_iterator.214] cannot get value");
					}
				}

				//TEST(constructors,"value")
				{
					{
						auto it = j_value.begin();
						EXPECT_TRUE(it[0] == json(42));
						EXPECT_THROW(it[1], json::invalid_iterator);
						//CHECK_THROWS_WITH(it[1], "[json.exception.invalid_iterator.214] cannot get value");
					}
					{
						auto it = j_value.cbegin();
						EXPECT_TRUE(it[0] == json(42));
						EXPECT_THROW(it[1], json::invalid_iterator);
						//CHECK_THROWS_WITH(it[1], "[json.exception.invalid_iterator.214] cannot get value");
					}
				}
			}
		}

		//TEST(constructors,"reverse iterator comparisons")
		{
			json j_values = {nullptr, true, 42, 42u, 23.23, {{"one", 1}, {"two", 2}}, {1, 2, 3, 4, 5}, "Hello, world"};

			for (json& j : j_values)
			{
				auto it1 = j.rbegin();
				auto it2 = j.rbegin();
				auto it3 = j.rbegin();
				++it2;
				++it3;
				++it3;
				auto it1_c = j.crbegin();
				auto it2_c = j.crbegin();
				auto it3_c = j.crbegin();
				++it2_c;
				++it3_c;
				++it3_c;

				// comparison: equal
				{
					EXPECT_TRUE(it1 == it1);
					EXPECT_TRUE(not (it1 == it2));
					EXPECT_TRUE(not (it1 == it3));
					EXPECT_TRUE(not (it2 == it3));
					EXPECT_TRUE(it1_c == it1_c);
					EXPECT_TRUE(not (it1_c == it2_c));
					EXPECT_TRUE(not (it1_c == it3_c));
					EXPECT_TRUE(not (it2_c == it3_c));
				}

				// comparison: not equal
				{
					// check definition
					EXPECT_TRUE( (it1 != it1) == not(it1 == it1) );
					EXPECT_TRUE( (it1 != it2) == not(it1 == it2) );
					EXPECT_TRUE( (it1 != it3) == not(it1 == it3) );
					EXPECT_TRUE( (it2 != it3) == not(it2 == it3) );
					EXPECT_TRUE( (it1_c != it1_c) == not(it1_c == it1_c) );
					EXPECT_TRUE( (it1_c != it2_c) == not(it1_c == it2_c) );
					EXPECT_TRUE( (it1_c != it3_c) == not(it1_c == it3_c) );
					EXPECT_TRUE( (it2_c != it3_c) == not(it2_c == it3_c) );
				}

				// comparison: smaller
				{
					if (j.type() == json::value_t::object)
					{
						EXPECT_THROW(it1 < it1, json::invalid_iterator);
						EXPECT_THROW(it1 < it2, json::invalid_iterator);
						EXPECT_THROW(it2 < it3, json::invalid_iterator);
						EXPECT_THROW(it1 < it3, json::invalid_iterator);
						EXPECT_THROW(it1_c < it1_c, json::invalid_iterator);
						EXPECT_THROW(it1_c < it2_c, json::invalid_iterator);
						EXPECT_THROW(it2_c < it3_c, json::invalid_iterator);
						EXPECT_THROW(it1_c < it3_c, json::invalid_iterator);
						//CHECK_THROWS_WITH(it1 < it1, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1 < it2, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it2 < it3, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1 < it3, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c < it1_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c < it2_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it2_c < it3_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c < it3_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
					}
					else
					{
						EXPECT_TRUE(not (it1 < it1));
						EXPECT_TRUE(it1 < it2);
						EXPECT_TRUE(it1 < it3);
						EXPECT_TRUE(it2 < it3);
						EXPECT_TRUE(not (it1_c < it1_c));
						EXPECT_TRUE(it1_c < it2_c);
						EXPECT_TRUE(it1_c < it3_c);
						EXPECT_TRUE(it2_c < it3_c);
					}
				}

				// comparison: less than or equal
				{
					if (j.type() == json::value_t::object)
					{
						EXPECT_THROW(it1 <= it1, json::invalid_iterator);
						EXPECT_THROW(it1 <= it2, json::invalid_iterator);
						EXPECT_THROW(it2 <= it3, json::invalid_iterator);
						EXPECT_THROW(it1 <= it3, json::invalid_iterator);
						EXPECT_THROW(it1_c <= it1_c, json::invalid_iterator);
						EXPECT_THROW(it1_c <= it2_c, json::invalid_iterator);
						EXPECT_THROW(it2_c <= it3_c, json::invalid_iterator);
						EXPECT_THROW(it1_c <= it3_c, json::invalid_iterator);
						//CHECK_THROWS_WITH(it1 <= it1, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1 <= it2, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it2 <= it3, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1 <= it3, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c <= it1_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c <= it2_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it2_c <= it3_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c <= it3_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
					}
					else
					{
						// check definition
						EXPECT_TRUE( (it1 <= it1) == not(it1 < it1) );
						EXPECT_TRUE( (it1 <= it2) == not(it2 < it1) );
						EXPECT_TRUE( (it1 <= it3) == not(it3 < it1) );
						EXPECT_TRUE( (it2 <= it3) == not(it3 < it2) );
						EXPECT_TRUE( (it1_c <= it1_c) == not(it1_c < it1_c) );
						EXPECT_TRUE( (it1_c <= it2_c) == not(it2_c < it1_c) );
						EXPECT_TRUE( (it1_c <= it3_c) == not(it3_c < it1_c) );
						EXPECT_TRUE( (it2_c <= it3_c) == not(it3_c < it2_c) );
					}
				}

				// comparison: greater than
				{
					if (j.type() == json::value_t::object)
					{
						EXPECT_THROW(it1 > it1, json::invalid_iterator);
						EXPECT_THROW(it1 > it2, json::invalid_iterator);
						EXPECT_THROW(it2 > it3, json::invalid_iterator);
						EXPECT_THROW(it1 > it3, json::invalid_iterator);
						EXPECT_THROW(it1_c > it1_c, json::invalid_iterator);
						EXPECT_THROW(it1_c > it2_c, json::invalid_iterator);
						EXPECT_THROW(it2_c > it3_c, json::invalid_iterator);
						EXPECT_THROW(it1_c > it3_c, json::invalid_iterator);
						//CHECK_THROWS_WITH(it1 > it1, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1 > it2, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it2 > it3, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1 > it3, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c > it1_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c > it2_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it2_c > it3_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c > it3_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
					}
					else
					{
						// check definition
						EXPECT_TRUE( (it1 > it1) == (it1 < it1) );
						EXPECT_TRUE( (it1 > it2) == (it2 < it1) );
						EXPECT_TRUE( (it1 > it3) == (it3 < it1) );
						EXPECT_TRUE( (it2 > it3) == (it3 < it2) );
						EXPECT_TRUE( (it1_c > it1_c) == (it1_c < it1_c) );
						EXPECT_TRUE( (it1_c > it2_c) == (it2_c < it1_c) );
						EXPECT_TRUE( (it1_c > it3_c) == (it3_c < it1_c) );
						EXPECT_TRUE( (it2_c > it3_c) == (it3_c < it2_c) );
					}
				}

				// comparison: greater than or equal
				{
					if (j.type() == json::value_t::object)
					{
						EXPECT_THROW(it1 >= it1, json::invalid_iterator);
						EXPECT_THROW(it1 >= it2, json::invalid_iterator);
						EXPECT_THROW(it2 >= it3, json::invalid_iterator);
						EXPECT_THROW(it1 >= it3, json::invalid_iterator);
						EXPECT_THROW(it1_c >= it1_c, json::invalid_iterator);
						EXPECT_THROW(it1_c >= it2_c, json::invalid_iterator);
						EXPECT_THROW(it2_c >= it3_c, json::invalid_iterator);
						EXPECT_THROW(it1_c >= it3_c, json::invalid_iterator);
						//CHECK_THROWS_WITH(it1 >= it1, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1 >= it2, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it2 >= it3, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1 >= it3, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c >= it1_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c >= it2_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it2_c >= it3_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
						//CHECK_THROWS_WITH(it1_c >= it3_c, "[json.exception.invalid_iterator.213] cannot compare order of object iterators");
					}
					else
					{
						// check definition
						EXPECT_TRUE( (it1 >= it1) == not(it1 < it1) );
						EXPECT_TRUE( (it1 >= it2) == not(it1 < it2) );
						EXPECT_TRUE( (it1 >= it3) == not(it1 < it3) );
						EXPECT_TRUE( (it2 >= it3) == not(it2 < it3) );
						EXPECT_TRUE( (it1_c >= it1_c) == not(it1_c < it1_c) );
						EXPECT_TRUE( (it1_c >= it2_c) == not(it1_c < it2_c) );
						EXPECT_TRUE( (it1_c >= it3_c) == not(it1_c < it3_c) );
						EXPECT_TRUE( (it2_c >= it3_c) == not(it2_c < it3_c) );
					}
				}
			}

			// check exceptions if different objects are compared
			for (auto j : j_values)
			{
				for (auto k : j_values)
				{
					if (j != k)
					{
						EXPECT_THROW(j.rbegin() == k.rbegin(), json::invalid_iterator);
						EXPECT_THROW(j.crbegin() == k.crbegin(), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.rbegin() == k.rbegin(), "[json.exception.invalid_iterator.212] cannot compare iterators of different containers");
						//CHECK_THROWS_WITH(j.crbegin() == k.crbegin(), "[json.exception.invalid_iterator.212] cannot compare iterators of different containers");

						EXPECT_THROW(j.rbegin() < k.rbegin(), json::invalid_iterator);
						EXPECT_THROW(j.crbegin() < k.crbegin(), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.rbegin() < k.rbegin(), "[json.exception.invalid_iterator.212] cannot compare iterators of different containers");
						//CHECK_THROWS_WITH(j.crbegin() < k.crbegin(), "[json.exception.invalid_iterator.212] cannot compare iterators of different containers");
					}
				}
			}
		}

		//TEST(constructors,"reverse iterator arithmetic")
		{
			json j_object = {{"one", 1}, {"two", 2}, {"three", 3}};
			json j_array = {1, 2, 3, 4, 5, 6};
			json j_null = nullptr;
			json j_value = 42;

			//TEST(constructors,"addition and subtraction")
			{
				//TEST(constructors,"object")
				{
					{
						auto it = j_object.rbegin();
						EXPECT_THROW(it += 1, json::invalid_iterator);
						//CHECK_THROWS_WITH(it += 1, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.crbegin();
						EXPECT_THROW(it += 1, json::invalid_iterator);
						//CHECK_THROWS_WITH(it += 1, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.rbegin();
						EXPECT_THROW(it + 1, json::invalid_iterator);
						//CHECK_THROWS_WITH(it + 1, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.crbegin();
						EXPECT_THROW(it + 1, json::invalid_iterator);
						//CHECK_THROWS_WITH(it + 1, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.rbegin();
						EXPECT_THROW(1 + it, json::invalid_iterator);
						//CHECK_THROWS_WITH(1 + it, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.crbegin();
						EXPECT_THROW(1 + it, json::invalid_iterator);
						//CHECK_THROWS_WITH(1 + it, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.rbegin();
						EXPECT_THROW(it -= 1, json::invalid_iterator);
						//CHECK_THROWS_WITH(it -= 1, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.crbegin();
						EXPECT_THROW(it -= 1, json::invalid_iterator);
						//CHECK_THROWS_WITH(it -= 1, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.rbegin();
						EXPECT_THROW(it - 1, json::invalid_iterator);
						//CHECK_THROWS_WITH(it - 1, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.crbegin();
						EXPECT_THROW(it - 1, json::invalid_iterator);
						//CHECK_THROWS_WITH(it - 1, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.rbegin();
						EXPECT_THROW(it - it, json::invalid_iterator);
						//CHECK_THROWS_WITH(it - it, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.crbegin();
						EXPECT_THROW(it - it, json::invalid_iterator);
						//CHECK_THROWS_WITH(it - it, "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
				}

				//TEST(constructors,"array")
				{
					{
						auto it = j_array.rbegin();
						it += 3;
						EXPECT_TRUE((j_array.rbegin() + 3) == it);
						EXPECT_TRUE(json::reverse_iterator(3 + j_array.rbegin()) == it);
						EXPECT_TRUE((it - 3) == j_array.rbegin());
						EXPECT_TRUE((it - j_array.rbegin()) == 3);
						EXPECT_TRUE(*it == json(3));
						it -= 2;
						EXPECT_TRUE(*it == json(5));
					}
					{
						auto it = j_array.crbegin();
						it += 3;
						EXPECT_TRUE((j_array.crbegin() + 3) == it);
						EXPECT_TRUE(json::const_reverse_iterator(3 + j_array.crbegin()) == it);
						EXPECT_TRUE((it - 3) == j_array.crbegin());
						EXPECT_TRUE((it - j_array.crbegin()) == 3);
						EXPECT_TRUE(*it == json(3));
						it -= 2;
						EXPECT_TRUE(*it == json(5));
					}
				}

				//TEST(constructors,"null")
				{
					{
						auto it = j_null.rbegin();
						it += 3;
						EXPECT_TRUE((j_null.rbegin() + 3) == it);
						EXPECT_TRUE(json::reverse_iterator(3 + j_null.rbegin()) == it);
						EXPECT_TRUE((it - 3) == j_null.rbegin());
						EXPECT_TRUE((it - j_null.rbegin()) == 3);
						EXPECT_TRUE(it != j_null.rend());
						it -= 3;
						EXPECT_TRUE(it == j_null.rend());
					}
					{
						auto it = j_null.crbegin();
						it += 3;
						EXPECT_TRUE((j_null.crbegin() + 3) == it);
						EXPECT_TRUE(json::const_reverse_iterator(3 + j_null.crbegin()) == it);
						EXPECT_TRUE((it - 3) == j_null.crbegin());
						EXPECT_TRUE((it - j_null.crbegin()) == 3);
						EXPECT_TRUE(it != j_null.crend());
						it -= 3;
						EXPECT_TRUE(it == j_null.crend());
					}
				}

				//TEST(constructors,"value")
				{
					{
						auto it = j_value.rbegin();
						it += 3;
						EXPECT_TRUE((j_value.rbegin() + 3) == it);
						EXPECT_TRUE(json::reverse_iterator(3 + j_value.rbegin()) == it);
						EXPECT_TRUE((it - 3) == j_value.rbegin());
						EXPECT_TRUE((it - j_value.rbegin()) == 3);
						EXPECT_TRUE(it != j_value.rend());
						it -= 3;
						EXPECT_TRUE(*it == json(42));
					}
					{
						auto it = j_value.crbegin();
						it += 3;
						EXPECT_TRUE((j_value.crbegin() + 3) == it);
						EXPECT_TRUE(json::const_reverse_iterator(3 + j_value.crbegin()) == it);
						EXPECT_TRUE((it - 3) == j_value.crbegin());
						EXPECT_TRUE((it - j_value.crbegin()) == 3);
						EXPECT_TRUE(it != j_value.crend());
						it -= 3;
						EXPECT_TRUE(*it == json(42));
					}
				}
			}

			//TEST(constructors,"subscript operator")
			{
				//TEST(constructors,"object")
				{
					{
						auto it = j_object.rbegin();
						EXPECT_THROW(it[0], json::invalid_iterator);
						EXPECT_THROW(it[1], json::invalid_iterator);
						//CHECK_THROWS_WITH(it[0], "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
						//CHECK_THROWS_WITH(it[1], "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
					{
						auto it = j_object.crbegin();
						EXPECT_THROW(it[0], json::invalid_iterator);
						EXPECT_THROW(it[1], json::invalid_iterator);
						//CHECK_THROWS_WITH(it[0], "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
						//CHECK_THROWS_WITH(it[1], "[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
					}
				}

				//TEST(constructors,"array")
				{
					{
						auto it = j_array.rbegin();
						EXPECT_TRUE(it[0] == json(6));
						EXPECT_TRUE(it[1] == json(5));
						EXPECT_TRUE(it[2] == json(4));
						EXPECT_TRUE(it[3] == json(3));
						EXPECT_TRUE(it[4] == json(2));
						EXPECT_TRUE(it[5] == json(1));
					}
					{
						auto it = j_array.crbegin();
						EXPECT_TRUE(it[0] == json(6));
						EXPECT_TRUE(it[1] == json(5));
						EXPECT_TRUE(it[2] == json(4));
						EXPECT_TRUE(it[3] == json(3));
						EXPECT_TRUE(it[4] == json(2));
						EXPECT_TRUE(it[5] == json(1));
					}
				}

				//TEST(constructors,"null")
				{
					{
						auto it = j_null.rbegin();
						EXPECT_THROW(it[0], json::invalid_iterator);
						EXPECT_THROW(it[1], json::invalid_iterator);
						//CHECK_THROWS_WITH(it[0], "[json.exception.invalid_iterator.214] cannot get value");
						//CHECK_THROWS_WITH(it[1], "[json.exception.invalid_iterator.214] cannot get value");
					}
					{
						auto it = j_null.crbegin();
						EXPECT_THROW(it[0], json::invalid_iterator);
						EXPECT_THROW(it[1], json::invalid_iterator);
						//CHECK_THROWS_WITH(it[0], "[json.exception.invalid_iterator.214] cannot get value");
						//CHECK_THROWS_WITH(it[1], "[json.exception.invalid_iterator.214] cannot get value");
					}
				}

				//TEST(constructors,"value")
				{
					{
						auto it = j_value.rbegin();
						EXPECT_TRUE(it[0] == json(42));
						EXPECT_THROW(it[1], json::invalid_iterator);
						//CHECK_THROWS_WITH(it[1], "[json.exception.invalid_iterator.214] cannot get value");
					}
					{
						auto it = j_value.crbegin();
						EXPECT_TRUE(it[0] == json(42));
						EXPECT_THROW(it[1], json::invalid_iterator);
						//CHECK_THROWS_WITH(it[1], "[json.exception.invalid_iterator.214] cannot get value");
					}
				}
			}
		}
	}
}
