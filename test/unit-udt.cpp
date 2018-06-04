#include "json.hpp"
#include "gtest/gtest.h"

using json = nlohmann::json;
#include <array>
#include <map>
#include <memory>
#include <string>

namespace udt {
enum class country { china, france, russia };

struct age {
  int m_val;
  age(int rhs = 0) : m_val(rhs) {}
};

struct name {
  std::string m_val;
  name(const std::string rhs = "") : m_val(rhs) {}
};

struct address {
  std::string m_val;
  address(const std::string rhs = "") : m_val(rhs) {}
};

struct person {
  age m_age;
  name m_name;
  country m_country;
  person() : m_age(), m_name(), m_country() {}
  person(const age &a, const name &n, const country &c)
      : m_age(a), m_name(n), m_country(c) {}
};

struct contact {
  person m_person;
  address m_address;
  contact() : m_person(), m_address() {}
  contact(const person &p, const address &a) : m_person(p), m_address(a) {}
};

struct contact_book {
  name m_book_name;
  std::vector<contact> m_contacts;
  contact_book() : m_book_name(), m_contacts() {}
  contact_book(const name &n, const std::vector<contact> &c)
      : m_book_name(n), m_contacts(c) {}
};
}

// to_json methods
namespace udt {
// templates because of the custom_json tests (see below)
template <typename BasicJsonType> void to_json(BasicJsonType &j, age a) {
  j = a.m_val;
}

template <typename BasicJsonType>
void to_json(BasicJsonType &j, const name &n) {
  j = n.m_val;
}

template <typename BasicJsonType> void to_json(BasicJsonType &j, country c) {
  switch (c) {
  case country::china:
    j = u8"中华人民共和国";
    return;
  case country::france:
    j = "France";
    return;
  case country::russia:
    j = u8"Российская Федерация";
    return;
  }
}

template <typename BasicJsonType>
void to_json(BasicJsonType &j, const person &p) {
  j = BasicJsonType{
      {"age", p.m_age}, {"name", p.m_name}, {"country", p.m_country}};
}

void to_json(nlohmann::json &j, const address &a) { j = a.m_val; }

void to_json(nlohmann::json &j, const contact &c) {
  j = json{{"person", c.m_person}, {"address", c.m_address}};
}

void to_json(nlohmann::json &j, const contact_book &cb) {
  j = json{{"name", cb.m_book_name}, {"contacts", cb.m_contacts}};
}

// operators
bool operator==(age lhs, age rhs) { return lhs.m_val == rhs.m_val; }

bool operator==(const address &lhs, const address &rhs) {
  return lhs.m_val == rhs.m_val;
}

bool operator==(const name &lhs, const name &rhs) {
  return lhs.m_val == rhs.m_val;
}

bool operator==(const person &lhs, const person &rhs) {
  return std::tie(lhs.m_name, lhs.m_age) == std::tie(rhs.m_name, rhs.m_age);
}

bool operator==(const contact &lhs, const contact &rhs) {
  return std::tie(lhs.m_person, lhs.m_address) ==
         std::tie(rhs.m_person, rhs.m_address);
}

bool operator==(const contact_book &lhs, const contact_book &rhs) {
  return std::tie(lhs.m_book_name, lhs.m_contacts) ==
         std::tie(rhs.m_book_name, rhs.m_contacts);
}
}

// from_json methods
namespace udt {
template <typename BasicJsonType>
void from_json(const BasicJsonType &j, age &a) {
  a.m_val = j.template get<int>();
}

template <typename BasicJsonType>
void from_json(const BasicJsonType &j, name &n) {
  n.m_val = j.template get<std::string>();
}

template <typename BasicJsonType>
void from_json(const BasicJsonType &j, country &c) {
  const auto str = j.template get<std::string>();
  static const std::map<std::string, country> m = {
      {u8"中华人民共和国", country::china},
      {"France", country::france},
      {u8"Российская Федерация", country::russia}};

  const auto it = m.find(str);
  // TODO test exceptions
  c = it->second;
}

template <typename BasicJsonType>
void from_json(const BasicJsonType &j, person &p) {
  p.m_age = j["age"].template get<age>();
  p.m_name = j["name"].template get<name>();
  p.m_country = j["country"].template get<country>();
}

void from_json(const nlohmann::json &j, address &a) {
  a.m_val = j.get<std::string>();
}

void from_json(const nlohmann::json &j, contact &c) {
  c.m_person = j["person"].get<person>();
  c.m_address = j["address"].get<address>();
}

void from_json(const nlohmann::json &j, contact_book &cb) {
  cb.m_book_name = j["name"].get<name>();
  cb.m_contacts = j["contacts"].get<std::vector<contact>>();
}
}

TEST(basic_usage, udt) {

  // a bit narcissic maybe :) ?
  const udt::age a{23};
  const udt::name n{"theo"};
  const udt::country c{udt::country::france};
  const udt::person sfinae_addict{a, n, c};
  const udt::person senior_programmer{{42}, {u8"王芳"}, udt::country::china};
  const udt::address addr{"Paris"};
  const udt::contact cpp_programmer{sfinae_addict, addr};
  const udt::contact_book book{{"C++"},
                               {cpp_programmer, {senior_programmer, addr}}};

  {
    EXPECT_TRUE(json(a) == json(23));
    EXPECT_TRUE(json(n) == json("theo"));
    EXPECT_TRUE(json(c) == json("France"));
    EXPECT_TRUE(json(sfinae_addict) ==
                R"({"name":"theo", "age":23, "country":"France"})"_json);
    EXPECT_TRUE(json("Paris") == json(addr));
    EXPECT_TRUE(
        json(cpp_programmer) ==
        R"({"person" : {"age":23, "name":"theo", "country":"France"}, "address":"Paris"})"_json);

    EXPECT_TRUE(
        json(book) ==
        u8R"({"name":"C++", "contacts" : [{"person" : {"age":23, "name":"theo", "country":"France"}, "address":"Paris"}, {"person" : {"age":42, "country":"中华人民共和国", "name":"王芳"}, "address":"Paris"}]})"_json);
  }

  {
    const auto big_json =
        u8R"({"name":"C++", "contacts" : [{"person" : {"age":23, "name":"theo", "country":"France"}, "address":"Paris"}, {"person" : {"age":42, "country":"中华人民共和国", "name":"王芳"}, "address":"Paris"}]})"_json;
    {
      const auto parsed_book = big_json.get<udt::contact_book>();
      const auto book_name = big_json["name"].get<udt::name>();
      const auto contacts =
          big_json["contacts"].get<std::vector<udt::contact>>();
      const auto contact_json = big_json["contacts"].at(0);
      const auto contact = contact_json.get<udt::contact>();
      const auto person = contact_json["person"].get<udt::person>();
      const auto address = contact_json["address"].get<udt::address>();
      const auto age = contact_json["person"]["age"].get<udt::age>();
      const auto country =
          contact_json["person"]["country"].get<udt::country>();
      const auto name = contact_json["person"]["name"].get<udt::name>();

      EXPECT_TRUE(age == a);
      EXPECT_TRUE(name == n);
      EXPECT_TRUE(country == c);
      EXPECT_TRUE(address == addr);
      EXPECT_TRUE(person == sfinae_addict);
      EXPECT_TRUE(contact == cpp_programmer);
      EXPECT_TRUE(contacts == book.m_contacts);
      EXPECT_TRUE(book_name == udt::name{"C++"});
      EXPECT_TRUE(book == parsed_book);
    }

    {
      const udt::contact_book parsed_book = big_json;
      const udt::name book_name = big_json["name"];
      const std::vector<udt::contact> contacts = big_json["contacts"];
      const auto contact_json = big_json["contacts"].at(0);
      const udt::contact contact = contact_json;
      const udt::person person = contact_json["person"];
      const udt::address address = contact_json["address"];
      const udt::age age = contact_json["person"]["age"];
      const udt::country country = contact_json["person"]["country"];
      const udt::name name = contact_json["person"]["name"];

      EXPECT_TRUE(age == a);
      EXPECT_TRUE(name == n);
      EXPECT_TRUE(country == c);
      EXPECT_TRUE(address == addr);
      EXPECT_TRUE(person == sfinae_addict);
      EXPECT_TRUE(contact == cpp_programmer);
      EXPECT_TRUE(contacts == book.m_contacts);
      EXPECT_TRUE(book_name == udt::name{"C++"});
      EXPECT_TRUE(book == parsed_book);
    }
  }
}

namespace udt {
struct legacy_type {
  std::string number;
  legacy_type() : number() {}
  legacy_type(const std::string &n) : number(n) {}
};
}

namespace nlohmann {
template <typename T> struct adl_serializer<std::shared_ptr<T>> {
  static void to_json(json &j, const std::shared_ptr<T> &opt) {
    if (opt) {
      j = *opt;
    } else {
      j = nullptr;
    }
  }

  static void from_json(const json &j, std::shared_ptr<T> &opt) {
    if (j.is_null()) {
      opt = nullptr;
    } else {
      opt.reset(new T(j.get<T>()));
    }
  }
};

template <> struct adl_serializer<udt::legacy_type> {
  static void to_json(json &j, const udt::legacy_type &l) {
    j = std::stoi(l.number);
  }

  static void from_json(const json &j, udt::legacy_type &l) {
    l.number = std::to_string(j.get<int>());
  }
};
}

TEST(adl_serializer_specialization, udt) {
  {{std::shared_ptr<udt::person> optPerson;

  json j = optPerson;
  EXPECT_TRUE(j.is_null());

  optPerson.reset(new udt::person{{42}, {"John Doe"}, udt::country::russia});
  j = optPerson;
  EXPECT_FALSE(j.is_null());

  EXPECT_TRUE(j.get<udt::person>() == *optPerson);
}

{
  auto person = udt::person{{42}, {"John Doe"}, udt::country::russia};
  json j = person;

  auto optPerson = j.get<std::shared_ptr<udt::person>>();
  ASSERT_TRUE(optPerson);
  EXPECT_TRUE(*optPerson == person);

  j = nullptr;
  optPerson = j.get<std::shared_ptr<udt::person>>();
  EXPECT_TRUE(!optPerson);
}
}

{
  {
    udt::legacy_type lt{"4242"};

    json j = lt;
    EXPECT_TRUE(j.get<int>() == 4242);
  }

  {
    json j = 4242;
    auto lt = j.get<udt::legacy_type>();
    EXPECT_TRUE(lt.number == "4242");
  }
}
}

namespace nlohmann {
template <> struct adl_serializer<std::vector<float>> {
  using type = std::vector<float>;
  static void to_json(json &j, const type &) { j = "hijacked!"; }

  static void from_json(const json &, type &opt) { opt = {42.0, 42.0, 42.0}; }

  // preferred version
  static type from_json(const json &) { return {4.0, 5.0, 6.0}; }
};
}

TEST(even_supported_types_can_be_specialized, udt) {
  json j = std::vector<float>{1.0, 2.0, 3.0};
  EXPECT_TRUE(j.dump() == R"("hijacked!")");
  auto f = j.get<std::vector<float>>();
  // the single argument from_json method is preferred
  EXPECT_TRUE((f == std::vector<float>{4.0, 5.0, 6.0}));
}

namespace nlohmann {
template <typename T> struct adl_serializer<std::unique_ptr<T>> {
  static void to_json(json &j, const std::unique_ptr<T> &opt) {
    if (opt) {
      j = *opt;
    } else {
      j = nullptr;
    }
  }

  // this is the overload needed for non-copyable types,
  static std::unique_ptr<T> from_json(const json &j) {
    if (j.is_null()) {
      return nullptr;
    } else {
      return std::unique_ptr<T>(new T(j.get<T>()));
    }
  }
};
}

TEST(Non_copyable_types, udt) {
  {
    std::unique_ptr<udt::person> optPerson;

    json j = optPerson;
    EXPECT_TRUE(j.is_null());

    optPerson.reset(new udt::person{{42}, {"John Doe"}, udt::country::russia});
    j = optPerson;
    EXPECT_FALSE(j.is_null());

    EXPECT_TRUE(j.get<udt::person>() == *optPerson);
  }

  {
    auto person = udt::person{{42}, {"John Doe"}, udt::country::russia};
    json j = person;

    auto optPerson = j.get<std::unique_ptr<udt::person>>();
    ASSERT_TRUE(optPerson);
    EXPECT_TRUE(*optPerson == person);

    j = nullptr;
    optPerson = j.get<std::unique_ptr<udt::person>>();
    EXPECT_TRUE(!optPerson);
  }
}

// custom serializer - advanced usage
// pack structs that are pod-types (but not scalar types)
// relies on adl for any other type
template <typename T, typename = void> struct pod_serializer {
  // use adl for non-pods, or scalar types
  template <typename BasicJsonType, typename U = T,
            typename std::enable_if<not(std::is_pod<U>::value and
                                        std::is_class<U>::value),
                                    int>::type = 0>
  static void from_json(const BasicJsonType &j, U &t) {
    using nlohmann::from_json;
    from_json(j, t);
  }

  // special behaviour for pods
  template <
      typename BasicJsonType, typename U = T,
      typename std::enable_if<std::is_pod<U>::value and std::is_class<U>::value,
                              int>::type = 0>
  static void from_json(const BasicJsonType &j, U &t) {
    std::uint64_t value;
    // TODO The following block is no longer relevant in this serializer, make
    // another one that shows the issue
    // the problem arises only when one from_json method is defined without any
    // constraint
    //
    // Why cannot we simply use: j.get<std::uint64_t>() ?
    // Well, with the current experiment, the get method looks for a from_json
    // function, which we are currently defining!
    // This would end up in a stack overflow. Calling nlohmann::from_json is a
    // workaround (is it?).
    // I shall find a good way to avoid this once all constructors are converted
    // to free methods
    //
    // In short, constructing a json by constructor calls to_json
    // calling get calls from_json, for now, we cannot do this in custom
    // serializers
    nlohmann::from_json(j, value);
    auto bytes = static_cast<char *>(static_cast<void *>(&value));
    std::memcpy(&t, bytes, sizeof(value));
  }

  template <typename BasicJsonType, typename U = T,
            typename std::enable_if<not(std::is_pod<U>::value and
                                        std::is_class<U>::value),
                                    int>::type = 0>
  static void to_json(BasicJsonType &j, const T &t) {
    using nlohmann::to_json;
    to_json(j, t);
  }

  template <
      typename BasicJsonType, typename U = T,
      typename std::enable_if<std::is_pod<U>::value and std::is_class<U>::value,
                              int>::type = 0>
  static void to_json(BasicJsonType &j, const T &t) noexcept {
    auto bytes =
        static_cast<const unsigned char *>(static_cast<const void *>(&t));
    std::uint64_t value = bytes[0];
    for (auto i = 1; i < 8; ++i)
      value |= std::uint64_t{bytes[i]} << 8 * i;
    nlohmann::to_json(j, value);
  }
};

namespace udt {
struct small_pod {
  int begin;
  char middle;
  short end;
};

struct non_pod {
  std::string s;
  non_pod() : s() {}
  non_pod(const std::string &S) : s(S) {}
};

template <typename BasicJsonType>
void to_json(BasicJsonType &j, const non_pod &np) {
  j = np.s;
}

template <typename BasicJsonType>
void from_json(const BasicJsonType &j, non_pod &np) {
  np.s = j.template get<std::string>();
}

bool operator==(small_pod lhs, small_pod rhs) noexcept {
  return std::tie(lhs.begin, lhs.middle, lhs.end) ==
         std::tie(rhs.begin, rhs.middle, rhs.end);
}

bool operator==(const non_pod &lhs, const non_pod &rhs) noexcept {
  return lhs.s == rhs.s;
}

std::ostream &operator<<(std::ostream &os, small_pod l) {
  return os << "begin: " << l.begin << ", middle: " << l.middle
            << ", end: " << l.end;
}
}

TEST(custom_serializer_for_pods, udt) {
  using custom_json =
      nlohmann::basic_json<std::map, std::vector, std::string, bool,
                           std::int64_t, std::uint64_t, double, std::allocator,
                           pod_serializer>;

  auto p = udt::small_pod{42, '/', 42};
  custom_json j = p;

  auto p2 = j.get<udt::small_pod>();

  EXPECT_TRUE(p == p2);

  auto np = udt::non_pod{{"non-pod"}};
  custom_json j2 = np;
  auto np2 = j2.get<udt::non_pod>();
  EXPECT_TRUE(np == np2);
}

template <typename T, typename> struct another_adl_serializer;

using custom_json =
    nlohmann::basic_json<std::map, std::vector, std::string, bool, std::int64_t,
                         std::uint64_t, double, std::allocator,
                         another_adl_serializer>;

template <typename T, typename> struct another_adl_serializer {
  static void from_json(const custom_json &j, T &t) {
    using nlohmann::from_json;
    from_json(j, t);
  }

  static void to_json(custom_json &j, const T &t) {
    using nlohmann::to_json;
    to_json(j, t);
  }
};

TEST(custom_serializer_that_does_adl_by_default, udt) {
  using json = nlohmann::json;

  auto me = udt::person{{23}, {"theo"}, udt::country::france};

  json j = me;
  custom_json cj = me;

  EXPECT_TRUE(j.dump() == cj.dump());

  EXPECT_TRUE(me == j.get<udt::person>());
  EXPECT_TRUE(me == cj.get<udt::person>());
}

TEST(different_basic_json_types_conversions, test) {
  using json = nlohmann::json;
  {
    json j;
    custom_json cj = j;
    EXPECT_TRUE(cj == nullptr);
  }

  {
    json j = true;
    custom_json cj = j;
    EXPECT_TRUE(cj == true);
  }

  {
    json j(json::value_t::discarded);
    custom_json cj;
    EXPECT_NO_THROW(cj = j);
    EXPECT_TRUE(cj.type() == custom_json::value_t::discarded);
  }

  {
    json j = {1, 2, 3};
    custom_json cj = j;
    EXPECT_TRUE((cj == std::vector<int>{1, 2, 3}));
  }

  {
    json j = 42;
    custom_json cj = j;
    EXPECT_TRUE(cj == 42);
  }

  {
    json j = 42.0;
    custom_json cj = j;
    EXPECT_TRUE(cj == 42.0);
  }

  {
    json j = 42u;
    custom_json cj = j;
    EXPECT_TRUE(cj == 42u);
  }

  {
    json j = "forty-two";
    custom_json cj = j;
    EXPECT_TRUE(cj == "forty-two");
  }

  {
    json j = {{"forty", "two"}};
    custom_json cj = j;
    auto m = j.get<std::map<std::string, std::string>>();
    EXPECT_TRUE(cj == m);
  }

  {
    json j = 42;
    custom_json cj = j.get<custom_json>();
    EXPECT_TRUE(cj == 42);
  }
}

namespace {
struct incomplete;

// std::is_constructible is broken on macOS' libc++
// use the cppreference implementation

template <typename T, typename = void>
struct is_constructible_patched : std::false_type {};

template <typename T>
struct is_constructible_patched<T, decltype(void(json(std::declval<T>())))>
    : std::true_type {};
}
TEST(
    an_incomplete_type_does_not_trigger_a_compiler_error_in_non_evaluated_context,
    udt) {
  static_assert(not is_constructible_patched<json, incomplete>::value, "");
}

namespace {
class Evil {
public:
  Evil() = default;
  template <typename T> Evil(T) {}
};

void from_json(const json &, Evil &) {}
}

TEST(Issue92, fix) {
  // Prevent get<std::vector<Evil>>() to throw
  auto j = json::array();

  EXPECT_NO_THROW(j.get<Evil>());
  EXPECT_NO_THROW(j.get<std::vector<Evil>>());
}
