# `hipony::enumerate`

[![Language](https://img.shields.io/badge/C%2B%2B-11/14/17/20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-BSL-blue.svg)](https://opensource.org/licenses/BSL-1.0) [![CI](https://github.com/hipony/enumerate/actions/workflows/ci.yaml/badge.svg)](https://github.com/hipony/enumerate/actions/workflows/ci.yaml)

C++11 compatible version of `enumerate`.

An adapter for "range-like" (and more) things which provides a range with a value type of struct with `index` and `value` members representing respectively the position and the value of the elements of the passed range.

It resembles the `views::enumerate` proposal vaguely, but not based on C++20 ranges.

```cpp
#include <hipony/enumerate.hpp>
#include <array>
#include <iostream>

int main() {
    std::array array{0, 1, 2, 3, 4, 5};
    for(auto&& [index, value] : hipony::enumerate(array)) {
        std::cout << index << ' ' << value << '\n';
    }
}
```

## Performance

[Compiler Explorer (iostream)](https://godbolt.org/z/6Ej7e5M3r)

[Compiler Explorer (printf)](https://godbolt.org/z/95qr1arcW)

## Notes

* With C++17 structured bindings we can bind member variables to convenient aliases
* With C++14 we can use `enumerate` in constexpr context
  * On MSVC requires at least v19.15 for that, but only works with value enumeration before v19.28, eg `for (auto item : enumerate(as_array, 0, 1, 2, 3, 4))`, but not anything that references anything.
  * On GCC requires at least 5.4
* With C++14 we can use `enumerate` on tuples with lambdas with `auto` parameters. In C++11 we'd need to create a function object with appropriate overloads.

## Features

### `_as<type>` to specify the type of the `index` to cast to

> If the size of a container is bigger than the maximum value for the specified type - the behavior is undefined.

```cpp
// C++17
#include <hipony/enumerate.hpp>
#include <type_traits>

int main() {
    using hipony::enumerate_as;
    using hipony::as_array;
    for(auto&& [index, value] : enumerate_as<int>(as_array, 0, 1, 2, 3, 4)) {
        static_assert(std::is_same_v<int, decltype(index)>);
    }
}
```

### Constexpr

```cpp
// C++20
#include <hipony/enumerate.hpp>

consteval auto get() -> int
{
    using hipony::enumerate;
    using hipony::as_array;
    for (auto&& [index, value] : enumerate(as_array, 0, 1, 2, 3, 4)) {
        if (index == 4) {
            return value;
        }
    }
    return 0;
}
```

```cpp
// C++14
#include <hipony/enumerate.hpp>

struct function_object {
    constexpr auto operator()() const -> int
    {
        using hipony::enumerate;
        using hipony::as_array;
        for (auto item : enumerate(as_array, 0, 10, 20, 30, 40)) {
            if (item.index == 4) {
                return item.value;
            }
        }
        return 0;
    }
};
```

### Tuples

For tuples we use a special member function `.each`. The library checks for a tuple protocol with `std::tuple_size` specialized, so practically a user should be able to pass a custom tuple. You also can directly invoke the overload with a special `as_tuple` tag.

```cpp
// C++14
#include <hipony/enumerate.hpp>

#include <tuple>
#include <iostream>

int main() {
    using hipony::enumerate;
    std::tuple tuple = {0, 1., "string"};
    enumerate(tuple).each([](auto index, auto& value) {
        std::cout << value << '\n';
    });
}
```

```cpp
// C++14
#include <hipony/enumerate.hpp>

#include <iostream>

int main() {
    using hipony::enumerate;
    using hipony::as_tuple;
    enumerate(as_tuple, 0, 1., "string").each([](auto index, auto& value) {
        std::cout << value << '\n';
    });
}
```

```cpp
// C++11
#include <hipony/enumerate.hpp>

#include <iostream>

struct function_object {
    template<typename Size, typename T>
    void operator()(Size index, T& value) {
        std::cout << index << ' ' << value << '\n';
    }
};

// or
// struct function_object {
//     void operator()(std::size_t index, int& value) {
//         std::cout << index << ' ' << value << '\n';
//     }
//     void operator()(std::size_t index, double& value) {
//         std::cout << index << ' ' << value << '\n';
//     }
//     void operator()(std::size_t index, char const(&value)[7]) {
//         std::cout << index << ' ' << value << '\n';
//     }
// };

int main() {
    using hipony::enumerate;
    using hipony::as_tuple;
    enumerate(as_tuple, 0, 1., "string").each(function_object{});
}
```

### [Optional] Simple Aggregates via `boost/pfr`

> Requires C++17

To enable the integration, use the `HIPONY_ENUMERATE_AGGREGATES_ENABLED` CMake option.

```cpp
#include <hipony/enumerate.hpp>

#include <string>
#include <iostream>

struct aggregate_t {
    int         i;
    double      d;
    std::string str;
};

int main() {
    using hipony::enumerate;
    auto aggregate = aggregate_t{0, 1., "2"};
    for (auto&& [index, value] : enumerate(aggregate)) {
        std::cout << value << '\n';
    }
}
```

The project uses Conan-provided config files for the `pfr` for dev purposes, but in practice a user only need to make sure that the header is visible when the option is enabled.

### Containers

```cpp
#include <hipony/enumerate.hpp>

#include <array>
#include <iostream>

int main() {
    using hipony::enumerate;
    auto array = std::array{1, 2, 3, 4, 5};
    for (auto&& [index, value] : enumerate(array)) {
        std::cout << value << '\n';
    }
}
```

```cpp
#include <hipony/enumerate.hpp>

#include <vector>
#include <iostream>

int main() {
    using hipony::enumerate;
    for (auto&& item : enumerate(std::vector<int>{1, 2, 3, 4, 5})) {
        std::cout << item.index << '\n';
        std::cout << item.value << '\n';
    }
}
```

### Container + Size

> If the size is a negative number - the behavior is undefined.
> If the size is bigger than the container.size() - enumeration will end at the container.size()

```cpp
#include <hipony/enumerate.hpp>

#include <array>
#include <iostream>

int main() {
    using hipony::enumerate;
    auto array = std::array{1, 2, 3, 4, 5};
    for (auto&& [index, value] : enumerate(array, 3u)) {
        std::cout << value << '\n';
    }
}
```

### Begin + End

> If the End iterator is not reachable from the Begin iterator - the behavior is undefined.

```cpp
#include <hipony/enumerate.hpp>

#include <list>
#include <iostream>

int main() {
    using hipony::enumerate;
    auto list = std::list{1, 2, 3, 4, 5};
    for (auto&& [index, value] : enumerate(list.begin(), list.end())) {
        std::cout << value << '\n';
    }
}
```

### Const Propagation

```cpp
#include <hipony/enumerate.hpp>

#include <vector>
#include <iostream>
#include <type_traits>

int main() {
    using hipony::enumerate;
    auto const vec = std::vector<int>{1, 2, 3, 4, 5};
    for (auto&& item : enumerate(vec)) {
        static_assert(
            std::is_same<int const&, decltype(item.value)>::value);
        std::cout << item.index << '\n';
        std::cout << item.value << '\n';
    }
}
```

### C-Arrays

```cpp
#include <hipony/enumerate.hpp>

#include <iostream>

int main() {
    using hipony::enumerate;
    int container[] = {0, 1, 2, 3, 4};
    for (auto&& item : enumerate(container)) {
        std::cout << item.index << '\n';
        std::cout << item.value << '\n';
    }
}
```

### C-Strings (null-terminated)

```cpp
#include <hipony/enumerate.hpp>

#include <iostream>

int main() {
    using hipony::enumerate;
    for (auto&& item : enumerate("01234")) {
        std::cout << item.index << ' ';
        std::cout << item.value << '\n';
    }
}
```

### Pointers + Size

> If the size is a negative number - the behavior is undefined.

```cpp
#include <hipony/enumerate.hpp>

#include <iostream>

int main() {
    using hipony::enumerate;
    int        ptr[] = {0, 1, 2, 3, 4};
    auto const size = 3u;
    for (auto&& item : enumerate(&ptr[0], size)) {
        std::cout << item.index << '\n';
        std::cout << item.value << '\n';
    }
}
```

## Installation

It's a single-file header-only library, so you can put the `hipony/enumerate.hpp` in the `include` folder directly into the project tree.

Alternatively, project provides CMake instructions for usage with `add_subdirectory` or `cmake install`.

```cmake
find_package(hipony-enumerate)
target_link_libraries(app PRIVATE hipony::enumerate)
```

## Compatibility

The library provides the `HIPONY_ENUMERATE_NAMESPACE` macro to specify a different from the default `hipony` namespace. It encapsulates all the internals in the `hipony_enumerate` namespace to avoid accidental ODR conflicts by changing the external namespace.

Additionally, library uses tag types `as_array_tag_t` and `as_tuple_tag_t` in the interface. For potential reuse in other libraries in the `hipony` namespace or related, they are encapsulated by the `HIPONY_AS_ARRAY_HPP_INCLUDED`/`HIPONY_AS_TUPLE_HPP_INCLUDED` guards with additional flags `HIPONY_ENUMERATE_AS_ARRAY_ENABLED`/`HIPONY_ENUMERATE_AS_TUPLE_ENABLED` to force the declaration of the types.

## Contributing

Project provides a `conanfile.txt` to pull in dependencies for testing, but uses a transparent integration otherwise. If used with another package manager - one should make sure the directory with config files is visible for `find_package`.

## References

* [Ranges-based Implementation](https://github.com/cor3ntin/rangesnext)
* [Standard Proposal](https://wg21.link/p2164)

## License

[BSL-1.0](./LICENSE)
