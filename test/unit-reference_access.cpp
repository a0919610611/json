#include "json.hpp"
#include "gtest/gtest.h"

using json = nlohmann::json;

TEST(JSON_Reference_Access, Simple) {
  json json_types = {{"boolean", true},
                     {"number", {{"integer", 42}, {"floating-point", 17.23}}},
                     {"string", "Hello, world!"},
                     {"array", {1, 2, 3, 4, 5}},
                     {"null", nullptr}};
}
TEST(JSON_Reference_Access, Reference_Access_To_Object_t) {
  using test_type = json::object_t;
  json value = {{"one", 1}, {"two", 2}};

  // check if references are returned correctly
  test_type &p1 = value.get_ref<test_type &>();
  EXPECT_EQ(&p1, value.get_ptr<test_type *>());
  EXPECT_EQ(p1, value.get<test_type>());

  const test_type &p2 = value.get_ref<const test_type &>();
  EXPECT_EQ(&p2, value.get_ptr<const test_type *>());
  EXPECT_EQ(p2, value.get<test_type>());
  EXPECT_THROW(
      {
        try {
          value.get_ref<json::array_t &>();
        } catch (const json::type_error &e) {
          EXPECT_STREQ("[json.exception.type_error.303] incompatible "
                       "ReferenceType for get_ref, actual type is object",
                       e.what());
          throw;
        }
      },
      json::type_error);
}
