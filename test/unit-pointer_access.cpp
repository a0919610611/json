#include "json.hpp"
#include "gtest/gtest.h"

using json = nlohmann::json;

TEST(pointer_access, test) {
  // create a JSON value with different types
  json json_types = {
      {"boolean", true},
      {"number",
       {{"integer", 42}, {"unsigned", 42u}, {"floating-point", 17.23}}},
      {"string", "Hello, world!"},
      {"array", {1, 2, 3, 4, 5}},
      {"null", nullptr}};

  {
    using test_type = json::object_t;
    json value = {{"one", 1}, {"two", 2}};

    // check if pointers are returned correctly
    test_type *p1 = value.get_ptr<test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<test_type *>());
    EXPECT_TRUE(*p1 == value.get<test_type>());

    const test_type *p2 = value.get_ptr<const test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *>());
    EXPECT_TRUE(*p2 == value.get<test_type>());

    const test_type *const p3 = value.get_ptr<const test_type *const>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *const>());
    EXPECT_TRUE(*p3 == value.get<test_type>());

    // check if null pointers are returned correctly
    EXPECT_TRUE(value.get_ptr<json::object_t *>() != nullptr);
    EXPECT_TRUE(value.get_ptr<json::array_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::string_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::boolean_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::number_integer_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::number_unsigned_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::number_float_t *>() == nullptr);
  }

  {
    using test_type = const json::object_t;
    const json value = {{"one", 1}, {"two", 2}};

    // check if pointers are returned correctly
    test_type *p1 = value.get_ptr<test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<test_type *>());
    EXPECT_TRUE(*p1 == value.get<test_type>());

    const test_type *p2 = value.get_ptr<const test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *>());
    EXPECT_TRUE(*p2 == value.get<test_type>());

    const test_type *const p3 = value.get_ptr<const test_type *const>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *const>());
    EXPECT_TRUE(*p3 == value.get<test_type>());

    // check if null pointers are returned correctly
    EXPECT_TRUE(value.get_ptr<const json::object_t *>() != nullptr);
    EXPECT_TRUE(value.get_ptr<const json::array_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::string_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::boolean_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::number_integer_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::number_unsigned_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::number_float_t *>() == nullptr);
  }

  {
    using test_type = json::array_t;
    json value = {1, 2, 3, 4};

    // check if pointers are returned correctly
    test_type *p1 = value.get_ptr<test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<test_type *>());
    EXPECT_TRUE(*p1 == value.get<test_type>());

    const test_type *p2 = value.get_ptr<const test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *>());
    EXPECT_TRUE(*p2 == value.get<test_type>());

    const test_type *const p3 = value.get_ptr<const test_type *const>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *const>());
    EXPECT_TRUE(*p3 == value.get<test_type>());

    // check if null pointers are returned correctly
    EXPECT_TRUE(value.get_ptr<json::object_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::array_t *>() != nullptr);
    EXPECT_TRUE(value.get_ptr<json::string_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::boolean_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::number_integer_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::number_unsigned_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::number_float_t *>() == nullptr);
  }

  {
    using test_type = const json::array_t;
    const json value = {1, 2, 3, 4};

    // check if pointers are returned correctly
    test_type *p1 = value.get_ptr<test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<test_type *>());
    EXPECT_TRUE(*p1 == value.get<test_type>());

    const test_type *p2 = value.get_ptr<const test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *>());
    EXPECT_TRUE(*p2 == value.get<test_type>());

    const test_type *const p3 = value.get_ptr<const test_type *const>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *const>());
    EXPECT_TRUE(*p3 == value.get<test_type>());

    // check if null pointers are returned correctly
    EXPECT_TRUE(value.get_ptr<const json::object_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::array_t *>() != nullptr);
    EXPECT_TRUE(value.get_ptr<const json::string_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::boolean_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::number_integer_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::number_unsigned_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::number_float_t *>() == nullptr);
  }

  {
    using test_type = json::string_t;
    json value = "hello";

    // check if pointers are returned correctly
    test_type *p1 = value.get_ptr<test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<test_type *>());
    EXPECT_TRUE(*p1 == value.get<test_type>());

    const test_type *p2 = value.get_ptr<const test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *>());
    EXPECT_TRUE(*p2 == value.get<test_type>());

    const test_type *const p3 = value.get_ptr<const test_type *const>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *const>());
    EXPECT_TRUE(*p3 == value.get<test_type>());

    // check if null pointers are returned correctly
    EXPECT_TRUE(value.get_ptr<json::object_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::array_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::string_t *>() != nullptr);
    EXPECT_TRUE(value.get_ptr<json::boolean_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::number_integer_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::number_unsigned_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::number_float_t *>() == nullptr);
  }

  {
    using test_type = const json::string_t;
    const json value = "hello";

    // check if pointers are returned correctly
    test_type *p1 = value.get_ptr<test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<test_type *>());
    EXPECT_TRUE(*p1 == value.get<test_type>());

    const test_type *p2 = value.get_ptr<const test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *>());
    EXPECT_TRUE(*p2 == value.get<test_type>());

    const test_type *const p3 = value.get_ptr<const test_type *const>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *const>());
    EXPECT_TRUE(*p3 == value.get<test_type>());

    // check if null pointers are returned correctly
    EXPECT_TRUE(value.get_ptr<const json::object_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::array_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::string_t *>() != nullptr);
    EXPECT_TRUE(value.get_ptr<const json::boolean_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::number_integer_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::number_unsigned_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::number_float_t *>() == nullptr);
  }

  {
    using test_type = json::boolean_t;
    json value = false;

    // check if pointers are returned correctly
    test_type *p1 = value.get_ptr<test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<test_type *>());
    EXPECT_TRUE(*p1 == value.get<test_type>());

    const test_type *p2 = value.get_ptr<const test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *>());
    EXPECT_TRUE(*p2 == value.get<test_type>());

    const test_type *const p3 = value.get_ptr<const test_type *const>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *const>());
    EXPECT_TRUE(*p3 == value.get<test_type>());

    // check if null pointers are returned correctly
    EXPECT_TRUE(value.get_ptr<json::object_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::array_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::string_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::boolean_t *>() != nullptr);
    EXPECT_TRUE(value.get_ptr<json::number_integer_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::number_unsigned_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::number_float_t *>() == nullptr);
  }

  {
    using test_type = const json::boolean_t;
    const json value = false;

    // check if pointers are returned correctly
    test_type *p1 = value.get_ptr<test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<test_type *>());
    // EXPECT_TRUE(*p1 == value.get<test_type>());

    const test_type *p2 = value.get_ptr<const test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *>());
    EXPECT_TRUE(*p2 == value.get<test_type>());

    const test_type *const p3 = value.get_ptr<const test_type *const>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *const>());
    EXPECT_TRUE(*p3 == value.get<test_type>());

    // check if null pointers are returned correctly
    EXPECT_TRUE(value.get_ptr<const json::object_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::array_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::string_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::boolean_t *>() != nullptr);
    EXPECT_TRUE(value.get_ptr<const json::number_integer_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::number_unsigned_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::number_float_t *>() == nullptr);
  }

  {
    using test_type = json::number_integer_t;
    json value = 23;

    // check if pointers are returned correctly
    test_type *p1 = value.get_ptr<test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<test_type *>());
    EXPECT_TRUE(*p1 == value.get<test_type>());

    const test_type *p2 = value.get_ptr<const test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *>());
    EXPECT_TRUE(*p2 == value.get<test_type>());

    const test_type *const p3 = value.get_ptr<const test_type *const>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *const>());
    EXPECT_TRUE(*p3 == value.get<test_type>());

    // check if null pointers are returned correctly
    EXPECT_TRUE(value.get_ptr<json::object_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::array_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::string_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::boolean_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::number_integer_t *>() != nullptr);
    EXPECT_TRUE(value.get_ptr<json::number_unsigned_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::number_float_t *>() == nullptr);
  }

  {
    using test_type = const json::number_integer_t;
    const json value = 23;

    // check if pointers are returned correctly
    test_type *p1 = value.get_ptr<test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<test_type *>());
    EXPECT_TRUE(*p1 == value.get<test_type>());

    const test_type *p2 = value.get_ptr<const test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *>());
    EXPECT_TRUE(*p2 == value.get<test_type>());

    const test_type *const p3 = value.get_ptr<const test_type *const>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *const>());
    EXPECT_TRUE(*p3 == value.get<test_type>());

    // check if null pointers are returned correctly
    EXPECT_TRUE(value.get_ptr<const json::object_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::array_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::string_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::boolean_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::number_integer_t *>() != nullptr);
    EXPECT_TRUE(value.get_ptr<const json::number_unsigned_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::number_float_t *>() == nullptr);
  }

  {
    using test_type = json::number_unsigned_t;
    json value = 23u;

    // check if pointers are returned correctly
    test_type *p1 = value.get_ptr<test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<test_type *>());
    EXPECT_TRUE(*p1 == value.get<test_type>());

    const test_type *p2 = value.get_ptr<const test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *>());
    EXPECT_TRUE(*p2 == value.get<test_type>());

    const test_type *const p3 = value.get_ptr<const test_type *const>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *const>());
    EXPECT_TRUE(*p3 == value.get<test_type>());

    // check if null pointers are returned correctly
    EXPECT_TRUE(value.get_ptr<json::object_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::array_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::string_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::boolean_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::number_integer_t *>() != nullptr);
    EXPECT_TRUE(value.get_ptr<json::number_unsigned_t *>() != nullptr);
    EXPECT_TRUE(value.get_ptr<json::number_float_t *>() == nullptr);
  }

  {
    using test_type = const json::number_unsigned_t;
    const json value = 23u;

    // check if pointers are returned correctly
    test_type *p1 = value.get_ptr<test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<test_type *>());
    EXPECT_TRUE(*p1 == value.get<test_type>());

    const test_type *p2 = value.get_ptr<const test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *>());
    EXPECT_TRUE(*p2 == value.get<test_type>());

    const test_type *const p3 = value.get_ptr<const test_type *const>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *const>());
    EXPECT_TRUE(*p3 == value.get<test_type>());

    // check if null pointers are returned correctly
    EXPECT_TRUE(value.get_ptr<const json::object_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::array_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::string_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::boolean_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::number_integer_t *>() != nullptr);
    EXPECT_TRUE(value.get_ptr<const json::number_unsigned_t *>() != nullptr);
    EXPECT_TRUE(value.get_ptr<const json::number_float_t *>() == nullptr);
  }

  {
    using test_type = json::number_float_t;
    json value = 42.23;

    // check if pointers are returned correctly
    test_type *p1 = value.get_ptr<test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<test_type *>());
    EXPECT_DOUBLE_EQ(*p1, (value.get<test_type>()));

    const test_type *p2 = value.get_ptr<const test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *>());
    EXPECT_DOUBLE_EQ(*p2, (value.get<test_type>()));

    const test_type *const p3 = value.get_ptr<const test_type *const>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *const>());
    EXPECT_DOUBLE_EQ(*p3, (value.get<test_type>()));

    // check if null pointers are returned correctly
    EXPECT_TRUE(value.get_ptr<json::object_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::array_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::string_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::boolean_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::number_integer_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::number_unsigned_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<json::number_float_t *>() != nullptr);
  }

  {
    using test_type = const json::number_float_t;
    const json value = 42.23;

    // check if pointers are returned correctly
    test_type *p1 = value.get_ptr<test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<test_type *>());
    EXPECT_DOUBLE_EQ(*p1, (value.get<test_type>()));

    const test_type *p2 = value.get_ptr<const test_type *>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *>());
    EXPECT_DOUBLE_EQ(*p2, (value.get<test_type>()));

    const test_type *const p3 = value.get_ptr<const test_type *const>();
    EXPECT_TRUE(p1 == value.get_ptr<const test_type *const>());
    EXPECT_DOUBLE_EQ(*p3, (value.get<test_type>()));

    // check if null pointers are returned correctly
    EXPECT_TRUE(value.get_ptr<const json::object_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::array_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::string_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::boolean_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::number_integer_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::number_unsigned_t *>() == nullptr);
    EXPECT_TRUE(value.get_ptr<const json::number_float_t *>() != nullptr);
  }
}
