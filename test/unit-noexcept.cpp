#include "json.hpp"
#include "gtest/gtest.h"

using json = nlohmann::json;

enum test {};

struct pod {};
struct pod_bis {};

void to_json(json &, pod) noexcept;
void to_json(json &, pod_bis);
void from_json(const json &, pod) noexcept;
void from_json(const json &, pod_bis);
static json j;

static_assert(noexcept(json{}), "");
static_assert(noexcept(nlohmann::to_json(j, 2)), "");
static_assert(noexcept(nlohmann::to_json(j, 2.5)), "");
static_assert(noexcept(nlohmann::to_json(j, true)), "");
static_assert(noexcept(nlohmann::to_json(j, test{})), "");
static_assert(noexcept(nlohmann::to_json(j, pod{})), "");
static_assert(not noexcept(nlohmann::to_json(j, pod_bis{})), "");
static_assert(noexcept(json(2)), "");
static_assert(noexcept(json(test{})), "");
static_assert(noexcept(json(pod{})), "");
static_assert(noexcept(j.get<pod>()), "");
static_assert(not noexcept(j.get<pod_bis>()), "");
static_assert(noexcept(json(pod{})), "");

TEST(runtime_checks, no_throw_copy_constructible_exceptions) {
  // for ERR60-CPP (https://github.com/nlohmann/json/issues/531):
  // Exceptions should be nothrow-copy-constructible. However, compilers
  // treat std::runtime_exception differently in this regard. Therefore,
  // we can only demand nothrow-copy-constructibility for our exceptions
  // if std::runtime_exception is.
  EXPECT_EQ(std::is_nothrow_copy_constructible<json::exception>::value,
            std::is_nothrow_copy_constructible<std::runtime_error>::value);
  EXPECT_EQ(std::is_nothrow_copy_constructible<json::parse_error>::value,
            std::is_nothrow_copy_constructible<std::runtime_error>::value);
  EXPECT_EQ(std::is_nothrow_copy_constructible<json::invalid_iterator>::value,
            std::is_nothrow_copy_constructible<std::runtime_error>::value);
  EXPECT_EQ(std::is_nothrow_copy_constructible<json::type_error>::value,
            std::is_nothrow_copy_constructible<std::runtime_error>::value);
  EXPECT_EQ(std::is_nothrow_copy_constructible<json::out_of_range>::value,
            std::is_nothrow_copy_constructible<std::runtime_error>::value);
  EXPECT_EQ(std::is_nothrow_copy_constructible<json::other_error>::value,
            std::is_nothrow_copy_constructible<std::runtime_error>::value);
}
