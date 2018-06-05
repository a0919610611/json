#include "gtest/gtest.h"
#include "json.hpp"

using nlohmann::json;

namespace
{

	// helper function to check std::less<json::value_t>
	// see http://en.cppreference.com/w/cpp/utility/functional/less
	template <typename A, typename B, typename U = std::less<json::value_t>>
	bool f(A a, B b, U u = U())
	{
		return u(a, b);
	}

	TEST(lexicographical_comparison_operators, comparison)
	{
		//TEST(comparison,"types")
		{
			std::vector<json::value_t> j_types =
			{
				json::value_t::null,
				json::value_t::boolean,
				json::value_t::number_integer,
				json::value_t::number_unsigned,
				json::value_t::number_float,
				json::value_t::object,
				json::value_t::array,
				json::value_t::string
			};

			//TEST(comparison,"comparison: less")
			{
				std::vector<std::vector<bool>> expected =
				{
					{false, true, true, true, true, true, true, true},
					{false, false, true, true, true, true, true, true},
					{false, false, false, false, false, true, true, true},
					{false, false, false, false, false, true, true, true},
					{false, false, false, false, false, true, true, true},
					{false, false, false, false, false, false, true, true},
					{false, false, false, false, false, false, false, true},
					{false, false, false, false, false, false, false, false}
				};

				for (size_t i = 0; i < j_types.size(); ++i)
				{
					for (size_t j = 0; j < j_types.size(); ++j)
					{
						//CAPTURE(i);
						//CAPTURE(j);
						// check precomputed values
						EXPECT_TRUE(operator<(j_types[i], j_types[j]) == expected[i][j]);
						EXPECT_TRUE(f(j_types[i], j_types[j]) == expected[i][j]);
					}
				}
			}
		}

		//TEST(comparison,"values")
		{
			json j_values =
			{
				nullptr, nullptr,
				-17, 42,
				8u, 13u,
				3.14159, 23.42,
				"foo", "bar",
				true, false,
				{1, 2, 3}, {"one", "two", "three"},
				{{"first", 1}, {"second", 2}}, {{"a", "A"}, {"b", {"B"}}}
			};

			//TEST(comparison,"comparison: equal")
			{
				std::vector<std::vector<bool>> expected =
				{
					{true, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
					{true, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
					{false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false},
					{false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false},
					{false, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false},
					{false, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false},
					{false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false},
					{false, false, false, false, false, false, false, true, false, false, false, false, false, false, false, false},
					{false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, false},
					{false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false},
					{false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false},
					{false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false},
					{false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false},
					{false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false},
					{false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false},
					{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true}
				};

				for (size_t i = 0; i < j_values.size(); ++i)
				{
					for (size_t j = 0; j < j_values.size(); ++j)
					{
						//CAPTURE(i);
						//CAPTURE(j);
						//CAPTURE(j_values[i]);
						//CAPTURE(j_values[j]);
						// check precomputed values
						EXPECT_TRUE( (j_values[i] == j_values[j]) == expected[i][j] );
					}
				}

				// comparison with discarded elements
				json j_discarded(json::value_t::discarded);
				for (size_t i = 0; i < j_values.size(); ++i)
				{
					EXPECT_TRUE( (j_values[i] == j_discarded) == false);
					EXPECT_TRUE( (j_discarded == j_values[i]) == false);
					EXPECT_TRUE( (j_discarded == j_discarded) == false);
				}

				// compare with null pointer
				json j_null;
				EXPECT_TRUE(j_null == nullptr);
				EXPECT_TRUE(nullptr == j_null);
			}

			//TEST(comparison,"comparison: not equal")
			{
				for (size_t i = 0; i < j_values.size(); ++i)
				{
					for (size_t j = 0; j < j_values.size(); ++j)
					{
						//CAPTURE(i);
						//CAPTURE(j);
						// check definition
						EXPECT_TRUE( (j_values[i] != j_values[j]) == not(j_values[i] == j_values[j]) );
					}
				}

				// compare with null pointer
				json j_null;
				EXPECT_TRUE( (j_null != nullptr) == false);
				EXPECT_TRUE( (nullptr != j_null) == false);
				EXPECT_TRUE( (j_null != nullptr) == not(j_null == nullptr));
				EXPECT_TRUE( (nullptr != j_null) == not(nullptr == j_null));
			}

			//TEST(comparison,"comparison: less")
			{
				std::vector<std::vector<bool>> expected =
				{
					{false, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true},
					{false, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true},
					{false, false, false, true, true, true, true, true, true, true, false, false, true, true, true, true},
					{false, false, false, false, false, false, false, false, true, true, false, false, true, true, true, true},
					{false, false, false, true, false, true, false, true, true, true, false, false, true, true, true, true},
					{false, false, false, true, false, false, false, true, true, true, false, false, true, true, true, true},
					{false, false, false, true, true, true, false, true, true, true, false, false, true, true, true, true},
					{false, false, false, true, false, false, false, false, true, true, false, false, true, true, true, true},
					{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
					{false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, false},
					{false, false, true, true, true, true, true, true, true, true, false, false, true, true, true, true},
					{false, false, true, true, true, true, true, true, true, true, true, false, true, true, true, true},
					{false, false, false, false, false, false, false, false, true, true, false, false, false, true, false, false},
					{false, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false},
					{false, false, false, false, false, false, false, false, true, true, false, false, true, true, false, false},
					{false, false, false, false, false, false, false, false, true, true, false, false, true, true, true, false}
				};

				for (size_t i = 0; i < j_values.size(); ++i)
				{
					for (size_t j = 0; j < j_values.size(); ++j)
					{
						//CAPTURE(i);
						//CAPTURE(j);
						//CAPTURE(j_values[i]);
						//CAPTURE(j_values[j]);
						// check precomputed values
						EXPECT_TRUE( (j_values[i] < j_values[j]) == expected[i][j] );
					}
				}

				// comparison with discarded elements
				json j_discarded(json::value_t::discarded);
				for (size_t i = 0; i < j_values.size(); ++i)
				{
					//CAPTURE(i);
					EXPECT_TRUE( (j_values[i] < j_discarded) == false);
					EXPECT_TRUE( (j_discarded < j_values[i]) == false);
					EXPECT_TRUE( (j_discarded < j_discarded) == false);
				}
			}

			//TEST(comparison,"comparison: less than or equal equal")
			{
				for (size_t i = 0; i < j_values.size(); ++i)
				{
					for (size_t j = 0; j < j_values.size(); ++j)
					{
						//CAPTURE(i);
						//CAPTURE(j);
						// check definition
						EXPECT_TRUE( (j_values[i] <= j_values[j]) == not(j_values[j] < j_values[i]) );
					}
				}
			}

			//TEST(comparison,"comparison: greater than")
			{
				for (size_t i = 0; i < j_values.size(); ++i)
				{
					for (size_t j = 0; j < j_values.size(); ++j)
					{
						//CAPTURE(i);
						//CAPTURE(j);
						// check definition
						EXPECT_TRUE( (j_values[i] > j_values[j]) == (j_values[j] < j_values[i]) );
					}
				}
			}

			//TEST(comparison,"comparison: greater than or equal")
			{
				for (size_t i = 0; i < j_values.size(); ++i)
				{
					for (size_t j = 0; j < j_values.size(); ++j)
					{
						//CAPTURE(i);
						//CAPTURE(j);
						// check definition
						EXPECT_TRUE( (j_values[i] >= j_values[j]) == not(j_values[i] < j_values[j]) );
					}
				}
			}
		}
	}
}
