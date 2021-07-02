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

#include <cassert>
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
#define HIPONY_ENUMERATE_CPP20_OR_GREATER (HIPONY_ENUMERATE_CPLUSPLUS >= 202002L)

#if defined(_MSC_VER)
#define HIPONY_ENUMERATE_HAS_CONSTEXPR_MSVC (_MSC_VER > 1916)
#else
#define HIPONY_ENUMERATE_HAS_CONSTEXPR_MSVC true
#endif

#if defined(__cpp_constexpr)
#define HIPONY_ENUMERATE_HAS_CONSTEXPR \
    ((__cpp_constexpr >= 201304L) && HIPONY_ENUMERATE_HAS_CONSTEXPR_MSVC)
#else
#define HIPONY_ENUMERATE_HAS_CONSTEXPR \
    (HIPONY_ENUMERATE_CPP14_OR_GREATER && HIPONY_ENUMERATE_HAS_CONSTEXPR_MSVC)
#endif

#if HIPONY_ENUMERATE_HAS_CONSTEXPR
#define HIPONY_ENUMERATE_CONSTEXPR constexpr
#else
#define HIPONY_ENUMERATE_CONSTEXPR /*constexpr*/
#endif

#if defined(__cpp_if_constexpr)
#define HIPONY_ENUMERATE_HAS_IF_CONSTEXPR (__cpp_if_constexpr >= 201606L)
#else
#define HIPONY_ENUMERATE_HAS_IF_CONSTEXPR false
#endif

#if defined(__has_cpp_attribute)
#define HIPONY_ENUMERATE_HAS_NODISCARD __has_cpp_attribute(nodiscard)
#else
#define HIPONY_ENUMERATE_HAS_NODISCARD HIPONY_ENUMERATE_CPP17_OR_GREATER
#endif

#if HIPONY_ENUMERATE_HAS_NODISCARD
#define HIPONY_ENUMERATE_NODISCARD [[nodiscard]]
#else
#define HIPONY_ENUMERATE_NODISCARD /*[[nodiscard]]*/
#endif

#if defined(__has_cpp_attribute)
#define HIPONY_ENUMERATE_HAS_MAYBE_UNUSED __has_cpp_attribute(maybe_unused)
#else
#define HIPONY_ENUMERATE_HAS_MAYBE_UNUSED HIPONY_ENUMERATE_CPP17_OR_GREATER
#endif

#if HIPONY_ENUMERATE_HAS_MAYBE_UNUSED
#define HIPONY_ENUMERATE_MAYBE_UNUSED [[maybe_unused]]
#else
#define HIPONY_ENUMERATE_MAYBE_UNUSED /*[[maybe_unused]]*/
#endif

#if defined(__cpp_char8_t)
#define HIPONY_ENUMERATE_HAS_CHAR8 (__cpp_char8_t >= 201811L)
#else
#define HIPONY_ENUMERATE_HAS_CHAR8 HIPONY_ENUMERATE_CPP20_OR_GREATER
#endif

#if defined(__has_include) && __has_include(<version>)
#include <version>
#endif

#if defined(__cpp_lib_concepts)
#define HIPONY_ENUMERATE_HAS_CONCEPTS (__cpp_lib_concepts >= 202002L)
#else
#define HIPONY_ENUMERATE_HAS_CONCEPTS false
#endif

#if HIPONY_ENUMERATE_HAS_CONCEPTS
#include <concepts>
#endif

#if defined(__cpp_lib_ranges)
#define HIPONY_ENUMERATE_HAS_RANGES (__cpp_lib_ranges >= 201911L)
#else
#define HIPONY_ENUMERATE_HAS_RANGES false
#endif

#if HIPONY_ENUMERATE_HAS_RANGES
#include <ranges>
#endif

#if HIPONY_ENUMERATE_AGGREGATES_ENABLED
#if !HIPONY_ENUMERATE_CPP17_OR_GREATER
#error Full C++17 support is required to use the Aggregates feature
#endif
#include <boost/pfr.hpp>
#define HIPONY_ENUMERATE_HAS_AGGREGATES 1
#else
#define HIPONY_ENUMERATE_HAS_AGGREGATES 0
#endif

namespace HIPONY_ENUMERATE_NAMESPACE {

#if !defined(HIPONY_AS_ARRAY_HPP_INCLUDED) || HIPONY_ENUMERATE_AS_ARRAY_ENABLED
#define HIPONY_AS_ARRAY_HPP_INCLUDED
struct as_array_tag_t {
    explicit as_array_tag_t() = default;
};
HIPONY_ENUMERATE_MAYBE_UNUSED HIPONY_ENUMERATE_CONSTEXPR auto const as_array = as_array_tag_t{};
#endif

#if !defined(HIPONY_AS_TUPLE_HPP_INCLUDED) || HIPONY_ENUMERATE_AS_TUPLE_ENABLED
#define HIPONY_AS_TUPLE_HPP_INCLUDED
struct as_tuple_tag_t {
    explicit as_tuple_tag_t() = default;
};
HIPONY_ENUMERATE_MAYBE_UNUSED HIPONY_ENUMERATE_CONSTEXPR auto const as_tuple = as_tuple_tag_t{};
#endif

namespace hipony_enumerate {

namespace detail {

template<typename... Ts>
struct make_void {
    using type = void;
};

template<typename... Ts>
using void_t = typename detail::make_void<Ts...>::type;

template<bool Value, typename T = void>
using enable_if_t = typename std::enable_if<Value, T>::type;

template<typename T>
using remove_ref_t = typename std::remove_reference<T>::type;

template<typename T>
struct remove_rvalue_reference {
    using type = T;
};

template<typename T>
struct remove_rvalue_reference<T&&> {
    using type = T;
};

template<typename T>
using remove_rref_t = typename remove_rvalue_reference<T>::type;

template<typename T>
using remove_cvref_t = typename std::remove_cv<typename detail::remove_ref_t<T>>::type;

template<typename T>
using remove_pointer_t = typename std::remove_pointer<T>::type;

template<typename T>
using decay_t = typename std::decay<T>::type;

template<typename T>
struct sanitize {
    using type = typename detail::remove_cvref_t<T>;
};

template<typename T, std::size_t N>
struct sanitize<T[N]> {
    using type = T[N];
};

template<typename T, std::size_t N>
struct sanitize<T (&)[N]> {
    using type = T[N];
};

template<typename T, std::size_t N>
struct sanitize<T(&&)[N]> {
    using type = T[N];
};

template<typename T>
using sanitize_t = typename sanitize<T>::type;

template<typename T>
struct is_string_literal : std::false_type {};

template<>
struct is_string_literal<char const> : std::true_type {};

template<>
struct is_string_literal<wchar_t const> : std::true_type {};

#if HIPONY_ENUMERATE_HAS_CHAR8

template<>
struct is_string_literal<char8_t const> : std::true_type {};

#endif

template<>
struct is_string_literal<char16_t const> : std::true_type {};

template<>
struct is_string_literal<char32_t const> : std::true_type {};

#if HIPONY_ENUMERATE_HAS_RANGES

template<typename T>
struct is_range {
    constexpr static auto value = std::ranges::range<T>;
};

#else

template<typename T, typename = void>
struct is_range : std::false_type {};

template<typename T>
struct is_range<
    T,
    typename detail::
        void_t<decltype(std::begin(std::declval<T>())), decltype(std::end(std::declval<T>()))>>
    : std::true_type {};

#endif

#if HIPONY_ENUMERATE_HAS_CONCEPTS

template<typename T>
struct is_iterator {
    constexpr static auto value = std::input_iterator<T>;
};

#else

template<typename T, typename = void>
struct is_iterator : std::false_type {};

template<typename T>
struct is_iterator<
    T,
    typename detail::void_t<
        decltype(std::declval<T&>() != std::declval<T&>()),
        decltype(++std::declval<T&>()),
        decltype(*std::declval<T&>())>> : std::true_type {};

#endif

#if HIPONY_ENUMERATE_HAS_CONCEPTS

template<typename T, typename U>
struct sentinel_for {
    constexpr static auto value = std::sentinel_for<T, U>;
};

#else

template<typename T, typename U, typename = void>
struct sentinel_for : std::false_type {};

template<typename T, typename U>
struct sentinel_for<
    T,
    U,
    detail::enable_if_t<
        detail::is_iterator<U>::value,
        detail::void_t<
            decltype(T()),
            decltype(std::declval<T&>() = T()),
            decltype(std::declval<U&>() == std::declval<T&>())>>> : std::true_type {};

#endif

template<typename T, typename = void>
struct is_tuple : std::false_type {};

template<typename T>
struct is_tuple<T, typename detail::void_t<decltype(std::tuple_size<T>::value)>>
    : std::true_type {};

template<typename = void, typename = void, typename = void>
struct size {
    using type = std::size_t;
};

template<typename T>
struct size<
    void,
    T,
    typename detail::enable_if_t<!std::is_array<T>::value && detail::is_range<T>::value>> {
    using type = typename T::size_type;
};

template<typename Size, typename T>
struct size<Size, T, typename detail::enable_if_t<std::is_integral<Size>::value>> {
    using type = Size;
};

template<typename... Ts>
using size_t = typename detail::size<Ts...>::type;

template<typename Size>
struct dynamic_extent {
    static Size const value = static_cast<Size>(-1);
};

template<
    typename It,
    typename Sentinel,
    typename Size,
    Size N   = detail::dynamic_extent<Size>::value,
    typename = void>
class span {
public:
    static_assert(detail::sentinel_for<Sentinel, It>::value, "Sentinel doesn't match Iterator");

    using iterator       = It;
    using sentinel       = Sentinel;
    using const_iterator = It;
    using const_sentinel = Sentinel;
    using size_type      = Size;

private:
    iterator _begin;
    sentinel _end;

public:
    HIPONY_ENUMERATE_CONSTEXPR span(iterator begin, sentinel end)
        : _begin{begin}
        , _end{end}
    {}

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() const noexcept
        -> const_iterator
    {
        return _begin;
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() const noexcept
        -> const_sentinel
    {
        return _end;
    }
};

template<typename It, typename Sentinel, typename Size, Size N>
class span<
    It,
    Sentinel,
    Size,
    N,
    typename detail::enable_if_t<
        std::is_base_of<
            std::random_access_iterator_tag,
            typename std::iterator_traits<It>::iterator_category>::value
        && std::is_same<It, Sentinel>::value>> {
public:
    using iterator       = It;
    using sentinel       = Sentinel;
    using const_iterator = It;
    using const_sentinel = Sentinel;
    using size_type      = Size;

    using iterator_category = typename std::iterator_traits<iterator>::iterator_category;

private:
    iterator _begin;
    sentinel _end;

public:
    HIPONY_ENUMERATE_CONSTEXPR span(iterator begin, sentinel end)
        : _begin{begin}
        , _end{end}
    {
        assert((_end - _begin) >= 0 && "Size is negative");
    }

    HIPONY_ENUMERATE_CONSTEXPR span(iterator ptr, size_type size)
        : _begin{ptr}
        , _end{ptr + size}
    {
        assert(size >= 0 && "Size is negative");
    }

    HIPONY_ENUMERATE_CONSTEXPR span(iterator ptr)
        : _begin{ptr}
        , _end{ptr + N}
    {
        assert(N >= 0 && "Size is negative");
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() const noexcept
        -> const_iterator
    {
        return _begin;
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() const noexcept
        -> const_sentinel
    {
        return _end;
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto size() const noexcept -> size_type
    {
        return _end - _begin;
    }
};

template<typename T>
struct zstring_iterator {
    using value_type      = T;
    using pointer         = T const*;
    using reference       = T const&;
    using const_reference = T const&;

    using iterator_category = std::forward_iterator_tag;
    using difference_type   = typename std::iterator_traits<pointer>::difference_type;

    pointer _ptr;

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto operator*() const noexcept
        -> const_reference
    {
        return *_ptr;
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto operator->() const noexcept
        -> pointer
    {
        return _ptr;
    }

    HIPONY_ENUMERATE_CONSTEXPR auto operator++() noexcept -> zstring_iterator&
    {
        _ptr++;
        return *this;
    }

    auto operator++(int) noexcept -> zstring_iterator
    {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    // NOTE: We don't use a Sentinel in here because we want to support C++11

    HIPONY_ENUMERATE_NODISCARD friend HIPONY_ENUMERATE_CONSTEXPR auto
    operator==(zstring_iterator const& lhs, zstring_iterator const& rhs) noexcept -> bool
    {
        if (lhs._ptr == rhs._ptr) {
            return true;
        }
        if (lhs._ptr == nullptr) {
            return *rhs._ptr == '\0';
        }
        if (rhs._ptr == nullptr) {
            return *lhs._ptr == '\0';
        }
        return false;
    }

    HIPONY_ENUMERATE_NODISCARD friend HIPONY_ENUMERATE_CONSTEXPR auto
    operator!=(zstring_iterator const& lhs, zstring_iterator const& rhs) noexcept -> bool
    {
        return !(lhs == rhs);
    }
};

template<typename Char>
class zstring_view;

template<typename Char>
class zstring_view<Char const*> {
public:
    using value_type      = Char;
    using pointer         = Char const*;
    using reference       = Char&;
    using const_reference = Char const&;

    using iterator       = zstring_iterator<value_type>;
    using const_iterator = iterator;

private:
    pointer _ptr;

public:
    HIPONY_ENUMERATE_CONSTEXPR zstring_view(pointer ptr)
        : _ptr{ptr}
    {}

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() const noexcept
        -> const_iterator
    {
        return {_ptr};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() const noexcept
        -> const_iterator
    {
        return {nullptr};
    }
};

template<typename T, typename std::iterator_traits<detail::remove_cvref_t<T>*>::difference_type N>
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

template<typename Size, typename InnerIterator>
struct iterator_base {
    using inner_iterator = InnerIterator;
    using size_type      = Size;

    inner_iterator _iterator;
    size_type      _index;

    HIPONY_ENUMERATE_CONSTEXPR iterator_base() = default;

    HIPONY_ENUMERATE_CONSTEXPR iterator_base(inner_iterator iterator, size_type index)
        : _iterator{static_cast<decltype(iterator)&&>(iterator)}
        , _index{index}
    {}
};

template<typename T, typename U, typename Size>
HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto
operator==(iterator_base<Size, T> const& lhs, iterator_base<Size, U> const& rhs) noexcept -> bool
{
    return lhs._iterator == rhs._iterator;
}

template<typename T, typename U, typename Size>
HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto
operator!=(iterator_base<Size, T> const& lhs, iterator_base<Size, U> const& rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template<typename Size, typename InnerIterator, typename = void>
struct iterator : iterator_base<Size, InnerIterator> {
    using iterator_base<Size, InnerIterator>::iterator_base;
};

template<typename Size, typename InnerIterator>
struct iterator<
    Size,
    InnerIterator,
    typename detail::enable_if_t<
        detail::is_iterator<InnerIterator>::value
        && !std::is_base_of<
            std::bidirectional_iterator_tag,
            typename std::iterator_traits<InnerIterator>::iterator_category>::value>>
    : iterator_base<Size, InnerIterator> {
    using inner_iterator  = InnerIterator;
    using inner_reference = decltype(*inner_iterator{});

    using iterator_category = std::input_iterator_tag;
    using difference_type   = typename std::iterator_traits<inner_iterator>::difference_type;
    using size_type         = Size;
    using value_type        = iterator_value<inner_reference, size_type>;
    using pointer           = iterator_value<inner_reference, size_type>;
    using reference         = iterator_value<inner_reference, size_type>;

    using iterator_base<Size, InnerIterator>::iterator_base;

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto operator*() noexcept -> reference
    {
        return {this->_index, *this->_iterator};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto operator*() const noexcept
        -> reference
    {
        return {this->_index, *this->_iterator};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto operator->() noexcept -> pointer
    {
        return {this->_index, *this->_iterator};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto operator->() const noexcept
        -> pointer
    {
        return {this->_index, *this->_iterator};
    }

    HIPONY_ENUMERATE_CONSTEXPR auto operator++() noexcept -> iterator&
    {
        this->_iterator++;
        this->_index++;
        return *this;
    }

    HIPONY_ENUMERATE_NODISCARD auto operator++(int) noexcept -> iterator
    {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }
};

template<typename Size, typename InnerIterator>
struct iterator<
    Size,
    InnerIterator,
    typename detail::enable_if_t<
        detail::is_iterator<InnerIterator>::value
        && std::is_base_of<
            std::bidirectional_iterator_tag,
            typename std::iterator_traits<InnerIterator>::iterator_category>::value>>
    : iterator_base<Size, InnerIterator> {
    using inner_iterator  = InnerIterator;
    using inner_reference = decltype(*inner_iterator{});

    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type   = typename std::iterator_traits<inner_iterator>::difference_type;
    using size_type         = Size;
    using value_type        = iterator_value<inner_reference, size_type>;
    using pointer           = iterator_value<inner_reference, size_type>;
    using reference         = iterator_value<inner_reference, size_type>;

    using iterator_base<Size, InnerIterator>::iterator_base;

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto operator*() noexcept -> reference
    {
        return {this->_index, *this->_iterator};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto operator*() const noexcept
        -> reference
    {
        return {this->_index, *this->_iterator};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto operator->() noexcept -> pointer
    {
        return {this->_index, *this->_iterator};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto operator->() const noexcept
        -> pointer
    {
        return {this->_index, *this->_iterator};
    }

    HIPONY_ENUMERATE_CONSTEXPR auto operator++() noexcept -> iterator&
    {
        this->_iterator++;
        this->_index++;
        return *this;
    }

    HIPONY_ENUMERATE_NODISCARD auto operator++(int) noexcept -> iterator
    {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    HIPONY_ENUMERATE_CONSTEXPR auto operator--() noexcept -> iterator&
    {
        this->_iterator--;
        this->_index++;
        return *this;
    }

    HIPONY_ENUMERATE_NODISCARD auto operator--(int) noexcept -> iterator
    {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }
};

template<typename Size, typename Container>
struct range {
    using value_type = typename detail::remove_rref_t<Container>;
    using size_type  = Size;

    value_type data;

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() noexcept
        -> iterator<size_type, decltype(data.begin())>
    {
        return {data.begin(), 0};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() noexcept
        -> iterator<size_type, decltype(data.end())>
    {
        return {data.end(), static_cast<size_type>(-1)};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() const noexcept
        -> iterator<size_type, decltype(data.begin())>
    {
        return {data.begin(), 0};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() const noexcept
        -> iterator<size_type, decltype(data.end())>
    {
        return {data.end(), static_cast<size_type>(-1)};
    }
};

#if HIPONY_ENUMERATE_HAS_RANGES && !defined(__clang__)

template<typename Size, typename Container>
struct range_view : std::ranges::view_interface<range_view<Size, Container>> {
    using value_type = typename detail::remove_ref_t<Container>;
    using size_type  = Size;

    value_type* data;

    HIPONY_ENUMERATE_CONSTEXPR range_view() = default;

    HIPONY_ENUMERATE_CONSTEXPR range_view(value_type& data_)
        : data{&data_}
    {}

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() noexcept
        -> iterator<size_type, decltype(data->begin())>
    {
        return {data->begin(), 0};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() noexcept
        -> iterator<size_type, decltype(data->end())>
    {
        return {data->end(), static_cast<size_type>(-1)};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() const noexcept
        -> iterator<size_type, decltype(data->begin())>
    {
        return {data->begin(), 0};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() const noexcept
        -> iterator<size_type, decltype(data->end())>
    {
        return {data->end(), static_cast<size_type>(-1)};
    }
};

template<typename Size, typename Container>
using view = detail::range_view<Size, Container>;

#else

template<typename Size, typename Container>
struct basic_view {
    using value_type = typename detail::remove_ref_t<Container>;
    using size_type  = Size;

    value_type* data;

    HIPONY_ENUMERATE_CONSTEXPR basic_view() = default;

    HIPONY_ENUMERATE_CONSTEXPR basic_view(value_type& data_)
        : data{&data_}
    {}

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() noexcept
        -> iterator<size_type, decltype(data->begin())>
    {
        return {data->begin(), 0};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() noexcept
        -> iterator<size_type, decltype(data->end())>
    {
        return {data->end(), static_cast<size_type>(-1)};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() const noexcept
        -> iterator<size_type, decltype(data->begin())>
    {
        return {data->begin(), 0};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() const noexcept
        -> iterator<size_type, decltype(data->end())>
    {
        return {data->end(), static_cast<size_type>(-1)};
    }
};

template<typename Size, typename Container>
using view = detail::basic_view<Size, Container>;

#endif

template<typename Size, typename InnerIterator, typename = void>
class limited_iterator {
public:
    using inner_iterator  = InnerIterator;
    using inner_reference = decltype(*inner_iterator{});

    using iterator_category = typename std::iterator_traits<inner_iterator>::iterator_category;
    using difference_type   = typename std::iterator_traits<inner_iterator>::difference_type;
    using size_type         = Size;
    using value_type        = iterator_value<inner_reference, size_type>;
    using pointer           = iterator_value<inner_reference, size_type>;
    using reference         = iterator_value<inner_reference, size_type>;

private:
    size_type      _max;
    size_type      _index;
    inner_iterator _iterator;

public:
    HIPONY_ENUMERATE_CONSTEXPR limited_iterator() = default;

    HIPONY_ENUMERATE_CONSTEXPR limited_iterator(size_type max, inner_iterator iterator)
        : _max{max}
        , _index{0}
        , _iterator{static_cast<inner_iterator&&>(iterator)}
    {}

    HIPONY_ENUMERATE_CONSTEXPR
    limited_iterator(size_type max, size_type index, inner_iterator iterator)
        : _max{max}
        , _index{index}
        , _iterator{static_cast<inner_iterator&&>(iterator)}
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

    HIPONY_ENUMERATE_CONSTEXPR auto operator++() noexcept -> limited_iterator&
    {
        _iterator++;
        _index++;
        return *this;
    }

    HIPONY_ENUMERATE_NODISCARD auto operator++(int) noexcept -> limited_iterator
    {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    HIPONY_ENUMERATE_NODISCARD friend HIPONY_ENUMERATE_CONSTEXPR auto
    operator==(limited_iterator const& lhs, limited_iterator const& rhs) noexcept -> bool
    {
        return lhs._index == rhs._index || lhs._iterator == rhs._iterator;
    }

    HIPONY_ENUMERATE_NODISCARD friend HIPONY_ENUMERATE_CONSTEXPR auto
    operator!=(limited_iterator const& lhs, limited_iterator const& rhs) noexcept -> bool
    {
        return !(lhs == rhs);
    }
};

template<typename Size, typename InnerIterator>
class limited_iterator<
    Size,
    InnerIterator,
    typename detail::enable_if_t<std::is_base_of<
        std::bidirectional_iterator_tag,
        typename std::iterator_traits<InnerIterator>::iterator_category>::value>> {
public:
    using inner_iterator  = InnerIterator;
    using inner_reference = decltype(*inner_iterator{});

    using iterator_category = typename std::iterator_traits<inner_iterator>::iterator_category;
    using difference_type   = typename std::iterator_traits<inner_iterator>::difference_type;
    using size_type         = Size;
    using value_type        = iterator_value<inner_reference, size_type>;
    using pointer           = iterator_value<inner_reference, size_type>;
    using reference         = iterator_value<inner_reference, size_type>;

private:
    size_type      _max;
    size_type      _index;
    inner_iterator _iterator;

public:
    HIPONY_ENUMERATE_CONSTEXPR limited_iterator() = default;

    HIPONY_ENUMERATE_CONSTEXPR limited_iterator(size_type max, inner_iterator iterator)
        : _max{max}
        , _index{0}
        , _iterator{static_cast<inner_iterator&&>(iterator)}
    {}

    HIPONY_ENUMERATE_CONSTEXPR
    limited_iterator(size_type max, size_type index, inner_iterator iterator)
        : _max{max}
        , _index{index}
        , _iterator{static_cast<inner_iterator&&>(iterator)}
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

    HIPONY_ENUMERATE_CONSTEXPR auto operator++() noexcept -> limited_iterator&
    {
        _iterator++;
        _index++;
        return *this;
    }

    HIPONY_ENUMERATE_NODISCARD auto operator++(int) noexcept -> limited_iterator
    {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    HIPONY_ENUMERATE_CONSTEXPR auto operator--() noexcept -> limited_iterator&
    {
        _iterator--;
        _index++;
        return *this;
    }

    HIPONY_ENUMERATE_NODISCARD auto operator--(int) noexcept -> limited_iterator
    {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    HIPONY_ENUMERATE_NODISCARD friend HIPONY_ENUMERATE_CONSTEXPR auto
    operator==(limited_iterator const& lhs, limited_iterator const& rhs) noexcept -> bool
    {
        return lhs._index == rhs._index || lhs._iterator == rhs._iterator;
    }

    HIPONY_ENUMERATE_NODISCARD friend HIPONY_ENUMERATE_CONSTEXPR auto
    operator!=(limited_iterator const& lhs, limited_iterator const& rhs) noexcept -> bool
    {
        return !(lhs == rhs);
    }
};

template<typename Size, typename Container, typename = void>
struct limited_range {
    using value_type = typename detail::remove_rref_t<Container>;
    using size_type  = Size;

    struct impl_t {
        value_type data;
        size_type  size;

        HIPONY_ENUMERATE_CONSTEXPR impl_t() = default;
        HIPONY_ENUMERATE_CONSTEXPR impl_t(value_type&& data_, size_type size_)
            : data{static_cast<decltype(data_)&&>(data_)}
            , size{size_}
        {}
    } impl;

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() noexcept
        -> limited_iterator<size_type, decltype(impl.data.begin())>
    {
        assert(impl.size >= 0 && "Size is negative");
        return {impl.size, impl.data.begin()};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() noexcept
        -> limited_iterator<size_type, decltype(impl.data.end())>
    {
        assert(impl.size >= 0 && "Size is negative");
        return {impl.size, impl.size, impl.data.end()};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() const noexcept
        -> limited_iterator<size_type, decltype(impl.data.begin())>
    {
        assert(impl.size >= 0 && "Size is negative");
        return {impl.size, impl.data.begin()};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() const noexcept
        -> limited_iterator<size_type, decltype(impl.data.end())>
    {
        assert(impl.size >= 0 && "Size is negative");
        return {impl.size, impl.size, impl.data.end()};
    }
};

template<typename Size, typename Container>
struct limited_range<
    Size,
    Container,
    typename detail::enable_if_t<std::is_base_of<
        std::random_access_iterator_tag,
        typename std::iterator_traits<
            typename detail::remove_cvref_t<Container>::iterator>::iterator_category>::value>> {
    using value_type      = typename detail::remove_rref_t<Container>;
    using inner_iterator  = typename detail::remove_cvref_t<Container>::iterator;
    using difference_type = typename std::iterator_traits<inner_iterator>::difference_type;
    using size_type       = Size;

    struct impl_t {
        value_type data;
        size_type  size;

        HIPONY_ENUMERATE_CONSTEXPR impl_t() = default;
        HIPONY_ENUMERATE_CONSTEXPR impl_t(value_type&& data_, size_type size_)
            : data{static_cast<decltype(data_)&&>(data_)}
            , size{size_}
        {}
    } impl;

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() noexcept
        -> iterator<size_type, decltype(impl.data.begin())>
    {
        return {impl.data.begin(), 0};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() noexcept
        -> iterator<size_type, decltype(impl.data.begin())>
    {
        assert(impl.size >= 0 && "Size is negative");
        return {
            ((impl.data.end() - impl.data.begin()) > static_cast<difference_type>(impl.size))
                ? (impl.data.begin() + impl.size)
                : impl.data.end(),
            static_cast<size_type>(-1)};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() const noexcept
        -> iterator<size_type, decltype(impl.data.begin())>
    {
        return {impl.data.begin(), 0};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() const noexcept
        -> iterator<size_type, decltype(impl.data.begin())>
    {
        assert(impl.size >= 0 && "Size is negative");
        return {
            ((impl.data.end() - impl.data.begin()) > static_cast<difference_type>(impl.size))
                ? (impl.data.begin() + impl.size)
                : impl.data.end(),
            static_cast<size_type>(-1)};
    }
};

#if HIPONY_ENUMERATE_HAS_RANGES && !defined(__clang__)

template<typename Size, typename Container, typename = void>
struct limited_range_view : std::ranges::view_interface<limited_range_view<Size, Container>> {
    using value_type = typename detail::remove_ref_t<Container>;
    using size_type  = Size;

    struct impl_t {
        value_type* data;
        size_type   size;

        HIPONY_ENUMERATE_CONSTEXPR impl_t() = default;
        HIPONY_ENUMERATE_CONSTEXPR impl_t(value_type& data_, size_type size_)
            : data{&data_}
            , size{size_}
        {}
    } impl;

    HIPONY_ENUMERATE_CONSTEXPR limited_range_view() = default;

    HIPONY_ENUMERATE_CONSTEXPR limited_range_view(impl_t impl_)
        : impl{static_cast<impl_t&&>(impl_)}
    {}

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() noexcept
        -> limited_iterator<size_type, decltype(impl.data->begin())>
    {
        assert(impl.size >= 0 && "Size is negative");
        return {impl.size, impl.data->begin()};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() noexcept
        -> limited_iterator<size_type, decltype(impl.data->end())>
    {
        assert(impl.size >= 0 && "Size is negative");
        return {impl.size, impl.size, impl.data->end()};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() const noexcept
        -> limited_iterator<size_type, decltype(impl.data->begin())>
    {
        assert(impl.size >= 0 && "Size is negative");
        return {impl.size, impl.data->begin()};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() const noexcept
        -> limited_iterator<size_type, decltype(impl.data->end())>
    {
        assert(impl.size >= 0 && "Size is negative");
        return {impl.size, impl.size, impl.data->end()};
    }
};

template<typename Size, typename Container>
struct limited_range_view<
    Size,
    Container,
    typename detail::enable_if_t<std::is_base_of<
        std::random_access_iterator_tag,
        typename std::iterator_traits<
            typename detail::remove_cvref_t<Container>::iterator>::iterator_category>::value>>
    : std::ranges::view_interface<limited_range_view<Size, Container>> {
    using value_type      = typename detail::remove_rref_t<Container>;
    using inner_iterator  = typename detail::remove_cvref_t<Container>::iterator;
    using difference_type = typename std::iterator_traits<inner_iterator>::difference_type;
    using size_type       = Size;

    struct impl_t {
        value_type* data;
        size_type   size;

        HIPONY_ENUMERATE_CONSTEXPR impl_t() = default;
        HIPONY_ENUMERATE_CONSTEXPR impl_t(value_type& data_, size_type size_)
            : data{&data_}
            , size{size_}
        {}
    } impl;

    HIPONY_ENUMERATE_CONSTEXPR limited_range_view() = default;

    HIPONY_ENUMERATE_CONSTEXPR limited_range_view(impl_t impl_)
        : impl{static_cast<impl_t&&>(impl_)}
    {}

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() noexcept
        -> iterator<size_type, decltype(impl.data->begin())>
    {
        return {impl.data->begin(), 0};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() noexcept
        -> iterator<size_type, decltype(impl.data->begin())>
    {
        assert(impl.size >= 0 && "Size is negative");
        return {
            ((impl.data->end() - impl.data->begin()) > static_cast<difference_type>(impl.size))
                ? (impl.data->begin() + impl.size)
                : impl.data->end(),
            static_cast<size_type>(-1)};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() const noexcept
        -> iterator<size_type, decltype(impl.data->begin())>
    {
        return {impl.data->begin(), 0};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() const noexcept
        -> iterator<size_type, decltype(impl.data->begin())>
    {
        assert(impl.size >= 0 && "Size is negative");
        return {
            ((impl.data->end() - impl.data->begin()) > static_cast<difference_type>(impl.size))
                ? (impl.data->begin() + impl.size)
                : impl.data->end(),
            static_cast<size_type>(-1)};
    }
};

template<typename Size, typename Container>
using limited_view = detail::limited_range_view<Size, Container>;

#else

template<typename Size, typename Container, typename = void>
struct limited_basic_view {
    using value_type = typename detail::remove_ref_t<Container>;
    using size_type  = Size;

    struct impl_t {
        value_type* data;
        size_type   size;

        HIPONY_ENUMERATE_CONSTEXPR impl_t() = default;
        HIPONY_ENUMERATE_CONSTEXPR impl_t(value_type& data_, size_type size_)
            : data{&data_}
            , size{size_}
        {}
    } impl;

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() noexcept
        -> limited_iterator<size_type, decltype(impl.data->begin())>
    {
        assert(impl.size >= 0 && "Size is negative");
        return {impl.size, impl.data->begin()};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() noexcept
        -> limited_iterator<size_type, decltype(impl.data->end())>
    {
        assert(impl.size >= 0 && "Size is negative");
        return {impl.size, impl.size, impl.data->end()};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() const noexcept
        -> limited_iterator<size_type, decltype(impl.data->begin())>
    {
        assert(impl.size >= 0 && "Size is negative");
        return {impl.size, impl.data->begin()};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() const noexcept
        -> limited_iterator<size_type, decltype(impl.data->end())>
    {
        assert(impl.size >= 0 && "Size is negative");
        return {impl.size, impl.size, impl.data->end()};
    }
};

template<typename Size, typename Container>
struct limited_basic_view<
    Size,
    Container,
    typename detail::enable_if_t<std::is_base_of<
        std::random_access_iterator_tag,
        typename std::iterator_traits<
            typename detail::remove_cvref_t<Container>::iterator>::iterator_category>::value>> {
    using value_type      = typename detail::remove_rref_t<Container>;
    using inner_iterator  = typename detail::remove_cvref_t<Container>::iterator;
    using difference_type = typename std::iterator_traits<inner_iterator>::difference_type;
    using size_type       = Size;

    struct impl_t {
        value_type* data;
        size_type   size;

        HIPONY_ENUMERATE_CONSTEXPR impl_t() = default;
        HIPONY_ENUMERATE_CONSTEXPR impl_t(value_type& data_, size_type size_)
            : data{&data_}
            , size{size_}
        {}
    } impl;

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() noexcept
        -> iterator<size_type, decltype(impl.data->begin())>
    {
        return {impl.data->begin(), 0};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() noexcept
        -> iterator<size_type, decltype(impl.data->begin())>
    {
        assert(impl.size >= 0 && "Size is negative");
        return {
            ((impl.data->end() - impl.data->begin()) > static_cast<difference_type>(impl.size))
                ? (impl.data->begin() + impl.size)
                : impl.data->end(),
            static_cast<size_type>(-1)};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() const noexcept
        -> iterator<size_type, decltype(impl.data->begin())>
    {
        return {impl.data->begin(), 0};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() const noexcept
        -> iterator<size_type, decltype(impl.data->begin())>
    {
        assert(impl.size >= 0 && "Size is negative");
        return {
            ((impl.data->end() - impl.data->begin()) > static_cast<difference_type>(impl.size))
                ? (impl.data->begin() + impl.size)
                : impl.data->end(),
            static_cast<size_type>(-1)};
    }
};

template<typename Size, typename Container>
using limited_view = detail::limited_basic_view<Size, Container>;

#endif

template<typename Size, typename T, typename U = T>
struct tuple_wrapper;

template<typename Size, typename T, template<typename...> class Tuple, typename... Ts>
struct tuple_wrapper<Size, T, Tuple<Ts...>> {
    using tuple_type = typename detail::remove_rref_t<T>;
    using size_type  = Size;

    tuple_type data;

    template<typename F>
    HIPONY_ENUMERATE_CONSTEXPR void each(F&& f)
    {
        do_each<F, 0, Ts...>(static_cast<F&&>(f));
    }

private:
    template<typename F, size_type N>
    HIPONY_ENUMERATE_CONSTEXPR void do_each(F&& /*f*/)
    {}

    template<typename F, size_type N, typename Arg, typename... Args>
    HIPONY_ENUMERATE_CONSTEXPR void do_each(F&& f)
    {
        f(N, std::get<N>(data));
        do_each<F, N + 1, Args...>(static_cast<F&&>(f));
    }
};

#if HIPONY_ENUMERATE_HAS_AGGREGATES

template<typename Size, typename T>
struct aggregate_wrapper {
    using aggregate_type = typename detail::remove_rref_t<T>;
    using size_type      = Size;

    aggregate_type data;

    template<typename F>
    HIPONY_ENUMERATE_CONSTEXPR void each(F&& f)
    {
        using tuple_type = decltype(boost::pfr::structure_tie(data));
        detail::tuple_wrapper<
            Size,
            detail::remove_rref_t<tuple_type>,
            detail::remove_cvref_t<tuple_type>>{boost::pfr::structure_tie(data)}
            .each(static_cast<F&&>(f));
    }
};

#endif

struct variadic_tuple_tag_t {};
struct variadic_array_tag_t {};
struct iterator_pointer_tag_t {};
struct iterator_tag_t {};
struct container_tag_t {};
struct container_size_tag_t {};
struct tuple_tag_t {};
struct pointer_tag_t {};
struct string_tag_t {};
struct array_tag_t {};

#if HIPONY_ENUMERATE_HAS_AGGREGATES
struct aggregate_tag_t {};
#endif

template<typename Size, typename T, typename = void, typename...>
struct tag;

template<typename Size, typename T, typename T1>
struct tag<
    Size,
    T,
    typename detail::enable_if_t<
        std::is_same<T, T1>::value && detail::is_iterator<T>::value && std::is_pointer<T>::value>,
    T1> {
    using type = iterator_pointer_tag_t;
};

template<typename Size, typename T, typename Sentinel>
struct tag<
    Size,
    T,
    typename detail::enable_if_t<
        detail::sentinel_for<Sentinel, T>::value && detail::is_iterator<T>::value
        && (!std::is_pointer<T>::value || !std::is_pointer<Sentinel>::value)>,
    Sentinel> {
    using type = iterator_tag_t;
};

template<typename Size, typename T>
struct tag<
    Size,
    T,
    typename detail::enable_if_t<!std::is_array<T>::value && detail::is_range<T>::value>> {
    using type = container_tag_t;
};

template<typename Size, typename T, typename TSize>
struct tag<
    Size,
    T,
    typename detail::enable_if_t<
        !std::is_array<T>::value && detail::is_range<T>::value && std::is_integral<Size>::value
        && std::is_convertible<TSize, Size>::value>,
    TSize> {
    using type = container_size_tag_t;
};

template<typename Size, typename T>
struct tag<
    Size,
    T,
    typename detail::enable_if_t<
        detail::is_tuple<detail::decay_t<T>>::value && !detail::is_range<T>::value>> {
    using type = tuple_tag_t;
};

template<typename Size, typename T, typename TSize>
struct tag<
    Size,
    T*,
    typename detail::enable_if_t<
        std::is_integral<Size>::value && std::is_convertible<TSize, Size>::value>,
    TSize> {
    using type = pointer_tag_t;
};

template<typename Size>
struct tag<Size, char const*, typename detail::enable_if_t<std::is_integral<Size>::value>> {
    using type = string_tag_t;
};

template<typename Size>
struct tag<Size, wchar_t const*, typename detail::enable_if_t<std::is_integral<Size>::value>> {
    using type = string_tag_t;
};

#if HIPONY_ENUMERATE_HAS_CHAR8

template<typename Size>
struct tag<Size, char8_t const*, typename detail::enable_if_t<std::is_integral<Size>::value>> {
    using type = string_tag_t;
};

#endif

template<typename Size>
struct tag<Size, char16_t const*, typename detail::enable_if_t<std::is_integral<Size>::value>> {
    using type = string_tag_t;
};

template<typename Size>
struct tag<Size, char32_t const*, typename detail::enable_if_t<std::is_integral<Size>::value>> {
    using type = string_tag_t;
};

template<typename Size, Size N>
struct tag<Size, char const[N], typename detail::enable_if_t<std::is_integral<Size>::value>> {
    using type = string_tag_t;
};

template<typename Size, Size N>
struct tag<Size, wchar_t const[N], typename detail::enable_if_t<std::is_integral<Size>::value>> {
    using type = string_tag_t;
};

#if HIPONY_ENUMERATE_HAS_CHAR8

template<typename Size, Size N>
struct tag<Size, char8_t const[N], typename detail::enable_if_t<std::is_integral<Size>::value>> {
    using type = string_tag_t;
};

#endif

template<typename Size, Size N>
struct tag<Size, char16_t const[N], typename detail::enable_if_t<std::is_integral<Size>::value>> {
    using type = string_tag_t;
};

template<typename Size, Size N>
struct tag<Size, char32_t const[N], typename detail::enable_if_t<std::is_integral<Size>::value>> {
    using type = string_tag_t;
};

template<typename Size, typename T, Size N>
struct tag<
    Size,
    T[N],
    typename detail::enable_if_t<
        std::is_integral<Size>::value && !detail::is_string_literal<T>::value>> {
    using type = array_tag_t;
};

template<typename Size, typename T, Size N, typename TSize>
struct tag<
    Size,
    T[N],
    typename detail::enable_if_t<
        std::is_integral<Size>::value && std::is_convertible<TSize, Size>::value>,
    TSize> {
    using type = array_tag_t;
};

#if HIPONY_ENUMERATE_HAS_AGGREGATES

template<typename Size, typename T>
struct tag<
    Size,
    T,
    typename detail::enable_if_t<
        std::is_aggregate<T>::value && !std::is_polymorphic<T>::value && !detail::is_tuple<T>::value
        && !std::is_array<T>::value>> {
    using type = aggregate_tag_t;
};

#endif

template<typename... Ts>
using tag_t = typename tag<Ts...>::type;

template<typename Tag = void, typename...>
struct dispatch;

template<typename Size, typename... Ts>
struct dispatch<detail::variadic_tuple_tag_t, Size, Ts...> {
    using type = detail::tuple_wrapper<Size, std::tuple<detail::remove_rref_t<Ts>...>>;
};

template<typename Size, typename T, typename... Ts>
struct dispatch<detail::variadic_array_tag_t, Size, T, Ts...> {
    using type = detail::range<Size, detail::array<detail::remove_rref_t<T>, sizeof...(Ts) + 1>>;
};

template<typename Size, typename T, typename T1>
struct dispatch<detail::iterator_pointer_tag_t, Size, T, T1> {
    using type
        = detail::range<Size, detail::span<detail::remove_ref_t<T>, detail::remove_ref_t<T1>, Size>>;
};

template<typename Size, typename T, typename Sentinel>
struct dispatch<detail::iterator_tag_t, Size, T, Sentinel> {
    using type = detail::
        range<Size, detail::span<detail::remove_ref_t<T>, detail::remove_ref_t<Sentinel>, Size>>;
};

template<typename Size, typename T>
struct dispatch<detail::container_tag_t, Size, T> {
    using type = detail::range<Size, detail::remove_rref_t<T>>;
};

template<typename Size, typename T>
struct dispatch<detail::container_tag_t, Size, T&> {
    using type = detail::view<Size, T>;
};

template<typename Size, typename T, typename TSize>
struct dispatch<detail::container_size_tag_t, Size, T, TSize> {
    using type = detail::limited_range<Size, detail::remove_rref_t<T>>;
};

template<typename Size, typename T, typename TSize>
struct dispatch<detail::container_size_tag_t, Size, T&, TSize> {
    using type = detail::limited_view<Size, T>;
};

template<typename Size, typename T>
struct dispatch<detail::tuple_tag_t, Size, T> {
    using type = detail::tuple_wrapper<Size, detail::remove_rref_t<T>, detail::remove_cvref_t<T>>;
};

template<typename Size, typename T, typename TSize>
struct dispatch<detail::pointer_tag_t, Size, T, TSize> {
    using type
        = detail::range<Size, detail::span<detail::remove_ref_t<T>, detail::remove_ref_t<T>, Size>>;
};

template<typename Size, typename T>
struct dispatch<detail::string_tag_t, Size, T> {
    using type = detail::range<Size, detail::zstring_view<detail::decay_t<T>>>;
};

template<typename Size, typename T, Size N>
struct dispatch<detail::array_tag_t, Size, T (&)[N]> {
    using type = detail::
        range<Size, detail::span<detail::remove_ref_t<T>*, detail::remove_ref_t<T>*, Size, N>>;
};

template<typename Size, typename T, Size N, typename TSize>
struct dispatch<detail::array_tag_t, Size, T (&)[N], TSize> {
    using type
        = detail::range<Size, detail::span<detail::remove_ref_t<T>*, detail::remove_ref_t<T>*, Size>>;
};

#if HIPONY_ENUMERATE_HAS_AGGREGATES

template<typename Size, typename T>
struct dispatch<detail::aggregate_tag_t, Size, T> {
    using type = detail::aggregate_wrapper<Size, T>;
};

#endif

template<typename... Ts>
using dispatch_t = typename dispatch<Ts...>::type;

} // namespace detail

template<typename T, typename... Ts>
HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR inline auto
enumerate(T&& t, Ts&&... ts) noexcept -> detail::dispatch_t<
    detail::tag_t<
        detail::size_t<detail::void_t<>, detail::remove_cvref_t<T>>,
        detail::sanitize_t<T>,
        detail::void_t<>,
        detail::remove_cvref_t<Ts>...>,
    detail::size_t<detail::void_t<>, detail::remove_cvref_t<T>>,
    T,
    Ts...>
{
    return {{static_cast<T&&>(t), static_cast<Ts&&>(ts)...}};
}

template<typename Size, typename T, typename... Ts>
HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR inline auto
enumerate_as(T&& t, Ts&&... ts) noexcept -> detail::dispatch_t<
    detail::tag_t<
        detail::size_t<Size, detail::remove_cvref_t<T>>,
        detail::sanitize_t<T>,
        detail::void_t<>,
        detail::remove_cvref_t<Ts>...>,
    detail::size_t<Size, detail::remove_cvref_t<T>>,
    T,
    Ts...>
{
    return {{static_cast<T&&>(t), static_cast<Ts&&>(ts)...}};
}

using HIPONY_ENUMERATE_NAMESPACE::as_tuple_tag_t;

template<typename T, typename... Ts>
HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR inline auto
enumerate(as_tuple_tag_t /*_*/, T&& t, Ts&&... ts) noexcept -> detail::dispatch_t<
    detail::variadic_tuple_tag_t,
    detail::size_t<detail::void_t<>, detail::remove_cvref_t<T>>,
    T,
    Ts...>
{
    return {{static_cast<T&&>(t), static_cast<Ts&&>(ts)...}};
}

template<typename Size, typename T, typename... Ts>
HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR inline auto
enumerate_as(as_tuple_tag_t /*_*/, T&& t, Ts&&... ts) noexcept -> detail::
    dispatch_t<detail::variadic_tuple_tag_t, detail::size_t<Size, detail::remove_cvref_t<T>>, T, Ts...>
{
    return {{static_cast<T&&>(t), static_cast<Ts&&>(ts)...}};
}

using HIPONY_ENUMERATE_NAMESPACE::as_array_tag_t;

template<typename T, typename... Ts>
HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR inline auto
enumerate(as_array_tag_t /*_*/, T&& t, Ts&&... ts) noexcept -> detail::dispatch_t<
    detail::variadic_array_tag_t,
    detail::size_t<detail::void_t<>, detail::remove_cvref_t<T>>,
    T,
    Ts...>
{
    return {{static_cast<T&&>(t), static_cast<Ts&&>(ts)...}};
}

template<typename Size, typename T, typename... Ts>
HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR inline auto
enumerate_as(as_array_tag_t /*_*/, T&& t, Ts&&... ts) noexcept -> detail::
    dispatch_t<detail::variadic_array_tag_t, detail::size_t<Size, detail::remove_cvref_t<T>>, T, Ts...>
{
    return {{static_cast<T&&>(t), static_cast<Ts&&>(ts)...}};
}

} // namespace hipony_enumerate

using hipony_enumerate::enumerate;
using hipony_enumerate::enumerate_as;

} // namespace HIPONY_ENUMERATE_NAMESPACE

#endif
