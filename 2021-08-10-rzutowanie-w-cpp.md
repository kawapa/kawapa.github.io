---
layout: post
title: "Rzutowanie w C++"
date: 2021-08-10 08:00:00
---

# Rzutowanie w C++
{: .no_toc }

Krótki opis rzutowania czyli mechanizmu umożliwiającego programiście zmianę typu danego obiektu na inny.
{: .fs-6 .fw-300 }

<details open markdown="block">
  <summary>
    Spis treści
  </summary>
  {: .text-delta }
1. TOC
{:toc}
</details>

## Rzutowanie w starym stylu

Wady:

* Możliwe jest w ten sposób dowolne rzutowanie
* Trudno wypatrzyć je w kodzie oraz odgadnąć zamysł programisty

```cpp
T obiekt = (T)wyrazenie_lub_obiekt_innego_typu
// rzutowanie w stylu C

T obiekt = T(wyrazenie_lub_obiekt_innego_typu)
// rzutowanie w stylu funkcyjnym
```

## Nowoczesne rzutowanie

W związku z tym, że rzutowanie w "starym stylu" nie sprawdzało czy ma ono sens logiczny czy nie, Stroustrup wprowadził cztery dodatkowe operatory rzutowania: [`static_cast`](#rzutowanie-static_cast), [`dynamic_cast`](#rzutowanie-dynamic_cast), [`const_cast`](#rzutowanie-const_cast) oraz [`reinterpret_cast`](#rzutowanie-reinterpret_cast), które za wyjątkiem rzutowania dynamicznego już w trakcie kompilacji jest walidowane przez kompilator.

## Rzutowanie `static_cast`

* Rzutowanie w trakcie kompilacji
* Konwersja typów podstawowych: `int`, `double`, `char`
    * W przypadku konieczności ucięcia części ułamkowej jakiejś liczby zalecane jest użycie funkcji `round()`
* Konwersja typów zdefiniowanych przez użytkownika wymagana zdefiniowania konstruktora przyjmującego jeden typ i zwracający inny
* Konwersja wskaźników klas podstawowych na ich odpowiedniki klas pochodnych (w dół hierarchii) oraz odwrotnie (w górę hierarchii)

```cpp
const double PI = 3.14159265358979323846264279502;
int int_pi = static_cast<int>(PI);
```

## Rzutowanie `dynamic_cast`

* Konwersja wskaźników (lub referencji) klas podstawowych na ich odpowiedniki klas pochodnych (w dół hierarchii) oraz odwrotnie (w górę hierarchii)
* **Bezpieczne** rzutowanie w trakcie wykonywanie programu gdyż w razie niekompatybilności `dynamic_cast` zwróci:
    * `nullptr` w przypadku rzutowania wskaźników
    * wyjątek `bad_cast`, w przypadku rzutowania referencji

```cpp
struct Base {
    virtual ~Base(){}
};

struct Derived : public Base {};

int main() {
    Derived* d = new Derived;

    Base* b = dynamic_cast<Base*>(d);
    // rzutowanie w górę

    Derived* new_d = dynamic_cast<Derived*>(b);
    // rzutowanie w dół
}
```

## Rzutowanie `const_cast`

* Służy do nadawania lub zdejmowania kwalifikatorów `const` i `volatile`
    * **Typ musi być ten sam!**
* Używając `const_cast` **należy operować na wskaźnikach**

```cpp
int main() {
    int a = 22;
    const int* constA = &a;
    std::cout << "a = " << a << std::endl;

    int* notConstA = const_cast<int*>(constA);
    // zdejmowanie const
    *notConstA = -1;
    std::cout << "a = " << a << std::endl;

    const int* secondConstA = const_cast<int*>(notConstA);
    // nadawanie const
    *secondConstA = 44; // ERROR
}
```

Output: `a = 22, a = -1`

```cpp
int main() {
    double a = -11;
    volatile double *b = &a;

    double *c = const_cast<double*>(b);
    // zdejmowanie volatile

    b = const_cast<volatile double*>(c);
    // nadawanie volatile
}
```

## Rzutowanie `reinterpret_cast`

Konwersje między niespokrewnionymi typami, na przykład:
* Ze wskaźnika jednego typu na inny

```cpp
float *f = new float;
// zmienna typu float zajmuje 4 bajty pamięci

*f = 33.2;
int *i = reinterpret_cast<int*>(f);
// zmienna int zajmuje również 4 bajty pamięci

std::cout << "float: " << *f << " ---> int: " << *i << endl;
// ten sam układ bitów, ale inna interpretacja
```

Output: `float: 33.2 ---> int: 1107610829`

* Z liczby całkowitej na wskaźnik
    * Jeśli wskaźnik wskazuje na komórki pamięci jednego typu (np. `float`), a chcemy zapisać wskazywany adres do wskaźnika innego typu to należy użyć `reinterpret_cast`
    
```cpp
int address = 0x0f6a2f1;
int* wsk = reinterpret_cast<int*>(addres);
// ustawienie wskaźnika na adres
```

## Bibliografia

* [Bjarne Stroustrup - Język C++. Kompendium wiedzy](https://helion.pl/ksiazki/jezyk-c-kompendium-wiedzy-wydanie-iv-bjarne-stroustrup,jcppkw.htm#format/d)
* [Mirosław Głowacki - Wykład](http://home.agh.edu.pl/~glowacki/docs/matwykl/O-o/_ProgObiekt_Rzutowania.pdf)
