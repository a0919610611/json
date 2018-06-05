#include "gtest/gtest.h"
#include "json.hpp"

using nlohmann::json;

namespace
{

	TEST(constructors, constructor2)
	{
		//TEST(constructors,"copy constructor")
		{
			//TEST(constructors,"object")
			{
				json j {{"foo", 1}, {"bar", false}};
				json k(j);
				EXPECT_TRUE(j == k);
			}

			//TEST(constructors,"array")
			{
				json j {"foo", 1, 42.23, false};
				json k(j);
				EXPECT_TRUE(j == k);
			}

			//TEST(constructors,"null")
			{
				json j(nullptr);
				json k(j);
				EXPECT_TRUE(j == k);
			}

			//TEST(constructors,"boolean")
			{
				json j(true);
				json k(j);
				EXPECT_TRUE(j == k);
			}

			//TEST(constructors,"string")
			{
				json j("Hello world");
				json k(j);
				EXPECT_TRUE(j == k);
			}

			//TEST(constructors,"number (integer)")
			{
				json j(42);
				json k(j);
				EXPECT_TRUE(j == k);
			}

			//TEST(constructors,"number (unsigned)")
			{
				json j(42u);
				json k(j);
				EXPECT_TRUE(j == k);
			}

			//TEST(constructors,"number (floating-point)")
			{
				json j(42.23);
				json k(j);
				EXPECT_TRUE(j == k);
			}
		}

		//TEST(constructors,"move constructor")
		{
			json j {{"foo", "bar"}, {"baz", {1, 2, 3, 4}}, {"a", 42u}, {"b", 42.23}, {"c", nullptr}};
			EXPECT_TRUE(j.type() == json::value_t::object);
			json k(std::move(j));
			EXPECT_TRUE(k.type() == json::value_t::object);
			EXPECT_TRUE(j.type() == json::value_t::null);
		}

		//TEST(constructors,"copy assignment")
		{
			//TEST(constructors,"object")
			{
				json j {{"foo", 1}, {"bar", false}};
				json k;
				k = j;
				EXPECT_TRUE(j == k);
			}

			//TEST(constructors,"array")
			{
				json j {"foo", 1, 42.23, false};
				json k;
				k = j;
				EXPECT_TRUE(j == k);
			}

			//TEST(constructors,"null")
			{
				json j(nullptr);
				json k;
				k = j;
				EXPECT_TRUE(j == k);
			}

			//TEST(constructors,"boolean")
			{
				json j(true);
				json k;
				k = j;
				EXPECT_TRUE(j == k);
			}

			//TEST(constructors,"string")
			{
				json j("Hello world");
				json k;
				k = j;
				EXPECT_TRUE(j == k);
			}

			//TEST(constructors,"number (integer)")
			{
				json j(42);
				json k;
				k = j;
				EXPECT_TRUE(j == k);
			}

			//TEST(constructors,"number (unsigned)")
			{
				json j(42u);
				json k;
				k = j;
				EXPECT_TRUE(j == k);
			}

			//TEST(constructors,"number (floating-point)")
			{
				json j(42.23);
				json k;
				k = j;
				EXPECT_TRUE(j == k);
			}
		}

		//TEST(constructors,"destructor")
		{
			//TEST(constructors,"object")
			{
				auto j = new json {{"foo", 1}, {"bar", false}};
				delete j;
			}

			//TEST(constructors,"array")
			{
				auto j = new json {"foo", 1, 1u, false, 23.42};
				delete j;
			}

			//TEST(constructors,"string")
			{
				auto j = new json("Hello world");
				delete j;
			}
		}
	}
}
