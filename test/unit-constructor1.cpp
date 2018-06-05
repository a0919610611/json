#include "gtest/gtest.h"
#define private public
#include "json.hpp"

using nlohmann::json;

#include <deque>
#include <forward_list>
#include <fstream>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <valarray>

TEST(constructors, constructor1)
{
    //TEST(constructors,"create an empty value with a given type")
    {
        //TEST(constructors,"null")
        {
            auto t = json::value_t::null;
            json j(t);
            EXPECT_TRUE(j.type() == t);
        }

        //TEST(constructors,"discarded")
        {
            auto t = json::value_t::discarded;
            json j(t);
            EXPECT_TRUE(j.type() == t);
        }

        //TEST(constructors,"object")
        {
            auto t = json::value_t::object;
            json j(t);
            EXPECT_TRUE(j.type() == t);
        }

        //TEST(constructors,"array")
        {
            auto t = json::value_t::array;
            json j(t);
            EXPECT_TRUE(j.type() == t);
        }

        //TEST(constructors,"boolean")
        {
            auto t = json::value_t::boolean;
            json j(t);
            EXPECT_TRUE(j.type() == t);
            EXPECT_TRUE(j == false);
        }

        //TEST(constructors,"string")
        {
            auto t = json::value_t::string;
            json j(t);
            EXPECT_TRUE(j.type() == t);
            EXPECT_TRUE(j == "");
        }

        //TEST(constructors,"number_integer")
        {
            auto t = json::value_t::number_integer;
            json j(t);
            EXPECT_TRUE(j.type() == t);
            EXPECT_TRUE(j == 0);
        }

        //TEST(constructors,"number_unsigned")
        {
            auto t = json::value_t::number_unsigned;
            json j(t);
            EXPECT_TRUE(j.type() == t);
            EXPECT_TRUE(j == 0);
        }

        //TEST(constructors,"number_float")
        {
            auto t = json::value_t::number_float;
            json j(t);
            EXPECT_TRUE(j.type() == t);
            EXPECT_TRUE(j == 0.0);
        }
    }

    //TEST(constructors,"create a null object (implicitly)")
    {
        //TEST(constructors,"no parameter")
        {
            json j{};
            EXPECT_TRUE(j.type() == json::value_t::null);
        }
    }

    //TEST(constructors,"create a null object (explicitly)")
    {
        //TEST(constructors,"parameter")
        {
            json j(nullptr);
            EXPECT_TRUE(j.type() == json::value_t::null);
        }
    }

    //TEST(constructors,"create an object (explicit)")
    {
        //TEST(constructors,"empty object")
        {
            json::object_t o;
            json j(o);
            EXPECT_TRUE(j.type() == json::value_t::object);
        }

        //TEST(constructors,"filled object")
        {
            json::object_t o {{"a", json(1)}, {"b", json(1u)}, {"c", json(2.2)}, {"d", json(false)}, {"e", json("string")}, {"f", json()}};
            json j(o);
            EXPECT_TRUE(j.type() == json::value_t::object);
        }
    }

    //TEST(constructors,"create an object (implicit)")
    {
        // reference object
        json::object_t o_reference {{"a", json(1)}, {"b", json(1u)}, {"c", json(2.2)}, {"d", json(false)}, {"e", json("string")}, {"f", json()}};
        json j_reference(o_reference);

        //TEST(constructors,"std::map<json::string_t, json>")
        {
            std::map<json::string_t, json> o {{"a", json(1)}, {"b", json(1u)}, {"c", json(2.2)}, {"d", json(false)}, {"e", json("string")}, {"f", json()}};
            json j(o);
            EXPECT_TRUE(j.type() == json::value_t::object);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"std::map<std::string, std::string> #600")
        {
            std::map<std::string, std::string> m;
            m["a"] = "b";
            m["c"] = "d";
            m["e"] = "f";

            json j(m);
            EXPECT_TRUE((j.get<decltype(m)>() == m));
        }

        //TEST(constructors,"std::map<const char*, json>")
        {
            std::map<const char*, json> o {{"a", json(1)}, {"b", json(1u)}, {"c", json(2.2)}, {"d", json(false)}, {"e", json("string")}, {"f", json()}};
            json j(o);
            EXPECT_TRUE(j.type() == json::value_t::object);
            EXPECT_TRUE(j == j_reference);
        }


        //TEST(constructors,"std::multimap<json::string_t, json>")
        {
            std::multimap<json::string_t, json> o {{"a", json(1)}, {"b", json(1u)}, {"c", json(2.2)}, {"d", json(false)}, {"e", json("string")}, {"f", json()}};
            json j(o);
            EXPECT_TRUE(j.type() == json::value_t::object);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"std::unordered_map<json::string_t, json>")
        {
            std::unordered_map<json::string_t, json> o {{"a", json(1)}, {"b", json(1u)}, {"c", json(2.2)}, {"d", json(false)}, {"e", json("string")}, {"f", json()}};
            json j(o);
            EXPECT_TRUE(j.type() == json::value_t::object);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"std::unordered_multimap<json::string_t, json>")
        {
            std::unordered_multimap<json::string_t, json> o {{"a", json(1)}, {"b", json(1u)}, {"c", json(2.2)}, {"d", json(false)}, {"e", json("string")}, {"f", json()}};
            json j(o);
            EXPECT_TRUE(j.type() == json::value_t::object);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"associative container literal")
        {
            json j({{"a", json(1)}, {"b", json(1u)}, {"c", json(2.2)}, {"d", json(false)}, {"e", json("string")}, {"f", json()}});
            EXPECT_TRUE(j.type() == json::value_t::object);
            EXPECT_TRUE(j == j_reference);
        }
    }

    //TEST(constructors,"create an array (explicit)")
    {
        //TEST(constructors,"empty array")
        {
            json::array_t a;
            json j(a);
            EXPECT_TRUE(j.type() == json::value_t::array);
        }

        //TEST(constructors,"filled array")
        {
            json::array_t a {json(1), json(1u), json(2.2), json(false), json("string"), json()};
            json j(a);
            EXPECT_TRUE(j.type() == json::value_t::array);
        }
    }

    //TEST(constructors,"create an array (implicit)")
    {
        // reference array
        json::array_t a_reference {json(1), json(1u), json(2.2), json(false), json("string"), json()};
        json j_reference(a_reference);

        //TEST(constructors,"std::list<json>")
        {
            std::list<json> a {json(1), json(1u), json(2.2), json(false), json("string"), json()};
            json j(a);
            EXPECT_TRUE(j.type() == json::value_t::array);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"std::pair")
        {
            std::pair<float, std::string> p{1.0f, "string"};
            json j(p);

            EXPECT_TRUE(j.type() == json::value_t::array);
            EXPECT_TRUE(j.get<decltype(p)>() == p);
            ASSERT_TRUE(j.size() == 2);
            EXPECT_TRUE(j[0] == std::get<0>(p));
            EXPECT_TRUE(j[1] == std::get<1>(p));
        }

        //TEST(constructors,"std::pair with discarded values")
        {
            json j{1, 2.0, "string"};

            const auto p = j.get<std::pair<int, float>>();
            EXPECT_TRUE(p.first == j[0]);
            EXPECT_TRUE(p.second == j[1]);
        }

        //TEST(constructors,"std::tuple")
        {
            const auto t = std::make_tuple(1.0, std::string{"string"}, 42, std::vector<int> {0, 1});
            json j(t);

            EXPECT_TRUE(j.type() == json::value_t::array);
            ASSERT_TRUE(j.size() == 4);
            EXPECT_TRUE(j.get<decltype(t)>() == t);
            EXPECT_TRUE(j[0] == std::get<0>(t));
            EXPECT_TRUE(j[1] == std::get<1>(t));
            EXPECT_TRUE(j[2] == std::get<2>(t));
            EXPECT_TRUE(j[3][0] == 0);
            EXPECT_TRUE(j[3][1] == 1);
        }

        //TEST(constructors,"std::tuple with discarded values")
        {
            json j{1, 2.0, "string", 42};

            const auto t = j.get<std::tuple<int, float, std::string>>();
            EXPECT_TRUE(std::get<0>(t) == j[0]);
            EXPECT_TRUE(std::get<1>(t) == j[1]);
            EXPECT_TRUE(std::get<2>(t) == j[2]);
        }

        //TEST(constructors,"std::pair/tuple/array failures")
        {
            json j{1};

            EXPECT_THROW((j.get<std::pair<int, int>>()), json::out_of_range);
            //CHECK_THROWS_WITH((j.get<std::pair<int, int>>()), "[json.exception.out_of_range.401] array index 1 is out of range");
            EXPECT_THROW((j.get<std::tuple<int, int>>()), json::out_of_range);
            //CHECK_THROWS_WITH((j.get<std::tuple<int, int>>()), "[json.exception.out_of_range.401] array index 1 is out of range");
            EXPECT_THROW((j.get<std::array<int, 3>>()), json::out_of_range);
            //CHECK_THROWS_WITH((j.get<std::array<int, 3>>()), "[json.exception.out_of_range.401] array index 1 is out of range");
        }

        //TEST(constructors,"std::forward_list<json>")
        {
            std::forward_list<json> a {json(1), json(1u), json(2.2), json(false), json("string"), json()};
            json j(a);
            EXPECT_TRUE(j.type() == json::value_t::array);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"std::array<json, 6>")
        {
            std::array<json, 6> a {{json(1), json(1u), json(2.2), json(false), json("string"), json()}};
            json j(a);
            EXPECT_TRUE(j.type() == json::value_t::array);
            EXPECT_TRUE(j == j_reference);

            const auto a2 = j.get<std::array<json, 6>>();
            EXPECT_TRUE(a2 == a);
        }

        //TEST(constructors,"std::valarray<int>")
        {
            std::valarray<int> va = {1, 2, 3, 4, 5};
            json j(va);
            EXPECT_TRUE(j.type() == json::value_t::array);
            EXPECT_TRUE(j == json({1, 2, 3, 4, 5}));

            std::valarray<int> jva = j;
            EXPECT_TRUE(jva.size() == va.size());
            for (size_t i = 0; i < jva.size(); ++i)
            {
                EXPECT_TRUE(va[i] == jva[i]);
            }
        }

        //TEST(constructors,"std::valarray<double>")
        {
            std::valarray<double> va = {1.2, 2.3, 3.4, 4.5, 5.6};
            json j(va);
            EXPECT_TRUE(j.type() == json::value_t::array);
            EXPECT_TRUE(j == json({1.2, 2.3, 3.4, 4.5, 5.6}));

            std::valarray<double> jva = j;
            EXPECT_TRUE(jva.size() == va.size());
            for (size_t i = 0; i < jva.size(); ++i)
            {
                EXPECT_TRUE(va[i] == jva[i]);
            }
        }

        //TEST(constructors,"std::vector<json>")
        {
            std::vector<json> a {json(1), json(1u), json(2.2), json(false), json("string"), json()};
            json j(a);
            EXPECT_TRUE(j.type() == json::value_t::array);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"std::deque<json>")
        {
            std::deque<json> a {json(1), json(1u), json(2.2), json(false), json("string"), json()};
            json j(a);
            EXPECT_TRUE(j.type() == json::value_t::array);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"std::set<json>")
        {
            std::set<json> a {json(1), json(1u), json(2.2), json(false), json("string"), json()};
            json j(a);
            EXPECT_TRUE(j.type() == json::value_t::array);
            // we cannot really check for equality here
        }

        //TEST(constructors,"std::unordered_set<json>")
        {
            std::unordered_set<json> a {json(1), json(1u), json(2.2), json(false), json("string"), json()};
            json j(a);
            EXPECT_TRUE(j.type() == json::value_t::array);
            // we cannot really check for equality here
        }

        //TEST(constructors,"sequence container literal")
        {
            json j({json(1), json(1u), json(2.2), json(false), json("string"), json()});
            EXPECT_TRUE(j.type() == json::value_t::array);
            EXPECT_TRUE(j == j_reference);
        }
    }

    //TEST(constructors,"create a string (explicit)")
    {
        //TEST(constructors,"empty string")
        {
            json::string_t s;
            json j(s);
            EXPECT_TRUE(j.type() == json::value_t::string);
        }

        //TEST(constructors,"filled string")
        {
            json::string_t s {"Hello world"};
            json j(s);
            EXPECT_TRUE(j.type() == json::value_t::string);
        }
    }

    //TEST(constructors,"create a string (implicit)")
    {
        // reference string
        json::string_t s_reference {"Hello world"};
        json j_reference(s_reference);

        //TEST(constructors,"std::string")
        {
            std::string s {"Hello world"};
            json j(s);
            EXPECT_TRUE(j.type() == json::value_t::string);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"char[]")
        {
            char s[] {"Hello world"};
            json j(s);
            EXPECT_TRUE(j.type() == json::value_t::string);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"const char*")
        {
            const char* s {"Hello world"};
            json j(s);
            EXPECT_TRUE(j.type() == json::value_t::string);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"string literal")
        {
            json j("Hello world");
            EXPECT_TRUE(j.type() == json::value_t::string);
            EXPECT_TRUE(j == j_reference);
        }
    }

    //TEST(constructors,"create a boolean (explicit)")
    {
        //TEST(constructors,"empty boolean")
        {
            json::boolean_t b{};
            json j(b);
            EXPECT_TRUE(j.type() == json::value_t::boolean);
        }

        //TEST(constructors,"filled boolean (true)")
        {
            json j(true);
            EXPECT_TRUE(j.type() == json::value_t::boolean);
        }

        //TEST(constructors,"filled boolean (false)")
        {
            json j(false);
            EXPECT_TRUE(j.type() == json::value_t::boolean);
        }
    }

    //TEST(constructors,"create an integer number (explicit)")
    {
        //TEST(constructors,"uninitialized value")
        {
            json::number_integer_t n{};
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_integer);
        }

        //TEST(constructors,"initialized value")
        {
            json::number_integer_t n(42);
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_integer);
        }
    }

    //TEST(constructors,"create an integer number (implicit)")
    {
        // reference objects
        json::number_integer_t n_reference = 42;
        json j_reference(n_reference);
        json::number_unsigned_t n_unsigned_reference = 42;
        json j_unsigned_reference(n_unsigned_reference);

        //TEST(constructors,"short")
        {
            short n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_integer);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"unsigned short")
        {
            unsigned short n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_unsigned);
            EXPECT_TRUE(j == j_unsigned_reference);
        }

        //TEST(constructors,"int")
        {
            int n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_integer);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"unsigned int")
        {
            unsigned int n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_unsigned);
            EXPECT_TRUE(j == j_unsigned_reference);
        }

        //TEST(constructors,"long")
        {
            long n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_integer);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"unsigned long")
        {
            unsigned long n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_unsigned);
            EXPECT_TRUE(j == j_unsigned_reference);
        }

        //TEST(constructors,"long long")
        {
            long long n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_integer);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"unsigned long long")
        {
            unsigned long long n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_unsigned);
            EXPECT_TRUE(j == j_unsigned_reference);
        }

        //TEST(constructors,"int8_t")
        {
            int8_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_integer);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"int16_t")
        {
            int16_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_integer);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"int32_t")
        {
            int32_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_integer);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"int64_t")
        {
            int64_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_integer);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"int_fast8_t")
        {
            int_fast8_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_integer);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"int_fast16_t")
        {
            int_fast16_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_integer);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"int_fast32_t")
        {
            int_fast32_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_integer);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"int_fast64_t")
        {
            int_fast64_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_integer);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"int_least8_t")
        {
            int_least8_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_integer);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"int_least16_t")
        {
            int_least16_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_integer);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"int_least32_t")
        {
            int_least32_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_integer);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"int_least64_t")
        {
            int_least64_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_integer);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"uint8_t")
        {
            uint8_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_unsigned);
            EXPECT_TRUE(j == j_unsigned_reference);
        }

        //TEST(constructors,"uint16_t")
        {
            uint16_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_unsigned);
            EXPECT_TRUE(j == j_unsigned_reference);
        }

        //TEST(constructors,"uint32_t")
        {
            uint32_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_unsigned);
            EXPECT_TRUE(j == j_unsigned_reference);
        }

        //TEST(constructors,"uint64_t")
        {
            uint64_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_unsigned);
            EXPECT_TRUE(j == j_unsigned_reference);
        }

        //TEST(constructors,"uint_fast8_t")
        {
            uint_fast8_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_unsigned);
            EXPECT_TRUE(j == j_unsigned_reference);
        }

        //TEST(constructors,"uint_fast16_t")
        {
            uint_fast16_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_unsigned);
            EXPECT_TRUE(j == j_unsigned_reference);
        }

        //TEST(constructors,"uint_fast32_t")
        {
            uint_fast32_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_unsigned);
            EXPECT_TRUE(j == j_unsigned_reference);
        }

        //TEST(constructors,"uint_fast64_t")
        {
            uint_fast64_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_unsigned);
            EXPECT_TRUE(j == j_unsigned_reference);
        }

        //TEST(constructors,"uint_least8_t")
        {
            uint_least8_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_unsigned);
            EXPECT_TRUE(j == j_unsigned_reference);
        }

        //TEST(constructors,"uint_least16_t")
        {
            uint_least16_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_unsigned);
            EXPECT_TRUE(j == j_unsigned_reference);
        }

        //TEST(constructors,"uint_least32_t")
        {
            uint_least32_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_unsigned);
            EXPECT_TRUE(j == j_unsigned_reference);
        }

        //TEST(constructors,"uint_least64_t")
        {
            uint_least64_t n = 42;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_unsigned);
            EXPECT_TRUE(j == j_unsigned_reference);
        }

        //TEST(constructors,"integer literal without suffix")
        {
            json j(42);
            EXPECT_TRUE(j.type() == json::value_t::number_integer);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"integer literal with u suffix")
        {
            json j(42u);
            EXPECT_TRUE(j.type() == json::value_t::number_unsigned);
            EXPECT_TRUE(j == j_unsigned_reference);
        }

        //TEST(constructors,"integer literal with l suffix")
        {
            json j(42l);
            EXPECT_TRUE(j.type() == json::value_t::number_integer);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"integer literal with ul suffix")
        {
            json j(42ul);
            EXPECT_TRUE(j.type() == json::value_t::number_unsigned);
            EXPECT_TRUE(j == j_unsigned_reference);
        }

        //TEST(constructors,"integer literal with ll suffix")
        {
            json j(42ll);
            EXPECT_TRUE(j.type() == json::value_t::number_integer);
            EXPECT_TRUE(j == j_reference);
        }

        //TEST(constructors,"integer literal with ull suffix")
        {
            json j(42ull);
            EXPECT_TRUE(j.type() == json::value_t::number_unsigned);
            EXPECT_TRUE(j == j_unsigned_reference);
        }
    }

    //TEST(constructors,"create a floating-point number (explicit)")
    {
        //TEST(constructors,"uninitialized value")
        {
            json::number_float_t n{};
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_float);
        }

        //TEST(constructors,"initialized value")
        {
            json::number_float_t n(42.23);
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_float);
        }

        //TEST(constructors,"infinity")
        {
            // infinity is stored properly, but serialized to null
            json::number_float_t n(std::numeric_limits<json::number_float_t>::infinity());
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_float);

            // check round trip of infinity
            json::number_float_t d = j;
            EXPECT_TRUE(d == n);

            // check that inf is serialized to null
            EXPECT_TRUE(j.dump() == "null");
        }
    }

    //TEST(constructors,"create a floating-point number (implicit)")
    {
        // reference object
        json::number_float_t n_reference = 42.23;
        json j_reference(n_reference);

        //TEST(constructors,"float")
        {
            float n = 42.23f;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_float);
            EXPECT_FLOAT_EQ(j.m_value.number_float, j_reference.m_value.number_float);
        }

        //TEST(constructors,"double")
        {
            double n = 42.23;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_float);
            EXPECT_FLOAT_EQ(j.m_value.number_float, j_reference.m_value.number_float);
        }

        //TEST(constructors,"long double")
        {
            long double n = 42.23l;
            json j(n);
            EXPECT_TRUE(j.type() == json::value_t::number_float);
            EXPECT_FLOAT_EQ(j.m_value.number_float, j_reference.m_value.number_float);
        }

        //TEST(constructors,"floating-point literal without suffix")
        {
            json j(42.23);
            EXPECT_TRUE(j.type() == json::value_t::number_float);
            EXPECT_FLOAT_EQ(j.m_value.number_float, j_reference.m_value.number_float);
        }

        //TEST(constructors,"integer literal with f suffix")
        {
            json j(42.23f);
            EXPECT_TRUE(j.type() == json::value_t::number_float);
            EXPECT_FLOAT_EQ(j.m_value.number_float, j_reference.m_value.number_float);
        }

        //TEST(constructors,"integer literal with l suffix")
        {
            json j(42.23l);
            EXPECT_TRUE(j.type() == json::value_t::number_float);
            EXPECT_FLOAT_EQ(j.m_value.number_float, j_reference.m_value.number_float);
        }
    }

    //TEST(constructors,"create a container (array or object) from an initializer list")
    {
        //TEST(constructors,"empty initializer list")
        {
            //TEST(constructors,"explicit")
            {
                json j(json::initializer_list_t {});
                EXPECT_TRUE(j.type() == json::value_t::object);
            }

            //TEST(constructors,"implicit")
            {
                json j {};
                EXPECT_TRUE(j.type() == json::value_t::null);
            }
        }

        //TEST(constructors,"one element")
        {
            //TEST(constructors,"array")
            {
                //TEST(constructors,"explicit")
                {
                    json j(json::initializer_list_t {json(json::array_t())});
                    EXPECT_TRUE(j.type() == json::value_t::array);
                }

                //TEST(constructors,"implicit")
                {
                    json j {json::array_t()};
                    EXPECT_TRUE(j.type() == json::value_t::array);
                }
            }

            //TEST(constructors,"object")
            {
                //TEST(constructors,"explicit")
                {
                    json j(json::initializer_list_t {json(json::object_t())});
                    EXPECT_TRUE(j.type() == json::value_t::array);
                }

                //TEST(constructors,"implicit")
                {
                    json j {json::object_t()};
                    EXPECT_TRUE(j.type() == json::value_t::array);
                }
            }

            //TEST(constructors,"string")
            {
                //TEST(constructors,"explicit")
                {
                    json j(json::initializer_list_t {json("Hello world")});
                    EXPECT_TRUE(j.type() == json::value_t::array);
                }

                //TEST(constructors,"implicit")
                {
                    json j {"Hello world"};
                    EXPECT_TRUE(j.type() == json::value_t::array);
                }
            }

            //TEST(constructors,"boolean")
            {
                //TEST(constructors,"explicit")
                {
                    json j(json::initializer_list_t {json(true)});
                    EXPECT_TRUE(j.type() == json::value_t::array);
                }

                //TEST(constructors,"implicit")
                {
                    json j {true};
                    EXPECT_TRUE(j.type() == json::value_t::array);
                }
            }

            //TEST(constructors,"number (integer)")
            {
                //TEST(constructors,"explicit")
                {
                    json j(json::initializer_list_t {json(1)});
                    EXPECT_TRUE(j.type() == json::value_t::array);
                }

                //TEST(constructors,"implicit")
                {
                    json j {1};
                    EXPECT_TRUE(j.type() == json::value_t::array);
                }
            }

            //TEST(constructors,"number (unsigned)")
            {
                //TEST(constructors,"explicit")
                {
                    json j(json::initializer_list_t {json(1u)});
                    EXPECT_TRUE(j.type() == json::value_t::array);
                }

                //TEST(constructors,"implicit")
                {
                    json j {1u};
                    EXPECT_TRUE(j.type() == json::value_t::array);
                }
            }

            //TEST(constructors,"number (floating-point)")
            {
                //TEST(constructors,"explicit")
                {
                    json j(json::initializer_list_t {json(42.23)});
                    EXPECT_TRUE(j.type() == json::value_t::array);
                }

                //TEST(constructors,"implicit")
                {
                    json j {42.23};
                    EXPECT_TRUE(j.type() == json::value_t::array);
                }
            }
        }

        //TEST(constructors,"more elements")
        {
            //TEST(constructors,"explicit")
            {
                json j(json::initializer_list_t {1, 1u, 42.23, true, nullptr, json::object_t(), json::array_t()});
                EXPECT_TRUE(j.type() == json::value_t::array);
            }

            //TEST(constructors,"implicit")
            {
                json j {1, 1u, 42.23, true, nullptr, json::object_t(), json::array_t()};
                EXPECT_TRUE(j.type() == json::value_t::array);
            }
        }

        //TEST(constructors,"implicit type deduction")
        {
            //TEST(constructors,"object")
            {
                json j { {"one", 1}, {"two", 1u}, {"three", 2.2}, {"four", false} };
                EXPECT_TRUE(j.type() == json::value_t::object);
            }

            //TEST(constructors,"array")
            {
                json j { {"one", 1}, {"two", 1u}, {"three", 2.2}, {"four", false}, 13 };
                EXPECT_TRUE(j.type() == json::value_t::array);
            }
        }

        //TEST(constructors,"explicit type deduction")
        {
            //TEST(constructors,"empty object")
            {
                json j = json::object();
                EXPECT_TRUE(j.type() == json::value_t::object);
            }

            //TEST(constructors,"object")
            {
                json j = json::object({ {"one", 1}, {"two", 1u}, {"three", 2.2}, {"four", false} });
                EXPECT_TRUE(j.type() == json::value_t::object);
            }

            //TEST(constructors,"object with error")
            {
                EXPECT_THROW(json::object({ {"one", 1}, {"two", 1u}, {"three", 2.2}, {"four", false}, 13 }), json::type_error);
                //CHECK_THROWS_WITH(json::object({ {"one", 1}, {"two", 1u}, {"three", 2.2}, {"four", false}, 13 }),
                //"[json.exception.type_error.301] cannot create object from initializer list");
            }

            //TEST(constructors,"empty array")
            {
                json j = json::array();
                EXPECT_TRUE(j.type() == json::value_t::array);
            }

            //TEST(constructors,"array")
            {
                json j = json::array({ {"one", 1}, {"two", 1u}, {"three", 2.2}, {"four", false} });
                EXPECT_TRUE(j.type() == json::value_t::array);
            }
        }

        //TEST(constructors,"move from initializer_list")
        {
            //TEST(constructors,"string")
            {
                // This should break through any short string optimization in std::string
                std::string source(1024, '!');
                const char* source_addr = source.data();

                //TEST(constructors,"constructor with implicit types (array)")
                {
                    json j = {std::move(source)};
                    EXPECT_TRUE(j[0].get_ref<std::string const&>().data() == source_addr);
                }

                //TEST(constructors,"constructor with implicit types (object)")
                {
					std::string source(1024, '!');
					const char* source_addr = source.data();
                    json j = {{"key", std::move(source)}};
                    EXPECT_TRUE(j["key"].get_ref<std::string const&>().data() == source_addr);
                }

                //TEST(constructors,"constructor with implicit types (object key)")
                {
					std::string source(1024, '!');
					const char* source_addr = source.data();
                    json j = {{std::move(source), 42}};
                    EXPECT_TRUE(j.get_ref<json::object_t&>().begin()->first.data() == source_addr);
                }
            }

            //TEST(constructors,"array")
            {
                json::array_t source = {1, 2, 3};
                const json* source_addr = source.data();

                //TEST(constructors,"constructor with implicit types (array)")
                {
                    json j {std::move(source)};
                    EXPECT_TRUE(j[0].get_ref<json::array_t const&>().data() == source_addr);
                }

                //TEST(constructors,"constructor with implicit types (object)")
                {
					json::array_t source = {1, 2, 3};
					const json* source_addr = source.data();
                    json j {{"key", std::move(source)}};
                    EXPECT_TRUE(j["key"].get_ref<json::array_t const&>().data() == source_addr);
                }

                //TEST(constructors,"assignment with implicit types (array)")
                {
					json::array_t source = {1, 2, 3};
					const json* source_addr = source.data();
                    json j = {std::move(source)};
                    EXPECT_TRUE(j[0].get_ref<json::array_t const&>().data() == source_addr);
                }

                //TEST(constructors,"assignment with implicit types (object)")
                {
					json::array_t source = {1, 2, 3};
					const json* source_addr = source.data();
                    json j = {{"key", std::move(source)}};
                    EXPECT_TRUE(j["key"].get_ref<json::array_t const&>().data() == source_addr);
                }
            }

            //TEST(constructors,"object")
            {
                json::object_t source = {{"hello", "world"}};
                const json* source_addr = &source.at("hello");

                //TEST(constructors,"constructor with implicit types (array)")
                {
					json::object_t source = {{"hello", "world"}};
					const json* source_addr = &source.at("hello");
                    json j {std::move(source)};
                    EXPECT_TRUE(&(j[0].get_ref<json::object_t const&>().at("hello")) == source_addr);
                }

                //TEST(constructors,"constructor with implicit types (object)")
                {
					json::object_t source = {{"hello", "world"}};
					const json* source_addr = &source.at("hello");
                    json j {{"key", std::move(source)}};
                    EXPECT_TRUE(&(j["key"].get_ref<json::object_t const&>().at("hello")) == source_addr);
                }

                //TEST(constructors,"assignment with implicit types (array)")
                {
					json::object_t source = {{"hello", "world"}};
					const json* source_addr = &source.at("hello");
                    json j = {std::move(source)};
                    EXPECT_TRUE(&(j[0].get_ref<json::object_t const&>().at("hello")) == source_addr);
                }

                //TEST(constructors,"assignment with implicit types (object)")
                {
					json::object_t source = {{"hello", "world"}};
					const json* source_addr = &source.at("hello");
                    json j = {{"key", std::move(source)}};
                    EXPECT_TRUE(&(j["key"].get_ref<json::object_t const&>().at("hello")) == source_addr);
                }
            }

            //TEST(constructors,"json")
            {
                json source {1, 2, 3};
                const json* source_addr = &source[0];

                //TEST(constructors,"constructor with implicit types (array)")
                {
					json source {1, 2, 3};
					const json* source_addr = &source[0];
                    json j {std::move(source), {}};
                    EXPECT_TRUE(&j[0][0] == source_addr);
                }

                //TEST(constructors,"constructor with implicit types (object)")
                {
					json source {1, 2, 3};
					const json* source_addr = &source[0];
                    json j {{"key", std::move(source)}};
                    EXPECT_TRUE(&j["key"][0] == source_addr);
                }

                //TEST(constructors,"assignment with implicit types (array)")
                {
					json source {1, 2, 3};
					const json* source_addr = &source[0];
                    json j = {std::move(source), {}};
                    EXPECT_TRUE(&j[0][0] == source_addr);
                }

                //TEST(constructors,"assignment with implicit types (object)")
                {
					json source {1, 2, 3};
					const json* source_addr = &source[0];
                    json j = {{"key", std::move(source)}};
                    EXPECT_TRUE(&j["key"][0] == source_addr);
                }
            }

        }
    }

    //TEST(constructors,"create an array of n copies of a given value")
    {
        //TEST(constructors,"cnt = 0")
        {
            json v = {1, "foo", 34.23, {1, 2, 3}, {{"A", 1}, {"B", 2u}}};
            json arr(0, v);
            EXPECT_TRUE(arr.size() == 0);
        }

        //TEST(constructors,"cnt = 1")
        {
            json v = {1, "foo", 34.23, {1, 2, 3}, {{"A", 1}, {"B", 2u}}};
            json arr(1, v);
            EXPECT_TRUE(arr.size() == 1);
            for (auto& x : arr)
            {
                EXPECT_TRUE(x == v);
            }
        }

        //TEST(constructors,"cnt = 3")
        {
            json v = {1, "foo", 34.23, {1, 2, 3}, {{"A", 1}, {"B", 2u}}};
            json arr(3, v);
            EXPECT_TRUE(arr.size() == 3);
            for (auto& x : arr)
            {
                EXPECT_TRUE(x == v);
            }
        }
    }

    //TEST(constructors,"create a JSON container from an iterator range")
    {
        //TEST(constructors,"object")
        {
            //TEST(constructors,"json(begin(), end())")
            {
                {
                    json jobject = {{"a", "a"}, {"b", 1}, {"c", 17u}};
                    json j_new(jobject.begin(), jobject.end());
                    EXPECT_TRUE(j_new == jobject);
                }
                {
                    json jobject = {{"a", "a"}, {"b", 1}, {"c", 17u}};
                    json j_new(jobject.cbegin(), jobject.cend());
                    EXPECT_TRUE(j_new == jobject);
                }
            }

            //TEST(constructors,"json(begin(), begin())")
            {
                {
                    json jobject = {{"a", "a"}, {"b", 1}, {"c", 17u}};
                    json j_new(jobject.begin(), jobject.begin());
                    EXPECT_TRUE(j_new == json::object());
                }
                {
                    json jobject = {{"a", "a"}, {"b", 1}, {"c", 17u}};
                    json j_new(jobject.cbegin(), jobject.cbegin());
                    EXPECT_TRUE(j_new == json::object());
                }
            }

            //TEST(constructors,"construct from subrange")
            {
                json jobject = {{"a", "a"}, {"b", 1}, {"c", 17u}, {"d", false}, {"e", true}};
                json j_new(jobject.find("b"), jobject.find("e"));
                EXPECT_TRUE(j_new == json({{"b", 1}, {"c", 17u}, {"d", false}}));
            }

            //TEST(constructors,"incompatible iterators")
            {
                {
                    json jobject = {{"a", "a"}, {"b", 1}, {"c", 17u}, {"d", false}, {"e", true}};
                    json jobject2 = {{"a", "a"}, {"b", 1}, {"c", 17u}};
                    EXPECT_THROW(json(jobject.begin(), jobject2.end()), json::invalid_iterator);
                    EXPECT_THROW(json(jobject2.begin(), jobject.end()), json::invalid_iterator);
                    //CHECK_THROWS_WITH(json(jobject.begin(), jobject2.end()), "[json.exception.invalid_iterator.201] iterators are not compatible");
                    //CHECK_THROWS_WITH(json(jobject2.begin(), jobject.end()), "[json.exception.invalid_iterator.201] iterators are not compatible");
                }
                {
                    json jobject = {{"a", "a"}, {"b", 1}, {"c", 17u}, {"d", false}, {"e", true}};
                    json jobject2 = {{"a", "a"}, {"b", 1}, {"c", 17u}};
                    EXPECT_THROW(json(jobject.cbegin(), jobject2.cend()), json::invalid_iterator);
                    EXPECT_THROW(json(jobject2.cbegin(), jobject.cend()), json::invalid_iterator);
                    //CHECK_THROWS_WITH(json(jobject.cbegin(), jobject2.cend()), "[json.exception.invalid_iterator.201] iterators are not compatible");
                    //CHECK_THROWS_WITH(json(jobject2.cbegin(), jobject.cend()), "[json.exception.invalid_iterator.201] iterators are not compatible");
                }
            }
        }

        //TEST(constructors,"array")
        {
            //TEST(constructors,"json(begin(), end())")
            {
                {
                    json jarray = {1, 2, 3, 4, 5};
                    json j_new(jarray.begin(), jarray.end());
                    EXPECT_TRUE(j_new == jarray);
                }
                {
                    json jarray = {1, 2, 3, 4, 5};
                    json j_new(jarray.cbegin(), jarray.cend());
                    EXPECT_TRUE(j_new == jarray);
                }
            }

            //TEST(constructors,"json(begin(), begin())")
            {
                {
                    json jarray = {1, 2, 3, 4, 5};
                    json j_new(jarray.begin(), jarray.begin());
                    EXPECT_TRUE(j_new == json::array());
                }
                {
                    json jarray = {1, 2, 3, 4, 5};
                    json j_new(jarray.cbegin(), jarray.cbegin());
                    EXPECT_TRUE(j_new == json::array());
                }
            }

            //TEST(constructors,"construct from subrange")
            {
                {
                    json jarray = {1, 2, 3, 4, 5};
                    json j_new(jarray.begin() + 1, jarray.begin() + 3);
                    EXPECT_TRUE(j_new == json({2, 3}));
                }
                {
                    json jarray = {1, 2, 3, 4, 5};
                    json j_new(jarray.cbegin() + 1, jarray.cbegin() + 3);
                    EXPECT_TRUE(j_new == json({2, 3}));
                }
            }

            //TEST(constructors,"incompatible iterators")
            {
                {
                    json jarray = {1, 2, 3, 4};
                    json jarray2 = {2, 3, 4, 5};
                    EXPECT_THROW(json(jarray.begin(), jarray2.end()), json::invalid_iterator);
                    EXPECT_THROW(json(jarray2.begin(), jarray.end()), json::invalid_iterator);
                    //CHECK_THROWS_WITH(json(jarray.begin(), jarray2.end()), "[json.exception.invalid_iterator.201] iterators are not compatible");
                    //CHECK_THROWS_WITH(json(jarray2.begin(), jarray.end()), "[json.exception.invalid_iterator.201] iterators are not compatible");
                }
                {
                    json jarray = {1, 2, 3, 4};
                    json jarray2 = {2, 3, 4, 5};
                    EXPECT_THROW(json(jarray.cbegin(), jarray2.cend()), json::invalid_iterator);
                    EXPECT_THROW(json(jarray2.cbegin(), jarray.cend()), json::invalid_iterator);
                    //CHECK_THROWS_WITH(json(jarray.cbegin(), jarray2.cend()), "[json.exception.invalid_iterator.201] iterators are not compatible");
                    //CHECK_THROWS_WITH(json(jarray2.cbegin(), jarray.cend()), "[json.exception.invalid_iterator.201] iterators are not compatible");
                }
            }
        }

        //TEST(constructors,"other values")
        {
            //TEST(constructors,"construct with two valid iterators")
            {
                //TEST(constructors,"null")
                {
                    {
                        json j;
                        EXPECT_THROW(json(j.begin(), j.end()), json::invalid_iterator);
                        //CHECK_THROWS_WITH(json(j.begin(), j.end()),
                                          //"[json.exception.invalid_iterator.206] cannot construct with iterators from null");
                    }
                    {
                        json j;
                        EXPECT_THROW(json(j.cbegin(), j.cend()), json::invalid_iterator);
                        //CHECK_THROWS_WITH(json(j.cbegin(), j.cend()),
                                          //"[json.exception.invalid_iterator.206] cannot construct with iterators from null");
                    }
                }

                //TEST(constructors,"string")
                {
                    {
                        json j = "foo";
                        json j_new(j.begin(), j.end());
                        EXPECT_TRUE(j == j_new);
                    }
                    {
                        json j = "bar";
                        json j_new(j.cbegin(), j.cend());
                        EXPECT_TRUE(j == j_new);
                    }
                }

                //TEST(constructors,"number (boolean)")
                {
                    {
                        json j = false;
                        json j_new(j.begin(), j.end());
                        EXPECT_TRUE(j == j_new);
                    }
                    {
                        json j = true;
                        json j_new(j.cbegin(), j.cend());
                        EXPECT_TRUE(j == j_new);
                    }
                }

                //TEST(constructors,"number (integer)")
                {
                    {
                        json j = 17;
                        json j_new(j.begin(), j.end());
                        EXPECT_TRUE(j == j_new);
                    }
                    {
                        json j = 17;
                        json j_new(j.cbegin(), j.cend());
                        EXPECT_TRUE(j == j_new);
                    }
                }

                //TEST(constructors,"number (unsigned)")
                {
                    {
                        json j = 17u;
                        json j_new(j.begin(), j.end());
                        EXPECT_TRUE(j == j_new);
                    }
                    {
                        json j = 17u;
                        json j_new(j.cbegin(), j.cend());
                        EXPECT_TRUE(j == j_new);
                    }
                }

                //TEST(constructors,"number (floating point)")
                {
                    {
                        json j = 23.42;
                        json j_new(j.begin(), j.end());
                        EXPECT_TRUE(j == j_new);
                    }
                    {
                        json j = 23.42;
                        json j_new(j.cbegin(), j.cend());
                        EXPECT_TRUE(j == j_new);
                    }
                }
            }

            //TEST(constructors,"construct with two invalid iterators")
            {
                //TEST(constructors,"string")
                {
                    {
                        json j = "foo";
                        EXPECT_THROW(json(j.end(), j.end()), json::invalid_iterator);
                        EXPECT_THROW(json(j.begin(), j.begin()), json::invalid_iterator);
                        //CHECK_THROWS_WITH(json(j.end(), j.end()), "[json.exception.invalid_iterator.204] iterators out of range");
                        //CHECK_THROWS_WITH(json(j.begin(), j.begin()), "[json.exception.invalid_iterator.204] iterators out of range");
                    }
                    {
                        json j = "bar";
                        EXPECT_THROW(json(j.cend(), j.cend()), json::invalid_iterator);
                        EXPECT_THROW(json(j.cbegin(), j.cbegin()), json::invalid_iterator);
                        //CHECK_THROWS_WITH(json(j.cend(), j.cend()), "[json.exception.invalid_iterator.204] iterators out of range");
                        //CHECK_THROWS_WITH(json(j.cbegin(), j.cbegin()), "[json.exception.invalid_iterator.204] iterators out of range");
                    }
                }

                //TEST(constructors,"number (boolean)")
                {
                    {
                        json j = false;
                        EXPECT_THROW(json(j.end(), j.end()), json::invalid_iterator);
                        EXPECT_THROW(json(j.begin(), j.begin()), json::invalid_iterator);
                        //CHECK_THROWS_WITH(json(j.end(), j.end()), "[json.exception.invalid_iterator.204] iterators out of range");
                        //CHECK_THROWS_WITH(json(j.begin(), j.begin()), "[json.exception.invalid_iterator.204] iterators out of range");
                    }
                    {
                        json j = true;
                        EXPECT_THROW(json(j.cend(), j.cend()), json::invalid_iterator);
                        EXPECT_THROW(json(j.cbegin(), j.cbegin()), json::invalid_iterator);
                        //CHECK_THROWS_WITH(json(j.cend(), j.cend()), "[json.exception.invalid_iterator.204] iterators out of range");
                        //CHECK_THROWS_WITH(json(j.cbegin(), j.cbegin()), "[json.exception.invalid_iterator.204] iterators out of range");
                    }
                }

                //TEST(constructors,"number (integer)")
                {
                    {
                        json j = 17;
                        EXPECT_THROW(json(j.end(), j.end()), json::invalid_iterator);
                        EXPECT_THROW(json(j.begin(), j.begin()), json::invalid_iterator);
                        //CHECK_THROWS_WITH(json(j.end(), j.end()), "[json.exception.invalid_iterator.204] iterators out of range");
                        //CHECK_THROWS_WITH(json(j.begin(), j.begin()), "[json.exception.invalid_iterator.204] iterators out of range");
                    }
                    {
                        json j = 17;
                        EXPECT_THROW(json(j.cend(), j.cend()), json::invalid_iterator);
                        EXPECT_THROW(json(j.cbegin(), j.cbegin()), json::invalid_iterator);
                        //CHECK_THROWS_WITH(json(j.cend(), j.cend()), "[json.exception.invalid_iterator.204] iterators out of range");
                        //CHECK_THROWS_WITH(json(j.cbegin(), j.cbegin()), "[json.exception.invalid_iterator.204] iterators out of range");
                    }
                }

                //TEST(constructors,"number (integer)")
                {
                    {
                        json j = 17u;
                        EXPECT_THROW(json(j.end(), j.end()), json::invalid_iterator);
                        EXPECT_THROW(json(j.begin(), j.begin()), json::invalid_iterator);
                        //CHECK_THROWS_WITH(json(j.end(), j.end()), "[json.exception.invalid_iterator.204] iterators out of range");
                        //CHECK_THROWS_WITH(json(j.begin(), j.begin()), "[json.exception.invalid_iterator.204] iterators out of range");
                    }
                    {
                        json j = 17u;
                        EXPECT_THROW(json(j.cend(), j.cend()), json::invalid_iterator);
                        EXPECT_THROW(json(j.cbegin(), j.cbegin()), json::invalid_iterator);
                        //CHECK_THROWS_WITH(json(j.cend(), j.cend()), "[json.exception.invalid_iterator.204] iterators out of range");
                        //CHECK_THROWS_WITH(json(j.cbegin(), j.cbegin()), "[json.exception.invalid_iterator.204] iterators out of range");
                    }
                }

                //TEST(constructors,"number (floating point)")
                {
                    {
                        json j = 23.42;
                        EXPECT_THROW(json(j.end(), j.end()), json::invalid_iterator);
                        EXPECT_THROW(json(j.begin(), j.begin()), json::invalid_iterator);
                        //CHECK_THROWS_WITH(json(j.end(), j.end()), "[json.exception.invalid_iterator.204] iterators out of range");
                        //CHECK_THROWS_WITH(json(j.begin(), j.begin()), "[json.exception.invalid_iterator.204] iterators out of range");
                    }
                    {
                        json j = 23.42;
                        EXPECT_THROW(json(j.cend(), j.cend()), json::invalid_iterator);
                        EXPECT_THROW(json(j.cbegin(), j.cbegin()), json::invalid_iterator);
                        //CHECK_THROWS_WITH(json(j.cend(), j.cend()), "[json.exception.invalid_iterator.204] iterators out of range");
                        //CHECK_THROWS_WITH(json(j.cbegin(), j.cbegin()), "[json.exception.invalid_iterator.204] iterators out of range");
                    }
                }
            }
        }
    }
}
