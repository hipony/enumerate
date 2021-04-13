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

#include <cstddef>
#include <iterator>
#include <tuple>
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

#define HIPONY_ENUMERATE_CPP14_OR_GREATER (HIPONY_ENUMERATE_CPLUSPLUS >= 201402L)
#define HIPONY_ENUMERATE_CPP17_OR_GREATER (HIPONY_ENUMERATE_CPLUSPLUS >= 201703L)

#define HIPONY_ENUMERATE_HAS_CONSTEXPR HIPONY_ENUMERATE_CPP14_OR_GREATER
#define HIPONY_ENUMERATE_HAS_NODISCARD HIPONY_ENUMERATE_CPP17_OR_GREATER

#if HIPONY_ENUMERATE_HAS_CONSTEXPR
#define HIPONY_ENUMERATE_CONSTEXPR constexpr
#else
#define HIPONY_ENUMERATE_CONSTEXPR /*constexpr*/
#endif

#if HIPONY_ENUMERATE_HAS_NODISCARD
#define HIPONY_ENUMERATE_NODISCARD [[nodiscard]]
#else
#define HIPONY_ENUMERATE_NODISCARD /*[[nodiscard]]*/
#endif

namespace HIPONY_ENUMERATE_NAMESPACE {

namespace hipony_enumerate {

namespace detail {

template<typename T>
constexpr auto is_same() noexcept -> bool
{
    return true;
}

template<typename T, typename First, typename... Tail>
constexpr auto is_same() noexcept -> bool
{
    return std::is_same<T, First>::value && detail::is_same<T, Tail...>();
}

template<typename... Ts>
struct make_void {
    using type = void;
};

template<typename... Ts>
using make_void_t = typename detail::make_void<Ts...>::type;

template<typename T>
using remove_cvref_t = typename std::remove_reference<typename std::remove_cv<T>::type>::type;

template<typename T>
struct remove_rvalue_reference {
    using type = T;
};

template<typename T>
struct remove_rvalue_reference<T&> {
    using type = T&;
};

template<typename T>
struct remove_rvalue_reference<T&&> {
    using type = T;
};

template<typename T>
using remove_rref_t = typename remove_rvalue_reference<T>::type;

template<typename T, typename = void>
struct is_container : std::false_type {};

template<typename T>
struct is_container<
    T,
    typename detail::make_void<
        decltype(std::begin(std::declval<T>())),
        decltype(std::end(std::declval<T>())),
        decltype(std::declval<T>().size())>::type> : std::true_type {};

template<typename T, typename = void>
struct is_tuple : std::false_type {};

template<typename T>
struct is_tuple<
    T,
    typename detail::make_void<
        decltype(std::tuple_size<T>::value),
        decltype(std::get<0>(std::declval<T>()))>::type> : std::true_type {};

template<typename It>
HIPONY_ENUMERATE_CONSTEXPR auto do_next(
    It                                                 it,
    typename std::iterator_traits<It>::difference_type n,
    std::input_iterator_tag                            tag) noexcept -> It
{
    return (n > 0) ? do_next(++it, --n, tag) : it;
}

template<typename It>
HIPONY_ENUMERATE_CONSTEXPR auto do_advance(
    It                                                 it,
    typename std::iterator_traits<It>::difference_type n,
    std::bidirectional_iterator_tag                    tag) noexcept -> It
{
    return (n > 0) ? do_next(++it, --n, tag) : ((n < 0) ? do_next(--it, ++n, tag) : it);
}

template<typename It>
HIPONY_ENUMERATE_CONSTEXPR auto do_advance(
    It                                                 it,
    typename std::iterator_traits<It>::difference_type n,
    std::random_access_iterator_tag) noexcept -> It
{
    return it + n;
}

template<typename It>
HIPONY_ENUMERATE_CONSTEXPR auto
next(It it, typename std::iterator_traits<It>::difference_type n) noexcept -> It
{
    return detail::do_next(
        it,
        typename std::iterator_traits<It>::difference_type(n),
        typename std::iterator_traits<It>::iterator_category());
}

template<typename T>
class span {
public:
    using value_type      = T;
    using pointer         = T*;
    using reference       = T&;
    using const_reference = const T&;
    using iterator        = T*;
    using const_iterator  = T*;
    using difference_type = typename std::iterator_traits<iterator>::difference_type;
    using size_type       = typename std::make_unsigned<difference_type>::type;

private:
    pointer   _ptr;
    size_type _size;

public:
    HIPONY_ENUMERATE_CONSTEXPR span(pointer ptr, size_type size)
        : _ptr{ptr}
        , _size{size}
    {}

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() const noexcept
        -> const_iterator
    {
        return _ptr;
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() const noexcept
        -> const_iterator
    {
        return _ptr + _size;
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto size() const noexcept -> size_type
    {
        return _size;
    }
};

template<typename T, typename std::iterator_traits<T*>::difference_type N>
struct array {
    using value_type      = T;
    using pointer         = T*;
    using reference       = T&;
    using const_reference = const T&;
    using iterator        = T*;
    using const_iterator  = T const*;
    using difference_type = typename std::iterator_traits<iterator>::difference_type;
    using size_type       = typename std::make_unsigned<difference_type>::type;

    value_type data[N];

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() noexcept -> iterator
    {
        return data;
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() noexcept -> iterator
    {
        return data + N;
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() const noexcept
        -> const_iterator
    {
        return data;
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() const noexcept
        -> const_iterator
    {
        return data + N;
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto size() const noexcept -> size_type
    {
        return N;
    }
};

template<typename T, typename IndexType>
struct iterator_value {
    using index_type = IndexType;
    using value_type = T;

    index_type index;
    value_type value;

    HIPONY_ENUMERATE_NODISCARD friend HIPONY_ENUMERATE_CONSTEXPR auto
    operator==(iterator_value const& lhs, iterator_value const& rhs) noexcept -> bool
    {
        return lhs.index == rhs.index && lhs.value == rhs.value;
    }

    HIPONY_ENUMERATE_NODISCARD friend HIPONY_ENUMERATE_CONSTEXPR auto
    operator!=(iterator_value const& lhs, iterator_value const& rhs) noexcept -> bool
    {
        return !(lhs == rhs);
    }
};

template<typename Container>
class iterator {
public:
    using inner_iterator  = decltype(std::declval<Container>().begin());
    using inner_reference = decltype(*inner_iterator{});

    using iterator_category = std::forward_iterator_tag;
    using difference_type   = typename detail::remove_cvref_t<Container>::difference_type;
    using size_type         = typename detail::remove_cvref_t<Container>::size_type;
    using value_type        = iterator_value<inner_reference, size_type>;
    using pointer           = iterator_value<inner_reference, size_type>;
    using reference         = iterator_value<inner_reference, size_type>;

private:
    size_type      _index;
    inner_iterator _iterator;

public:
    HIPONY_ENUMERATE_CONSTEXPR iterator(inner_iterator iterator)
        : _index{0}
        , _iterator{static_cast<decltype(iterator)&&>(iterator)}
    {}

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto operator*() noexcept -> reference
    {
        return {_index, *_iterator};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto operator*() const noexcept
        -> reference
    {
        return {_index, *_iterator};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto operator->() noexcept -> pointer
    {
        return {_index, *_iterator};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto operator->() const noexcept
        -> pointer
    {
        return {_index, *_iterator};
    }

    HIPONY_ENUMERATE_CONSTEXPR auto operator++() noexcept -> iterator&
    {
        _iterator++;
        _index++;
        return *this;
    }

    HIPONY_ENUMERATE_NODISCARD auto operator++(int) noexcept -> iterator
    {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    HIPONY_ENUMERATE_NODISCARD friend HIPONY_ENUMERATE_CONSTEXPR auto
    operator==(iterator const& lhs, iterator const& rhs) noexcept -> bool
    {
        return lhs._iterator == rhs._iterator;
    }

    HIPONY_ENUMERATE_NODISCARD friend HIPONY_ENUMERATE_CONSTEXPR auto
    operator!=(iterator const& lhs, iterator const& rhs) noexcept -> bool
    {
        return !(lhs == rhs);
    }
};

template<typename Container>
struct wrapper {
    using value_type = typename detail::remove_rref_t<Container>;
    using size_type  = typename detail::remove_cvref_t<Container>::size_type;

    value_type data;
    size_type  size;

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() noexcept
        -> iterator<value_type>
    {
        return {data.begin()};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() noexcept
        -> iterator<value_type>
    {
        return {data.size() < size ? data.end() : detail::next(data.begin(), size)};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() const noexcept
        -> iterator<value_type>
    {
        return {data.begin()};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() const noexcept
        -> iterator<Container>
    {
        return {data.size() < size ? data.end() : detail::next(data.begin(), size)};
    }

    template<typename F>
    HIPONY_ENUMERATE_CONSTEXPR void each(F&& f)
    {
        for (auto&& item : *this) {
            f(item.index, item.value);
        }
    }
};

template<typename Tuple, typename... U>
struct tuple_wrapper {
    using tuple_type = detail::remove_rref_t<Tuple>;
    using size_type  = decltype(std::tuple_size<detail::remove_cvref_t<tuple_type>>::value);

    tuple_type data;
    size_type  size;

    template<typename F>
    HIPONY_ENUMERATE_CONSTEXPR void each(F&& f)
    {
        do_each<F, 0, U...>(static_cast<F&&>(f));
    }

private:
    template<typename F, size_type N>
    HIPONY_ENUMERATE_CONSTEXPR void do_each(F&& /*f*/)
    {}

    template<typename F, size_type N, typename Arg, typename... Args>
    HIPONY_ENUMERATE_CONSTEXPR void do_each(F&& f)
    {
        if (N < size) {
            f(N, std::get<N>(data));
            do_each<F, N + 1, Args...>(static_cast<F&&>(f));
        }
    }
};

template<typename T>
struct enumerate_traits;

template<template<typename...> class T, typename... Args>
struct enumerate_traits<T<Args...>> {
    using wrapper = tuple_wrapper<T<Args...>, Args...>;
};

template<template<typename...> class T, typename... Args>
struct enumerate_traits<T<Args...>&> {
    using wrapper = tuple_wrapper<T<Args...>&, Args...>;
};

template<template<typename...> class T, typename... Args>
struct enumerate_traits<T<Args...> const&> {
    using wrapper = tuple_wrapper<T<Args...> const&, Args...>;
};

template<template<typename...> class T, typename... Args>
struct enumerate_traits<T<Args...>&&> {
    using wrapper = tuple_wrapper<T<Args...>&&, Args...>;
};

template<template<typename...> class T, typename... Args>
struct enumerate_traits<T<Args...> const&&> {
    using wrapper = tuple_wrapper<T<Args...> const&&, Args...>;
};

} // namespace detail

template<typename Container>
HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto enumerate(Container&& c) noexcept ->
    typename std::enable_if<
        detail::is_container<detail::remove_cvref_t<decltype(c)>>::value,
        detail::wrapper<detail::remove_rref_t<decltype(c)>>>::type
{
    return {static_cast<decltype(c)&&>(c), c.size()};
}

template<typename Container>
HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto
enumerate(Container&& c, std::size_t n) noexcept -> typename std::enable_if<
    detail::is_container<detail::remove_cvref_t<decltype(c)>>::value,
    detail::wrapper<detail::remove_rref_t<decltype(c)>>>::type
{
    return {static_cast<decltype(c)&&>(c), n};
}

template<typename Tuple>
HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto enumerate(Tuple&& t) noexcept ->
    typename std::enable_if<
        detail::is_tuple<detail::remove_cvref_t<decltype(t)>>::value
            && !detail::is_container<detail::remove_cvref_t<decltype(t)>>::value,
        typename detail::enumerate_traits<Tuple>::wrapper>::type
{
    return {
        static_cast<decltype(t)&&>(t), std::tuple_size<detail::remove_cvref_t<decltype(t)>>::value};
}

template<typename Tuple>
HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto
enumerate(Tuple&& t, std::size_t n) noexcept -> typename std::enable_if<
    detail::is_tuple<detail::remove_cvref_t<decltype(t)>>::value
        && !detail::is_container<detail::remove_cvref_t<decltype(t)>>::value,
    typename detail::enumerate_traits<Tuple>::wrapper>::type
{
    return {static_cast<decltype(t)&&>(t), n};
}

template<typename T>
HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto
enumerate(T* const& ptr, std::size_t n) noexcept -> detail::wrapper<detail::span<T>>
{
    return {{ptr, n}, n};
}

template<typename T, std::size_t N>
HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto enumerate(T (&arr)[N]) noexcept
    -> detail::wrapper<detail::span<T>>
{
    return {{arr, N}, N};
}

template<typename T, std::size_t N>
HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto
enumerate(T (&arr)[N], std::size_t n) noexcept -> detail::wrapper<detail::span<T>>
{
    return {{arr, N}, n};
}

// template<typename T, typename... Args>
// HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto
// enumerate(T&& first, Args&&... args) noexcept -> typename std::enable_if<
//     !detail::is_same<detail::remove_cvref_t<T>, detail::remove_cvref_t<Args>...>()
//         && !detail::is_tuple<detail::remove_cvref_t<T>>::value,
//     detail::tuple_wrapper<std::tuple<T, Args...>>>::type
// {
//     return {static_cast<T&&>(first), static_cast<Args&&>(args)...};
// }

template<typename T, typename... Args>
HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto
enumerate(T&& first, Args&&... args) noexcept -> typename std::enable_if<
    detail::is_same<detail::remove_cvref_t<T>, detail::remove_cvref_t<Args>...>()
        && !detail::is_tuple<detail::remove_cvref_t<T>>::value,
    detail::wrapper<detail::array<T, sizeof...(Args) + 1>>>::type
{
    return {{static_cast<T&&>(first), static_cast<Args&&>(args)...}, sizeof...(Args) + 1};
}

} // namespace hipony_enumerate

using hipony_enumerate::enumerate;

} // namespace HIPONY_ENUMERATE_NAMESPACE

#endif
