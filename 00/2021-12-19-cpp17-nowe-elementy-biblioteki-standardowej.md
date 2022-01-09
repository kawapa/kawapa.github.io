---
layout: post
title: C++17 - nowe elementy biblioteki standardowej
date: 2021-12-19 17:00:00
permalink: /cpp17-nowe-elementy-biblioteki-standardowej
search_exclude: true
---

https://en.cppreference.com/w/cpp/17







## std::string_view

string_view
https://www.youtube.com/watch?v=vek110N918Y
https://infotraining.bitbucket.io/cpp-17/string-view.html
https://www.learncpp.com/cpp-tutorial/an-introduction-to-stdstring_view/

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

* http://home.agh.edu.pl/~glowacki/docs/matwykl/O-o/_ProgObiekt-C++17-Rozsz.pdf