---
layout: post
title: "C++14 - nowe elementy biblioteki standardowej"
date: 2021-11-28 17:00:00
permalink: /cpp14-nowe-elementy-biblioteki-standardowej
search_exclude: true
---

std::shared_timed_mutex and std::shared_lock
std::integer_sequence
std::exchange
std::quoted
and many small improvements to existing library facilities, such as
two-range overloads for some algorithms
type alias versions of type traits
user-defined literals for basic_string, duration and complex
etc.


#### Literaly dla `std::complex`, `std::chrono` i `std::string`

```cpp
#include <chrono>
#include <complex>
#include <string>

using namespace std::string_literals;
using namespace std::complex_literals;
using namespace std::chrono_literals;

int main() {    
    auto st = "Book"s;  // std::string

    auto i = 1i;        // complex<double>

    auto h = 1h;        // chrono::hours
    auto m = 1min;      // chrono::minutes
    auto s = 1s;        // chrono::seconds

    std::chrono::duration_cast<std::chrono::minutes>(h).count(); // == 60
}
```

## std::make_unique

```cpp
auto uniqueEntity = std::make_unique<Entity>(); // działa od C++14

std::unique_ptr<Entity> entity(new Entity());
```

* Rekomendowane tworzenie wskaźnika poprzez `std::make_unique`
    * Brak użycia używamy operatora `new`
    * Brak powtórzeń typu w kodzie (`std::make_shared<T>{new T}`)
    * Bezpieczene w przypadku wystąpienia wyjątku

```cpp
foo(std::unique_ptr<T>{new T}, function_that_throws(), std::unique_ptr<T>{new T});

// kompilator nie gwarantuje kolejności wykonania, a możliwe że 
// nastąpi przeplot operacji. Zawołanie operatora new to:
// * Alokacja pamięci na stercie
// * Wywołanie konstruktora
// * Przypisanie adresu pamięci do wskaźnika
```

* Rekomendowane przekazywane do funkcji `std::unique_ptr` jako `const&`

```cpp
void foo(const std::unique_ptr<Entity>& p);
```

## Bibliografia

* http://home.agh.edu.pl/~glowacki/docs/matwykl/O-o/_ProgObiekt-C++14-Rozsz.pdf
