#include "json.hpp"
#include "gtest/gtest.h"

using json = nlohmann::json;
bool wstring_is_utf16();
bool wstring_is_utf16()
{
    return (std::wstring(L"💩") == std::wstring(L"\U0001F4A9"));
}

bool u16string_is_utf16();
bool u16string_is_utf16()
{
    return (std::u16string(u"💩") == std::u16string(u"\U0001F4A9"));
}

bool u32string_is_utf32();
bool u32string_is_utf32()
{
    return (std::u32string(U"💩") == std::u32string(U"\U0001F4A9"));
}

TEST(WideStringTest, wstring_is_utf16)
{
    if (wstring_is_utf16()) {
        std::wstring w = L"[12.2,\"Ⴥaäö💤🧢\"]";
        json j = json::parse(w);
        EXPECT_EQ(j.dump(), "[12.2,\"Ⴥaäö💤🧢\"]");
    }
}
TEST(WideStringTest, invalid_wstring_is_utf16)
{
    if (wstring_is_utf16()) {
        std::wstring w = L"\"\xDBFF";
        EXPECT_THROW(json::parse(w), json::parse_error);
    }
}

TEST(WideStringTest, u16string)
{
    if (u16string_is_utf16()) {
        std::u16string w = u"[12.2,\"Ⴥaäö💤🧢\"]";
        json j = json::parse(w);
        EXPECT_EQ(j.dump(), "[12.2,\"Ⴥaäö💤🧢\"]");
    }
}

TEST(WideStringTest, invalid_u16string)
{
    if (u16string_is_utf16()) {
        std::u16string w = u"\"\xDBFF";
        EXPECT_THROW(json::parse(w), json::parse_error);
    }
}
TEST(WideStringTest, u32string)
{
  if (u32string_is_utf32()){
    std::u32string w = U"[12.2,\"Ⴥaäö💤🧢\"]";
    json j = json::parse(w);
    EXPECT_EQ(j.dump() , "[12.2,\"Ⴥaäö💤🧢\"]");
  }
}
TEST(WideStringTest, invalid_u32string)
{
  if (u32string_is_utf32()){
    std::u32string w = U"\"\x110000";
    EXPECT_THROW(json::parse(w), json::parse_error);

  }
}
