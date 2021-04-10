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
constexpr auto is_same() noexcept -> bool
{
    return true;
}

template<typename T, typename First, typename... Tail>
constexpr auto is_same() noexcept -> bool
{
    return std::is_same<T, First>::value && detail::is_same<T, Tail...>();
}

template<typename It>
constexpr void do_advance(
    It&                                                it,
    typename std::iterator_traits<It>::difference_type n,
    std::input_iterator_tag) noexcept
{
    while (n > 0) {
        --n;
        ++it;
    }
}

template<typename It>
constexpr void do_advance(
    It&                                                it,
    typename std::iterator_traits<It>::difference_type n,
    std::bidirectional_iterator_tag                    tag) noexcept
{
    while (n > 0) {
        --n;
        ++it;
    }
    while (n < 0) {
        ++n;
        --it;
    }
}

template<typename It>
constexpr void do_advance(
    It&                                                it,
    typename std::iterator_traits<It>::difference_type n,
    std::random_access_iterator_tag) noexcept
{
    it += n;
}

template<typename It>
constexpr auto next(It it, typename std::iterator_traits<It>::difference_type n) noexcept -> It
{
    detail::do_advance(
        it,
        typename std::iterator_traits<It>::difference_type(n),
        typename std::iterator_traits<It>::iterator_category());
    return it;
}

template<typename T>
using remove_cvref_t = typename std::remove_reference<typename std::remove_cv<T>::type>::type;

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
    constexpr span(pointer ptr, size_type size)
        : _ptr{ptr}
        , _size{size}
    {}

    HIPONY_ENUMERATE_NODISCARD constexpr auto begin() const noexcept -> const_iterator
    {
        return _ptr;
    }

    HIPONY_ENUMERATE_NODISCARD constexpr auto end() const noexcept -> const_iterator
    {
        return _ptr + _size;
    }

    HIPONY_ENUMERATE_NODISCARD constexpr auto size() const noexcept -> size_type
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

    HIPONY_ENUMERATE_NODISCARD constexpr auto begin() noexcept -> iterator
    {
        return data;
    }

    HIPONY_ENUMERATE_NODISCARD constexpr auto end() noexcept -> iterator
    {
        return data + N;
    }

    HIPONY_ENUMERATE_NODISCARD constexpr auto begin() const noexcept -> const_iterator
    {
        return data;
    }

    HIPONY_ENUMERATE_NODISCARD constexpr auto end() const noexcept -> const_iterator
    {
        return data + N;
    }

    HIPONY_ENUMERATE_NODISCARD constexpr auto size() const noexcept -> size_type
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

    HIPONY_ENUMERATE_NODISCARD friend constexpr auto
    operator==(iterator_value const& lhs, iterator_value const& rhs) noexcept -> bool
    {
        return lhs.index == rhs.index && lhs.value == rhs.value;
    }

    HIPONY_ENUMERATE_NODISCARD friend constexpr auto
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
    constexpr iterator(inner_iterator iterator)
        : _index{0}
        , _iterator{static_cast<decltype(iterator)&&>(iterator)}
    {}

    HIPONY_ENUMERATE_NODISCARD constexpr auto operator*() noexcept -> reference
    {
        return {_index, *_iterator};
    }

    HIPONY_ENUMERATE_NODISCARD constexpr auto operator*() const noexcept -> reference
    {
        return {_index, *_iterator};
    }

    HIPONY_ENUMERATE_NODISCARD constexpr auto operator->() noexcept -> pointer
    {
        return {_index, *_iterator};
    }

    HIPONY_ENUMERATE_NODISCARD constexpr auto operator->() const noexcept -> pointer
    {
        return {_index, *_iterator};
    }

    constexpr auto operator++() noexcept -> iterator&
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

    HIPONY_ENUMERATE_NODISCARD friend constexpr auto
    operator==(iterator const& lhs, iterator const& rhs) noexcept -> bool
    {
        return lhs._iterator == rhs._iterator;
    }

    HIPONY_ENUMERATE_NODISCARD friend constexpr auto
    operator!=(iterator const& lhs, iterator const& rhs) noexcept -> bool
    {
        return !(lhs == rhs);
    }
};

template<typename Container>
struct wrapper {
    using size_type = typename detail::remove_cvref_t<Container>::size_type;

    Container data;
    size_type size;

    HIPONY_ENUMERATE_NODISCARD constexpr auto begin() noexcept -> iterator<Container>
    {
        return {data.begin()};
    }

    HIPONY_ENUMERATE_NODISCARD constexpr auto end() noexcept -> iterator<Container>
    {
        return {data.size() < size ? data.end() : detail::next(data.begin(), size)};
    }

    HIPONY_ENUMERATE_NODISCARD constexpr auto begin() const noexcept -> iterator<Container>
    {
        return {data.begin()};
    }

    HIPONY_ENUMERATE_NODISCARD constexpr auto end() const noexcept -> iterator<Container>
    {
        return {data.size() < size ? data.end() : detail::next(data.begin(), size)};
    }
};

} // namespace detail

template<typename Container>
HIPONY_ENUMERATE_NODISCARD constexpr auto enumerate(Container&& c) noexcept
    -> detail::wrapper<decltype(c)>
{
    return {static_cast<decltype(c)&&>(c), c.size()};
}

template<typename Container>
HIPONY_ENUMERATE_NODISCARD constexpr auto enumerate(Container&& c, std::size_t n) noexcept ->
    typename std::enable_if<
        !std::is_pointer<detail::remove_cvref_t<Container>>::value,
        detail::wrapper<decltype(c)>>::type
{
    return {static_cast<decltype(c)&&>(c), n};
}

template<typename T>
HIPONY_ENUMERATE_NODISCARD constexpr auto enumerate(T ptr, std::size_t n) noexcept ->
    typename std::enable_if<
        std::is_pointer<detail::remove_cvref_t<T>>::value,
        detail::wrapper<detail::span<typename std::remove_pointer<T>::type>>>::type
{
    return {{ptr, n}, n};
}

template<typename T, typename... Args>
HIPONY_ENUMERATE_NODISCARD constexpr auto enumerate(T first, Args... args) noexcept ->
    typename std::enable_if<
        detail::is_same<T, Args...>(),
        detail::wrapper<detail::array<T, sizeof...(Args) + 1>>>::type
{
    return {{static_cast<T&&>(first), static_cast<Args&&>(args)...}, sizeof...(Args) + 1};
}

template<typename T, std::size_t N>
HIPONY_ENUMERATE_NODISCARD constexpr auto enumerate(T (&arr)[N]) noexcept
    -> detail::wrapper<detail::span<T>>
{
    return {{arr, N}, N};
}

template<typename T, std::size_t N>
HIPONY_ENUMERATE_NODISCARD constexpr auto enumerate(T (&arr)[N], std::size_t n) noexcept
    -> detail::wrapper<detail::span<T>>
{
    return {{arr, N}, n};
}

} // namespace hipony_enumerate

using hipony_enumerate::enumerate;

} // namespace HIPONY_ENUMERATE_NAMESPACE

#endif
