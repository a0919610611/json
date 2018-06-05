#include "gtest/gtest.h"
#define private public
#include "json.hpp"

using nlohmann::json;
namespace
{
	TEST(const_iterator_class, const_iterator)
	{
		//TEST(const_iterator_class,"construction")
		{
			//TEST(const_iterator_class,"constructor")
			{
				//TEST(const_iterator_class,"null")
				{
					json j(json::value_t::null);
					json::const_iterator it(&j);
				}

				//TEST(const_iterator_class,"object")
				{
					json j(json::value_t::object);
					json::const_iterator it(&j);
				}

				//TEST(const_iterator_class,"array")
				{
					json j(json::value_t::array);
					json::const_iterator it(&j);
				}
			}

			//TEST(const_iterator_class,"copy assignment")
			{
				json j(json::value_t::null);
				json::const_iterator it(&j);
				json::const_iterator it2(&j);
				it2 = it;
			}

			//TEST(const_iterator_class,"copy constructor from non-const iterator")
			{
				//TEST(const_iterator_class,"create from uninitialized iterator")
				{
					const json::iterator it {};
					json::const_iterator cit(it);
				}

				//TEST(const_iterator_class,"create from initialized iterator")
				{
					json j;
					const json::iterator it = j.begin();
					json::const_iterator cit(it);
				}
			}
		}

		//TEST(const_iterator_class,"initialization")
		{
			//TEST(const_iterator_class,"set_begin")
			{
				//TEST(const_iterator_class,"null")
				{
					json j(json::value_t::null);
					json::const_iterator it(&j);
					it.set_begin();
					EXPECT_TRUE((it == j.cbegin()));
				}

				//TEST(const_iterator_class,"object")
				{
					json j(json::value_t::object);
					json::const_iterator it(&j);
					it.set_begin();
					EXPECT_TRUE((it == j.cbegin()));
				}

				//TEST(const_iterator_class,"array")
				{
					json j(json::value_t::array);
					json::const_iterator it(&j);
					it.set_begin();
					EXPECT_TRUE((it == j.cbegin()));
				}
			}

			//TEST(const_iterator_class,"set_end")
			{
				//TEST(const_iterator_class,"null")
				{
					json j(json::value_t::null);
					json::const_iterator it(&j);
					it.set_end();
					EXPECT_TRUE((it == j.cend()));
				}

				//TEST(const_iterator_class,"object")
				{
					json j(json::value_t::object);
					json::const_iterator it(&j);
					it.set_end();
					EXPECT_TRUE((it == j.cend()));
				}

				//TEST(const_iterator_class,"array")
				{
					json j(json::value_t::array);
					json::const_iterator it(&j);
					it.set_end();
					EXPECT_TRUE((it == j.cend()));
				}
			}
		}

		//TEST(const_iterator_class,"element access")
		{
			//TEST(const_iterator_class,"operator*")
			{
				//TEST(const_iterator_class,"null")
				{
					json j(json::value_t::null);
					json::const_iterator it = j.cbegin();
					EXPECT_THROW(*it, json::invalid_iterator);
					//CHECK_THROWS_WITH(*it, "[json.exception.invalid_iterator.214] cannot get value");
				}

				//TEST(const_iterator_class,"number")
				{
					json j(17);
					json::const_iterator it = j.cbegin();
					EXPECT_TRUE(*it == json(17));
					it = j.cend();
					EXPECT_THROW(*it, json::invalid_iterator);
					//CHECK_THROWS_WITH(*it, "[json.exception.invalid_iterator.214] cannot get value");
				}

				//TEST(const_iterator_class,"object")
				{
					json j({{"foo", "bar"}});
					json::const_iterator it = j.cbegin();
					EXPECT_TRUE(*it == json("bar"));
				}

				//TEST(const_iterator_class,"array")
				{
					json j({1, 2, 3, 4});
					json::const_iterator it = j.cbegin();
					EXPECT_TRUE(*it == json(1));
				}
			}

			//TEST(const_iterator_class,"operator->")
			{
				//TEST(const_iterator_class,"null")
				{
					json j(json::value_t::null);
					json::const_iterator it = j.cbegin();
					EXPECT_THROW(std::string(it->type_name()), json::invalid_iterator);
					//CHECK_THROWS_WITH(std::string(it->type_name()), "[json.exception.invalid_iterator.214] cannot get value");
				}

				//TEST(const_iterator_class,"number")
				{
					json j(17);
					json::const_iterator it = j.cbegin();
					EXPECT_TRUE(std::string(it->type_name()) == "number");
					it = j.cend();
					EXPECT_THROW(std::string(it->type_name()), json::invalid_iterator);
					//CHECK_THROWS_WITH(std::string(it->type_name()), "[json.exception.invalid_iterator.214] cannot get value");
				}

				//TEST(const_iterator_class,"object")
				{
					json j({{"foo", "bar"}});
					json::const_iterator it = j.cbegin();
					EXPECT_TRUE(std::string(it->type_name()) == "string");
				}

				//TEST(const_iterator_class,"array")
				{
					json j({1, 2, 3, 4});
					json::const_iterator it = j.cbegin();
					EXPECT_TRUE(std::string(it->type_name()) == "number");
				}
			}
		}
		//TEST(const_iterator_class,"increment/decrement")
		{
			//TEST(const_iterator_class,"post-increment")
			{
				//TEST(const_iterator_class,"null")
				{
					json j(json::value_t::null);
					json::const_iterator it = j.cbegin();
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 1));
					it++;
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it != 0 and it.m_it.primitive_iterator.m_it != 1));
				}

				//TEST(const_iterator_class,"number")
				{
					json j(17);
					json::const_iterator it = j.cbegin();
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 0));
					it++;
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 1));
					it++;
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it != 0 and it.m_it.primitive_iterator.m_it != 1));
				}

				//TEST(const_iterator_class,"object")
				{
					json j({{"foo", "bar"}});
					json::const_iterator it = j.cbegin();
					EXPECT_TRUE((it.m_it.object_iterator == it.m_object->m_value.object->begin()));
					it++;
					EXPECT_TRUE((it.m_it.object_iterator == it.m_object->m_value.object->end()));
				}

				//TEST(const_iterator_class,"array")
				{
					json j({1, 2, 3, 4});
					json::const_iterator it = j.cbegin();
					EXPECT_TRUE((it.m_it.array_iterator == it.m_object->m_value.array->begin()));
					it++;
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->begin()));
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->end()));
					it++;
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->begin()));
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->end()));
					it++;
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->begin()));
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->end()));
					it++;
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->begin()));
					EXPECT_TRUE((it.m_it.array_iterator == it.m_object->m_value.array->end()));
				}
			}

			//TEST(const_iterator_class,"pre-increment")
			{
				//TEST(const_iterator_class,"null")
				{
					json j(json::value_t::null);
					json::const_iterator it = j.cbegin();
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 1));
					++it;
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it != 0 and it.m_it.primitive_iterator.m_it != 1));
				}

				//TEST(const_iterator_class,"number")
				{
					json j(17);
					json::const_iterator it = j.cbegin();
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 0));
					++it;
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 1));
					++it;
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it != 0 and it.m_it.primitive_iterator.m_it != 1));
				}

				//TEST(const_iterator_class,"object")
				{
					json j({{"foo", "bar"}});
					json::const_iterator it = j.cbegin();
					EXPECT_TRUE((it.m_it.object_iterator == it.m_object->m_value.object->begin()));
					++it;
					EXPECT_TRUE((it.m_it.object_iterator == it.m_object->m_value.object->end()));
				}

				//TEST(const_iterator_class,"array")
				{
					json j({1, 2, 3, 4});
					json::const_iterator it = j.cbegin();
					EXPECT_TRUE((it.m_it.array_iterator == it.m_object->m_value.array->begin()));
					++it;
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->begin()));
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->end()));
					++it;
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->begin()));
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->end()));
					++it;
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->begin()));
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->end()));
					++it;
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->begin()));
					EXPECT_TRUE((it.m_it.array_iterator == it.m_object->m_value.array->end()));
				}
			}

			//TEST(const_iterator_class,"post-decrement")
			{
				//TEST(const_iterator_class,"null")
				{
					json j(json::value_t::null);
					json::const_iterator it = j.cend();
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 1));
				}

				//TEST(const_iterator_class,"number")
				{
					json j(17);
					json::const_iterator it = j.cend();
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 1));
					it--;
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 0));
					it--;
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it != 0 and it.m_it.primitive_iterator.m_it != 1));
				}

				//TEST(const_iterator_class,"object")
				{
					json j({{"foo", "bar"}});
					json::const_iterator it = j.cend();
					EXPECT_TRUE((it.m_it.object_iterator == it.m_object->m_value.object->end()));
					it--;
					EXPECT_TRUE((it.m_it.object_iterator == it.m_object->m_value.object->begin()));
				}

				//TEST(const_iterator_class,"array")
				{
					json j({1, 2, 3, 4});
					json::const_iterator it = j.cend();
					EXPECT_TRUE((it.m_it.array_iterator == it.m_object->m_value.array->end()));
					it--;
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->begin()));
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->end()));
					it--;
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->begin()));
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->end()));
					it--;
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->begin()));
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->end()));
					it--;
					EXPECT_TRUE((it.m_it.array_iterator == it.m_object->m_value.array->begin()));
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->end()));
				}
			}

			//TEST(const_iterator_class,"pre-decrement")
			{
				//TEST(const_iterator_class,"null")
				{
					json j(json::value_t::null);
					json::const_iterator it = j.cend();
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 1));
				}

				//TEST(const_iterator_class,"number")
				{
					json j(17);
					json::const_iterator it = j.cend();
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 1));
					--it;
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 0));
					--it;
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it != 0 and it.m_it.primitive_iterator.m_it != 1));
				}

				//TEST(const_iterator_class,"object")
				{
					json j({{"foo", "bar"}});
					json::const_iterator it = j.cend();
					EXPECT_TRUE((it.m_it.object_iterator == it.m_object->m_value.object->end()));
					--it;
					EXPECT_TRUE((it.m_it.object_iterator == it.m_object->m_value.object->begin()));
				}

				//TEST(const_iterator_class,"array")
				{
					json j({1, 2, 3, 4});
					json::const_iterator it = j.cend();
					EXPECT_TRUE((it.m_it.array_iterator == it.m_object->m_value.array->end()));
					--it;
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->begin()));
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->end()));
					--it;
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->begin()));
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->end()));
					--it;
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->begin()));
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->end()));
					--it;
					EXPECT_TRUE((it.m_it.array_iterator == it.m_object->m_value.array->begin()));
					EXPECT_TRUE((it.m_it.array_iterator != it.m_object->m_value.array->end()));
				}
			}
		}
	}
}
