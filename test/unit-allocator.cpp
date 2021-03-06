#include "gtest/gtest.h"
#define private public
#include "json.hpp"

using nlohmann::json;
namespace
{
	// special test case to check if memory is leaked if constructor throws

	template<class T>
	struct bad_allocator : std::allocator<T>
	{
		template<class... Args>
		void construct(T*, Args&& ...)
		{
			throw std::bad_alloc();
		}
	};

	TEST(allocator, bad_alloc)
	{
		//TEST(allocator,"bad_alloc")
		{
			// create JSON type using the throwing allocator
			using bad_json = nlohmann::basic_json<std::map,
				  std::vector,
				  std::string,
				  bool,
				  std::int64_t,
				  std::uint64_t,
				  double,
				  bad_allocator>;

			// creating an object should throw
			EXPECT_THROW(bad_json(bad_json::value_t::object), std::bad_alloc);
		}
	}

	static bool next_construct_fails = false;
	static bool next_destroy_fails = false;
	static bool next_deallocate_fails = false;

	template<class T>
	struct my_allocator : std::allocator<T>
	{
		template<class... Args>
		void construct(T* p, Args&& ... args)
		{
			if (next_construct_fails)
			{
				next_construct_fails = false;
				throw std::bad_alloc();
			}
			else
			{
				::new (reinterpret_cast<void*>(p)) T(std::forward<Args>(args)...);
			}
		}

		void deallocate(T* p, std::size_t n)
		{
			if (next_deallocate_fails)
			{
				next_deallocate_fails = false;
				throw std::bad_alloc();
			}
			else
			{
				std::allocator<T>::deallocate(p, n);
			}
		}

		void destroy(T* p)
		{
			if (next_destroy_fails)
			{
				next_destroy_fails = false;
				throw std::bad_alloc();
			}
			else
			{
				p->~T();
			}
		}
	};

	// allows deletion of raw pointer, usually hold by json_value
	template<class T>
	void my_allocator_clean_up(T* p)
	{
		assert(p != nullptr);
		my_allocator<T> alloc;
		alloc.destroy(p);
		alloc.deallocate(p, 1);
	}

	TEST(allocator, controlled_bad_alloc)
	{
		// create JSON type using the throwing allocator
		using my_json = nlohmann::basic_json<std::map,
			  std::vector,
			  std::string,
			  bool,
			  std::int64_t,
			  std::uint64_t,
			  double,
			  my_allocator>;

		//TEST(allocator,"class json_value")
		{
			//TEST(allocator,"json_value(value_t)")
			{
				//TEST(allocator,"object")
				{
					next_construct_fails = false;
					auto t = my_json::value_t::object;
					EXPECT_NO_THROW(my_allocator_clean_up(my_json::json_value(t).object));
					next_construct_fails = true;
					EXPECT_NO_THROW(my_json::json_value(t));
					next_construct_fails = false;
				}
				//TEST(allocator,"array")
				{
					next_construct_fails = false;
					auto t = my_json::value_t::array;
					EXPECT_NO_THROW(my_allocator_clean_up(my_json::json_value(t).array));
					next_construct_fails = true;
					EXPECT_NO_THROW(my_json::json_value(t));
					next_construct_fails = false;
				}
				//TEST(allocator,"string")
				{
					next_construct_fails = false;
					auto t = my_json::value_t::string;
					EXPECT_NO_THROW(my_allocator_clean_up(my_json::json_value(t).string));
					next_construct_fails = true;
					EXPECT_NO_THROW(my_json::json_value(t));
					next_construct_fails = false;
				}
			}

			//TEST(allocator,"json_value(const string_t&)")
			{
				next_construct_fails = false;
				my_json::string_t v("foo");
				EXPECT_NO_THROW(my_allocator_clean_up(my_json::json_value(v).string));
				next_construct_fails = true;
				EXPECT_NO_THROW(my_json::json_value(v));
				next_construct_fails = false;
			}
		}

		//TEST(allocator,"class basic_json")
		{
			//TEST(allocator,"basic_json(const CompatibleObjectType&)")
			{
				next_construct_fails = false;
				std::map<std::string, std::string> v {{"foo", "bar"}};
				EXPECT_NO_THROW(my_json(v));
				next_construct_fails = true;
				EXPECT_NO_THROW(my_json(v));
				next_construct_fails = false;
			}

			//TEST(allocator,"basic_json(const CompatibleArrayType&)")
			{
				next_construct_fails = false;
				std::vector<std::string> v {"foo", "bar", "baz"};
				EXPECT_NO_THROW(my_json(v));
				next_construct_fails = true;
				EXPECT_NO_THROW(my_json(v));
				next_construct_fails = false;
			}

			//TEST(allocator,"basic_json(const typename string_t::value_type*)")
			{
				next_construct_fails = false;
				EXPECT_NO_THROW(my_json("foo"));
				next_construct_fails = true;
				EXPECT_THROW(my_json("foo"), std::bad_alloc);
				next_construct_fails = false;
			}

			//TEST(allocator,"basic_json(const typename string_t::value_type*)")
			{
				next_construct_fails = false;
				std::string s("foo");
				EXPECT_NO_THROW(my_json(s));
				next_construct_fails = true;
				EXPECT_NO_THROW(my_json(s));
				next_construct_fails = false;
			}
		}
	}
}
