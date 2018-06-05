#include "gtest/gtest.h"
#include "json.hpp"

using nlohmann::json;

#include <fstream>

namespace
{
	TEST(JSONpatch, patch)
	{
		//TEST(constructors,"examples from RFC 6902")
		{
			//TEST(constructors,"4. Operations")
			{
				// the ordering of members in JSON objects is not significant:
				json op1 = R"({ "op": "add", "path": "/a/b/c", "value": "foo" })"_json;
				json op2 = R"({ "path": "/a/b/c", "op": "add", "value": "foo" })"_json;
				json op3 = R"({ "value": "foo", "path": "/a/b/c", "op": "add" })"_json;

				// check if the operation objects are equivalent
				EXPECT_TRUE(op1 == op2);
				EXPECT_TRUE(op1 == op3);
			}

			//TEST(constructors,"4.1 add")
			{
				json patch = R"([{ "op": "add", "path": "/a/b/c", "value": [ "foo", "bar" ] }])"_json;

				// However, the object itself or an array containing it does need
				// to exist, and it remains an error for that not to be the case.
				// For example, an "add" with a target location of "/a/b" starting
				// with this document
				json doc1 = R"({ "a": { "foo": 1 } })"_json;

				// is not an error, because "a" exists, and "b" will be added to
				// its value.
				EXPECT_NO_THROW(doc1.patch(patch));
				EXPECT_TRUE(doc1.patch(patch) == R"(
					{
						"a": {
							"foo": 1,
							"b": {
								"c": [ "foo", "bar" ]
							}
						}
					}
				)"_json);

				// It is an error in this document:
				json doc2 = R"({ "q": { "bar": 2 } })"_json;

				// because "a" does not exist.
				EXPECT_THROW(doc2.patch(patch), json::out_of_range);
				//CHECK_THROWS_WITH(doc2.patch(patch),
								  //"[json.exception.out_of_range.403] key 'a' not found");
			}

			//TEST(constructors,"4.2 remove")
			{
				// If removing an element from an array, any elements above the
				// specified index are shifted one position to the left.
				json doc = {1, 2, 3, 4};
				json patch = {{{"op", "remove"}, {"path", "/1"}}};
				EXPECT_TRUE(doc.patch(patch) == json({1, 3, 4}));
			}

			//TEST(constructors,"A.1. Adding an Object Member")
			{
				// An example target JSON document:
				json doc = R"(
						{ "foo": "bar"}
					)"_json;

				// A JSON Patch document:
				json patch = R"(
						[
							{ "op": "add", "path": "/baz", "value": "qux" }
						]
					)"_json;

				// The resulting JSON document:
				json expected = R"(
						{
							"baz": "qux",
							"foo": "bar"
						}
					)"_json;

				// check if patched value is as expected
				EXPECT_TRUE(doc.patch(patch) == expected);

				// check roundtrip
				EXPECT_TRUE(doc.patch(json::diff(doc, expected)) == expected);
			}

			//TEST(constructors,"A.2. Adding an Array Element")
			{
				// An example target JSON document:
				json doc = R"(
						{ "foo": [ "bar", "baz" ] }
					)"_json;

				// A JSON Patch document:
				json patch = R"(
						[
							{ "op": "add", "path": "/foo/1", "value": "qux" }
						]
					)"_json;

				// The resulting JSON document:
				json expected = R"(
						{ "foo": [ "bar", "qux", "baz" ] }
					)"_json;

				// check if patched value is as expected
				EXPECT_TRUE(doc.patch(patch) == expected);

				// check roundtrip
				EXPECT_TRUE(doc.patch(json::diff(doc, expected)) == expected);
			}

			//TEST(constructors,"A.3. Removing an Object Member")
			{
				// An example target JSON document:
				json doc = R"(
						{
							"baz": "qux",
							"foo": "bar"
						}
					)"_json;

				// A JSON Patch document:
				json patch = R"(
						[
							{ "op": "remove", "path": "/baz" }
						]
					)"_json;

				// The resulting JSON document:
				json expected = R"(
						{ "foo": "bar" }
					)"_json;

				// check if patched value is as expected
				EXPECT_TRUE(doc.patch(patch) == expected);

				// check roundtrip
				EXPECT_TRUE(doc.patch(json::diff(doc, expected)) == expected);
			}

			//TEST(constructors,"A.4. Removing an Array Element")
			{
				// An example target JSON document:
				json doc = R"(
						{ "foo": [ "bar", "qux", "baz" ] }
					)"_json;

				// A JSON Patch document:
				json patch = R"(
						[
							{ "op": "remove", "path": "/foo/1" }
						]
					)"_json;

				// The resulting JSON document:
				json expected = R"(
						{ "foo": [ "bar", "baz" ] }
					)"_json;

				// check if patched value is as expected
				EXPECT_TRUE(doc.patch(patch) == expected);

				// check roundtrip
				EXPECT_TRUE(doc.patch(json::diff(doc, expected)) == expected);
			}

			//TEST(constructors,"A.5. Replacing a Value")
			{
				// An example target JSON document:
				json doc = R"(
						{
							"baz": "qux",
							"foo": "bar"
						}
					)"_json;

				// A JSON Patch document:
				json patch = R"(
						[
							{ "op": "replace", "path": "/baz", "value": "boo" }
						]
					)"_json;

				json expected = R"(
						{
							"baz": "boo",
							"foo": "bar"
						}
					)"_json;

				// check if patched value is as expected
				EXPECT_TRUE(doc.patch(patch) == expected);

				// check roundtrip
				EXPECT_TRUE(doc.patch(json::diff(doc, expected)) == expected);
			}

			//TEST(constructors,"A.6. Moving a Value")
			{
				// An example target JSON document:
				json doc = R"(
						{
							"foo": {
							   "bar": "baz",
								"waldo": "fred"
							},
							"qux": {
								"corge": "grault"
							}
						}
					)"_json;

				// A JSON Patch document:
				json patch = R"(
						[
							{ "op": "move", "from": "/foo/waldo", "path": "/qux/thud" }
						]
					)"_json;

				// The resulting JSON document:
				json expected = R"(
						{
							"foo": {
							   "bar": "baz"
							},
							"qux": {
								"corge": "grault",
								"thud": "fred"
							}
						}
					)"_json;

				// check if patched value is as expected
				EXPECT_TRUE(doc.patch(patch) == expected);

				// check roundtrip
				EXPECT_TRUE(doc.patch(json::diff(doc, expected)) == expected);
			}

			//TEST(constructors,"A.7. Moving a Value")
			{
				// An example target JSON document:
				json doc = R"(
						{ "foo": [ "all", "grass", "cows", "eat" ] }
					)"_json;

				// A JSON Patch document:
				json patch = R"(
						[
							{ "op": "move", "from": "/foo/1", "path": "/foo/3" }
						]
					)"_json;

				// The resulting JSON document:
				json expected = R"(
						{ "foo": [ "all", "cows", "eat", "grass" ] }
					)"_json;

				// check if patched value is as expected
				EXPECT_TRUE(doc.patch(patch) == expected);

				// check roundtrip
				EXPECT_TRUE(doc.patch(json::diff(doc, expected)) == expected);
			}

			//TEST(constructors,"A.8. Testing a Value: Success")
			{
				// An example target JSON document:
				json doc = R"(
						{
							 "baz": "qux",
							 "foo": [ "a", 2, "c" ]
						}
					)"_json;

				// A JSON Patch document that will result in successful evaluation:
				json patch = R"(
						[
							{ "op": "test", "path": "/baz", "value": "qux" },
							{ "op": "test", "path": "/foo/1", "value": 2 }
						]
					)"_json;

				// check if evaluation does not throw
				EXPECT_NO_THROW(doc.patch(patch));
				// check if patched document is unchanged
				EXPECT_TRUE(doc.patch(patch) == doc);
			}

			//TEST(constructors,"A.9. Testing a Value: Error")
			{
				// An example target JSON document:
				json doc = R"(
						{ "baz": "qux" }
					)"_json;

				// A JSON Patch document that will result in an error condition:
				json patch = R"(
						[
							{ "op": "test", "path": "/baz", "value": "bar" }
						]
					)"_json;

				// check that evaluation throws
				EXPECT_THROW(doc.patch(patch), json::other_error);
				//CHECK_THROWS_WITH(doc.patch(patch), "[json.exception.other_error.501] unsuccessful: " + patch[0].dump());
			}

			//TEST(constructors,"A.10. Adding a Nested Member Object")
			{
				// An example target JSON document:
				json doc = R"(
						{ "foo": "bar" }
					)"_json;

				// A JSON Patch document:
				json patch = R"(
						[
							{ "op": "add", "path": "/child", "value": { "grandchild": { } } }
						]
					)"_json;

				// The resulting JSON document:
				json expected = R"(
					{
						"foo": "bar",
						"child": {
							"grandchild": {
							}
						}
					}
					)"_json;

				// check if patched value is as expected
				EXPECT_TRUE(doc.patch(patch) == expected);

				// check roundtrip
				EXPECT_TRUE(doc.patch(json::diff(doc, expected)) == expected);
			}

			//TEST(constructors,"A.11. Ignoring Unrecognized Elements")
			{
				// An example target JSON document:
				json doc = R"(
						{ "foo": "bar" }
					)"_json;

				// A JSON Patch document:
				json patch = R"(
						[
							{ "op": "add", "path": "/baz", "value": "qux", "xyz": 123 }
						]
					)"_json;

				json expected = R"(
						{
							"foo": "bar",
							"baz": "qux"
						} 
					)"_json;

				// check if patched value is as expected
				EXPECT_TRUE(doc.patch(patch) == expected);

				// check roundtrip
				EXPECT_TRUE(doc.patch(json::diff(doc, expected)) == expected);
			}

			//TEST(constructors,"A.12. Adding to a Nonexistent Target")
			{
				// An example target JSON document:
				json doc = R"(
						{ "foo": "bar" }
					)"_json;

				// A JSON Patch document:
				json patch = R"(
						[
							{ "op": "add", "path": "/baz/bat", "value": "qux" }
						]
					)"_json;

				// This JSON Patch document, applied to the target JSON document
				// above, would result in an error (therefore, it would not be
				// applied), because the "add" operation's target location that
				// references neither the root of the document, nor a member of
				// an existing object, nor a member of an existing array.

				EXPECT_THROW(doc.patch(patch), json::out_of_range);
				//CHECK_THROWS_WITH(doc.patch(patch),
								  //"[json.exception.out_of_range.403] key 'baz' not found");
			}

			// A.13. Invalid JSON Patch Document
			// not applicable

			//TEST(constructors,"A.14. Escape Ordering")
			{
				// An example target JSON document:
				json doc = R"(
						{
							"/": 9,
							"~1": 10
						}
					)"_json;

				// A JSON Patch document:
				json patch = R"(
						[
							{"op": "test", "path": "/~01", "value": 10}
						]
					)"_json;

				json expected = R"(
						{
							"/": 9,
							"~1": 10
						} 
					)"_json;

				// check if patched value is as expected
				EXPECT_TRUE(doc.patch(patch) == expected);

				// check roundtrip
				EXPECT_TRUE(doc.patch(json::diff(doc, expected)) == expected);
			}

			//TEST(constructors,"A.15. Comparing Strings and Numbers")
			{
				// An example target JSON document:
				json doc = R"(
						{
							"/": 9,
							"~1": 10
						} 
					)"_json;

				// A JSON Patch document that will result in an error condition:
				json patch = R"(
						[
							{"op": "test", "path": "/~01", "value": "10"}
						]
					)"_json;

				// check that evaluation throws
				EXPECT_THROW(doc.patch(patch), json::other_error);
				//CHECK_THROWS_WITH(doc.patch(patch), "[json.exception.other_error.501] unsuccessful: " + patch[0].dump());
			}

			//TEST(constructors,"A.16. Adding an Array Value")
			{
				// An example target JSON document:
				json doc = R"(
						{ "foo": ["bar"] }
					)"_json;

				// A JSON Patch document:
				json patch = R"(
						[
							{ "op": "add", "path": "/foo/-", "value": ["abc", "def"] }
						]
					)"_json;

				// The resulting JSON document:
				json expected = R"(
						{ "foo": ["bar", ["abc", "def"]] }
					)"_json;

				// check if patched value is as expected
				EXPECT_TRUE(doc.patch(patch) == expected);

				// check roundtrip
				EXPECT_TRUE(doc.patch(json::diff(doc, expected)) == expected);
			}
		}

		//TEST(constructors,"own examples")
		{
			//TEST(constructors,"add")
			{
				//TEST(constructors,"add to the root element")
				{
					// If the path is the root of the target document - the
					// specified value becomes the entire content of the target
					// document.

					// An example target JSON document:
					json doc = 17;

					// A JSON Patch document:
					json patch = R"(
							[
								{ "op": "add", "path": "", "value": [1,2,3] }
							]
						)"_json;

					// The resulting JSON document:
					json expected = {1, 2, 3};

					// check if patched value is as expected
					EXPECT_TRUE(doc.patch(patch) == expected);

					// check roundtrip
					EXPECT_TRUE(doc.patch(json::diff(doc, expected)) == expected);
				}

				//TEST(constructors,"add to end of the array")
				{
					// The specified index MUST NOT be greater than the number of
					// elements in the array. The example below uses and index of
					// exactly the number of elements in the array which is legal.

					// An example target JSON document:
					json doc = {0, 1, 2};

					// A JSON Patch document:
					json patch = R"(
						[
							{ "op": "add", "path": "/3", "value": 3 }
						]
					)"_json;

					// The resulting JSON document:
					json expected = {0, 1, 2, 3};

					// check if patched value is as expected
					EXPECT_TRUE(doc.patch(patch) == expected);

					// check roundtrip
					EXPECT_TRUE(doc.patch(json::diff(doc, expected)) == expected);
				}
			}

			//TEST(constructors,"copy")
			{
				// An example target JSON document:
				json doc = R"(
					{
						"foo": {
							"bar": "baz",
							"waldo": "fred"
						},
						"qux": {
						   "corge": "grault"
						}
					}
				)"_json;

				// A JSON Patch document:
				json patch = R"(
					[
						{ "op": "copy", "from": "/foo/waldo", "path": "/qux/thud" }
					]
				)"_json;

				// The resulting JSON document:
				json expected = R"(
					{
						"foo": {
							"bar": "baz",
							"waldo": "fred"
						},
						"qux": {
						   "corge": "grault",
						   "thud": "fred"
						}
					}
				)"_json;

				// check if patched value is as expected
				EXPECT_TRUE(doc.patch(patch) == expected);

				// check roundtrip
				EXPECT_TRUE(doc.patch(json::diff(doc, expected)) == expected);
			}

			//TEST(constructors,"replace")
			{
				json j = "string";
				json patch = {{{"op", "replace"}, {"path", ""}, {"value", 1}}};
				EXPECT_TRUE(j.patch(patch) == json(1));
			}

			//TEST(constructors,"documentation GIF")
			{
				{
					// a JSON patch
					json p1 = R"(
						 [{"op": "add", "path": "/GB", "value": "London"}]
						)"_json;

					// a JSON value
					json source = R"(
						  {"D": "Berlin", "F": "Paris"}
						)"_json;

					// apply the patch
					json target = source.patch(p1);
					// target = { "D": "Berlin", "F": "Paris", "GB": "London" }
					EXPECT_TRUE(target == R"({ "D": "Berlin", "F": "Paris", "GB": "London" })"_json);

					// create a diff from two JSONs
					json p2 = json::diff(target, source);
					// p2 = [{"op": "delete", "path": "/GB"}]
					EXPECT_TRUE(p2 == R"([{"op":"remove","path":"/GB"}])"_json);
				}
				{
					// a JSON value
					json j = {"good", "bad", "ugly"};

					// a JSON pointer
					auto ptr = json::json_pointer("/2");

					// use to access elements
					j[ptr] = {{"it", "cattivo"}};
					EXPECT_TRUE(j == R"(["good","bad",{"it":"cattivo"}])"_json);

					// use user-defined string literal
					j["/2/en"_json_pointer] = "ugly";
					EXPECT_TRUE(j == R"(["good","bad",{"en":"ugly","it":"cattivo"}])"_json);

					json flat = j.flatten();
					EXPECT_TRUE(flat == R"({"/0":"good","/1":"bad","/2/en":"ugly","/2/it":"cattivo"})"_json);
				}
			}
		}

		//TEST(constructors,"errors")
		{
			//TEST(constructors,"unknown operation")
			{
				//TEST(constructors,"not an array")
				{
					json j;
					json patch = {{"op", "add"}, {"path", ""}, {"value", 1}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.104] parse error: JSON patch must be an array of objects");
				}

				//TEST(constructors,"not an array of objects")
				{
					json j;
					json patch = {"op", "add", "path", "", "value", 1};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.104] parse error: JSON patch must be an array of objects");
				}

				//TEST(constructors,"missing 'op'")
				{
					json j;
					json patch = {{{"foo", "bar"}}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.105] parse error: operation must have member 'op'");
				}

				//TEST(constructors,"non-string 'op'")
				{
					json j;
					json patch = {{{"op", 1}}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.105] parse error: operation must have string member 'op'");
				}

				//TEST(constructors,"invalid operation")
				{
					json j;
					json patch = {{{"op", "foo"}, {"path", ""}}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.105] parse error: operation value 'foo' is invalid");
				}
			}

			//TEST(constructors,"add")
			{
				//TEST(constructors,"missing 'path'")
				{
					json j;
					json patch = {{{"op", "add"}}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.105] parse error: operation 'add' must have member 'path'");
				}

				//TEST(constructors,"non-string 'path'")
				{
					json j;
					json patch = {{{"op", "add"}, {"path", 1}}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.105] parse error: operation 'add' must have string member 'path'");
				}

				//TEST(constructors,"missing 'value'")
				{
					json j;
					json patch = {{{"op", "add"}, {"path", ""}}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.105] parse error: operation 'add' must have member 'value'");
				}

				//TEST(constructors,"invalid array index")
				{
					json j = {1, 2};
					json patch = {{{"op", "add"}, {"path", "/4"}, {"value", 4}}};
					EXPECT_THROW(j.patch(patch), json::out_of_range);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.out_of_range.401] array index 4 is out of range");
				}
			}

			//TEST(constructors,"remove")
			{
				//TEST(constructors,"missing 'path'")
				{
					json j;
					json patch = {{{"op", "remove"}}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.105] parse error: operation 'remove' must have member 'path'");
				}

				//TEST(constructors,"non-string 'path'")
				{
					json j;
					json patch = {{{"op", "remove"}, {"path", 1}}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.105] parse error: operation 'remove' must have string member 'path'");
				}

				//TEST(constructors,"nonexisting target location (array)")
				{
					json j = {1, 2, 3};
					json patch = {{{"op", "remove"}, {"path", "/17"}}};
					EXPECT_THROW(j.patch(patch), json::out_of_range);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.out_of_range.401] array index 17 is out of range");
				}

				//TEST(constructors,"nonexisting target location (object)")
				{
					json j = {{"foo", 1}, {"bar", 2}};
					json patch = {{{"op", "remove"}, {"path", "/baz"}}};
					EXPECT_THROW(j.patch(patch), json::out_of_range);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.out_of_range.403] key 'baz' not found");
				}

				//TEST(constructors,"root element as target location")
				{
					json j = "string";
					json patch = {{{"op", "remove"}, {"path", ""}}};
					EXPECT_THROW(j.patch(patch), json::out_of_range);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.out_of_range.405] JSON pointer has no parent");
				}
			}

			//TEST(constructors,"replace")
			{
				//TEST(constructors,"missing 'path'")
				{
					json j;
					json patch = {{{"op", "replace"}}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.105] parse error: operation 'replace' must have member 'path'");
				}

				//TEST(constructors,"non-string 'path'")
				{
					json j;
					json patch = {{{"op", "replace"}, {"path", 1}}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.105] parse error: operation 'replace' must have string member 'path'");
				}

				//TEST(constructors,"missing 'value'")
				{
					json j;
					json patch = {{{"op", "replace"}, {"path", ""}}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.105] parse error: operation 'replace' must have member 'value'");
				}

				//TEST(constructors,"nonexisting target location (array)")
				{
					json j = {1, 2, 3};
					json patch = {{{"op", "replace"}, {"path", "/17"}, {"value", 19}}};
					EXPECT_THROW(j.patch(patch), json::out_of_range);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.out_of_range.401] array index 17 is out of range");
				}

				//TEST(constructors,"nonexisting target location (object)")
				{
					json j = {{"foo", 1}, {"bar", 2}};
					json patch = {{{"op", "replace"}, {"path", "/baz"}, {"value", 3}}};
					EXPECT_THROW(j.patch(patch), json::out_of_range);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.out_of_range.403] key 'baz' not found");
				}
			}

			//TEST(constructors,"move")
			{
				//TEST(constructors,"missing 'path'")
				{
					json j;
					json patch = {{{"op", "move"}}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.105] parse error: operation 'move' must have member 'path'");
				}

				//TEST(constructors,"non-string 'path'")
				{
					json j;
					json patch = {{{"op", "move"}, {"path", 1}}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.105] parse error: operation 'move' must have string member 'path'");
				}

				//TEST(constructors,"missing 'from'")
				{
					json j;
					json patch = {{{"op", "move"}, {"path", ""}}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.105] parse error: operation 'move' must have member 'from'");
				}

				//TEST(constructors,"non-string 'from'")
				{
					json j;
					json patch = {{{"op", "move"}, {"path", ""}, {"from", 1}}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.105] parse error: operation 'move' must have string member 'from'");
				}

				//TEST(constructors,"nonexisting from location (array)")
				{
					json j = {1, 2, 3};
					json patch = {{{"op", "move"}, {"path", "/0"}, {"from", "/5"}}};
					EXPECT_THROW(j.patch(patch), json::out_of_range);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.out_of_range.401] array index 5 is out of range");
				}

				//TEST(constructors,"nonexisting from location (object)")
				{
					json j = {{"foo", 1}, {"bar", 2}};
					json patch = {{{"op", "move"}, {"path", "/baz"}, {"from", "/baz"}}};
					EXPECT_THROW(j.patch(patch), json::out_of_range);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.out_of_range.403] key 'baz' not found");
				}
			}

			//TEST(constructors,"copy")
			{
				//TEST(constructors,"missing 'path'")
				{
					json j;
					json patch = {{{"op", "copy"}}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.105] parse error: operation 'copy' must have member 'path'");
				}

				//TEST(constructors,"non-string 'path'")
				{
					json j;
					json patch = {{{"op", "copy"}, {"path", 1}}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.105] parse error: operation 'copy' must have string member 'path'");
				}

				//TEST(constructors,"missing 'from'")
				{
					json j;
					json patch = {{{"op", "copy"}, {"path", ""}}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.105] parse error: operation 'copy' must have member 'from'");
				}

				//TEST(constructors,"non-string 'from'")
				{
					json j;
					json patch = {{{"op", "copy"}, {"path", ""}, {"from", 1}}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.105] parse error: operation 'copy' must have string member 'from'");
				}

				//TEST(constructors,"nonexisting from location (array)")
				{
					json j = {1, 2, 3};
					json patch = {{{"op", "copy"}, {"path", "/0"}, {"from", "/5"}}};
					EXPECT_THROW(j.patch(patch), json::out_of_range);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.out_of_range.401] array index 5 is out of range");
				}

				//TEST(constructors,"nonexisting from location (object)")
				{
					json j = {{"foo", 1}, {"bar", 2}};
					json patch = {{{"op", "copy"}, {"path", "/fob"}, {"from", "/baz"}}};
					EXPECT_THROW(j.patch(patch), json::out_of_range);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.out_of_range.403] key 'baz' not found");
				}
			}

			//TEST(constructors,"test")
			{
				//TEST(constructors,"missing 'path'")
				{
					json j;
					json patch = {{{"op", "test"}}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.105] parse error: operation 'test' must have member 'path'");
				}

				//TEST(constructors,"non-string 'path'")
				{
					json j;
					json patch = {{{"op", "test"}, {"path", 1}}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.105] parse error: operation 'test' must have string member 'path'");
				}

				//TEST(constructors,"missing 'value'")
				{
					json j;
					json patch = {{{"op", "test"}, {"path", ""}}};
					EXPECT_THROW(j.patch(patch), json::parse_error);
					//CHECK_THROWS_WITH(j.patch(patch),
									  //"[json.exception.parse_error.105] parse error: operation 'test' must have member 'value'");
				}
			}
		}

		//TEST(constructors,"Examples from jsonpatch.com")
		{
			//TEST(constructors,"Simple Example")
			{
				// The original document
				json doc = R"(
					{
					  "baz": "qux",
					  "foo": "bar"
					}
				)"_json;

				// The patch
				json patch = R"(
					[
					  { "op": "replace", "path": "/baz", "value": "boo" },
					  { "op": "add", "path": "/hello", "value": ["world"] },
					  { "op": "remove", "path": "/foo"}
					]
				)"_json;

				// The result
				json result = R"(
					{
					   "baz": "boo",
					   "hello": ["world"]
					}
				)"_json;

				// check if patched value is as expected
				EXPECT_TRUE(doc.patch(patch) == result);

				// check roundtrip
				EXPECT_TRUE(doc.patch(json::diff(doc, result)) == result);
			}

			//TEST(constructors,"Operations")
			{
				// The original document
				json doc = R"(
					{
					  "biscuits": [
						{"name":"Digestive"},
						{"name": "Choco Liebniz"}
					  ]
					}
				)"_json;

				//TEST(constructors,"add")
				{
					// The patch
					json patch = R"(
						[
							{"op": "add", "path": "/biscuits/1", "value": {"name": "Ginger Nut"}}
						]
					)"_json;

					// The result
					json result = R"(
						{
						  "biscuits": [
							{"name": "Digestive"},
							{"name": "Ginger Nut"},
							{"name": "Choco Liebniz"}
						  ]
						}
					)"_json;

					// check if patched value is as expected
					EXPECT_TRUE(doc.patch(patch) == result);

					// check roundtrip
					EXPECT_TRUE(doc.patch(json::diff(doc, result)) == result);
				}

				//TEST(constructors,"remove")
				{
					// The patch
					json patch = R"(
						[
							{"op": "remove", "path": "/biscuits"}
						]
					)"_json;

					// The result
					json result = R"(
						{}
					)"_json;

					// check if patched value is as expected
					EXPECT_TRUE(doc.patch(patch) == result);

					// check roundtrip
					EXPECT_TRUE(doc.patch(json::diff(doc, result)) == result);
				}

				//TEST(constructors,"replace")
				{
					// The patch
					json patch = R"(
						[
							{"op": "replace", "path": "/biscuits/0/name", "value": "Chocolate Digestive"}
						]
					)"_json;

					// The result
					json result = R"(
						{
						  "biscuits": [
							{"name": "Chocolate Digestive"},
							{"name": "Choco Liebniz"}
						  ]
						}
					)"_json;

					// check if patched value is as expected
					EXPECT_TRUE(doc.patch(patch) == result);

					// check roundtrip
					EXPECT_TRUE(doc.patch(json::diff(doc, result)) == result);
				}

				//TEST(constructors,"copy")
				{
					// The patch
					json patch = R"(
						[
							{"op": "copy", "from": "/biscuits/0", "path": "/best_biscuit"}
						]
					)"_json;

					// The result
					json result = R"(
						{
						  "biscuits": [
							{"name": "Digestive"},
							{"name": "Choco Liebniz"}
						  ],
						  "best_biscuit": {
							"name": "Digestive"
						  }
						}
					)"_json;

					// check if patched value is as expected
					EXPECT_TRUE(doc.patch(patch) == result);

					// check roundtrip
					EXPECT_TRUE(doc.patch(json::diff(doc, result)) == result);
				}

				//TEST(constructors,"move")
				{
					// The patch
					json patch = R"(
						[
							{"op": "move", "from": "/biscuits", "path": "/cookies"}
						]
					)"_json;

					// The result
					json result = R"(
						{
						  "cookies": [
							{"name": "Digestive"},
							{"name": "Choco Liebniz"}
						  ]
						}
					)"_json;

					// check if patched value is as expected
					EXPECT_TRUE(doc.patch(patch) == result);

					// check roundtrip
					EXPECT_TRUE(doc.patch(json::diff(doc, result)) == result);
				}

				//TEST(constructors,"test")
				{
					// The patch
					json patch = R"(
						[
							{"op": "test", "path": "/best_biscuit/name", "value": "Choco Liebniz"}
						]
					)"_json;

					// the test will fail
					EXPECT_THROW(doc.patch(patch), json::other_error);
					//CHECK_THROWS_WITH(doc.patch(patch), "[json.exception.other_error.501] unsuccessful: " + patch[0].dump());
				}
			}
		}

		//TEST(constructors,"Examples from bruth.github.io/jsonpatch-js")
		{
			//TEST(constructors,"add")
			{
				EXPECT_TRUE(R"( {} )"_json.patch(
						  R"( [{"op": "add", "path": "/foo", "value": "bar"}] )"_json
					  ) == R"( {"foo": "bar"} )"_json);

				EXPECT_TRUE(R"( {"foo": [1, 3]} )"_json.patch(
						  R"( [{"op": "add", "path": "/foo", "value": "bar"}] )"_json
					  ) == R"( {"foo": "bar"} )"_json);

				EXPECT_TRUE(R"( {"foo": [{}]} )"_json.patch(
						  R"( [{"op": "add", "path": "/foo/0/bar", "value": "baz"}] )"_json
					  ) == R"( {"foo": [{"bar": "baz"}]} )"_json);
			}

			//TEST(constructors,"remove")
			{
				EXPECT_TRUE(R"( {"foo": "bar"} )"_json.patch(
						  R"( [{"op": "remove", "path": "/foo"}] )"_json
					  ) == R"( {} )"_json);

				EXPECT_TRUE(R"( {"foo": [1, 2, 3]} )"_json.patch(
						  R"( [{"op": "remove", "path": "/foo/1"}] )"_json
					  ) == R"( {"foo": [1, 3]} )"_json);

				EXPECT_TRUE(R"( {"foo": [{"bar": "baz"}]} )"_json.patch(
						  R"( [{"op": "remove", "path": "/foo/0/bar"}] )"_json
					  ) == R"( {"foo": [{}]} )"_json);
			}

			//TEST(constructors,"replace")
			{
				EXPECT_TRUE(R"( {"foo": "bar"} )"_json.patch(
						  R"( [{"op": "replace", "path": "/foo", "value": 1}] )"_json
					  ) == R"( {"foo": 1} )"_json);

				EXPECT_TRUE(R"( {"foo": [1, 2, 3]} )"_json.patch(
						  R"( [{"op": "replace", "path": "/foo/1", "value": 4}] )"_json
					  ) == R"( {"foo": [1, 4, 3]} )"_json);

				EXPECT_TRUE(R"( {"foo": [{"bar": "baz"}]} )"_json.patch(
						  R"( [{"op": "replace", "path": "/foo/0/bar", "value": 1}] )"_json
					  ) == R"( {"foo": [{"bar": 1}]} )"_json);
			}

			//TEST(constructors,"move")
			{
				EXPECT_TRUE(R"( {"foo": [1, 2, 3]} )"_json.patch(
						  R"( [{"op": "move", "from": "/foo", "path": "/bar"}] )"_json
					  ) == R"( {"bar": [1, 2, 3]} )"_json);
			}

			//TEST(constructors,"copy")
			{
				EXPECT_TRUE(R"( {"foo": [1, 2, 3]} )"_json.patch(
						  R"( [{"op": "copy", "from": "/foo/1", "path": "/bar"}] )"_json
					  ) == R"( {"foo": [1, 2, 3], "bar": 2} )"_json);
			}

			//TEST(constructors,"copy")
			{
				EXPECT_NO_THROW(R"( {"foo": "bar"} )"_json.patch(
								  R"( [{"op": "test", "path": "/foo", "value": "bar"}] )"_json));
			}
		}

		//TEST(constructors,"Tests from github.com/json-patch/json-patch-tests")
		{
			for (auto filename :
					{"test/data/json-patch-tests/spec_tests.json",
					 "test/data/json-patch-tests/tests.json"
					})
			{
				//CAPTURE(filename);
				std::ifstream f(filename);
				json suite = json::parse(f);

				for (const auto& test : suite)
				{
					//CAPTURE(test.value("comment", ""))

					// skip tests marked as disabled
					if (test.value("disabled", false))
					{
						continue;
					}

					const auto& doc = test["doc"];
					const auto& patch = test["patch"];

					if (test.count("error") == 0)
					{
						// if an expected value is given, use it; use doc otherwise
						const auto& expected = test.value("expected", doc);
						EXPECT_TRUE(doc.patch(patch) == expected);
					}
					else
					{
						EXPECT_ANY_THROW(doc.patch(patch));
					}
				}
			}
		}
	}
}
