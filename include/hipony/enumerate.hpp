//
// enumerate for C++11 and later.
// For more information see https://github.com/hipony/enumerate
//
// Copyright 2021 Alexandr Timofeev
//
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1.0.txt)

#ifndef HIPONY_ENUMERATE_HPP_INCLUDED
#define HIPONY_ENUMERATE_HPP_INCLUDED

#include <array>
#include <cstddef>
#include <iterator>
#include <type_traits>

#ifndef HIPONY_ENUMERATE_NAMESPACE
#define HIPONY_ENUMERATE_NAMESPACE hipony
#endif

#ifndef HIPONY_ENUMERATE_CPLUSPLUS
#if defined(_MSVC_LANG) && !defined(__clang__)
#define HIPONY_ENUMERATE_CPLUSPLUS (_MSC_VER == 1900 ? 201103L : _MSVC_LANG)
#else
#define HIPONY_ENUMERATE_CPLUSPLUS __cplusplus
#endif
#endif

#define HIPONY_ENUMERATE_CPP17_OR_GREATER (HIPONY_ENUMERATE_CPLUSPLUS >= 201703L)

#define HIPONY_ENUMERATE_HAS_NODISCARD HIPONY_ENUMERATE_CPP17_OR_GREATER

#if HIPONY_ENUMERATE_HAS_NODISCARD
#define HIPONY_ENUMERATE_NODISCARD [[nodiscard]]
#else
#define HIPONY_ENUMERATE_NODISCARD /*[[nodiscard]]*/
#endif

namespace HIPONY_ENUMERATE_NAMESPACE {

namespace hipony_enumerate {

namespace detail {

template<typename T>
class span {
public:
    using pointer   = T*;
    using size_type = std::size_t;
    using iterator  = pointer;

private:
    pointer   _ptr;
    size_type _size;

public:
    span(pointer ptr, size_type size)
        : _ptr{ptr}
        , _size{size}
    {}

    HIPONY_ENUMERATE_NODISCARD auto begin() const -> iterator
    {
        return _ptr;
    }

    HIPONY_ENUMERATE_NODISCARD auto end() const -> iterator
    {
        return _ptr + _size;
    }

    HIPONY_ENUMERATE_NODISCARD auto size() const -> size_type
    {
        return _size;
    }
};

template<typename T>
struct iterator_value {
    std::size_t index;
    T           value;

    HIPONY_ENUMERATE_NODISCARD friend auto
    operator==(iterator_value const& lhs, iterator_value const& rhs) -> bool
    {
        return lhs.index == rhs.index && lhs.value == rhs.value;
    }

    HIPONY_ENUMERATE_NODISCARD friend auto
    operator!=(iterator_value const& lhs, iterator_value const& rhs) -> bool
    {
        return !(lhs == rhs);
    }
};

template<typename Container>
class iterator {
public:
    using inner_iterator  = decltype(std::begin(std::declval<Container>()));
    using inner_reference = decltype(*inner_iterator{});

    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = iterator_value<inner_reference>;
    using pointer           = iterator_value<inner_reference>;
    using reference         = iterator_value<inner_reference>;

private:
    std::size_t    _index{};
    inner_iterator _iterator{};

public:
    iterator(inner_iterator iterator)
        : _iterator{std::move(iterator)}
    {}

    HIPONY_ENUMERATE_NODISCARD auto operator*() const -> reference
    {
        return {_index, *_iterator};
    }

    HIPONY_ENUMERATE_NODISCARD auto operator-> () -> pointer
    {
        return {_index, *_iterator};
    }

    auto operator++() -> iterator&
    {
        _iterator++;
        _index++;
        return *this;
    }

    HIPONY_ENUMERATE_NODISCARD auto operator++(int) -> iterator
    {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    HIPONY_ENUMERATE_NODISCARD friend auto operator==(iterator const& lhs, iterator const& rhs)
        -> bool
    {
        return lhs._iterator == rhs._iterator;
    }

    HIPONY_ENUMERATE_NODISCARD friend auto operator!=(iterator const& lhs, iterator const& rhs)
        -> bool
    {
        return !(lhs == rhs);
    }
};

template<typename Container>
struct wrapper {
    Container   data;
    std::size_t size;

    HIPONY_ENUMERATE_NODISCARD auto begin() -> iterator<Container>
    {
        return {std::begin(data)};
    }

    HIPONY_ENUMERATE_NODISCARD auto end() -> iterator<Container>
    {
        return {data.size() < size ? std::end(data) : std::next(std::begin(data), size)};
    }
};

template<typename T>
constexpr auto is_same() -> bool
{
    return true;
}

template<typename T, typename First, typename... Tail>
constexpr auto is_same() -> bool
{
    return std::is_same<T, First>::value && detail::is_same<T, Tail...>();
}

template<typename T>
using remove_cvref_t = typename std::remove_reference<typename std::remove_cv<T>::type>::type;

} // namespace detail

template<typename Container>
HIPONY_ENUMERATE_NODISCARD auto enumerate(Container&& c) -> detail::wrapper<decltype(c)>
{
    return {static_cast<decltype(c)&&>(c), c.size()};
}

template<typename Container>
HIPONY_ENUMERATE_NODISCARD auto enumerate(Container&& c, std::size_t n) -> typename std::enable_if<
    !std::is_pointer<detail::remove_cvref_t<Container>>::value,
    detail::wrapper<decltype(c)>>::type
{
    return {static_cast<decltype(c)&&>(c), n};
}

template<typename T>
HIPONY_ENUMERATE_NODISCARD auto enumerate(T ptr, std::size_t n) -> typename std::enable_if<
    std::is_pointer<detail::remove_cvref_t<T>>::value,
    detail::wrapper<detail::span<typename std::remove_pointer<T>::type>>>::type
{
    return {{ptr, n}, n};
}

template<typename T, typename... Args>
HIPONY_ENUMERATE_NODISCARD auto enumerate(T first, Args... args) -> typename std::enable_if<
    detail::is_same<T, Args...>(),
    detail::wrapper<std::array<T, sizeof...(Args) + 1>>>::type
{
    return {{static_cast<T&&>(first), static_cast<Args&&>(args)...}, sizeof...(Args) + 1};
}

template<typename T, std::size_t N>
HIPONY_ENUMERATE_NODISCARD auto enumerate(T (&arr)[N]) -> detail::wrapper<detail::span<T>>
{
    return {{arr, N}, N};
}

template<typename T, std::size_t N>
HIPONY_ENUMERATE_NODISCARD auto enumerate(T (&arr)[N], std::size_t n)
    -> detail::wrapper<detail::span<T>>
{
    return {{arr, N}, n};
}

} // namespace hipony_enumerate

using hipony_enumerate::enumerate;

} // namespace HIPONY_ENUMERATE_NAMESPACE

#endif
