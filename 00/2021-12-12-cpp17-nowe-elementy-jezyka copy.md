---
layout: post
title: C++17 - nowe elementy języka
date: 2021-12-12 17:00:00
permalink: /cpp17-nowe-elementy-jezyka
search_exclude: true
---

fold-expressions
class template argument deduction
non-type template parameters declared with auto
compile-time if constexpr
inline variables
structured bindings
initializers for if and switch
u8 character literal
simplified nested namespaces
using-declaration declaring multiple names
made noexcept part of type system
new order of evaluation rules
guaranteed copy elision
temporary materialization
lambda capture of *this
constexpr lambda
attribute namespaces don't have to repeat
new attributes:
[[fallthrough]]
[[maybe_unused]]
[[nodiscard]]
__has_include


## Wiązania strukturalne

Od C++17 możliwe jest przypisanie zmiennym pochodzących z:
* tablicy o stałej wielkości
* `std::pair`
* `std::tuple`
* ze struktur, ale takich gdzie:
    * żaden element nie jest statyczny
    * wszystkie pola muszą być zdefiniowane w tej samej klasie bazowej

```cpp
auto [zmienna_1, zmienna_2, zmienna3] = egzemplarz tablicy, pary, tupli, struktury;
```

* Liczba zmiennych musi odpowiadać liczbie zmiennych znajdujących się po prawej stronie
* Przed C++17 możliwe to było przy zastosowaniu `std::tie`, ale wszystkie zmienne muszą być wcześniej zadeklarowane
    * Pewnym ułatwieniem w `std::tie` jest zastosowanie `std::ignore` czyli niedeklarowanie zmiennej której nie będziemy potrzebować

```cpp
auto pair = std::make_pair<int, std::string>(1, "Matrix");

std::string name;
std::tie(std::ignore, name) = pair;

std::cout << name;
```

## Mozliwosc inicjalizacji zmiennych w konstrukcjach if oraz switch

W C++17 wprowadzono dodatkową składnię dla instrukcji `if` oraz `switch` umożliwiającą zgrupowanie instrukcji inicjującej oraz sprawdzającej warunek. Ogarniczamy w ten sposób zasięg zmiennych

```cpp
if (init; condition)
{}

switch(init; condition)
{}
```

**Przykłady**

```cpp
if (Status status = g.status(); status == Status::bad) {
    std::cerr << "Gadget is broken(status=" << static_cast<int>(status) << std::endl;
}

if (std::lock_guard<std::mutex> lk{mtx}; !q.empty()) {
    std::cout << q.front() << std::endl;
}

switch (Gadget g{2}; auto s = g.status()) {
case Status::on:
    cout << "Gadget is on" << endl;
    break;
case Status::off:
    cout << "Gadget is off" << endl;
    break;
case Status::bad:
    cout << "Gadget is broken" << endl;
    break;
}
```

## Statyczne pola wbudowane

Od C++17, statyczne pole w klasie z nagłówkiem `inline` nie wymaga definicji poza klasą.

```cpp
class Entity {
    static int index = 1;
    inline static int newIndex = 1;
};

int Entity::index = 1;        // DOBRZE     
int Entity::newIndex = 1;     // ŹLE
```

## Automatyczna dedukcja typu szablonu klasy

Od C++17 kompilator sam wydedukuje typ szablonu klasy w oparciu o typ danych który zostanie podany do konstruktora.

```cpp
template <class T = float>
class Entity {
public:
    T name_;
    Entity() : name_{} {}
    Entity(T name) : name_(name) { }
};

int main() {
    Entity entity1{1};      // Entity<int>
    Entity entity2{2.55};   // Entity<float>
    Entity entity3;         // Entity<float>
}
```

## `constexpr` lambdy

Od C++17 możliwe są `constexpr` lambdy.

```cpp
auto identity = [](int n) constexpr { return n; };

static_assert(identity(123) == 123);
```

```cpp
constexpr auto sum = [](int a, int b){ return a + b; };

static_assert(sum(3, 7) == 10, "3 + 7 == 10");
```

## Atrybuty fallthrough

`[[fallthrough]]` - wskazuje na zamierzony brak instrukcji break po instrukcji case i kompilator nie powinien wysyłać ostrzeżeń.

```cpp
switch (n) {
  case 1: [[fallthrough]]
    // ...
  case 2:
    // ...
    break;
}
```

---

## std::variant

Dostępna od C++17 alternatywa dla Unii. Cechy:
* Automatycznie wołany destruktor (po wyjściu poza zakres)
* W przypadku próby pobrania niewłaściwego typu rzucany jest wyjątek
* Tworzenie `std::variant`

```cpp
std::variant<int, std::string> v1;

v1 = 5;

```

* Dostęp do wartości albo przez index albo przez typ

```cpp
std::variant<int, std::string> v2;
v2 = 10;

auto a = std::get<0>(v);
auto b = std::get<int>(v);
```

* Umożliwia przechowywanie wielu wartości tego samego typu:
    * Inicjalizowanie wartością wymaga użycia `std::in_place_index`
    * Dostęp do wartości tylko przez index

```cpp
std::variant<int, int> v3;
std::variant<int, int> v1(std::in_place_index<1>, 12);

auto c = get<1>(v3);
auto d = get<int>(v3);  // ŹLE
```

## Bibliografia

- https://github.com/AnthonyCalandra/modern-cpp-features
- http://home.agh.edu.pl/~glowacki/docs/matwykl/O-o/_ProgObiekt-C++17-Rozsz.pdf
