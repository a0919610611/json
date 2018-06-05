#include "gtest/gtest.h"
#include "json.hpp"

using nlohmann::json;

namespace
{
	TEST(items, iterator_wrapper)
	{
		//TEST(constructors,"object")
		{
			//TEST(constructors,"value")
			{
				json j = {{"A", 1}, {"B", 2}};
				int counter = 1;

				for (auto i : json::iterator_wrapper(j))
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "A");
							EXPECT_TRUE(i.value() == json(1));
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "B");
							EXPECT_TRUE(i.value() == json(2));
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}

			//TEST(constructors,"reference")
			{
				json j = {{"A", 1}, {"B", 2}};
				int counter = 1;

				for (auto& i : json::iterator_wrapper(j))
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "A");
							EXPECT_TRUE(i.value() == json(1));

							// change the value
							i.value() = json(11);
							EXPECT_TRUE(i.value() == json(11));
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "B");
							EXPECT_TRUE(i.value() == json(2));

							// change the value
							i.value() = json(22);
							EXPECT_TRUE(i.value() == json(22));
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);

				// check if values where changed
				EXPECT_TRUE(j == json({{"A", 11}, {"B", 22}}));
			}

			//TEST(constructors,"const value")
			{
				json j = {{"A", 1}, {"B", 2}};
				int counter = 1;

				for (const auto i : json::iterator_wrapper(j))
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "A");
							EXPECT_TRUE(i.value() == json(1));
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "B");
							EXPECT_TRUE(i.value() == json(2));
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}

			//TEST(constructors,"const reference")
			{
				json j = {{"A", 1}, {"B", 2}};
				int counter = 1;

				for (const auto& i : json::iterator_wrapper(j))
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "A");
							EXPECT_TRUE(i.value() == json(1));
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "B");
							EXPECT_TRUE(i.value() == json(2));
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}
		}

		//TEST(constructors,"const object")
		{
			//TEST(constructors,"value")
			{
				const json j = {{"A", 1}, {"B", 2}};
				int counter = 1;

				for (auto i : json::iterator_wrapper(j))
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "A");
							EXPECT_TRUE(i.value() == json(1));
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "B");
							EXPECT_TRUE(i.value() == json(2));
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}

			//TEST(constructors,"reference")
			{
				const json j = {{"A", 1}, {"B", 2}};
				int counter = 1;

				for (auto& i : json::iterator_wrapper(j))
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "A");
							EXPECT_TRUE(i.value() == json(1));
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "B");
							EXPECT_TRUE(i.value() == json(2));
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}

			//TEST(constructors,"const value")
			{
				const json j = {{"A", 1}, {"B", 2}};
				int counter = 1;

				for (const auto i : json::iterator_wrapper(j))
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "A");
							EXPECT_TRUE(i.value() == json(1));
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "B");
							EXPECT_TRUE(i.value() == json(2));
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}

			//TEST(constructors,"const reference")
			{
				const json j = {{"A", 1}, {"B", 2}};
				int counter = 1;

				for (const auto& i : json::iterator_wrapper(j))
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "A");
							EXPECT_TRUE(i.value() == json(1));
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "B");
							EXPECT_TRUE(i.value() == json(2));
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}
		}

		//TEST(constructors,"array")
		{
			//TEST(constructors,"value")
			{
				json j = {"A", "B"};
				int counter = 1;

				for (auto i : json::iterator_wrapper(j))
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "0");
							EXPECT_TRUE(i.value() == "A");
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "1");
							EXPECT_TRUE(i.value() == "B");
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}

			//TEST(constructors,"reference")
			{
				json j = {"A", "B"};
				int counter = 1;

				for (auto& i : json::iterator_wrapper(j))
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "0");
							EXPECT_TRUE(i.value() == "A");

							// change the value
							i.value() = "AA";
							EXPECT_TRUE(i.value() == "AA");
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "1");
							EXPECT_TRUE(i.value() == "B");

							// change the value
							i.value() = "BB";
							EXPECT_TRUE(i.value() == "BB");
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);

				// check if values where changed
				EXPECT_TRUE(j == json({"AA", "BB"}));
			}

			//TEST(constructors,"const value")
			{
				json j = {"A", "B"};
				int counter = 1;

				for (const auto i : json::iterator_wrapper(j))
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "0");
							EXPECT_TRUE(i.value() == "A");
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "1");
							EXPECT_TRUE(i.value() == "B");
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}

			//TEST(constructors,"const reference")
			{
				json j = {"A", "B"};
				int counter = 1;

				for (const auto& i : json::iterator_wrapper(j))
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "0");
							EXPECT_TRUE(i.value() == "A");
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "1");
							EXPECT_TRUE(i.value() == "B");
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}
		}

		//TEST(constructors,"const array")
		{
			//TEST(constructors,"value")
			{
				const json j = {"A", "B"};
				int counter = 1;

				for (auto i : json::iterator_wrapper(j))
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "0");
							EXPECT_TRUE(i.value() == "A");
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "1");
							EXPECT_TRUE(i.value() == "B");
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}

			//TEST(constructors,"reference")
			{
				const json j = {"A", "B"};
				int counter = 1;

				for (auto& i : json::iterator_wrapper(j))
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "0");
							EXPECT_TRUE(i.value() == "A");
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "1");
							EXPECT_TRUE(i.value() == "B");
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}

			//TEST(constructors,"const value")
			{
				const json j = {"A", "B"};
				int counter = 1;

				for (const auto i : json::iterator_wrapper(j))
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "0");
							EXPECT_TRUE(i.value() == "A");
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "1");
							EXPECT_TRUE(i.value() == "B");
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}

			//TEST(constructors,"const reference")
			{
				const json j = {"A", "B"};
				int counter = 1;

				for (const auto& i : json::iterator_wrapper(j))
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "0");
							EXPECT_TRUE(i.value() == "A");
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "1");
							EXPECT_TRUE(i.value() == "B");
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}
		}

		//TEST(constructors,"primitive")
		{
			//TEST(constructors,"value")
			{
				json j = 1;
				int counter = 1;

				for (auto i : json::iterator_wrapper(j))
				{
					++counter;
					EXPECT_TRUE(i.key() == "");
					EXPECT_TRUE(i.value() == json(1));
				}

				EXPECT_TRUE(counter == 2);
			}

			//TEST(constructors,"reference")
			{
				json j = 1;
				int counter = 1;

				for (auto& i : json::iterator_wrapper(j))
				{
					++counter;
					EXPECT_TRUE(i.key() == "");
					EXPECT_TRUE(i.value() == json(1));

					// change value
					i.value() = json(2);
				}

				EXPECT_TRUE(counter == 2);

				// check if value has changed
				EXPECT_TRUE(j == json(2));
			}

			//TEST(constructors,"const value")
			{
				json j = 1;
				int counter = 1;

				for (const auto i : json::iterator_wrapper(j))
				{
					++counter;
					EXPECT_TRUE(i.key() == "");
					EXPECT_TRUE(i.value() == json(1));
				}

				EXPECT_TRUE(counter == 2);
			}

			//TEST(constructors,"const reference")
			{
				json j = 1;
				int counter = 1;

				for (const auto& i : json::iterator_wrapper(j))
				{
					++counter;
					EXPECT_TRUE(i.key() == "");
					EXPECT_TRUE(i.value() == json(1));
				}

				EXPECT_TRUE(counter == 2);
			}
		}

		//TEST(constructors,"const primitive")
		{
			//TEST(constructors,"value")
			{
				const json j = 1;
				int counter = 1;

				for (auto i : json::iterator_wrapper(j))
				{
					++counter;
					EXPECT_TRUE(i.key() == "");
					EXPECT_TRUE(i.value() == json(1));
				}

				EXPECT_TRUE(counter == 2);
			}

			//TEST(constructors,"reference")
			{
				const json j = 1;
				int counter = 1;

				for (auto& i : json::iterator_wrapper(j))
				{
					++counter;
					EXPECT_TRUE(i.key() == "");
					EXPECT_TRUE(i.value() == json(1));
				}

				EXPECT_TRUE(counter == 2);
			}

			//TEST(constructors,"const value")
			{
				const json j = 1;
				int counter = 1;

				for (const auto i : json::iterator_wrapper(j))
				{
					++counter;
					EXPECT_TRUE(i.key() == "");
					EXPECT_TRUE(i.value() == json(1));
				}

				EXPECT_TRUE(counter == 2);
			}

			//TEST(constructors,"const reference")
			{
				const json j = 1;
				int counter = 1;

				for (const auto& i : json::iterator_wrapper(j))
				{
					++counter;
					EXPECT_TRUE(i.key() == "");
					EXPECT_TRUE(i.value() == json(1));
				}

				EXPECT_TRUE(counter == 2);
			}
		}
	}

	TEST(items, items)
	{
		//TEST(constructors,"object")
		{
			//TEST(constructors,"value")
			{
				json j = {{"A", 1}, {"B", 2}};
				int counter = 1;

				for (auto i : j.items())
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "A");
							EXPECT_TRUE(i.value() == json(1));
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "B");
							EXPECT_TRUE(i.value() == json(2));
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}

			//TEST(constructors,"reference")
			{
				json j = {{"A", 1}, {"B", 2}};
				int counter = 1;

				for (auto& i : j.items())
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "A");
							EXPECT_TRUE(i.value() == json(1));

							// change the value
							i.value() = json(11);
							EXPECT_TRUE(i.value() == json(11));
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "B");
							EXPECT_TRUE(i.value() == json(2));

							// change the value
							i.value() = json(22);
							EXPECT_TRUE(i.value() == json(22));
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);

				// check if values where changed
				EXPECT_TRUE(j == json({{"A", 11}, {"B", 22}}));
			}

			//TEST(constructors,"const value")
			{
				json j = {{"A", 1}, {"B", 2}};
				int counter = 1;

				for (const auto i : j.items())
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "A");
							EXPECT_TRUE(i.value() == json(1));
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "B");
							EXPECT_TRUE(i.value() == json(2));
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}

			//TEST(constructors,"const reference")
			{
				json j = {{"A", 1}, {"B", 2}};
				int counter = 1;

				for (const auto& i : j.items())
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "A");
							EXPECT_TRUE(i.value() == json(1));
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "B");
							EXPECT_TRUE(i.value() == json(2));
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}
		}

		//TEST(constructors,"const object")
		{
			//TEST(constructors,"value")
			{
				const json j = {{"A", 1}, {"B", 2}};
				int counter = 1;

				for (auto i : j.items())
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "A");
							EXPECT_TRUE(i.value() == json(1));
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "B");
							EXPECT_TRUE(i.value() == json(2));
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}

			//TEST(constructors,"reference")
			{
				const json j = {{"A", 1}, {"B", 2}};
				int counter = 1;

				for (auto& i : j.items())
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "A");
							EXPECT_TRUE(i.value() == json(1));
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "B");
							EXPECT_TRUE(i.value() == json(2));
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}

			//TEST(constructors,"const value")
			{
				const json j = {{"A", 1}, {"B", 2}};
				int counter = 1;

				for (const auto i : j.items())
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "A");
							EXPECT_TRUE(i.value() == json(1));
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "B");
							EXPECT_TRUE(i.value() == json(2));
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}

			//TEST(constructors,"const reference")
			{
				const json j = {{"A", 1}, {"B", 2}};
				int counter = 1;

				for (const auto& i : j.items())
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "A");
							EXPECT_TRUE(i.value() == json(1));
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "B");
							EXPECT_TRUE(i.value() == json(2));
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}
		}

		//TEST(constructors,"array")
		{
			//TEST(constructors,"value")
			{
				json j = {"A", "B"};
				int counter = 1;

				for (auto i : j.items())
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "0");
							EXPECT_TRUE(i.value() == "A");
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "1");
							EXPECT_TRUE(i.value() == "B");
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}

			//TEST(constructors,"reference")
			{
				json j = {"A", "B"};
				int counter = 1;

				for (auto& i : j.items())
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "0");
							EXPECT_TRUE(i.value() == "A");

							// change the value
							i.value() = "AA";
							EXPECT_TRUE(i.value() == "AA");
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "1");
							EXPECT_TRUE(i.value() == "B");

							// change the value
							i.value() = "BB";
							EXPECT_TRUE(i.value() == "BB");
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);

				// check if values where changed
				EXPECT_TRUE(j == json({"AA", "BB"}));
			}

			//TEST(constructors,"const value")
			{
				json j = {"A", "B"};
				int counter = 1;

				for (const auto i : j.items())
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "0");
							EXPECT_TRUE(i.value() == "A");
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "1");
							EXPECT_TRUE(i.value() == "B");
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}

			//TEST(constructors,"const reference")
			{
				json j = {"A", "B"};
				int counter = 1;

				for (const auto& i : j.items())
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "0");
							EXPECT_TRUE(i.value() == "A");
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "1");
							EXPECT_TRUE(i.value() == "B");
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}
		}

		//TEST(constructors,"const array")
		{
			//TEST(constructors,"value")
			{
				const json j = {"A", "B"};
				int counter = 1;

				for (auto i : j.items())
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "0");
							EXPECT_TRUE(i.value() == "A");
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "1");
							EXPECT_TRUE(i.value() == "B");
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}

			//TEST(constructors,"reference")
			{
				const json j = {"A", "B"};
				int counter = 1;

				for (auto& i : j.items())
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "0");
							EXPECT_TRUE(i.value() == "A");
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "1");
							EXPECT_TRUE(i.value() == "B");
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}

			//TEST(constructors,"const value")
			{
				const json j = {"A", "B"};
				int counter = 1;

				for (const auto i : j.items())
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "0");
							EXPECT_TRUE(i.value() == "A");
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "1");
							EXPECT_TRUE(i.value() == "B");
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}

			//TEST(constructors,"const reference")
			{
				const json j = {"A", "B"};
				int counter = 1;

				for (const auto& i : j.items())
				{
					switch (counter++)
					{
						case 1:
						{
							EXPECT_TRUE(i.key() == "0");
							EXPECT_TRUE(i.value() == "A");
							break;
						}

						case 2:
						{
							EXPECT_TRUE(i.key() == "1");
							EXPECT_TRUE(i.value() == "B");
							break;
						}

						default:
						{
							break;
						}
					}
				}

				EXPECT_TRUE(counter == 3);
			}
		}

		//TEST(constructors,"primitive")
		{
			//TEST(constructors,"value")
			{
				json j = 1;
				int counter = 1;

				for (auto i : j.items())
				{
					++counter;
					EXPECT_TRUE(i.key() == "");
					EXPECT_TRUE(i.value() == json(1));
				}

				EXPECT_TRUE(counter == 2);
			}

			//TEST(constructors,"reference")
			{
				json j = 1;
				int counter = 1;

				for (auto& i : j.items())
				{
					++counter;
					EXPECT_TRUE(i.key() == "");
					EXPECT_TRUE(i.value() == json(1));

					// change value
					i.value() = json(2);
				}

				EXPECT_TRUE(counter == 2);

				// check if value has changed
				EXPECT_TRUE(j == json(2));
			}

			//TEST(constructors,"const value")
			{
				json j = 1;
				int counter = 1;

				for (const auto i : j.items())
				{
					++counter;
					EXPECT_TRUE(i.key() == "");
					EXPECT_TRUE(i.value() == json(1));
				}

				EXPECT_TRUE(counter == 2);
			}

			//TEST(constructors,"const reference")
			{
				json j = 1;
				int counter = 1;

				for (const auto& i : j.items())
				{
					++counter;
					EXPECT_TRUE(i.key() == "");
					EXPECT_TRUE(i.value() == json(1));
				}

				EXPECT_TRUE(counter == 2);
			}
		}

		//TEST(constructors,"const primitive")
		{
			//TEST(constructors,"value")
			{
				const json j = 1;
				int counter = 1;

				for (auto i : j.items())
				{
					++counter;
					EXPECT_TRUE(i.key() == "");
					EXPECT_TRUE(i.value() == json(1));
				}

				EXPECT_TRUE(counter == 2);
			}

			//TEST(constructors,"reference")
			{
				const json j = 1;
				int counter = 1;

				for (auto& i : j.items())
				{
					++counter;
					EXPECT_TRUE(i.key() == "");
					EXPECT_TRUE(i.value() == json(1));
				}

				EXPECT_TRUE(counter == 2);
			}

			//TEST(constructors,"const value")
			{
				const json j = 1;
				int counter = 1;

				for (const auto i : j.items())
				{
					++counter;
					EXPECT_TRUE(i.key() == "");
					EXPECT_TRUE(i.value() == json(1));
				}

				EXPECT_TRUE(counter == 2);
			}

			//TEST(constructors,"const reference")
			{
				const json j = 1;
				int counter = 1;

				for (const auto& i : j.items())
				{
					++counter;
					EXPECT_TRUE(i.key() == "");
					EXPECT_TRUE(i.value() == json(1));
				}

				EXPECT_TRUE(counter == 2);
			}
		}
	}
}
