# `hipony::enumerate`

[![Language](https://img.shields.io/badge/C%2B%2B-11/14/17/20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-BSL-blue.svg)](https://opensource.org/licenses/BSL-1.0)

C++11 compatible version of `enumerate`.

An adapter for "range-like" things whose value type is a struct with `index` and `value` members representing respectively the position and the value of the elements of the passed range.

It doesn't resemble the `views::enumerate` proposal since it's not based on C++20 ranges concepts.

Supports containers, variadic packs, pointer and size pairs, c arrays.

## Performance

[Compiler Explorer](https://godbolt.org/z/s7eWbnhEd)

## Examples

### Variadic Packs

```cpp
#include <hipony/enumerate.hpp>

#include <iostream>

int main() {
    using hipony::enumerate;
    for (auto&& [index, value] : enumerate(1, 2, 3, 4, 5)) {
        std::cout << value << '\n';
    }
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
    for (auto&& [index, value] : enumerate(std::vector{1, 2, 3, 4, 5})) {
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
    auto const vec = std::vector{1, 2, 3, 4, 5};
    for (auto&& [index, value] : enumerate(vec)) {
        static_assert(
            std::is_same_v<int const&, decltype(value)>);
        std::cout << value << '\n';
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
    for (auto&& [index, value] : enumerate(container)) {
        std::cout << value << '\n';
    }
}
```

### Pointer + Size

```cpp
#include <hipony/enumerate.hpp>

#include <iostream>

int main() {
    using hipony::enumerate;
    auto       container = "01234";
    auto const size      = 5;
    for (auto&& [index, value] : enumerate(container, size)) {
        std::cout << value << '\n';
    }
}
```

### Container + Size

```cpp
#include <hipony/enumerate.hpp>

#include <vector>
#include <iostream>

int main() {
    using hipony::enumerate;
    auto const vec  = std::vector{1, 2, 3, 4, 5};
    auto const size = 3;
    for (auto&& [index, value] : enumerate(vec, size)) {
        std::cout << value << '\n';
    }
}
```

### C Array + Size

```cpp
#include <hipony/enumerate.hpp>

#include <iostream>

int main() {
    using hipony::enumerate;
    int        container[] = {0, 1, 2, 3, 4};
    auto const size = 3;
    for (auto&& [index, value] : enumerate(container, size)) {
        std::cout << value << '\n';
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
