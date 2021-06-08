// Copyright 2021 Alexandr Timofeev
//
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1.0.txt)

#include <hipony/enumerate.hpp>

#include <array>
#include <map>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace HIPONY_ENUMERATE_NAMESPACE {
namespace hipony_enumerate {

// Traits

static_assert(std::is_same<detail::remove_cvref_t<int>, int>::value, "");
static_assert(std::is_same<detail::remove_cvref_t<int&>, int>::value, "");
static_assert(std::is_same<detail::remove_cvref_t<int&&>, int>::value, "");
static_assert(std::is_same<detail::remove_cvref_t<int const&>, int>::value, "");
static_assert(std::is_same<detail::remove_cvref_t<int const&&>, int>::value, "");
static_assert(std::is_same<detail::remove_cvref_t<int*>, int*>::value, "");
static_assert(std::is_same<detail::remove_cvref_t<int*&>, int*>::value, "");
static_assert(std::is_same<detail::remove_cvref_t<int const*>, int const*>::value, "");
static_assert(std::is_same<detail::remove_cvref_t<int const*&&>, int const*>::value, "");
static_assert(std::is_same<detail::remove_cvref_t<char const*&>, char const*>::value, "");

static_assert(std::is_same<detail::remove_rref_t<int>, int>::value, "");
static_assert(std::is_same<detail::remove_rref_t<int&>, int&>::value, "");
static_assert(std::is_same<detail::remove_rref_t<int&&>, int>::value, "");
static_assert(std::is_same<detail::remove_rref_t<int const&>, int const&>::value, "");
static_assert(std::is_same<detail::remove_rref_t<int const&&>, int const>::value, "");
static_assert(std::is_same<detail::remove_rref_t<int*>, int*>::value, "");
static_assert(std::is_same<detail::remove_rref_t<int*&>, int*&>::value, "");
static_assert(std::is_same<detail::remove_rref_t<int const*>, int const*>::value, "");
static_assert(std::is_same<detail::remove_rref_t<int const*&&>, int const*>::value, "");

static_assert(!detail::is_container<int>::value, "");
static_assert(!detail::is_container<int[2]>::value, "");
static_assert(detail::is_container<std::array<int, 1>>::value, "");
static_assert(detail::is_container<std::vector<int>>::value, "");
static_assert(detail::is_container<std::map<int, int>>::value, "");
static_assert(detail::is_container<std::string>::value, "");
static_assert(!detail::is_container<std::tuple<int, double>>::value, "");
static_assert(!detail::is_container<std::pair<int, double>>::value, "");

static_assert(!detail::is_tuple<int>::value, "");
static_assert(detail::is_tuple<std::array<int, 1>>::value, "");
static_assert(!detail::is_tuple<std::vector<int>>::value, "");
static_assert(!detail::is_tuple<std::map<int, int>>::value, "");
static_assert(!detail::is_tuple<std::string>::value, "");
static_assert(detail::is_tuple<std::tuple<int, double>>::value, "");
static_assert(detail::is_tuple<std::pair<int, double>>::value, "");

// Size inference

static_assert(std::is_same<detail::size_t<void, std::vector<int>>, std::size_t>::value, "");
static_assert(std::is_same<detail::size_t<void, std::array<int, 4>>, std::size_t>::value, "");
static_assert(std::is_same<detail::size_t<void, std::string>, std::size_t>::value, "");
static_assert(std::is_same<detail::size_t<void, std::tuple<int, float>>, std::size_t>::value, "");
static_assert(std::is_same<detail::size_t<int, std::tuple<int, float>>, int>::value, "");

namespace {
struct user_container {
    int* _begin;
    int* _end;
    using size_type = int;
    auto begin() const -> int*
    {
        return _begin;
    }
    auto end() const -> int*
    {
        return _end;
    }
    auto size() const -> size_type
    {
        return _end - _begin;
    }
};
} // namespace

static_assert(std::is_same<detail::size_t<void, user_container>, int>::value, "");
static_assert(std::is_same<detail::size_t<std::size_t, user_container>, std::size_t>::value, "");

// Tag inference

static_assert(std::is_same<detail::tag_t<std::size_t, int>, detail::variadic_tag_t>::value, "");
static_assert(
    std::is_same<detail::tag_t<std::size_t, int, void, std::string>, detail::variadic_tag_t>::value,
    "");

static_assert(
    std::is_same<detail::tag_t<std::size_t, int, void, int>, detail::variadic_array_tag_t>::value,
    "");

static_assert(
    std::is_same<detail::tag_t<std::size_t, std::vector<int>>, detail::container_tag_t>::value,
    "");
static_assert(
    std::is_same<detail::tag_t<std::size_t, std::array<int, 4>>, detail::container_tag_t>::value,
    "");
static_assert(
    std::is_same<detail::tag_t<std::size_t, std::string>, detail::container_tag_t>::value,
    "");
static_assert(
    std::is_same<detail::tag_t<std::size_t, std::map<int, int>>, detail::container_tag_t>::value,
    "");

static_assert(
    std::is_same<detail::tag_t<std::size_t, std::tuple<int, int>>, detail::tuple_tag_t>::value,
    "");
static_assert(
    std::is_same<detail::tag_t<std::size_t, std::pair<int, int>>, detail::tuple_tag_t>::value,
    "");

static_assert(
    std::is_same<detail::tag_t<std::size_t, int*, void, int>, detail::pointer_tag_t>::value,
    "");
static_assert(
    std::is_same<detail::tag_t<std::size_t, char*, void, int>, detail::pointer_tag_t>::value,
    "");
static_assert(
    std::is_same<detail::tag_t<std::size_t, char const*, void, int>, detail::pointer_tag_t>::value,
    "");
static_assert(
    std::is_same<detail::tag_t<std::size_t, char const*, void, int const>, detail::pointer_tag_t>::
        value,
    "");

static_assert(
    std::is_same<detail::tag_t<std::size_t, char const*>, detail::string_tag_t>::value,
    "");
static_assert(
    std::is_same<detail::tag_t<std::size_t, wchar_t const*>, detail::string_tag_t>::value,
    "");
static_assert(
    std::is_same<detail::tag_t<std::size_t, char16_t const*>, detail::string_tag_t>::value,
    "");
static_assert(
    std::is_same<detail::tag_t<std::size_t, char32_t const*>, detail::string_tag_t>::value,
    "");

static_assert(std::is_same<detail::tag_t<std::size_t, int[3]>, detail::array_tag_t>::value, "");
static_assert(
    std::is_same<detail::tag_t<std::size_t, int[3], void, std::size_t>, detail::array_tag_t>::value,
    "");

// Returned type

static_assert(detail::is_container<decltype(enumerate(0, 1, 2, 3, 4))>::value, "");
// static_assert(detail::is_container<decltype(enumerate({0, 1, 2, 3, 4}))>::value, "");
static_assert(!detail::is_container<decltype(enumerate(0, 1., "string"))>::value, "");
static_assert(
    detail::is_container<decltype(enumerate(std::declval<std::vector<int>>()))>::value,
    "");
static_assert(
    detail::is_container<decltype(enumerate(std::declval<std::array<int, 3>>()))>::value,
    "");
static_assert(
    !detail::is_container<decltype(enumerate(std::declval<std::tuple<int, int>>()))>::value,
    "");
static_assert(
    !detail::is_container<decltype(enumerate(std::declval<std::pair<int, int>>()))>::value,
    "");
static_assert(
    detail::is_container<
        decltype(enumerate(std::declval<int*>(), std::declval<std::size_t>()))>::value,
    "");
static_assert(detail::is_container<decltype(enumerate("123456"))>::value, "");
static_assert(
    detail::is_container<decltype(enumerate("123456", std::declval<std::size_t>()))>::value,
    "");
static_assert(detail::is_container<decltype(enumerate(std::declval<int (&)[5]>()))>::value, "");
static_assert(
    detail::is_container<
        decltype(enumerate(std::declval<int (&)[5]>(), std::declval<std::size_t>()))>::value,
    "");

static_assert(detail::is_container<decltype(enumerate_as<int>(0, 1, 2, 3, 4))>::value, "");
static_assert(!detail::is_container<decltype(enumerate_as<int>(0, 1., "string"))>::value, "");
static_assert(
    detail::is_container<decltype(enumerate_as<int>(std::declval<std::vector<int>>()))>::value,
    "");
static_assert(
    detail::is_container<decltype(enumerate_as<int>(std::declval<std::array<int, 3>>()))>::value,
    "");
static_assert(
    !detail::is_container<decltype(enumerate_as<int>(std::declval<std::tuple<int, int>>()))>::value,
    "");
static_assert(
    !detail::is_container<decltype(enumerate_as<int>(std::declval<std::pair<int, int>>()))>::value,
    "");
static_assert(
    detail::is_container<
        decltype(enumerate_as<int>(std::declval<int*>(), std::declval<int>()))>::value,
    "");
static_assert(detail::is_container<decltype(enumerate_as<int>("123456"))>::value, "");
static_assert(
    detail::is_container<decltype(enumerate_as<int>("123456", std::declval<int>()))>::value,
    "");
static_assert(
    detail::is_container<decltype(enumerate_as<int>(std::declval<int (&)[5]>()))>::value,
    "");
static_assert(
    detail::is_container<
        decltype(enumerate_as<int>(std::declval<int (&)[5]>(), std::declval<int>()))>::value,
    "");

} // namespace hipony_enumerate
} // namespace HIPONY_ENUMERATE_NAMESPACE
