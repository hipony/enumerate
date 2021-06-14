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
#define HIPONY_ENUMERATE_CPP20_OR_GREATER (HIPONY_ENUMERATE_CPLUSPLUS >= 202002L)

#if defined(_MSC_VER)
#define HIPONY_ENUMERATE_HAS_CONSTEXPR (HIPONY_ENUMERATE_CPP14_OR_GREATER && _MSC_VER > 1914)
#else
#define HIPONY_ENUMERATE_HAS_CONSTEXPR HIPONY_ENUMERATE_CPP14_OR_GREATER
#endif

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
    std::random_access_iterator_tag /*tag*/) noexcept -> It
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
constexpr auto is_same() noexcept -> bool
{
    return true;
}

template<typename T, typename First, typename... Tail>
constexpr auto is_same() noexcept -> bool
{
    return std::is_same<T, First>::value && detail::is_same<T, Tail...>();
}

template<bool Value, typename T = void>
using enable_if_t = typename std::enable_if<Value, T>::type;

template<typename... Ts>
struct make_void {
    using type = void;
};

template<typename... Ts>
using void_t = typename detail::make_void<Ts...>::type;

template<typename T>
using remove_ref_t = typename std::remove_reference<T>::type;

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

#if HIPONY_ENUMERATE_CPP20_OR_GREATER

template<>
struct is_string_literal<char8_t const> : std::true_type {};

#endif

template<>
struct is_string_literal<char16_t const> : std::true_type {};

template<>
struct is_string_literal<char32_t const> : std::true_type {};

template<typename T>
using is_pointer = typename std::is_pointer<T>;

template<typename T, typename = void>
struct is_container : std::false_type {};

template<typename T>
struct is_container<
    T,
    typename detail::void_t<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>>
    : std::true_type {};

template<typename T, typename = void>
struct is_iterator : std::false_type {};

template<typename T>
struct is_iterator<
    T,
    typename detail::void_t<
        decltype(std::declval<T&>() != std::declval<T&>()),
        decltype(++std::declval<T&>()),
        decltype(*std::declval<T&>())>> : std::true_type {};

template<typename T, typename = void>
struct is_tuple : std::false_type {};

template<typename T>
struct is_tuple<
    T,
    typename detail::
        void_t<decltype(std::tuple_size<T>::value), decltype(std::get<0>(std::declval<T>()))>>
    : std::true_type {};

template<typename = void, typename = void, typename = void>
struct size {
    using type = std::size_t;
};

template<typename T>
struct size<void, T, typename detail::enable_if_t<detail::is_container<T>::value>> {
    using type = typename T::size_type;
};

template<typename Size, typename T>
struct size<Size, T, typename detail::enable_if_t<std::is_integral<Size>::value>> {
    using type = Size;
};

template<typename... Ts>
using size_t = typename detail::size<Ts...>::type;

struct variadic_tag_t {};
struct variadic_array_tag_t {};
struct iterator_pointer_tag_t {};
struct iterator_tag_t {};
struct container_tag_t {};
struct tuple_tag_t {};
struct pointer_tag_t {};
struct string_tag_t {};
struct array_tag_t {};

template<typename Size, typename T, typename = void, typename...>
struct tag;

template<typename Size, typename T, typename T1>
struct tag<
    Size,
    T,
    typename detail::enable_if_t<
        detail::is_same<T, T1>() && detail::is_iterator<T>::value && detail::is_pointer<T>::value>,
    T1> {
    using type = iterator_pointer_tag_t;
};

template<typename Size, typename T, typename T1>
struct tag<
    Size,
    T,
    typename detail::enable_if_t<
        detail::is_same<T, T1>() && detail::is_iterator<T>::value && !detail::is_pointer<T>::value>,
    T1> {
    using type = iterator_tag_t;
};

template<typename Size, typename T>
struct tag<Size, T, typename detail::enable_if_t<detail::is_container<T>::value>> {
    using type = container_tag_t;
};

template<typename Size, typename T>
struct tag<
    Size,
    T,
    typename detail::enable_if_t<
        detail::is_tuple<detail::decay_t<T>>::value && !detail::is_container<T>::value>> {
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

#if HIPONY_ENUMERATE_CPP20_OR_GREATER

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

#if HIPONY_ENUMERATE_CPP20_OR_GREATER

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

template<typename... Ts>
using tag_t = typename tag<Ts...>::type;

template<typename Size>
struct dynamic_extent {
    static Size const value = static_cast<Size>(-1);
};

template<typename T, typename Size, Size N = detail::dynamic_extent<Size>::value>
class span {
public:
    using value_type      = T;
    using pointer         = T*;
    using reference       = T&;
    using const_reference = const T&;
    using iterator        = T*;
    using const_iterator  = T*;
    using size_type       = Size;

private:
    pointer   _ptr;
    size_type _size;

public:
    HIPONY_ENUMERATE_CONSTEXPR span(pointer begin, pointer end)
        : _ptr{begin}
        , _size{static_cast<size_type>(end - begin)}
    {}
    HIPONY_ENUMERATE_CONSTEXPR span(pointer ptr, size_type size)
        : _ptr{ptr}
        , _size{size}
    {}
    HIPONY_ENUMERATE_CONSTEXPR span(pointer ptr)
        : _ptr{ptr}
        , _size{N}
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

template<typename It, typename Size>
class range_span {
public:
    using iterator       = It;
    using const_iterator = It;
    using size_type      = Size;

private:
    iterator _begin;
    iterator _end;

public:
    HIPONY_ENUMERATE_CONSTEXPR range_span(iterator begin, iterator end)
        : _begin{begin}
        , _end{end}
    {}

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() const noexcept
        -> const_iterator
    {
        return _begin;
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() const noexcept
        -> const_iterator
    {
        return _end;
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

    using iterator = struct iterator {
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

        HIPONY_ENUMERATE_CONSTEXPR auto operator++() noexcept -> iterator&
        {
            _ptr++;
            return *this;
        }

        auto operator++(int) noexcept -> iterator
        {
            auto tmp = *this;
            ++(*this);
            return tmp;
        }

        HIPONY_ENUMERATE_NODISCARD friend HIPONY_ENUMERATE_CONSTEXPR auto
        operator==(iterator const& lhs, iterator const& rhs) noexcept -> bool
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
        operator!=(iterator const& lhs, iterator const& rhs) noexcept -> bool
        {
            return !(lhs == rhs);
        }
    };
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

template<typename Size, typename InnerIterator>
class iterator {
public:
    using inner_iterator  = InnerIterator;
    using inner_reference = decltype(*inner_iterator{});

    using iterator_category = std::forward_iterator_tag;
    using size_type         = Size;
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

template<typename Size, typename Container>
struct wrapper {
    using value_type = typename detail::remove_rref_t<Container>;
    using size_type  = Size;

    value_type data;

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() noexcept
        -> iterator<size_type, decltype(data.begin())>
    {
        return {data.begin()};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() noexcept
        -> iterator<size_type, decltype(data.begin())>
    {
        return {data.end()};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto begin() const noexcept
        -> iterator<size_type, decltype(data.begin())>
    {
        return {data.begin()};
    }

    HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR auto end() const noexcept
        -> iterator<size_type, decltype(data.begin())>
    {
        return {data.end()};
    }
};

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

template<typename Tag = void, typename...>
struct dispatch;

template<typename Size, typename... Ts>
struct dispatch<detail::variadic_tag_t, Size, Ts...> {
    using type = detail::tuple_wrapper<Size, std::tuple<detail::remove_rref_t<Ts>...>>;
};

template<typename Size, typename T, typename... Ts>
struct dispatch<detail::variadic_array_tag_t, Size, T, Ts...> {
    using type = detail::wrapper<Size, detail::array<detail::remove_rref_t<T>, sizeof...(Ts) + 1>>;
};

template<typename Size, typename T, typename T1>
struct dispatch<detail::iterator_pointer_tag_t, Size, T, T1> {
    using type = detail::
        wrapper<Size, detail::span<detail::remove_pointer_t<detail::remove_ref_t<T>>, Size>>;
};

template<typename Size, typename T, typename T1>
struct dispatch<detail::iterator_tag_t, Size, T, T1> {
    using type = detail::wrapper<Size, detail::range_span<detail::remove_ref_t<T>, Size>>;
};

template<typename Size, typename T>
struct dispatch<detail::container_tag_t, Size, T> {
    using type = detail::wrapper<Size, detail::remove_rref_t<T>>;
};

template<typename Size, typename T>
struct dispatch<detail::tuple_tag_t, Size, T> {
    using type = detail::tuple_wrapper<Size, detail::remove_rref_t<T>, detail::remove_cvref_t<T>>;
};

template<typename Size, typename T, typename TSize>
struct dispatch<detail::pointer_tag_t, Size, T, TSize> {
    using type = detail::
        wrapper<Size, detail::span<detail::remove_pointer_t<detail::remove_ref_t<T>>, Size>>;
};

template<typename Size, typename T>
struct dispatch<detail::string_tag_t, Size, T> {
    using type = detail::wrapper<Size, detail::zstring_view<detail::decay_t<T>>>;
};

template<typename Size, typename T, Size N>
struct dispatch<detail::array_tag_t, Size, T (&)[N]> {
    using type = detail::wrapper<Size, detail::span<detail::remove_ref_t<T>, Size, N>>;
};

template<typename Size, typename T, Size N, typename TSize>
struct dispatch<detail::array_tag_t, Size, T (&)[N], TSize> {
    using type = detail::wrapper<Size, detail::span<detail::remove_ref_t<T>, Size>>;
};

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

struct as_tuple_t {
    explicit as_tuple_t() = default;
};

template<typename T, typename... Ts>
HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR inline auto
enumerate(as_tuple_t /*_*/, T&& t, Ts&&... ts) noexcept -> detail::dispatch_t<
    detail::variadic_tag_t,
    detail::size_t<detail::void_t<>, detail::remove_cvref_t<T>>,
    T,
    Ts...>
{
    return {{static_cast<T&&>(t), static_cast<Ts&&>(ts)...}};
}

template<typename Size, typename T, typename... Ts>
HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR inline auto
enumerate_as(as_tuple_t /*_*/, T&& t, Ts&&... ts) noexcept -> detail::
    dispatch_t<detail::variadic_tag_t, detail::size_t<Size, detail::remove_cvref_t<T>>, T, Ts...>
{
    return {{static_cast<T&&>(t), static_cast<Ts&&>(ts)...}};
}

struct as_array_t {
    explicit as_array_t() = default;
};

template<typename T, typename... Ts>
HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR inline auto
enumerate(as_array_t /*_*/, T&& t, Ts&&... ts) noexcept -> detail::dispatch_t<
    detail::variadic_array_tag_t,
    detail::size_t<detail::void_t<>, detail::remove_cvref_t<T>>,
    T,
    Ts...>
{
    return {{static_cast<T&&>(t), static_cast<Ts&&>(ts)...}};
}

template<typename Size, typename T, typename... Ts>
HIPONY_ENUMERATE_NODISCARD HIPONY_ENUMERATE_CONSTEXPR inline auto
enumerate_as(as_array_t /*_*/, T&& t, Ts&&... ts) noexcept -> detail::
    dispatch_t<detail::variadic_array_tag_t, detail::size_t<Size, detail::remove_cvref_t<T>>, T, Ts...>
{
    return {{static_cast<T&&>(t), static_cast<Ts&&>(ts)...}};
}

} // namespace hipony_enumerate

#ifndef HIPONY_AS_ARRAY_ALIASED
#define HIPONY_AS_ARRAY_ALIASED
using hipony_enumerate::as_array_t;
HIPONY_ENUMERATE_CONSTEXPR auto const as_array = as_array_t{};
#endif

#ifndef HIPONY_AS_TUPLE_ALIASED
#define HIPONY_AS_TUPLE_ALIASED
using hipony_enumerate::as_tuple_t;
HIPONY_ENUMERATE_CONSTEXPR auto const as_tuple = as_tuple_t{};
#endif

using hipony_enumerate::enumerate;
using hipony_enumerate::enumerate_as;

} // namespace HIPONY_ENUMERATE_NAMESPACE

#endif
