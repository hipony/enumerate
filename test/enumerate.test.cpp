// Copyright 2021 Alexandr Timofeev
//
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1.0.txt)

#include <hipony/enumerate.hpp>

#include <catch2/catch.hpp>

#include <array>
#include <list>
#include <string>
#include <type_traits>
#include <vector>

namespace HIPONY_ENUMERATE_NAMESPACE {

namespace {

template<typename T, typename U>
constexpr auto assert_same() -> int
{
    static_assert(std::is_same<T, U>::value, "Types are not the same");
    return 0;
}

template<typename T>
constexpr auto index_of() -> int;

template<>
constexpr auto index_of<int>() -> int
{
    return 0;
}

template<>
constexpr auto index_of<double>() -> int
{
    return 1;
}

template<>
constexpr auto index_of<char const*>() -> int
{
    return 2;
}

} // namespace

#if HIPONY_ENUMERATE_CPP14_OR_GREATER

TEST_CASE("as_tuple")
{
    SECTION("each")
    {
        auto counter = 0;
        enumerate(as_tuple, 0, 1., "str").each([&](auto index, auto& value) {
            assert_same<decltype(index), std::size_t>();

            REQUIRE(index == index_of<typename std::decay<decltype(value)>::type>());
            ++counter;
        });
        REQUIRE(counter == 3);
    }
    SECTION("each as int")
    {
        auto counter = 0;
        enumerate_as<int>(as_tuple, 0, 1., "str").each([&](auto index, auto& value) {
            assert_same<decltype(index), int>();

            REQUIRE(index == index_of<typename std::decay<decltype(value)>::type>());
            ++counter;
        });
        REQUIRE(counter == 3);
    }
}

#endif // HIPONY_ENUMERATE_CPP14_OR_GREATER

TEST_CASE("as_array")
{
    SECTION("for-range")
    {
        auto counter = 0;
        for (auto&& item : enumerate(as_array, 0, 10, 20, 30, 40)) {
            assert_same<std::size_t, decltype(item.index)>();
            assert_same<int&, decltype(item.value)>();

            REQUIRE(item.index * 10 == item.value);
            ++counter;
        }
        REQUIRE(counter == 5);
    }
    SECTION("for-range as int")
    {
        auto counter = 0;
        for (auto&& item : enumerate_as<int>(as_array, 0, 10, 20, 30, 40)) {
            assert_same<int, decltype(item.index)>();
            assert_same<int&, decltype(item.value)>();

            REQUIRE(item.index * 10 == item.value);
            ++counter;
        }
        REQUIRE(counter == 5);
    }
#if HIPONY_ENUMERATE_HAS_RANGES && !defined(__clang__)
    SECTION("ranges")
    {
        auto counter = 0;
        auto range   = enumerate_as<int>(as_array, 0, 10, 20, 30, 40);
        for (auto&& item : range | std::ranges::views::take(3)) {
            assert_same<int, decltype(item.index)>();
            assert_same<int&, decltype(item.value)>();

            REQUIRE(item.index * 10 == item.value);
            ++counter;
        }
        REQUIRE(counter == 3);
    }
#endif
}

TEST_CASE("iterator_pointer_tag_t")
{
    SECTION("array")
    {
        auto counter = 0;
        auto array   = std::array<int, 5>({0, 10, 20, 30, 40});
        for (auto&& item : enumerate(array.begin(), array.end())) {
            assert_same<int&, decltype(item.value)>();
            assert_same<std::size_t, decltype(item.index)>();

            REQUIRE(item.index * 10 == item.value);
            ++counter;
        }
        REQUIRE(counter == 5);
    }
    SECTION("const")
    {
        auto       counter = 0;
        auto const array   = std::array<int, 5>({0, 10, 20, 30, 40});
        for (auto&& item : enumerate(array.begin(), array.end())) {
            assert_same<int const&, decltype(item.value)>();
            assert_same<std::size_t, decltype(item.index)>();

            REQUIRE(item.index * 10 == item.value);
            ++counter;
        }
        REQUIRE(counter == 5);
    }
    SECTION("as int")
    {
        auto       counter = 0;
        auto const array   = std::array<int, 5>({0, 10, 20, 30, 40});
        for (auto&& item : enumerate_as<int>(array.begin(), array.end())) {
            assert_same<int const&, decltype(item.value)>();
            assert_same<int, decltype(item.index)>();

            REQUIRE(item.index * 10 == item.value);
            ++counter;
        }
        REQUIRE(counter == 5);
    }
#if HIPONY_ENUMERATE_HAS_RANGES && !defined(__clang__)
    SECTION("ranges")
    {
        auto       counter = 0;
        auto const array   = std::array<int, 5>({0, 10, 20, 30, 40});
        auto const range   = enumerate_as<int>(array.begin(), array.end());
        for (auto&& item : range | std::ranges::views::take(3)) {
            assert_same<int const&, decltype(item.value)>();
            assert_same<int, decltype(item.index)>();

            REQUIRE(item.index * 10 == item.value);
            ++counter;
        }
        REQUIRE(counter == 3);
    }
#endif
}

TEST_CASE("iterator_tag_t")
{
    SECTION("list")
    {
        auto counter = 0;
        auto list    = std::list<int>({0, 10, 20, 30, 40});
        for (auto&& item : enumerate(list.begin(), list.end())) {
            assert_same<int&, decltype(item.value)>();
            assert_same<std::size_t, decltype(item.index)>();

            REQUIRE(item.index * 10 == item.value);
            ++counter;
        }
        REQUIRE(counter == 5);
    }
    SECTION("const")
    {
        auto       counter = 0;
        auto const list    = std::list<int>({0, 10, 20, 30, 40});
        for (auto&& item : enumerate(list.begin(), list.end())) {
            assert_same<int const&, decltype(item.value)>();
            assert_same<std::size_t, decltype(item.index)>();

            REQUIRE(item.index * 10 == item.value);
            ++counter;
        }
        REQUIRE(counter == 5);
    }
    SECTION("as int")
    {
        auto       counter = 0;
        auto const list    = std::list<int>({0, 10, 20, 30, 40});
        for (auto&& item : enumerate_as<int>(list.begin(), list.end())) {
            assert_same<int const&, decltype(item.value)>();
            assert_same<int, decltype(item.index)>();

            REQUIRE(item.index * 10 == item.value);
            ++counter;
        }
        REQUIRE(counter == 5);
    }
#if HIPONY_ENUMERATE_HAS_RANGES && !defined(__clang__)
    SECTION("ranges")
    {
        auto       counter = 0;
        auto const list    = std::list<int>({0, 10, 20, 30, 40});
        auto const range   = enumerate_as<int>(list.begin(), list.end());
        for (auto&& item : range | std::ranges::views::take(3)) {
            assert_same<int const&, decltype(item.value)>();
            assert_same<int, decltype(item.index)>();

            REQUIRE(item.index * 10 == item.value);
            ++counter;
        }
        REQUIRE(counter == 3);
    }
#endif
}

TEST_CASE("container_tag_t")
{
    SECTION("array")
    {
        SECTION("prvalue")
        {
            auto counter = 0;
            for (auto&& item : enumerate(std::array<int, 5>({0, 10, 20, 30, 40}))) {
                assert_same<int&, decltype(item.value)>();

                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
        SECTION("lvalue")
        {
            auto counter = 0;
            auto array   = std::array<int, 5>({0, 10, 20, 30, 40});
            for (auto&& item : enumerate(array)) {
                assert_same<decltype(array)::size_type, decltype(item.index)>();
                assert_same<decltype(array)::value_type&, decltype(item.value)>();

                REQUIRE(&array[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
        SECTION("const")
        {
            auto       counter = 0;
            auto const array   = std::array<int, 5>({0, 10, 20, 30, 40});
            for (auto&& item : enumerate(array)) {
                assert_same<decltype(array)::size_type, decltype(item.index)>();
                assert_same<decltype(array)::value_type const&, decltype(item.value)>();

                REQUIRE(&array[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
        SECTION("as int")
        {
            auto       counter = 0;
            auto const array   = std::array<int, 5>({0, 10, 20, 30, 40});
            for (auto&& item : enumerate_as<int>(array)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(array)::value_type const&, decltype(item.value)>();

                REQUIRE(&array[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
#if HIPONY_ENUMERATE_HAS_RANGES && !defined(__clang__)
        SECTION("ranges")
        {
            auto       counter = 0;
            auto const range   = enumerate_as<int>(std::array<int, 5>({0, 10, 20, 30, 40}));
            for (auto&& item : range | std::ranges::views::take(3)) {
                assert_same<int, decltype(item.index)>();
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == 3);
        }
        SECTION("ranges-view")
        {
            auto       counter = 0;
            auto const array   = std::array<int, 5>({0, 10, 20, 30, 40});
            for (auto&& item : enumerate_as<int>(array) | std::ranges::views::take(3)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(array)::value_type const&, decltype(item.value)>();

                REQUIRE(&array[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == 3);
        }
        SECTION("ranges-reverse")
        {
            auto       counter = 0;
            auto const array   = std::array<int, 5>({0, 10, 20, 30, 40});
            for (auto&& item : enumerate_as<int>(array) | std::ranges::views::reverse) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(array)::value_type const&, decltype(item.value)>();

                auto const index = array.size() - (item.index + 1);
                REQUIRE(&array[index] == &item.value);
                REQUIRE(index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == array.size());
        }
#endif
    }
    SECTION("vector")
    {
        SECTION("prvalue")
        {
            auto counter = 0;
            for (auto&& item : enumerate(std::vector<int>({0, 10, 20, 30, 40}))) {
                assert_same<int&, decltype(item.value)>();

                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
        SECTION("lvalue")
        {
            auto counter = 0;
            auto vector  = std::vector<int>({0, 10, 20, 30, 40});
            for (auto&& item : enumerate(vector)) {
                assert_same<decltype(vector)::size_type, decltype(item.index)>();
                assert_same<decltype(vector)::value_type&, decltype(item.value)>();

                REQUIRE(&vector[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
        SECTION("const")
        {
            auto       counter = 0;
            auto const vector  = std::vector<int>({0, 10, 20, 30, 40});
            for (auto&& item : enumerate(vector)) {
                assert_same<decltype(vector)::size_type, decltype(item.index)>();
                assert_same<decltype(vector)::value_type const&, decltype(item.value)>();

                REQUIRE(&vector[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
        SECTION("as int")
        {
            auto       counter = 0;
            auto const vector  = std::vector<int>({0, 10, 20, 30, 40});
            for (auto&& item : enumerate_as<int>(vector)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(vector)::value_type const&, decltype(item.value)>();

                REQUIRE(&vector[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
#if HIPONY_ENUMERATE_HAS_RANGES && !defined(__clang__)
        SECTION("ranges")
        {
            auto       counter = 0;
            auto const range   = enumerate_as<int>(std::vector<int>({0, 10, 20, 30, 40}));
            for (auto&& item : range | std::ranges::views::take(3)) {
                assert_same<int, decltype(item.index)>();
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == 3);
        }
        SECTION("ranges-view")
        {
            auto       counter = 0;
            auto const vector  = std::vector<int>({0, 10, 20, 30, 40});
            for (auto&& item : enumerate_as<int>(vector) | std::ranges::views::take(3)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(vector)::value_type const&, decltype(item.value)>();

                REQUIRE(&vector[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == 3);
        }
        SECTION("ranges-reverse")
        {
            auto       counter = 0;
            auto const vector  = std::vector<int>({0, 10, 20, 30, 40});
            for (auto&& item : enumerate_as<int>(vector) | std::ranges::views::reverse) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(vector)::value_type const&, decltype(item.value)>();

                auto const index = vector.size() - (item.index + 1);
                REQUIRE(&vector[index] == &item.value);
                REQUIRE(index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == vector.size());
        }
#endif
    }
    SECTION("string")
    {
        SECTION("prvalue")
        {
            auto counter = 0;
            for (auto&& item : enumerate(std::string("01234"))) {
                assert_same<char&, decltype(item.value)>();

                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
        SECTION("lvalue")
        {
            auto counter = 0;
            auto string  = std::string("01234");
            for (auto&& item : enumerate(string)) {
                assert_same<decltype(string)::size_type, decltype(item.index)>();
                assert_same<decltype(string)::value_type&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value);
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
        SECTION("const")
        {
            auto       counter = 0;
            auto const string  = std::string("01234");
            for (auto&& item : enumerate(string)) {
                assert_same<decltype(string)::size_type, decltype(item.index)>();
                assert_same<decltype(string)::value_type const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value);
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
        SECTION("as int")
        {
            auto       counter = 0;
            auto const string  = std::string("01234");
            for (auto&& item : enumerate_as<int>(string)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(string)::value_type const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value);
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
#if HIPONY_ENUMERATE_HAS_RANGES && !defined(__clang__)
        SECTION("ranges")
        {
            auto       counter = 0;
            auto const range   = enumerate_as<int>(std::string("01234"));
            for (auto&& item : range | std::ranges::views::take(3)) {
                assert_same<int, decltype(item.index)>();
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 3);
        }
        SECTION("ranges-views")
        {
            auto       counter = 0;
            auto const string  = std::string("01234");
            for (auto&& item : enumerate_as<int>(string) | std::ranges::views::take(3)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(string)::value_type const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value);
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 3);
        }
        SECTION("ranges-reverse")
        {
            auto       counter = 0;
            auto const string  = std::string("01234");
            for (auto&& item : enumerate_as<int>(string) | std::ranges::views::reverse) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(string)::value_type const&, decltype(item.value)>();

                auto const index = string.size() - (item.index + 1);
                REQUIRE(&string[index] == &item.value);
                REQUIRE(index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == string.size());
        }
#endif
    }
    SECTION("list")
    {
        SECTION("prvalue")
        {
            auto counter = 0;
            for (auto&& item : enumerate(std::list<int>({0, 10, 20, 30, 40}))) {
                assert_same<int&, decltype(item.value)>();

                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
        SECTION("lvalue")
        {
            auto counter = 0;
            auto list    = std::list<int>({0, 10, 20, 30, 40});
            for (auto&& item : enumerate(list)) {
                assert_same<decltype(list)::size_type, decltype(item.index)>();
                assert_same<decltype(list)::value_type&, decltype(item.value)>();

                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
        SECTION("const")
        {
            auto       counter = 0;
            auto const list    = std::list<int>({0, 10, 20, 30, 40});
            for (auto&& item : enumerate(list)) {
                assert_same<decltype(list)::size_type, decltype(item.index)>();
                assert_same<decltype(list)::value_type const&, decltype(item.value)>();

                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
        SECTION("as int")
        {
            auto       counter = 0;
            auto const list    = std::list<int>({0, 10, 20, 30, 40});
            for (auto&& item : enumerate_as<int>(list)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(list)::value_type const&, decltype(item.value)>();

                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
#if HIPONY_ENUMERATE_HAS_RANGES && !defined(__clang__)
        SECTION("ranges")
        {
            auto       counter = 0;
            auto const range   = enumerate_as<int>(std::list<int>({0, 10, 20, 30, 40}));
            for (auto&& item : range | std::ranges::views::take(3)) {
                assert_same<int, decltype(item.index)>();
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == 3);
        }
        SECTION("ranges-view")
        {
            auto       counter = 0;
            auto const list    = std::list<int>({0, 10, 20, 30, 40});
            for (auto&& item : enumerate_as<int>(list) | std::ranges::views::take(3)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(list)::value_type const&, decltype(item.value)>();

                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == 3);
        }
        SECTION("ranges-reverse")
        {
            auto       counter = 0;
            auto const list    = std::list<int>({0, 10, 20, 30, 40});
            for (auto&& item : enumerate_as<int>(list) | std::ranges::views::reverse) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(list)::value_type const&, decltype(item.value)>();

                auto const index = list.size() - (item.index + 1);
                REQUIRE(index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == list.size());
        }
#endif
    }
}

TEST_CASE("container_size_tag_t")
{
    SECTION("array")
    {
        SECTION("prvalue")
        {
            auto       counter = 0;
            auto const size    = 3u;
            for (auto&& item : enumerate(std::array<int, 5>({0, 10, 20, 30, 40}), size)) {
                assert_same<int&, decltype(item.value)>();

                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
        }
        SECTION("lvalue")
        {
            auto       counter = 0;
            auto       array   = std::array<int, 5>({0, 10, 20, 30, 40});
            auto const size    = 3u;
            for (auto&& item : enumerate(array, size)) {
                assert_same<decltype(array)::size_type, decltype(item.index)>();
                assert_same<decltype(array)::value_type&, decltype(item.value)>();

                REQUIRE(&array[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter != array.size());
        }
        SECTION("const")
        {
            auto       counter = 0;
            auto const array   = std::array<int, 5>({0, 10, 20, 30, 40});
            auto const size    = 3u;
            for (auto&& item : enumerate(array, size)) {
                assert_same<decltype(array)::size_type, decltype(item.index)>();
                assert_same<decltype(array)::value_type const&, decltype(item.value)>();

                REQUIRE(&array[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter != array.size());
        }
        SECTION("as int")
        {
            auto       counter = 0;
            auto const array   = std::array<int, 5>({0, 10, 20, 30, 40});
            auto const size    = 3;
            for (auto&& item : enumerate_as<int>(array, size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(array)::value_type const&, decltype(item.value)>();

                REQUIRE(&array[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter != array.size());
        }
#if HIPONY_ENUMERATE_HAS_RANGES && !defined(__clang__)
        SECTION("ranges")
        {
            auto       counter = 0;
            auto const size    = 3;
            auto const range   = enumerate_as<int>(std::array<int, 5>({0, 10, 20, 30, 40}), 5);
            for (auto&& item : range | std::ranges::views::take(size)) {
                assert_same<int, decltype(item.index)>();
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
        }
        SECTION("ranges-view")
        {
            auto       counter = 0;
            auto const array   = std::array<int, 5>({0, 10, 20, 30, 40});
            auto const size    = 3;
            for (auto&& item : enumerate_as<int>(array, static_cast<int>(array.size()))
                     | std::ranges::views::take(size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(array)::value_type const&, decltype(item.value)>();

                REQUIRE(&array[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter != array.size());
        }
        SECTION("ranges-reverse")
        {
            auto       counter = 0;
            auto const array   = std::array<int, 5>({0, 10, 20, 30, 40});
            auto const size    = 3;
            for (auto&& item : enumerate_as<int>(array, 3) | std::ranges::views::reverse) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(array)::value_type const&, decltype(item.value)>();

                auto const index = size - (item.index + 1);
                REQUIRE(&array[index] == &item.value);
                REQUIRE(index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
        }
#endif
        SECTION("more")
        {
            auto       counter = 0;
            auto const array   = std::array<int, 5>({0, 10, 20, 30, 40});
            auto const size    = 6;
            for (auto&& item : enumerate_as<int>(array, size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(array)::value_type const&, decltype(item.value)>();

                REQUIRE(&array[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter != size);
            REQUIRE(counter == array.size());
        }
        SECTION("exact")
        {
            auto       counter = 0;
            auto const array   = std::array<int, 5>({0, 10, 20, 30, 40});
            auto const size    = 5;
            for (auto&& item : enumerate_as<int>(array, size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(array)::value_type const&, decltype(item.value)>();

                REQUIRE(&array[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter == array.size());
        }
        SECTION("zero")
        {
            auto       counter = 0;
            auto const array   = std::array<int, 0>({});
            auto const size    = 0;
            for (auto&& item : enumerate_as<int>(array, size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(array)::value_type const&, decltype(item.value)>();

                REQUIRE(&array[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter == array.size());
        }
        SECTION("zero-more")
        {
            auto       counter = 0;
            auto const array   = std::array<int, 0>({});
            auto const size    = 1;
            for (auto&& item : enumerate_as<int>(array, size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(array)::value_type const&, decltype(item.value)>();

                REQUIRE(&array[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter != size);
            REQUIRE(counter == array.size());
        }
    }
    SECTION("vector")
    {
        SECTION("prvalue")
        {
            auto       counter = 0;
            auto const size    = 3u;
            for (auto&& item : enumerate(std::vector<int>({0, 10, 20, 30, 40}), size)) {
                assert_same<int&, decltype(item.value)>();

                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
        }
        SECTION("lvalue")
        {
            auto       counter = 0;
            auto       vector  = std::vector<int>({0, 10, 20, 30, 40});
            auto const size    = 3u;
            for (auto&& item : enumerate(vector, size)) {
                assert_same<decltype(vector)::size_type, decltype(item.index)>();
                assert_same<decltype(vector)::value_type&, decltype(item.value)>();

                REQUIRE(&vector[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter != vector.size());
        }
        SECTION("const")
        {
            auto       counter = 0;
            auto const vector  = std::vector<int>({0, 10, 20, 30, 40});
            auto const size    = 3u;
            for (auto&& item : enumerate(vector, size)) {
                assert_same<decltype(vector)::size_type, decltype(item.index)>();
                assert_same<decltype(vector)::value_type const&, decltype(item.value)>();

                REQUIRE(&vector[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter != vector.size());
        }
        SECTION("as int")
        {
            auto       counter = 0;
            auto const vector  = std::vector<int>({0, 10, 20, 30, 40});
            auto const size    = 3;
            for (auto&& item : enumerate_as<int>(vector, size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(vector)::value_type const&, decltype(item.value)>();

                REQUIRE(&vector[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter != vector.size());
        }
#if HIPONY_ENUMERATE_HAS_RANGES && !defined(__clang__)
        SECTION("ranges")
        {
            auto       counter = 0;
            auto const size    = 3;
            auto const range   = enumerate_as<int>(std::vector<int>({0, 10, 20, 30, 40}), 5);
            for (auto&& item : range | std::ranges::views::take(size)) {
                assert_same<int, decltype(item.index)>();
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
        }
        SECTION("ranges-view")
        {
            auto       counter = 0;
            auto const vector  = std::vector<int>({0, 10, 20, 30, 40});
            auto const size    = 3;
            for (auto&& item : enumerate_as<int>(vector, static_cast<int>(vector.size()))
                     | std::ranges::views::take(size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(vector)::value_type const&, decltype(item.value)>();

                REQUIRE(&vector[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter != vector.size());
        }
        SECTION("ranges-reverse")
        {
            auto       counter = 0;
            auto const vector  = std::vector<int>({0, 10, 20, 30, 40});
            auto const size    = 3;
            for (auto&& item : enumerate_as<int>(vector, 3) | std::ranges::views::reverse) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(vector)::value_type const&, decltype(item.value)>();

                auto const index = size - (item.index + 1);
                REQUIRE(&vector[index] == &item.value);
                REQUIRE(index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
        }
#endif
        SECTION("more")
        {
            auto       counter = 0;
            auto const vector  = std::vector<int>({0, 10, 20, 30, 40});
            auto const size    = 6;
            for (auto&& item : enumerate_as<int>(vector, size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(vector)::value_type const&, decltype(item.value)>();

                REQUIRE(&vector[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter != size);
            REQUIRE(counter == vector.size());
        }
        SECTION("exact")
        {
            auto       counter = 0;
            auto const vector  = std::vector<int>({0, 10, 20, 30, 40});
            auto const size    = 5;
            for (auto&& item : enumerate_as<int>(vector, size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(vector)::value_type const&, decltype(item.value)>();

                REQUIRE(&vector[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter == vector.size());
        }
        SECTION("zero")
        {
            auto       counter = 0;
            auto const vector  = std::vector<int>({});
            auto const size    = 0;
            for (auto&& item : enumerate_as<int>(vector, size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(vector)::value_type const&, decltype(item.value)>();

                REQUIRE(&vector[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter == vector.size());
        }
        SECTION("zero-more")
        {
            auto       counter = 0;
            auto const vector  = std::vector<int>({});
            auto const size    = 1;
            for (auto&& item : enumerate_as<int>(vector, size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(vector)::value_type const&, decltype(item.value)>();

                REQUIRE(&vector[item.index] == &item.value);
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter != size);
            REQUIRE(counter == vector.size());
        }
    }
    SECTION("string")
    {
        SECTION("prvalue")
        {
            auto       counter = 0;
            auto const size    = 3u;
            for (auto&& item : enumerate(std::string("01234"), size)) {
                assert_same<char&, decltype(item.value)>();

                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
        }
        SECTION("lvalue")
        {
            auto       counter = 0;
            auto       string  = std::string("01234");
            auto const size    = 3u;
            for (auto&& item : enumerate(string, size)) {
                assert_same<decltype(string)::size_type, decltype(item.index)>();
                assert_same<decltype(string)::value_type&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value);
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter != string.size());
        }
        SECTION("const")
        {
            auto       counter = 0;
            auto const string  = std::string("01234");
            auto const size    = 3u;
            for (auto&& item : enumerate(string, size)) {
                assert_same<decltype(string)::size_type, decltype(item.index)>();
                assert_same<decltype(string)::value_type const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value);
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter != string.size());
        }
        SECTION("as int")
        {
            auto       counter = 0;
            auto const string  = std::string("01234");
            auto const size    = 3;
            for (auto&& item : enumerate_as<int>(string, size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(string)::value_type const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value);
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter != string.size());
        }
#if HIPONY_ENUMERATE_HAS_RANGES && !defined(__clang__)
        SECTION("ranges")
        {
            auto       counter = 0;
            auto const size    = 3;
            auto const range   = enumerate_as<int>(std::string("01234"), 5);
            for (auto&& item : range | std::ranges::views::take(size)) {
                assert_same<int, decltype(item.index)>();
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
        }
        SECTION("ranges-view")
        {
            auto       counter = 0;
            auto const string  = std::string("01234");
            auto const size    = 3;
            for (auto&& item : enumerate_as<int>(string, static_cast<int>(string.size()))
                     | std::ranges::views::take(size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(string)::value_type const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value);
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter != string.size());
        }
#endif
        SECTION("more")
        {
            auto       counter = 0;
            auto const string  = std::string("01234");
            auto const size    = 6;
            for (auto&& item : enumerate_as<int>(string, size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(string)::value_type const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value);
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter != size);
            REQUIRE(counter == string.size());
        }
        SECTION("exact")
        {
            auto       counter = 0;
            auto const string  = std::string("01234");
            auto const size    = 5;
            for (auto&& item : enumerate_as<int>(string, size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(string)::value_type const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value);
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter == string.size());
        }
        SECTION("zero")
        {
            auto       counter = 0;
            auto const string  = std::string();
            auto const size    = 0;
            for (auto&& item : enumerate_as<int>(string, size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(string)::value_type const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value);
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter == string.size());
        }
        SECTION("zero-more")
        {
            auto       counter = 0;
            auto const string  = std::string();
            auto const size    = 1;
            for (auto&& item : enumerate_as<int>(string, size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(string)::value_type const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value);
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter != size);
            REQUIRE(counter == string.size());
        }
    }
    SECTION("list")
    {
        SECTION("prvalue")
        {
            auto       counter = 0;
            auto const size    = 3u;
            for (auto&& item : enumerate(std::list<int>({0, 10, 20, 30, 40}), size)) {
                assert_same<int&, decltype(item.value)>();

                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
        }
        SECTION("lvalue")
        {
            auto       counter = 0;
            auto       list    = std::list<int>({0, 10, 20, 30, 40});
            auto const size    = 3u;
            for (auto&& item : enumerate(list, size)) {
                assert_same<decltype(list)::size_type, decltype(item.index)>();
                assert_same<decltype(list)::value_type&, decltype(item.value)>();

                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter != list.size());
        }
        SECTION("const")
        {
            auto       counter = 0;
            auto const list    = std::list<int>({0, 10, 20, 30, 40});
            auto const size    = 3u;
            for (auto&& item : enumerate(list, size)) {
                assert_same<decltype(list)::size_type, decltype(item.index)>();
                assert_same<decltype(list)::value_type const&, decltype(item.value)>();

                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter != list.size());
        }
        SECTION("as int")
        {
            auto       counter = 0;
            auto const list    = std::list<int>({0, 10, 20, 30, 40});
            auto const size    = 3;
            for (auto&& item : enumerate_as<int>(list, size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(list)::value_type const&, decltype(item.value)>();

                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter != list.size());
        }
#if HIPONY_ENUMERATE_HAS_RANGES && !defined(__clang__)
        SECTION("ranges")
        {
            auto       counter = 0;
            auto const size    = 3;
            auto const range   = enumerate_as<int>(std::list<int>({0, 10, 20, 30, 40}), 5);
            for (auto&& item : range | std::ranges::views::take(size)) {
                assert_same<int, decltype(item.index)>();
                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
        }
        SECTION("ranges-view")
        {
            auto       counter = 0;
            auto const list    = std::list<int>({0, 10, 20, 30, 40});
            auto const size    = 3;
            for (auto&& item : enumerate_as<int>(list, static_cast<int>(list.size()))
                     | std::ranges::views::take(size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(list)::value_type const&, decltype(item.value)>();

                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter != list.size());
        }
#endif
        SECTION("more")
        {
            auto       counter = 0;
            auto const list    = std::list<int>({0, 10, 20, 30, 40});
            auto const size    = 6;
            for (auto&& item : enumerate_as<int>(list, size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(list)::value_type const&, decltype(item.value)>();

                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter != size);
            REQUIRE(counter == list.size());
        }
        SECTION("exact")
        {
            auto       counter = 0;
            auto const list    = std::list<int>({0, 10, 20, 30, 40});
            auto const size    = 5;
            for (auto&& item : enumerate_as<int>(list, size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(list)::value_type const&, decltype(item.value)>();

                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter == list.size());
        }
        SECTION("zero")
        {
            auto       counter = 0;
            auto const list    = std::list<int>({});
            auto const size    = 0;
            for (auto&& item : enumerate_as<int>(list, size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(list)::value_type const&, decltype(item.value)>();

                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter == size);
            REQUIRE(counter == list.size());
        }
        SECTION("zero-more")
        {
            auto       counter = 0;
            auto const list    = std::list<int>({});
            auto const size    = 1;
            for (auto&& item : enumerate_as<int>(list, size)) {
                assert_same<int, decltype(item.index)>();
                assert_same<decltype(list)::value_type const&, decltype(item.value)>();

                REQUIRE(item.index * 10 == item.value);
                ++counter;
            }
            REQUIRE(counter != size);
            REQUIRE(counter == list.size());
        }
    }
}

#if HIPONY_ENUMERATE_CPP14_OR_GREATER

TEST_CASE("tuple_tag_t")
{
    SECTION("prvalue")
    {
        auto counter = 0;
        enumerate(std::make_tuple(0, 1., "str")).each([&](auto index, auto& value) {
            REQUIRE(index == index_of<typename std::decay<decltype(value)>::type>());
            ++counter;
        });
        REQUIRE(counter == 3);
    }
    SECTION("lvalue")
    {
        auto counter = 0;
        auto tuple   = std::make_tuple(0, 1., "str");
        enumerate(tuple).each([&](auto index, auto& value) {
            assert_same<decltype(index), std::size_t>();

            REQUIRE(index == index_of<typename std::decay<decltype(value)>::type>());
            ++counter;
        });
        REQUIRE(counter == 3);
    }
    SECTION("const")
    {
        auto       counter = 0;
        auto const tuple   = std::make_tuple(0, 1., "str");
        enumerate(tuple).each([&](auto index, auto& value) {
            assert_same<decltype(index), std::size_t>();
            static_assert(
                std::is_const<typename std::remove_reference<decltype(value)>::type>::value,
                "Const propagation is broken");

            REQUIRE(index == index_of<typename std::decay<decltype(value)>::type>());
            ++counter;
        });
        REQUIRE(counter == 3);
    }
    SECTION("as int")
    {
        auto       counter = 0;
        auto const tuple   = std::make_tuple(0, 1., "str");
        enumerate_as<int>(tuple).each([&](auto index, auto& value) {
            assert_same<decltype(index), int>();
            static_assert(
                std::is_const<typename std::remove_reference<decltype(value)>::type>::value,
                "Const propagation is broken");

            REQUIRE(index == index_of<typename std::decay<decltype(value)>::type>());
            ++counter;
        });
        REQUIRE(counter == 3);
    }
}

#endif // HIPONY_ENUMERATE_CPP14_OR_GREATER

TEST_CASE("pointer_tag_t")
{
    SECTION("for-range")
    {
        auto       counter = 0;
        int        ptr[]   = {0, 10, 20, 30, 40};
        auto const size    = sizeof(ptr) / sizeof(int);
        for (auto&& item : enumerate(&ptr[0], size)) {
            assert_same<std::size_t, decltype(item.index)>();
            assert_same<int&, decltype(item.value)>();

            REQUIRE(&ptr[item.index] == &item.value);
            REQUIRE(item.index * 10 == item.value);
            ++counter;
        }
        REQUIRE(counter == 5);
    }
    SECTION("const")
    {
        auto       counter = 0;
        int const  ptr[]   = {0, 10, 20, 30, 40};
        auto const size    = sizeof(ptr) / sizeof(int);
        for (auto&& item : enumerate(&ptr[0], size)) {
            assert_same<std::size_t, decltype(item.index)>();
            assert_same<int const&, decltype(item.value)>();

            REQUIRE(&ptr[item.index] == &item.value);
            REQUIRE(item.index * 10 == item.value);
            ++counter;
        }
        REQUIRE(counter == 5);
    }
    SECTION("as int")
    {
        auto       counter = 0;
        int const  ptr[]   = {0, 10, 20, 30, 40};
        auto const size    = static_cast<int>(sizeof(ptr) / sizeof(int));
        for (auto&& item : enumerate_as<int>(&ptr[0], size)) {
            assert_same<int, decltype(item.index)>();
            assert_same<int const&, decltype(item.value)>();

            REQUIRE(&ptr[item.index] == &item.value);
            REQUIRE(item.index * 10 == item.value);
            ++counter;
        }
        REQUIRE(counter == 5);
    }
#if HIPONY_ENUMERATE_HAS_RANGES && !defined(__clang__)
    SECTION("ranges")
    {
        auto       counter = 0;
        int const  ptr[]   = {0, 10, 20, 30, 40};
        auto const size    = static_cast<int>(sizeof(ptr) / sizeof(int));
        auto const range   = enumerate_as<int>(&ptr[0], size);
        for (auto&& item : range | std::ranges::views::take(3)) {
            assert_same<int, decltype(item.index)>();
            assert_same<int const&, decltype(item.value)>();

            REQUIRE(&ptr[item.index] == &item.value);
            REQUIRE(item.index * 10 == item.value);
            ++counter;
        }
        REQUIRE(counter == 3);
    }
#endif
}

TEST_CASE("string_tag_t")
{
    SECTION("char")
    {
        SECTION("prvalue")
        {
            auto counter = 0;
            for (auto&& item : enumerate("01234")) {
                assert_same<std::size_t, decltype(item.index)>();
                assert_same<char const&, decltype(item.value)>();

                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
        SECTION("lvalue")
        {
            auto counter = 0;
            auto string  = "01234";
            for (auto&& item : enumerate(string)) {
                assert_same<std::size_t, decltype(item.index)>();
                assert_same<char const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value); // NOLINT
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
        SECTION("as int")
        {
            auto counter = 0;
            auto string  = "01234";
            for (auto&& item : enumerate_as<int>(string)) {
                assert_same<int, decltype(item.index)>();
                assert_same<char const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value); // NOLINT
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
#if HIPONY_ENUMERATE_HAS_RANGES && !defined(__clang__)
        SECTION("ranges")
        {
            auto       counter = 0;
            auto       string  = "01234";
            auto const range   = enumerate_as<int>(string);
            for (auto&& item : range | std::ranges::views::take(3)) {
                assert_same<int, decltype(item.index)>();
                assert_same<char const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value); // NOLINT
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 3);
        }
#endif
    }
    SECTION("wchar")
    {
        SECTION("prvalue")
        {
            auto counter = 0;
            for (auto&& item : enumerate(L"01234")) {
                assert_same<std::size_t, decltype(item.index)>();
                assert_same<wchar_t const&, decltype(item.value)>();

                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
        SECTION("lvalue")
        {
            auto counter = 0;
            auto string  = L"01234";
            for (auto&& item : enumerate(string)) {
                assert_same<std::size_t, decltype(item.index)>();
                assert_same<wchar_t const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value); // NOLINT
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
        SECTION("as int")
        {
            auto counter = 0;
            auto string  = L"01234";
            for (auto&& item : enumerate_as<int>(string)) {
                assert_same<int, decltype(item.index)>();
                assert_same<wchar_t const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value); // NOLINT
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
#if HIPONY_ENUMERATE_HAS_RANGES && !defined(__clang__)
        SECTION("ranges")
        {
            auto       counter = 0;
            auto       string  = L"01234";
            auto const range   = enumerate_as<int>(string);
            for (auto&& item : range | std::ranges::views::take(3)) {
                assert_same<int, decltype(item.index)>();
                assert_same<wchar_t const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value); // NOLINT
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 3);
        }
#endif
    }

#if HIPONY_ENUMERATE_HAS_CHAR8
    SECTION("char8")
    {
        SECTION("prvalue")
        {
            auto counter = 0;
            for (auto&& item : enumerate(u8"01234")) {
                assert_same<std::size_t, decltype(item.index)>();
                assert_same<char8_t const&, decltype(item.value)>();

                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
        SECTION("lvalue")
        {
            auto counter = 0;
            auto string  = u8"01234";
            for (auto&& item : enumerate(string)) {
                assert_same<std::size_t, decltype(item.index)>();
                assert_same<char8_t const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value); // NOLINT
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
        SECTION("as int")
        {
            auto counter = 0;
            auto string  = u8"01234";
            for (auto&& item : enumerate_as<int>(string)) {
                assert_same<int, decltype(item.index)>();
                assert_same<char8_t const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value); // NOLINT
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
#if HIPONY_ENUMERATE_HAS_RANGES && !defined(__clang__)
        SECTION("ranges")
        {
            auto       counter = 0;
            auto       string  = u8"01234";
            auto const range   = enumerate_as<int>(string);
            for (auto&& item : range | std::ranges::views::take(3)) {
                assert_same<int, decltype(item.index)>();
                assert_same<char8_t const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value); // NOLINT
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 3);
        }
#endif
    }
#endif // HIPONY_ENUMERATE_HAS_CHAR8

    SECTION("char16")
    {
        SECTION("prvalue")
        {
            auto counter = 0;
            for (auto&& item : enumerate(u"01234")) {
                assert_same<std::size_t, decltype(item.index)>();
                assert_same<char16_t const&, decltype(item.value)>();

                // FIXME: Deduced as an array_tag_t, not string_tag_t
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
        SECTION("lvalue")
        {
            auto counter = 0;
            auto string  = u"01234";
            for (auto&& item : enumerate(string)) {
                assert_same<std::size_t, decltype(item.index)>();
                assert_same<char16_t const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value); // NOLINT
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
        SECTION("as int")
        {
            auto counter = 0;
            auto string  = u"01234";
            for (auto&& item : enumerate_as<int>(string)) {
                assert_same<int, decltype(item.index)>();
                assert_same<char16_t const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value); // NOLINT
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
#if HIPONY_ENUMERATE_HAS_RANGES && !defined(__clang__)
        SECTION("ranges")
        {
            auto       counter = 0;
            auto       string  = u"01234";
            auto const range   = enumerate_as<int>(string);
            for (auto&& item : range | std::ranges::views::take(3)) {
                assert_same<int, decltype(item.index)>();
                assert_same<char16_t const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value); // NOLINT
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 3);
        }
#endif
    }

    SECTION("char32")
    {
        SECTION("prvalue")
        {
            auto counter = 0;
            for (auto&& item : enumerate(U"01234")) {
                assert_same<std::size_t, decltype(item.index)>();
                assert_same<char32_t const&, decltype(item.value)>();

                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
        SECTION("lvalue")
        {
            auto counter = 0;
            auto string  = U"01234";
            for (auto&& item : enumerate(string)) {
                assert_same<std::size_t, decltype(item.index)>();
                assert_same<char32_t const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value); // NOLINT
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
        SECTION("as int")
        {
            auto counter = 0;
            auto string  = U"01234";
            for (auto&& item : enumerate_as<int>(string)) {
                assert_same<int, decltype(item.index)>();
                assert_same<char32_t const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value); // NOLINT
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 5);
        }
#if HIPONY_ENUMERATE_HAS_RANGES && !defined(__clang__)
        SECTION("ranges")
        {
            auto       counter = 0;
            auto       string  = U"01234";
            auto const range   = enumerate_as<int>(string);
            for (auto&& item : range | std::ranges::views::take(3)) {
                assert_same<int, decltype(item.index)>();
                assert_same<char32_t const&, decltype(item.value)>();

                REQUIRE(&string[item.index] == &item.value); // NOLINT
                REQUIRE(item.index + '0' == item.value);
                ++counter;
            }
            REQUIRE(counter == 3);
        }
#endif
    }
}

TEST_CASE("array_tag_t")
{
    // FIXME: The lifetime of the array prvalue will end after the function call returns
    // SECTION("prvalue")
    // {
    //     auto counter = 0;
    //     for (auto&& item : enumerate({0, 10, 20, 30, 40})) {
    //         assert_same<std::size_t, decltype(item.index)>();
    //         assert_same<int&, decltype(item.value)>();

    //         REQUIRE(item.index * 10 == item.value);

    //         ++counter;
    //     }
    //     REQUIRE(counter == 5);
    // }
    SECTION("for-range")
    {
        auto counter     = 0;
        int  container[] = {0, 10, 20, 30, 40};
        for (auto&& item : enumerate(container)) {
            assert_same<std::size_t, decltype(item.index)>();
            assert_same<int&, decltype(item.value)>();

            REQUIRE(&container[item.index] == &item.value);
            REQUIRE(item.index * 10 == item.value);

            ++counter;
        }
        REQUIRE(counter == 5);
    }
    SECTION("const")
    {
        auto      counter     = 0;
        int const container[] = {0, 10, 20, 30, 40};
        for (auto&& item : enumerate(container)) {
            assert_same<std::size_t, decltype(item.index)>();
            assert_same<int const&, decltype(item.value)>();

            REQUIRE(&container[item.index] == &item.value);
            REQUIRE(item.index * 10 == item.value);

            ++counter;
        }
        REQUIRE(counter == 5);
    }
    SECTION("as int")
    {
        auto      counter     = 0;
        int const container[] = {0, 10, 20, 30, 40};
        for (auto&& item : enumerate_as<int>(container)) {
            assert_same<int, decltype(item.index)>();
            assert_same<int const&, decltype(item.value)>();

            REQUIRE(&container[item.index] == &item.value);
            REQUIRE(item.index * 10 == item.value);

            ++counter;
        }
        REQUIRE(counter == 5);
    }
#if HIPONY_ENUMERATE_HAS_RANGES && !defined(__clang__)
    SECTION("ranges")
    {
        auto       counter     = 0;
        int const  container[] = {0, 10, 20, 30, 40};
        auto const range       = enumerate_as<int>(container);
        for (auto&& item : range | std::ranges::views::take(3)) {
            assert_same<int, decltype(item.index)>();
            assert_same<int const&, decltype(item.value)>();

            REQUIRE(&container[item.index] == &item.value);
            REQUIRE(item.index * 10 == item.value);

            ++counter;
        }
        REQUIRE(counter == 3);
    }
#endif
}

#if HIPONY_ENUMERATE_HAS_CONSTEXPR

TEST_CASE("constexpr")
{
    struct function_object {
        constexpr auto operator()() const -> int
        {
            for (auto item : enumerate(as_array, 0, 10, 20, 30, 40)) {
                if (item.index == 3) {
                    return item.value;
                }
            }
            return 0;
        }
    };
    constexpr auto const value = function_object{}();
    REQUIRE(value == 30);
}

#endif

#if HIPONY_ENUMERATE_HAS_AGGREGATES

TEST_CASE("aggregate_tag_t")
{
    struct aggregate_t {
        int         i;
        double      d;
        char const* str;
    };
    SECTION("prvalue")
    {
        auto counter = 0;
        enumerate(aggregate_t{0, 1., "str"}).each([&](auto index, auto& value) {
            REQUIRE(index == index_of<typename std::decay<decltype(value)>::type>());
            ++counter;
        });
        REQUIRE(counter == 3);
    }
    SECTION("lvalue")
    {
        auto counter   = 0;
        auto aggregate = aggregate_t{0, 1., "str"};
        enumerate(aggregate).each([&](auto index, auto& value) {
            assert_same<decltype(index), std::size_t>();

            REQUIRE(index == index_of<typename std::decay<decltype(value)>::type>());
            ++counter;
        });
        REQUIRE(counter == 3);
    }
    SECTION("const")
    {
        auto       counter   = 0;
        auto const aggregate = aggregate_t{0, 1., "str"};
        enumerate(aggregate).each([&](auto index, auto& value) {
            assert_same<decltype(index), std::size_t>();
            static_assert(
                std::is_const<typename std::remove_reference<decltype(value)>::type>::value,
                "Const propagation is broken");

            REQUIRE(index == index_of<typename std::decay<decltype(value)>::type>());
            ++counter;
        });
        REQUIRE(counter == 3);
    }
    SECTION("as int")
    {
        auto       counter   = 0;
        auto const aggregate = aggregate_t{0, 1., "str"};
        enumerate_as<int>(aggregate).each([&](auto index, auto& value) {
            assert_same<decltype(index), int>();
            static_assert(
                std::is_const<typename std::remove_reference<decltype(value)>::type>::value,
                "Const propagation is broken");

            REQUIRE(index == index_of<typename std::decay<decltype(value)>::type>());
            ++counter;
        });
        REQUIRE(counter == 3);
    }
}

#endif

} // namespace HIPONY_ENUMERATE_NAMESPACE
