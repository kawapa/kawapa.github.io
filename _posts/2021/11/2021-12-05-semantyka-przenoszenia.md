---
layout: post
title: Semantyka przenoszenia
date: 2021-11-13 17:00:00
permalink: /semantyka-przenoszenia
---

# Semantyka przenoszenia

Semantyka przenoszenia to mechanizm pozwalający:

* uniknąć niepotrzebnego kopiowania (np. dużych danych z jednego obiektu do drugiego)
* przekazywać niekopiowalne elementy

Nowe elementy języka umożliwiające wykorzystanie semantyki przenoszenia:

* Referencje do r-value
* Konstruktor przenoszący: `Entity(Entity&& src)`
* Przenoszący operator przypisania: `Entity& operator=(Entity&& src)`
* `std::move`
* `std::forward`

## Podział na `r-value` i `l-value`

### `l-value`

* Obiekt posiada nazwę
* Możliwe jest pobranie jego adresu
* Obiekt w kolejnej linijce programu dalej istnieje

```cpp
int a;          // a to l-value
int* a;         // a to l-value

int foo(int a); // a to l-value

foo(5);         // obiekt tymczasowy to r-value
```

### `r-value`

* Obiekt bez nazwy
* Nie można pobrać adresu obiektu
* Obiekt tymczasowy (na przykład zwrócony z funkcji, ale nieprzypisany do niczego), który w kolejnej linijce programu przestaje istnieć

## Referencje do r-wartości

```cpp
int a = 10;
int& ref_a = a;

std::string foo();
const std::string& bar = foo();
// r-value moze być wiązane do referencji do l-value ale tylko const !!

std::string& bar = foo();
// ERROR!
// r-value nie może być wiązane do referencji do l-

std::string&& bar = foo();
// r-value wiązane do referencji do r-value

std::string&& bar = "Hello"s;
// ERROR!
// l-value nie może być wiązane do referencji do r-value

std::string temp;
const std::string&& ref_temp = temp;
// OK ale nie ma sensu
// stała l-value wiązana do stałej referencji do r-value
```

## Właśności semantyki przenoszenia

* Przenosi dane z obiektu źródłowego do obiektu docelowego
* Obiekt źródłowy przechodzi w stan "nieokreślony", ale prawidłowy (np. można na nim wykonać `delete`)
  * Obiekt źródłowy nie powinien być więcej używany (Undefined behaviour)

```cpp
class Entity
```
1:06:19

## Implementacja




## Uniwersalne referencje (forwarding references)







`std::move()` - tworzy referencję do r-value (konwertuje wszystko w obiekt tymczasowy?)


https://devcode.pl/cpp11-semantyka-przeniesienia/
3. Co robi konstruktor przenoszacy?
4. Jaka jest zaleta operacji move?
https://www.youtube.com/watch?v=St0MNEU5b0o
https://www.youtube.com/watch?v=IOkgBrXCtfo
cAły kanał Bo Brian



## Bibliografia

* http://home.agh.edu.pl/~glowacki/docs/matwykl/O-o/_ProgObiekt-C++14-Rozsz.pdf
