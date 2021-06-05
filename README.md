# `hipony::enumerate`

[![Language](https://img.shields.io/badge/C%2B%2B-11/14/17/20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-BSL-blue.svg)](https://opensource.org/licenses/BSL-1.0) [![CI](https://github.com/hipony/enumerate/actions/workflows/ci.yaml/badge.svg)](https://github.com/hipony/enumerate/actions/workflows/ci.yaml)

C++11 compatible version of `enumerate`.

An adapter for "range-like" things whose value type is a struct with `index` and `value` members representing respectively the position and the value of the elements of the passed range.

It resembles the `views::enumerate` proposal vaguely, but not based on C++20 ranges.

```cpp
#include <hipony/enumerate.hpp>
#include <iostream>

int main() {
    using hipony::enumerate_as;
    for(auto&& [index, value] : enumerate_as<int>(0, 1, 2, 3, 4)) {
        std::cout << index << ' ' << value << '\n';
    }
}
```

## Performance

[Compiler Explorer](https://godbolt.org/z/TGM5Wfaeh)

## Notes

* With C++17 structured bindings we can bind member variables to convenient aliases
* With C++14 we can use `enumerate` in constexpr context
  * On MSVC requires at least v19.15 for that
* With C++14 we can use `enumerate` with tuples via `.each` member function. It requires `auto` lambda parameters for it to work.

## Features

### As Size

> If the size of a container is bigger than the maximum value for the specified type - the behavior is undefined.

```cpp
// C++17
#include <hipony/enumerate.hpp>
#include <type_traits>

int main() {
    using hipony::enumerate_as;
    for(auto&& [index, value] : enumerate_as<int>(0, 1, 2, 3, 4)) {
        static_assert(std::is_same_v<int, decltype(item.index)>);
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
    for (auto&& [index, value] : enumerate(0, 1, 2, 3, 4)) {
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
        for (auto&& item : enumerate(0, 10, 20, 30, 40)) {
            if (item.index == 4) {
                return item.value;
            }
        }
        return 0;
    }
};
```

### Tuples

```cpp
// C++14
#include <hipony/enumerate.hpp>

#include <iostream>

int main() {
    using hipony::enumerate;
    enumerate(0, 1., "string").each(auto index, auto& value) {
        std::cout << value << '\n';
    });
}
```

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

### C-Strings

```cpp
#include <hipony/enumerate.hpp>

#include <iostream>

int main() {
    using hipony::enumerate;
    auto string = "01234";
    for (auto&& item : enumerate(string)) {
        std::cout << item.index << '\n';
        std::cout << item.value << '\n';
    }
}
```

### Pointers + Size

```cpp
#include <hipony/enumerate.hpp>

#include <iostream>

int main() {
    using hipony::enumerate;
    int        ptr[] = {0, 1, 2, 3, 4};
    auto const size = 3;
    for (auto&& item : enumerate(&ptr[0], size)) {
        std::cout << item.index << '\n';
        std::cout << item.value << '\n';
    }
}
```

## Installation

It's a single-file header-only library, so you can put the `hipony/enumerate.hpp` in the `include` folder directly into the project tree.

Alternatively, project provides CMake instructions for usage with `add_subdirectory` or `cmake install`.

## Developing

Project provides a `conanfile.txt` to pull in dependencies for testing, but uses a transparent integration otherwise. If used with another package manager - one should make sure the directory with config files is visible for `find_package`.

## References

* [Ranges-based Implementation](https://github.com/cor3ntin/rangesnext)
* [Standard Proposal](https://wg21.link/p2164)

## License

[BSL-1.0](./LICENSE)
