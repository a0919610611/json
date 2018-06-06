#include "helper.hpp"
#include "json.hpp"
#include "gtest/gtest.h"
#include <fstream>

using json = nlohmann::json;

class SaxCountdown : public nlohmann::json::json_sax_t {
public:
    explicit SaxCountdown(const int count)
        : events_left(count)
    {
    }

    bool null() override { return events_left-- > 0; }

    bool boolean(bool) override { return events_left-- > 0; }

    bool number_integer(json::number_integer_t) override
    {
        return events_left-- > 0;
    }

    bool number_unsigned(json::number_unsigned_t) override
    {
        return events_left-- > 0;
    }

    bool number_float(json::number_float_t, const std::string&) override
    {
        return events_left-- > 0;
    }

    bool string(std::string&) override { return events_left-- > 0; }

    bool start_object(std::size_t) override { return events_left-- > 0; }

    bool key(std::string&) override { return events_left-- > 0; }

    bool end_object() override { return events_left-- > 0; }

    bool start_array(std::size_t) override { return events_left-- > 0; }

    bool end_array() override { return events_left-- > 0; }

    bool parse_error(std::size_t, const std::string&,
        const json::exception&) override
    {
        return false;
    }

private:
    int events_left = 0;
};

TEST(UBJSON, test){ { { // discarded values are not serialized
    json j = json::value_t::discarded;
const auto result = json::to_ubjson(j);
EXPECT_TRUE(result.empty());
}

{
    json j = nullptr;
    std::vector<uint8_t> expected = { 'Z' };
    const auto result = json::to_ubjson(j);
    EXPECT_TRUE(result == expected);

    // roundtrip
    EXPECT_TRUE(json::from_ubjson(result) == j);
    EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}

{ { json j = true;
std::vector<uint8_t> expected = { 'T' };
const auto result = json::to_ubjson(j);
EXPECT_TRUE(result == expected);

// roundtrip
EXPECT_TRUE(json::from_ubjson(result) == j);
EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}

{
    json j = false;
    std::vector<uint8_t> expected = { 'F' };
    const auto result = json::to_ubjson(j);
    EXPECT_TRUE(result == expected);

    // roundtrip
    EXPECT_TRUE(json::from_ubjson(result) == j);
    EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}
}

{ { { std::vector<int64_t> numbers;
numbers.push_back((std::numeric_limits<int64_t>::min)());
numbers.push_back(-1000000000000000000ll);
numbers.push_back(-100000000000000000ll);
numbers.push_back(-10000000000000000ll);
numbers.push_back(-1000000000000000ll);
numbers.push_back(-100000000000000ll);
numbers.push_back(-10000000000000ll);
numbers.push_back(-1000000000000ll);
numbers.push_back(-100000000000ll);
numbers.push_back(-10000000000ll);
numbers.push_back(-2147483649ll);
for (auto i : numbers) {

    // create JSON value with integer number
    json j = i;

    // check type
    EXPECT_TRUE(j.is_number_integer());

    // create expected byte vector
    std::vector<uint8_t> expected;
    expected.push_back(static_cast<uint8_t>('L'));
    expected.push_back(static_cast<uint8_t>((i >> 56) & 0xff));
    expected.push_back(static_cast<uint8_t>((i >> 48) & 0xff));
    expected.push_back(static_cast<uint8_t>((i >> 40) & 0xff));
    expected.push_back(static_cast<uint8_t>((i >> 32) & 0xff));
    expected.push_back(static_cast<uint8_t>((i >> 24) & 0xff));
    expected.push_back(static_cast<uint8_t>((i >> 16) & 0xff));
    expected.push_back(static_cast<uint8_t>((i >> 8) & 0xff));
    expected.push_back(static_cast<uint8_t>(i & 0xff));

    // compare result + size
    const auto result = json::to_ubjson(j);
    EXPECT_TRUE(result == expected);
    EXPECT_TRUE(result.size() == 9);

    // check individual bytes
    EXPECT_TRUE(result[0] == 'L');
    int64_t restored = (static_cast<int64_t>(result[1]) << 070) + (static_cast<int64_t>(result[2]) << 060) + (static_cast<int64_t>(result[3]) << 050) + (static_cast<int64_t>(result[4]) << 040) + (static_cast<int64_t>(result[5]) << 030) + (static_cast<int64_t>(result[6]) << 020) + (static_cast<int64_t>(result[7]) << 010) + static_cast<int64_t>(result[8]);
    EXPECT_TRUE(restored == i);

    // roundtrip
    EXPECT_TRUE(json::from_ubjson(result) == j);
    EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}
}

{
    std::vector<int32_t> numbers;
    numbers.push_back(-32769);
    numbers.push_back(-100000);
    numbers.push_back(-1000000);
    numbers.push_back(-10000000);
    numbers.push_back(-100000000);
    numbers.push_back(-1000000000);
    numbers.push_back(-2147483647 - 1); // https://stackoverflow.com/a/29356002/266378
    for (auto i : numbers) {

        // create JSON value with integer number
        json j = i;

        // check type
        EXPECT_TRUE(j.is_number_integer());

        // create expected byte vector
        std::vector<uint8_t> expected;
        expected.push_back(static_cast<uint8_t>('l'));
        expected.push_back(static_cast<uint8_t>((i >> 24) & 0xff));
        expected.push_back(static_cast<uint8_t>((i >> 16) & 0xff));
        expected.push_back(static_cast<uint8_t>((i >> 8) & 0xff));
        expected.push_back(static_cast<uint8_t>(i & 0xff));

        // compare result + size
        const auto result = json::to_ubjson(j);
        EXPECT_TRUE(result == expected);
        EXPECT_TRUE(result.size() == 5);

        // check individual bytes
        EXPECT_TRUE(result[0] == 'l');
        int32_t restored = (static_cast<int32_t>(result[1]) << 030) + (static_cast<int32_t>(result[2]) << 020) + (static_cast<int32_t>(result[3]) << 010) + static_cast<int32_t>(result[4]);
        EXPECT_TRUE(restored == i);

        // roundtrip
        EXPECT_TRUE(json::from_ubjson(result) == j);
        EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
    }
}

{
    for (int32_t i = -32768; i <= -129; ++i) {

        // create JSON value with integer number
        json j = i;

        // check type
        EXPECT_TRUE(j.is_number_integer());

        // create expected byte vector
        std::vector<uint8_t> expected;
        expected.push_back(static_cast<uint8_t>('I'));
        expected.push_back(static_cast<uint8_t>((i >> 8) & 0xff));
        expected.push_back(static_cast<uint8_t>(i & 0xff));

        // compare result + size
        const auto result = json::to_ubjson(j);
        EXPECT_TRUE(result == expected);
        EXPECT_TRUE(result.size() == 3);

        // check individual bytes
        EXPECT_TRUE(result[0] == 'I');
        int16_t restored = static_cast<int16_t>(((result[1] << 8) + result[2]));
        EXPECT_TRUE(restored == i);

        // roundtrip
        EXPECT_TRUE(json::from_ubjson(result) == j);
        EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
    }
}

{
    json j = -9263;
    std::vector<uint8_t> expected = { 'I', 0xdb, 0xd1 };

    // compare result + size
    const auto result = json::to_ubjson(j);
    EXPECT_TRUE(result == expected);
    EXPECT_TRUE(result.size() == 3);

    // check individual bytes
    EXPECT_TRUE(result[0] == 'I');
    int16_t restored = static_cast<int16_t>(((result[1] << 8) + result[2]));
    EXPECT_TRUE(restored == -9263);

    // roundtrip
    EXPECT_TRUE(json::from_ubjson(result) == j);
    EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}

{
    for (auto i = -128; i <= -1; ++i) {

        // create JSON value with integer number
        json j = i;

        // check type
        EXPECT_TRUE(j.is_number_integer());

        // create expected byte vector
        std::vector<uint8_t> expected;
        expected.push_back('i');
        expected.push_back(static_cast<uint8_t>(i));

        // compare result + size
        const auto result = json::to_ubjson(j);
        EXPECT_TRUE(result == expected);
        EXPECT_TRUE(result.size() == 2);

        // check individual bytes
        EXPECT_TRUE(result[0] == 'i');
        EXPECT_TRUE(static_cast<int8_t>(result[1]) == i);

        // roundtrip
        EXPECT_TRUE(json::from_ubjson(result) == j);
        EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
    }
}

{
    for (size_t i = 0; i <= 127; ++i) {

        // create JSON value with integer number
        json j = -1;
        j.get_ref<json::number_integer_t&>() = static_cast<json::number_integer_t>(i);

        // check type
        EXPECT_TRUE(j.is_number_integer());

        // create expected byte vector
        std::vector<uint8_t> expected;
        expected.push_back(static_cast<uint8_t>('i'));
        expected.push_back(static_cast<uint8_t>(i));

        // compare result + size
        const auto result = json::to_ubjson(j);
        EXPECT_TRUE(result == expected);
        EXPECT_TRUE(result.size() == 2);

        // check individual bytes
        EXPECT_TRUE(result[0] == 'i');
        EXPECT_TRUE(result[1] == i);

        // roundtrip
        EXPECT_TRUE(json::from_ubjson(result) == j);
        EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
    }
}

{
    for (size_t i = 128; i <= 255; ++i) {

        // create JSON value with integer number
        json j = -1;
        j.get_ref<json::number_integer_t&>() = static_cast<json::number_integer_t>(i);

        // check type
        EXPECT_TRUE(j.is_number_integer());

        // create expected byte vector
        std::vector<uint8_t> expected;
        expected.push_back(static_cast<uint8_t>('U'));
        expected.push_back(static_cast<uint8_t>(i));

        // compare result + size
        const auto result = json::to_ubjson(j);
        EXPECT_TRUE(result == expected);
        EXPECT_TRUE(result.size() == 2);

        // check individual bytes
        EXPECT_TRUE(result[0] == 'U');
        EXPECT_TRUE(result[1] == i);

        // roundtrip
        EXPECT_TRUE(json::from_ubjson(result) == j);
        EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
    }
}

{
    for (size_t i = 256; i <= 32767; ++i) {

        // create JSON value with integer number
        json j = -1;
        j.get_ref<json::number_integer_t&>() = static_cast<json::number_integer_t>(i);

        // check type
        EXPECT_TRUE(j.is_number_integer());

        // create expected byte vector
        std::vector<uint8_t> expected;
        expected.push_back(static_cast<uint8_t>('I'));
        expected.push_back(static_cast<uint8_t>((i >> 8) & 0xff));
        expected.push_back(static_cast<uint8_t>(i & 0xff));

        // compare result + size
        const auto result = json::to_ubjson(j);
        EXPECT_TRUE(result == expected);
        EXPECT_TRUE(result.size() == 3);

        // check individual bytes
        EXPECT_TRUE(result[0] == 'I');
        uint16_t restored = static_cast<uint16_t>(static_cast<uint8_t>(result[1]) * 256 + static_cast<uint8_t>(result[2]));
        EXPECT_TRUE(restored == i);

        // roundtrip
        EXPECT_TRUE(json::from_ubjson(result) == j);
        EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
    }
}

{
    for (uint32_t i : { 65536u, 77777u, 1048576u }) {

        // create JSON value with integer number
        json j = -1;
        j.get_ref<json::number_integer_t&>() = static_cast<json::number_integer_t>(i);

        // check type
        EXPECT_TRUE(j.is_number_integer());

        // create expected byte vector
        std::vector<uint8_t> expected;
        expected.push_back('l');
        expected.push_back(static_cast<uint8_t>((i >> 24) & 0xff));
        expected.push_back(static_cast<uint8_t>((i >> 16) & 0xff));
        expected.push_back(static_cast<uint8_t>((i >> 8) & 0xff));
        expected.push_back(static_cast<uint8_t>(i & 0xff));

        // compare result + size
        const auto result = json::to_ubjson(j);
        EXPECT_TRUE(result == expected);
        EXPECT_TRUE(result.size() == 5);

        // check individual bytes
        EXPECT_TRUE(result[0] == 'l');
        uint32_t restored = (static_cast<uint32_t>(result[1]) << 030) + (static_cast<uint32_t>(result[2]) << 020) + (static_cast<uint32_t>(result[3]) << 010) + static_cast<uint32_t>(result[4]);
        EXPECT_TRUE(restored == i);

        // roundtrip
        EXPECT_TRUE(json::from_ubjson(result) == j);
        EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
    }
}

{
    std::vector<uint64_t> v = { 2147483648ul, 9223372036854775807ul };
    for (uint64_t i : v) {

        // create JSON value with integer number
        json j = -1;
        j.get_ref<json::number_integer_t&>() = static_cast<json::number_integer_t>(i);

        // check type
        EXPECT_TRUE(j.is_number_integer());

        // create expected byte vector
        std::vector<uint8_t> expected;
        expected.push_back('L');
        expected.push_back(static_cast<uint8_t>((i >> 070) & 0xff));
        expected.push_back(static_cast<uint8_t>((i >> 060) & 0xff));
        expected.push_back(static_cast<uint8_t>((i >> 050) & 0xff));
        expected.push_back(static_cast<uint8_t>((i >> 040) & 0xff));
        expected.push_back(static_cast<uint8_t>((i >> 030) & 0xff));
        expected.push_back(static_cast<uint8_t>((i >> 020) & 0xff));
        expected.push_back(static_cast<uint8_t>((i >> 010) & 0xff));
        expected.push_back(static_cast<uint8_t>(i & 0xff));

        // compare result + size
        const auto result = json::to_ubjson(j);
        EXPECT_TRUE(result == expected);
        EXPECT_TRUE(result.size() == 9);

        // check individual bytes
        EXPECT_TRUE(result[0] == 'L');
        uint64_t restored = (static_cast<uint64_t>(result[1]) << 070) + (static_cast<uint64_t>(result[2]) << 060) + (static_cast<uint64_t>(result[3]) << 050) + (static_cast<uint64_t>(result[4]) << 040) + (static_cast<uint64_t>(result[5]) << 030) + (static_cast<uint64_t>(result[6]) << 020) + (static_cast<uint64_t>(result[7]) << 010) + static_cast<uint64_t>(result[8]);
        EXPECT_TRUE(restored == i);

        // roundtrip
        EXPECT_TRUE(json::from_ubjson(result) == j);
        EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
    }
}
}

{ { for (size_t i = 0; i <= 127; ++i){

    // create JSON value with unsigned integer number
    json j = i;

// check type
EXPECT_TRUE(j.is_number_unsigned());

// create expected byte vector
std::vector<uint8_t> expected;
expected.push_back('i');
expected.push_back(static_cast<uint8_t>(i));

// compare result + size
const auto result = json::to_ubjson(j);
EXPECT_TRUE(result == expected);
EXPECT_TRUE(result.size() == 2);

// check individual bytes
EXPECT_TRUE(result[0] == 'i');
uint8_t restored = static_cast<uint8_t>(result[1]);
EXPECT_TRUE(restored == i);

// roundtrip
EXPECT_TRUE(json::from_ubjson(result) == j);
EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}
}

{
    for (size_t i = 128; i <= 255; ++i) {

        // create JSON value with unsigned integer number
        json j = i;

        // check type
        EXPECT_TRUE(j.is_number_unsigned());

        // create expected byte vector
        std::vector<uint8_t> expected;
        expected.push_back('U');
        expected.push_back(static_cast<uint8_t>(i));

        // compare result + size
        const auto result = json::to_ubjson(j);
        EXPECT_TRUE(result == expected);
        EXPECT_TRUE(result.size() == 2);

        // check individual bytes
        EXPECT_TRUE(result[0] == 'U');
        uint8_t restored = static_cast<uint8_t>(result[1]);
        EXPECT_TRUE(restored == i);

        // roundtrip
        EXPECT_TRUE(json::from_ubjson(result) == j);
        EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
    }
}

{
    for (size_t i = 256; i <= 32767; ++i) {

        // create JSON value with unsigned integer number
        json j = i;

        // check type
        EXPECT_TRUE(j.is_number_unsigned());

        // create expected byte vector
        std::vector<uint8_t> expected;
        expected.push_back('I');
        expected.push_back(static_cast<uint8_t>((i >> 8) & 0xff));
        expected.push_back(static_cast<uint8_t>(i & 0xff));

        // compare result + size
        const auto result = json::to_ubjson(j);
        EXPECT_TRUE(result == expected);
        EXPECT_TRUE(result.size() == 3);

        // check individual bytes
        EXPECT_TRUE(result[0] == 'I');
        uint16_t restored = static_cast<uint16_t>(static_cast<uint8_t>(result[1]) * 256 + static_cast<uint8_t>(result[2]));
        EXPECT_TRUE(restored == i);

        // roundtrip
        EXPECT_TRUE(json::from_ubjson(result) == j);
        EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
    }
}

{
    for (uint32_t i : { 65536u, 77777u, 1048576u }) {

        // create JSON value with unsigned integer number
        json j = i;

        // check type
        EXPECT_TRUE(j.is_number_unsigned());

        // create expected byte vector
        std::vector<uint8_t> expected;
        expected.push_back('l');
        expected.push_back(static_cast<uint8_t>((i >> 24) & 0xff));
        expected.push_back(static_cast<uint8_t>((i >> 16) & 0xff));
        expected.push_back(static_cast<uint8_t>((i >> 8) & 0xff));
        expected.push_back(static_cast<uint8_t>(i & 0xff));

        // compare result + size
        const auto result = json::to_ubjson(j);
        EXPECT_TRUE(result == expected);
        EXPECT_TRUE(result.size() == 5);

        // check individual bytes
        EXPECT_TRUE(result[0] == 'l');
        uint32_t restored = (static_cast<uint32_t>(result[1]) << 030) + (static_cast<uint32_t>(result[2]) << 020) + (static_cast<uint32_t>(result[3]) << 010) + static_cast<uint32_t>(result[4]);
        EXPECT_TRUE(restored == i);

        // roundtrip
        EXPECT_TRUE(json::from_ubjson(result) == j);
        EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
    }
}

{
    std::vector<uint64_t> v = { 2147483648ul, 9223372036854775807ul };
    for (uint64_t i : v) {

        // create JSON value with integer number
        json j = i;

        // check type
        EXPECT_TRUE(j.is_number_unsigned());

        // create expected byte vector
        std::vector<uint8_t> expected;
        expected.push_back('L');
        expected.push_back(static_cast<uint8_t>((i >> 070) & 0xff));
        expected.push_back(static_cast<uint8_t>((i >> 060) & 0xff));
        expected.push_back(static_cast<uint8_t>((i >> 050) & 0xff));
        expected.push_back(static_cast<uint8_t>((i >> 040) & 0xff));
        expected.push_back(static_cast<uint8_t>((i >> 030) & 0xff));
        expected.push_back(static_cast<uint8_t>((i >> 020) & 0xff));
        expected.push_back(static_cast<uint8_t>((i >> 010) & 0xff));
        expected.push_back(static_cast<uint8_t>(i & 0xff));

        // compare result + size
        const auto result = json::to_ubjson(j);
        EXPECT_TRUE(result == expected);
        EXPECT_TRUE(result.size() == 9);

        // check individual bytes
        EXPECT_TRUE(result[0] == 'L');
        uint64_t restored = (static_cast<uint64_t>(result[1]) << 070) + (static_cast<uint64_t>(result[2]) << 060) + (static_cast<uint64_t>(result[3]) << 050) + (static_cast<uint64_t>(result[4]) << 040) + (static_cast<uint64_t>(result[5]) << 030) + (static_cast<uint64_t>(result[6]) << 020) + (static_cast<uint64_t>(result[7]) << 010) + static_cast<uint64_t>(result[8]);
        EXPECT_TRUE(restored == i);

        // roundtrip
        EXPECT_TRUE(json::from_ubjson(result) == j);
        EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
    }
}
}

{
    {
        double v = 3.1415925;
        json j = v;
        std::vector<uint8_t> expected = { 'D', 0x40, 0x09, 0x21, 0xfb,
            0x3f, 0xa6, 0xde, 0xfc };
        const auto result = json::to_ubjson(j);
        EXPECT_TRUE(result == expected);

        // roundtrip
        EXPECT_TRUE(json::from_ubjson(result) == j);
        EXPECT_TRUE(json::from_ubjson(result) == v);
        EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
    }
}
}

{ { for (size_t N = 0; N <= 127; ++N){

    // create JSON value with string containing of N * 'x'
    const auto s = std::string(N, 'x');
json j = s;

// create expected byte vector
std::vector<uint8_t> expected;
expected.push_back('S');
expected.push_back('i');
expected.push_back(static_cast<uint8_t>(N));
for (size_t i = 0; i < N; ++i) {
    expected.push_back('x');
}

// compare result + size
const auto result = json::to_ubjson(j);
EXPECT_TRUE(result == expected);
EXPECT_TRUE(result.size() == N + 3);
// check that no null byte is appended
if (N > 0) {
    EXPECT_TRUE(result.back() != '\x00');
}

// roundtrip
EXPECT_TRUE(json::from_ubjson(result) == j);
EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}
}

{
    for (size_t N = 128; N <= 255; ++N) {

        // create JSON value with string containing of N * 'x'
        const auto s = std::string(N, 'x');
        json j = s;

        // create expected byte vector
        std::vector<uint8_t> expected;
        expected.push_back('S');
        expected.push_back('U');
        expected.push_back(static_cast<uint8_t>(N));
        for (size_t i = 0; i < N; ++i) {
            expected.push_back('x');
        }

        // compare result + size
        const auto result = json::to_ubjson(j);
        EXPECT_TRUE(result == expected);
        EXPECT_TRUE(result.size() == N + 3);
        // check that no null byte is appended
        EXPECT_TRUE(result.back() != '\x00');

        // roundtrip
        EXPECT_TRUE(json::from_ubjson(result) == j);
        EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
    }
}

{
    for (size_t N : { 256u, 999u, 1025u, 3333u, 2048u, 32767u }) {

        // create JSON value with string containing of N * 'x'
        const auto s = std::string(N, 'x');
        json j = s;

        // create expected byte vector (hack: create string first)
        std::vector<uint8_t> expected(N, 'x');
        // reverse order of commands, because we insert at begin()
        expected.insert(expected.begin(), static_cast<uint8_t>(N & 0xff));
        expected.insert(expected.begin(), static_cast<uint8_t>((N >> 8) & 0xff));
        expected.insert(expected.begin(), 'I');
        expected.insert(expected.begin(), 'S');

        // compare result + size
        const auto result = json::to_ubjson(j);
        EXPECT_TRUE(result == expected);
        EXPECT_TRUE(result.size() == N + 4);
        // check that no null byte is appended
        EXPECT_TRUE(result.back() != '\x00');

        // roundtrip
        EXPECT_TRUE(json::from_ubjson(result) == j);
        EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
    }
}

{
    for (size_t N : { 65536u, 77777u, 1048576u }) {

        // create JSON value with string containing of N * 'x'
        const auto s = std::string(N, 'x');
        json j = s;

        // create expected byte vector (hack: create string first)
        std::vector<uint8_t> expected(N, 'x');
        // reverse order of commands, because we insert at begin()
        expected.insert(expected.begin(), static_cast<uint8_t>(N & 0xff));
        expected.insert(expected.begin(), static_cast<uint8_t>((N >> 8) & 0xff));
        expected.insert(expected.begin(), static_cast<uint8_t>((N >> 16) & 0xff));
        expected.insert(expected.begin(), static_cast<uint8_t>((N >> 24) & 0xff));
        expected.insert(expected.begin(), 'l');
        expected.insert(expected.begin(), 'S');

        // compare result + size
        const auto result = json::to_ubjson(j);
        EXPECT_TRUE(result == expected);
        EXPECT_TRUE(result.size() == N + 6);
        // check that no null byte is appended
        EXPECT_TRUE(result.back() != '\x00');

        // roundtrip
        EXPECT_TRUE(json::from_ubjson(result) == j);
        EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
    }
}
}

{ { { json j = json::array();
std::vector<uint8_t> expected = { '[', ']' };
const auto result = json::to_ubjson(j);
EXPECT_TRUE(result == expected);

// roundtrip
EXPECT_TRUE(json::from_ubjson(result) == j);
EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}

{
    json j = json::array();
    std::vector<uint8_t> expected = { '[', '#', 'i', 0 };
    const auto result = json::to_ubjson(j, true);
    EXPECT_TRUE(result == expected);

    // roundtrip
    EXPECT_TRUE(json::from_ubjson(result) == j);
    EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}

{
    json j = json::array();
    std::vector<uint8_t> expected = { '[', '#', 'i', 0 };
    const auto result = json::to_ubjson(j, true, true);
    EXPECT_TRUE(result == expected);

    // roundtrip
    EXPECT_TRUE(json::from_ubjson(result) == j);
    EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}
}

{ { json j = { nullptr };
std::vector<uint8_t> expected = { '[', 'Z', ']' };
const auto result = json::to_ubjson(j);
EXPECT_TRUE(result == expected);

// roundtrip
EXPECT_TRUE(json::from_ubjson(result) == j);
EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}

{
    json j = { nullptr };
    std::vector<uint8_t> expected = { '[', '#', 'i', 1, 'Z' };
    const auto result = json::to_ubjson(j, true);
    EXPECT_TRUE(result == expected);

    // roundtrip
    EXPECT_TRUE(json::from_ubjson(result) == j);
    EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}

{
    json j = { nullptr };
    std::vector<uint8_t> expected = { '[', '$', 'Z', '#', 'i', 1 };
    const auto result = json::to_ubjson(j, true, true);
    EXPECT_TRUE(result == expected);

    // roundtrip
    EXPECT_TRUE(json::from_ubjson(result) == j);
    EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}
}

{ { json j = json::parse("[1,2,3,4,5]");
std::vector<uint8_t> expected = { '[', 'i', 1, 'i', 2, 'i',
    3, 'i', 4, 'i', 5, ']' };
const auto result = json::to_ubjson(j);
EXPECT_TRUE(result == expected);

// roundtrip
EXPECT_TRUE(json::from_ubjson(result) == j);
EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}

{
    json j = json::parse("[1,2,3,4,5]");
    std::vector<uint8_t> expected = { '[', '#', 'i', 5, 'i', 1, 'i',
        2, 'i', 3, 'i', 4, 'i', 5 };
    const auto result = json::to_ubjson(j, true);
    EXPECT_TRUE(result == expected);

    // roundtrip
    EXPECT_TRUE(json::from_ubjson(result) == j);
    EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}

{
    json j = json::parse("[1,2,3,4,5]");
    std::vector<uint8_t> expected = { '[', '$', 'i', '#', 'i', 5, 1, 2, 3, 4, 5 };
    const auto result = json::to_ubjson(j, true, true);
    EXPECT_TRUE(result == expected);

    // roundtrip
    EXPECT_TRUE(json::from_ubjson(result) == j);
    EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}
}

{ { json j = json::parse("[[[[]]]]");
std::vector<uint8_t> expected = { '[', '[', '[', '[', ']', ']', ']', ']' };
const auto result = json::to_ubjson(j);
EXPECT_TRUE(result == expected);

// roundtrip
EXPECT_TRUE(json::from_ubjson(result) == j);
EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}

{
    json j = json::parse("[[[[]]]]");
    std::vector<uint8_t> expected = { '[', '#', 'i', 1, '[', '#', 'i', 1,
        '[', '#', 'i', 1, '[', '#', 'i', 0 };
    const auto result = json::to_ubjson(j, true);
    EXPECT_TRUE(result == expected);

    // roundtrip
    EXPECT_TRUE(json::from_ubjson(result) == j);
    EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}

{
    json j = json::parse("[[[[]]]]");
    std::vector<uint8_t> expected = { '[', '$', '[', '#', 'i', 1, '$',
        '[', '#', 'i', 1, '$', '[', '#',
        'i', 1, '#', 'i', 0 };
    const auto result = json::to_ubjson(j, true, true);
    EXPECT_TRUE(result == expected);

    // roundtrip
    EXPECT_TRUE(json::from_ubjson(result) == j);
    EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}
}

{ { json j(257, nullptr);
std::vector<uint8_t> expected(j.size() + 2, 'Z'); // all null
expected[0] = '['; // opening array
expected[258] = ']'; // closing array
const auto result = json::to_ubjson(j);
EXPECT_TRUE(result == expected);

// roundtrip
EXPECT_TRUE(json::from_ubjson(result) == j);
EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}

{
    json j(257, nullptr);
    std::vector<uint8_t> expected(j.size() + 5, 'Z'); // all null
    expected[0] = '['; // opening array
    expected[1] = '#'; // array size
    expected[2] = 'I'; // int16
    expected[3] = 0x01; // 0x0101, first byte
    expected[4] = 0x01; // 0x0101, second byte
    const auto result = json::to_ubjson(j, true);
    EXPECT_TRUE(result == expected);

    // roundtrip
    EXPECT_TRUE(json::from_ubjson(result) == j);
    EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}

{
    json j(257, nullptr);
    std::vector<uint8_t> expected = { '[', '$', 'Z', '#', 'I', 0x01, 0x01 };
    const auto result = json::to_ubjson(j, true, true);
    EXPECT_TRUE(result == expected);

    // roundtrip
    EXPECT_TRUE(json::from_ubjson(result) == j);
    EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}
}

{
    {
        json j(65793, nullptr);
        std::vector<uint8_t> expected(j.size() + 2, 'Z'); // all null
        expected[0] = '['; // opening array
        expected[65794] = ']'; // closing array
        const auto result = json::to_ubjson(j);
        EXPECT_TRUE(result == expected);

        // roundtrip
        EXPECT_TRUE(json::from_ubjson(result) == j);
        EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
    }

    {
        json j(65793, nullptr);
        std::vector<uint8_t> expected(j.size() + 7, 'Z'); // all null
        expected[0] = '['; // opening array
        expected[1] = '#'; // array size
        expected[2] = 'l'; // int32
        expected[3] = 0x00; // 0x00010101, first byte
        expected[4] = 0x01; // 0x00010101, second byte
        expected[5] = 0x01; // 0x00010101, third byte
        expected[6] = 0x01; // 0x00010101, fourth byte
        const auto result = json::to_ubjson(j, true);
        EXPECT_TRUE(result == expected);

        // roundtrip
        EXPECT_TRUE(json::from_ubjson(result) == j);
        EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
    }

    {
        json j(65793, nullptr);
        std::vector<uint8_t> expected = { '[', '$', 'Z', '#', 'l',
            0x00, 0x01, 0x01, 0x01 };
        const auto result = json::to_ubjson(j, true, true);
        EXPECT_TRUE(result == expected);

        // roundtrip
        EXPECT_TRUE(json::from_ubjson(result) == j);
        EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
    }
}
}

{
    { { json j = json::object();
    std::vector<uint8_t> expected = { '{', '}' };
    const auto result = json::to_ubjson(j);
    EXPECT_TRUE(result == expected);

    // roundtrip
    EXPECT_TRUE(json::from_ubjson(result) == j);
    EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}

{
    json j = json::object();
    std::vector<uint8_t> expected = { '{', '#', 'i', 0 };
    const auto result = json::to_ubjson(j, true);
    EXPECT_TRUE(result == expected);

    // roundtrip
    EXPECT_TRUE(json::from_ubjson(result) == j);
    EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}

{
    json j = json::object();
    std::vector<uint8_t> expected = { '{', '#', 'i', 0 };
    const auto result = json::to_ubjson(j, true, true);
    EXPECT_TRUE(result == expected);

    // roundtrip
    EXPECT_TRUE(json::from_ubjson(result) == j);
    EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}
}

{ { json j = { { "", nullptr } };
std::vector<uint8_t> expected = { '{', 'i', 0, 'Z', '}' };
const auto result = json::to_ubjson(j);
EXPECT_TRUE(result == expected);

// roundtrip
EXPECT_TRUE(json::from_ubjson(result) == j);
EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}

{
    json j = { { "", nullptr } };
    std::vector<uint8_t> expected = { '{', '#', 'i', 1, 'i', 0, 'Z' };
    const auto result = json::to_ubjson(j, true);
    EXPECT_TRUE(result == expected);

    // roundtrip
    EXPECT_TRUE(json::from_ubjson(result) == j);
    EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}

{
    json j = { { "", nullptr } };
    std::vector<uint8_t> expected = { '{', '$', 'Z', '#', 'i', 1, 'i', 0 };
    const auto result = json::to_ubjson(j, true, true);
    EXPECT_TRUE(result == expected);

    // roundtrip
    EXPECT_TRUE(json::from_ubjson(result) == j);
    EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
}
}

{
    {
        json j = json::parse("{\"a\": {\"b\": {\"c\": {}}}}");
        std::vector<uint8_t> expected = { '{', 'i', 1, 'a', '{', 'i',
            1, 'b', '{', 'i', 1, 'c',
            '{', '}', '}', '}', '}' };
        const auto result = json::to_ubjson(j);
        EXPECT_TRUE(result == expected);

        // roundtrip
        EXPECT_TRUE(json::from_ubjson(result) == j);
        EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
    }

    {
        json j = json::parse("{\"a\": {\"b\": {\"c\": {}}}}");
        std::vector<uint8_t> expected = {
            '{', '#', 'i', 1, 'i', 1, 'a', '{', '#', 'i', 1, 'i', 1,
            'b', '{', '#', 'i', 1, 'i', 1, 'c', '{', '#', 'i', 0
        };
        const auto result = json::to_ubjson(j, true);
        EXPECT_TRUE(result == expected);

        // roundtrip
        EXPECT_TRUE(json::from_ubjson(result) == j);
        EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
    }

    {
        json j = json::parse("{\"a\": {\"b\": {\"c\": {}}}}");
        std::vector<uint8_t> expected = {
            '{', '$', '{', '#', 'i', 1, 'i', 1, 'a', '$', '{', '#', 'i', 1,
            'i', 1, 'b', '$', '{', '#', 'i', 1, 'i', 1, 'c', '#', 'i', 0
        };
        const auto result = json::to_ubjson(j, true, true);
        EXPECT_TRUE(result == expected);

        // roundtrip
        EXPECT_TRUE(json::from_ubjson(result) == j);
        EXPECT_TRUE(json::from_ubjson(result, true, false) == j);
    }
}
}
}

{ { std::vector<uint8_t> vec = { 'Z', 'Z' };
{
    const auto result = json::from_ubjson(vec, false);
    EXPECT_TRUE(result == json());
}

{
    HELPER_THROW(json::from_ubjson(vec), json::parse_error, "[json.exception.parse_error."
                                                            "110] parse error at 2: "
                                                            "expected end of input");
}
}

{
    // larger than max int64
    json j = 9223372036854775808llu;
    HELPER_THROW(json::to_ubjson(j),
        json::out_of_range, "[json.exception.out_of_range.407] "
                            "number overflow serializing "
                            "9223372036854775808");
}

{
    {
        std::vector<uint8_t> v_ubjson = { '[', '$', 'Z', '#', 'L', 0x78, 0x28,
            0x00, 0x68, 0x28, 0x69, 0x69, 0x17 };
        EXPECT_THROW(json::from_ubjson(v_ubjson), json::out_of_range);

        json j;
        nlohmann::detail::json_sax_dom_callback_parser<json> scp(
            j, [](int, json::parse_event_t, const json&) { return true; });
        EXPECT_THROW(json::sax_parse(v_ubjson, &scp, json::input_format_t::ubjson),
            json::out_of_range);
    }

    {
        std::vector<uint8_t> v_ubjson = { '{', '$', 'Z', '#', 'L', 0x78, 0x28,
            0x00, 0x68, 0x28, 0x69, 0x69, 0x17 };
        EXPECT_THROW(json::from_ubjson(v_ubjson), json::out_of_range);

        json j;
        nlohmann::detail::json_sax_dom_callback_parser<json> scp(
            j, [](int, json::parse_event_t, const json&) { return true; });
        EXPECT_THROW(json::sax_parse(v_ubjson, &scp, json::input_format_t::ubjson),
            json::out_of_range);
    }
}
}

{ { std::vector<uint8_t> v = { '[', 'T', 'F', ']' };
SaxCountdown scp(0);
EXPECT_TRUE(not json::sax_parse(v, &scp, json::input_format_t::ubjson));
}

{
    std::vector<uint8_t> v = { '{', 'i', 3, 'f', 'o', 'o', 'F', '}' };
    SaxCountdown scp(0);
    EXPECT_TRUE(not json::sax_parse(v, &scp, json::input_format_t::ubjson));
}

{
    std::vector<uint8_t> v = { '{', 'i', 3, 'f', 'o', 'o', 'F', '}' };
    SaxCountdown scp(1);
    EXPECT_TRUE(not json::sax_parse(v, &scp, json::input_format_t::ubjson));
}

{
    std::vector<uint8_t> v = { '[', '#', 'i', '2', 'T', 'F' };
    SaxCountdown scp(0);
    EXPECT_TRUE(not json::sax_parse(v, &scp, json::input_format_t::ubjson));
}

{
    std::vector<uint8_t> v = { '{', '#', 'i', '1', 3, 'f', 'o', 'o', 'F' };
    SaxCountdown scp(0);
    EXPECT_TRUE(not json::sax_parse(v, &scp, json::input_format_t::ubjson));
}

{
    std::vector<uint8_t> v = { '{', 'i', 3, 'f', 'o', 'o', 'F', '}' };
    SaxCountdown scp(1);
    EXPECT_TRUE(not json::sax_parse(v, &scp, json::input_format_t::ubjson));
}
}

{ { // create a single-character string for all number types
    std::vector<uint8_t> s_i = { 'S', 'i', 1, 'a' };
std::vector<uint8_t> s_U = { 'S', 'U', 1, 'a' };
std::vector<uint8_t> s_I = { 'S', 'I', 0, 1, 'a' };
std::vector<uint8_t> s_l = { 'S', 'l', 0, 0, 0, 1, 'a' };
std::vector<uint8_t> s_L = { 'S', 'L', 0, 0, 0, 0, 0, 0, 0, 1, 'a' };

// check if string is parsed correctly to "a"
EXPECT_TRUE(json::from_ubjson(s_i) == "a");
EXPECT_TRUE(json::from_ubjson(s_U) == "a");
EXPECT_TRUE(json::from_ubjson(s_I) == "a");
EXPECT_TRUE(json::from_ubjson(s_l) == "a");
EXPECT_TRUE(json::from_ubjson(s_L) == "a");

// roundtrip: output should be optimized
EXPECT_TRUE(json::to_ubjson(json::from_ubjson(s_i)) == s_i);
EXPECT_TRUE(json::to_ubjson(json::from_ubjson(s_U)) == s_i);
EXPECT_TRUE(json::to_ubjson(json::from_ubjson(s_I)) == s_i);
EXPECT_TRUE(json::to_ubjson(json::from_ubjson(s_l)) == s_i);
EXPECT_TRUE(json::to_ubjson(json::from_ubjson(s_L)) == s_i);
}

{ { // float32
    std::vector<uint8_t> v_d = { 'd', 0x40, 0x49, 0x0f, 0xd0 };
EXPECT_TRUE(json::from_ubjson(v_d) == 3.14159f);

// float64
std::vector<uint8_t> v_D = { 'D', 0x40, 0x09, 0x21, 0xf9,
    0xf0, 0x1b, 0x86, 0x6e };
EXPECT_TRUE(json::from_ubjson(v_D) == 3.14159);

// float32 is serialized as float64 as the library does not support
// float32
EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_d)) == json::to_ubjson(3.14159f));
}
}

{
    {
        // create vector with two elements of the same type
        std::vector<uint8_t> v_TU = { '[', '#', 'U', 2, 'T', 'T' };
        std::vector<uint8_t> v_T = { '[', '#', 'i', 2, 'T', 'T' };
        std::vector<uint8_t> v_F = { '[', '#', 'i', 2, 'F', 'F' };
        std::vector<uint8_t> v_Z = { '[', '#', 'i', 2, 'Z', 'Z' };
        std::vector<uint8_t> v_i = { '[', '#', 'i', 2, 'i', 0x7F, 'i', 0x7F };
        std::vector<uint8_t> v_U = { '[', '#', 'i', 2, 'U', 0xFF, 'U', 0xFF };
        std::vector<uint8_t> v_I = { '[', '#', 'i', 2, 'I',
            0x7F, 0xFF, 'I', 0x7F, 0xFF };
        std::vector<uint8_t> v_l = { '[', '#', 'i', 2, 'l', 0x7F, 0xFF,
            0xFF, 0xFF, 'l', 0x7F, 0xFF, 0xFF, 0xFF };
        std::vector<uint8_t> v_L = { '[', '#', 'i', 2, 'L', 0x7F, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 'L', 0x7F, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
        std::vector<uint8_t> v_D = { '[', '#', 'i', 2, 'D', 0x40, 0x09, 0x21,
            0xfb, 0x4d, 0x12, 0xd8, 0x4a, 'D', 0x40, 0x09,
            0x21, 0xfb, 0x4d, 0x12, 0xd8, 0x4a };
        std::vector<uint8_t> v_S = { '[', '#', 'i', 2, 'S', 'i',
            1, 'a', 'S', 'i', 1, 'a' };
        std::vector<uint8_t> v_C = { '[', '#', 'i', 2, 'C', 'a', 'C', 'a' };

        // check if vector is parsed correctly
        EXPECT_TRUE(json::from_ubjson(v_TU) == json({ true, true }));
        EXPECT_TRUE(json::from_ubjson(v_T) == json({ true, true }));
        EXPECT_TRUE(json::from_ubjson(v_F) == json({ false, false }));
        EXPECT_TRUE(json::from_ubjson(v_Z) == json({ nullptr, nullptr }));
        EXPECT_TRUE(json::from_ubjson(v_i) == json({ 127, 127 }));
        EXPECT_TRUE(json::from_ubjson(v_U) == json({ 255, 255 }));
        EXPECT_TRUE(json::from_ubjson(v_I) == json({ 32767, 32767 }));
        EXPECT_TRUE(json::from_ubjson(v_l) == json({ 2147483647, 2147483647 }));
        EXPECT_TRUE(json::from_ubjson(v_L) == json({ 9223372036854775807, 9223372036854775807 }));
        EXPECT_TRUE(json::from_ubjson(v_D) == json({ 3.1415926, 3.1415926 }));
        EXPECT_TRUE(json::from_ubjson(v_S) == json({ "a", "a" }));
        EXPECT_TRUE(json::from_ubjson(v_C) == json({ "a", "a" }));

        // roundtrip: output should be optimized
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_T), true) == v_T);
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_F), true) == v_F);
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_Z), true) == v_Z);
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_i), true) == v_i);
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_U), true) == v_U);
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_I), true) == v_I);
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_l), true) == v_l);
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_L), true) == v_L);
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_D), true) == v_D);
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_S), true) == v_S);
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_C), true) == v_S); // char is serialized to string
    }

    {
        // create vector with two elements of the same type
        std::vector<uint8_t> v_N = { '[', '$', 'N', '#', 'i', 2 };
        std::vector<uint8_t> v_T = { '[', '$', 'T', '#', 'i', 2 };
        std::vector<uint8_t> v_F = { '[', '$', 'F', '#', 'i', 2 };
        std::vector<uint8_t> v_Z = { '[', '$', 'Z', '#', 'i', 2 };
        std::vector<uint8_t> v_i = { '[', '$', 'i', '#', 'i', 2, 0x7F, 0x7F };
        std::vector<uint8_t> v_U = { '[', '$', 'U', '#', 'i', 2, 0xFF, 0xFF };
        std::vector<uint8_t> v_I = { '[', '$', 'I', '#', 'i',
            2, 0x7F, 0xFF, 0x7F, 0xFF };
        std::vector<uint8_t> v_l = { '[', '$', 'l', '#', 'i', 2, 0x7F,
            0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF };
        std::vector<uint8_t> v_L = { '[', '$', 'L', '#', 'i', 2, 0x7F, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
        std::vector<uint8_t> v_D = { '[', '$', 'D', '#', 'i', 2, 0x40, 0x09,
            0x21, 0xfb, 0x4d, 0x12, 0xd8, 0x4a, 0x40, 0x09,
            0x21, 0xfb, 0x4d, 0x12, 0xd8, 0x4a };
        std::vector<uint8_t> v_S = { '[', '$', 'S', '#', 'i', 2,
            'i', 1, 'a', 'i', 1, 'a' };
        std::vector<uint8_t> v_C = { '[', '$', 'C', '#', 'i', 2, 'a', 'a' };

        // check if vector is parsed correctly
        EXPECT_TRUE(json::from_ubjson(v_N) == json::array());
        EXPECT_TRUE(json::from_ubjson(v_T) == json({ true, true }));
        EXPECT_TRUE(json::from_ubjson(v_F) == json({ false, false }));
        EXPECT_TRUE(json::from_ubjson(v_Z) == json({ nullptr, nullptr }));
        EXPECT_TRUE(json::from_ubjson(v_i) == json({ 127, 127 }));
        EXPECT_TRUE(json::from_ubjson(v_U) == json({ 255, 255 }));
        EXPECT_TRUE(json::from_ubjson(v_I) == json({ 32767, 32767 }));
        EXPECT_TRUE(json::from_ubjson(v_l) == json({ 2147483647, 2147483647 }));
        EXPECT_TRUE(json::from_ubjson(v_L) == json({ 9223372036854775807, 9223372036854775807 }));
        EXPECT_TRUE(json::from_ubjson(v_D) == json({ 3.1415926, 3.1415926 }));
        EXPECT_TRUE(json::from_ubjson(v_S) == json({ "a", "a" }));
        EXPECT_TRUE(json::from_ubjson(v_C) == json({ "a", "a" }));

        // roundtrip: output should be optimized
        std::vector<uint8_t> v_empty = { '[', '#', 'i', 0 };
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_N), true, true) == v_empty);
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_T), true, true) == v_T);
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_F), true, true) == v_F);
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_Z), true, true) == v_Z);
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_i), true, true) == v_i);
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_U), true, true) == v_U);
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_I), true, true) == v_I);
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_l), true, true) == v_l);
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_L), true, true) == v_L);
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_D), true, true) == v_D);
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_S), true, true) == v_S);
        EXPECT_TRUE(json::to_ubjson(json::from_ubjson(v_C), true, true) == v_S); // char is serialized to string
    }
}
}

{
    HELPER_THROW(json::from_ubjson(std::vector<uint8_t>()), json::parse_error,
        "[json.exception.parse_error.110] parse error at 1: "
        "unexpected end of input");
}

{ { std::vector<uint8_t> v = { 'C' };
HELPER_THROW(json::from_ubjson(v), json::parse_error, "[json.exception.parse_error."
                                                      "110] parse error at 2: "
                                                      "unexpected end of input");
}

{
    std::vector<uint8_t> v = { 'C', 130 };
    HELPER_THROW(json::from_ubjson(v), json::parse_error, "[json.exception.parse_error."
                                                          "113] parse error at 2: byte "
                                                          "after 'C' must be in range "
                                                          "0x00..0x7F; last byte: 0x82");
}
}

{ { std::vector<uint8_t> v = { 'S' };
HELPER_THROW(json::from_ubjson(v), json::parse_error, "[json.exception.parse_error."
                                                      "110] parse error at 2: "
                                                      "unexpected end of input");
}

{
    std::vector<uint8_t> v = { 'S', '1', 'a' };
    HELPER_THROW(json::from_ubjson(v), json::parse_error,
        "[json.exception.parse_error.113] parse error at 2: "
        "expected a UBJSON string; last byte: 0x31");
}
}

{ { std::vector<uint8_t> v = { '[', '$', 'i', 2 };
HELPER_THROW(json::from_ubjson(v), json::parse_error,
    "[json.exception.parse_error.112] parse error at 4: "
    "expected '#' after UBJSON type information; last "
    "byte: 0x02");
}
}

{
    std::vector<uint8_t> vS = { 'S' };
    HELPER_THROW(json::from_ubjson(vS), json::parse_error, "[json.exception.parse_error."
                                                           "110] parse error at 2: "
                                                           "unexpected end of input");
    EXPECT_TRUE(json::from_ubjson(vS, true, false).is_discarded());

    std::vector<uint8_t> v = { 'S', 'i', '2', 'a' };
    HELPER_THROW(json::from_ubjson(v), json::parse_error, "[json.exception.parse_error.110]"
                                                          " parse error at 5: unexpected "
                                                          "end of input");
    EXPECT_TRUE(json::from_ubjson(v, true, false).is_discarded());

    std::vector<uint8_t> vC = { 'C' };
    HELPER_THROW(json::from_ubjson(vC), json::parse_error, "[json.exception.parse_error."
                                                           "110] parse error at 2: "
                                                           "unexpected end of input");
    EXPECT_TRUE(json::from_ubjson(vC, true, false).is_discarded());
}

{
    std::vector<uint8_t> vU = { '[', '#', 'U' };
    HELPER_THROW(json::from_ubjson(vU), json::parse_error, "[json.exception.parse_error."
                                                           "110] parse error at 4: "
                                                           "unexpected end of input");
    EXPECT_TRUE(json::from_ubjson(vU, true, false).is_discarded());

    std::vector<uint8_t> vi = { '[', '#', 'i' };
    HELPER_THROW(json::from_ubjson(vi), json::parse_error, "[json.exception.parse_error."
                                                           "110] parse error at 4: "
                                                           "unexpected end of input");
    EXPECT_TRUE(json::from_ubjson(vi, true, false).is_discarded());

    std::vector<uint8_t> vI = { '[', '#', 'I' };
    HELPER_THROW(json::from_ubjson(vI), json::parse_error, "[json.exception.parse_error."
                                                           "110] parse error at 4: "
                                                           "unexpected end of input");
    EXPECT_TRUE(json::from_ubjson(vI, true, false).is_discarded());

    std::vector<uint8_t> vl = { '[', '#', 'l' };
    HELPER_THROW(json::from_ubjson(vl), json::parse_error, "[json.exception.parse_error."
                                                           "110] parse error at 4: "
                                                           "unexpected end of input");
    EXPECT_TRUE(json::from_ubjson(vl, true, false).is_discarded());

    std::vector<uint8_t> vL = { '[', '#', 'L' };
    HELPER_THROW(json::from_ubjson(vL), json::parse_error, "[json.exception.parse_error."
                                                           "110] parse error at 4: "
                                                           "unexpected end of input");
    EXPECT_TRUE(json::from_ubjson(vL, true, false).is_discarded());

    std::vector<uint8_t> v0 = { '[', '#', 'T', ']' };
    HELPER_THROW(json::from_ubjson(v0), json::parse_error, "[json.exception.parse_error."
                                                           "113] parse error at 3: byte "
                                                           "after '#' must denote a number "
                                                           "type; last byte: 0x54");
    EXPECT_TRUE(json::from_ubjson(v0, true, false).is_discarded());
}

{
    std::vector<uint8_t> v0 = { '[', '$' };
    HELPER_THROW(json::from_ubjson(v0), json::parse_error, "[json.exception.parse_error."
                                                           "110] parse error at 3: "
                                                           "unexpected end of input");
    EXPECT_TRUE(json::from_ubjson(v0, true, false).is_discarded());

    std::vector<uint8_t> vi = { '[', '$', '#' };
    HELPER_THROW(json::from_ubjson(vi), json::parse_error, "[json.exception.parse_error."
                                                           "110] parse error at 4: "
                                                           "unexpected end of input");
    EXPECT_TRUE(json::from_ubjson(vi, true, false).is_discarded());

    std::vector<uint8_t> vT = { '[', '$', 'T' };
    HELPER_THROW(json::from_ubjson(vT), json::parse_error, "[json.exception.parse_error."
                                                           "110] parse error at 4: "
                                                           "unexpected end of input");
    EXPECT_TRUE(json::from_ubjson(vT, true, false).is_discarded());
}

{
    std::vector<uint8_t> vST = { '[', '$', 'i', '#', 'i', 2, 1 };
    HELPER_THROW(json::from_ubjson(vST), json::parse_error, "[json.exception.parse_error."
                                                            "110] parse error at 8: "
                                                            "unexpected end of input");
    EXPECT_TRUE(json::from_ubjson(vST, true, false).is_discarded());

    std::vector<uint8_t> vS = { '[', '#', 'i', 2, 'i', 1 };
    HELPER_THROW(json::from_ubjson(vS), json::parse_error, "[json.exception.parse_error."
                                                           "110] parse error at 7: "
                                                           "unexpected end of input");
    EXPECT_TRUE(json::from_ubjson(vS, true, false).is_discarded());

    std::vector<uint8_t> v = { '[', 'i', 2, 'i', 1 };
    HELPER_THROW(json::from_ubjson(v), json::parse_error, "[json.exception.parse_error.110]"
                                                          " parse error at 6: unexpected "
                                                          "end of input");
    EXPECT_TRUE(json::from_ubjson(v, true, false).is_discarded());
}

{
    std::vector<uint8_t> vST = { '{', '$', 'i', '#', 'i', 2, 'i', 1, 'a', 1 };
    HELPER_THROW(json::from_ubjson(vST), json::parse_error, "[json.exception.parse_error."
                                                            "110] parse error at 11: "
                                                            "unexpected end of input");
    EXPECT_TRUE(json::from_ubjson(vST, true, false).is_discarded());

    std::vector<uint8_t> vT = { '{', '$', 'i', 'i', 1, 'a', 1 };
    HELPER_THROW(json::from_ubjson(vT), json::parse_error, "[json.exception.parse_error."
                                                           "112] parse error at 4: "
                                                           "expected '#' after UBJSON type "
                                                           "information; last byte: 0x69");
    EXPECT_TRUE(json::from_ubjson(vT, true, false).is_discarded());

    std::vector<uint8_t> vS = { '{', '#', 'i', 2, 'i', 1, 'a', 'i', 1 };
    HELPER_THROW(json::from_ubjson(vS), json::parse_error, "[json.exception.parse_error."
                                                           "110] parse error at 10: "
                                                           "unexpected end of input");
    EXPECT_TRUE(json::from_ubjson(vS, true, false).is_discarded());

    std::vector<uint8_t> v = { '{', 'i', 1, 'a', 'i', 1 };
    HELPER_THROW(json::from_ubjson(v), json::parse_error, "[json.exception.parse_error.110]"
                                                          " parse error at 7: unexpected "
                                                          "end of input");
    EXPECT_TRUE(json::from_ubjson(v, true, false).is_discarded());

    std::vector<uint8_t> v2 = { '{', 'i', 1, 'a', 'i', 1, 'i' };
    HELPER_THROW(json::from_ubjson(v2), json::parse_error, "[json.exception.parse_error."
                                                           "110] parse error at 8: "
                                                           "unexpected end of input");
    EXPECT_TRUE(json::from_ubjson(v2, true, false).is_discarded());

    std::vector<uint8_t> v3 = { '{', 'i', 1, 'a' };
    HELPER_THROW(json::from_ubjson(v3), json::parse_error, "[json.exception.parse_error."
                                                           "110] parse error at 5: "
                                                           "unexpected end of input");
    EXPECT_TRUE(json::from_ubjson(v3, true, false).is_discarded());

    std::vector<uint8_t> vST1 = { '{', '$', 'd', '#', 'i', 2, 'i', 1, 'a' };
    HELPER_THROW(json::from_ubjson(vST1), json::parse_error, "[json.exception.parse_error."
                                                             "110] parse error at 10: "
                                                             "unexpected end of input");
    EXPECT_TRUE(json::from_ubjson(vST1, true, false).is_discarded());

    std::vector<uint8_t> vST2 = { '{', '#', 'i', 2, 'i', 1, 'a' };
    HELPER_THROW(json::from_ubjson(vST2), json::parse_error, "[json.exception.parse_error."
                                                             "110] parse error at 8: "
                                                             "unexpected end of input");
    EXPECT_TRUE(json::from_ubjson(vST2, true, false).is_discarded());
}

{
    { { json j = { 1, -1 };
    std::vector<uint8_t> expected = { '[', '$', 'i', '#', 'i', 2, 1, 0xff };
    EXPECT_TRUE(json::to_ubjson(j, true, true) == expected);
}

{
    json j = { 200, 201 };
    std::vector<uint8_t> expected = { '[', '$', 'U', '#', 'i', 2, 0xC8, 0xC9 };
    EXPECT_TRUE(json::to_ubjson(j, true, true) == expected);
}

{
    json j = { 30000, -30000 };
    std::vector<uint8_t> expected = { '[', '$', 'I', '#', 'i',
        2, 0x75, 0x30, 0x8a, 0xd0 };
    EXPECT_TRUE(json::to_ubjson(j, true, true) == expected);
}

{
    json j = { 70000, -70000 };
    std::vector<uint8_t> expected = { '[', '$', 'l', '#', 'i', 2, 0x00,
        0x01, 0x11, 0x70, 0xFF, 0xFE, 0xEE, 0x90 };
    EXPECT_TRUE(json::to_ubjson(j, true, true) == expected);
}

{
    json j = { 5000000000, -5000000000 };
    std::vector<uint8_t> expected = {
        '[', '$', 'L', '#', 'i', 2, 0x00, 0x00, 0x00, 0x01, 0x2A,
        0x05, 0xF2, 0x00, 0xFF, 0xFF, 0xFF, 0xFE, 0xD5, 0xFA, 0x0E, 0x00
    };
    EXPECT_TRUE(json::to_ubjson(j, true, true) == expected);
}
}

{ { json j = { 1u, 2u };
std::vector<uint8_t> expected = { '[', '$', 'i', '#', 'i', 2, 1, 2 };
std::vector<uint8_t> expected_size = { '[', '#', 'i', 2, 'i', 1, 'i', 2 };
EXPECT_TRUE(json::to_ubjson(j, true, true) == expected);
EXPECT_TRUE(json::to_ubjson(j, true) == expected_size);
}

{
    json j = { 200u, 201u };
    std::vector<uint8_t> expected = { '[', '$', 'U', '#', 'i', 2, 0xC8, 0xC9 };
    std::vector<uint8_t> expected_size = { '[', '#', 'i', 2, 'U', 0xC8, 'U', 0xC9 };
    EXPECT_TRUE(json::to_ubjson(j, true, true) == expected);
    EXPECT_TRUE(json::to_ubjson(j, true) == expected_size);
}

{
    json j = { 30000u, 30001u };
    std::vector<uint8_t> expected = { '[', '$', 'I', '#', 'i',
        2, 0x75, 0x30, 0x75, 0x31 };
    std::vector<uint8_t> expected_size = { '[', '#', 'i', 2, 'I',
        0x75, 0x30, 'I', 0x75, 0x31 };
    EXPECT_TRUE(json::to_ubjson(j, true, true) == expected);
    EXPECT_TRUE(json::to_ubjson(j, true) == expected_size);
}

{
    json j = { 70000u, 70001u };
    std::vector<uint8_t> expected = { '[', '$', 'l', '#', 'i', 2, 0x00,
        0x01, 0x11, 0x70, 0x00, 0x01, 0x11, 0x71 };
    std::vector<uint8_t> expected_size = { '[', '#', 'i', 2, 'l',
        0x00, 0x01, 0x11, 0x70, 'l',
        0x00, 0x01, 0x11, 0x71 };
    EXPECT_TRUE(json::to_ubjson(j, true, true) == expected);
    EXPECT_TRUE(json::to_ubjson(j, true) == expected_size);
}

{
    json j = { 5000000000u, 5000000001u };
    std::vector<uint8_t> expected = {
        '[', '$', 'L', '#', 'i', 2, 0x00, 0x00, 0x00, 0x01, 0x2A,
        0x05, 0xF2, 0x00, 0x00, 0x00, 0x00, 0x01, 0x2A, 0x05, 0xF2, 0x01
    };
    std::vector<uint8_t> expected_size = {
        '[', '#', 'i', 2, 'L', 0x00, 0x00, 0x00, 0x01, 0x2A, 0x05,
        0xF2, 0x00, 'L', 0x00, 0x00, 0x00, 0x01, 0x2A, 0x05, 0xF2, 0x01
    };
    EXPECT_TRUE(json::to_ubjson(j, true, true) == expected);
    EXPECT_TRUE(json::to_ubjson(j, true) == expected_size);
}
}

{
    json j = { json::value_t::discarded, json::value_t::discarded };
    std::vector<uint8_t> expected = { '[', '$', 'N', '#', 'i', 2 };
    EXPECT_TRUE(json::to_ubjson(j, true, true) == expected);
}
}
}

TEST(UBJSON, Universal_Binary_JSON_Specification_Examples_1)
{
    {
        json j = { { "passcode", nullptr } };
        std::vector<uint8_t> v = { '{', 'i', 8, 'p', 'a', 's', 's',
            'c', 'o', 'd', 'e', 'Z', '}' };
        EXPECT_TRUE(json::to_ubjson(j) == v);
        EXPECT_TRUE(json::from_ubjson(v) == j);
    }

    {
        json j = { "foo", "bar", "baz" };
        std::vector<uint8_t> v = { '[', 'S', 'i', 3, 'f', 'o', 'o', 'S', 'i', 3,
            'b', 'a', 'r', 'S', 'i', 3, 'b', 'a', 'z', ']' };
        std::vector<uint8_t> v2 = { '[', 'S', 'i', 3, 'f', 'o', 'o', 'N', 'S',
            'i', 3, 'b', 'a', 'r', 'N', 'N', 'N', 'S',
            'i', 3, 'b', 'a', 'z', 'N', 'N', ']' };
        EXPECT_TRUE(json::to_ubjson(j) == v);
        EXPECT_TRUE(json::from_ubjson(v) == j);
        EXPECT_TRUE(json::from_ubjson(v2) == j);
    }

    {
        json j = { { "authorized", true }, { "verified", false } };
        std::vector<uint8_t> v = { '{', 'i', 10, 'a', 'u', 't', 'h', 'o', 'r',
            'i', 'z', 'e', 'd', 'T', 'i', 8, 'v', 'e',
            'r', 'i', 'f', 'i', 'e', 'd', 'F', '}' };
        EXPECT_TRUE(json::to_ubjson(j) == v);
        EXPECT_TRUE(json::from_ubjson(v) == j);
    }

    {
        json j = { { "int8", 16 },
            { "uint8", 255 },
            { "int16", 32767 },
            { "int32", 2147483647 },
            { "int64", 9223372036854775807 },
            { "float64", 113243.7863123 } };
        std::vector<uint8_t> v = {
            '{', 'i', 7, 'f', 'l', 'o', 'a', 't', '6', '4', 'D',
            0x40, 0xfb, 0xa5, 0xbc, 0x94, 0xbc, 0x34, 0xcf, 'i', 5, 'i',
            'n', 't', '1', '6', 'I', 0x7f, 0xff, 'i', 5, 'i', 'n',
            't', '3', '2', 'l', 0x7f, 0xff, 0xff, 0xff, 'i', 5, 'i',
            'n', 't', '6', '4', 'L', 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 'i', 4, 'i', 'n', 't', '8', 'i', 16, 'i',
            5, 'u', 'i', 'n', 't', '8', 'U', 0xff, '}'
        };
        EXPECT_TRUE(json::to_ubjson(j) == v);
        EXPECT_TRUE(json::from_ubjson(v) == j);
    }

    {
        json j = { { "rolecode", "a" }, { "delim", ";" } };
        std::vector<uint8_t> v = { '{', 'i', 5, 'd', 'e', 'l', 'i', 'm',
            'C', ';', 'i', 8, 'r', 'o', 'l', 'e',
            'c', 'o', 'd', 'e', 'C', 'a', '}' };
        // EXPECT_TRUE(json::to_ubjson(j) == v);
        EXPECT_TRUE(json::from_ubjson(v) == j);
    }

    { { json j = "hello";
    std::vector<uint8_t> v = { 'S', 'i', 5, 'h', 'e', 'l', 'l', 'o' };
    EXPECT_TRUE(json::to_ubjson(j) == v);
    EXPECT_TRUE(json::from_ubjson(v) == j);
}

{
    json j = "привет";
    std::vector<uint8_t> v = { 'S', 'i', 12, 0xD0, 0xBF, 0xD1, 0x80, 0xD0,
        0xB8, 0xD0, 0xB2, 0xD0, 0xB5, 0xD1, 0x82 };
    EXPECT_TRUE(json::to_ubjson(j) == v);
    EXPECT_TRUE(json::from_ubjson(v) == j);
}

{
    json j = "مرحبا";
    std::vector<uint8_t> v = { 'S', 'i', 10, 0xD9, 0x85, 0xD8, 0xB1,
        0xD8, 0xAD, 0xD8, 0xA8, 0xD8, 0xA7 };
    EXPECT_TRUE(json::to_ubjson(j) == v);
    EXPECT_TRUE(json::from_ubjson(v) == j);
}
}

{ { // note the float has been replaced by a double
    json j = { nullptr, true, false, 4782345193, 153.132, "ham" };
std::vector<uint8_t> v = { '[', 'Z', 'T', 'F', 'L', 0x00, 0x00, 0x00,
    0x01, 0x1D, 0x0C, 0xCB, 0xE9, 'D', 0x40, 0x63,
    0x24, 0x39, 0x58, 0x10, 0x62, 0x4e, 'S', 'i',
    3, 'h', 'a', 'm', ']' };
EXPECT_TRUE(json::to_ubjson(j) == v);
EXPECT_TRUE(json::from_ubjson(v) == j);
}

{
    // note the float has been replaced by a double
    json j = { nullptr, true, false, 4782345193, 153.132, "ham" };
    std::vector<uint8_t> v = { '[', '#', 'i', 6, 'Z', 'T', 'F', 'L',
        0x00, 0x00, 0x00, 0x01, 0x1D, 0x0C, 0xCB, 0xE9,
        'D', 0x40, 0x63, 0x24, 0x39, 0x58, 0x10, 0x62,
        0x4e, 'S', 'i', 3, 'h', 'a', 'm' };
    EXPECT_TRUE(json::to_ubjson(j, true) == v);
    EXPECT_TRUE(json::from_ubjson(v) == j);
}

{
    // note the float has been replaced by a double
    json j = { nullptr, true, false, 4782345193, 153.132, "ham" };
    std::vector<uint8_t> v = { '[', '#', 'i', 6, 'Z', 'T', 'F', 'L',
        0x00, 0x00, 0x00, 0x01, 0x1D, 0x0C, 0xCB, 0xE9,
        'D', 0x40, 0x63, 0x24, 0x39, 0x58, 0x10, 0x62,
        0x4e, 'S', 'i', 3, 'h', 'a', 'm' };
    EXPECT_TRUE(json::to_ubjson(j, true, true) == v);
    EXPECT_TRUE(json::from_ubjson(v) == j);
}
}

{ { json j = { { "post",
        { { "id", 1137 },
            { "author", "rkalla" },
            { "timestamp", 1364482090592 },
            { "body", "I totally agree!" } } } };
std::vector<uint8_t> v = {
    '{', 'i', 4, 'p', 'o', 's', 't', '{', 'i', 6, 'a', 'u',
    't', 'h', 'o', 'r', 'S', 'i', 6, 'r', 'k', 'a', 'l', 'l',
    'a', 'i', 4, 'b', 'o', 'd', 'y', 'S', 'i', 16, 'I', ' ',
    't', 'o', 't', 'a', 'l', 'l', 'y', ' ', 'a', 'g', 'r', 'e',
    'e', '!', 'i', 2, 'i', 'd', 'I', 0x04, 0x71, 'i', 9, 't',
    'i', 'm', 'e', 's', 't', 'a', 'm', 'p', 'L', 0x00, 0x00, 0x01,
    0x3D, 0xB1, 0x78, 0x66, 0x60, '}', '}'
};
EXPECT_TRUE(json::to_ubjson(j) == v);
EXPECT_TRUE(json::from_ubjson(v) == j);
}

{
    json j = { { "post",
        { { "id", 1137 },
            { "author", "rkalla" },
            { "timestamp", 1364482090592 },
            { "body", "I totally agree!" } } } };
    std::vector<uint8_t> v = {
        '{', '#', 'i', 1, 'i', 4, 'p', 'o', 's', 't', '{', '#',
        'i', 4, 'i', 6, 'a', 'u', 't', 'h', 'o', 'r', 'S', 'i',
        6, 'r', 'k', 'a', 'l', 'l', 'a', 'i', 4, 'b', 'o', 'd',
        'y', 'S', 'i', 16, 'I', ' ', 't', 'o', 't', 'a', 'l', 'l',
        'y', ' ', 'a', 'g', 'r', 'e', 'e', '!', 'i', 2, 'i', 'd',
        'I', 0x04, 0x71, 'i', 9, 't', 'i', 'm', 'e', 's', 't', 'a',
        'm', 'p', 'L', 0x00, 0x00, 0x01, 0x3D, 0xB1, 0x78, 0x66, 0x60
    };
    EXPECT_TRUE(json::to_ubjson(j, true) == v);
    EXPECT_TRUE(json::from_ubjson(v) == j);
}

{
    json j = { { "post",
        { { "id", 1137 },
            { "author", "rkalla" },
            { "timestamp", 1364482090592 },
            { "body", "I totally agree!" } } } };
    std::vector<uint8_t> v = {
        '{', '$', '{', '#', 'i', 1, 'i', 4, 'p', 'o', 's', 't',
        '#', 'i', 4, 'i', 6, 'a', 'u', 't', 'h', 'o', 'r', 'S',
        'i', 6, 'r', 'k', 'a', 'l', 'l', 'a', 'i', 4, 'b', 'o',
        'd', 'y', 'S', 'i', 16, 'I', ' ', 't', 'o', 't', 'a', 'l',
        'l', 'y', ' ', 'a', 'g', 'r', 'e', 'e', '!', 'i', 2, 'i',
        'd', 'I', 0x04, 0x71, 'i', 9, 't', 'i', 'm', 'e', 's', 't',
        'a', 'm', 'p', 'L', 0x00, 0x00, 0x01, 0x3D, 0xB1, 0x78, 0x66, 0x60
    };
    EXPECT_TRUE(json::to_ubjson(j, true, true) == v);
    EXPECT_TRUE(json::from_ubjson(v) == j);
}
}

{
    { { // note the floats have been replaced by doubles
        json j = { 29.97, 31.13, 67.0, 2.113, 23.888 };
    std::vector<uint8_t> v = {
        '[', 'D', 0x40, 0x3d, 0xf8, 0x51, 0xeb, 0x85, 0x1e, 0xb8, 'D', 0x40,
        0x3f, 0x21, 0x47, 0xae, 0x14, 0x7a, 0xe1, 'D', 0x40, 0x50, 0xc0, 0x00,
        0x00, 0x00, 0x00, 0x00, 'D', 0x40, 0x00, 0xe7, 0x6c, 0x8b, 0x43, 0x95,
        0x81, 'D', 0x40, 0x37, 0xe3, 0x53, 0xf7, 0xce, 0xd9, 0x17, ']'
    };
    EXPECT_TRUE(json::to_ubjson(j) == v);
    EXPECT_TRUE(json::from_ubjson(v) == j);
}

{
    // note the floats have been replaced by doubles
    json j = { 29.97, 31.13, 67.0, 2.113, 23.888 };
    std::vector<uint8_t> v = { '[', '#', 'i', 5, 'D', 0x40, 0x3d, 0xf8, 0x51,
        0xeb, 0x85, 0x1e, 0xb8, 'D', 0x40, 0x3f, 0x21, 0x47,
        0xae, 0x14, 0x7a, 0xe1, 'D', 0x40, 0x50, 0xc0, 0x00,
        0x00, 0x00, 0x00, 0x00, 'D', 0x40, 0x00, 0xe7, 0x6c,
        0x8b, 0x43, 0x95, 0x81, 'D', 0x40, 0x37, 0xe3, 0x53,
        0xf7, 0xce, 0xd9, 0x17 };
    EXPECT_TRUE(json::to_ubjson(j, true) == v);
    EXPECT_TRUE(json::from_ubjson(v) == j);
}

{
    // note the floats have been replaced by doubles
    json j = { 29.97, 31.13, 67.0, 2.113, 23.888 };
    std::vector<uint8_t> v = {
        '[', '$', 'D', '#', 'i', 5, 0x40, 0x3d, 0xf8, 0x51, 0xeb, 0x85,
        0x1e, 0xb8, 0x40, 0x3f, 0x21, 0x47, 0xae, 0x14, 0x7a, 0xe1, 0x40, 0x50,
        0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0xe7, 0x6c, 0x8b, 0x43,
        0x95, 0x81, 0x40, 0x37, 0xe3, 0x53, 0xf7, 0xce, 0xd9, 0x17
    };
    EXPECT_TRUE(json::to_ubjson(j, true, true) == v);
    EXPECT_TRUE(json::from_ubjson(v) == j);
}
}

{ { // note the floats have been replaced by doubles
    json j = { { "lat", 29.976 }, { "long", 31.131 }, { "alt", 67.0 } };
std::vector<uint8_t> v = { '{', 'i', 3, 'a', 'l', 't', 'D', 0x40, 0x50,
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 'i', 3, 'l',
    'a', 't', 'D', 0x40, 0x3d, 0xf9, 0xdb, 0x22, 0xd0,
    0xe5, 0x60, 'i', 4, 'l', 'o', 'n', 'g', 'D',
    0x40, 0x3f, 0x21, 0x89, 0x37, 0x4b, 0xc6, 0xa8, '}' };
EXPECT_TRUE(json::to_ubjson(j) == v);
EXPECT_TRUE(json::from_ubjson(v) == j);
}

{
    // note the floats have been replaced by doubles
    json j = { { "lat", 29.976 }, { "long", 31.131 }, { "alt", 67.0 } };
    std::vector<uint8_t> v = {
        '{', '#', 'i', 3, 'i', 3, 'a', 'l', 't', 'D', 0x40, 0x50,
        0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 'i', 3, 'l', 'a', 't', 'D',
        0x40, 0x3d, 0xf9, 0xdb, 0x22, 0xd0, 0xe5, 0x60, 'i', 4, 'l', 'o',
        'n', 'g', 'D', 0x40, 0x3f, 0x21, 0x89, 0x37, 0x4b, 0xc6, 0xa8
    };
    EXPECT_TRUE(json::to_ubjson(j, true) == v);
    EXPECT_TRUE(json::from_ubjson(v) == j);
}

{
    // note the floats have been replaced by doubles
    json j = { { "lat", 29.976 }, { "long", 31.131 }, { "alt", 67.0 } };
    std::vector<uint8_t> v = {
        '{', '$', 'D', '#', 'i', 3, 'i', 3, 'a', 'l', 't', 0x40,
        0x50, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 'i', 3, 'l', 'a', 't',
        0x40, 0x3d, 0xf9, 0xdb, 0x22, 0xd0, 0xe5, 0x60, 'i', 4, 'l', 'o',
        'n', 'g', 0x40, 0x3f, 0x21, 0x89, 0x37, 0x4b, 0xc6, 0xa8
    };
    EXPECT_TRUE(json::to_ubjson(j, true, true) == v);
    EXPECT_TRUE(json::from_ubjson(v) == j);
}
}

{
    {
        std::vector<uint8_t> v = { '[', '$', 'N', '#', 'I', 0x02, 0x00 };
        EXPECT_TRUE(json::from_ubjson(v) == json::array());
    }

    {
        std::vector<uint8_t> v = { '{', '$', 'Z', '#', 'i', 3, 'i', 4, 'n', 'a',
            'm', 'e', 'i', 8, 'p', 'a', 's', 's', 'w', 'o',
            'r', 'd', 'i', 5, 'e', 'm', 'a', 'i', 'l' };
        EXPECT_TRUE(json::from_ubjson(v) == json({ { "name", nullptr }, { "password", nullptr }, { "email", nullptr } }));
    }
}
}
}

TEST(UBJSON, all_UBJSON_first_bytes_throws)
{
    // these bytes will fail immediately with exception parse_error.112
    std::set<uint8_t> supported = { 'T', 'F', 'Z', 'U', 'i', 'I', 'l', 'L',
        'd', 'D', 'C', 'S', '[', '{', 'N' };

    for (auto i = 0; i < 256; ++i) {
        const auto byte = static_cast<uint8_t>(i);

        try {
            json::from_ubjson(std::vector<uint8_t>(1, byte));
        } catch (const json::parse_error& e) {
            // check that parse_error.112 is only thrown if the
            // first byte is not in the supported set
            if (std::find(supported.begin(), supported.end(), byte) == supported.end()) {
                EXPECT_TRUE(e.id == 112);
            } else {
                EXPECT_TRUE(e.id != 112);
            }
        }
    }
}

TEST(UBJSON, UBJSON_roundtrips_hide)
{
    {
        for (std::string filename :
            { "test/data/json_nlohmann_tests/all_unicode.json",
                "test/data/json.org/1.json",
                "test/data/json.org/2.json",
                "test/data/json.org/3.json",
                "test/data/json.org/4.json",
                "test/data/json.org/5.json",
                "test/data/json_roundtrip/roundtrip01.json",
                "test/data/json_roundtrip/roundtrip02.json",
                "test/data/json_roundtrip/roundtrip03.json",
                "test/data/json_roundtrip/roundtrip04.json",
                "test/data/json_roundtrip/roundtrip05.json",
                "test/data/json_roundtrip/roundtrip06.json",
                "test/data/json_roundtrip/roundtrip07.json",
                "test/data/json_roundtrip/roundtrip08.json",
                "test/data/json_roundtrip/roundtrip09.json",
                "test/data/json_roundtrip/roundtrip10.json",
                "test/data/json_roundtrip/roundtrip11.json",
                "test/data/json_roundtrip/roundtrip12.json",
                "test/data/json_roundtrip/roundtrip13.json",
                "test/data/json_roundtrip/roundtrip14.json",
                "test/data/json_roundtrip/roundtrip15.json",
                "test/data/json_roundtrip/roundtrip16.json",
                "test/data/json_roundtrip/roundtrip17.json",
                "test/data/json_roundtrip/roundtrip18.json",
                "test/data/json_roundtrip/roundtrip19.json",
                "test/data/json_roundtrip/roundtrip20.json",
                "test/data/json_roundtrip/roundtrip21.json",
                "test/data/json_roundtrip/roundtrip22.json",
                "test/data/json_roundtrip/roundtrip23.json",
                "test/data/json_roundtrip/roundtrip24.json",
                "test/data/json_roundtrip/roundtrip25.json",
                "test/data/json_roundtrip/roundtrip26.json",
                "test/data/json_roundtrip/roundtrip27.json",
                "test/data/json_roundtrip/roundtrip28.json",
                "test/data/json_roundtrip/roundtrip29.json",
                "test/data/json_roundtrip/roundtrip30.json",
                "test/data/json_roundtrip/roundtrip31.json",
                "test/data/json_roundtrip/roundtrip32.json",
                "test/data/json_testsuite/sample.json",
                "test/data/json_tests/pass1.json",
                "test/data/json_tests/pass2.json",
                "test/data/json_tests/pass3.json" }) {

            // parse JSON file
            std::ifstream f_json(filename);
            json j1 = json::parse(f_json);

            {
                // parse MessagePack file
                std::ifstream f_ubjson(filename + ".ubjson", std::ios::binary);
                std::vector<uint8_t> packed((std::istreambuf_iterator<char>(f_ubjson)),
                    std::istreambuf_iterator<char>());
                json j2;
                EXPECT_NO_THROW(j2 = json::from_ubjson(packed));

                // compare parsed JSON values
                EXPECT_TRUE(j1 == j2);
            }

            {
                // parse MessagePack file
                std::ifstream f_ubjson(filename + ".ubjson", std::ios::binary);
                json j2;
                EXPECT_NO_THROW(j2 = json::from_ubjson(f_ubjson));

                // compare parsed JSON values
                EXPECT_TRUE(j1 == j2);
            }

            {
                // parse MessagePack file
                std::ifstream f_ubjson(filename + ".ubjson", std::ios::binary);
                std::vector<uint8_t> packed((std::istreambuf_iterator<char>(f_ubjson)),
                    std::istreambuf_iterator<char>());
                json j2;
                EXPECT_NO_THROW(j2 = json::from_ubjson({ packed.data(), packed.size() }));

                // compare parsed JSON values
                EXPECT_TRUE(j1 == j2);
            }

            {
                // parse MessagePack file
                std::ifstream f_ubjson(filename + ".ubjson", std::ios::binary);
                std::vector<uint8_t> packed((std::istreambuf_iterator<char>(f_ubjson)),
                    std::istreambuf_iterator<char>());

                {
                    std::vector<uint8_t> vec;
                    json::to_ubjson(j1, vec);
                    EXPECT_TRUE(vec == packed);
                }
            }
        }
    }
}
