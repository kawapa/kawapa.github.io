---
layout: post
title: "C++14 - nowe elementy języka"
date: 2021-11-28 17:00:00
permalink: /cpp14-nowe-elementy-jezyka
search_exclude: true
---

variable templates
generic lambdas
lambda init-capture
new/delete elision
relaxed restrictions on constexpr functions
binary literals
digit separators
return type deduction for functions
aggregate classes with default non-static member initializers.

## Literaly binarne

Od C++14 można stosować zapis binarny.

```cpp
int x = 0B001101;
```

## Lambdy generyczne

Od C++14 parametr zadeklarowany w lambdzie jako `auto` zachowuje się jako parametr szablonowy (polimorficzne lambdy).

```cpp
auto identity = [](auto x) { return x; };

int three = identity(3);                // == 3
std::string foo = identity("foo");      // == "foo"
```

## Wyrazenia przechwytujace lambda

C++14 umożliwia przechwycenie przez przeniesienie (`std::move`) jak i deklarowanie dowolnych obiektów wewnątrz funkcji lambda, bez konieczności istnienia relatywnej zmiennej w zasięgu zewnętrznym.

* W C++11 funkcja lambda mogła przechwycić zmienne zewnętrzne tylko przez wartość lub przez referencję!

```cpp
std::unique_ptr<int> ptr(new int(10));

// Lambda sama dedukuje typ z wyrażenia inicjalizującego
auto lambda = [value = std::move(ptr)]{
    return *value; };
```

## Automatyczna dedukcja typu zwracanego z funkcji

Od C++14 można stosować `auto` jako typ zwracany z funkcji. Warunki:

* Wszystkie instrukcje `return` zwracają ten sam typ (o ile jest więcej niż jedna)
* W przypadku rekurencji, pierwsze napotkane `return` musi zwracać wartość nierekurencyjną
* Definicja funkcji musi znaleźć się przed pierwszym jej użyciem (deklaracja nie wystarczy)

```cpp
auto multiply(int x, int y) {
    return x * y;
}
```

```cpp
int fun1(int i);
auto fun2(int i);

int main() {
    std::cout << fun1(1) << std::endl; // Ok
    std::cout << fun2(1) << std::endl; // Błąd

    // Należy przesunąć definicji funkcji fun2() przed main()
    
    return 0;
}

int fun1(int i) { return i; }
auto fun2(int i) { return i; }
```

## decltype(auto)

Od C++14 deklaracja `decltype(auto)` jako typu zwracanego z funkcji powoduje zastosowanie do dedukcji typu mechanizmu `decltype` (zachowującego referencje i modyfikatory const oraz volatile) zamiast mechanizmu auto.

```cpp
const int x = 0;
auto x1 = x;           // int
decltype(auto) x2 = x; // const int

int y = 0;
int& y1 = y;
auto y2 = y1;           // int
decltype(auto) y3 = y1; // int&

int&& z = 0;
auto z1 = std::move(z);             // int
decltype(auto) z2 = std::move(z);   // int&&
```

## Rozluznienie ograniczen dla funkcji `constexpr`

C++11 wprowadził pojęcie funkcji deklarowanej jako `constexpr`, czyli  takiej, która może być wykonywana podczas kompilacji. Wartości zwracane takich funkcji mogą być użyte przez operacje wymagające stałych wyrażeń, takich jak argument typu całkowitego szablonu. Jednak funkcje `constexpr` w C++11 mogą zawierać tylko jedno wyrażenie, które jest zwracane oraz niewielką liczbę innych deklaracji.

```cpp
constexpr uint64_t fib(int x)
{
  if (x <= 2)
    return 1;
  return fib(x - 1) + fib(x - 2);
}

/*...*/
  constexpr uint64_t a = fib(35);
  std::cout << a;
```

**Od C++14** funkcje `constexpr` mogą zawierać:
* Wszelkie deklaracje z wyjątkiem zmiennych statycznych lub `thread_local`
* Instrukcje warunkowe `if` i rozgałęzienia `switch`
* Dowolne instrukcje pętli, w tym `for` dla zakresów
* Wyrażenia zmieniające wartość obiektu, jeśli zakres istnienia tego  biektu rozpoczął się w funkcji wyrażenia stałego
* Wywołania dowolnych metod niebędących `constexpr` za wyjątkiem metod `static`

W C++14 niestatyczne metody zadelkarowane jako `constexpr` są również domyślnie `const`. W C++14 nie są domyślnie `const`.

## Szablony zmiennych

C++14 wprowadza szablony dla zmiennych. Przykładowe użycie:

```cpp
template<class T>
constexpr T pi = T(3.1415926535897932385);
template<class T>
constexpr T e  = T(2.7182818284590452353);
```

Poprzednie wersje języka umożliwiały tworzenie szablonów tylko z funkcji, klas oraz aliasów typów.

## Atrybut `[[deprecated]]`

C++14 pozwala na oznaczenie konstrukcji przestarzałej. Konstrukcja taka jest nadal legalna, ale kompilator wyświetli komunikat ostrzegawczy. Opcjonalny literał łańcuchowy z komentarzem.

```cpp
[[deprecated]]
void foo();

[[deprecated("Use different function instead")]]
void foo();
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

## Literaly dla `std::complex`, `std::chrono` i `std::string`

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

## Bibliografia

- https://github.com/AnthonyCalandra/modern-cpp-features
- http://home.agh.edu.pl/~glowacki/docs/matwykl/O-o/_ProgObiekt-C++14-Rozsz.pdf