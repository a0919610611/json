#include "gtest/gtest.h"
#define private public
#include "json.hpp"

using nlohmann::json;

namespace
{
	TEST(iterator_class, iterator_class_test)
	{
		//TEST(iterator_class,"construction")
		{
			//TEST(iterator_class,"constructor")
			{
				//TEST(iterator_class,"null")
				{
					json j(json::value_t::null);
					json::iterator it(&j);
				}

				//TEST(iterator_class,"object")
				{
					json j(json::value_t::object);
					json::iterator it(&j);
				}

				//TEST(iterator_class,"array")
				{
					json j(json::value_t::array);
					json::iterator it(&j);
				}
			}

			//TEST(iterator_class,"copy assignment")
			{
				json j(json::value_t::null);
				json::iterator it(&j);
				json::iterator it2(&j);
				it2 = it;
			}
		}

		//TEST(iterator_class,"initialization")
		{
			//TEST(iterator_class,"set_begin")
			{
				//TEST(iterator_class,"null")
				{
					json j(json::value_t::null);
					json::iterator it(&j);
					it.set_begin();
					EXPECT_TRUE((it == j.begin()));
				}

				//TEST(iterator_class,"object")
				{
					json j(json::value_t::object);
					json::iterator it(&j);
					it.set_begin();
					EXPECT_TRUE((it == j.begin()));
				}

				//TEST(iterator_class,"array")
				{
					json j(json::value_t::array);
					json::iterator it(&j);
					it.set_begin();
					EXPECT_TRUE((it == j.begin()));
				}
			}

			//TEST(iterator_class,"set_end")
			{
				//TEST(iterator_class,"null")
				{
					json j(json::value_t::null);
					json::iterator it(&j);
					it.set_end();
					EXPECT_TRUE((it == j.end()));
				}

				//TEST(iterator_class,"object")
				{
					json j(json::value_t::object);
					json::iterator it(&j);
					it.set_end();
					EXPECT_TRUE((it == j.end()));
				}

				//TEST(iterator_class,"array")
				{
					json j(json::value_t::array);
					json::iterator it(&j);
					it.set_end();
					EXPECT_TRUE((it == j.end()));
				}
			}
		}

		//TEST(iterator_class,"element access")
		{
			//TEST(iterator_class,"operator*")
			{
				//TEST(iterator_class,"null")
				{
					json j(json::value_t::null);
					json::iterator it = j.begin();
					EXPECT_THROW(*it, json::invalid_iterator);
					//CHECK_THROWS_WITH(*it, "[json.exception.invalid_iterator.214] cannot get value");
				}

				//TEST(iterator_class,"number")
				{
					json j(17);
					json::iterator it = j.begin();
					EXPECT_EQ(*it, json(17));
					it = j.end();
					EXPECT_THROW(*it, json::invalid_iterator);
					//CHECK_THROWS_WITH(*it, "[json.exception.invalid_iterator.214] cannot get value");
				}

				//TEST(iterator_class,"object")
				{
					json j({{"foo", "bar"}});
					json::iterator it = j.begin();
					EXPECT_EQ(*it, json("bar"));
				}

				//TEST(iterator_class,"array")
				{
					json j({1, 2, 3, 4});
					json::iterator it = j.begin();
					EXPECT_EQ(*it, json(1));
				}
			}

			//TEST(iterator_class,"operator->")
			{
				//TEST(iterator_class,"null")
				{
					json j(json::value_t::null);
					json::iterator it = j.begin();
					EXPECT_THROW(std::string(it->type_name()), json::invalid_iterator);
					//CHECK_THROWS_WITH(std::string(it->type_name()), "[json.exception.invalid_iterator.214] cannot get value");
				}

				//TEST(iterator_class,"number")
				{
					json j(17);
					json::iterator it = j.begin();
					EXPECT_EQ(std::string(it->type_name()), "number");
					it = j.end();
					EXPECT_THROW(std::string(it->type_name()), json::invalid_iterator);
					//CHECK_THROWS_WITH(std::string(it->type_name()), "[json.exception.invalid_iterator.214] cannot get value");
				}

				//TEST(iterator_class,"object")
				{
					json j({{"foo", "bar"}});
					json::iterator it = j.begin();
					EXPECT_EQ(std::string(it->type_name()), "string");
				}

				//TEST(iterator_class,"array")
				{
					json j({1, 2, 3, 4});
					json::iterator it = j.begin();
					EXPECT_EQ(std::string(it->type_name()), "number");
				}
			}
		}

		//TEST(iterator_class,"increment/decrement")
		{
			//TEST(iterator_class,"post-increment")
			{
				//TEST(iterator_class,"null")
				{
					json j(json::value_t::null);
					json::iterator it = j.begin();
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 1));
					it++;
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it != 0 and it.m_it.primitive_iterator.m_it != 1));
				}

				//TEST(iterator_class,"number")
				{
					json j(17);
					json::iterator it = j.begin();
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 0));
					it++;
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 1));
					it++;
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it != 0 and it.m_it.primitive_iterator.m_it != 1));
				}

				//TEST(iterator_class,"object")
				{
					json j({{"foo", "bar"}});
					json::iterator it = j.begin();
					EXPECT_TRUE((it.m_it.object_iterator == it.m_object->m_value.object->begin()));
					it++;
					EXPECT_TRUE((it.m_it.object_iterator == it.m_object->m_value.object->end()));
				}

				//TEST(iterator_class,"array")
				{
					json j({1, 2, 3, 4});
					json::iterator it = j.begin();
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

			//TEST(iterator_class,"pre-increment")
			{
				//TEST(iterator_class,"null")
				{
					json j(json::value_t::null);
					json::iterator it = j.begin();
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 1));
					++it;
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it != 0 and it.m_it.primitive_iterator.m_it != 1));
				}

				//TEST(iterator_class,"number")
				{
					json j(17);
					json::iterator it = j.begin();
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 0));
					++it;
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 1));
					++it;
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it != 0 and it.m_it.primitive_iterator.m_it != 1));
				}

				//TEST(iterator_class,"object")
				{
					json j({{"foo", "bar"}});
					json::iterator it = j.begin();
					EXPECT_TRUE((it.m_it.object_iterator == it.m_object->m_value.object->begin()));
					++it;
					EXPECT_TRUE((it.m_it.object_iterator == it.m_object->m_value.object->end()));
				}

				//TEST(iterator_class,"array")
				{
					json j({1, 2, 3, 4});
					json::iterator it = j.begin();
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

			//TEST(iterator_class,"post-decrement")
			{
				//TEST(iterator_class,"null")
				{
					json j(json::value_t::null);
					json::iterator it = j.end();
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 1));
				}

				//TEST(iterator_class,"number")
				{
					json j(17);
					json::iterator it = j.end();
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 1));
					it--;
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 0));
					it--;
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it != 0 and it.m_it.primitive_iterator.m_it != 1));
				}

				//TEST(iterator_class,"object")
				{
					json j({{"foo", "bar"}});
					json::iterator it = j.end();
					EXPECT_TRUE((it.m_it.object_iterator == it.m_object->m_value.object->end()));
					it--;
					EXPECT_TRUE((it.m_it.object_iterator == it.m_object->m_value.object->begin()));
				}

				//TEST(iterator_class,"array")
				{
					json j({1, 2, 3, 4});
					json::iterator it = j.end();
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

			//TEST(iterator_class,"pre-decrement")
			{
				//TEST(iterator_class,"null")
				{
					json j(json::value_t::null);
					json::iterator it = j.end();
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 1));
				}

				//TEST(iterator_class,"number")
				{
					json j(17);
					json::iterator it = j.end();
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 1));
					--it;
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it == 0));
					--it;
					EXPECT_TRUE((it.m_it.primitive_iterator.m_it != 0 and it.m_it.primitive_iterator.m_it != 1));
				}

				//TEST(iterator_class,"object")
				{
					json j({{"foo", "bar"}});
					json::iterator it = j.end();
					EXPECT_TRUE((it.m_it.object_iterator == it.m_object->m_value.object->end()));
					--it;
					EXPECT_TRUE((it.m_it.object_iterator == it.m_object->m_value.object->begin()));
				}

				//TEST(iterator_class,"array")
				{
					json j({1, 2, 3, 4});
					json::iterator it = j.end();
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
