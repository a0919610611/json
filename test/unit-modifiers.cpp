#include "helper.hpp"
#include "json.hpp"
#include "gtest/gtest.h"

using json = nlohmann::json;

TEST(modifiers, test) {
  {{json j = true;
  json k = j;

  j.clear();
  EXPECT_TRUE(j == json(json::value_t::boolean));
  EXPECT_TRUE(j == json(k.type()));
}

{
  json j = "hello world";
  json k = j;

  j.clear();
  EXPECT_TRUE(j == json(json::value_t::string));
  EXPECT_TRUE(j == json(k.type()));
}

{{json j = json::array();
json k = j;

j.clear();
EXPECT_TRUE(j.empty());
EXPECT_TRUE(j == json(json::value_t::array));
EXPECT_TRUE(j == json(k.type()));
}

{
  json j = {1, 2, 3};
  json k = j;

  j.clear();
  EXPECT_TRUE(j.empty());
  EXPECT_TRUE(j == json(json::value_t::array));
  EXPECT_TRUE(j == json(k.type()));
}
}

{{json j = json::object();
json k = j;

j.clear();
EXPECT_TRUE(j.empty());
EXPECT_TRUE(j == json(json::value_t::object));
EXPECT_TRUE(j == json(k.type()));
}

{
  json j = {{"one", 1}, {"two", 2}, {"three", 3}};
  json k = j;

  j.clear();
  EXPECT_TRUE(j.empty());
  EXPECT_TRUE(j == json(json::value_t::object));
  EXPECT_TRUE(j == json(k.type()));
}
}

{
  json j = 23;
  json k = j;

  j.clear();
  EXPECT_TRUE(j == json(json::value_t::number_integer));
  EXPECT_TRUE(j == json(k.type()));
}

{
  json j = 23u;
  json k = j;

  j.clear();
  EXPECT_TRUE(j == json(json::value_t::number_integer));
  EXPECT_TRUE(j == json(k.type()));
}

{
  json j = 23.42;
  json k = j;

  j.clear();
  EXPECT_TRUE(j == json(json::value_t::number_float));
  EXPECT_TRUE(j == json(k.type()));
}

{
  json j = nullptr;
  json k = j;

  j.clear();
  EXPECT_TRUE(j == json(json::value_t::null));
  EXPECT_TRUE(j == json(k.type()));
}
}

{{{{json j;
j.push_back(1);
j.push_back(2);
EXPECT_TRUE(j.type() == json::value_t::array);
EXPECT_TRUE(j == json({1, 2}));
}

{
  json j = {1, 2, 3};
  j.push_back("Hello");
  EXPECT_TRUE(j.type() == json::value_t::array);
  EXPECT_TRUE(j == json({1, 2, 3, "Hello"}));
}

{
  json j = 1;
  HELPER_THROW(j.push_back("Hello"), json::type_error,
               "[json.exception.type_error."
               "308] cannot use push_back() "
               "with number");
}
}

{
  {
    json j;
    json k(1);
    j.push_back(k);
    j.push_back(k);
    EXPECT_TRUE(j.type() == json::value_t::array);
    EXPECT_TRUE(j == json({1, 1}));
  }

  {
    json j = {1, 2, 3};
    json k("Hello");
    j.push_back(k);
    EXPECT_TRUE(j.type() == json::value_t::array);
    EXPECT_TRUE(j == json({1, 2, 3, "Hello"}));
  }

  {
    json j = 1;
    json k("Hello");
    HELPER_THROW(j.push_back(k), json::type_error,
                 "[json.exception.type_error.308] "
                 "cannot use push_back() with "
                 "number");
  }
}
}

{{json j;
j.push_back(json::object_t::value_type({"one", 1}));
j.push_back(json::object_t::value_type({"two", 2}));
EXPECT_TRUE(j.type() == json::value_t::object);
EXPECT_TRUE(j.size() == 2);
EXPECT_TRUE(j["one"] == json(1));
EXPECT_TRUE(j["two"] == json(2));
}

{
  json j(json::value_t::object);
  j.push_back(json::object_t::value_type({"one", 1}));
  j.push_back(json::object_t::value_type({"two", 2}));
  EXPECT_TRUE(j.size() == 2);
  EXPECT_TRUE(j["one"] == json(1));
  EXPECT_TRUE(j["two"] == json(2));
}

{
  json j = 1;
  json k("Hello");
  HELPER_THROW(j.push_back(json::object_t::value_type({"one", 1})),
               json::type_error, "[json.exception.type_error.308] cannot use "
                                 "push_back() with number");
}
}

{
  {
    json j;
    j.push_back({"foo", "bar"});
    EXPECT_TRUE(j == json::array({{"foo", "bar"}}));

    json k;
    k.push_back({1, 2, 3});
    EXPECT_TRUE(k == json::array({{1, 2, 3}}));
  }

  {
    json j = {1, 2, 3};
    j.push_back({"foo", "bar"});
    EXPECT_TRUE(j == json({1, 2, 3, {"foo", "bar"}}));

    json k = {1, 2, 3};
    k.push_back({1, 2, 3});
    EXPECT_TRUE(k == json({1, 2, 3, {1, 2, 3}}));
  }

  {
    json j = {{"key1", 1}};
    j.push_back({"key2", "bar"});
    EXPECT_TRUE(j == json({{"key1", 1}, {"key2", "bar"}}));

    // invalid values (no string/val pair)
    HELPER_THROW(j.push_back({1}), json::type_error,
                 "[json.exception.type_error.308] "
                 "cannot use push_back() with "
                 "object");
    HELPER_THROW(j.push_back({1, 2}), json::type_error,
                 "[json.exception.type_error.308]"
                 " cannot use push_back() with "
                 "object");
    HELPER_THROW(j.push_back({1, 2, 3, 4}), json::type_error,
                 "[json.exception.type_"
                 "error.308] cannot use "
                 "push_back() with object");
  }
}
}

{{{json j;
j.emplace_back(1);
j.emplace_back(2);
EXPECT_TRUE(j.type() == json::value_t::array);
EXPECT_TRUE(j == json({1, 2}));
}

{
  json j = {1, 2, 3};
  j.emplace_back("Hello");
  EXPECT_TRUE(j.type() == json::value_t::array);
  EXPECT_TRUE(j == json({1, 2, 3, "Hello"}));
}

{
  json j;
  j.emplace_back(3, "foo");
  EXPECT_TRUE(j.type() == json::value_t::array);
  EXPECT_TRUE(j == json({{"foo", "foo", "foo"}}));
}
}

{
  json j = 1;
  HELPER_THROW(j.emplace_back("Hello"), json::type_error,
               "[json.exception.type_error."
               "311] cannot use "
               "emplace_back() with number");
}
}

{{{// start with a null value
   json j;

// add a new key
auto res1 = j.emplace("foo", "bar");
EXPECT_TRUE(res1.second == true);
EXPECT_TRUE(*res1.first == "bar");

// the null value is changed to an object
EXPECT_TRUE(j.type() == json::value_t::object);

// add a new key
auto res2 = j.emplace("baz", "bam");
EXPECT_TRUE(res2.second == true);
EXPECT_TRUE(*res2.first == "bam");

// we try to insert at given key - no change
auto res3 = j.emplace("baz", "bad");
EXPECT_TRUE(res3.second == false);
EXPECT_TRUE(*res3.first == "bam");

// the final object
EXPECT_TRUE(j == json({{"baz", "bam"}, {"foo", "bar"}}));
}

{
  // start with an object
  json j = {{"foo", "bar"}};

  // add a new key
  auto res1 = j.emplace("baz", "bam");
  EXPECT_TRUE(res1.second == true);
  EXPECT_TRUE(*res1.first == "bam");

  // add an existing key
  auto res2 = j.emplace("foo", "bad");
  EXPECT_TRUE(res2.second == false);
  EXPECT_TRUE(*res2.first == "bar");

  // check final object
  EXPECT_TRUE(j == json({{"baz", "bam"}, {"foo", "bar"}}));
}
}

{
  json j = 1;
  HELPER_THROW(
      j.emplace("foo", "bar"), json::type_error,
      "[json.exception.type_error.311] cannot use emplace() with number");
}
}

{{{{json j;
j += 1;
j += 2;
EXPECT_TRUE(j.type() == json::value_t::array);
EXPECT_TRUE(j == json({1, 2}));
}

{
  json j = {1, 2, 3};
  j += "Hello";
  EXPECT_TRUE(j.type() == json::value_t::array);
  EXPECT_TRUE(j == json({1, 2, 3, "Hello"}));
}

{
  json j = 1;
  HELPER_THROW(j += "Hello", json::type_error,
               "[json.exception.type_error.308] "
               "cannot use push_back() with number");
}
}

{
  {
    json j;
    json k(1);
    j += k;
    j += k;
    EXPECT_TRUE(j.type() == json::value_t::array);
    EXPECT_TRUE(j == json({1, 1}));
  }

  {
    json j = {1, 2, 3};
    json k("Hello");
    j += k;
    EXPECT_TRUE(j.type() == json::value_t::array);
    EXPECT_TRUE(j == json({1, 2, 3, "Hello"}));
  }

  {
    json j = 1;
    json k("Hello");
    HELPER_THROW(j += k, json::type_error,
                 "[json.exception.type_error.308] cannot "
                 "use push_back() with number");
  }
}
}

{{json j;
j += json::object_t::value_type({"one", 1});
j += json::object_t::value_type({"two", 2});
EXPECT_TRUE(j.type() == json::value_t::object);
EXPECT_TRUE(j.size() == 2);
EXPECT_TRUE(j["one"] == json(1));
EXPECT_TRUE(j["two"] == json(2));
}

{
  json j(json::value_t::object);
  j += json::object_t::value_type({"one", 1});
  j += json::object_t::value_type({"two", 2});
  EXPECT_TRUE(j.size() == 2);
  EXPECT_TRUE(j["one"] == json(1));
  EXPECT_TRUE(j["two"] == json(2));
}

{
  json j = 1;
  json k("Hello");
  HELPER_THROW(j += json::object_t::value_type({"one", 1}), json::type_error,
               "[json.exception.type_error.308] cannot use "
               "push_back() with number");
}
}

{
  {
    json j;
    j += {"foo", "bar"};
    EXPECT_TRUE(j == json::array({{"foo", "bar"}}));

    json k;
    k += {1, 2, 3};
    EXPECT_TRUE(k == json::array({{1, 2, 3}}));
  }

  {
    json j = {1, 2, 3};
    j += {"foo", "bar"};
    EXPECT_TRUE(j == json({1, 2, 3, {"foo", "bar"}}));

    json k = {1, 2, 3};
    k += {1, 2, 3};
    EXPECT_TRUE(k == json({1, 2, 3, {1, 2, 3}}));
  }

  {
    json j = {{"key1", 1}};
    j += {"key2", "bar"};
    EXPECT_TRUE(j == json({{"key1", 1}, {"key2", "bar"}}));

    json k = {{"key1", 1}};
    HELPER_THROW((k += {1, 2, 3, 4}), json::type_error,
                 "[json.exception.type_error.308]"
                 " cannot use push_back() with "
                 "object");
  }
}
}

{
  json j_array = {1, 2, 3, 4};
  json j_value = 5;

  {{json j_array = {1, 2, 3, 4};
  json j_value = 5;
  auto it = j_array.insert(j_array.begin(), j_value);
  EXPECT_TRUE(j_array.size() == 5);
  EXPECT_TRUE(*it == j_value);
  EXPECT_TRUE(j_array.begin() == it);
  EXPECT_TRUE(j_array == json({5, 1, 2, 3, 4}));
}

{
  json j_array = {1, 2, 3, 4};
  json j_value = 5;
  auto it = j_array.insert(j_array.begin() + 2, j_value);
  EXPECT_TRUE(j_array.size() == 5);
  EXPECT_TRUE(*it == j_value);
  EXPECT_TRUE((it - j_array.begin()) == 2);
  EXPECT_TRUE(j_array == json({1, 2, 5, 3, 4}));
}

{
  json j_array = {1, 2, 3, 4};
  json j_value = 5;
  auto it = j_array.insert(j_array.end(), j_value);
  EXPECT_TRUE(j_array.size() == 5);
  EXPECT_TRUE(*it == j_value);
  EXPECT_TRUE((j_array.end() - it) == 1);
  EXPECT_TRUE(j_array == json({1, 2, 3, 4, 5}));
}
}

{{json j_array = {1, 2, 3, 4};
json j_value = 5;
auto it = j_array.insert(j_array.begin(), 5);
EXPECT_TRUE(j_array.size() == 5);
EXPECT_TRUE(*it == j_value);
EXPECT_TRUE(j_array.begin() == it);
EXPECT_TRUE(j_array == json({5, 1, 2, 3, 4}));
}

{
  json j_array = {1, 2, 3, 4};
  json j_value = 5;
  auto it = j_array.insert(j_array.begin() + 2, 5);
  EXPECT_TRUE(j_array.size() == 5);
  EXPECT_TRUE(*it == j_value);
  EXPECT_TRUE((it - j_array.begin()) == 2);
  EXPECT_TRUE(j_array == json({1, 2, 5, 3, 4}));
}

{
  json j_array = {1, 2, 3, 4};
  json j_value = 5;
  auto it = j_array.insert(j_array.end(), 5);
  EXPECT_TRUE(j_array.size() == 5);
  EXPECT_TRUE(*it == j_value);
  EXPECT_TRUE((j_array.end() - it) == 1);
  EXPECT_TRUE(j_array == json({1, 2, 3, 4, 5}));
}
}

{{json j_array = {1, 2, 3, 4};
json j_value = 5;
auto it = j_array.insert(j_array.begin(), 3, 5);
EXPECT_TRUE(j_array.size() == 7);
EXPECT_TRUE(*it == j_value);
EXPECT_TRUE(j_array.begin() == it);
EXPECT_TRUE(j_array == json({5, 5, 5, 1, 2, 3, 4}));
}

{
  json j_array = {1, 2, 3, 4};
  json j_value = 5;
  auto it = j_array.insert(j_array.begin() + 2, 3, 5);
  EXPECT_TRUE(j_array.size() == 7);
  EXPECT_TRUE(*it == j_value);
  EXPECT_TRUE((it - j_array.begin()) == 2);
  EXPECT_TRUE(j_array == json({1, 2, 5, 5, 5, 3, 4}));
}

{
  json j_array = {1, 2, 3, 4};
  json j_value = 5;
  auto it = j_array.insert(j_array.end(), 3, 5);
  EXPECT_TRUE(j_array.size() == 7);
  EXPECT_TRUE(*it == j_value);
  EXPECT_TRUE((j_array.end() - it) == 3);
  EXPECT_TRUE(j_array == json({1, 2, 3, 4, 5, 5, 5}));
}

{
  json j_array = {1, 2, 3, 4};
  json j_value = 5;
  auto it = j_array.insert(j_array.end(), 0, 5);
  EXPECT_TRUE(j_array.size() == 4);
  // the returned iterator points to the first inserted element;
  // there were 4 elements, so it should point to the 5th
  EXPECT_TRUE(it == j_array.begin() + 4);
  EXPECT_TRUE(j_array == json({1, 2, 3, 4}));
}
}

{
  json j_other_array = {"first", "second"};

  {
    json j_array = {1, 2, 3, 4};
    json j_value = 5;
    auto it = j_array.insert(j_array.end(), j_other_array.begin(),
                             j_other_array.end());
    EXPECT_TRUE(j_array.size() == 6);
    EXPECT_TRUE(*it == *j_other_array.begin());
    EXPECT_TRUE((j_array.end() - it) == 2);
    EXPECT_TRUE(j_array == json({1, 2, 3, 4, "first", "second"}));
  }

  {
    json j_array = {1, 2, 3, 4};
    json j_value = 5;
    auto it = j_array.insert(j_array.end(), j_other_array.begin(),
                             j_other_array.begin());
    EXPECT_TRUE(j_array.size() == 4);
    EXPECT_TRUE(it == j_array.end());
    EXPECT_TRUE(j_array == json({1, 2, 3, 4}));
  }

  {
    json j_other_array2 = {"first", "second"};

    json j_array = {1, 2, 3, 4};
    json j_value = 5;
    HELPER_THROW(
        j_array.insert(j_array.end(), j_array.begin(), j_array.end()),
        json::invalid_iterator,
        "[json.exception.invalid_iterator.211] passed iterators may not "
        "belong to container");
    HELPER_THROW(j_array.insert(j_array.end(), j_other_array.begin(),
                                j_other_array2.end()),
                 json::invalid_iterator,
                 "[json.exception.invalid_iterator.210] iterators do not fit");
  }
}

{
  json j_object1 = {{"one", "eins"}, {"two", "zwei"}};
  json j_object2 = {{"eleven", "elf"}, {"seventeen", "siebzehn"}};

  {
    json j_object1 = {{"one", "eins"}, {"two", "zwei"}};
    json j_object2 = {{"eleven", "elf"}, {"seventeen", "siebzehn"}};
    j_object1.insert(j_object2.begin(), j_object2.end());
    EXPECT_TRUE(j_object1.size() == 4);
  }

  {
    json j_object1 = {{"one", "eins"}, {"two", "zwei"}};
    json j_object2 = {{"eleven", "elf"}, {"seventeen", "siebzehn"}};
    j_object1.insert(j_object2.begin(), j_object2.begin());
    EXPECT_TRUE(j_object1.size() == 2);
  }

  {
    json j_other_array2 = {"first", "second"};

    HELPER_THROW(
        j_array.insert(j_object2.begin(), j_object2.end()), json::type_error,
        "[json.exception.type_error.309] cannot use insert() with array");
    HELPER_THROW(j_object1.insert(j_object1.begin(), j_object2.end()),
                 json::invalid_iterator,
                 "[json.exception.invalid_iterator.210] iterators do not fit");
    HELPER_THROW(j_object1.insert(j_array.begin(), j_array.end()),
                 json::invalid_iterator,
                 "[json.exception.invalid_iterator.202] iterators "
                 "first and last must point to objects");
  }
}

{{auto it = j_array.insert(j_array.begin(), {7, 8, 9});
EXPECT_TRUE(j_array.size() == 7);
EXPECT_TRUE(*it == json(7));
EXPECT_TRUE(j_array.begin() == it);
EXPECT_TRUE(j_array == json({7, 8, 9, 1, 2, 3, 4}));
}

{
  json j_array = {1, 2, 3, 4};
  json j_value = 5;
  auto it = j_array.insert(j_array.begin() + 2, {7, 8, 9});
  EXPECT_TRUE(j_array.size() == 7);
  EXPECT_TRUE(*it == json(7));
  EXPECT_TRUE((it - j_array.begin()) == 2);
  EXPECT_TRUE(j_array == json({1, 2, 7, 8, 9, 3, 4}));
}

{
  json j_array = {1, 2, 3, 4};
  json j_value = 5;
  auto it = j_array.insert(j_array.end(), {7, 8, 9});
  EXPECT_TRUE(j_array.size() == 7);
  EXPECT_TRUE(*it == json(7));
  EXPECT_TRUE((j_array.end() - it) == 3);
  EXPECT_TRUE(j_array == json({1, 2, 3, 4, 7, 8, 9}));
}
}

{
  json j_array = {1, 2, 3, 4};
  json j_value = 5;
  // pass iterator to a different array
  json j_another_array = {1, 2};
  json j_yet_another_array = {"first", "second"};

  HELPER_THROW(j_array.insert(j_another_array.end(), 10),
               json::invalid_iterator,
               "[json.exception.invalid_iterator.202] iterator does "
               "not fit current value");
  HELPER_THROW(j_array.insert(j_another_array.end(), j_value),
               json::invalid_iterator,
               "[json.exception.invalid_iterator.202] iterator does "
               "not fit current value");
  HELPER_THROW(j_array.insert(j_another_array.end(), 10, 11),
               json::invalid_iterator,
               "[json.exception.invalid_iterator.202] iterator does "
               "not fit current value");
  HELPER_THROW(j_array.insert(j_another_array.end(),
                              j_yet_another_array.begin(),
                              j_yet_another_array.end()),
               json::invalid_iterator,
               "[json.exception.invalid_iterator.202] iterator does "
               "not fit current value");
  HELPER_THROW(j_array.insert(j_another_array.end(), {1, 2, 3, 4}),
               json::invalid_iterator,
               "[json.exception.invalid_iterator.202] iterator does "
               "not fit current value");
}

{
  // call insert on a non-array type
  json j_nonarray = 3;
  json j_yet_another_array = {"first", "second"};

  HELPER_THROW(
      j_nonarray.insert(j_nonarray.end(), 10), json::type_error,
      "[json.exception.type_error.309] cannot use insert() with number");
  HELPER_THROW(
      j_nonarray.insert(j_nonarray.end(), j_value), json::type_error,
      "[json.exception.type_error.309] cannot use insert() with number");
  HELPER_THROW(
      j_nonarray.insert(j_nonarray.end(), 10, 11), json::type_error,
      "[json.exception.type_error.309] cannot use insert() with number");
  HELPER_THROW(
      j_nonarray.insert(j_nonarray.end(), j_yet_another_array.begin(),
                        j_yet_another_array.end()),
      json::type_error,
      "[json.exception.type_error.309] cannot use insert() with number");
  HELPER_THROW(
      j_nonarray.insert(j_nonarray.end(), {1, 2, 3, 4}), json::type_error,
      "[json.exception.type_error.309] cannot use insert() with number");
}
}

{
  json j_object1 = {{"one", "eins"}, {"two", "zwei"}};
  json j_object2 = {{"three", "drei"}, {"two", "zwo"}};
  json j_array = {1, 2, 3, 4};

  {{j_object1.update(j_object2);
  EXPECT_TRUE(j_object1 ==
              json({{"one", "eins"}, {"two", "zwo"}, {"three", "drei"}}));

  json j_null;
  j_null.update(j_object2);
  EXPECT_TRUE(j_null == j_object2);
}

{
  HELPER_THROW(
      j_array.update(j_object1), json::type_error,
      "[json.exception.type_error.312] cannot use update() with array");
  HELPER_THROW(
      j_object1.update(j_array), json::type_error,
      "[json.exception.type_error.312] cannot use update() with array");
}
}

{
  {
    j_object1.update(j_object2.begin(), j_object2.end());
    EXPECT_TRUE(j_object1 ==
                json({{"one", "eins"}, {"two", "zwo"}, {"three", "drei"}}));

    json j_null;
    j_null.update(j_object2.begin(), j_object2.end());
    EXPECT_TRUE(j_null == j_object2);
  }

  {
  json j_object1 = {{"one", "eins"}, {"two", "zwei"}};
  json j_object2 = {{"three", "drei"}, {"two", "zwo"}};
    j_object1.update(j_object2.begin(), j_object2.begin());
    EXPECT_TRUE(j_object1 == json({{"one", "eins"}, {"two", "zwei"}}));
  }

  {
    json j_other_array2 = {"first", "second"};

    HELPER_THROW(
        j_array.update(j_object2.begin(), j_object2.end()), json::type_error,
        "[json.exception.type_error.312] cannot use update() with array");
    HELPER_THROW(j_object1.update(j_object1.begin(), j_object2.end()),
                 json::invalid_iterator,
                 "[json.exception.invalid_iterator.210] iterators do not fit");
    HELPER_THROW(j_object1.update(j_array.begin(), j_array.end()),
                 json::invalid_iterator,
                 "[json.exception.invalid_iterator.202] iterators "
                 "first and last must point to objects");
  }
}
}

{
  {{json j("hello world");
  json k(42.23);

  j.swap(k);

  EXPECT_TRUE(j == json(42.23));
  EXPECT_TRUE(k == json("hello world"));
}

{
  json j("hello world");
  json k(42.23);

  std::swap(j, k);

  EXPECT_TRUE(j == json(42.23));
  EXPECT_TRUE(k == json("hello world"));
}
}

{{json j = {1, 2, 3, 4};
json::array_t a = {"foo", "bar", "baz"};

j.swap(a);

EXPECT_TRUE(j == json({"foo", "bar", "baz"}));

j.swap(a);

EXPECT_TRUE(j == json({1, 2, 3, 4}));
}

{
  json j = 17;
  json::array_t a = {"foo", "bar", "baz"};

  HELPER_THROW(j.swap(a), json::type_error,
               "[json.exception.type_error.310] cannot use swap() with number");
}
}

{{json j = {{"one", 1}, {"two", 2}};
json::object_t o = {{"cow", "Kuh"}, {"chicken", "Huhn"}};

j.swap(o);

EXPECT_TRUE(j == json({{"cow", "Kuh"}, {"chicken", "Huhn"}}));

j.swap(o);

EXPECT_TRUE(j == json({{"one", 1}, {"two", 2}}));
}

{
  json j = 17;
  json::object_t o = {{"cow", "Kuh"}, {"chicken", "Huhn"}};

  HELPER_THROW(j.swap(o), json::type_error,
               "[json.exception.type_error.310] cannot use swap() with number");
}
}

{
  {
    json j = "Hello world";
    json::string_t s = "Hallo Welt";

    j.swap(s);

    EXPECT_TRUE(j == json("Hallo Welt"));

    j.swap(s);

    EXPECT_TRUE(j == json("Hello world"));
  }

  {
    json j = 17;
    json::string_t s = "Hallo Welt";

    HELPER_THROW(
        j.swap(s), json::type_error,
        "[json.exception.type_error.310] cannot use swap() with number");
  }
}
}
}
