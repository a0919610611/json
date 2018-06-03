#include "gtest/gtest.h"
#include "json.hpp"

using nlohmann::json;

namespace
{
	//TEST(capacity, "empty()")
	//{
		//TEST(capacity, "boolean")
		//{
			json j = true;
			const json j_const(j);

			TEST(capacity, resultofempty)
			{
				EXPECT_FALSE(j.empty());
				EXPECT_FALSE(j_const.empty());
			}

			TEST(capacity, definitionofempty)
			{
				EXPECT_EQ(j.empty(), (j.begin() == j.end()));
				EXPECT_EQ(j_const.empty(), (j_const.begin() == j_const.end()));
			}
		//}

		//TEST(capacity, "string")
		//{
			json j0 = "hello world";
			const json j_const0(j0);

			TEST(capacity, stringresultofempty)
			{
				EXPECT_FALSE(j0.empty());
				EXPECT_FALSE(j_const0.empty());
			}

			TEST(capacity, stringdefinitionofempty)
			{
				EXPECT_EQ(j0.empty(), (j0.begin() == j0.end()));
				EXPECT_EQ(j_const0.empty(), (j_const0.begin() == j_const0.end()));
			}
		//}

		//TEST(capacity, "array")
		//{
			//TEST(capacity, "empty array")
			//{
				json j1 = json::array();
				const json j_const1(j1);

				TEST(capacity, arrayresultofempty)
				{
					EXPECT_TRUE(j1.empty());
					EXPECT_TRUE(j_const1.empty());
				}

				TEST(capacity, arraydefinitionofempty)
				{
					EXPECT_EQ(j1.empty(), (j1.begin() == j1.end()));
					EXPECT_EQ(j_const1.empty(), (j_const1.begin() == j_const1.end()));
				}
			//}

			//TEST(capacity, "filled array")
			//{
				json j2 = {1, 2, 3};
				const json j_const2(j2);

				TEST(capacity, filledarrayresultofempty)
				{
					EXPECT_FALSE(j2.empty());
					EXPECT_FALSE(j_const2.empty());
				}

				TEST(capacity, filledarraydefinitionofempty)
				{
					EXPECT_EQ(j2.empty(), (j2.begin() == j2.end()));
					EXPECT_EQ(j_const2.empty(), (j_const2.begin() == j_const2.end()));
				}
			//}
		//}

		//TEST(capacity, "object")
		//{
			//TEST(capacity, "empty object")
			//{
				json j3 = json::object();
				const json j_const3(j3);

				TEST(capacity, objectresultofempty)
				{
					EXPECT_TRUE(j3.empty());
					EXPECT_TRUE(j_const3.empty());
				}

				TEST(capacity, objectdefinitionofempty)
				{
					EXPECT_EQ(j3.empty(), (j3.begin() == j3.end()));
					EXPECT_EQ(j_const3.empty(), (j_const3.begin() == j_const3.end()));
				}
			//}

			//TEST(capacity, "filled object")
			//{
				json j4 = {{"one", 1}, {"two", 2}, {"three", 3}};
				const json j_const4(j4);

				TEST(capacity, filledobjectrestultofempty)
				{
					EXPECT_FALSE(j4.empty());
					EXPECT_FALSE(j_const4.empty());
				}

				TEST(capacity, filledobjectdefinitionofempty)
				{
					EXPECT_EQ(j4.empty(), (j4.begin() == j4.end()));
					EXPECT_EQ(j_const4.empty(), (j_const4.begin() == j_const4.end()));
				}
			//}
		//}

		//TEST(capacity, "number (integer)")
		//{

			TEST(capacity, intresultofempty)
			{
				json j = -23;
				const json j_const(j);
				EXPECT_FALSE(j.empty());
				EXPECT_FALSE(j_const.empty());
			}

			TEST(capacity, intdefinitionofempty)
			{
				json j = -23;
				const json j_const(j);
				EXPECT_EQ(j.empty(), (j.begin() == j.end()));
				EXPECT_EQ(j_const.empty(), (j_const.begin() == j_const.end()));
			}
		//}

		//TEST(capacity, "number (unsigned)")
		//{

			TEST(capacity, uintresultofempty)
			{
				json j = 23u;
				const json j_const(j);
				EXPECT_FALSE(j.empty());
				EXPECT_FALSE(j_const.empty());
			}

			TEST(capacity, uintdefinitionofempty)
			{
				json j = 23u;
				const json j_const(j);
				EXPECT_EQ(j.empty(), (j.begin() == j.end()));
				EXPECT_EQ(j_const.empty(), (j_const.begin() == j_const.end()));
			}
		//}

		//TEST(capacity, "number (float)")
		//{

			TEST(capacity, floatresultofempty)
			{
				json j = 23.42;
				const json j_const(j);
				EXPECT_FALSE(j.empty());
				EXPECT_FALSE(j_const.empty());
			}

			TEST(capacity, floatdefinitionofempty)
			{
				json j = 23.42;
				const json j_const(j);
				EXPECT_EQ(j.empty(), (j.begin() == j.end()));
				EXPECT_EQ(j_const.empty(), (j_const.begin() == j_const.end()));
			}
		//}

		//TEST(capacity, "null")
		//{

			TEST(capacity, nullresultofempty)
			{
				json j = nullptr;
				const json j_const(j);
				EXPECT_TRUE(j.empty());
				EXPECT_TRUE(j_const.empty());
			}

			TEST(capacity, nulledefinitionofempty)
			{
				json j = nullptr;
				const json j_const(j);
				EXPECT_EQ(j.empty(), (j.begin() == j.end()));
				EXPECT_EQ(j_const.empty(), (j_const.begin() == j_const.end()));
			}
		//}
	//}

	//TEST(capacity, "size()")
	//{
		//TEST(capacity, "boolean")
		//{

			TEST(capacity, booleanresultofsize)
			{
				json j = true;
				const json j_const(j);
				EXPECT_EQ(j.size(), 1);
				EXPECT_EQ(j_const.size(), 1);
			}

			TEST(capacity, booleandefinitionofsize)
			{
				json j = true;
				const json j_const(j);
				EXPECT_EQ(std::distance(j.begin(), j.end()), j.size());
				EXPECT_EQ(std::distance(j_const.begin(), j_const.end()), j_const.size());
				EXPECT_EQ(std::distance(j.rbegin(), j.rend()), j.size());
				EXPECT_EQ(std::distance(j_const.crbegin(), j_const.crend()), j_const.size());
			}
		//}

		//TEST(capacity, "string")
		//{

			TEST(capacity, stringresultofsize)
			{
				json j = "hello world";
				const json j_const(j);
				EXPECT_EQ(j.size(), 1);
				EXPECT_EQ(j_const.size(), 1);
			}

			TEST(capacity, stringdefinitionofsize)
			{
				json j = "hello world";
				const json j_const(j);
				EXPECT_EQ(std::distance(j.begin(), j.end()), j.size());
				EXPECT_EQ(std::distance(j_const.begin(), j_const.end()), j_const.size());
				EXPECT_EQ(std::distance(j.rbegin(), j.rend()), j.size());
				EXPECT_EQ(std::distance(j_const.crbegin(), j_const.crend()), j_const.size());
			}
		//}

		//TEST(capacity, "array")
		//{
			//TEST(capacity, "empty array")
			//{

				TEST(capacity, emptyarrayresultofsize)
				{
					json j = json::array();
					const json j_const(j);
					EXPECT_EQ(j.size(), 0);
					EXPECT_EQ(j_const.size(), 0);
				}

				TEST(capacity, emptyarraydefinitionofsize)
				{
					json j = json::array();
					const json j_const(j);
					EXPECT_EQ(std::distance(j.begin(), j.end()), j.size());
					EXPECT_EQ(std::distance(j_const.begin(), j_const.end()), j_const.size());
					EXPECT_EQ(std::distance(j.rbegin(), j.rend()), j.size());
					EXPECT_EQ(std::distance(j_const.crbegin(), j_const.crend()), j_const.size());
				}
			//}

			//TEST(capacity, "filled array")
			//{

				TEST(capacity, filledarrayresultofsize)
				{
					json j = {1, 2, 3};
					const json j_const(j);
					EXPECT_EQ(j.size(), 3);
					EXPECT_EQ(j_const.size(), 3);
				}

				TEST(capacity, filledarraydefinitionofsize)
				{
					json j = {1, 2, 3};
					const json j_const(j);
					EXPECT_EQ(std::distance(j.begin(), j.end()), j.size());
					EXPECT_EQ(std::distance(j_const.begin(), j_const.end()), j_const.size());
					EXPECT_EQ(std::distance(j.rbegin(), j.rend()), j.size());
					EXPECT_EQ(std::distance(j_const.crbegin(), j_const.crend()), j_const.size());
				}
			//}
		//}

		//TEST(capacity, "object")
		//{
			//TEST(capacity, "empty object")
			//{

				TEST(capacity, emptyobjectresultofsize)
				{
					json j = json::object();
					const json j_const(j);
					EXPECT_EQ(j.size(), 0);
					EXPECT_EQ(j_const.size(), 0);
				}

				TEST(capacity, emptyobjectdefinitionofsize)
				{
					json j = json::object();
					const json j_const(j);
					EXPECT_EQ(std::distance(j.begin(), j.end()), j.size());
					EXPECT_EQ(std::distance(j_const.begin(), j_const.end()), j_const.size());
					EXPECT_EQ(std::distance(j.rbegin(), j.rend()), j.size());
					EXPECT_EQ(std::distance(j_const.crbegin(), j_const.crend()), j_const.size());
				}
			//}

			//TEST(capacity, "filled object")
			//{

				TEST(capacity, filledobjectresultofsize)
				{
					json j = {{"one", 1}, {"two", 2}, {"three", 3}};
					const json j_const(j);
					EXPECT_EQ(j.size(), 3);
					EXPECT_EQ(j_const.size(), 3);
				}

				TEST(capacity, filledobjectdefinitionofsize)
				{
					json j = {{"one", 1}, {"two", 2}, {"three", 3}};
					const json j_const(j);
					EXPECT_EQ(std::distance(j.begin(), j.end()), j.size());
					EXPECT_EQ(std::distance(j_const.begin(), j_const.end()), j_const.size());
					EXPECT_EQ(std::distance(j.rbegin(), j.rend()), j.size());
					EXPECT_EQ(std::distance(j_const.crbegin(), j_const.crend()), j_const.size());
				}
			//}
		//}

		//TEST(capacity, "number (integer)")
		//{

			TEST(capacity, intresultofsize)
			{
				json j = -23;
				const json j_const(j);
				EXPECT_EQ(j.size(), 1);
				EXPECT_EQ(j_const.size(), 1);
			}

			TEST(capacity, intdefinitionofsize)
			{
				json j = -23;
				const json j_const(j);
				EXPECT_EQ(std::distance(j.begin(), j.end()), j.size());
				EXPECT_EQ(std::distance(j_const.begin(), j_const.end()), j_const.size());
				EXPECT_EQ(std::distance(j.rbegin(), j.rend()), j.size());
				EXPECT_EQ(std::distance(j_const.crbegin(), j_const.crend()), j_const.size());
			}
		//}

		//TEST(capacity, "number (unsigned)")
		//{

			TEST(capacity, uintresultofsize)
			{
				json j = 23u;
				const json j_const(j);
				EXPECT_EQ(j.size(), 1);
				EXPECT_EQ(j_const.size(), 1);
			}

			TEST(capacity, uintdefinitionofsize)
			{
				json j = 23u;
				const json j_const(j);
				EXPECT_EQ(std::distance(j.begin(), j.end()), j.size());
				EXPECT_EQ(std::distance(j_const.begin(), j_const.end()), j_const.size());
				EXPECT_EQ(std::distance(j.rbegin(), j.rend()), j.size());
				EXPECT_EQ(std::distance(j_const.crbegin(), j_const.crend()), j_const.size());
			}
		//}

		//TEST(capacity, "number (float)")
		//{

			TEST(capacity, floatresultofsize)
			{
				json j = 23.42;
				const json j_const(j);
				EXPECT_EQ(j.size(), 1);
				EXPECT_EQ(j_const.size(), 1);
			}

			TEST(capacity, floatdefinitionofsize)
			{
				json j = 23.42;
				const json j_const(j);
				EXPECT_EQ(std::distance(j.begin(), j.end()), j.size());
				EXPECT_EQ(std::distance(j_const.begin(), j_const.end()), j_const.size());
				EXPECT_EQ(std::distance(j.rbegin(), j.rend()), j.size());
				EXPECT_EQ(std::distance(j_const.crbegin(), j_const.crend()), j_const.size());
			}
		//}

		//TEST(capacity, "null")
		//{

			TEST(capacity, nullresultofsize)
			{
				json j = nullptr;
				const json j_const(j);
				EXPECT_EQ(j.size(), 0);
				EXPECT_EQ(j_const.size(), 0);
			}

			TEST(capacity, nulldefinitionofsize)
			{
				json j = nullptr;
				const json j_const(j);
				EXPECT_EQ(std::distance(j.begin(), j.end()), j.size());
				EXPECT_EQ(std::distance(j_const.begin(), j_const.end()), j_const.size());
				EXPECT_EQ(std::distance(j.rbegin(), j.rend()), j.size());
				EXPECT_EQ(std::distance(j_const.crbegin(), j_const.crend()), j_const.size());
			}
		//}
	//}

	//TEST(capacity, "max_size()")
	//{
		//TEST(capacity, "boolean")
		//{

			TEST(capacity, booleanresultofmax_size)
			{
				json j = true;
				const json j_const(j);
				EXPECT_EQ(j.max_size(), 1);
				EXPECT_EQ(j_const.max_size(), 1);
			}
		//}

		//TEST(capacity, "string")
		//{

			TEST(capacity, stringresultofmax_size)
			{
				json j = "hello world";
				const json j_const(j);
				EXPECT_EQ(j.max_size(), 1);
				EXPECT_EQ(j_const.max_size(), 1);
			}
		//}

		//TEST(capacity, "array")
		//{
			//TEST(capacity, "empty array")
			//{

				TEST(capacity, emptyarrayresultofmax_size)
				{
					json j = json::array();
					const json j_const(j);
					EXPECT_GE(j.max_size(), j.size());
					EXPECT_GE(j_const.max_size(), j_const.size());
				}
			//}

			//TEST(capacity, "filled array")
			//{

				TEST(capacity, filledarrayresultofmax_size)
				{
					json j = {1, 2, 3};
					const json j_const(j);
					EXPECT_GE(j.max_size(), j.size());
					EXPECT_GE(j_const.max_size(), j_const.size());
				}
			//}
		//}

		//TEST(capacity, "object")
		//{
			//TEST(capacity, "empty object")
			//{

				TEST(capacity, emptyobjectresultofmax_size)
				{
					json j = json::object();
					const json j_const(j);
					EXPECT_GE(j.max_size(), j.size());
					EXPECT_GE(j_const.max_size(), j_const.size());
				}
			//}

			//TEST(capacity, "filled object")
			//{

				TEST(capacity, filledobjectresultofmax_size)
				{
					json j = {{"one", 1}, {"two", 2}, {"three", 3}};
					const json j_const(j);
					EXPECT_GE(j.max_size(), j.size());
					EXPECT_GE(j_const.max_size(), j_const.size());
				}
			//}
		//}

		//TEST(capacity, "number (integer)")
		//{

			TEST(capacity, intresultofmax_size)
			{
				json j = -23;
				const json j_const(j);
				EXPECT_EQ(j.max_size(), 1);
				EXPECT_EQ(j_const.max_size(), 1);
			}
		//}

		//TEST(capacity, "number (unsigned)")
		//{

			TEST(capacity, uintresultofmax_size)
			{
				json j = 23u;
				const json j_const(j);
				EXPECT_EQ(j.max_size(), 1);
				EXPECT_EQ(j_const.max_size(), 1);
			}
		//}

		//TEST(capacity, "number (float)")
		//{

			TEST(capacity, floatresultofmax_size)
			{
				json j = 23.42;
				const json j_const(j);
				EXPECT_EQ(j.max_size(), 1);
				EXPECT_EQ(j_const.max_size(), 1);
			}
		//}

		//TEST(capacity, "null")
		//{

			TEST(capacity, nullresultofmax_size)
			{
				json j = nullptr;
				const json j_const(j);
				EXPECT_EQ(j.max_size(), 0);
				EXPECT_EQ(j_const.max_size(), 0);
			}
		//}
	//}
}
