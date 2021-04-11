// Copyright 2021 Alexandr Timofeev
//
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1.0.txt)

#include <hipony/enumerate.hpp>

#include <catch2/catch.hpp>

#include <array>
#include <map>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace hipony {

namespace {

template<typename T, typename O>
constexpr void assert_type()
{
    static_assert(std::is_same<T, O>::value, "Incorrect type propagation");
}

} // namespace

TEST_CASE("variadic pack", "[enumerate]")
{
    auto counter = 0;
    SECTION("for-range")
    {
        for (auto&& item : enumerate(0, 10, 20, 30, 40)) {
            assert_type<int&, decltype(item.value)>();

            REQUIRE(item.index * 10 == item.value);
            ++counter;
        }
        REQUIRE(counter == 5);
    }
    SECTION("each")
    {
        enumerate(0, 10, 20, 30, 40).each([&](std::size_t index, int& value) {
            REQUIRE(index * 10 == value);
            ++counter;
        });
        REQUIRE(counter == 5);
    }
}

TEST_CASE("tuple", "[enumerate]")
{
    auto counter = std::size_t{0};
    SECTION("exact size")
    {
        enumerate(std::make_tuple(0, 10, 20, 30, 40)).each([&](std::size_t index, int& value) {
            REQUIRE(index * 10 == value);
            ++counter;
        });
        REQUIRE(counter == 5);
    }
    SECTION("more")
    {
        enumerate(std::make_tuple(0, 10, 20, 30, 40), 10).each([&](std::size_t index, int& value) {
            REQUIRE(index * 10 == value);
            ++counter;
        });
        REQUIRE(counter == 5);
    }
    SECTION("less")
    {
        enumerate(std::make_tuple(0, 10, 20, 30, 40), 3).each([&](std::size_t index, int& value) {
            REQUIRE(index * 10 == value);
            ++counter;
        });
        REQUIRE(counter == 3);
    }
    SECTION("lvalue")
    {
        auto tuple = std::make_tuple(0, 10, 20, 30, 40);
        enumerate(tuple).each([&](std::size_t index, int& value) {
            REQUIRE(index * 10 == value);
            ++counter;
        });
        REQUIRE(counter == 3);
    }
    SECTION("const propagation")
    {
        struct const_function_object {
            std::size_t& counter;

            void operator()(std::size_t index, int& value)
            {}
            void operator()(std::size_t index, int const& value)
            {
                REQUIRE(index * 10 == value);
                ++counter;
            }
        };
        auto const tuple = std::make_tuple(0, 10, 20, 30, 40);
        enumerate(tuple).each(const_function_object{counter});
        REQUIRE(counter == 5);
    }
}

TEST_CASE("c-array", "[enumerate]")
{
    auto const size            = 5;
    int        container[size] = {0, 1, 2, 3, 4};

    auto i = 0;
    for (auto&& item : enumerate(container)) {
        static_assert(
            std::is_same<int&, decltype(item.value)>::value, "Incorrect type propagation");

        REQUIRE(i == item.index);
        REQUIRE(i == item.value);

        auto const new_value = static_cast<int>(size - item.index);

        item.value = new_value;
        REQUIRE(container[item.index] == new_value);

        ++i;
    }
}

TEST_CASE("array", "[enumerate]")
{
    auto const container = std::array<double, 5>({0., 1., 2., 3., 4.});

    auto i = 0;
    for (auto&& item : enumerate(container)) {
        static_assert(
            std::is_same<double const&, decltype(item.value)>::value, "Incorrect type propagation");

        REQUIRE(i == item.index);
        REQUIRE(i == item.value);

        ++i;
    }
}

TEST_CASE("vector", "[enumerate]")
{
    auto container = std::vector<double>({0., 1., 2., 3., 4.});

    auto i = 0;
    for (auto&& item : enumerate(container)) {
        static_assert(
            std::is_same<double&, decltype(item.value)>::value, "Incorrect type propagation");

        REQUIRE(i == item.index);
        REQUIRE(i == item.value);

        auto const new_value = static_cast<int>(container.size() - item.index);

        item.value = new_value;
        REQUIRE(container[item.index] == new_value);

        ++i;
    }
}

TEST_CASE("string literal", "[enumerate]")
{
    auto       container = "01234";
    auto const size      = 5;

    auto i = 0;
    for (auto&& item : enumerate(container, size)) {
        static_assert(
            std::is_same<char const&, decltype(item.value)>::value, "Incorrect type propagation");

        REQUIRE(i == item.index);
        REQUIRE('0' + i == item.value);

        ++i;
    }
}

TEST_CASE("string", "[enumerate]")
{
    auto container = std::string("01234");

    auto i = 0;
    for (auto&& item : enumerate(container)) {
        static_assert(
            std::is_same<char&, decltype(item.value)>::value, "Incorrect type propagation");

        REQUIRE(i == item.index);
        REQUIRE('0' + i == item.value);

        auto const new_value = static_cast<char>('0' + container.size() - item.index);

        item.value = new_value;
        REQUIRE(container[item.index] == new_value);

        ++i;
    }
}

TEST_CASE("map", "[enumerate]")
{
    auto container = std::map<int, int>({{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}});

    auto i = 0;
    for (auto&& item : enumerate(container)) {
        static_assert(
            std::is_same<int, decltype(item.value.second)>::value, "Incorrect type propagation");

        REQUIRE(i == item.index);
        REQUIRE(i == item.value.second);

        auto const new_value = static_cast<int>(container.size() - item.index);

        item.value.second = new_value;
        REQUIRE(container[item.index] == new_value);

        ++i;
    }
}

TEST_CASE("unordered_map", "[enumerate]")
{
    auto container
        = std::unordered_map<char, int>({{'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}});

    for (auto&& item : enumerate(container)) {
        static_assert(
            std::is_same<int, decltype(item.value.second)>::value, "Incorrect type propagation");
        (void)item.index;
        (void)item.value;
    }
}

TEST_CASE("array constraint less than size", "[enumerate]")
{
    int        container[] = {0, 1, 2, 3, 4};
    auto const size        = 3;

    auto i = 0;
    for (auto&& item : enumerate(container, size)) {
        static_assert(
            std::is_same<int&, decltype(item.value)>::value, "Incorrect type propagation");
        ++i;
    }
    REQUIRE(i == size);
}

TEST_CASE("array constraint more than size", "[enumerate]")
{
    int const  container[] = {0, 1, 2, 3, 4};
    auto const size        = 8;

    auto i = 0;
    for (auto&& item : enumerate(container, size)) {
        static_assert(
            std::is_same<int const&, decltype(item.value)>::value, "Incorrect type propagation");
        ++i;
    }
    REQUIRE(i == (sizeof(container) / sizeof(int)));
}

TEST_CASE("container constraint less than size", "[enumerate]")
{
    auto       container = std::vector<double>({0., 1., 2., 3., 4.});
    auto const size      = 3;

    auto i = 0;
    for (auto&& item : enumerate(container, size)) {
        static_assert(
            std::is_same<double&, decltype(item.value)>::value, "Incorrect type propagation");
        ++i;
    }
    REQUIRE(i == size);
}

TEST_CASE("container constraint more than size", "[enumerate]")
{
    auto       container = std::vector<double>({0., 1., 2., 3., 4.});
    auto const size      = 8;

    auto i = 0;
    for (auto&& item : enumerate(container, size)) {
        static_assert(
            std::is_same<double&, decltype(item.value)>::value, "Incorrect type propagation");
        ++i;
    }
    REQUIRE(i == container.size());
}

#if HIPONY_ENUMERATE_HAS_CONSTEXPR

TEST_CASE("constexpr", "[enumerate]")
{
    struct function_object {
        constexpr auto operator()() const -> int
        {
            for (auto&& item : enumerate(0, 10, 20, 30, 40)) {
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

} // namespace hipony
