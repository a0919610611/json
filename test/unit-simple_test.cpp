#include "gtest/gtest.h"
#include "json.hpp"

using json = nlohmann::json;

namespace
{

	TEST(SIMPLE, T00)
	{
		json j;
		j["a"] = "apple";
	}
}
