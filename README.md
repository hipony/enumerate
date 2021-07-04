# `hipony::enumerate`

[![Language](https://img.shields.io/badge/C%2B%2B-11/14/17/20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-BSL-blue.svg)](https://opensource.org/licenses/BSL-1.0) [![CI](https://github.com/hipony/enumerate/actions/workflows/ci.yaml/badge.svg)](https://github.com/hipony/enumerate/actions/workflows/ci.yaml)

C++11 compatible version of `enumerate`.

An adapter for "range-like" (and more) things which provides a range with a value type of struct with `index` and `value` members representing respectively the position and the value of the elements of the passed range.

It's partially based on the `views::enumerate` proposal, but extends its features greately.

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

[Compiler Explorer](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAM1QDsCBlZAQwBtMQBGAFlJvoCqAZ0wAFAB4gA5AAYppAFZdSrZrVDIApACYAQjt2kR7ZATx1KmWugDCqVgFcAtrRABmXlfQAZPLUwAcs4ARpjEIABspAAOqEKE5rR2ji7uvLHxZnS%2B/kFOoeFRxpimiQwEzMQEyc6uHkaYJlm05ZUEOYEhYZFGFVU1qfVCfe1%2BnfndEQCURqgOxMgcUjpufsiOWADUOtoIBATRQiAA9MfEzADuAHTAhAgOwQ4iC3QEVgRXaE7HCHixtABPY5WZxhZhvY5OZjDMLHNYbTA/P50IEgpxgt5XBDRaI7TQyACC%2BKJ2lWtHWDi2mjcNkq5wB1OwxJW8MpmG2NPMw2ImGYTkZzMJzAcRB0EU2VAc5OaEGG6BAIDpzAZnPopE2nAiAu04qVAKm2wA7PpCSyqNZMFRNgIAOLeACaxM2zolJAgwtFOrF2wArLo/FhxOqAG5sByYTQ%2BgAimxAm1%2B/wBCrRGMw7uI9KmBs0xqdLvzocc7IAVNSYwHMOJqSaCfmc1HmaTGiI8865Qr4gAvTAAfQImwr4g5MZk1dbruIm3dItQYu9hfDsc2euzucJ%2BYLYZLZYHFqrbhrG5dBgMg7H6%2BPhobpqb1jwVHHPII81oy4zyvPRKvxKkM1Y0h9eRXFkeRUGkGwTz0TYhDmBZ2RWTh5AIaQ5CzUgAGsQG4TgrhkTg3AADk4ABOfDtB9bgZG4KJ/ykbggJQ0DpHkI4ZFIZCQJmOBYBgRAUFQJxojwdgyAoCAviEkSUFUdQ%2B2IKV0L4YS3mII4IGCRjSGCPxKiTKRENIL50XoAB5WhWD0uRSCwKF1HYTT8B5Upg0wI4QNISsShFJYrL8N5aKs1g8GCc5iABOwsGkAyCGIPAnCi38%2BFeJg2A4HgksEEQJE0pROBUNQNEgwwguCI5YFoPkOCoJwCFIFzwhihS0NQaJmjcgBaEy3E2dq5TLLQ9AMbRmB6gB1NhWE2FjGhKZpLGsAZXDyrwOjyAplAyBI6EWja4i22hVq6cI8uKUo6Fafp7FqZRTuaC7RlyI6bpGHaTpGQ6JmOmYYPmRYuD/ACGPcsCpHEAiInaiJuE2dYCqnRraHQg0IFwQgSG2Uk8s2OxBOEsIMbcTgDQgwa9CQxi0Mw7hDSucGZDcH08Mo0lDQiPLaPo0h4sNGQrgiAjKPB7hCcJ/m3FIYCrJBliQDYjjUNIbi%2BLmA4RXISgJLx46PPwIhtf4RgWHszg2IN4QxEkdyLnOaIEoBqRAIlzSQZMkVohFTZUCtMGIahmGZOAeH5MR5Gcck/GEKmcnOJmBBeSwcIIHtzn4u0YirkJn1SIZ/mxc4Q0neB5ijFl9iKZmTDNSuH03GImRiMNH0Im0GR%2BZ9bQVGkNwgal4v5cSpXB6QTWRPV8SBPD8JYdkhHFKoZSwjUjT3O0iqwoSwyBOMggzIshzMFs4B7PcxzZrwFy3KszzkG8je/MaTSStC8KMCWaLYvi/TEoNlLjd4M2sqWyskoDuAcUBFRUMFMqSdSAtTatITq3VeoEHQP1Iqw0xoTWdO1KMtoHTTSaIkeatgrqpGWtYD6608qbWaK9GIe1miUO6CdGaZ0WgvVIUtBohDzrvTGGtZhvQ2h0OGG0JhX1Zi/TSvbR2ksmKg3BpDaG09A4QFnsjVGesCZYzDlrAm2hiZFWjqhCu7g3AZzcJYqx1irGdzovIbmOFiI6g8JRCIrduAtx9IXXuUgZZywporXiEAkAq3drVMSI9ugd0wLrEgygf5GzSv/V45tspWxtnbOxsjnbSFdqrfsXtNg%2ByUf7OGajg5IynLokS%2Bio5lxjqQOOzAE6UGTg4kA2gCK4UNG4CIPos61wZoaYi3BvFyNgcXViDSTEYS4DTbg1MZAEUsTIGupEZDkTsd3Hx8jjED2CUgfAVAqBj0SalLgKTMoW0fggI47M7nHKoAQAE0QOBsWIHczppBPlCCeS8t5ssZE93kVGe83tFF%2BxUUHJqmxgxCGKZC5RAcYUh32ZTTp3iOYgsmX4kuATGm0W0Di6WMzfwzHqvECw3AgA%3D%3D%3D)

## Notes

* With C++17 structured bindings we can bind member variables to convenient aliases

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

### Ranges

> Note, Clang doesn't yet have full support for Concepts and Ranges

When you pass an lvalue expression to `enumerate`, then the result type will satisfy the `std::ranges::view` concept, allowing to use the function directly with range adapters.

When you pass an rvalue expression to `enumerate`, then the result type will satisfy the `std::ranges::range`, which requires an out of line declaration.

```cpp
// C++20
#include <hipony/enumerate.hpp>
#include <array>
#include <iostream>
#include <ranges>

int main() {
    auto array = std::array{0, 1, 2, 3, 4, 5};
    for(auto&& [index, value] : hipony::enumerate(array) | std::ranges::views::take(3)) {
        std::cout << index << ' ' << value << '\n';
    }

    auto range = hipony::enumerate(std::array{0, 1, 2, 3, 4, 5});
    for(auto&& [index, value] : range | std::ranges::views::take(3)) {
        std::cout << index << ' ' << value << '\n';
    }
}
```

[Compiler Explorer - Codegen Comparison](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAM1QDsCBlZAQwBtMQBGAFlJvoCqAZ0wAFAB4gA5AAYppAFZdSrZrVDIApACYAQjt2kR7ZATx1KmWugDCqVgFcAtrWVX0AGTy1MAOWcARpjEINoypAAOqEKE5rR2ji7KUTFmdF4%2B/k5BIWFGmCZptAwEzMQECc6unPmFcSVlBBl%2BgcGh4UKl5ZVJNZ2NzVk57QCURqgOxMgcUjoAzN7IjlgA1DraCAQEEUIgAPR7xMwA7gB0wIQIDgEOIlN0BFYEp2hOewh4UbQAnntWzsFmI89k5mJ1gntFstMO9PnRfv8nIDHqcEBEIutNDIAIJY3HaBa0JYOVaaOY2MpHb5k7B4%2BZQkmYNbk8ydYiYZhOGl0nHMBxEHQANhWVAcRKKEE66BAIEpzGpLPopBWnEF3O0wrl3xGawA7PocfSqNZMFQVgIAOIeACaeJW9pFJAgfIFGqFawArLpvFhxMqAG5sByYTQegAiKxAKw%2BX2%2BMsRyMwzuIVOVPAcIx1mn1dodecDjiZACoyRGfZhxGSDdi89mw3SCQURLn7VKZTEAF6YAD6BBW5fEzIjMirLcdxGd/NQQvdBeDkZWWr1NhWbZAR3UmF2IH9eEwx23pQA1kmeJm9dW8/mg8XS/2TZW5per/aDAYB6OcbXdfXDY3rHgVBjuyBCTLQi4pvKn64j%2BeJSGMrDSB68iuLI8ioNINhvnoq4TFMTLzJw8gENIciZqQR4gHMAAcpy6tR3DUTIGoAJzcDw3C6mxKjSNwKGkeh0jyLs4QkWhYxwLAMCICgqBOBEeDsGQFAQK8ClKSAwBCLQzA7AgqAEHwimPMQuwQAEAmkAE3hlHGUhEaQrxIvQADytCsHZcikFgoLqOwln4Oyph4P6W6WRWmDIPyMxed4jyIWhKh4AERzEN8dhYNIDkEMQeBOFl8F8A8TBsBwPBFYIIgSJZSg1Ko6goNhhisMluywDpSIgFQTiGaFIQ5WKR7kagERFLsUgALQuXMKwTVKpZaHoBjaMws0AOpsKwKzCQUkVFJY1g9NUpDuIMrQhDUKSxHQR3JNE120Gd2RtH0u3BXQDTdPYVTKMYe31F0TTeC0z0XUYgO3X0gNPcMnBjEIeHTFwCFIfxiUYVI4jUYKE2CtwKzAMgyArBAA20ENJO4IQJBrASNQrHY8mKcEtNzHDDNNcRAnkZRnGnNjMhzB6Mg8Mxcy6oKdW8fI%2BW6jIpyCgxMjY9wbNs4rcykKhXkY8JICidzpCSTJEzbPy5CUGpzNg5g%2BBEGD/CMCw/mcOEjvCGIkiJccRwRAVKNSMhWuWRjLn8hE/IrKgZpYzjeME0TJNkxTECM%2BpLOESMXPiWMCAclgIQQAHfGkPl2gsacbMeixnBC4rGucLqwfo0JRj66QYlkWMlGcLRLH99RHq6rXuraLqnGCjxUhzGjOut53hXG0vSBW0pFuqXJ6chFpOl6QZRmsCZZkWYl1k6WlBWOXJzkEG5HkBZgvnAP5iWBf9oXjV5EVRY8l9xQUlkWopVshlGY2Vcr5XsoVR2JUXa8HdlVL2XklDaBUGoDQTUkoBDakXUgI0xrSCmjNOaBB0ALSaitdam17QTTDJaG0O06gWAgO4SGJ1rAwxepEe6RQ2FXSKJwsGf13rFAht9XotR/ofWhsDIYXD%2BhfUSMdBRQNMjnWRuMSYSM4ZTyDtrQSmNsa43xoTYmpNiCDR1BAKm9tWb0zTtbVm2gdRYSWnobOXcKJUTmJXOYfj/EBP8VPEustOCnBYhqOY3BuAyEFLE7gYQPTNznlIPWBtxJG2khAJApsI6GRUqvNoqDbbUwdsVZ2ZV4EPA9tVb2vt/a6NngYsOZs%2BzRxWLHYxCczHJysQ4pSTis4d25rnfObRcEJRCaEWiMhdRzEFB6aucwWJCy4twJJ%2Bi8GtxEsMnOXjG6nG0JwD0USRaKw9ExaJU8Z7JIMR4xeWSkD4CoFQdeMCKlcCqZVT2gCEC7Dqn855VACDfAiBwcIxA/mhFIJCoQQKQVgv1gHPRIdpBhkAjHIx8dTFJwseTHU/ohAdKxSYxO5jLH3J5qEJJkymlbNSW3dJniEraDpbrXZni%2BoxAsNwIAA%3D%3D%3D)

### Sentinels

> Requires C++17

```cpp
#include <hipony/enumerate.hpp>

#include <iostream>
#include <list>

struct sentinel {
    friend auto operator==(std::list<int>::const_iterator const& it, sentinel) -> bool
    {
        return *it == 3;
    }
};

int main() {

    auto const list = std::list<int>({0, 1, 2, 3, 4});

    using hipony::enumerate;
    for (auto&& [index, value] : enumerate(list.begin(), sentinel())) {
        std::cout << index << ' ' << value << '\n';
    }
}
```

[Compiler Explorer - Codegen Comparison](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAM1QDsCBlZAQwBtMQBGAFlJvoCqAZ0wAFAB4gA5AAYppAFZdSrZrVDIApACYAQjt2kR7ZATx1KmWugDCqVgFcAtrRAA2UlfQAZPLUwAcs4ARpjEXADspAAOqEKE5rR2ji7uMXEJdL7%2BQU6h4ZxRxpimiQwEzMQEyc6uHsWldOWVBNmBIWGRRhVVNan1Pa1%2B7XmdhQCURqgOxMgcUjoAzH7IjlgA1DraCAQE0UIgAPSHxMwA7gB0wIQIDsEOIrN0BFYEF2hOhwh4sbQAnocrM4wswXocnMwhC9iIcVmtMF8fnQAUCnCCXhcENFoltNDIAIJ4wnaZa0VYODaaRY2Vh4KFU7BEpZwimYTbU8xQ4iYZhOBlMglchymdYiejDVibCL6AnrOXrKjEPBedbMBxEdaoaLokhUgAi%2BogUPQIBAtPpHPoDNNaFoUIA%2BoQdcR1rb6do3OtCKRRa8JeN1gBaBnrYKoexE%2BVSmX4qNR7kEGa0dYAKkI7INiz160WVJjUc0EQNBMLmZjRLVRB0nqoDjJZjoRoIJrNdIIVJsfnbi0ZHvW5oIAcL5ZJeCo1kwVHWAgA4t4AJqR%2BU0YgQSuoavVzYAVl0fiw4h9ADc2A5MJpt9mQOtvr8/qbUejMBABxdQtdaBBJr7xf5WMPS3GIdpSXON1hPRw2RTfUvQncQ81AqVi2JRZMFYEREONU14gAL0we0CFgg8M3WGQENlZcSHWNd1Q3D0twgs91mvAdgPzMCvSnCBGLZfUYMWNjEI40NuWYABrcjYw40shPlHjUxg/dMHgxZ2LAgwDCUlS1KQpkSS8MdEITJN%2BzbSSZIJKRJlYaRt3kVxZHkVBpBsDS9FFaZZl4klOHkAhpDkIDSDEkBFm3C5twADm4bRuAATgiSKIgiGRIs4OLtxUaRuHsgKnOkeQDhkUh/McyY4FgGBEBQVAnGiPB2DICgIA%2BerGpAYAhFoZh9gQVACD4BroQOCBgjy0hgj8Sp7ykXzSA%2BNF6AAeVoVgZrkUgsAhdR2HG/BuVKI9MAORzPHEEp1XmDauzQ8baWCU5iD%2BOwsGkOaCCVJw3qsvhniYNgOB4X7BBECRxqUTgVDUDQ3MMe6Dlgbq0RAKgnAGo7wg%2BusxKCrUGztaRAyWxYg2NfUtD0AxtGYIMAHU2ElQq0JKfHLGsPpXEhrw2lyfJlFieJ8Y5/mMnxnmOgKIxmcaWhml6examUBp8bloYcglpXBmFyGoRacXRgKSYhE8uYuGs2zctO5ypHESK3EDNxuHWYBkGQaisdoHHqNwQgqKWSH1jsOqGrCTYfIDVzKb0Py8qCkLuAiC47ZkMKZB4GQSQiNxIZsqQctIL6UouNxotSx3Fk4CuS8WUgHI263CpAYrSsC0gKuq6Y9nVchKFakPJcwfAiEl/hGBYXbOGK0fhDESRTrOU5om%2B82pDs2vxutpb1WidVNSnW37cd53Xfd4hsYDCAg7a0P/fGGOysmBAeSwcIvyyvP5C%2B7Q4ouCvtziyu24S7V0KOvK2BUjBNxKrHSYIVtCcGLiSbgbgIgxQ9OlIGudFiW3rhAluP126EKQH3RqPcWq1WvuETq3Ver9UGqwYalAxqnUmt1J6315q1UWgQFaa09qYG2sAXap19oszwEdE6G1lIXReBwm6ucNr3Ues9DA8x3qfWXsDMeAMuC8GnqDOeG0lDaChuoFAsMVB4GCAjN%2BeNEgnSJiTQMZMswU30HoamdMGZykDHqWcC4mYmFZhALw2tPDWH1nzSGAtMhJAVqkaJotEiRLGFLIJZQtbxM5mksRTRBgpMlrreWKRslFLViMKJRsTaAxXmvOu%2BUbZ2wdk7F2bsIAey9hAH2w8w4Vx9FffuvTtAR1hvfQKsDQqLF/osGZsy5mzPfvnQuCC4oekWNwbgMg3BbJijITK9TSAN0gc3WObcqoQCQJ3HeA1mokM6CYwevsR5/XHoDPRzwZ5g3novTRuc6kb2kFvLuhFUD7yaUfVpp9z7UQGY1IZd9oEP1IE/ZgL9KAryWSAbQkULgyAiIsNw25/6LDimFCIcVuD7IBVIRuJykUhUKBccl2hsXaESnFFBHoPBYJwQ0sZBDzlIHwFQKgZDR7/Qnu8kGs87oIAODnOVwqqAED%2BNqKBxA5VYtIBqoQSqVVqpkLU3lhzpB6jHGCw%2BLST7tLPp7AMR4hDrAPs04%2BbSOkIvwXHLFmVc75wOUcoqiLxnv20Mao5nrJgY3iBYbgQA%3D)

### Constexpr

> Requires C++14

On MSVC requires at least VS2019 (v19.20). But works only with value enumeration before v19.28, eg `for (auto item : enumerate(as_array, 0, 1, 2, 3, 4))`, but not anything that references anything.

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
    enumerate(aggregate).each([](auto index, auto&& value) {
        std::cout << index << ' ' << value << '\n';
    });
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

### Package Managers

* [Conan](https://conan.io/center/hipony-enumerate)

### Manual

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
