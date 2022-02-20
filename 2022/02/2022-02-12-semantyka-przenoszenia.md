---
layout: post
title: Semantyka przenoszenia
date: 2022-02-12 17:00:00
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

* Czas życia obiektu tymczasowego jest przedłużony do czasu życia jego referencji

```cpp
int a = 10;
int& ref_a = a;
// l-value może być wiązane do referencji do l-value

std::string foo();
const std::string& bar = foo();
// r-value moze być wiązane do referencji do l-value ale tylko const !!

std::string& bar = foo();
// ERROR!
// r-value nie może być wiązane do referencji do l-value

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

```cpp
std::string&& bar = foo();
```

* foo() to r-value
* bar to referencja do r-value
* samo bar to l-value bo ma adres i nazwę i można się do niej później odnieść

## Użycie semantyki przenoszenia

```cpp
template <typename T>
class Container {
    // ...
public:
    // void insert(T item);         // inserts a copy of an item (3 copies)
    void insert(const T& item);  // inserts a copy of an item (2 copies)
    void insert(T&& item);       // moves item into the container (1 copy)
};

Container<std::string> c;
std::string str = "text";

c.insert(str);              // lvalue -> insert(const std::string&)
                            // inserts a copy of str, str is used later
c.insert(str + str);        // rvalue -> insert(string&&)
                            // moves temporary into the container
c.insert("text");           // rvalue -> insert(string&&)
                            // moves temporary into the container
c.insert(std::move(str));   // rvalue -> insert(string&&)
                            // moves str into the container, str should not be used
```

## Właśności semantyki przenoszenia

* Przenosi dane z obiektu źródłowego do obiektu docelowego
* Obiekt źródłowy przechodzi w stan "nieokreślony"
  * Obiekt źródłowy nie powinien być więcej używany (Undefined behaviour)
    * Na `std::unique_ptr` można wykonać `reset(new int{20})`
  * Można go bezpiecznie usunąć

## Implementacja

Wykorzystanie semantyki przenoszenia wymaga zaimplementowania:

* **Konstruktora przenoszącego**
  * Jeśli klasa dziedziczy po innej klasie, trzeba też wywołać jej konstruktor przekazując jej cały obiekt
    * Trzeba wykonać `std::move` na wszystkich składowych
* **Przenoszącego operatora przypisania** `Entity& operator=(Entity&& e)`
* W obu metodach należy doprowadzić obiekt do bezpiecznego stanu
  * Jeśli klasa przechowywała wskaźniki to trzeba je zresetować i ustawić na `nullptr`


```cpp
// concept only!
class X : public Base {
  Member m_;

  X(X&& x) : Base(std::move(x)), m_(std::move(x.m_)) {
      x.set_to_resourceless_state();
  }

  X& operator=(X&& x) {
      Base::operator=(std::move(x));
      m_ = std::move(x.m_);
      x.set_to_resourceless_state();
      return *this;
  }

  void set_to_resourceless_state() { /* reset pointers, handlers, etc. */ }
};
```

### Nowoczesne podejście

* Rzadko się pisze samodzielnie tego typu składowe klasy
  * Tylko wtedy kiedy nasza klasa trzyma gołe wskaźniki
* Jeśli nie trzyma, używamy `default` - wtedy kompilator sam je wygeneruje
  * `default` działa tylko z metodami z *Rule of 5*

```cpp
class X : public Base {
    Member m_;

    X(X&& x) = default;
    X& operator=(X&& x) = default;
};
```

## `std::move`

* `std::move` przyjmuje dowolony typ referencji i konwertuje go na referencję do *r-value*
  * Spowoduje to, że jeśli wyślemy do funkcji obiekt przez `std::move`, mamy pewność, że wywoła się to przeciążenie, które przyjmuje *r-value reference*

Inna definicja:
* `std::move()` konwertuje dowolny obiekt w obiekt tymczasowy, który jest później dopasowany przez kompilator do przeciążeń funkcji przyjmujących referencję do r-value

```cpp
template <typename T>
typename std::remove_reference<T>::type&& move(T&& obj) noexcept {
    using ReturnType = typename std::remove_reference<T>::type&&;
    return static_cast<ReturnType>(obj);
}
```

## Forwarding reference (Uniwersalne referencja)

* Nazwana przez Scotta Meyersa jako *Universal Reference*
* **Przyjmuje każdy typ referencji, zarówno `l-value` jak i `r-value`**
  * Dzięki temu możemy napisać jedną uniwersalną funkcję zamiast osobnej dla
    * `const Entity& e`
    * `Entity& e`
    * `Entity&& e`
      * Trzeba użyć `std::forward<T>`
* Oznacza się w funkcji szablonowej, przy typie `T` jako `T&&`

## Reference Collapsing Rules

* Kiedy kompilator pod typ szablonowy `T` podstawi konkretny typ, tych ampersandów `&` robi się dużo
  * Jeśli typ szablonowy przyjmuje `T&`, a przekażemy mu *l-value* (`&`) - kompilator wydedukuje `T&`
  * Jeśli typ szablonowy przyjmuje `T&&`, a przekażemy mu *r-value* (`&&`) - kompilator wydedukuje `T&`
  * Jeśli typ szablonowy przyjmuje `T&&`, a przekażemy mu *l-value* (`&`) - kompilator wydedukuje `T&`
  * Jeśli typ szablonowy przyjmuje `T&&`, a przekażemy mu *r-value* (`&&`) - kompilator wydedukuje `T&&`

T& & -> T& 
T& && -> T&
T&& & -> T&
T&& && -> T&&

Zwijanie referencji odbywa się gdy kompilator generuje instancje szablonów

```cpp
template <typename T>
void f(T & item) {}    // takes item always as an l-value reference

void f(int& & item);   // passing int& as a param, like f(a) -> f(int&)
void f(int&& & item);  // passing int&& as a param, like f(5) -> f(int&)
```

```cpp
template <typename T>
void g(T && item) {}   // takes item as a forwarding reference

void g(int& && item);  // passing int& as a param, like g(a) -> g(int&)
void g(int&& && item); // passing int&& as a param, like g(5) -> g(int&&)
```

## Odśmiecanie interfejsów










https://devcode.pl/cpp11-semantyka-przeniesienia/
1. Co robi konstruktor przenoszacy?
2. Jaka jest zaleta operacji move?
https://www.youtube.com/watch?v=St0MNEU5b0o
https://www.youtube.com/watch?v=IOkgBrXCtfo
cAły kanał Bo Brian


