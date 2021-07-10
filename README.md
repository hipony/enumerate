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

[Compiler Explorer](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAM1QDsCBlZAQwBtMQBGAFlJvoCqAZ0wAFAB4gA5AAYppAFZdSrZrVDIApACYAQjt2kR7ZATx1KmWugDCqVgFcAtrWVX0AGTy1MAOWcARpjEINoypAAOqEKE5rR2ji7KUTFmdF4%2B/k5BIWFGmCZptAwEzMQECc6unPmFcSVlBBl%2BgcGh4UKl5ZVJNZ2NzVk57QCURqgOxMgcUjoAzN7IjlgA1DraCAQEEUIgAPR7xMwA7gB0wIQIDgEOIlN0BFYEp2hOewh4UbQAnntWzsFmI89k5mJ1gntFstMO9PnRfv8nIDHqcEBEIutNDIAIJY3HaBa0JYOVaaOY2MpHb5k7B4%2BZQkmYNbk8ydYiYZhOGl0gkM0nkgjfCKYAD6BCOhCE3JxeOYDiIOgAbCsqA4iUUIJ10CAQJTmNSWfRSCtOIrudplXrviM1gB2fQy3lUayYKgrAQAcQ8AE08St/SqSBA5QqLUq1gBWXTeLDiY0ANzYDkwmgjABEViAVh8vt8dYjkaKwWSbN4CDTg8QqSMbZp7X6A43%2BmZkCKwXcCJqCNqQHghCKhJzRfGS2XjVgloLhRAY5hxCMaQu5g7sY3G4nHEyAFRkjOz8RkleNutpnlzAoiBv%2BmjEGf0Fb75kZmSHh8u8TMmwrK2nGIAL0wCAl10NY9AMfda3rHE1wDK1U2jd9UwzHc5j3RDlyvO1T0dc9rDwKhMPZAhJlob8q31Q86VtbDsSkMZWGkCN5FcWR5FQaQbAMAwViECYpiZeZOHkAhpDkGtSAAaxAbhOFOGRODmAAOTgAE4FO0CNuBkbhFRUaRuGY0S2OkeRdnCETWLGOBYBgRAUFQJwIjwdgyAoCBXiclyUFUdQxWINUJL4ZzHmIXYIACIzSACbwyjzKQhNIV4kXoAB5WhWDiuRSCwUF1HYSL8HZUw8HjTBdlY0g50wZB5RmLKywKSLWDwAIjmIb47CwaQEvFPAnG6ui%2BAeJg2A4HghsEEQJEipQah8jQuL0FQWt2WBaCHEAqCcAhSFKkJxQC8TUAiIpyoAWhSuYVjOrVdy0MC9G0ZhroAdTYVgVlMgpqqKSxrB6apKusQZWhCGoUliOgAeSaJIdoEHsjaPpvuKugGm6ewqmUYwfvqLomm8FpEbBox8ehvp8YR4ZODGXjJmmLh6MYwyKvYqRxEUxUzsVbgViWNRgBWCADtoCSbQgXBCBIUC5hqFY7Ec5zghlmn5cW3RhKM8SpO4W1Tk5mQ5gjeStIJW1FTm/T5H620ZFORVFK0znuFl2WHbmUgWKytnTJAcytdIay7ImbZ5XISgPKVknMHwIgSf4RgWHyzhwgT4QxEkCrjiOCIBqZqQmM9yK2ZS%2BUInlFZUDdDmuZ5vn5qFkWxaFhXPOVwSRk1yyxgQDksBCIC9KkAzSH67QVNOWWIzUo2HfdzhbSL1mTKMP3SAssSxik01TgjOYVJkFTbQjRUwgdiNtCHuYWe9leN8GoPH6QSOXPD9yHLbkJ%2Bd8pugtYEKwoRQqtFda7UBqJQcslAgaUMoFUwLlYA%2BUKqFVxqVcqWUqo1UeOAhqDEKrNVarFTqMwerED6nnCaidRpcF4GnKamcspKEvvNFA6tloBFWoPY6p1pAXSujdbsd11ZPVeu9f0Z00yeh9F9OoFgIDuHJkDTwhMhhI0iLDIoiiIZFCpmonGqNihk0xr0WouM0aUxUaDbGRjEiA36OUXRYNaZ8QZjTIehcvbGXZpzbmvNv6C2Fv5UW4tJZxxVsaVuUcZbaBtJxB6Gt15ay3iAOYcxJ6pIyZkzJQ8R421kipC0cxuBaUVDIHmYQIxL1vlIX2/tLKB1shAJAIdy47Tci/Nol8Y5S3jsNJOY1aEPHTtNLOOcKF4I8cXaQpdQ4EErtXHxdd/GNyCc3CAkSXLRM7ok7upBe7MH7pQfOuTQiKTkraOYioIzT33kbW0KluCVM8aQH2q86mb0klwPWxTbaKVSTIPeakZAaSvjfLxXcxINPgE0kA%2BAqBUDfgnEaydBmTQzk1BAuw5qYrhVQKcHBwjEExaEUgRKhC4vxX7fOkzl5SDTPhBZtc/EN0CYdFY8YhArBrr4%2BuAsVmHQhXRZJIK8Ej2ea8syOyPl4O0GCl5d8km7WCDECw3AgA%3D%3D)

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
    for(auto&& [index, value] : array | hipony::enumerate() | std::ranges::views::take(3)) {
        std::cout << index << ' ' << value << '\n';
    }

    auto range = hipony::enumerate(std::array{0, 1, 2, 3, 4, 5});
    for(auto&& [index, value] : range | std::ranges::views::take(3)) {
        std::cout << index << ' ' << value << '\n';
    }
}
```

[Compiler Explorer](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAM1QDsCBlZAQwBtMQBGAFlJvoCqAZ0wAFAB4gA5AAYppAFZdSrZrVDIApACYAQjt2kR7ZATx1KmWugDCqVgFcAtrWVX0AGTy1MAOWcARpjEINoypAAOqEKE5rR2ji7KUTFmdF4%2B/k5BIWFGmCZptAwEzMQECc6unPmFcSVlBBl%2BgcGh4UKl5ZVJNZ2NzVk57QCURqgOxMgcUjoAzN7IjlgA1DraCAQEEUIgAPR7xMwA7gB0wIQIDgEOIlN0BFYEp2hOewh4UbQAnntWzsFmI89k5mJ1gntFstMO9PnRfv8nIDHqcEBEIutNDIAIJY3HaBa0JYOVaaOY2MpHb5k7B4%2BZQkmYNbk8ydYiYZhOGl0nHMBxEHQANhWVAcRKKEE66BAIEpzGpLPopBWnEF3O0wrl3xGawA7PocfSqNZMFQVgIAOIeACaeJW9pFJAgfIFGqFawArLpvFhxMqAG5sByYTQegAiKxAKw%2BX2%2BMsRyMwzuIVOVPAcIx1mn1dodecDjiZACoyRGfZhxGSDdi89mw3SCQURLn7VKZTEAF6YAD6BBW5fEzIjMirLcdxGd/NQQvdBeDkZWWr1NhWbZAR3UmF2IH9eEwx23pQA1kmeJm9dW8/mg8XS/2TZW5per/aDAYB6OcbXdfXDY3rHgVBjuyBCTLQi4pvKn64j%2BeJSGMrDSB68iuLI8ioNINhvnoq4TFMTLzJw8gENIciZqQR4gHMAAcpy6tR3DUTIGoAJzcDw3C6mxKjSNwKGkeh0jyLs4QkWhYxwLAMCICgqBOBEeDsGQFAQK8ClKSAwBCLQzA7AgqAEHwimPMQuwQAEAmkAE3hlHGUhEaQrxIvQADytCsHZcikFgoLqOwln4Oyph4P6W6WRWmDIPyMxed4jyIWhKh4AERzEN8dhYNIDkEMQeBOFl8F8A8TBsBwPBFYIIgSJZSg1Ko6goNhhisMluywDpSIgFQTiGaFIQ5WKR7kagERFLsUgALQuXMKwTVKpZaHoBjaMws0AOpsKwKzCQUkVFJY1g9NUpDuIMrQhDUKSxHQR3JNE120Gd2RtH0u3BXQDTdPYVTKMYe31F0TTeC0z0XUYgO3X0gNPcMnBjEIeHTFwCFIfxiUYVI4jUYKE2CtwKzAMgyArBAA20ENJO4IQJBrASNQrHY8mKcEtNzHDDNNcRAnkZRnGnNjMhzB6Mg8Mxcy6oKdW8fI%2BW6jIpyCgxMjY9wbNs4rcykKhXkY8JICidzpCSTJEzbPy5CUGpzNg5g%2BBEGD/CMCw/mcOEjvCGIkiJccRwRAVKNSMhWuWRjLn8hE/IrKgZpYzjeME0TJNkxTECM%2BpLOESMXPiWMCAclgIQQAHfGkPl2gsacbMeixnBC4rGucLqwfo0JRj66QYlkWMlGcLRLH99RHq6rXuraLqnGCjxUhzGjOut53hXG0vSBW0pFuqXJ6chFpOl6QZRmsCZZkWYl1k6WlBWOXJzkEG5HkBZgvnAP5iWBf9oXjV5EVRY8l9xQUlkWopVshlGY2Vcr5XsoVR2JUXa8HdlVL2XklDaBUGoDQTUkoBDakXUgI0xrSCmjNOaBB0ALSaitdam17QTTDJaG0O06gWAgO4SGJ1rAwxepEe6RQ2FXSKJwsGf13rFAht9XotR/ofWhsDIYXD%2BhfUSMdBRQNMjnWRuMSYSM4ZTyDtrQSmNsa43xoTYmpNiCDR1BAKm9tWb0zTtbVm2gdRYSWnobOXcKJUTmJXOYfj/EBP8VPEustOCnBYhqOY3BuAyEFLE7gYQPTNznlIPWBtxJG2khAJApsI6GRUqvNoqDbbUwdsVZ2ZV4EPA9tVb2vt/a6NngYsOZs%2BzRxWLHYxCczHJysQ4pSTis4d25rnfObRcEJRCaEWiMhdRzEFB6aucwWJCy4twJJ%2Bi8GtxEsMnOXjG6nG0JwD0USRaKw9ExaJU8Z7JIMR4xeWSkD4CoFQdeMCKlcCqZVT2gCEC7Dqn855VACDfAiBwcIxA/mhFIJCoQQKQVgv1gHPRIdpBhkAjHIx8dTFJwseTHU/ohAdKxSYxO5jLH3J5qEJJkymlbNSW3dJniEraDpbrXZni%2BoxAsNwIAA%3D%3D%3D)

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

[Compiler Explorer](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAM1QDsCBlZAQwBtMQBGAFlJvoCqAZ0wAFAB4gA5AAYppAFZdSrZrVDIApACYAQjt2kR7ZATx1KmWugDCqVgFcAtrRAA2UlfQAZPLUwAcs4ARpjEXADspAAOqEKE5rR2ji7uMXEJdL7%2BQU6h4ZxRxpimiQwEzMQEyc6uHsWldOWVBNmBIWGRRhVVNan1Pa1%2B7XmdhQCURqgOxMgcUjoAzH7IjlgA1DraCAQE0UIgAPSHxMwA7gB0wIQIDsEOIrN0BFYEF2hOhwh4sbQAnocrM4wswXocnMwhC9iIcVmtMF8fnQAUCnCCXhcENFoltNDIAIJ4wnaZa0VYODaaRY2Vh4KFU7BEpZwimYTbU8xQ4iYZhOBlMglchymdYiejDVibCL6AnrOXrKjEPBedbMBxEdaoaLokhUgAi%2BogUPQIBAtPpHPoDNNaFoUIA%2BoQdcR1rb6do3OtCKRRa8JeN1gBaBnrYKoexE%2BVSmX4qNR7kEGa0dYAKkI7INiz160WVJjUc0EQNBMLmZjRLVRB0nqoDjJZjoRoIJrNdIIVJsfnbi0ZHvW5oIAcL5ZJeCo1kwVHWAgA4t4AJqR%2BU0YgQSuoavVzYAVl0fiw4h9ADc2A5MJpt9mQOtvr8/qbUejMBABxdQtdaBBJr7xf5WMPS3GIdpSXON1hPRw2RTfUvQncQ81AqVi2JRZMFYEREONU14gAL0we0CFgg8M3WGQENlZcSHWNd1Q3D0twgs91mvAdgPzMCvSnCBGLZfUYMWNjEI40NuWYABrcjYw40shPlHjUxg/dMHgxZ2LAgwDCUlS1KQpkSS8MdEITJN%2BzbSSZIJKRJlYaRt3kVxZHkVBpBsDS9FFaZZl4klOHkAhpDkIDSDEkBFm3C5twADm4bRuAATgiSKIgiGRIs4OLtxUaRuHsgKnOkeQDhkUh/McyY4FgGBEBQVAnGiPB2DICgIA%2BerGpAYAhFoZh9gQVACD4BroQOCBgjy0hgj8Sp7ykXzSA%2BNF6AAeVoVgZrkUgsAhdR2HG/BuVKI9MAORzPHEEp1XmDauzQ8baWCU5iD%2BOwsGkOaCCVJw3qsvhniYNgOB4X7BBECRxqUTgVDUDQ3MMe6Dlgbq0RAKgnAGo7wg%2BusxKCrUGztaRAyWxYg2NfUtD0AxtGYIMAHU2ElQq0JKfHLGsPpXEhrw2lyfJlFieJ8Y5/mMnxnmOgKIxmcaWhml6examUBp8bloYcglpXBmFyGoRacXRgKSYhE8uYuGs2zctO5ypHESK3EDNxuHWYBkGQaisdoHHqNwQgqKWSH1jsOqGrCTYfIDVzKb0Py8qCkLuAiC47ZkMKZB4GQSQiNxIZsqQctIL6UouNxotSx3Fk4CuS8WUgHI263CpAYrSsC0gKuq6Y9nVchKFakPJcwfAiEl/hGBYXbOGK0fhDESRTrOU5om%2B82pDs2vxutpb1WidVNSnW37cd53Xfd4hsYDCAg7a0P/fGGOysmBAeSwcIvyyvP5C%2B7Q4ouCvtziyu24S7V0KOvK2BUjBNxKrHSYIVtCcGLiSbgbgIgxQ9OlIGudFiW3rhAluP126EKQH3RqPcWq1WvuETq3Ver9UGqwYalAxqnUmt1J6315q1UWgQFaa09qYG2sAXap19oszwEdE6G1lIXReBwm6ucNr3Ues9DA8x3qfWXsDMeAMuC8GnqDOeG0lDaChuoFAsMVB4GCAjN%2BeNEgnSJiTQMZMswU30HoamdMGZykDHqWcC4mYmFZhALw2tPDWH1nzSGAtMhJAVqkaJotEiRLGFLIJZQtbxM5mksRTRBgpMlrreWKRslFLViMKJRsTaAxXmvOu%2BUbZ2wdk7F2bsIAey9hAH2w8w4Vx9FffuvTtAR1hvfQKsDQqLF/osGZsy5mzPfvnQuCC4oekWNwbgMg3BbJijITK9TSAN0gc3WObcqoQCQJ3HeA1mokM6CYwevsR5/XHoDPRzwZ5g3novTRuc6kb2kFvLuhFUD7yaUfVpp9z7UQGY1IZd9oEP1IE/ZgL9KAryWSAbQkULgyAiIsNw25/6LDimFCIcVuD7IBVIRuJykUhUKBccl2hsXaESnFFBHoPBYJwQ0sZBDzlIHwFQKgZDR7/Qnu8kGs87oIAODnOVwqqAED%2BNqKBxA5VYtIBqoQSqVVqpkLU3lhzpB6jHGCw%2BLST7tLPp7AMR4hDrAPs04%2BbSOkIvwXHLFmVc75wOUcoqiLxnv20Mao5nrJgY3iBYbgQA%3D)

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

[Compiler Explorer](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAM1QDsCBlZAQwBtMQBGAFlJvoCqAZ0wAFAB4gA5AAYppAFZdSrZrVDIApACYAQjt2kR7ZATx1KmWugDCqVgFcAtrRABmAJykr6ADJ5aTAA5ZwAjTGIQbTdSAAdUIUJzWjtHF3cveMSzOn9AkKdwyOijTBMc2gYCZmICVOdXT1Ly5KqagjzgsIiomKFq2vr0pv72zoKi3oBKI1QHYmQOKR03AORHLABqHW0EAgJYoRAAemPiZgB3ADpgQgQHUIcRBboCKwIrtCdjhDx42gAnscrM4Isw3scnMx%2BhFjmsNpgfn86ECQU4wW8rghYrEdpoZABBfFE6LwhxbTRuGw1c4AynYYkrMkUqnmfrETDMJz0xmEtC0GEANzYm2YDiImyoDlopmSECm2wA7PpCZs1aLxahRcRads3AARTb9dAgEA05h05WcUjaUgxXgAVk0iv1lJVJNWVGsmComwEAHFfABNYnqyUkCBiog6ABsse2Dt0ASw4lIm2FjkwmgdhpAm1%2B/wBprRGMwkZ1FqmCud7rDYYzDkwmwAVJTDcnMOI3aH1c7XYSVmURD21cbTYkAF6YAD6BE2HfEesNMm7qvVNGIm0jmtj8YbTbz5oB1eVI7r%2B5bbfn3q7blrdbVBgMC9XBLDfcZ0R8eCoZ45BHmWhtVpV8PwHQkAjnKEAnlJV7zVfkYXEWJNyjLUjyXSVpVlOh5VAl1iSkGZWGkB15FcWR5FQaQbCfPQjTmBYmxWTh5AIaQ5CrUgAGt3E4K5FQdbQPBkRVtAdAAODxuDcTgHV4EipG4ciOKo6R5COGRSHYyiZjgWAYEQFBUCcWI8HYMgKAgL4zIskBgCEWhmEOBBUAIPhzLeYgjggUJVNIUIAhqIspFY0gvnRegAHlaFYEK5FILAoXUdh/PwDlZUFTAjko7xxEwZBxSWBLILKfzWDwUJzmIAE7CwaQwoIYg8CcBqiL4V4mDYDgeA6wQRAkfylGtVR1BQOjDAq0IjlgJz0RAKgnHcrLIia6VuK41BYgqHKAFoorcTZduNNstD0AxtGYI6AHU2FYTYNLKAqKksawhlca0fHGbpImtLIkjod7lH%2BipvsKHprWMZ7WgGOp7AaZQoZwypYbByZIdhoGMbGAIunB36ZiERjFi4YjSJU3LqKkcQJJjXaY24TZgGQZAtzW2gNq3XBCBIbZomtTY7FM8yIj52SFVo869DY1SuN47hFSuWmZDcB0ZB4GRokVGMRukZTSFaxUZCuGMJO4GRaZkzhZNNmIKISqmNJALSdM40h9KMuYDnFchKBskXfu8fAiED/hGBYVLOC0sPhDESRcouc5YjasmpDI0h7bUqQovFWJxU2VBfRpumGaZlm2eIdaFQgIXbNFliphl3SZgQTksEieUVD1%2BRWuEq5ZIdDxrYdU3bc4RUM/8x2jGd7TZZmXjxKubh5IkmQPA8B1rbN8eJK7qQ3Aph31Ln3T3cMj2ICQf2LN96yTLryIHKcly3I81gvJ8vzcsCpyara8KJlIoEBinFNKmBkrAFSrldK0Mso5QSp2AqRUAGlUUglKa1VaoYCWI1ZqrVQrtTDl1SOvAY4DXjglJQtpRoaAmioSqM1O5bR2tIfah1joEHQKdCal0bp3TVLtfUAZgyPRaBYCAPgsbeGsGjCGcQEgAxSPDdIf1FGg1xhMeRSMKhtEGCoj6zRoZ0D0R0TRP1EaYwMZYnG%2BQLGcEJsTHqqd06Z1IFTYu9NGbM1ZhAdmnMIDcxDmLAWtcA5i20BLCaTdOIL3cG4fubgknJJSck/e%2BtDb8Q8NoGMbhuDmxjDIBm2gZAOknpTE%2BmlT5u0vkgL2ed3JWRvj0W0mBg4kGUMQiOPUyGvFjoNBOScU771cVPaQOdvZzkLpsTxpcfEVyrluMJFkImN2qURFubceid0UhkqIEkriiTcDGB0g9PCq0VNJMpbjp5VNdhsniXBFaXO0NoCS2hFRSRjGJGMMZ96H3KcfKQMT2q1JAPgKgVA75dO6lwXp/U47lQQEcEayKIVUAIACWIHAtLEGRVEUgeKhDosxdi52Lij5Z31D%2BIutMvFl18f4hUgohAzLpXM8ufjK4czWfcuWUQym7Mpe4yps8%2BWp20MK6e4rSArUSBYbgQA%3D%3D%3D)

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

[Compiler Explorer](https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(fontScale:14,fontUsePx:'0',j:1,lang:c%2B%2B,selection:(endColumn:1,endLineNumber:12,positionColumn:1,positionLineNumber:12,selectionStartColumn:1,selectionStartLineNumber:12,startColumn:1,startLineNumber:12),source:'%23include+%22https://raw.githubusercontent.com/hipony/enumerate/master/include/hipony/enumerate.hpp%22%0A%0A%23include+%3Ctuple%3E%0A%23include+%3Ciostream%3E%0A%0Aint+main()+%7B%0A++++std::tuple+tuple+%3D+%7B0,+1.,+%22string%22%7D%3B%0A++++hipony::enumerate(tuple).each(%5B%5D(auto+index,+auto%26+value)+%7B%0A++++++++std::cout+%3C%3C+index+%3C%3C+!'+!'+%3C%3C+value+%3C%3C+!'%5Cn!'%3B%0A++++%7D)%3B%0A%7D%0A'),l:'5',n:'0',o:'C%2B%2B+source+%231',t:'0')),k:53.14904865377949,l:'4',n:'0',o:'',s:0,t:'0'),(g:!((g:!((h:compiler,i:(compiler:gsnapshot,filters:(b:'0',binary:'1',commentOnly:'0',demangle:'0',directives:'0',execute:'0',intel:'0',libraryCode:'1',trim:'1'),fontScale:14,fontUsePx:'0',j:1,lang:c%2B%2B,libs:!((name:fmt,ver:trunk)),options:'-O3+-std%3Dc%2B%2B2a+-Wall+',selection:(endColumn:1,endLineNumber:1,positionColumn:1,positionLineNumber:1,selectionStartColumn:1,selectionStartLineNumber:1,startColumn:1,startLineNumber:1),source:1),l:'5',n:'0',o:'x86-64+gcc+(trunk)+(Editor+%231,+Compiler+%231)+C%2B%2B',t:'0')),k:47.86035014023761,l:'4',m:70.68408643131683,n:'0',o:'',s:0,t:'0'),(g:!((h:output,i:(compiler:1,editor:1,fontScale:10,fontUsePx:'0',wrap:'1'),l:'5',n:'0',o:'Output+of+x86-64+gcc+(trunk)+(Compiler+%231)',t:'0')),header:(),l:'4',m:29.31591356868317,n:'0',o:'',s:0,t:'0')),k:46.85095134622051,l:'3',n:'0',o:'',t:'0')),l:'2',n:'0',o:'',t:'0')),version:4)

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

[Compiler Explorer](https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(fontScale:14,fontUsePx:'0',j:1,lang:c%2B%2B,selection:(endColumn:1,endLineNumber:18,positionColumn:1,positionLineNumber:18,selectionStartColumn:1,selectionStartLineNumber:18,startColumn:1,startLineNumber:18),source:'%23include+%22https://raw.githubusercontent.com/hipony/enumerate/master/include/hipony/enumerate.hpp%22%0A%0A%23include+%3Cstring%3E%0A%23include+%3Ciostream%3E%0A%0Astruct+aggregate_t+%7B%0A++++int+++++++++i%3B%0A++++double++++++d%3B%0A++++std::string+str%3B%0A%7D%3B%0A%0Aint+main()+%7B%0A++++auto+aggregate+%3D+aggregate_t%7B0,+1.,+%222%22%7D%3B%0A++++hipony::enumerate(aggregate).each(%5B%5D(auto+index,+auto%26+value)+%7B%0A++++++++std::cout+%3C%3C+index+%3C%3C+!'+!'+%3C%3C+value+%3C%3C+!'%5Cn!'%3B%0A++++%7D)%3B%0A%7D%0A'),l:'5',n:'0',o:'C%2B%2B+source+%231',t:'0')),k:53.14904865377949,l:'4',n:'0',o:'',s:0,t:'0'),(g:!((g:!((h:compiler,i:(compiler:gsnapshot,filters:(b:'0',binary:'1',commentOnly:'0',demangle:'0',directives:'0',execute:'0',intel:'0',libraryCode:'1',trim:'1'),fontScale:14,fontUsePx:'0',j:1,lang:c%2B%2B,libs:!((name:boost,ver:'176'),(name:fmt,ver:trunk)),options:'-O3+-std%3Dc%2B%2B2a+-Wall+-DHIPONY_ENUMERATE_AGGREGATES_ENABLED',selection:(endColumn:1,endLineNumber:1,positionColumn:1,positionLineNumber:1,selectionStartColumn:1,selectionStartLineNumber:1,startColumn:1,startLineNumber:1),source:1),l:'5',n:'0',o:'x86-64+gcc+(trunk)+(Editor+%231,+Compiler+%231)+C%2B%2B',t:'0')),k:47.86035014023761,l:'4',m:70.68408643131683,n:'0',o:'',s:0,t:'0'),(g:!((h:output,i:(compiler:1,editor:1,fontScale:10,fontUsePx:'0',wrap:'1'),l:'5',n:'0',o:'Output+of+x86-64+gcc+(trunk)+(Compiler+%231)',t:'0')),header:(),l:'4',m:29.31591356868317,n:'0',o:'',s:0,t:'0')),k:46.85095134622051,l:'3',n:'0',o:'',t:'0')),l:'2',n:'0',o:'',t:'0')),version:4)

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

[Compiler Explorer](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAM1QDsCBlZAQwBtMQBGAFlJvoCqAZ0wAFAB4gA5AAYppAFZdSrZrVDIApACYAQjt2kR7ZATx1KmWugDCqVgFcAtrWVX0AGTy1MAOWcARpjEINoypAAOqEKE5rR2ji7KUTFmdF4%2B/k5BIWFGmCZptAwEzMQECc6unPmFcSVlBBl%2BgcGh4UKl5ZVJNZ2NzVk57QCURqgOxMgcUjoAzN7IjlgA1DraCAQEEUIgAPR7xMwA7gB0wIQIDgEOIlN0BFYEp2hOewh4UbQAnntWzsFmI89k5mJ1gntFstMO9PnRfv8nIDHqcEBEIutNDIAIJY3HaBa0JYOVaaOY2ABumFMJDJ2Dx8yhJMwa3J5k6xEwzCcdIZOOYDiIOgAbCsqA4iUUIJ10CAQFSacQyTZvARedpRQqiMQRmsAOz6HGMqjWTBUFYCADiHgAmniVg6xSQIAKhRqRWsAKy6bxYcSkFYUtgOTCaT0AERWIBWHy%2B3zliORmAgWpII11mgN9sdOaDjhZACoyZHfZhxGTDdic5nwwyCQURNmHTK5TEAF6YAD6BBWpfErMjMgrTadxBWLsFqBFHrzIajgep2ozWZxOdzwcLxd7pvLc0ra8dBgMfeHq8PetrRvr1jwVBHnIIk1oC8Vp9xF7xUjGrGknvkrlkeRUGkGwjz0FYhAmKYWXmTh5AIaQ5HTUgAGsQG4ThThkTg5gADk4ABOHDtE9bgZG4YUVGkbh/0QoDpHkXZwgQwCxjgWAYEQFBUCcCI8HYMgKAgV4%2BIElBVHUbtiAlFC%2BH4x5iF2CAAjo0gAm8Mp4ykODSFeJF6AAeVoVgtLkUgsFBdR2FU/BOVMPAqV2QDSDLalBRmMzVQKVTWDwAIjmIb47CwaQdIIYg8CcUKvz4B4mDYDgeFiwQRAkVSlBqCSNDAwxfICXZYFobkOCoJwCFIKkQnCmTkNQCIiicgBaAy5hWRqZWLLQ9AMbRmDagB1NhWBWRiCkXOJLGsHpqhc6xBlaEIahSWI6Gm5JohW2h5uyNo%2BjG%2By6Aabp7CqZRjHGw6uiabwWh2xajCuta%2Biu7bhk4MZIMmaYuG/X9aOc4CpHEXDhUa4VuBWJY1GAcdqtoFDdQgXBCBINYCRqFY7F4/jgjRuZ3sxnL4Lo5C0O4PVThBmQ5k9bCyIJPVhUy6j5CivUZFOYVcLIkHuHx/GubmUgALMwHGJAZiSdIdiuImbZBXISgRJx%2B7MHwbVlH4RgWGszhwi14QxEkZzjiOCJot%2BqQ/2F1TAYMwUIkFFZUHNYHQfByGsth6T4cRrHRNx2CRmJ1ixgQLksBCCBLZo0gou0AjTnxz0iJprnBc4PUbYBhijAl0gWKQsY0M4YVTk9OYCJkAi9U9YUwi5z1tCoqQ5n%2B0Xc8LmKZZ7pBlYExXhJ4gOQihyS4dkqh5OCJSVOc9SisC6LdJ4/SCCMkybMwSzgGs5zbPGxzVNc5B3OXryf2cvKAqCjAZjCiKou0mKtfi3XeAN1LjbMpRm6ylAcoqD8gVaOpA6oNWkM1Vq7UCDoE6jlXqA0hoOkauGK0tpRp1AsBAdwT1ZqeBukMXakQNpFDwctIor1iHnQOsUR6J1ei1AunQgYhCFpnXoYkGa/RyhUMWh9KC313ot2tiLeiQMQZgwhmPGGEAJ6I2RtqPGGN/YqzxtoXUoFup6BDkXVCIA5hzCToYkxpjTEt1jmzTCBENRzG4GRYUMhwZhE9NnDuUhxaS1YtLTiEAkBy0duVIS/c2jNzVije6r8daJQ/g8Q2aUTZmwtiI9u4j7byx7C7FYbspGe2ht7Gq45VECXUcHAuJMw4RzaKAy%2BljQi4SwnqOYwpPQp0rjTPUBFuCuLEWA3OTFymh30ZnU49j2a4UMTICuREZAkRbm3Nx4jdHd18UgfAVAqCDyiQlLgsSUpGx8ggXYmUjnrKoAQb4EQODhGIEc0IpBblCDORcq5EtLaiNttIcMt5XaSI9jIgpvtAxCGyX86RXs5E%2BwRss0moRXG1NSX0jxecvF6MvtoRFYtBl6MqjECw3AgA%3D)

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

> Note that we compare with `std::ranges` instead of an alternative C-style loop implementation since we're relying on range designs .

[Compiler Explorer](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAM1QDsCBlZAQwBtMQBGAFlJvoCqAZ0wAFAB4gA5AAYppAFZdSrZrVDIApACYAQjt2kR7ZATx1KmWugDCqVgFcAtrRDbSV9ABk8tTADlnACNMYi4ATlIAB1QhQnNaO0cXN2jY%2BLofP0CnELDOSONMUwSGAmZiAiTnV3cikroyioIsgODQiKNyyuqUuu6W3zbcjoKASiNUB2JkDikdAGZfZEcsAGodbQQCAiihEAB6A%2BJmAHcAOmBCBAcghxEZugIrAnO0JwOEPBjaAE8DqzOULMZ4HJzMITPYgHZarTCfb50f6ApzA57nBBRKKbTQyACCuIJ2iWtBWDnWmgWNgAbsUiMRKdhCYtYeTMBsqSd1JghIzmfjmA4iDoAGxrKgOUlmOgQSHoEAgWmmEiUmy%2BAh87RipX00hrNC0SFrOUKuIAL0wAH0CMa8BaxhsAOz6fEsqjWTBUNYCADiXgAmoS1sHxSQIILhVrRRsAKy6XxYcR66lsByYTQxgAiaxAay%2BP1%2BCpRaMwEB1JD15swYwdmmdQZDjZTjnZACpKdmE5hxJSXXjG3XM8ziZhWCIG8GTSAq9a1l3xBzszJexPQ8Q1uGhahRdHm2mc2ty%2Bu6zZjQR5SAucAeQrqXhMKd9iBygBrUtVmtOvuNpuptsducPR7BZvx/YMDAMecV3xAdHSHV0R2sPAqFXYhMAIaZaEPOkVRA5k4KkCZWGkGN5FcWR5FQaQbAgvRjSmGZ2UWTh5AIaQ5BrUgXxABYZHOYkY20cIAA5hO4ISFk4EVhJUaRuDI9jKOkeR9hkUg2IoiY4FgGBEBQVAnCiPB2DICgIHeIyTJAYAhFoZg9gQVACD4YyoX2CAgkU0ggl8CpCykFjSHeVF6AAeVoVh/LkUgsHBdR2C8/A0JKWl9gojxxGKIU5mi9VRy81g8CCE5iF%2BOwsGkQKCGIPAnEqwi%2BCeJg2A4HhGsEEQJC8pROBUNQNFowxCqCfZYDs1EQCoJxnNpMJqslF9ONQKJpUNaQAFpQoWNZ1rlDstD0AxtGYHaAHU2FYHbM38TNsF0X0VNHOkEksaxelcXrPFaHI8mUGI4lW96/vSVbvvafIjCehpaCaHp7BqZR6lW2HBmycHEYGIHeshZowZGfIJiEBjZi4IiSIU9KqKkcRhJFdaRW4NZgGQZAN3m2hFo3XBCBIDZiV6tY7EM4zQj5ySHRow69FYxTOO47hHXOWmZAWGMZB4GRiUdEVeuIqR5NIOrHT46TuBkWnuEkyTpIWUhyOiqmVJANSNI40htL0qZdiFchKAskWIcwfB6WUfhGBYBLODUsPhDESR0tOE4onqsmpFIu2vKp0KhSiIU1lQL0abphmmZZtniAWh0ICFyzReYsYZc0iYEEwZgsDCCBU4NuqhPOSSY3CThVekm3OEdDPKeUoxnfU2WJm4zhhP4ngRRFR1hMdcIFlVmNhNtvWFgph2p9dhqPfPpB/ZM33zIM2uwhsuyHKclzWDcyhPPSny7NK%2BqgoMkKBBwqRUSpgOKwAErpSSs9VKXluxZWeH/PKetorDRKmVDAcwqo1TqgFBqYdmqR14DHTq8dopKHcKodQKBBoqCKqNTupBlqrTSptbau1zz7UGsdM6F1gzrUzL6AMaxHomFWq9Ww8MUifWsHjX6vV/oZESFIj6aQAYJDkaMSGYjSiYxUYjKGyMBiaIhjjOGyRVFmNRsMeRhNiatVTune2Slqa03pozZmrMIDs05hAbm9IxYCxrgHMW2gJaDUbhxeePEFh923vEhJCTZL63kEbTg5xwhagWNwM2IoZAM20DIGME9j5SCdi7WW7tdIQCQF7XOzkzJXw6O4IOPMIYEIjq1YhTxY5dQTknFOySnGZ2kNnb2NoC5rCLu40uXifFV2CSZUJDdZ5N1IC3NuHRGF627m4JeMhHQLBFDGAeCwt4xk3twYpzimFT1UqsqJXE3DcHOCvbQjpxLcFEtobQYlikHyPi4yJZ9qlIHwFQKgN8OktS4N0jqccCoIH2LrJF4KqAEF%2BFEDgaliBItSLioQaKMVYudo4wFtypCZmQoXNxJdPHl0roeIQUzaUeLLt4iuHMVmnzlm4RWZsFiOgHprYS4QZDhEHskg2NzHbTwqWsvW2hyWyp5RMWacQLDcCAA%3D%3D)

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

[Compiler Explorer](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAM1QDsCBlZAQwBtMQBGAFlJvoCqAZ0wAFAB4gA5AAYppAFZdSrZrVDIApACYAQjt2kR7ZATx1KmWugDCqVgFcAtrWVX0AGTy1MAOWcARpjEXACcpAAOqEKE5rR2ji7KUTFmdF4%2B/k5BIZzhxpimcQwEzMQECc6unEaYJmm0JWUEGX6BwWFGpeWVSTVC3S3ebdkdeQCURqgOxMgcUjoAzN7IjlgA1DraCAQEEUIgAPSHxMwA7gB0wIQIDgEOIrN0BFYEF2hOhwh4UbQAnocrM5gswXocnMwBsFDis1pgvj86ACgU4QS8LggIhEtpoZABBXEE7TLWirBwbTSLGysPADSnYQmE5gOIg6ABs6yoDlJDQgA3QIBANLpVO8BHp7PWwoI402AHZ9PilngqNZMFR1gIAOIeACahPWhs5JAgzNZ2jZks0AFZdN4sOJSOsAG5sByYG0AEXWIHW31%2Bf0FKLRmAg0ouQWutAgkyltLe7hj41lmgVBqNGddjkw6wAVJTvfbMOJKYq8RnU57GcS6iJ04b%2BYKYgAvTAAfQI6yL4k2i29MlL9eNxHWppZqHZkqz7p9cYGKbT%2BIzmbdOfzfa7apLizLy6NBgM3cHS/3cqrSpr1hVQ%2BImAIM1oc/FO8ZZ8JUkmrGk1vkrlk8lQaQbAPPR1iEaZZhzJZOHkAhpDkZNSAAaxARZtAuAAOGQ5UWUIMNCTgMM4Yi2V4L8pG4X94IA6R5AOGRSDg/9JjgWAYEQFBUCcCI8HYMgKAgD4eL4kBgCEWhmH2BBUAIPheJeYgDggAJqNIAJvDKQMpBg0gPlRegAHlaFYLS5FILAIXUdhVPwW8imdTADn/Uhi0KFl5jMsU6lUmkAlOYg/jsLBpB0ghiDwJwQo/PhniYNgOB4GLBBECRVKUGpVHUFAQMMXyDlgCTURAKgnFkhyQjC7kkMQ1AIgaJyAFoDMWdYGv5AstD0AxtGYVqAHU2FYVrPV8T1sF0bU6LqQoGksaxemqFzrFaLIcmSaJYjoBb1tSOIVvaXJanqYpBm2/ppqKOgmnKfbRkOgZmjOrpmlutbOEmcCZjmLhP2/KjnMAqRxAwtkGtI9ZgGQZBR0q2hqtHXBCBITZiRqdY7G43jghRxZ3vRnLYOoxCUO4OVMLZGRFmtGQeBkYk5TZDLpEo0hIrlGQLjZDDuBkEHuFx3GucWUg/zMwG6JABimIQ0hWI46Y9hZchKCErHDswfAiEO/hGBYazOAYnXhDESRnLOU4Iii36pB/EXVMBgyWQiFl1lQDVgdB8HIehiBYfhiAMeE7HoPGQnmMmBBMGYLAQhjFRmfkSLtFCC5cetAiqa5oXODlO2AdooxJcYonJhQzhrU57htGtNk5Sw7hy5r7Rc/IxZ/rFgvpeiuWe6QVW%2BOVwSuKDkIxIkqSZLk1gFKUlTnPUiSAqi3SuP0ggjJMmzMEs4BrOc2yZrwBynLM1zkHc5evPIszfP8wKMHmULwsi7Top1uL9d4I2UtNsylG0FQagNA5RUHgAI%2BU461XqtIJqLU2oEHQB1HKPV%2BqDUNA1T02o9TrCmsdCwEB3BPXcK9MYkQNoNCeikTatASH3Qug0a6FR7BVGUAUS6jRBi0NYadZhfRno3WGKtMYH0ILfXevHG27caJAxBmDbgEMoYw2IFVWUEBEZaxxmjQOascbaFlMBLqegw4IVLqhRYqdFiWKsdYqxEiWZs04BcUIFpFjcB5hTUi2gZDWjzh3KQEspZE1luxCASAFbO1kgJfuHQAEayRtrWKesEpf2eMbVKZsLZWwkbbUW0jHaK07G7dYHs5EKJ9n7VR2i%2BK6NDsXcOpBI7Rw6HHci9iQDaAwhcbCiw2TWnTrhKmcpQjcB8bk0g4tC6BPqWXNkFx%2BYyAImyZxMhuChFCK4iRbdfHSOMd3EJSB8BUCoIPd%2BSSuApOSibHyCADgZRuYcqgBA/gRA4AxYgNz2mkHeUIB5TyXmS2tjk%2B20hPQqndrIr2ijfbKLhrKZ0QhikQvkd7JRKjdnE1QhXYiBFOBskGcSVxTMKJSPGQXeidSTESO0CSiZXdELlRiBYbgQA%3D%3D)

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

[Compiler Explorer](https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(fontScale:14,fontUsePx:'0',j:1,lang:c%2B%2B,selection:(endColumn:1,endLineNumber:13,positionColumn:1,positionLineNumber:13,selectionStartColumn:1,selectionStartLineNumber:13,startColumn:1,startLineNumber:13),source:'%23include+%22https://raw.githubusercontent.com/hipony/enumerate/master/include/hipony/enumerate.hpp%22%0A%0A%23include+%3Clist%3E%0A%23include+%3Ctype_traits%3E%0A%0Aauto%26+function(std::list%3Cint%3E+const%26+list)+%7B%0A++++for(auto%26%26+%5Bindex,+value%5D+:+hipony::enumerate(list.begin(),+list.end()))+%7B%0A++++++++static_assert(%0A++++++++++++std::is_same_v%3Cint+const%26,+decltype(value)%3E)%3B%0A++++%7D%0A++++return+list%3B%0A%7D%0A'),l:'5',n:'0',o:'C%2B%2B+source+%231',t:'0')),k:58.582415556978006,l:'4',n:'0',o:'',s:0,t:'0'),(g:!((g:!((h:compiler,i:(compiler:gsnapshot,filters:(b:'0',binary:'1',commentOnly:'0',demangle:'0',directives:'0',execute:'0',intel:'0',libraryCode:'1',trim:'1'),fontScale:14,fontUsePx:'0',j:1,lang:c%2B%2B,libs:!((name:fmt,ver:trunk)),options:'-O3+-std%3Dc%2B%2B2a+-Wall+-DNDEBUG',selection:(endColumn:1,endLineNumber:1,positionColumn:1,positionLineNumber:1,selectionStartColumn:1,selectionStartLineNumber:1,startColumn:1,startLineNumber:1),source:1),l:'5',n:'0',o:'x86-64+gcc+(trunk)+(Editor+%231,+Compiler+%231)+C%2B%2B',t:'0')),k:47.86035014023761,l:'4',m:70.68408643131683,n:'0',o:'',s:0,t:'0'),(g:!((h:output,i:(compiler:1,editor:1,fontScale:10,fontUsePx:'0',wrap:'1'),l:'5',n:'0',o:'Output+of+x86-64+gcc+(trunk)+(Compiler+%231)',t:'0')),header:(),l:'4',m:29.31591356868317,n:'0',o:'',s:0,t:'0')),k:41.417584443022,l:'3',n:'0',o:'',t:'0')),l:'2',n:'0',o:'',t:'0')),version:4)

### C-Arrays

```cpp
#include <hipony/enumerate.hpp>

#include <iostream>

int main() {
    using hipony::enumerate;
    int container[] = {0, 1, 2, 3, 4};
    for (auto&& [index, value] : enumerate(container)) {
        std::cout << index << ' ' << value << '\n';
    }
}
```

[Compiler Explorer](https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(fontScale:14,fontUsePx:'0',j:1,lang:c%2B%2B,selection:(endColumn:1,endLineNumber:11,positionColumn:1,positionLineNumber:11,selectionStartColumn:1,selectionStartLineNumber:11,startColumn:1,startLineNumber:11),source:'%23include+%22https://raw.githubusercontent.com/hipony/enumerate/master/include/hipony/enumerate.hpp%22%0A%0A%23include+%3Ciostream%3E%0A%0Aint+main()+%7B%0A++++int+container%5B%5D+%3D+%7B0,+1,+2,+3,+4%7D%3B%0A++++for(auto%26%26+%5Bindex,+value%5D+:+hipony::enumerate(container))+%7B%0A++++++++std::cout+%3C%3C+index+%3C%3C+!'+!'+%3C%3C+value+%3C%3C+!'%5Cn!'%3B%0A++++%7D%0A%7D%0A'),l:'5',n:'0',o:'C%2B%2B+source+%231',t:'0')),k:58.582415556978006,l:'4',n:'0',o:'',s:0,t:'0'),(g:!((g:!((h:compiler,i:(compiler:gsnapshot,filters:(b:'0',binary:'1',commentOnly:'0',demangle:'0',directives:'0',execute:'0',intel:'0',libraryCode:'1',trim:'1'),fontScale:14,fontUsePx:'0',j:1,lang:c%2B%2B,libs:!((name:fmt,ver:trunk)),options:'-O3+-std%3Dc%2B%2B2a+-Wall+-DNDEBUG',selection:(endColumn:1,endLineNumber:1,positionColumn:1,positionLineNumber:1,selectionStartColumn:1,selectionStartLineNumber:1,startColumn:1,startLineNumber:1),source:1),l:'5',n:'0',o:'x86-64+gcc+(trunk)+(Editor+%231,+Compiler+%231)+C%2B%2B',t:'0')),k:47.86035014023761,l:'4',m:70.68408643131683,n:'0',o:'',s:0,t:'0'),(g:!((h:output,i:(compiler:1,editor:1,fontScale:10,fontUsePx:'0',wrap:'1'),l:'5',n:'0',o:'Output+of+x86-64+gcc+(trunk)+(Compiler+%231)',t:'0')),header:(),l:'4',m:29.31591356868317,n:'0',o:'',s:0,t:'0')),k:41.417584443022,l:'3',n:'0',o:'',t:'0')),l:'2',n:'0',o:'',t:'0')),version:4)

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

[Compiler Explorer](https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(fontScale:14,fontUsePx:'0',j:1,lang:c%2B%2B,selection:(endColumn:1,endLineNumber:6,positionColumn:1,positionLineNumber:6,selectionStartColumn:1,selectionStartLineNumber:6,startColumn:1,startLineNumber:6),source:'%23include+%22https://raw.githubusercontent.com/hipony/enumerate/master/include/hipony/enumerate.hpp%22%0A%0A%23include+%3Ciostream%3E%0A%0Aint+main()+%7B%0A++++for(auto%26%26+%5Bindex,+value%5D+:+hipony::enumerate(%2201234%22))+%7B%0A++++++++std::cout+%3C%3C+index+%3C%3C+!'+!'+%3C%3C+value+%3C%3C+!'%5Cn!'%3B%0A++++%7D%0A%7D%0A'),l:'5',n:'0',o:'C%2B%2B+source+%231',t:'0')),k:58.582415556978006,l:'4',n:'0',o:'',s:0,t:'0'),(g:!((g:!((h:compiler,i:(compiler:gsnapshot,filters:(b:'0',binary:'1',commentOnly:'0',demangle:'0',directives:'0',execute:'0',intel:'0',libraryCode:'1',trim:'1'),fontScale:14,fontUsePx:'0',j:1,lang:c%2B%2B,libs:!((name:fmt,ver:trunk)),options:'-O3+-std%3Dc%2B%2B2a+-Wall+-DNDEBUG',selection:(endColumn:1,endLineNumber:1,positionColumn:1,positionLineNumber:1,selectionStartColumn:1,selectionStartLineNumber:1,startColumn:1,startLineNumber:1),source:1),l:'5',n:'0',o:'x86-64+gcc+(trunk)+(Editor+%231,+Compiler+%231)+C%2B%2B',t:'0')),k:47.86035014023761,l:'4',m:70.68408643131683,n:'0',o:'',s:0,t:'0'),(g:!((h:output,i:(compiler:1,editor:1,fontScale:10,fontUsePx:'0',wrap:'1'),l:'5',n:'0',o:'Output+of+x86-64+gcc+(trunk)+(Compiler+%231)',t:'0')),header:(),l:'4',m:29.31591356868317,n:'0',o:'',s:0,t:'0')),k:41.417584443022,l:'3',n:'0',o:'',t:'0')),l:'2',n:'0',o:'',t:'0')),version:4)

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

[Compiler Explorer](https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(fontScale:14,fontUsePx:'0',j:1,lang:c%2B%2B,selection:(endColumn:1,endLineNumber:13,positionColumn:1,positionLineNumber:13,selectionStartColumn:1,selectionStartLineNumber:13,startColumn:1,startLineNumber:13),source:'%23include+%22https://raw.githubusercontent.com/hipony/enumerate/master/include/hipony/enumerate.hpp%22%0A%0A%23include+%3Ciostream%3E%0A%0Aint+main()+%7B%0A++++using+hipony::enumerate%3B%0A++++int++++++++ptr%5B%5D+%3D+%7B0,+1,+2,+3,+4%7D%3B%0A++++auto+const+size+%3D+3u%3B%0A++++for+(auto%26%26+%5Bindex,+value%5D+:+enumerate(%26ptr%5B0%5D,+size))+%7B%0A++++++++std::cout+%3C%3C+index+%3C%3C+!'+!'+%3C%3C+value+%3C%3C+!'%5Cn!'%3B%0A++++%7D%0A%7D%0A'),l:'5',n:'0',o:'C%2B%2B+source+%231',t:'0')),k:58.582415556978006,l:'4',n:'0',o:'',s:0,t:'0'),(g:!((g:!((h:compiler,i:(compiler:gsnapshot,filters:(b:'0',binary:'1',commentOnly:'0',demangle:'0',directives:'0',execute:'0',intel:'0',libraryCode:'1',trim:'1'),fontScale:14,fontUsePx:'0',j:1,lang:c%2B%2B,libs:!((name:fmt,ver:trunk)),options:'-O3+-std%3Dc%2B%2B2a+-Wall+-DNDEBUG',selection:(endColumn:1,endLineNumber:1,positionColumn:1,positionLineNumber:1,selectionStartColumn:1,selectionStartLineNumber:1,startColumn:1,startLineNumber:1),source:1),l:'5',n:'0',o:'x86-64+gcc+(trunk)+(Editor+%231,+Compiler+%231)+C%2B%2B',t:'0')),k:47.86035014023761,l:'4',m:70.68408643131683,n:'0',o:'',s:0,t:'0'),(g:!((h:output,i:(compiler:1,editor:1,fontScale:10,fontUsePx:'0',wrap:'1'),l:'5',n:'0',o:'Output+of+x86-64+gcc+(trunk)+(Compiler+%231)',t:'0')),header:(),l:'4',m:29.31591356868317,n:'0',o:'',s:0,t:'0')),k:41.417584443022,l:'3',n:'0',o:'',t:'0')),l:'2',n:'0',o:'',t:'0')),version:4)

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
