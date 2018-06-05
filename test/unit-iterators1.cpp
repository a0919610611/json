#include "gtest/gtest.h"
#define private public
#include "json.hpp"
using nlohmann::json;

namespace
{
	TEST(iterators1, iterators1)
	{
		//TEST(constructors,"basic behavior")
		{
			//TEST(constructors,"uninitialized")
			{
				json::iterator it;
				EXPECT_TRUE(it.m_object == nullptr);

				json::const_iterator cit;
				EXPECT_TRUE(cit.m_object == nullptr);
			}

			//TEST(constructors,"boolean")
			{
				json j = true;
				json j_const(j);

				//TEST(constructors,"json + begin/end")
				{
					json::iterator it = j.begin();
					EXPECT_TRUE(it != j.end());
					EXPECT_TRUE(*it == j);

					it++;
					EXPECT_TRUE(it != j.begin());
					EXPECT_TRUE(it == j.end());

					it--;
					EXPECT_TRUE(it == j.begin());
					EXPECT_TRUE(it != j.end());
					EXPECT_TRUE(*it == j);

					++it;
					EXPECT_TRUE(it != j.begin());
					EXPECT_TRUE(it == j.end());

					--it;
					EXPECT_TRUE(it == j.begin());
					EXPECT_TRUE(it != j.end());
					EXPECT_TRUE(*it == j);
				}

				//TEST(constructors,"const json + begin/end")
				{
					json::const_iterator it = j_const.begin();
					EXPECT_TRUE(it != j_const.end());
					EXPECT_TRUE(*it == j_const);

					it++;
					EXPECT_TRUE(it != j_const.begin());
					EXPECT_TRUE(it == j_const.end());

					it--;
					EXPECT_TRUE(it == j_const.begin());
					EXPECT_TRUE(it != j_const.end());
					EXPECT_TRUE(*it == j_const);

					++it;
					EXPECT_TRUE(it != j_const.begin());
					EXPECT_TRUE(it == j_const.end());

					--it;
					EXPECT_TRUE(it == j_const.begin());
					EXPECT_TRUE(it != j_const.end());
					EXPECT_TRUE(*it == j_const);
				}

				//TEST(constructors,"json + cbegin/cend")
				{
					json::const_iterator it = j.cbegin();
					EXPECT_TRUE(it != j.cend());
					EXPECT_TRUE(*it == j);

					it++;
					EXPECT_TRUE(it != j.cbegin());
					EXPECT_TRUE(it == j.cend());

					it--;
					EXPECT_TRUE(it == j.cbegin());
					EXPECT_TRUE(it != j.cend());
					EXPECT_TRUE(*it == j);

					++it;
					EXPECT_TRUE(it != j.cbegin());
					EXPECT_TRUE(it == j.cend());

					--it;
					EXPECT_TRUE(it == j.cbegin());
					EXPECT_TRUE(it != j.cend());
					EXPECT_TRUE(*it == j);
				}

				//TEST(constructors,"const json + cbegin/cend")
				{
					json::const_iterator it = j_const.cbegin();
					EXPECT_TRUE(it != j_const.cend());
					EXPECT_TRUE(*it == j_const);

					it++;
					EXPECT_TRUE(it != j_const.cbegin());
					EXPECT_TRUE(it == j_const.cend());

					it--;
					EXPECT_TRUE(it == j_const.cbegin());
					EXPECT_TRUE(it != j_const.cend());
					EXPECT_TRUE(*it == j_const);

					++it;
					EXPECT_TRUE(it != j_const.cbegin());
					EXPECT_TRUE(it == j_const.cend());

					--it;
					EXPECT_TRUE(it == j_const.cbegin());
					EXPECT_TRUE(it != j_const.cend());
					EXPECT_TRUE(*it == j_const);
				}

				//TEST(constructors,"json + rbegin/rend")
				{
					json::reverse_iterator it = j.rbegin();
					EXPECT_TRUE(it != j.rend());
					EXPECT_TRUE(*it == j);

					it++;
					EXPECT_TRUE(it != j.rbegin());
					EXPECT_TRUE(it == j.rend());

					it--;
					EXPECT_TRUE(it == j.rbegin());
					EXPECT_TRUE(it != j.rend());
					EXPECT_TRUE(*it == j);

					++it;
					EXPECT_TRUE(it != j.rbegin());
					EXPECT_TRUE(it == j.rend());

					--it;
					EXPECT_TRUE(it == j.rbegin());
					EXPECT_TRUE(it != j.rend());
					EXPECT_TRUE(*it == j);
				}

				//TEST(constructors,"json + crbegin/crend")
				{
					json::const_reverse_iterator it = j.crbegin();
					EXPECT_TRUE(it != j.crend());
					EXPECT_TRUE(*it == j);

					it++;
					EXPECT_TRUE(it != j.crbegin());
					EXPECT_TRUE(it == j.crend());

					it--;
					EXPECT_TRUE(it == j.crbegin());
					EXPECT_TRUE(it != j.crend());
					EXPECT_TRUE(*it == j);

					++it;
					EXPECT_TRUE(it != j.crbegin());
					EXPECT_TRUE(it == j.crend());

					--it;
					EXPECT_TRUE(it == j.crbegin());
					EXPECT_TRUE(it != j.crend());
					EXPECT_TRUE(*it == j);
				}

				//TEST(constructors,"const json + crbegin/crend")
				{
					json::const_reverse_iterator it = j_const.crbegin();
					EXPECT_TRUE(it != j_const.crend());
					EXPECT_TRUE(*it == j_const);

					it++;
					EXPECT_TRUE(it != j_const.crbegin());
					EXPECT_TRUE(it == j_const.crend());

					it--;
					EXPECT_TRUE(it == j_const.crbegin());
					EXPECT_TRUE(it != j_const.crend());
					EXPECT_TRUE(*it == j_const);

					++it;
					EXPECT_TRUE(it != j_const.crbegin());
					EXPECT_TRUE(it == j_const.crend());

					--it;
					EXPECT_TRUE(it == j_const.crbegin());
					EXPECT_TRUE(it != j_const.crend());
					EXPECT_TRUE(*it == j_const);
				}

				//TEST(constructors,"additional tests")
				{
					//TEST(constructors,"!(begin != begin)")
					{
						EXPECT_TRUE(not(j.begin() != j.begin()));
					}

					//TEST(constructors,"!(end != end)")
					{
						EXPECT_TRUE(not(j.end() != j.end()));
					}

					//TEST(constructors,"begin < end")
					{
						EXPECT_TRUE(j.begin() < j.end());
					}

					//TEST(constructors,"begin <= end")
					{
						EXPECT_TRUE(j.begin() <= j.end());
					}

					//TEST(constructors,"end > begin")
					{
						EXPECT_TRUE(j.end() > j.begin());
					}

					//TEST(constructors,"end >= begin")
					{
						EXPECT_TRUE(j.end() >= j.begin());
					}

					//TEST(constructors,"end == end")
					{
						EXPECT_TRUE(j.end() == j.end());
					}

					//TEST(constructors,"end <= end")
					{
						EXPECT_TRUE(j.end() <= j.end());
					}

					//TEST(constructors,"begin == begin")
					{
						EXPECT_TRUE(j.begin() == j.begin());
					}

					//TEST(constructors,"begin <= begin")
					{
						EXPECT_TRUE(j.begin() <= j.begin());
					}

					//TEST(constructors,"begin >= begin")
					{
						EXPECT_TRUE(j.begin() >= j.begin());
					}

					//TEST(constructors,"!(begin == end)")
					{
						EXPECT_TRUE(not(j.begin() == j.end()));
					}

					//TEST(constructors,"begin != end")
					{
						EXPECT_TRUE(j.begin() != j.end());
					}

					//TEST(constructors,"begin+1 == end")
					{
						EXPECT_TRUE(j.begin() + 1 == j.end());
					}

					//TEST(constructors,"begin == end-1")
					{
						EXPECT_TRUE(j.begin() == j.end() - 1);
					}

					//TEST(constructors,"begin != end+1")
					{
						EXPECT_TRUE(j.begin() != j.end() + 1);
					}

					//TEST(constructors,"end != end+1")
					{
						EXPECT_TRUE(j.end() != j.end() + 1);
					}

					//TEST(constructors,"begin+1 != begin+2")
					{
						EXPECT_TRUE(j.begin() + 1 != j.begin() + 2);
					}

					//TEST(constructors,"begin+1 < begin+2")
					{
						EXPECT_TRUE(j.begin() + 1 < j.begin() + 2);
					}

					//TEST(constructors,"begin+1 <= begin+2")
					{
						EXPECT_TRUE(j.begin() + 1 <= j.begin() + 2);
					}

					//TEST(constructors,"end+1 != end+2")
					{
						EXPECT_TRUE(j.end() + 1 != j.end() + 2);
					}
				}

				//TEST(constructors,"key/value")
				{
					auto it = j.begin();
					auto cit = j_const.cbegin();
					EXPECT_THROW(it.key(), json::invalid_iterator);
					//CHECK_THROWS_WITH(it.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					EXPECT_TRUE(it.value() == json(true));
					EXPECT_THROW(cit.key(), json::invalid_iterator);
					//CHECK_THROWS_WITH(cit.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					EXPECT_TRUE(cit.value() == json(true));

					auto rit = j.rend();
					auto crit = j.crend();
					EXPECT_THROW(rit.key(), json::invalid_iterator);
					EXPECT_THROW(rit.value(), json::invalid_iterator);
					EXPECT_THROW(crit.key(), json::invalid_iterator);
					EXPECT_THROW(crit.value(), json::invalid_iterator);
					//CHECK_THROWS_WITH(rit.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					//CHECK_THROWS_WITH(rit.value(), "[json.exception.invalid_iterator.214] cannot get value");
					//CHECK_THROWS_WITH(crit.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					//CHECK_THROWS_WITH(crit.value(), "[json.exception.invalid_iterator.214] cannot get value");
				}
			}

			//TEST(constructors,"string")
			{
				json j = "hello world";
				json j_const(j);

				//TEST(constructors,"json + begin/end")
				{
					json::iterator it = j.begin();
					EXPECT_TRUE(it != j.end());
					EXPECT_TRUE(*it == j);

					it++;
					EXPECT_TRUE(it != j.begin());
					EXPECT_TRUE(it == j.end());

					it--;
					EXPECT_TRUE(it == j.begin());
					EXPECT_TRUE(it != j.end());
					EXPECT_TRUE(*it == j);

					++it;
					EXPECT_TRUE(it != j.begin());
					EXPECT_TRUE(it == j.end());

					--it;
					EXPECT_TRUE(it == j.begin());
					EXPECT_TRUE(it != j.end());
					EXPECT_TRUE(*it == j);
				}

				//TEST(constructors,"const json + begin/end")
				{
					json::const_iterator it = j_const.begin();
					EXPECT_TRUE(it != j_const.end());
					EXPECT_TRUE(*it == j_const);

					it++;
					EXPECT_TRUE(it != j_const.begin());
					EXPECT_TRUE(it == j_const.end());

					it--;
					EXPECT_TRUE(it == j_const.begin());
					EXPECT_TRUE(it != j_const.end());
					EXPECT_TRUE(*it == j_const);

					++it;
					EXPECT_TRUE(it != j_const.begin());
					EXPECT_TRUE(it == j_const.end());

					--it;
					EXPECT_TRUE(it == j_const.begin());
					EXPECT_TRUE(it != j_const.end());
					EXPECT_TRUE(*it == j_const);
				}

				//TEST(constructors,"json + cbegin/cend")
				{
					json::const_iterator it = j.cbegin();
					EXPECT_TRUE(it != j.cend());
					EXPECT_TRUE(*it == j);

					it++;
					EXPECT_TRUE(it != j.cbegin());
					EXPECT_TRUE(it == j.cend());

					it--;
					EXPECT_TRUE(it == j.cbegin());
					EXPECT_TRUE(it != j.cend());
					EXPECT_TRUE(*it == j);

					++it;
					EXPECT_TRUE(it != j.cbegin());
					EXPECT_TRUE(it == j.cend());

					--it;
					EXPECT_TRUE(it == j.cbegin());
					EXPECT_TRUE(it != j.cend());
					EXPECT_TRUE(*it == j);
				}

				//TEST(constructors,"const json + cbegin/cend")
				{
					json::const_iterator it = j_const.cbegin();
					EXPECT_TRUE(it != j_const.cend());
					EXPECT_TRUE(*it == j_const);

					it++;
					EXPECT_TRUE(it != j_const.cbegin());
					EXPECT_TRUE(it == j_const.cend());

					it--;
					EXPECT_TRUE(it == j_const.cbegin());
					EXPECT_TRUE(it != j_const.cend());
					EXPECT_TRUE(*it == j_const);

					++it;
					EXPECT_TRUE(it != j_const.cbegin());
					EXPECT_TRUE(it == j_const.cend());

					--it;
					EXPECT_TRUE(it == j_const.cbegin());
					EXPECT_TRUE(it != j_const.cend());
					EXPECT_TRUE(*it == j_const);
				}

				//TEST(constructors,"json + rbegin/rend")
				{
					json::reverse_iterator it = j.rbegin();
					EXPECT_TRUE(it != j.rend());
					EXPECT_TRUE(*it == j);

					it++;
					EXPECT_TRUE(it != j.rbegin());
					EXPECT_TRUE(it == j.rend());

					it--;
					EXPECT_TRUE(it == j.rbegin());
					EXPECT_TRUE(it != j.rend());
					EXPECT_TRUE(*it == j);

					++it;
					EXPECT_TRUE(it != j.rbegin());
					EXPECT_TRUE(it == j.rend());

					--it;
					EXPECT_TRUE(it == j.rbegin());
					EXPECT_TRUE(it != j.rend());
					EXPECT_TRUE(*it == j);
				}

				//TEST(constructors,"json + crbegin/crend")
				{
					json::const_reverse_iterator it = j.crbegin();
					EXPECT_TRUE(it != j.crend());
					EXPECT_TRUE(*it == j);

					it++;
					EXPECT_TRUE(it != j.crbegin());
					EXPECT_TRUE(it == j.crend());

					it--;
					EXPECT_TRUE(it == j.crbegin());
					EXPECT_TRUE(it != j.crend());
					EXPECT_TRUE(*it == j);

					++it;
					EXPECT_TRUE(it != j.crbegin());
					EXPECT_TRUE(it == j.crend());

					--it;
					EXPECT_TRUE(it == j.crbegin());
					EXPECT_TRUE(it != j.crend());
					EXPECT_TRUE(*it == j);
				}

				//TEST(constructors,"const json + crbegin/crend")
				{
					json::const_reverse_iterator it = j_const.crbegin();
					EXPECT_TRUE(it != j_const.crend());
					EXPECT_TRUE(*it == j_const);

					it++;
					EXPECT_TRUE(it != j_const.crbegin());
					EXPECT_TRUE(it == j_const.crend());

					it--;
					EXPECT_TRUE(it == j_const.crbegin());
					EXPECT_TRUE(it != j_const.crend());
					EXPECT_TRUE(*it == j_const);

					++it;
					EXPECT_TRUE(it != j_const.crbegin());
					EXPECT_TRUE(it == j_const.crend());

					--it;
					EXPECT_TRUE(it == j_const.crbegin());
					EXPECT_TRUE(it != j_const.crend());
					EXPECT_TRUE(*it == j_const);
				}

				//TEST(constructors,"key/value")
				{
					auto it = j.begin();
					auto cit = j_const.cbegin();
					EXPECT_THROW(it.key(), json::invalid_iterator);
					//CHECK_THROWS_WITH(it.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					EXPECT_TRUE(it.value() == json("hello world"));
					EXPECT_THROW(cit.key(), json::invalid_iterator);
					//CHECK_THROWS_WITH(cit.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					EXPECT_TRUE(cit.value() == json("hello world"));

					auto rit = j.rend();
					auto crit = j.crend();
					EXPECT_THROW(rit.key(), json::invalid_iterator);
					EXPECT_THROW(rit.value(), json::invalid_iterator);
					EXPECT_THROW(crit.key(), json::invalid_iterator);
					EXPECT_THROW(crit.value(), json::invalid_iterator);
					//CHECK_THROWS_WITH(rit.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					//CHECK_THROWS_WITH(rit.value(), "[json.exception.invalid_iterator.214] cannot get value");
					//CHECK_THROWS_WITH(crit.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					//CHECK_THROWS_WITH(crit.value(), "[json.exception.invalid_iterator.214] cannot get value");
				}
			}

			//TEST(constructors,"array")
			{
				json j = {1, 2, 3};
				json j_const(j);

				//TEST(constructors,"json + begin/end")
				{
					json::iterator it_begin = j.begin();
					json::iterator it_end = j.end();

					auto it = it_begin;
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j[0]);

					it++;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j[1]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j[2]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it == it_end);
				}

				//TEST(constructors,"const json + begin/end")
				{
					json::const_iterator it_begin = j_const.begin();
					json::const_iterator it_end = j_const.end();

					auto it = it_begin;
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j_const[0]);

					it++;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j_const[1]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j_const[2]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it == it_end);
				}

				//TEST(constructors,"json + cbegin/cend")
				{
					json::const_iterator it_begin = j.cbegin();
					json::const_iterator it_end = j.cend();

					auto it = it_begin;
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j[0]);

					it++;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j[1]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j[2]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it == it_end);
				}

				//TEST(constructors,"const json + cbegin/cend")
				{
					json::const_iterator it_begin = j_const.cbegin();
					json::const_iterator it_end = j_const.cend();

					auto it = it_begin;
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j[0]);

					it++;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j[1]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j[2]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it == it_end);
				}

				//TEST(constructors,"json + rbegin/rend")
				{
					json::reverse_iterator it_begin = j.rbegin();
					json::reverse_iterator it_end = j.rend();

					auto it = it_begin;
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j[2]);

					it++;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j[1]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j[0]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it == it_end);
				}

				//TEST(constructors,"json + crbegin/crend")
				{
					json::const_reverse_iterator it_begin = j.crbegin();
					json::const_reverse_iterator it_end = j.crend();

					auto it = it_begin;
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j[2]);

					it++;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j[1]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j[0]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it == it_end);
				}

				//TEST(constructors,"const json + crbegin/crend")
				{
					json::const_reverse_iterator it_begin = j_const.crbegin();
					json::const_reverse_iterator it_end = j_const.crend();

					auto it = it_begin;
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j[2]);

					it++;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j[1]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j[0]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it == it_end);
				}

				//TEST(constructors,"key/value")
				{
					auto it = j.begin();
					auto cit = j_const.cbegin();
					EXPECT_THROW(it.key(), json::invalid_iterator);
					//CHECK_THROWS_WITH(it.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					EXPECT_TRUE(it.value() == json(1));
					EXPECT_THROW(cit.key(), json::invalid_iterator);
					//CHECK_THROWS_WITH(cit.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					EXPECT_TRUE(cit.value() == json(1));
				}
			}

			//TEST(constructors,"object")
			{
				json j = {{"A", 1}, {"B", 2}, {"C", 3}};
				json j_const(j);

				//TEST(constructors,"json + begin/end")
				{
					json::iterator it_begin = j.begin();
					json::iterator it_end = j.end();

					auto it = it_begin;
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j["A"]);

					it++;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j["B"]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j["C"]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it == it_end);
				}

				//TEST(constructors,"const json + begin/end")
				{
					json::const_iterator it_begin = j_const.begin();
					json::const_iterator it_end = j_const.end();

					auto it = it_begin;
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j_const["A"]);

					it++;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j_const["B"]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j_const["C"]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it == it_end);
				}

				//TEST(constructors,"json + cbegin/cend")
				{
					json::const_iterator it_begin = j.cbegin();
					json::const_iterator it_end = j.cend();

					auto it = it_begin;
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j["A"]);

					it++;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j["B"]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j["C"]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it == it_end);
				}

				//TEST(constructors,"const json + cbegin/cend")
				{
					json::const_iterator it_begin = j_const.cbegin();
					json::const_iterator it_end = j_const.cend();

					auto it = it_begin;
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j_const["A"]);

					it++;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j_const["B"]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j_const["C"]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it == it_end);
				}

				//TEST(constructors,"json + rbegin/rend")
				{
					json::reverse_iterator it_begin = j.rbegin();
					json::reverse_iterator it_end = j.rend();

					auto it = it_begin;
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j["C"]);

					it++;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j["B"]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j["A"]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it == it_end);
				}

				//TEST(constructors,"json + crbegin/crend")
				{
					json::const_reverse_iterator it_begin = j.crbegin();
					json::const_reverse_iterator it_end = j.crend();

					auto it = it_begin;
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j["C"]);

					it++;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j["B"]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j["A"]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it == it_end);
				}

				//TEST(constructors,"const json + crbegin/crend")
				{
					json::const_reverse_iterator it_begin = j_const.crbegin();
					json::const_reverse_iterator it_end = j_const.crend();

					auto it = it_begin;
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j["C"]);

					it++;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j["B"]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it != it_end);
					EXPECT_TRUE(*it == j["A"]);

					++it;
					EXPECT_TRUE(it != it_begin);
					EXPECT_TRUE(it == it_end);
				}

				//TEST(constructors,"key/value")
				{
					auto it = j.begin();
					auto cit = j_const.cbegin();
					EXPECT_TRUE(it.key() == "A");
					EXPECT_TRUE(it.value() == json(1));
					EXPECT_TRUE(cit.key() == "A");
					EXPECT_TRUE(cit.value() == json(1));
				}
			}

			//TEST(constructors,"number (integer)")
			{
				json j = 23;
				json j_const(j);

				//TEST(constructors,"json + begin/end")
				{
					json::iterator it = j.begin();
					EXPECT_TRUE(it != j.end());
					EXPECT_TRUE(*it == j);

					it++;
					EXPECT_TRUE(it != j.begin());
					EXPECT_TRUE(it == j.end());

					it--;
					EXPECT_TRUE(it == j.begin());
					EXPECT_TRUE(it != j.end());
					EXPECT_TRUE(*it == j);

					++it;
					EXPECT_TRUE(it != j.begin());
					EXPECT_TRUE(it == j.end());

					--it;
					EXPECT_TRUE(it == j.begin());
					EXPECT_TRUE(it != j.end());
					EXPECT_TRUE(*it == j);
				}

				//TEST(constructors,"const json + begin/end")
				{
					json::const_iterator it = j_const.begin();
					EXPECT_TRUE(it != j_const.end());
					EXPECT_TRUE(*it == j_const);

					it++;
					EXPECT_TRUE(it != j_const.begin());
					EXPECT_TRUE(it == j_const.end());

					it--;
					EXPECT_TRUE(it == j_const.begin());
					EXPECT_TRUE(it != j_const.end());
					EXPECT_TRUE(*it == j_const);

					++it;
					EXPECT_TRUE(it != j_const.begin());
					EXPECT_TRUE(it == j_const.end());

					--it;
					EXPECT_TRUE(it == j_const.begin());
					EXPECT_TRUE(it != j_const.end());
					EXPECT_TRUE(*it == j_const);
				}

				//TEST(constructors,"json + cbegin/cend")
				{
					json::const_iterator it = j.cbegin();
					EXPECT_TRUE(it != j.cend());
					EXPECT_TRUE(*it == j);

					it++;
					EXPECT_TRUE(it != j.cbegin());
					EXPECT_TRUE(it == j.cend());

					it--;
					EXPECT_TRUE(it == j.cbegin());
					EXPECT_TRUE(it != j.cend());
					EXPECT_TRUE(*it == j);

					++it;
					EXPECT_TRUE(it != j.cbegin());
					EXPECT_TRUE(it == j.cend());

					--it;
					EXPECT_TRUE(it == j.cbegin());
					EXPECT_TRUE(it != j.cend());
					EXPECT_TRUE(*it == j);
				}

				//TEST(constructors,"const json + cbegin/cend")
				{
					json::const_iterator it = j_const.cbegin();
					EXPECT_TRUE(it != j_const.cend());
					EXPECT_TRUE(*it == j_const);

					it++;
					EXPECT_TRUE(it != j_const.cbegin());
					EXPECT_TRUE(it == j_const.cend());

					it--;
					EXPECT_TRUE(it == j_const.cbegin());
					EXPECT_TRUE(it != j_const.cend());
					EXPECT_TRUE(*it == j_const);

					++it;
					EXPECT_TRUE(it != j_const.cbegin());
					EXPECT_TRUE(it == j_const.cend());

					--it;
					EXPECT_TRUE(it == j_const.cbegin());
					EXPECT_TRUE(it != j_const.cend());
					EXPECT_TRUE(*it == j_const);
				}

				//TEST(constructors,"json + rbegin/rend")
				{
					json::reverse_iterator it = j.rbegin();
					EXPECT_TRUE(it != j.rend());
					EXPECT_TRUE(*it == j);

					it++;
					EXPECT_TRUE(it != j.rbegin());
					EXPECT_TRUE(it == j.rend());

					it--;
					EXPECT_TRUE(it == j.rbegin());
					EXPECT_TRUE(it != j.rend());
					EXPECT_TRUE(*it == j);

					++it;
					EXPECT_TRUE(it != j.rbegin());
					EXPECT_TRUE(it == j.rend());

					--it;
					EXPECT_TRUE(it == j.rbegin());
					EXPECT_TRUE(it != j.rend());
					EXPECT_TRUE(*it == j);
				}

				//TEST(constructors,"json + crbegin/crend")
				{
					json::const_reverse_iterator it = j.crbegin();
					EXPECT_TRUE(it != j.crend());
					EXPECT_TRUE(*it == j);

					it++;
					EXPECT_TRUE(it != j.crbegin());
					EXPECT_TRUE(it == j.crend());

					it--;
					EXPECT_TRUE(it == j.crbegin());
					EXPECT_TRUE(it != j.crend());
					EXPECT_TRUE(*it == j);

					++it;
					EXPECT_TRUE(it != j.crbegin());
					EXPECT_TRUE(it == j.crend());

					--it;
					EXPECT_TRUE(it == j.crbegin());
					EXPECT_TRUE(it != j.crend());
					EXPECT_TRUE(*it == j);
				}

				//TEST(constructors,"const json + crbegin/crend")
				{
					json::const_reverse_iterator it = j_const.crbegin();
					EXPECT_TRUE(it != j_const.crend());
					EXPECT_TRUE(*it == j_const);

					it++;
					EXPECT_TRUE(it != j_const.crbegin());
					EXPECT_TRUE(it == j_const.crend());

					it--;
					EXPECT_TRUE(it == j_const.crbegin());
					EXPECT_TRUE(it != j_const.crend());
					EXPECT_TRUE(*it == j_const);

					++it;
					EXPECT_TRUE(it != j_const.crbegin());
					EXPECT_TRUE(it == j_const.crend());

					--it;
					EXPECT_TRUE(it == j_const.crbegin());
					EXPECT_TRUE(it != j_const.crend());
					EXPECT_TRUE(*it == j_const);
				}

				//TEST(constructors,"key/value")
				{
					auto it = j.begin();
					auto cit = j_const.cbegin();
					EXPECT_THROW(it.key(), json::invalid_iterator);
					//CHECK_THROWS_WITH(it.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					EXPECT_TRUE(it.value() == json(23));
					EXPECT_THROW(cit.key(), json::invalid_iterator);
					//CHECK_THROWS_WITH(cit.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					EXPECT_TRUE(cit.value() == json(23));

					auto rit = j.rend();
					auto crit = j.crend();
					EXPECT_THROW(rit.key(), json::invalid_iterator);
					EXPECT_THROW(rit.value(), json::invalid_iterator);
					EXPECT_THROW(crit.key(), json::invalid_iterator);
					EXPECT_THROW(crit.value(), json::invalid_iterator);
					//CHECK_THROWS_WITH(rit.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					//CHECK_THROWS_WITH(rit.value(), "[json.exception.invalid_iterator.214] cannot get value");
					//CHECK_THROWS_WITH(crit.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					//CHECK_THROWS_WITH(crit.value(), "[json.exception.invalid_iterator.214] cannot get value");
				}
			}

			//TEST(constructors,"number (unsigned)")
			{
				json j = 23u;
				json j_const(j);

				//TEST(constructors,"json + begin/end")
				{
					json::iterator it = j.begin();
					EXPECT_TRUE(it != j.end());
					EXPECT_TRUE(*it == j);

					it++;
					EXPECT_TRUE(it != j.begin());
					EXPECT_TRUE(it == j.end());

					it--;
					EXPECT_TRUE(it == j.begin());
					EXPECT_TRUE(it != j.end());
					EXPECT_TRUE(*it == j);

					++it;
					EXPECT_TRUE(it != j.begin());
					EXPECT_TRUE(it == j.end());

					--it;
					EXPECT_TRUE(it == j.begin());
					EXPECT_TRUE(it != j.end());
					EXPECT_TRUE(*it == j);
				}

				//TEST(constructors,"const json + begin/end")
				{
					json::const_iterator it = j_const.begin();
					EXPECT_TRUE(it != j_const.end());
					EXPECT_TRUE(*it == j_const);

					it++;
					EXPECT_TRUE(it != j_const.begin());
					EXPECT_TRUE(it == j_const.end());

					it--;
					EXPECT_TRUE(it == j_const.begin());
					EXPECT_TRUE(it != j_const.end());
					EXPECT_TRUE(*it == j_const);

					++it;
					EXPECT_TRUE(it != j_const.begin());
					EXPECT_TRUE(it == j_const.end());

					--it;
					EXPECT_TRUE(it == j_const.begin());
					EXPECT_TRUE(it != j_const.end());
					EXPECT_TRUE(*it == j_const);
				}

				//TEST(constructors,"json + cbegin/cend")
				{
					json::const_iterator it = j.cbegin();
					EXPECT_TRUE(it != j.cend());
					EXPECT_TRUE(*it == j);

					it++;
					EXPECT_TRUE(it != j.cbegin());
					EXPECT_TRUE(it == j.cend());

					it--;
					EXPECT_TRUE(it == j.cbegin());
					EXPECT_TRUE(it != j.cend());
					EXPECT_TRUE(*it == j);

					++it;
					EXPECT_TRUE(it != j.cbegin());
					EXPECT_TRUE(it == j.cend());

					--it;
					EXPECT_TRUE(it == j.cbegin());
					EXPECT_TRUE(it != j.cend());
					EXPECT_TRUE(*it == j);
				}

				//TEST(constructors,"const json + cbegin/cend")
				{
					json::const_iterator it = j_const.cbegin();
					EXPECT_TRUE(it != j_const.cend());
					EXPECT_TRUE(*it == j_const);

					it++;
					EXPECT_TRUE(it != j_const.cbegin());
					EXPECT_TRUE(it == j_const.cend());

					it--;
					EXPECT_TRUE(it == j_const.cbegin());
					EXPECT_TRUE(it != j_const.cend());
					EXPECT_TRUE(*it == j_const);

					++it;
					EXPECT_TRUE(it != j_const.cbegin());
					EXPECT_TRUE(it == j_const.cend());

					--it;
					EXPECT_TRUE(it == j_const.cbegin());
					EXPECT_TRUE(it != j_const.cend());
					EXPECT_TRUE(*it == j_const);
				}

				//TEST(constructors,"json + rbegin/rend")
				{
					json::reverse_iterator it = j.rbegin();
					EXPECT_TRUE(it != j.rend());
					EXPECT_TRUE(*it == j);

					it++;
					EXPECT_TRUE(it != j.rbegin());
					EXPECT_TRUE(it == j.rend());

					it--;
					EXPECT_TRUE(it == j.rbegin());
					EXPECT_TRUE(it != j.rend());
					EXPECT_TRUE(*it == j);

					++it;
					EXPECT_TRUE(it != j.rbegin());
					EXPECT_TRUE(it == j.rend());

					--it;
					EXPECT_TRUE(it == j.rbegin());
					EXPECT_TRUE(it != j.rend());
					EXPECT_TRUE(*it == j);
				}

				//TEST(constructors,"json + crbegin/crend")
				{
					json::const_reverse_iterator it = j.crbegin();
					EXPECT_TRUE(it != j.crend());
					EXPECT_TRUE(*it == j);

					it++;
					EXPECT_TRUE(it != j.crbegin());
					EXPECT_TRUE(it == j.crend());

					it--;
					EXPECT_TRUE(it == j.crbegin());
					EXPECT_TRUE(it != j.crend());
					EXPECT_TRUE(*it == j);

					++it;
					EXPECT_TRUE(it != j.crbegin());
					EXPECT_TRUE(it == j.crend());

					--it;
					EXPECT_TRUE(it == j.crbegin());
					EXPECT_TRUE(it != j.crend());
					EXPECT_TRUE(*it == j);
				}

				//TEST(constructors,"const json + crbegin/crend")
				{
					json::const_reverse_iterator it = j_const.crbegin();
					EXPECT_TRUE(it != j_const.crend());
					EXPECT_TRUE(*it == j_const);

					it++;
					EXPECT_TRUE(it != j_const.crbegin());
					EXPECT_TRUE(it == j_const.crend());

					it--;
					EXPECT_TRUE(it == j_const.crbegin());
					EXPECT_TRUE(it != j_const.crend());
					EXPECT_TRUE(*it == j_const);

					++it;
					EXPECT_TRUE(it != j_const.crbegin());
					EXPECT_TRUE(it == j_const.crend());

					--it;
					EXPECT_TRUE(it == j_const.crbegin());
					EXPECT_TRUE(it != j_const.crend());
					EXPECT_TRUE(*it == j_const);
				}

				//TEST(constructors,"key/value")
				{
					auto it = j.begin();
					auto cit = j_const.cbegin();
					EXPECT_THROW(it.key(), json::invalid_iterator);
					//CHECK_THROWS_WITH(it.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					EXPECT_TRUE(it.value() == json(23));
					EXPECT_THROW(cit.key(), json::invalid_iterator);
					//CHECK_THROWS_WITH(cit.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					EXPECT_TRUE(cit.value() == json(23));

					auto rit = j.rend();
					auto crit = j.crend();
					EXPECT_THROW(rit.key(), json::invalid_iterator);
					EXPECT_THROW(rit.value(), json::invalid_iterator);
					EXPECT_THROW(crit.key(), json::invalid_iterator);
					EXPECT_THROW(crit.value(), json::invalid_iterator);
					//CHECK_THROWS_WITH(rit.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					//CHECK_THROWS_WITH(rit.value(), "[json.exception.invalid_iterator.214] cannot get value");
					//CHECK_THROWS_WITH(crit.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					//CHECK_THROWS_WITH(crit.value(), "[json.exception.invalid_iterator.214] cannot get value");
				}
			}

			//TEST(constructors,"number (float)")
			{
				json j = 23.42;
				json j_const(j);

				//TEST(constructors,"json + begin/end")
				{
					json::iterator it = j.begin();
					EXPECT_TRUE(it != j.end());
					EXPECT_TRUE(*it == j);

					it++;
					EXPECT_TRUE(it != j.begin());
					EXPECT_TRUE(it == j.end());

					it--;
					EXPECT_TRUE(it == j.begin());
					EXPECT_TRUE(it != j.end());
					EXPECT_TRUE(*it == j);

					++it;
					EXPECT_TRUE(it != j.begin());
					EXPECT_TRUE(it == j.end());

					--it;
					EXPECT_TRUE(it == j.begin());
					EXPECT_TRUE(it != j.end());
					EXPECT_TRUE(*it == j);
				}

				//TEST(constructors,"const json + begin/end")
				{
					json::const_iterator it = j_const.begin();
					EXPECT_TRUE(it != j_const.end());
					EXPECT_TRUE(*it == j_const);

					it++;
					EXPECT_TRUE(it != j_const.begin());
					EXPECT_TRUE(it == j_const.end());

					it--;
					EXPECT_TRUE(it == j_const.begin());
					EXPECT_TRUE(it != j_const.end());
					EXPECT_TRUE(*it == j_const);

					++it;
					EXPECT_TRUE(it != j_const.begin());
					EXPECT_TRUE(it == j_const.end());

					--it;
					EXPECT_TRUE(it == j_const.begin());
					EXPECT_TRUE(it != j_const.end());
					EXPECT_TRUE(*it == j_const);
				}

				//TEST(constructors,"json + cbegin/cend")
				{
					json::const_iterator it = j.cbegin();
					EXPECT_TRUE(it != j.cend());
					EXPECT_TRUE(*it == j);

					it++;
					EXPECT_TRUE(it != j.cbegin());
					EXPECT_TRUE(it == j.cend());

					it--;
					EXPECT_TRUE(it == j.cbegin());
					EXPECT_TRUE(it != j.cend());
					EXPECT_TRUE(*it == j);

					++it;
					EXPECT_TRUE(it != j.cbegin());
					EXPECT_TRUE(it == j.cend());

					--it;
					EXPECT_TRUE(it == j.cbegin());
					EXPECT_TRUE(it != j.cend());
					EXPECT_TRUE(*it == j);
				}

				//TEST(constructors,"const json + cbegin/cend")
				{
					json::const_iterator it = j_const.cbegin();
					EXPECT_TRUE(it != j_const.cend());
					EXPECT_TRUE(*it == j_const);

					it++;
					EXPECT_TRUE(it != j_const.cbegin());
					EXPECT_TRUE(it == j_const.cend());

					it--;
					EXPECT_TRUE(it == j_const.cbegin());
					EXPECT_TRUE(it != j_const.cend());
					EXPECT_TRUE(*it == j_const);

					++it;
					EXPECT_TRUE(it != j_const.cbegin());
					EXPECT_TRUE(it == j_const.cend());

					--it;
					EXPECT_TRUE(it == j_const.cbegin());
					EXPECT_TRUE(it != j_const.cend());
					EXPECT_TRUE(*it == j_const);
				}

				//TEST(constructors,"json + rbegin/rend")
				{
					json::reverse_iterator it = j.rbegin();
					EXPECT_TRUE(it != j.rend());
					EXPECT_TRUE(*it == j);

					it++;
					EXPECT_TRUE(it != j.rbegin());
					EXPECT_TRUE(it == j.rend());

					it--;
					EXPECT_TRUE(it == j.rbegin());
					EXPECT_TRUE(it != j.rend());
					EXPECT_TRUE(*it == j);

					++it;
					EXPECT_TRUE(it != j.rbegin());
					EXPECT_TRUE(it == j.rend());

					--it;
					EXPECT_TRUE(it == j.rbegin());
					EXPECT_TRUE(it != j.rend());
					EXPECT_TRUE(*it == j);
				}

				//TEST(constructors,"json + crbegin/crend")
				{
					json::const_reverse_iterator it = j.crbegin();
					EXPECT_TRUE(it != j.crend());
					EXPECT_TRUE(*it == j);

					it++;
					EXPECT_TRUE(it != j.crbegin());
					EXPECT_TRUE(it == j.crend());

					it--;
					EXPECT_TRUE(it == j.crbegin());
					EXPECT_TRUE(it != j.crend());
					EXPECT_TRUE(*it == j);

					++it;
					EXPECT_TRUE(it != j.crbegin());
					EXPECT_TRUE(it == j.crend());

					--it;
					EXPECT_TRUE(it == j.crbegin());
					EXPECT_TRUE(it != j.crend());
					EXPECT_TRUE(*it == j);
				}

				//TEST(constructors,"const json + crbegin/crend")
				{
					json::const_reverse_iterator it = j_const.crbegin();
					EXPECT_TRUE(it != j_const.crend());
					EXPECT_TRUE(*it == j_const);

					it++;
					EXPECT_TRUE(it != j_const.crbegin());
					EXPECT_TRUE(it == j_const.crend());

					it--;
					EXPECT_TRUE(it == j_const.crbegin());
					EXPECT_TRUE(it != j_const.crend());
					EXPECT_TRUE(*it == j_const);

					++it;
					EXPECT_TRUE(it != j_const.crbegin());
					EXPECT_TRUE(it == j_const.crend());

					--it;
					EXPECT_TRUE(it == j_const.crbegin());
					EXPECT_TRUE(it != j_const.crend());
					EXPECT_TRUE(*it == j_const);
				}

				//TEST(constructors,"key/value")
				{
					auto it = j.begin();
					auto cit = j_const.cbegin();
					EXPECT_THROW(it.key(), json::invalid_iterator);
					//CHECK_THROWS_WITH(it.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					EXPECT_TRUE(it.value() == json(23.42));
					EXPECT_THROW(cit.key(), json::invalid_iterator);
					//CHECK_THROWS_WITH(cit.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					EXPECT_TRUE(cit.value() == json(23.42));

					auto rit = j.rend();
					auto crit = j.crend();
					EXPECT_THROW(rit.key(), json::invalid_iterator);
					EXPECT_THROW(rit.value(), json::invalid_iterator);
					EXPECT_THROW(crit.key(), json::invalid_iterator);
					EXPECT_THROW(crit.value(), json::invalid_iterator);
					//CHECK_THROWS_WITH(rit.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					//CHECK_THROWS_WITH(rit.value(), "[json.exception.invalid_iterator.214] cannot get value");
					//CHECK_THROWS_WITH(crit.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					//CHECK_THROWS_WITH(crit.value(), "[json.exception.invalid_iterator.214] cannot get value");
				}
			}

			//TEST(constructors,"null")
			{
				json j = nullptr;
				json j_const(j);

				//TEST(constructors,"json + begin/end")
				{
					json::iterator it = j.begin();
					EXPECT_TRUE(it == j.end());
				}

				//TEST(constructors,"const json + begin/end")
				{
					json::const_iterator it_begin = j_const.begin();
					json::const_iterator it_end = j_const.end();
					EXPECT_TRUE(it_begin == it_end);
				}

				//TEST(constructors,"json + cbegin/cend")
				{
					json::const_iterator it_begin = j.cbegin();
					json::const_iterator it_end = j.cend();
					EXPECT_TRUE(it_begin == it_end);
				}

				//TEST(constructors,"const json + cbegin/cend")
				{
					json::const_iterator it_begin = j_const.cbegin();
					json::const_iterator it_end = j_const.cend();
					EXPECT_TRUE(it_begin == it_end);
				}

				//TEST(constructors,"json + rbegin/rend")
				{
					json::reverse_iterator it = j.rbegin();
					EXPECT_TRUE(it == j.rend());
				}

				//TEST(constructors,"json + crbegin/crend")
				{
					json::const_reverse_iterator it = j.crbegin();
					EXPECT_TRUE(it == j.crend());
				}

				//TEST(constructors,"const json + crbegin/crend")
				{
					json::const_reverse_iterator it = j_const.crbegin();
					EXPECT_TRUE(it == j_const.crend());
				}

				//TEST(constructors,"key/value")
				{
					auto it = j.begin();
					auto cit = j_const.cbegin();
					EXPECT_THROW(it.key(), json::invalid_iterator);
					EXPECT_THROW(it.value(), json::invalid_iterator);
					EXPECT_THROW(cit.key(), json::invalid_iterator);
					EXPECT_THROW(cit.value(), json::invalid_iterator);
					//CHECK_THROWS_WITH(it.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					//CHECK_THROWS_WITH(it.value(), "[json.exception.invalid_iterator.214] cannot get value");
					//CHECK_THROWS_WITH(cit.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					//CHECK_THROWS_WITH(cit.value(), "[json.exception.invalid_iterator.214] cannot get value");

					auto rit = j.rend();
					auto crit = j.crend();
					EXPECT_THROW(rit.key(), json::invalid_iterator);
					EXPECT_THROW(rit.value(), json::invalid_iterator);
					EXPECT_THROW(crit.key(), json::invalid_iterator);
					EXPECT_THROW(crit.value(), json::invalid_iterator);
					//CHECK_THROWS_WITH(rit.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					//CHECK_THROWS_WITH(rit.value(), "[json.exception.invalid_iterator.214] cannot get value");
					//CHECK_THROWS_WITH(crit.key(), "[json.exception.invalid_iterator.207] cannot use key() for non-object iterators");
					//CHECK_THROWS_WITH(crit.value(), "[json.exception.invalid_iterator.214] cannot get value");
				}
			}
		}

		//TEST(constructors,"conversion from iterator to const iterator")
		{
			//TEST(constructors,"boolean")
			{
				json j = true;
				json::const_iterator it = j.begin();
				EXPECT_TRUE(it == j.cbegin());
				it = j.begin();
				EXPECT_TRUE(it == j.cbegin());
			}
			//TEST(constructors,"string")
			{
				json j = "hello world";
				json::const_iterator it = j.begin();
				EXPECT_TRUE(it == j.cbegin());
				it = j.begin();
				EXPECT_TRUE(it == j.cbegin());
			}
			//TEST(constructors,"array")
			{
				json j = {1, 2, 3};
				json::const_iterator it = j.begin();
				EXPECT_TRUE(it == j.cbegin());
				it = j.begin();
				EXPECT_TRUE(it == j.cbegin());
			}
			//TEST(constructors,"object")
			{
				json j = {{"A", 1}, {"B", 2}, {"C", 3}};
				json::const_iterator it = j.begin();
				EXPECT_TRUE(it == j.cbegin());
				it = j.begin();
				EXPECT_TRUE(it == j.cbegin());
			}
			//TEST(constructors,"number (integer)")
			{
				json j = 23;
				json::const_iterator it = j.begin();
				EXPECT_TRUE(it == j.cbegin());
				it = j.begin();
				EXPECT_TRUE(it == j.cbegin());
			}
			//TEST(constructors,"number (unsigned)")
			{
				json j = 23u;
				json::const_iterator it = j.begin();
				EXPECT_TRUE(it == j.cbegin());
				it = j.begin();
				EXPECT_TRUE(it == j.cbegin());
			}
			//TEST(constructors,"number (float)")
			{
				json j = 23.42;
				json::const_iterator it = j.begin();
				EXPECT_TRUE(it == j.cbegin());
				it = j.begin();
				EXPECT_TRUE(it == j.cbegin());
			}
			//TEST(constructors,"null")
			{
				json j = nullptr;
				json::const_iterator it = j.begin();
				EXPECT_TRUE(it == j.cbegin());
				it = j.begin();
				EXPECT_TRUE(it == j.cbegin());
			}
		}
	}
}
