// Copyright 2021 Alexandr Timofeev
//
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1.0.txt)

#include <hipony/enumerate.hpp>

#include <catch2/catch.hpp>

#include <array>
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

TEST_CASE("variadic_tag_t", "[enumerate]")
{
    SECTION("each")
    {
        auto counter = 0;
        enumerate(0, 1., "str").each([&](auto index, auto& value) {
            assert_same<decltype(index), std::size_t>();

            REQUIRE(index == index_of<typename std::decay<decltype(value)>::type>());
            ++counter;
        });
        REQUIRE(counter == 3);
    }
    SECTION("each as int")
    {
        auto counter = 0;
        enumerate_as<int>(0, 1., "str").each([&](auto index, auto& value) {
            assert_same<decltype(index), int>();

            REQUIRE(index == index_of<typename std::decay<decltype(value)>::type>());
            ++counter;
        });
        REQUIRE(counter == 3);
    }
}

#endif // HIPONY_ENUMERATE_CPP14_OR_GREATER

TEST_CASE("variadic_array_tag_t", "[enumerate]")
{
    SECTION("for-range")
    {
        auto counter = 0;
        for (auto&& item : enumerate(0, 10, 20, 30, 40)) {
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
        for (auto&& item : enumerate_as<int>(0, 10, 20, 30, 40)) {
            assert_same<int, decltype(item.index)>();
            assert_same<int&, decltype(item.value)>();

            REQUIRE(item.index * 10 == item.value);
            ++counter;
        }
        REQUIRE(counter == 5);
    }
}

TEST_CASE("container_tag_t", "[enumerate]")
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
    }
}

#if HIPONY_ENUMERATE_CPP14_OR_GREATER

TEST_CASE("tuple_tag_t", "[enumerate]")
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

TEST_CASE("pointer_tag_t", "[enumerate]")
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
}

TEST_CASE("string_tag_t", "[enumerate]")
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
    }

#if HIPONY_ENUMERATE_CPP20_OR_GREATER
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
    }
#endif // HIPONY_ENUMERATE_CPP20_OR_GREATER

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
    }
}

TEST_CASE("", "[enumerate]")
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

} // namespace HIPONY_ENUMERATE_NAMESPACE
