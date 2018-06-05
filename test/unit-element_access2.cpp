#include "gtest/gtest.h"
#include "json.hpp"

using nlohmann::json;

namespace
{

	TEST(elementaccess, test1)
	{
		//TEST(constructors,"object")
		{
			json j = {{"integer", 1}, {"unsigned", 1u}, {"floating", 42.23}, {"null", nullptr}, {"string", "hello world"}, {"boolean", true}, {"object", json::object()}, {"array", {1, 2, 3}}};
			const json j_const = j;

			//TEST(constructors,"access specified element with bounds checking")
			{
				//TEST(constructors,"access within bounds")
				{
					EXPECT_TRUE(j.at("integer") == json(1));
					EXPECT_TRUE(j.at("unsigned") == json(1u));
					EXPECT_TRUE(j.at("boolean") == json(true));
					EXPECT_TRUE(j.at("null") == json(nullptr));
					EXPECT_TRUE(j.at("string") == json("hello world"));
					EXPECT_TRUE(j.at("floating") == json(42.23));
					EXPECT_TRUE(j.at("object") == json::object());
					EXPECT_TRUE(j.at("array") == json({1, 2, 3}));

					EXPECT_TRUE(j_const.at("integer") == json(1));
					EXPECT_TRUE(j_const.at("unsigned") == json(1u));
					EXPECT_TRUE(j_const.at("boolean") == json(true));
					EXPECT_TRUE(j_const.at("null") == json(nullptr));
					EXPECT_TRUE(j_const.at("string") == json("hello world"));
					EXPECT_TRUE(j_const.at("floating") == json(42.23));
					EXPECT_TRUE(j_const.at("object") == json::object());
					EXPECT_TRUE(j_const.at("array") == json({1, 2, 3}));
				}

				//TEST(constructors,"access outside bounds")
				{
					EXPECT_THROW(j.at("foo"), json::out_of_range);
					EXPECT_THROW(j_const.at("foo"), json::out_of_range);
					//CHECK_THROWS_WITH(j.at("foo"),
									  //"[json.exception.out_of_range.403] key 'foo' not found");
					//CHECK_THROWS_WITH(j_const.at("foo"),
									  //"[json.exception.out_of_range.403] key 'foo' not found");
				}

				//TEST(constructors,"access on non-object type")
				{
					//TEST(constructors,"null")
					{
						json j_nonobject(json::value_t::null);
						const json j_nonobject_const(j_nonobject);
						EXPECT_THROW(j_nonobject.at("foo"), json::type_error);
						EXPECT_THROW(j_nonobject_const.at("foo"), json::type_error);
						//CHECK_THROWS_WITH(j_nonobject.at("foo"), "[json.exception.type_error.304] cannot use at() with null");
						//CHECK_THROWS_WITH(j_nonobject_const.at("foo"), "[json.exception.type_error.304] cannot use at() with null");
					}

					//TEST(constructors,"boolean")
					{
						json j_nonobject(json::value_t::boolean);
						const json j_nonobject_const(j_nonobject);
						EXPECT_THROW(j_nonobject.at("foo"), json::type_error);
						EXPECT_THROW(j_nonobject_const.at("foo"), json::type_error);
						//CHECK_THROWS_WITH(j_nonobject.at("foo"), "[json.exception.type_error.304] cannot use at() with boolean");
						//CHECK_THROWS_WITH(j_nonobject_const.at("foo"), "[json.exception.type_error.304] cannot use at() with boolean");
					}

					//TEST(constructors,"string")
					{
						json j_nonobject(json::value_t::string);
						const json j_nonobject_const(j_nonobject);
						EXPECT_THROW(j_nonobject.at("foo"), json::type_error);
						EXPECT_THROW(j_nonobject_const.at("foo"), json::type_error);
						//CHECK_THROWS_WITH(j_nonobject.at("foo"), "[json.exception.type_error.304] cannot use at() with string");
						//CHECK_THROWS_WITH(j_nonobject_const.at("foo"), "[json.exception.type_error.304] cannot use at() with string");
					}

					//TEST(constructors,"array")
					{
						json j_nonobject(json::value_t::array);
						const json j_nonobject_const(j_nonobject);
						EXPECT_THROW(j_nonobject.at("foo"), json::type_error);
						EXPECT_THROW(j_nonobject_const.at("foo"), json::type_error);
						//CHECK_THROWS_WITH(j_nonobject.at("foo"), "[json.exception.type_error.304] cannot use at() with array");
						//CHECK_THROWS_WITH(j_nonobject_const.at("foo"), "[json.exception.type_error.304] cannot use at() with array");
					}

					//TEST(constructors,"number (integer)")
					{
						json j_nonobject(json::value_t::number_integer);
						const json j_nonobject_const(j_nonobject);
						EXPECT_THROW(j_nonobject.at("foo"), json::type_error);
						EXPECT_THROW(j_nonobject_const.at("foo"), json::type_error);
						//CHECK_THROWS_WITH(j_nonobject.at("foo"), "[json.exception.type_error.304] cannot use at() with number");
						//CHECK_THROWS_WITH(j_nonobject_const.at("foo"), "[json.exception.type_error.304] cannot use at() with number");
					}

					//TEST(constructors,"number (unsigned)")
					{
						json j_nonobject(json::value_t::number_unsigned);
						const json j_nonobject_const(j_nonobject);
						EXPECT_THROW(j_nonobject.at("foo"), json::type_error);
						EXPECT_THROW(j_nonobject_const.at("foo"), json::type_error);
						//CHECK_THROWS_WITH(j_nonobject.at("foo"), "[json.exception.type_error.304] cannot use at() with number");
						//CHECK_THROWS_WITH(j_nonobject_const.at("foo"), "[json.exception.type_error.304] cannot use at() with number");
					}

					//TEST(constructors,"number (floating-point)")
					{
						json j_nonobject(json::value_t::number_float);
						const json j_nonobject_const(j_nonobject);
						EXPECT_THROW(j_nonobject.at("foo"), json::type_error);
						EXPECT_THROW(j_nonobject_const.at("foo"), json::type_error);
						//CHECK_THROWS_WITH(j_nonobject.at("foo"), "[json.exception.type_error.304] cannot use at() with number");
						//CHECK_THROWS_WITH(j_nonobject_const.at("foo"), "[json.exception.type_error.304] cannot use at() with number");
					}
				}
			}

			//TEST(constructors,"access specified element with default value")
			{
				//TEST(constructors,"given a key")
				{
					//TEST(constructors,"access existing value")
					{
						EXPECT_TRUE(j.value("integer", 2) == 1);
						EXPECT_FLOAT_EQ(j.value("integer", 1.0), 1);
						EXPECT_TRUE(j.value("unsigned", 2) == 1u);
						EXPECT_FLOAT_EQ(j.value("unsigned", 1.0), 1u);
						EXPECT_TRUE(j.value("null", json(1)) == json());
						EXPECT_TRUE(j.value("boolean", false) == true);
						EXPECT_TRUE(j.value("string", "bar") == "hello world");
						EXPECT_TRUE(j.value("string", std::string("bar")) == "hello world");
						EXPECT_FLOAT_EQ(j.value("floating", 12.34), 42.23);
						EXPECT_TRUE(j.value("floating", 12) == 42);
						EXPECT_TRUE(j.value("object", json({{"foo", "bar"}})) == json::object());
						EXPECT_TRUE(j.value("array", json({10, 100})) == json({1, 2, 3}));

						EXPECT_TRUE(j_const.value("integer", 2) == 1);
						EXPECT_FLOAT_EQ(j_const.value("integer", 1.0), 1);
						EXPECT_TRUE(j_const.value("unsigned", 2) == 1u);
						EXPECT_FLOAT_EQ(j_const.value("unsigned", 1.0), 1u);
						EXPECT_TRUE(j_const.value("boolean", false) == true);
						EXPECT_TRUE(j_const.value("string", "bar") == "hello world");
						EXPECT_TRUE(j_const.value("string", std::string("bar")) == "hello world");
						EXPECT_FLOAT_EQ(j_const.value("floating", 12.34), 42.23);
						EXPECT_TRUE(j_const.value("floating", 12) == 42);
						EXPECT_TRUE(j_const.value("object", json({{"foo", "bar"}})) == json::object());
						EXPECT_TRUE(j_const.value("array", json({10, 100})) == json({1, 2, 3}));
					}

					//TEST(constructors,"access non-existing value")
					{
						EXPECT_TRUE(j.value("_", 2) == 2);
						EXPECT_TRUE(j.value("_", 2u) == 2u);
						EXPECT_TRUE(j.value("_", false) == false);
						EXPECT_TRUE(j.value("_", "bar") == "bar");
						EXPECT_FLOAT_EQ(j.value("_", 12.34), 12.34);
						EXPECT_TRUE(j.value("_", json({{"foo", "bar"}})) == json({{"foo", "bar"}}));
						EXPECT_TRUE(j.value("_", json({10, 100})) == json({10, 100}));

						EXPECT_TRUE(j_const.value("_", 2) == 2);
						EXPECT_TRUE(j_const.value("_", 2u) == 2u);
						EXPECT_TRUE(j_const.value("_", false) == false);
						EXPECT_TRUE(j_const.value("_", "bar") == "bar");
						EXPECT_FLOAT_EQ(j_const.value("_", 12.34), 12.34);
						EXPECT_TRUE(j_const.value("_", json({{"foo", "bar"}})) == json({{"foo", "bar"}}));
						EXPECT_TRUE(j_const.value("_", json({10, 100})) == json({10, 100}));
					}

					//TEST(constructors,"access on non-object type")
					{
						//TEST(constructors,"null")
						{
							json j_nonobject(json::value_t::null);
							const json j_nonobject_const(j_nonobject);
							EXPECT_THROW(j_nonobject.value("foo", 1), json::type_error);
							EXPECT_THROW(j_nonobject_const.value("foo", 1), json::type_error);
							//CHECK_THROWS_WITH(j_nonobject.value("foo", 1),
											  //"[json.exception.type_error.306] cannot use value() with null");
							//CHECK_THROWS_WITH(j_nonobject_const.value("foo", 1),
											  //"[json.exception.type_error.306] cannot use value() with null");
						}

						//TEST(constructors,"boolean")
						{
							json j_nonobject(json::value_t::boolean);
							const json j_nonobject_const(j_nonobject);
							EXPECT_THROW(j_nonobject.value("foo", 1), json::type_error);
							EXPECT_THROW(j_nonobject_const.value("foo", 1), json::type_error);
							//CHECK_THROWS_WITH(j_nonobject.value("foo", 1),
											  //"[json.exception.type_error.306] cannot use value() with boolean");
							//CHECK_THROWS_WITH(j_nonobject_const.value("foo", 1),
											  //"[json.exception.type_error.306] cannot use value() with boolean");
						}

						//TEST(constructors,"string")
						{
							json j_nonobject(json::value_t::string);
							const json j_nonobject_const(j_nonobject);
							EXPECT_THROW(j_nonobject.value("foo", 1), json::type_error);
							EXPECT_THROW(j_nonobject_const.value("foo", 1), json::type_error);
							//CHECK_THROWS_WITH(j_nonobject.value("foo", 1),
											  //"[json.exception.type_error.306] cannot use value() with string");
							//CHECK_THROWS_WITH(j_nonobject_const.value("foo", 1),
											  //"[json.exception.type_error.306] cannot use value() with string");
						}

						//TEST(constructors,"array")
						{
							json j_nonobject(json::value_t::array);
							const json j_nonobject_const(j_nonobject);
							EXPECT_THROW(j_nonobject.value("foo", 1), json::type_error);
							EXPECT_THROW(j_nonobject_const.value("foo", 1), json::type_error);
							//CHECK_THROWS_WITH(j_nonobject.value("foo", 1),
											  //"[json.exception.type_error.306] cannot use value() with array");
							//CHECK_THROWS_WITH(j_nonobject_const.value("foo", 1),
											  //"[json.exception.type_error.306] cannot use value() with array");
						}

						//TEST(constructors,"number (integer)")
						{
							json j_nonobject(json::value_t::number_integer);
							const json j_nonobject_const(j_nonobject);
							EXPECT_THROW(j_nonobject.value("foo", 1), json::type_error);
							EXPECT_THROW(j_nonobject_const.value("foo", 1), json::type_error);
							//CHECK_THROWS_WITH(j_nonobject.value("foo", 1),
											  //"[json.exception.type_error.306] cannot use value() with number");
							//CHECK_THROWS_WITH(j_nonobject_const.value("foo", 1),
											  //"[json.exception.type_error.306] cannot use value() with number");
						}

						//TEST(constructors,"number (unsigned)")
						{
							json j_nonobject(json::value_t::number_unsigned);
							const json j_nonobject_const(j_nonobject);
							EXPECT_THROW(j_nonobject.value("foo", 1), json::type_error);
							EXPECT_THROW(j_nonobject_const.value("foo", 1), json::type_error);
							//CHECK_THROWS_WITH(j_nonobject.value("foo", 1),
											  //"[json.exception.type_error.306] cannot use value() with number");
							//CHECK_THROWS_WITH(j_nonobject_const.value("foo", 1),
											  //"[json.exception.type_error.306] cannot use value() with number");
						}

						//TEST(constructors,"number (floating-point)")
						{
							json j_nonobject(json::value_t::number_float);
							const json j_nonobject_const(j_nonobject);
							EXPECT_THROW(j_nonobject.value("foo", 1), json::type_error);
							EXPECT_THROW(j_nonobject_const.value("foo", 1), json::type_error);
							//CHECK_THROWS_WITH(j_nonobject.value("foo", 1),
											  //"[json.exception.type_error.306] cannot use value() with number");
							//CHECK_THROWS_WITH(j_nonobject_const.value("foo", 1),
											  //"[json.exception.type_error.306] cannot use value() with number");
						}
					}
				}

				//TEST(constructors,"given a JSON pointer")
				{
					//TEST(constructors,"access existing value")
					{
						EXPECT_TRUE(j.value("/integer"_json_pointer, 2) == 1);
						EXPECT_FLOAT_EQ(j.value("/integer"_json_pointer, 1.0), 1);
						EXPECT_TRUE(j.value("/unsigned"_json_pointer, 2) == 1u);
						EXPECT_FLOAT_EQ(j.value("/unsigned"_json_pointer, 1.0), 1u);
						EXPECT_TRUE(j.value("/null"_json_pointer, json(1)) == json());
						EXPECT_TRUE(j.value("/boolean"_json_pointer, false) == true);
						EXPECT_TRUE(j.value("/string"_json_pointer, "bar") == "hello world");
						EXPECT_TRUE(j.value("/string"_json_pointer, std::string("bar")) == "hello world");
						EXPECT_FLOAT_EQ(j.value("/floating"_json_pointer, 12.34), 42.23);
						EXPECT_TRUE(j.value("/floating"_json_pointer, 12) == 42);
						EXPECT_TRUE(j.value("/object"_json_pointer, json({{"foo", "bar"}})) == json::object());
						EXPECT_TRUE(j.value("/array"_json_pointer, json({10, 100})) == json({1, 2, 3}));

						EXPECT_TRUE(j_const.value("/integer"_json_pointer, 2) == 1);
						EXPECT_FLOAT_EQ(j_const.value("/integer"_json_pointer, 1.0), 1);
						EXPECT_TRUE(j_const.value("/unsigned"_json_pointer, 2) == 1u);
						EXPECT_FLOAT_EQ(j_const.value("/unsigned"_json_pointer, 1.0), 1u);
						EXPECT_TRUE(j_const.value("/boolean"_json_pointer, false) == true);
						EXPECT_TRUE(j_const.value("/string"_json_pointer, "bar") == "hello world");
						EXPECT_TRUE(j_const.value("/string"_json_pointer, std::string("bar")) == "hello world");
						EXPECT_FLOAT_EQ(j_const.value("/floating"_json_pointer, 12.34), 42.23);
						EXPECT_TRUE(j_const.value("/floating"_json_pointer, 12) == 42);
						EXPECT_TRUE(j_const.value("/object"_json_pointer, json({{"foo", "bar"}})) == json::object());
						EXPECT_TRUE(j_const.value("/array"_json_pointer, json({10, 100})) == json({1, 2, 3}));
					}

					//TEST(constructors,"access on non-object type")
					{
						//TEST(constructors,"null")
						{
							json j_nonobject(json::value_t::null);
							const json j_nonobject_const(j_nonobject);
							EXPECT_THROW(j_nonobject.value("/foo"_json_pointer, 1), json::type_error);
							EXPECT_THROW(j_nonobject_const.value("/foo"_json_pointer, 1), json::type_error);
							//CHECK_THROWS_WITH(j_nonobject.value("/foo"_json_pointer, 1),
											  //"[json.exception.type_error.306] cannot use value() with null");
							//CHECK_THROWS_WITH(j_nonobject_const.value("/foo"_json_pointer, 1),
											  //"[json.exception.type_error.306] cannot use value() with null");
						}

						//TEST(constructors,"boolean")
						{
							json j_nonobject(json::value_t::boolean);
							const json j_nonobject_const(j_nonobject);
							EXPECT_THROW(j_nonobject.value("/foo"_json_pointer, 1), json::type_error);
							EXPECT_THROW(j_nonobject_const.value("/foo"_json_pointer, 1), json::type_error);
							//CHECK_THROWS_WITH(j_nonobject.value("/foo"_json_pointer, 1),
											  //"[json.exception.type_error.306] cannot use value() with boolean");
							//CHECK_THROWS_WITH(j_nonobject_const.value("/foo"_json_pointer, 1),
											  //"[json.exception.type_error.306] cannot use value() with boolean");
						}

						//TEST(constructors,"string")
						{
							json j_nonobject(json::value_t::string);
							const json j_nonobject_const(j_nonobject);
							EXPECT_THROW(j_nonobject.value("/foo"_json_pointer, 1), json::type_error);
							EXPECT_THROW(j_nonobject_const.value("/foo"_json_pointer, 1), json::type_error);
							//CHECK_THROWS_WITH(j_nonobject.value("/foo"_json_pointer, 1),
											  //"[json.exception.type_error.306] cannot use value() with string");
							//CHECK_THROWS_WITH(j_nonobject_const.value("/foo"_json_pointer, 1),
											  //"[json.exception.type_error.306] cannot use value() with string");
						}

						//TEST(constructors,"array")
						{
							json j_nonobject(json::value_t::array);
							const json j_nonobject_const(j_nonobject);
							EXPECT_THROW(j_nonobject.value("/foo"_json_pointer, 1), json::type_error);
							EXPECT_THROW(j_nonobject_const.value("/foo"_json_pointer, 1), json::type_error);
							//CHECK_THROWS_WITH(j_nonobject.value("/foo"_json_pointer, 1),
											  //"[json.exception.type_error.306] cannot use value() with array");
							//CHECK_THROWS_WITH(j_nonobject_const.value("/foo"_json_pointer, 1),
											  //"[json.exception.type_error.306] cannot use value() with array");
						}

						//TEST(constructors,"number (integer)")
						{
							json j_nonobject(json::value_t::number_integer);
							const json j_nonobject_const(j_nonobject);
							EXPECT_THROW(j_nonobject.value("/foo"_json_pointer, 1), json::type_error);
							EXPECT_THROW(j_nonobject_const.value("/foo"_json_pointer, 1), json::type_error);
							//CHECK_THROWS_WITH(j_nonobject.value("/foo"_json_pointer, 1),
											  //"[json.exception.type_error.306] cannot use value() with number");
							//CHECK_THROWS_WITH(j_nonobject_const.value("/foo"_json_pointer, 1),
											  //"[json.exception.type_error.306] cannot use value() with number");
						}

						//TEST(constructors,"number (unsigned)")
						{
							json j_nonobject(json::value_t::number_unsigned);
							const json j_nonobject_const(j_nonobject);
							EXPECT_THROW(j_nonobject.value("/foo"_json_pointer, 1), json::type_error);
							EXPECT_THROW(j_nonobject_const.value("/foo"_json_pointer, 1), json::type_error);
							//CHECK_THROWS_WITH(j_nonobject.value("/foo"_json_pointer, 1),
											  //"[json.exception.type_error.306] cannot use value() with number");
							//CHECK_THROWS_WITH(j_nonobject_const.value("/foo"_json_pointer, 1),
											  //"[json.exception.type_error.306] cannot use value() with number");
						}

						//TEST(constructors,"number (floating-point)")
						{
							json j_nonobject(json::value_t::number_float);
							const json j_nonobject_const(j_nonobject);
							EXPECT_THROW(j_nonobject.value("/foo"_json_pointer, 1), json::type_error);
							EXPECT_THROW(j_nonobject_const.value("/foo"_json_pointer, 1), json::type_error);
							//CHECK_THROWS_WITH(j_nonobject.value("/foo"_json_pointer, 1),
											  //"[json.exception.type_error.306] cannot use value() with number");
							//CHECK_THROWS_WITH(j_nonobject_const.value("/foo"_json_pointer, 1),
											  //"[json.exception.type_error.306] cannot use value() with number");
						}
					}
				}
			}

			//TEST(constructors,"front and back")
			{
				// "array" is the smallest key
				EXPECT_TRUE(j.front() == json({1, 2, 3}));
				EXPECT_TRUE(j_const.front() == json({1, 2, 3}));
				// "unsigned" is the largest key
				EXPECT_TRUE(j.back() == json(1u));
				EXPECT_TRUE(j_const.back() == json(1u));
			}

			//TEST(constructors,"access specified element")
			{
				//TEST(constructors,"access within bounds")
				{
					EXPECT_TRUE(j["integer"] == json(1));
					EXPECT_TRUE(j[json::object_t::key_type("integer")] == j["integer"]);

					EXPECT_TRUE(j["unsigned"] == json(1u));
					EXPECT_TRUE(j[json::object_t::key_type("unsigned")] == j["unsigned"]);

					EXPECT_TRUE(j["boolean"] == json(true));
					EXPECT_TRUE(j[json::object_t::key_type("boolean")] == j["boolean"]);

					EXPECT_TRUE(j["null"] == json(nullptr));
					EXPECT_TRUE(j[json::object_t::key_type("null")] == j["null"]);

					EXPECT_TRUE(j["string"] == json("hello world"));
					EXPECT_TRUE(j[json::object_t::key_type("string")] == j["string"]);

					EXPECT_TRUE(j["floating"] == json(42.23));
					EXPECT_TRUE(j[json::object_t::key_type("floating")] == j["floating"]);

					EXPECT_TRUE(j["object"] == json::object());
					EXPECT_TRUE(j[json::object_t::key_type("object")] == j["object"]);

					EXPECT_TRUE(j["array"] == json({1, 2, 3}));
					EXPECT_TRUE(j[json::object_t::key_type("array")] == j["array"]);

					EXPECT_TRUE(j_const["integer"] == json(1));
					EXPECT_TRUE(j_const[json::object_t::key_type("integer")] == j["integer"]);

					EXPECT_TRUE(j_const["boolean"] == json(true));
					EXPECT_TRUE(j_const[json::object_t::key_type("boolean")] == j["boolean"]);

					EXPECT_TRUE(j_const["null"] == json(nullptr));
					EXPECT_TRUE(j_const[json::object_t::key_type("null")] == j["null"]);

					EXPECT_TRUE(j_const["string"] == json("hello world"));
					EXPECT_TRUE(j_const[json::object_t::key_type("string")] == j["string"]);

					EXPECT_TRUE(j_const["floating"] == json(42.23));
					EXPECT_TRUE(j_const[json::object_t::key_type("floating")] == j["floating"]);

					EXPECT_TRUE(j_const["object"] == json::object());
					EXPECT_TRUE(j_const[json::object_t::key_type("object")] == j["object"]);

					EXPECT_TRUE(j_const["array"] == json({1, 2, 3}));
					EXPECT_TRUE(j_const[json::object_t::key_type("array")] == j["array"]);
				}

				//TEST(constructors,"access on non-object type")
				{
					//TEST(constructors,"null")
					{
						json j_nonobject(json::value_t::null);
						json j_nonobject2(json::value_t::null);
						const json j_const_nonobject(j_nonobject);
						EXPECT_NO_THROW(j_nonobject["foo"]);
						EXPECT_NO_THROW(j_nonobject2[json::object_t::key_type("foo")]);
						EXPECT_THROW(j_const_nonobject["foo"], json::type_error);
						EXPECT_THROW(j_const_nonobject[json::object_t::key_type("foo")], json::type_error);
						//CHECK_THROWS_WITH(j_const_nonobject["foo"], "[json.exception.type_error.305] cannot use operator[] with null");
						//CHECK_THROWS_WITH(j_const_nonobject[json::object_t::key_type("foo")],
										  //"[json.exception.type_error.305] cannot use operator[] with null");
					}

					//TEST(constructors,"boolean")
					{
						json j_nonobject(json::value_t::boolean);
						const json j_const_nonobject(j_nonobject);
						EXPECT_THROW(j_nonobject["foo"], json::type_error);
						EXPECT_THROW(j_nonobject[json::object_t::key_type("foo")], json::type_error);
						EXPECT_THROW(j_const_nonobject["foo"], json::type_error);
						EXPECT_THROW(j_const_nonobject[json::object_t::key_type("foo")], json::type_error);
						//CHECK_THROWS_WITH(j_nonobject["foo"],
										  //"[json.exception.type_error.305] cannot use operator[] with boolean");
						//CHECK_THROWS_WITH(j_nonobject[json::object_t::key_type("foo")],
										  //"[json.exception.type_error.305] cannot use operator[] with boolean");
						//CHECK_THROWS_WITH(j_const_nonobject["foo"],
										  //"[json.exception.type_error.305] cannot use operator[] with boolean");
						//CHECK_THROWS_WITH(j_const_nonobject[json::object_t::key_type("foo")],
										  //"[json.exception.type_error.305] cannot use operator[] with boolean");
					}

					//TEST(constructors,"string")
					{
						json j_nonobject(json::value_t::string);
						const json j_const_nonobject(j_nonobject);
						EXPECT_THROW(j_nonobject["foo"], json::type_error);
						EXPECT_THROW(j_nonobject[json::object_t::key_type("foo")], json::type_error);
						EXPECT_THROW(j_const_nonobject["foo"], json::type_error);
						EXPECT_THROW(j_const_nonobject[json::object_t::key_type("foo")], json::type_error);
						//CHECK_THROWS_WITH(j_nonobject["foo"],
										  //"[json.exception.type_error.305] cannot use operator[] with string");
						//CHECK_THROWS_WITH(j_nonobject[json::object_t::key_type("foo")],
										  //"[json.exception.type_error.305] cannot use operator[] with string");
						//CHECK_THROWS_WITH(j_const_nonobject["foo"],
										  //"[json.exception.type_error.305] cannot use operator[] with string");
						//CHECK_THROWS_WITH(j_const_nonobject[json::object_t::key_type("foo")],
										  //"[json.exception.type_error.305] cannot use operator[] with string");
					}

					//TEST(constructors,"array")
					{
						json j_nonobject(json::value_t::array);
						const json j_const_nonobject(j_nonobject);
						EXPECT_THROW(j_nonobject["foo"], json::type_error);
						EXPECT_THROW(j_nonobject[json::object_t::key_type("foo")], json::type_error);
						EXPECT_THROW(j_const_nonobject["foo"], json::type_error);
						EXPECT_THROW(j_const_nonobject[json::object_t::key_type("foo")], json::type_error);
						//CHECK_THROWS_WITH(j_nonobject["foo"],
										  //"[json.exception.type_error.305] cannot use operator[] with array");
						//CHECK_THROWS_WITH(j_nonobject[json::object_t::key_type("foo")], "[json.exception.type_error.305] cannot use operator[] with array");
						//CHECK_THROWS_WITH(j_const_nonobject["foo"],
										  //"[json.exception.type_error.305] cannot use operator[] with array");
						//CHECK_THROWS_WITH(j_const_nonobject[json::object_t::key_type("foo")],
										  //"[json.exception.type_error.305] cannot use operator[] with array");
					}

					//TEST(constructors,"number (integer)")
					{
						json j_nonobject(json::value_t::number_integer);
						const json j_const_nonobject(j_nonobject);
						EXPECT_THROW(j_nonobject["foo"], json::type_error);
						EXPECT_THROW(j_nonobject[json::object_t::key_type("foo")], json::type_error);
						EXPECT_THROW(j_const_nonobject["foo"], json::type_error);
						EXPECT_THROW(j_const_nonobject[json::object_t::key_type("foo")], json::type_error);
						//CHECK_THROWS_WITH(j_nonobject["foo"],
										  //"[json.exception.type_error.305] cannot use operator[] with number");
						//CHECK_THROWS_WITH(j_nonobject[json::object_t::key_type("foo")],
										  //"[json.exception.type_error.305] cannot use operator[] with number");
						//CHECK_THROWS_WITH(j_const_nonobject["foo"],
										  //"[json.exception.type_error.305] cannot use operator[] with number");
						//CHECK_THROWS_WITH(j_const_nonobject[json::object_t::key_type("foo")],
										  //"[json.exception.type_error.305] cannot use operator[] with number");
					}

					//TEST(constructors,"number (unsigned)")
					{
						json j_nonobject(json::value_t::number_unsigned);
						const json j_const_nonobject(j_nonobject);
						EXPECT_THROW(j_nonobject["foo"], json::type_error);
						EXPECT_THROW(j_nonobject[json::object_t::key_type("foo")], json::type_error);
						EXPECT_THROW(j_const_nonobject["foo"], json::type_error);
						EXPECT_THROW(j_const_nonobject[json::object_t::key_type("foo")], json::type_error);
						//CHECK_THROWS_WITH(j_nonobject["foo"],
										  //"[json.exception.type_error.305] cannot use operator[] with number");
						//CHECK_THROWS_WITH(j_nonobject[json::object_t::key_type("foo")],
										  //"[json.exception.type_error.305] cannot use operator[] with number");
						//CHECK_THROWS_WITH(j_const_nonobject["foo"],
										  //"[json.exception.type_error.305] cannot use operator[] with number");
						//CHECK_THROWS_WITH(j_const_nonobject[json::object_t::key_type("foo")],
										  //"[json.exception.type_error.305] cannot use operator[] with number");
					}

					//TEST(constructors,"number (floating-point)")
					{
						json j_nonobject(json::value_t::number_float);
						const json j_const_nonobject(j_nonobject);
						EXPECT_THROW(j_nonobject["foo"], json::type_error);
						EXPECT_THROW(j_nonobject[json::object_t::key_type("foo")], json::type_error);
						EXPECT_THROW(j_const_nonobject["foo"], json::type_error);
						EXPECT_THROW(j_const_nonobject[json::object_t::key_type("foo")], json::type_error);
						//CHECK_THROWS_WITH(j_nonobject["foo"],
										  //"[json.exception.type_error.305] cannot use operator[] with number");
						//CHECK_THROWS_WITH(j_nonobject[json::object_t::key_type("foo")],
										  //"[json.exception.type_error.305] cannot use operator[] with number");
						//CHECK_THROWS_WITH(j_const_nonobject["foo"],
										  //"[json.exception.type_error.305] cannot use operator[] with number");
						//CHECK_THROWS_WITH(j_const_nonobject[json::object_t::key_type("foo")],
										  //"[json.exception.type_error.305] cannot use operator[] with number");
					}
				}
			}

			//TEST(constructors,"remove specified element")
			{
				//TEST(constructors,"remove element by key")
				{
					EXPECT_TRUE(j.find("integer") != j.end());
					EXPECT_TRUE(j.erase("integer") == 1);
					EXPECT_TRUE(j.find("integer") == j.end());
					EXPECT_TRUE(j.erase("integer") == 0);

					EXPECT_TRUE(j.find("unsigned") != j.end());
					EXPECT_TRUE(j.erase("unsigned") == 1);
					EXPECT_TRUE(j.find("unsigned") == j.end());
					EXPECT_TRUE(j.erase("unsigned") == 0);

					EXPECT_TRUE(j.find("boolean") != j.end());
					EXPECT_TRUE(j.erase("boolean") == 1);
					EXPECT_TRUE(j.find("boolean") == j.end());
					EXPECT_TRUE(j.erase("boolean") == 0);

					EXPECT_TRUE(j.find("null") != j.end());
					EXPECT_TRUE(j.erase("null") == 1);
					EXPECT_TRUE(j.find("null") == j.end());
					EXPECT_TRUE(j.erase("null") == 0);

					EXPECT_TRUE(j.find("string") != j.end());
					EXPECT_TRUE(j.erase("string") == 1);
					EXPECT_TRUE(j.find("string") == j.end());
					EXPECT_TRUE(j.erase("string") == 0);

					EXPECT_TRUE(j.find("floating") != j.end());
					EXPECT_TRUE(j.erase("floating") == 1);
					EXPECT_TRUE(j.find("floating") == j.end());
					EXPECT_TRUE(j.erase("floating") == 0);

					EXPECT_TRUE(j.find("object") != j.end());
					EXPECT_TRUE(j.erase("object") == 1);
					EXPECT_TRUE(j.find("object") == j.end());
					EXPECT_TRUE(j.erase("object") == 0);

					EXPECT_TRUE(j.find("array") != j.end());
					EXPECT_TRUE(j.erase("array") == 1);
					EXPECT_TRUE(j.find("array") == j.end());
					EXPECT_TRUE(j.erase("array") == 0);
				}

				//TEST(constructors,"remove element by iterator")
				{
					//TEST(constructors,"erase(begin())")
					{
						{
							json jobject = {{"a", "a"}, {"b", 1}, {"c", 17u}};
							json::iterator it2 = jobject.erase(jobject.begin());
							EXPECT_TRUE(jobject == json({{"b", 1}, {"c", 17u}}));
							EXPECT_TRUE(*it2 == json(1));
						}
						{
							json jobject = {{"a", "a"}, {"b", 1}, {"c", 17u}};
							json::const_iterator it2 = jobject.erase(jobject.cbegin());
							EXPECT_TRUE(jobject == json({{"b", 1}, {"c", 17u}}));
							EXPECT_TRUE(*it2 == json(1));
						}
					}

					//TEST(constructors,"erase(begin(), end())")
					{
						{
							json jobject = {{"a", "a"}, {"b", 1}, {"c", 17u}};
							json::iterator it2 = jobject.erase(jobject.begin(), jobject.end());
							EXPECT_TRUE(jobject == json::object());
							EXPECT_TRUE(it2 == jobject.end());
						}
						{
							json jobject = {{"a", "a"}, {"b", 1}, {"c", 17u}};
							json::const_iterator it2 = jobject.erase(jobject.cbegin(), jobject.cend());
							EXPECT_TRUE(jobject == json::object());
							EXPECT_TRUE(it2 == jobject.cend());
						}
					}

					//TEST(constructors,"erase(begin(), begin())")
					{
						{
							json jobject = {{"a", "a"}, {"b", 1}, {"c", 17u}};
							json::iterator it2 = jobject.erase(jobject.begin(), jobject.begin());
							EXPECT_TRUE(jobject == json({{"a", "a"}, {"b", 1}, {"c", 17u}}));
							EXPECT_TRUE(*it2 == json("a"));
						}
						{
							json jobject = {{"a", "a"}, {"b", 1}, {"c", 17u}};
							json::const_iterator it2 = jobject.erase(jobject.cbegin(), jobject.cbegin());
							EXPECT_TRUE(jobject == json({{"a", "a"}, {"b", 1}, {"c", 17u}}));
							EXPECT_TRUE(*it2 == json("a"));
						}
					}

					//TEST(constructors,"erase at offset")
					{
						{
							json jobject = {{"a", "a"}, {"b", 1}, {"c", 17u}};
							json::iterator it = jobject.find("b");
							json::iterator it2 = jobject.erase(it);
							EXPECT_TRUE(jobject == json({{"a", "a"}, {"c", 17u}}));
							EXPECT_TRUE(*it2 == json(17));
						}
						{
							json jobject = {{"a", "a"}, {"b", 1}, {"c", 17u}};
							json::const_iterator it = jobject.find("b");
							json::const_iterator it2 = jobject.erase(it);
							EXPECT_TRUE(jobject == json({{"a", "a"}, {"c", 17u}}));
							EXPECT_TRUE(*it2 == json(17));
						}
					}

					//TEST(constructors,"erase subrange")
					{
						{
							json jobject = {{"a", "a"}, {"b", 1}, {"c", 17u}, {"d", false}, {"e", true}};
							json::iterator it2 = jobject.erase(jobject.find("b"), jobject.find("e"));
							EXPECT_TRUE(jobject == json({{"a", "a"}, {"e", true}}));
							EXPECT_TRUE(*it2 == json(true));
						}
						{
							json jobject = {{"a", "a"}, {"b", 1}, {"c", 17u}, {"d", false}, {"e", true}};
							json::const_iterator it2 = jobject.erase(jobject.find("b"), jobject.find("e"));
							EXPECT_TRUE(jobject == json({{"a", "a"}, {"e", true}}));
							EXPECT_TRUE(*it2 == json(true));
						}
					}

					//TEST(constructors,"different objects")
					{
						{
							json jobject = {{"a", "a"}, {"b", 1}, {"c", 17u}, {"d", false}, {"e", true}};
							json jobject2 = {{"a", "a"}, {"b", 1}, {"c", 17u}};
							EXPECT_THROW(jobject.erase(jobject2.begin()), json::invalid_iterator);
							EXPECT_THROW(jobject.erase(jobject.begin(), jobject2.end()), json::invalid_iterator);
							EXPECT_THROW(jobject.erase(jobject2.begin(), jobject.end()), json::invalid_iterator);
							EXPECT_THROW(jobject.erase(jobject2.begin(), jobject2.end()), json::invalid_iterator);
							//CHECK_THROWS_WITH(jobject.erase(jobject2.begin()),
											  //"[json.exception.invalid_iterator.202] iterator does not fit current value");
							//CHECK_THROWS_WITH(jobject.erase(jobject.begin(), jobject2.end()),
											  //"[json.exception.invalid_iterator.203] iterators do not fit current value");
							//CHECK_THROWS_WITH(jobject.erase(jobject2.begin(), jobject.end()),
											  //"[json.exception.invalid_iterator.203] iterators do not fit current value");
							//CHECK_THROWS_WITH(jobject.erase(jobject2.begin(), jobject2.end()),
											  //"[json.exception.invalid_iterator.203] iterators do not fit current value");
						}
						{
							json jobject = {{"a", "a"}, {"b", 1}, {"c", 17u}, {"d", false}, {"e", true}};
							json jobject2 = {{"a", "a"}, {"b", 1}, {"c", 17u}};
							EXPECT_THROW(jobject.erase(jobject2.cbegin()), json::invalid_iterator);
							EXPECT_THROW(jobject.erase(jobject.cbegin(), jobject2.cend()), json::invalid_iterator);
							EXPECT_THROW(jobject.erase(jobject2.cbegin(), jobject.cend()), json::invalid_iterator);
							EXPECT_THROW(jobject.erase(jobject2.cbegin(), jobject2.cend()), json::invalid_iterator);
							//CHECK_THROWS_WITH(jobject.erase(jobject2.cbegin()),
											  //"[json.exception.invalid_iterator.202] iterator does not fit current value");
							//CHECK_THROWS_WITH(jobject.erase(jobject.cbegin(), jobject2.cend()),
											  //"[json.exception.invalid_iterator.203] iterators do not fit current value");
							//CHECK_THROWS_WITH(jobject.erase(jobject2.cbegin(), jobject.cend()),
											  //"[json.exception.invalid_iterator.203] iterators do not fit current value");
							//CHECK_THROWS_WITH(jobject.erase(jobject2.cbegin(), jobject2.cend()),
											  //"[json.exception.invalid_iterator.203] iterators do not fit current value");
						}
					}
				}

				//TEST(constructors,"remove element by key in non-object type")
				{
					//TEST(constructors,"null")
					{
						json j_nonobject(json::value_t::null);
						EXPECT_THROW(j_nonobject.erase("foo"), json::type_error);
						//CHECK_THROWS_WITH(j_nonobject.erase("foo"),
										  //"[json.exception.type_error.307] cannot use erase() with null");
					}

					//TEST(constructors,"boolean")
					{
						json j_nonobject(json::value_t::boolean);
						EXPECT_THROW(j_nonobject.erase("foo"), json::type_error);
						//CHECK_THROWS_WITH(j_nonobject.erase("foo"),
										  //"[json.exception.type_error.307] cannot use erase() with boolean");
					}

					//TEST(constructors,"string")
					{
						json j_nonobject(json::value_t::string);
						EXPECT_THROW(j_nonobject.erase("foo"), json::type_error);
						//CHECK_THROWS_WITH(j_nonobject.erase("foo"),
										  //"[json.exception.type_error.307] cannot use erase() with string");
					}

					//TEST(constructors,"array")
					{
						json j_nonobject(json::value_t::array);
						EXPECT_THROW(j_nonobject.erase("foo"), json::type_error);
						//CHECK_THROWS_WITH(j_nonobject.erase("foo"),
										  //"[json.exception.type_error.307] cannot use erase() with array");
					}

					//TEST(constructors,"number (integer)")
					{
						json j_nonobject(json::value_t::number_integer);
						EXPECT_THROW(j_nonobject.erase("foo"), json::type_error);
						//CHECK_THROWS_WITH(j_nonobject.erase("foo"),
										  //"[json.exception.type_error.307] cannot use erase() with number");
					}

					//TEST(constructors,"number (floating-point)")
					{
						json j_nonobject(json::value_t::number_float);
						EXPECT_THROW(j_nonobject.erase("foo"), json::type_error);
						//CHECK_THROWS_WITH(j_nonobject.erase("foo"),
										  //"[json.exception.type_error.307] cannot use erase() with number");
					}
				}
			}

			//TEST(constructors,"find an element in an object")
			{
				//TEST(constructors,"existing element")
				{
					json j = {{"integer", 1}, {"unsigned", 1u}, {"floating", 42.23}, {"null", nullptr}, {"string", "hello world"}, {"boolean", true}, {"object", json::object()}, {"array", {1, 2, 3}}};
					const json j_const = j;
					for (auto key :
							{"integer", "unsigned", "floating", "null", "string", "boolean", "object", "array"
							})
					{
						EXPECT_TRUE(j.find(key) != j.end());
						EXPECT_TRUE(*j.find(key) == j.at(key));
						EXPECT_TRUE(j_const.find(key) != j_const.end());
						EXPECT_TRUE(*j_const.find(key) == j_const.at(key));
					}
				}

				//TEST(constructors,"nonexisting element")
				{
					EXPECT_TRUE(j.find("foo") == j.end());
					EXPECT_TRUE(j_const.find("foo") == j_const.end());
				}

				//TEST(constructors,"all types")
				{
					//TEST(constructors,"null")
					{
						json j_nonarray(json::value_t::null);
						const json j_nonarray_const(j_nonarray);
						EXPECT_TRUE(j_nonarray.find("foo") == j_nonarray.end());
						EXPECT_TRUE(j_nonarray_const.find("foo") == j_nonarray_const.end());
					}

					//TEST(constructors,"string")
					{
						json j_nonarray(json::value_t::string);
						const json j_nonarray_const(j_nonarray);
						EXPECT_TRUE(j_nonarray.find("foo") == j_nonarray.end());
						EXPECT_TRUE(j_nonarray_const.find("foo") == j_nonarray_const.end());
					}

					//TEST(constructors,"object")
					{
						json j_nonarray(json::value_t::object);
						const json j_nonarray_const(j_nonarray);
						EXPECT_TRUE(j_nonarray.find("foo") == j_nonarray.end());
						EXPECT_TRUE(j_nonarray_const.find("foo") == j_nonarray_const.end());
					}

					//TEST(constructors,"array")
					{
						json j_nonarray(json::value_t::array);
						const json j_nonarray_const(j_nonarray);
						EXPECT_TRUE(j_nonarray.find("foo") == j_nonarray.end());
						EXPECT_TRUE(j_nonarray_const.find("foo") == j_nonarray_const.end());
					}

					//TEST(constructors,"boolean")
					{
						json j_nonarray(json::value_t::boolean);
						const json j_nonarray_const(j_nonarray);
						EXPECT_TRUE(j_nonarray.find("foo") == j_nonarray.end());
						EXPECT_TRUE(j_nonarray_const.find("foo") == j_nonarray_const.end());
					}

					//TEST(constructors,"number (integer)")
					{
						json j_nonarray(json::value_t::number_integer);
						const json j_nonarray_const(j_nonarray);
						EXPECT_TRUE(j_nonarray.find("foo") == j_nonarray.end());
						EXPECT_TRUE(j_nonarray_const.find("foo") == j_nonarray_const.end());
					}

					//TEST(constructors,"number (unsigned)")
					{
						json j_nonarray(json::value_t::number_unsigned);
						const json j_nonarray_const(j_nonarray);
						EXPECT_TRUE(j_nonarray.find("foo") == j_nonarray.end());
						EXPECT_TRUE(j_nonarray_const.find("foo") == j_nonarray_const.end());
					}

					//TEST(constructors,"number (floating-point)")
					{
						json j_nonarray(json::value_t::number_float);
						const json j_nonarray_const(j_nonarray);
						EXPECT_TRUE(j_nonarray.find("foo") == j_nonarray.end());
						EXPECT_TRUE(j_nonarray_const.find("foo") == j_nonarray_const.end());
					}
				}
			}

			//TEST(constructors,"count keys in an object")
			{
				//TEST(constructors,"existing element")
				{
					json j = {{"integer", 1}, {"unsigned", 1u}, {"floating", 42.23}, {"null", nullptr}, {"string", "hello world"}, {"boolean", true}, {"object", json::object()}, {"array", {1, 2, 3}}};
					const json j_const = j;
					for (auto key :
							{"integer", "unsigned", "floating", "null", "string", "boolean", "object", "array"
							})
					{
						EXPECT_TRUE(j.count(key) == 1);
						EXPECT_TRUE(j_const.count(key) == 1);
					}
				}

				//TEST(constructors,"nonexisting element")
				{
					EXPECT_TRUE(j.count("foo") == 0);
					EXPECT_TRUE(j_const.count("foo") == 0);
				}

				//TEST(constructors,"all types")
				{
					//TEST(constructors,"null")
					{
						json j_nonobject(json::value_t::null);
						const json j_nonobject_const(j_nonobject);
						EXPECT_TRUE(j_nonobject.count("foo") == 0);
						EXPECT_TRUE(j_nonobject_const.count("foo") == 0);
					}

					//TEST(constructors,"string")
					{
						json j_nonobject(json::value_t::string);
						const json j_nonobject_const(j_nonobject);
						EXPECT_TRUE(j_nonobject.count("foo") == 0);
						EXPECT_TRUE(j_nonobject_const.count("foo") == 0);
					}

					//TEST(constructors,"object")
					{
						json j_nonobject(json::value_t::object);
						const json j_nonobject_const(j_nonobject);
						EXPECT_TRUE(j_nonobject.count("foo") == 0);
						EXPECT_TRUE(j_nonobject_const.count("foo") == 0);
					}

					//TEST(constructors,"array")
					{
						json j_nonobject(json::value_t::array);
						const json j_nonobject_const(j_nonobject);
						EXPECT_TRUE(j_nonobject.count("foo") == 0);
						EXPECT_TRUE(j_nonobject_const.count("foo") == 0);
					}

					//TEST(constructors,"boolean")
					{
						json j_nonobject(json::value_t::boolean);
						const json j_nonobject_const(j_nonobject);
						EXPECT_TRUE(j_nonobject.count("foo") == 0);
						EXPECT_TRUE(j_nonobject_const.count("foo") == 0);
					}

					//TEST(constructors,"number (integer)")
					{
						json j_nonobject(json::value_t::number_integer);
						const json j_nonobject_const(j_nonobject);
						EXPECT_TRUE(j_nonobject.count("foo") == 0);
						EXPECT_TRUE(j_nonobject_const.count("foo") == 0);
					}

					//TEST(constructors,"number (unsigned)")
					{
						json j_nonobject(json::value_t::number_unsigned);
						const json j_nonobject_const(j_nonobject);
						EXPECT_TRUE(j_nonobject.count("foo") == 0);
						EXPECT_TRUE(j_nonobject_const.count("foo") == 0);
					}

					//TEST(constructors,"number (floating-point)")
					{
						json j_nonobject(json::value_t::number_float);
						const json j_nonobject_const(j_nonobject);
						EXPECT_TRUE(j_nonobject.count("foo") == 0);
						EXPECT_TRUE(j_nonobject_const.count("foo") == 0);
					}
				}
			}
		}
	}

	TEST(elementaccess, test2)
	{
		//TEST(constructors,"object")
		{
			json j = {{"integer", 1}, {"unsigned", 1u}, {"floating", 42.23}, {"null", nullptr}, {"string", "hello world"}, {"boolean", true}, {"object", json::object()}, {"array", {1, 2, 3}}};
			const json j_const = j;

			//TEST(constructors,"access specified element with default value")
			{
				//TEST(constructors,"given a JSON pointer")
				{
					//TEST(constructors,"access non-existing value")
					{
						EXPECT_TRUE(j.value("/not/existing"_json_pointer, 2) == 2);
						EXPECT_TRUE(j.value("/not/existing"_json_pointer, 2u) == 2u);
						EXPECT_TRUE(j.value("/not/existing"_json_pointer, false) == false);
						EXPECT_TRUE(j.value("/not/existing"_json_pointer, "bar") == "bar");
						EXPECT_FLOAT_EQ(j.value("/not/existing"_json_pointer, 12.34), 12.34);
						EXPECT_TRUE(j.value("/not/existing"_json_pointer, json({{"foo", "bar"}})) == json({{"foo", "bar"}}));
						EXPECT_TRUE(j.value("/not/existing"_json_pointer, json({10, 100})) == json({10, 100}));

						EXPECT_TRUE(j_const.value("/not/existing"_json_pointer, 2) == 2);
						EXPECT_TRUE(j_const.value("/not/existing"_json_pointer, 2u) == 2u);
						EXPECT_TRUE(j_const.value("/not/existing"_json_pointer, false) == false);
						EXPECT_TRUE(j_const.value("/not/existing"_json_pointer, "bar") == "bar");
						EXPECT_FLOAT_EQ(j_const.value("/not/existing"_json_pointer, 12.34), 12.34);
						EXPECT_TRUE(j_const.value("/not/existing"_json_pointer, json({{"foo", "bar"}})) == json({{"foo", "bar"}}));
						EXPECT_TRUE(j_const.value("/not/existing"_json_pointer, json({10, 100})) == json({10, 100}));
					}
				}
			}
		}
	}
}
