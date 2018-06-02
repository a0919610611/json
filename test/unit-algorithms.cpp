#include "gtest/gtest.h"
#include "json.hpp"

using nlohmann::json;

namespace
{
	class algorithm : public testing::Test
	{
	public:
		json j_array = {13, 29, 3, {{"one", 1}, {"two", 2}}, true, false, {1, 2, 3}, "foo", "baz"};
		json j_object = {{"one", 1}, {"two", 2}};
	};

	//TEST_F("non-modifying sequence operations")
	//{
		TEST_F(algorithm, stdColColall_of)
		{
			EXPECT_TRUE(std::all_of(j_array.begin(), j_array.end(), [](const json & value)
			{
				return value.size() > 0;
			}));
			EXPECT_TRUE(std::all_of(j_object.begin(), j_object.end(), [](const json & value)
			{
				return value.type() == json::value_t::number_integer;
			}));
		}

		TEST_F(algorithm, stdColColany_of)
		{
			EXPECT_TRUE(std::any_of(j_array.begin(), j_array.end(), [](const json & value)
			{
				return value.is_string() and value.get<std::string>() == "foo";
			}));
			EXPECT_TRUE(std::any_of(j_object.begin(), j_object.end(), [](const json & value)
			{
				return value.get<int>() > 1;
			}));
		}

		TEST_F(algorithm, stdColColnone_of)
		{
			EXPECT_TRUE(std::none_of(j_array.begin(), j_array.end(), [](const json & value)
			{
				return value.size() == 0;
			}));
			EXPECT_TRUE(std::none_of(j_object.begin(), j_object.end(), [](const json & value)
			{
				return value.get<int>() <= 0;
			}));
		}

		//TEST_F(algorithm,"std::for_each")
		//{
			TEST_F(algorithm, reading)
			{
				int sum = 0;

				std::for_each(j_array.cbegin(), j_array.cend(), [&sum](const json & value)
				{
					if (value.is_number())
					{
						sum += static_cast<int>(value);
					}
				});

				EXPECT_EQ(sum, 45);
			}

			TEST_F(algorithm, writing)
			{
				auto add17 = [](json & value)
				{
					if (value.is_array())
					{
						value.push_back(17);
					}
				};

				std::for_each(j_array.begin(), j_array.end(), add17);

				EXPECT_EQ(j_array[6], json({1, 2, 3, 17}));
			}
		//}

		TEST_F(algorithm, stdColColcount)
		{
			EXPECT_EQ(std::count(j_array.begin(), j_array.end(), json(true)), 1);
		}

		TEST_F(algorithm, stdColColcountUnderscoreif)
		{
			int result;
			result = std::count_if(j_array.begin(), j_array.end(), [](const json & value)
			{
				return (value.is_number());
			});
			EXPECT_EQ(result , 3);
			result = std::count_if(j_array.begin(), j_array.end(), [](const json&)
			{
				return true;
			});
			EXPECT_EQ(result, 9);
		}

		TEST_F(algorithm, stdColColmismatch)
		{
			json j_array2 = {13, 29, 3, {{"one", 1}, {"two", 2}, {"three", 3}}, true, false, {1, 2, 3}, "foo", "baz"};
			auto res = std::mismatch(j_array.begin(), j_array.end(), j_array2.begin());
			EXPECT_EQ(*res.first, json({{"one", 1}, {"two", 2}}));
			EXPECT_EQ(*res.second, json({{"one", 1}, {"two", 2}, {"three", 3}}));
		}

		//TEST_F(algorithm,"std::equal")
		//{
			TEST_F(algorithm, operatorEqualEqual)
			{
				EXPECT_TRUE(std::equal(j_array.begin(), j_array.end(), j_array.begin()));
				EXPECT_TRUE(std::equal(j_object.begin(), j_object.end(), j_object.begin()));
				EXPECT_FALSE(std::equal(j_array.begin(), j_array.end(), j_object.begin()));
			}

			TEST_F(algorithm, userdefinedcomparison)
			{
				// compare objects only by size of its elements
				json j_array2 = {13, 29, 3, {"Hello", "World"}, true, false, {{"one", 1}, {"two", 2}, {"three", 3}}, "foo", "baz"};
				EXPECT_FALSE(std::equal(j_array.begin(), j_array.end(), j_array2.begin()));
				EXPECT_TRUE(std::equal(j_array.begin(), j_array.end(), j_array2.begin(),
								 [](const json & a, const json & b)
				{
					return (a.size() == b.size());
				}));
			}
		//}

		TEST_F(algorithm, stdColColfind)
		{
			auto it = std::find(j_array.begin(), j_array.end(), json(false));
			EXPECT_EQ(std::distance(j_array.begin(), it), 5);
		}

		TEST_F(algorithm, stdColColfindUnderscoreif)
		{
			auto it = std::find_if(j_array.begin(), j_array.end(),
								   [](const json & value)
			{
				return value.is_boolean();
			});
			EXPECT_EQ(std::distance(j_array.begin(), it), 4);
		}

		TEST_F(algorithm, stdColColfindUnderscoreifUnderscorenot)
		{
			auto it = std::find_if_not(j_array.begin(), j_array.end(),
									   [](const json & value)
			{
				return value.is_number();
			});
			EXPECT_EQ(std::distance(j_array.begin(), it), 3);
		}

		TEST_F(algorithm, stdColColadjacentUnderscorefind)
		{
			EXPECT_TRUE(std::adjacent_find(j_array.begin(), j_array.end()) == j_array.end());
			EXPECT_EQ(j_array.begin(), std::adjacent_find(j_array.begin(), j_array.end(),
									 [](const json & v1, const json & v2)
			{
				return v1.type() == v2.type();
			}));
		}
	//}

	//TEST_F(algorithm,"modifying sequence operations")
	//{
		TEST_F(algorithm, stdColColreverse)
		{
			std::reverse(j_array.begin(), j_array.end());
			EXPECT_EQ(j_array, json({"baz", "foo", {1, 2, 3}, false, true, {{"one", 1}, {"two", 2}}, 3, 29, 13}));
		}

		TEST_F(algorithm, stdColColrotate)
		{
			std::rotate(j_array.begin(), j_array.begin() + 1, j_array.end());
			EXPECT_EQ(j_array, json({29, 3, {{"one", 1}, {"two", 2}}, true, false, {1, 2, 3}, "foo", "baz", 13}));
		}

		TEST_F(algorithm, stdColColpartition)
		{
			auto it = std::partition(j_array.begin(), j_array.end(), [](const json & v)
			{
				return v.is_string();
			});
			EXPECT_EQ(std::distance(j_array.begin(), it), 2);
			EXPECT_FALSE(it[2].is_string());
		}
	//}

	//TEST_F(algorithm,"sorting operations")
	//{
		//TEST_F(algorithm,"std::sort")
		//{
			TEST_F(algorithm, withstandardcomparison)
			{
				json j = {13, 29, 3, {{"one", 1}, {"two", 2}}, true, false, {1, 2, 3}, "foo", "baz", nullptr};
				std::sort(j.begin(), j.end());
				EXPECT_EQ(j, json({nullptr, false, true, 3, 13, 29, {{"one", 1}, {"two", 2}}, {1, 2, 3}, "baz", "foo"}));
			}

			TEST_F(algorithm, withuserdefinedcomparison)
			{
				json j = {3, {{"one", 1}, {"two", 2}}, {1, 2, 3}, nullptr};
				std::sort(j.begin(), j.end(), [](const json & a, const json & b)
				{
					return a.size() < b.size();
				});
				EXPECT_EQ(j, json({nullptr, 3, {{"one", 1}, {"two", 2}}, {1, 2, 3}}));
			}

			TEST_F(algorithm, sortinganobject)
			{
				json j({{"one", 1}, {"two", 2}});
				EXPECT_THROW(std::sort(j.begin(), j.end()), json::invalid_iterator);
				//CHECK_THROWS_WITH(std::sort(j.begin(), j.end()),
								  //"[json.exception.invalid_iterator.209] cannot use offsets with object iterators");
			}
		//}

		TEST_F(algorithm, stdColColpartial_sort)
		{
			json j = {13, 29, 3, {{"one", 1}, {"two", 2}}, true, false, {1, 2, 3}, "foo", "baz", nullptr};
			std::partial_sort(j.begin(), j.begin() + 4, j.end());
			EXPECT_EQ(j, json({nullptr, false, true, 3, {{"one", 1}, {"two", 2}}, 29, {1, 2, 3}, "foo", "baz", 13}));
		}
	//}

	//TEST_F(algorithm,"set operations")
	//{
		TEST_F(algorithm, stdColColmerge)
		{
			{
				json j1 = {2, 4, 6, 8};
				json j2 = {1, 2, 3, 5, 7};
				json j3;

				std::merge(j1.begin(), j1.end(), j2.begin(), j2.end(), std::back_inserter(j3));
				EXPECT_EQ(j3, json({1, 2, 2, 3, 4, 5, 6, 7, 8}));
			}
		}

		TEST_F(algorithm, stdColColset_difference)
		{
			json j1 = {1, 2, 3, 4, 5, 6, 7, 8};
			json j2 = {1, 2, 3, 5, 7};
			json j3;

			std::set_difference(j1.begin(), j1.end(), j2.begin(), j2.end(), std::back_inserter(j3));
			EXPECT_EQ(j3, json({4, 6, 8}));
		}

		TEST_F(algorithm, stdColColset_intersection)
		{
			json j1 = {1, 2, 3, 4, 5, 6, 7, 8};
			json j2 = {1, 2, 3, 5, 7};
			json j3;

			std::set_intersection(j1.begin(), j1.end(), j2.begin(), j2.end(), std::back_inserter(j3));
			EXPECT_EQ(j3, json({1, 2, 3, 5, 7}));
		}

		TEST_F(algorithm, stdColColset_union)
		{
			json j1 = {2, 4, 6, 8};
			json j2 = {1, 2, 3, 5, 7};
			json j3;

			std::set_union(j1.begin(), j1.end(), j2.begin(), j2.end(), std::back_inserter(j3));
			EXPECT_EQ(j3, json({1, 2, 3, 4, 5, 6, 7, 8}));
		}

		TEST_F(algorithm, stdColColset_symmetric_difference)
		{
			json j1 = {2, 4, 6, 8};
			json j2 = {1, 2, 3, 5, 7};
			json j3;

			std::set_symmetric_difference(j1.begin(), j1.end(), j2.begin(), j2.end(), std::back_inserter(j3));
			EXPECT_EQ(j3, json({1, 3, 4, 5, 6, 7, 8}));
		}
	//}

	TEST_F(algorithm, heapoperations)
	{
		std::make_heap(j_array.begin(), j_array.end());
		EXPECT_TRUE(std::is_heap(j_array.begin(), j_array.end()));
		std::sort_heap(j_array.begin(), j_array.end());
		EXPECT_TRUE(j_array == json({false, true, 3, 13, 29, {{"one", 1}, {"two", 2}}, {1, 2, 3}, "baz", "foo"}));
	}
}
