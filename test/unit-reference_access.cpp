#include "helper.hpp"
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
  EXPECT_NO_THROW(value.get_ref<json::object_t &>());
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
  EXPECT_THROW(
      {
        try {
          value.get_ref<json::string_t &>();
        } catch (const json::type_error &e) {
          EXPECT_STREQ("[json.exception.type_error.303] incompatible "
                       "ReferenceType for get_ref, actual type is object",
                       e.what());
          throw;
        }
      },
      json::type_error);
  EXPECT_THROW(
      {
        try {
          value.get_ref<json::boolean_t &>();
        } catch (const json::type_error &e) {
          EXPECT_STREQ("[json.exception.type_error.303] incompatible "
                       "ReferenceType for get_ref, actual type is object",
                       e.what());
          throw;
        }
      },
      json::type_error);
  EXPECT_THROW(
      {
        try {
          value.get_ref<json::number_integer_t &>();
        } catch (const json::type_error &e) {
          EXPECT_STREQ("[json.exception.type_error.303] incompatible "
                       "ReferenceType for get_ref, actual type is object",
                       e.what());
          throw;
        }
      },
      json::type_error);
  EXPECT_THROW(
      {
        try {
          value.get_ref<json::number_unsigned_t &>();
        } catch (const json::type_error &e) {
          EXPECT_STREQ("[json.exception.type_error.303] incompatible "
                       "ReferenceType for get_ref, actual type is object",
                       e.what());
          throw;
        }
      },
      json::type_error);
  EXPECT_THROW(
      {
        try {
          value.get_ref<json::boolean_t &>();
        } catch (const json::type_error &e) {
          EXPECT_STREQ("[json.exception.type_error.303] incompatible "
                       "ReferenceType for get_ref, actual type is object",
                       e.what());
          throw;
        }
      },
      json::type_error);
  HELPER_THROW(value.get_ref<json::boolean_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is object");
}

TEST(JSON_Reference_Access, Reference_Access_To_Const_Object_t) {
  using test_type = json::object_t;
  const json value = {{"one", 1}, {"two", 2}};

  // check if references are returned correctly
  const test_type &p2 = value.get_ref<const test_type &>();
  EXPECT_EQ(&p2, value.get_ptr<const test_type *>());
  EXPECT_EQ(p2, value.get<test_type>());
}

TEST(JSON_Reference_Access, Reference_Access_To_Array_t) {
  using test_type = json::array_t;
  json value = {1, 2, 3, 4};

  // check if references are returned correctly
  test_type &p1 = value.get_ref<test_type &>();
  EXPECT_EQ(&p1, value.get_ptr<test_type *>());
  EXPECT_EQ(p1, value.get<test_type>());

  const test_type &p2 = value.get_ref<const test_type &>();
  EXPECT_EQ(&p2, value.get_ptr<const test_type *>());
  EXPECT_EQ(p2, value.get<test_type>());
  EXPECT_NO_THROW(value.get_ref<json::array_t &>());
  HELPER_THROW(value.get_ref<json::object_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is array");
  HELPER_THROW(value.get_ref<json::string_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is array");
  HELPER_THROW(value.get_ref<json::boolean_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is array");
  HELPER_THROW(value.get_ref<json::number_integer_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is array");
  HELPER_THROW(value.get_ref<json::number_unsigned_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is array");
  HELPER_THROW(value.get_ref<json::number_float_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is array");
}
TEST(JSON_Reference_Access, Reference_Access_To_String_t) {
  using test_type = json::string_t;
  json value = "hello";

  // check if references are returned correctly
  test_type &p1 = value.get_ref<test_type &>();
  EXPECT_EQ(&p1, value.get_ptr<test_type *>());
  EXPECT_EQ(p1, value.get<test_type>());

  const test_type &p2 = value.get_ref<const test_type &>();
  EXPECT_EQ(&p2, value.get_ptr<const test_type *>());
  EXPECT_EQ(p2, value.get<test_type>());
  EXPECT_NO_THROW(value.get_ref<json::string_t &>());
  HELPER_THROW(value.get_ref<json::object_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is string");
  HELPER_THROW(value.get_ref<json::array_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is string");
  HELPER_THROW(value.get_ref<json::boolean_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is string");
  HELPER_THROW(value.get_ref<json::number_integer_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is string");
  HELPER_THROW(value.get_ref<json::number_unsigned_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is string");
  HELPER_THROW(value.get_ref<json::number_float_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is string");
}
TEST(JSON_Reference_Access, Reference_Access_To_Boolean_t) {
  using test_type = json::boolean_t;
  json value = false;

  // check if references are returned correctly
  test_type &p1 = value.get_ref<test_type &>();
  EXPECT_EQ(&p1, value.get_ptr<test_type *>());
  EXPECT_EQ(p1, value.get<test_type>());

  const test_type &p2 = value.get_ref<const test_type &>();
  EXPECT_EQ(&p2, value.get_ptr<const test_type *>());
  EXPECT_EQ(p2, value.get<test_type>());
  EXPECT_NO_THROW(value.get_ref<json::boolean_t &>());
  HELPER_THROW(value.get_ref<json::object_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is boolean");
  HELPER_THROW(value.get_ref<json::array_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is boolean");
  HELPER_THROW(value.get_ref<json::string_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is boolean");
  HELPER_THROW(value.get_ref<json::number_integer_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is boolean");
  HELPER_THROW(value.get_ref<json::number_unsigned_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is boolean");
  HELPER_THROW(value.get_ref<json::number_float_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is boolean");
}
TEST(JSON_Reference_Access, Reference_Access_To_Number_Integer_t) {
  using test_type = json::number_integer_t;
  json value = -100;

  // check if references are returned correctly
  test_type &p1 = value.get_ref<test_type &>();
  EXPECT_EQ(&p1, value.get_ptr<test_type *>());
  EXPECT_EQ(p1, value.get<test_type>());

  const test_type &p2 = value.get_ref<const test_type &>();
  EXPECT_EQ(&p2, value.get_ptr<const test_type *>());
  EXPECT_EQ(p2, value.get<test_type>());
  EXPECT_NO_THROW(value.get_ref<json::number_integer_t &>());
  HELPER_THROW(value.get_ref<json::object_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is number");
  HELPER_THROW(value.get_ref<json::array_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is number");
  HELPER_THROW(value.get_ref<json::string_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is number");
  HELPER_THROW(value.get_ref<json::boolean_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is number");
  HELPER_THROW(value.get_ref<json::number_unsigned_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is number");
  HELPER_THROW(value.get_ref<json::number_float_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is number");
}
TEST(JSON_Reference_Access, Reference_Access_To_Number_Unsinged_Integer_t) {
  using test_type = json::number_unsigned_t;
  json value = 100u;

  // check if references are returned correctly
  test_type &p1 = value.get_ref<test_type &>();
  EXPECT_EQ(&p1, value.get_ptr<test_type *>());
  EXPECT_EQ(p1, value.get<test_type>());

  const test_type &p2 = value.get_ref<const test_type &>();
  EXPECT_EQ(&p2, value.get_ptr<const test_type *>());
  EXPECT_EQ(p2, value.get<test_type>());
  EXPECT_NO_THROW(value.get_ref<json::number_unsigned_t &>());
  HELPER_THROW(value.get_ref<json::object_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is number");
  HELPER_THROW(value.get_ref<json::array_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is number");
  HELPER_THROW(value.get_ref<json::string_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is number");
  HELPER_THROW(value.get_ref<json::boolean_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is number");
  HELPER_THROW(value.get_ref<json::number_float_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is number");
}
TEST(JSON_Reference_Access, Reference_Access_To_Number_Float_t) {
  using test_type = json::number_float_t;
  json value = 42.23;

  // check if references are returned correctly
  test_type &p1 = value.get_ref<test_type &>();
  EXPECT_EQ(&p1, value.get_ptr<test_type *>());
  EXPECT_EQ(p1, value.get<test_type>());

  const test_type &p2 = value.get_ref<const test_type &>();
  EXPECT_EQ(&p2, value.get_ptr<const test_type *>());
  EXPECT_EQ(p2, value.get<test_type>());
  EXPECT_NO_THROW(value.get_ref<json::number_float_t &>());
  HELPER_THROW(value.get_ref<json::object_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is number");
  HELPER_THROW(value.get_ref<json::array_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is number");
  HELPER_THROW(value.get_ref<json::string_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is number");
  HELPER_THROW(value.get_ref<json::boolean_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is number");
  HELPER_THROW(value.get_ref<json::number_unsigned_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is number");
  HELPER_THROW(value.get_ref<json::number_integer_t &>(), json::type_error,
               "[json.exception.type_error.303] incompatible ReferenceType for "
               "get_ref, actual type is number");
}
