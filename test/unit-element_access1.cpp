#include "gtest/gtest.h"
#include "json.hpp"

using nlohmann::json;

namespace
{
	TEST(element_access, element_access)
	{
		//TEST(constructors,"array")
		{
			json j = {1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}};
			const json j_const = j;

			//TEST(constructors,"access specified element with bounds checking")
			{
				//TEST(constructors,"access within bounds")
				{
					EXPECT_TRUE(j.at(0) == json(1));
					EXPECT_TRUE(j.at(1) == json(1u));
					EXPECT_TRUE(j.at(2) == json(true));
					EXPECT_TRUE(j.at(3) == json(nullptr));
					EXPECT_TRUE(j.at(4) == json("string"));
					EXPECT_TRUE(j.at(5) == json(42.23));
					EXPECT_TRUE(j.at(6) == json::object());
					EXPECT_TRUE(j.at(7) == json({1, 2, 3}));

					EXPECT_TRUE(j_const.at(0) == json(1));
					EXPECT_TRUE(j_const.at(1) == json(1u));
					EXPECT_TRUE(j_const.at(2) == json(true));
					EXPECT_TRUE(j_const.at(3) == json(nullptr));
					EXPECT_TRUE(j_const.at(4) == json("string"));
					EXPECT_TRUE(j_const.at(5) == json(42.23));
					EXPECT_TRUE(j_const.at(6) == json::object());
					EXPECT_TRUE(j_const.at(7) == json({1, 2, 3}));
				}

				//TEST(constructors,"access outside bounds")
				{
					EXPECT_THROW(j.at(8), json::out_of_range);
					EXPECT_THROW(j_const.at(8), json::out_of_range);

					//CHECK_THROWS_WITH(j.at(8),
									  //"[json.exception.out_of_range.401] array index 8 is out of range");
					//CHECK_THROWS_WITH(j_const.at(8),
									  //"[json.exception.out_of_range.401] array index 8 is out of range");
				}

				//TEST(constructors,"access on non-array type")
				{
					//TEST(constructors,"null")
					{
						json j_nonarray(json::value_t::null);
						const json j_nonarray_const(j_nonarray);
						EXPECT_THROW(j_nonarray.at(0), json::type_error);
						EXPECT_THROW(j_nonarray_const.at(0), json::type_error);

						//CHECK_THROWS_WITH(j_nonarray.at(0), "[json.exception.type_error.304] cannot use at() with null");
						//CHECK_THROWS_WITH(j_nonarray_const.at(0), "[json.exception.type_error.304] cannot use at() with null");
					}

					//TEST(constructors,"boolean")
					{
						json j_nonarray(json::value_t::boolean);
						const json j_nonarray_const(j_nonarray);
						EXPECT_THROW(j_nonarray.at(0), json::type_error);
						EXPECT_THROW(j_nonarray_const.at(0), json::type_error);

						//CHECK_THROWS_WITH(j_nonarray.at(0), "[json.exception.type_error.304] cannot use at() with boolean");
						//CHECK_THROWS_WITH(j_nonarray_const.at(0), "[json.exception.type_error.304] cannot use at() with boolean");
					}

					//TEST(constructors,"string")
					{
						json j_nonarray(json::value_t::string);
						const json j_nonarray_const(j_nonarray);
						EXPECT_THROW(j_nonarray.at(0), json::type_error);
						EXPECT_THROW(j_nonarray_const.at(0), json::type_error);

						//CHECK_THROWS_WITH(j_nonarray.at(0), "[json.exception.type_error.304] cannot use at() with string");
						//CHECK_THROWS_WITH(j_nonarray_const.at(0), "[json.exception.type_error.304] cannot use at() with string");
					}

					//TEST(constructors,"object")
					{
						json j_nonarray(json::value_t::object);
						const json j_nonarray_const(j_nonarray);
						EXPECT_THROW(j_nonarray.at(0), json::type_error);
						EXPECT_THROW(j_nonarray_const.at(0), json::type_error);

						//CHECK_THROWS_WITH(j_nonarray.at(0), "[json.exception.type_error.304] cannot use at() with object");
						//CHECK_THROWS_WITH(j_nonarray_const.at(0), "[json.exception.type_error.304] cannot use at() with object");
					}

					//TEST(constructors,"number (integer)")
					{
						json j_nonarray(json::value_t::number_integer);
						const json j_nonarray_const(j_nonarray);
						EXPECT_THROW(j_nonarray.at(0), json::type_error);
						EXPECT_THROW(j_nonarray_const.at(0), json::type_error);

						//CHECK_THROWS_WITH(j_nonarray.at(0), "[json.exception.type_error.304] cannot use at() with number");
						//CHECK_THROWS_WITH(j_nonarray_const.at(0), "[json.exception.type_error.304] cannot use at() with number");
					}

					//TEST(constructors,"number (unsigned)")
					{
						json j_nonarray(json::value_t::number_unsigned);
						const json j_nonarray_const(j_nonarray);
						EXPECT_THROW(j_nonarray.at(0), json::type_error);
						EXPECT_THROW(j_nonarray_const.at(0), json::type_error);

						//CHECK_THROWS_WITH(j_nonarray.at(0), "[json.exception.type_error.304] cannot use at() with number");
						//CHECK_THROWS_WITH(j_nonarray_const.at(0), "[json.exception.type_error.304] cannot use at() with number");
					}

					//TEST(constructors,"number (floating-point)")
					{
						json j_nonarray(json::value_t::number_float);
						const json j_nonarray_const(j_nonarray);
						EXPECT_THROW(j_nonarray.at(0), json::type_error);
						EXPECT_THROW(j_nonarray_const.at(0), json::type_error);

						//CHECK_THROWS_WITH(j_nonarray.at(0), "[json.exception.type_error.304] cannot use at() with number");
						//CHECK_THROWS_WITH(j_nonarray_const.at(0), "[json.exception.type_error.304] cannot use at() with number");
					}
				}
			}

			//TEST(constructors,"front and back")
			{
				EXPECT_TRUE(j.front() == json(1));
				EXPECT_TRUE(j_const.front() == json(1));
				EXPECT_TRUE(j.back() == json({1, 2, 3}));
				EXPECT_TRUE(j_const.back() == json({1, 2, 3}));
			}

			//TEST(constructors,"access specified element")
			{
				//TEST(constructors,"access within bounds")
				{
					EXPECT_TRUE(j[0] == json(1));
					EXPECT_TRUE(j[1] == json(1u));
					EXPECT_TRUE(j[2] == json(true));
					EXPECT_TRUE(j[3] == json(nullptr));
					EXPECT_TRUE(j[4] == json("string"));
					EXPECT_TRUE(j[5] == json(42.23));
					EXPECT_TRUE(j[6] == json::object());
					EXPECT_TRUE(j[7] == json({1, 2, 3}));

					EXPECT_TRUE(j_const[0] == json(1));
					EXPECT_TRUE(j_const[1] == json(1u));
					EXPECT_TRUE(j_const[2] == json(true));
					EXPECT_TRUE(j_const[3] == json(nullptr));
					EXPECT_TRUE(j_const[4] == json("string"));
					EXPECT_TRUE(j_const[5] == json(42.23));
					EXPECT_TRUE(j_const[6] == json::object());
					EXPECT_TRUE(j_const[7] == json({1, 2, 3}));
				}

				//TEST(constructors,"access on non-array type")
				{
					//TEST(constructors,"null")
					{
						//TEST(constructors,"standard tests")
						{
							json j_nonarray(json::value_t::null);
							const json j_nonarray_const(j_nonarray);
							EXPECT_NO_THROW(j_nonarray[0]);
							EXPECT_THROW(j_nonarray_const[0], json::type_error);
							//CHECK_THROWS_WITH(j_nonarray_const[0], "[json.exception.type_error.305] cannot use operator[] with null");
						}

						//TEST(constructors,"implicit transformation to properly filled array")
						{
							json j_nonarray;
							j_nonarray[3] = 42;
							EXPECT_TRUE(j_nonarray == json({nullptr, nullptr, nullptr, 42}));
						}
					}

					//TEST(constructors,"boolean")
					{
						json j_nonarray(json::value_t::boolean);
						const json j_nonarray_const(j_nonarray);
						EXPECT_THROW(j_nonarray[0], json::type_error);
						EXPECT_THROW(j_nonarray_const[0], json::type_error);
						//CHECK_THROWS_WITH(j_nonarray[0], "[json.exception.type_error.305] cannot use operator[] with boolean");
						//CHECK_THROWS_WITH(j_nonarray_const[0], "[json.exception.type_error.305] cannot use operator[] with boolean");
					}

					//TEST(constructors,"string")
					{
						json j_nonarray(json::value_t::string);
						const json j_nonarray_const(j_nonarray);
						EXPECT_THROW(j_nonarray[0], json::type_error);
						EXPECT_THROW(j_nonarray_const[0], json::type_error);
						//CHECK_THROWS_WITH(j_nonarray[0], "[json.exception.type_error.305] cannot use operator[] with string");
						//CHECK_THROWS_WITH(j_nonarray_const[0], "[json.exception.type_error.305] cannot use operator[] with string");
					}

					//TEST(constructors,"object")
					{
						json j_nonarray(json::value_t::object);
						const json j_nonarray_const(j_nonarray);
						EXPECT_THROW(j_nonarray[0], json::type_error);
						EXPECT_THROW(j_nonarray_const[0], json::type_error);
						//CHECK_THROWS_WITH(j_nonarray[0], "[json.exception.type_error.305] cannot use operator[] with object");
						//CHECK_THROWS_WITH(j_nonarray_const[0], "[json.exception.type_error.305] cannot use operator[] with object");
					}

					//TEST(constructors,"number (integer)")
					{
						json j_nonarray(json::value_t::number_integer);
						const json j_nonarray_const(j_nonarray);
						EXPECT_THROW(j_nonarray[0], json::type_error);
						EXPECT_THROW(j_nonarray_const[0], json::type_error);
						//CHECK_THROWS_WITH(j_nonarray[0], "[json.exception.type_error.305] cannot use operator[] with number");
						//CHECK_THROWS_WITH(j_nonarray_const[0], "[json.exception.type_error.305] cannot use operator[] with number");
					}

					//TEST(constructors,"number (unsigned)")
					{
						json j_nonarray(json::value_t::number_unsigned);
						const json j_nonarray_const(j_nonarray);
						EXPECT_THROW(j_nonarray[0], json::type_error);
						EXPECT_THROW(j_nonarray_const[0], json::type_error);
						//CHECK_THROWS_WITH(j_nonarray[0], "[json.exception.type_error.305] cannot use operator[] with number");
						//CHECK_THROWS_WITH(j_nonarray_const[0], "[json.exception.type_error.305] cannot use operator[] with number");
					}

					//TEST(constructors,"number (floating-point)")
					{
						json j_nonarray(json::value_t::number_float);
						const json j_nonarray_const(j_nonarray);
						EXPECT_THROW(j_nonarray[0], json::type_error);
						EXPECT_THROW(j_nonarray_const[0], json::type_error);
						//CHECK_THROWS_WITH(j_nonarray[0], "[json.exception.type_error.305] cannot use operator[] with number");
						//CHECK_THROWS_WITH(j_nonarray_const[0], "[json.exception.type_error.305] cannot use operator[] with number");
					}
				}
			}

			//TEST(constructors,"remove specified element")
			{
				//TEST(constructors,"remove element by index")
				{
					{
						json jarray = {1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}};
						jarray.erase(0);
						EXPECT_TRUE(jarray == json({1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}}));
					}
					{
						json jarray = {1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}};
						jarray.erase(1);
						EXPECT_TRUE(jarray == json({1, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}}));
					}
					{
						json jarray = {1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}};
						jarray.erase(2);
						EXPECT_TRUE(jarray == json({1, 1u, nullptr, "string", 42.23, json::object(), {1, 2, 3}}));
					}
					{
						json jarray = {1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}};
						jarray.erase(3);
						EXPECT_TRUE(jarray == json({1, 1u, true, "string", 42.23, json::object(), {1, 2, 3}}));
					}
					{
						json jarray = {1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}};
						jarray.erase(4);
						EXPECT_TRUE(jarray == json({1, 1u, true, nullptr, 42.23, json::object(), {1, 2, 3}}));
					}
					{
						json jarray = {1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}};
						jarray.erase(5);
						EXPECT_TRUE(jarray == json({1, 1u, true, nullptr, "string", json::object(), {1, 2, 3}}));
					}
					{
						json jarray = {1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}};
						jarray.erase(6);
						EXPECT_TRUE(jarray == json({1, 1u, true, nullptr, "string", 42.23, {1, 2, 3}}));
					}
					{
						json jarray = {1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}};
						jarray.erase(7);
						EXPECT_TRUE(jarray == json({1, 1u, true, nullptr, "string", 42.23, json::object()}));
					}
					{
						json jarray = {1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}};
						EXPECT_THROW(jarray.erase(8), json::out_of_range);
						//CHECK_THROWS_WITH(jarray.erase(8),
										  //"[json.exception.out_of_range.401] array index 8 is out of range");
					}
				}

				//TEST(constructors,"remove element by iterator")
				{
					//TEST(constructors,"erase(begin())")
					{
						{
							json jarray = {1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}};
							json::iterator it2 = jarray.erase(jarray.begin());
							EXPECT_TRUE(jarray == json({1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}}));
							EXPECT_TRUE(*it2 == json(1u));
						}
						{
							json jarray = {1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}};
							json::const_iterator it2 = jarray.erase(jarray.cbegin());
							EXPECT_TRUE(jarray == json({1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}}));
							EXPECT_TRUE(*it2 == json(1u));
						}
					}

					//TEST(constructors,"erase(begin(), end())")
					{
						{
							json jarray = {1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}};
							json::iterator it2 = jarray.erase(jarray.begin(), jarray.end());
							EXPECT_TRUE(jarray == json::array());
							EXPECT_TRUE(it2 == jarray.end());
						}
						{
							json jarray = {1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}};
							json::const_iterator it2 = jarray.erase(jarray.cbegin(), jarray.cend());
							EXPECT_TRUE(jarray == json::array());
							EXPECT_TRUE(it2 == jarray.cend());
						}
					}

					//TEST(constructors,"erase(begin(), begin())")
					{
						{
							json jarray = {1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}};
							json::iterator it2 = jarray.erase(jarray.begin(), jarray.begin());
							EXPECT_TRUE(jarray == json({1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}}));
							EXPECT_TRUE(*it2 == json(1));
						}
						{
							json jarray = {1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}};
							json::const_iterator it2 = jarray.erase(jarray.cbegin(), jarray.cbegin());
							EXPECT_TRUE(jarray == json({1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}}));
							EXPECT_TRUE(*it2 == json(1));
						}
					}

					//TEST(constructors,"erase at offset")
					{
						{
							json jarray = {1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}};
							json::iterator it = jarray.begin() + 4;
							json::iterator it2 = jarray.erase(it);
							EXPECT_TRUE(jarray == json({1, 1u, true, nullptr, 42.23, json::object(), {1, 2, 3}}));
							EXPECT_TRUE(*it2 == json(42.23));
						}
						{
							json jarray = {1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}};
							json::const_iterator it = jarray.cbegin() + 4;
							json::const_iterator it2 = jarray.erase(it);
							EXPECT_TRUE(jarray == json({1, 1u, true, nullptr, 42.23, json::object(), {1, 2, 3}}));
							EXPECT_TRUE(*it2 == json(42.23));
						}
					}

					//TEST(constructors,"erase subrange")
					{
						{
							json jarray = {1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}};
							json::iterator it2 = jarray.erase(jarray.begin() + 3, jarray.begin() + 6);
							EXPECT_TRUE(jarray == json({1, 1u, true, json::object(), {1, 2, 3}}));
							EXPECT_TRUE(*it2 == json::object());
						}
						{
							json jarray = {1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}};
							json::const_iterator it2 = jarray.erase(jarray.cbegin() + 3, jarray.cbegin() + 6);
							EXPECT_TRUE(jarray == json({1, 1u, true, json::object(), {1, 2, 3}}));
							EXPECT_TRUE(*it2 == json::object());
						}
					}

					//TEST(constructors,"different arrays")
					{
						{
							json jarray = {1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}};
							json jarray2 = {"foo", "bar"};
							EXPECT_THROW(jarray.erase(jarray2.begin()), json::invalid_iterator);
							EXPECT_THROW(jarray.erase(jarray.begin(), jarray2.end()), json::invalid_iterator);
							EXPECT_THROW(jarray.erase(jarray2.begin(), jarray.end()), json::invalid_iterator);
							EXPECT_THROW(jarray.erase(jarray2.begin(), jarray2.end()), json::invalid_iterator);

							//CHECK_THROWS_WITH(jarray.erase(jarray2.begin()),
											  //"[json.exception.invalid_iterator.202] iterator does not fit current value");
							//CHECK_THROWS_WITH(jarray.erase(jarray.begin(), jarray2.end()),
											  //"[json.exception.invalid_iterator.203] iterators do not fit current value");
							//CHECK_THROWS_WITH(jarray.erase(jarray2.begin(), jarray.end()),
											  //"[json.exception.invalid_iterator.203] iterators do not fit current value");
							//CHECK_THROWS_WITH(jarray.erase(jarray2.begin(), jarray2.end()),
											  //"[json.exception.invalid_iterator.203] iterators do not fit current value");
						}
						{
							json jarray = {1, 1u, true, nullptr, "string", 42.23, json::object(), {1, 2, 3}};
							json jarray2 = {"foo", "bar"};
							EXPECT_THROW(jarray.erase(jarray2.cbegin()), json::invalid_iterator);
							EXPECT_THROW(jarray.erase(jarray.cbegin(), jarray2.cend()), json::invalid_iterator);
							EXPECT_THROW(jarray.erase(jarray2.cbegin(), jarray.cend()), json::invalid_iterator);
							EXPECT_THROW(jarray.erase(jarray2.cbegin(), jarray2.cend()), json::invalid_iterator);

							//CHECK_THROWS_WITH(jarray.erase(jarray2.cbegin()),
											  //"[json.exception.invalid_iterator.202] iterator does not fit current value");
							//CHECK_THROWS_WITH(jarray.erase(jarray.cbegin(), jarray2.cend()),
											  //"[json.exception.invalid_iterator.203] iterators do not fit current value");
							//CHECK_THROWS_WITH(jarray.erase(jarray2.cbegin(), jarray.cend()),
											  //"[json.exception.invalid_iterator.203] iterators do not fit current value");
							//CHECK_THROWS_WITH(jarray.erase(jarray2.cbegin(), jarray2.cend()),
											  //"[json.exception.invalid_iterator.203] iterators do not fit current value");
						}
					}
				}

				//TEST(constructors,"remove element by index in non-array type")
				{
					//TEST(constructors,"null")
					{
						json j_nonobject(json::value_t::null);
						EXPECT_THROW(j_nonobject.erase(0), json::type_error);
						//CHECK_THROWS_WITH(j_nonobject.erase(0),
										  //"[json.exception.type_error.307] cannot use erase() with null");
					}

					//TEST(constructors,"boolean")
					{
						json j_nonobject(json::value_t::boolean);
						EXPECT_THROW(j_nonobject.erase(0), json::type_error);
						//CHECK_THROWS_WITH(j_nonobject.erase(0),
										  //"[json.exception.type_error.307] cannot use erase() with boolean");
					}

					//TEST(constructors,"string")
					{
						json j_nonobject(json::value_t::string);
						EXPECT_THROW(j_nonobject.erase(0), json::type_error);
						//CHECK_THROWS_WITH(j_nonobject.erase(0),
										  //"[json.exception.type_error.307] cannot use erase() with string");
					}

					//TEST(constructors,"object")
					{
						json j_nonobject(json::value_t::object);
						EXPECT_THROW(j_nonobject.erase(0), json::type_error);
						//CHECK_THROWS_WITH(j_nonobject.erase(0),
										  //"[json.exception.type_error.307] cannot use erase() with object");
					}

					//TEST(constructors,"number (integer)")
					{
						json j_nonobject(json::value_t::number_integer);
						EXPECT_THROW(j_nonobject.erase(0), json::type_error);
						//CHECK_THROWS_WITH(j_nonobject.erase(0),
										  //"[json.exception.type_error.307] cannot use erase() with number");
					}

					//TEST(constructors,"number (unsigned)")
					{
						json j_nonobject(json::value_t::number_unsigned);
						EXPECT_THROW(j_nonobject.erase(0), json::type_error);
						//CHECK_THROWS_WITH(j_nonobject.erase(0),
										  //"[json.exception.type_error.307] cannot use erase() with number");
					}

					//TEST(constructors,"number (floating-point)")
					{
						json j_nonobject(json::value_t::number_float);
						EXPECT_THROW(j_nonobject.erase(0), json::type_error);
						//CHECK_THROWS_WITH(j_nonobject.erase(0),
										  //"[json.exception.type_error.307] cannot use erase() with number");
					}
				}
			}
		}

		//TEST(constructors,"other values")
		{
			//TEST(constructors,"front and back")
			{
				//TEST(constructors,"null")
				{
					{
						json j;
						EXPECT_THROW(j.front(), json::invalid_iterator);
						EXPECT_THROW(j.back(), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.front(), "[json.exception.invalid_iterator.214] cannot get value");
						//CHECK_THROWS_WITH(j.back(), "[json.exception.invalid_iterator.214] cannot get value");
					}
					{
						const json j{};
						EXPECT_THROW(j.front(), json::invalid_iterator);
						EXPECT_THROW(j.back(), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.front(), "[json.exception.invalid_iterator.214] cannot get value");
						//CHECK_THROWS_WITH(j.back(), "[json.exception.invalid_iterator.214] cannot get value");
					}
				}

				//TEST(constructors,"string")
				{
					{
						json j = "foo";
						EXPECT_TRUE(j.front() == j);
						EXPECT_TRUE(j.back() == j);
					}
					{
						const json j = "bar";
						EXPECT_TRUE(j.front() == j);
						EXPECT_TRUE(j.back() == j);
					}
				}

				//TEST(constructors,"number (boolean)")
				{
					{
						json j = false;
						EXPECT_TRUE(j.front() == j);
						EXPECT_TRUE(j.back() == j);
					}
					{
						const json j = true;
						EXPECT_TRUE(j.front() == j);
						EXPECT_TRUE(j.back() == j);
					}
				}

				//TEST(constructors,"number (integer)")
				{
					{
						json j = 17;
						EXPECT_TRUE(j.front() == j);
						EXPECT_TRUE(j.back() == j);
					}
					{
						const json j = 17;
						EXPECT_TRUE(j.front() == j);
						EXPECT_TRUE(j.back() == j);
					}
				}

				//TEST(constructors,"number (unsigned)")
				{
					{
						json j = 17u;
						EXPECT_TRUE(j.front() == j);
						EXPECT_TRUE(j.back() == j);
					}
					{
						const json j = 17u;
						EXPECT_TRUE(j.front() == j);
						EXPECT_TRUE(j.back() == j);
					}
				}

				//TEST(constructors,"number (floating point)")
				{
					{
						json j = 23.42;
						EXPECT_TRUE(j.front() == j);
						EXPECT_TRUE(j.back() == j);
					}
					{
						const json j = 23.42;
						EXPECT_TRUE(j.front() == j);
						EXPECT_TRUE(j.back() == j);
					}
				}
			}

			//TEST(constructors,"erase with one valid iterator")
			{
				//TEST(constructors,"null")
				{
					{
						json j;
						EXPECT_THROW(j.erase(j.begin()), json::type_error);
						//CHECK_THROWS_WITH(j.erase(j.begin()),
										  //"[json.exception.type_error.307] cannot use erase() with null");
					}
					{
						json j;
						EXPECT_THROW(j.erase(j.cbegin()), json::type_error);
						//CHECK_THROWS_WITH(j.erase(j.begin()),
										  //"[json.exception.type_error.307] cannot use erase() with null");
					}
				}

				//TEST(constructors,"string")
				{
					{
						json j = "foo";
						json::iterator it = j.erase(j.begin());
						EXPECT_TRUE(j.type() == json::value_t::null);
						EXPECT_TRUE(it == j.end());
					}
					{
						json j = "bar";
						json::const_iterator it = j.erase(j.cbegin());
						EXPECT_TRUE(j.type() == json::value_t::null);
						EXPECT_TRUE(it == j.end());
					}
				}

				//TEST(constructors,"number (boolean)")
				{
					{
						json j = false;
						json::iterator it = j.erase(j.begin());
						EXPECT_TRUE(j.type() == json::value_t::null);
						EXPECT_TRUE(it == j.end());
					}
					{
						json j = true;
						json::const_iterator it = j.erase(j.cbegin());
						EXPECT_TRUE(j.type() == json::value_t::null);
						EXPECT_TRUE(it == j.end());
					}
				}

				//TEST(constructors,"number (integer)")
				{
					{
						json j = 17;
						json::iterator it = j.erase(j.begin());
						EXPECT_TRUE(j.type() == json::value_t::null);
						EXPECT_TRUE(it == j.end());
					}
					{
						json j = 17;
						json::const_iterator it = j.erase(j.cbegin());
						EXPECT_TRUE(j.type() == json::value_t::null);
						EXPECT_TRUE(it == j.end());
					}
				}

				//TEST(constructors,"number (unsigned)")
				{
					{
						json j = 17u;
						json::iterator it = j.erase(j.begin());
						EXPECT_TRUE(j.type() == json::value_t::null);
						EXPECT_TRUE(it == j.end());
					}
					{
						json j = 17u;
						json::const_iterator it = j.erase(j.cbegin());
						EXPECT_TRUE(j.type() == json::value_t::null);
						EXPECT_TRUE(it == j.end());
					}
				}

				//TEST(constructors,"number (floating point)")
				{
					{
						json j = 23.42;
						json::iterator it = j.erase(j.begin());
						EXPECT_TRUE(j.type() == json::value_t::null);
						EXPECT_TRUE(it == j.end());
					}
					{
						json j = 23.42;
						json::const_iterator it = j.erase(j.cbegin());
						EXPECT_TRUE(j.type() == json::value_t::null);
						EXPECT_TRUE(it == j.end());
					}
				}
			}

			//TEST(constructors,"erase with one invalid iterator")
			{
				//TEST(constructors,"string")
				{
					{
						json j = "foo";
						EXPECT_THROW(j.erase(j.end()), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.erase(j.end()),
										  //"[json.exception.invalid_iterator.205] iterator out of range");
					}
					{
						json j = "bar";
						EXPECT_THROW(j.erase(j.cend()), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.erase(j.cend()),
										  //"[json.exception.invalid_iterator.205] iterator out of range");
					}
				}

				//TEST(constructors,"number (boolean)")
				{
					{
						json j = false;
						EXPECT_THROW(j.erase(j.end()), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.erase(j.end()),
										  //"[json.exception.invalid_iterator.205] iterator out of range");
					}
					{
						json j = true;
						EXPECT_THROW(j.erase(j.cend()), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.erase(j.cend()),
										  //"[json.exception.invalid_iterator.205] iterator out of range");
					}
				}

				//TEST(constructors,"number (integer)")
				{
					{
						json j = 17;
						EXPECT_THROW(j.erase(j.end()), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.erase(j.end()),
										  //"[json.exception.invalid_iterator.205] iterator out of range");
					}
					{
						json j = 17;
						EXPECT_THROW(j.erase(j.cend()), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.erase(j.cend()),
										  //"[json.exception.invalid_iterator.205] iterator out of range");
					}
				}

				//TEST(constructors,"number (unsigned)")
				{
					{
						json j = 17u;
						EXPECT_THROW(j.erase(j.end()), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.erase(j.end()),
										  //"[json.exception.invalid_iterator.205] iterator out of range");
					}
					{
						json j = 17u;
						EXPECT_THROW(j.erase(j.cend()), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.erase(j.cend()),
										  //"[json.exception.invalid_iterator.205] iterator out of range");
					}
				}

				//TEST(constructors,"number (floating point)")
				{
					{
						json j = 23.42;
						EXPECT_THROW(j.erase(j.end()), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.erase(j.end()),
										  //"[json.exception.invalid_iterator.205] iterator out of range");
					}
					{
						json j = 23.42;
						EXPECT_THROW(j.erase(j.cend()), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.erase(j.cend()),
										  //"[json.exception.invalid_iterator.205] iterator out of range");
					}
				}
			}

			//TEST(constructors,"erase with two valid iterators")
			{
				//TEST(constructors,"null")
				{
					{
						json j;
						EXPECT_THROW(j.erase(j.begin(), j.end()), json::type_error);
						//CHECK_THROWS_WITH(j.erase(j.begin(), j.end()),
										  //"[json.exception.type_error.307] cannot use erase() with null");
					}
					{
						json j;
						EXPECT_THROW(j.erase(j.cbegin(), j.cend()), json::type_error);
						//CHECK_THROWS_WITH(j.erase(j.cbegin(), j.cend()),
										  //"[json.exception.type_error.307] cannot use erase() with null");
					}
				}

				//TEST(constructors,"string")
				{
					{
						json j = "foo";
						json::iterator it = j.erase(j.begin(), j.end());
						EXPECT_TRUE(j.type() == json::value_t::null);
						EXPECT_TRUE(it == j.end());
					}
					{
						json j = "bar";
						json::const_iterator it = j.erase(j.cbegin(), j.cend());
						EXPECT_TRUE(j.type() == json::value_t::null);
						EXPECT_TRUE(it == j.end());
					}
				}

				//TEST(constructors,"number (boolean)")
				{
					{
						json j = false;
						json::iterator it = j.erase(j.begin(), j.end());
						EXPECT_TRUE(j.type() == json::value_t::null);
						EXPECT_TRUE(it == j.end());
					}
					{
						json j = true;
						json::const_iterator it = j.erase(j.cbegin(), j.cend());
						EXPECT_TRUE(j.type() == json::value_t::null);
						EXPECT_TRUE(it == j.end());
					}
				}

				//TEST(constructors,"number (integer)")
				{
					{
						json j = 17;
						json::iterator it = j.erase(j.begin(), j.end());
						EXPECT_TRUE(j.type() == json::value_t::null);
						EXPECT_TRUE(it == j.end());
					}
					{
						json j = 17;
						json::const_iterator it = j.erase(j.cbegin(), j.cend());
						EXPECT_TRUE(j.type() == json::value_t::null);
						EXPECT_TRUE(it == j.end());
					}
				}

				//TEST(constructors,"number (unsigned)")
				{
					{
						json j = 17u;
						json::iterator it = j.erase(j.begin(), j.end());
						EXPECT_TRUE(j.type() == json::value_t::null);
						EXPECT_TRUE(it == j.end());
					}
					{
						json j = 17u;
						json::const_iterator it = j.erase(j.cbegin(), j.cend());
						EXPECT_TRUE(j.type() == json::value_t::null);
						EXPECT_TRUE(it == j.end());
					}
				}

				//TEST(constructors,"number (floating point)")
				{
					{
						json j = 23.42;
						json::iterator it = j.erase(j.begin(), j.end());
						EXPECT_TRUE(j.type() == json::value_t::null);
						EXPECT_TRUE(it == j.end());
					}
					{
						json j = 23.42;
						json::const_iterator it = j.erase(j.cbegin(), j.cend());
						EXPECT_TRUE(j.type() == json::value_t::null);
						EXPECT_TRUE(it == j.end());
					}
				}
			}

			//TEST(constructors,"erase with two invalid iterators")
			{
				//TEST(constructors,"string")
				{
					{
						json j = "foo";
						EXPECT_THROW(j.erase(j.end(), j.end()), json::invalid_iterator);
						EXPECT_THROW(j.erase(j.begin(), j.begin()), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.erase(j.end(), j.end()), "[json.exception.invalid_iterator.204] iterators out of range");
						//CHECK_THROWS_WITH(j.erase(j.begin(), j.begin()), "[json.exception.invalid_iterator.204] iterators out of range");
					}
					{
						json j = "bar";
						EXPECT_THROW(j.erase(j.cend(), j.cend()), json::invalid_iterator);
						EXPECT_THROW(j.erase(j.cbegin(), j.cbegin()), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.erase(j.cend(), j.cend()), "[json.exception.invalid_iterator.204] iterators out of range");
						//CHECK_THROWS_WITH(j.erase(j.cbegin(), j.cbegin()), "[json.exception.invalid_iterator.204] iterators out of range");
					}
				}

				//TEST(constructors,"number (boolean)")
				{
					{
						json j = false;
						EXPECT_THROW(j.erase(j.end(), j.end()), json::invalid_iterator);
						EXPECT_THROW(j.erase(j.begin(), j.begin()), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.erase(j.end(), j.end()), "[json.exception.invalid_iterator.204] iterators out of range");
						//CHECK_THROWS_WITH(j.erase(j.begin(), j.begin()), "[json.exception.invalid_iterator.204] iterators out of range");
					}
					{
						json j = true;
						EXPECT_THROW(j.erase(j.cend(), j.cend()), json::invalid_iterator);
						EXPECT_THROW(j.erase(j.cbegin(), j.cbegin()), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.erase(j.cend(), j.cend()), "[json.exception.invalid_iterator.204] iterators out of range");
						//CHECK_THROWS_WITH(j.erase(j.cbegin(), j.cbegin()), "[json.exception.invalid_iterator.204] iterators out of range");
					}
				}

				//TEST(constructors,"number (integer)")
				{
					{
						json j = 17;
						EXPECT_THROW(j.erase(j.end(), j.end()), json::invalid_iterator);
						EXPECT_THROW(j.erase(j.begin(), j.begin()), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.erase(j.end(), j.end()), "[json.exception.invalid_iterator.204] iterators out of range");
						//CHECK_THROWS_WITH(j.erase(j.begin(), j.begin()), "[json.exception.invalid_iterator.204] iterators out of range");
					}
					{
						json j = 17;
						EXPECT_THROW(j.erase(j.cend(), j.cend()), json::invalid_iterator);
						EXPECT_THROW(j.erase(j.cbegin(), j.cbegin()), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.erase(j.cend(), j.cend()), "[json.exception.invalid_iterator.204] iterators out of range");
						//CHECK_THROWS_WITH(j.erase(j.cbegin(), j.cbegin()), "[json.exception.invalid_iterator.204] iterators out of range");
					}
				}

				//TEST(constructors,"number (unsigned)")
				{
					{
						json j = 17u;
						EXPECT_THROW(j.erase(j.end(), j.end()), json::invalid_iterator);
						EXPECT_THROW(j.erase(j.begin(), j.begin()), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.erase(j.end(), j.end()), "[json.exception.invalid_iterator.204] iterators out of range");
						//CHECK_THROWS_WITH(j.erase(j.begin(), j.begin()), "[json.exception.invalid_iterator.204] iterators out of range");
					}
					{
						json j = 17u;
						EXPECT_THROW(j.erase(j.cend(), j.cend()), json::invalid_iterator);
						EXPECT_THROW(j.erase(j.cbegin(), j.cbegin()), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.erase(j.cend(), j.cend()), "[json.exception.invalid_iterator.204] iterators out of range");
						//CHECK_THROWS_WITH(j.erase(j.cbegin(), j.cbegin()), "[json.exception.invalid_iterator.204] iterators out of range");
					}
				}

				//TEST(constructors,"number (floating point)")
				{
					{
						json j = 23.42;
						EXPECT_THROW(j.erase(j.end(), j.end()), json::invalid_iterator);
						EXPECT_THROW(j.erase(j.begin(), j.begin()), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.erase(j.end(), j.end()), "[json.exception.invalid_iterator.204] iterators out of range");
						//CHECK_THROWS_WITH(j.erase(j.begin(), j.begin()), "[json.exception.invalid_iterator.204] iterators out of range");
					}
					{
						json j = 23.42;
						EXPECT_THROW(j.erase(j.cend(), j.cend()), json::invalid_iterator);
						EXPECT_THROW(j.erase(j.cbegin(), j.cbegin()), json::invalid_iterator);
						//CHECK_THROWS_WITH(j.erase(j.cend(), j.cend()), "[json.exception.invalid_iterator.204] iterators out of range");
						//CHECK_THROWS_WITH(j.erase(j.cbegin(), j.cbegin()), "[json.exception.invalid_iterator.204] iterators out of range");
					}
				}
			}
		}
	}
}
