---
layout: post
title: Zarządzanie zasobami
categories: [post]
date: 2022-01-22
permalink: /zarzadzanie-zasobami
nav_exclude: true
---

## RAII

Idiom, wzorzec w C++ oznaczający *Resource Acquisition Is Initialization*.

* Każdy zasób ma właściciela
* Zasób pozyskany w konstruktorze
* Zasób automatycznie zwalniany w destruktorze
  * Nasz obiekt (wrapper) jest alokowany na stosie
  * Jeśli wystąpi wyjątek to automatycznie wołany jest destruktor (zwijanie stosu)

Wykorzystanie: pliki, gniazda sieciowe, mutexy...

Zalety:
* Krótszy kod (nie trzeba sprawdzać czy usunięte, jeśli nie to usuń itd.)
* Jasna odpowiedzialność
* Można stosować do dowolnych zasobów
* Nie potrzeba sekcji `finally` (z Javy...)
  * Sekcja `finally` jest uruchamiana zawsze, niezależnie od tego czy został rzucony wyjątek czy nie

---

## Zasada 5 i 0

### Zasada 5

**Jeśli implementujesz jedną z poniższych funkcji** (bo na przykład zarządzasz gołym wskaźnikiem i musisz zwolnić pamięć w destruktorze):
* Destruktor
* Konstruktor kopiujący
* Kopiujący operator przypisania
* Konstruktor przenoszący
* Przenoszący operator przypisania

... **to znaczy, że ręcznie zarządzasz zasobami i najprawdopodobniej musisz zaimplementować je wszystkie**. Dzięki temu mamy pewność prawidłowego użycia w każdym kontekście.

* Nie dotyczy to sytuacji w której implementujemy wirtualny destruktor (z pustą implementacją) na potrzeby dziedziczenia
* Przed C++11 i wprowadzeniem semantyki przenoszenia była "Zasada 3".

---

### Zasada 0

**Jeśli używasz wrapper'ów RAII na zasoby, nie musisz implementować żadnej z powyższych funkcji** (nawet jako `= default`)
  * Wszystkie dozwolone funkcje zostaną wydedukowane i niejawnie zaimplementowane przez kompilator (na podstawie tego co przechowujesz w klasie)

---

## Pamięć procesu

* `.text` - kod programu
* `.data` - dane do odczytu i zapisu (zmienne globalne i statyczne)
  * W tym `.rodata` - dane tylko do odczytu (np. stałe)
* `.bss` - *block starting symbol* czy lista zmiennych niezaincjalizowanych lub zaincjalizowanych zerem (w zależności od platformy). Można w ten sposób skompresować dane i zmniejszyć rozmiar pliku wykonywalnego
* sterta - dynamicznie zaalokowana pamieć
* stos - stos wywołań, adresy powrotu, parametry funkcji, zmienne lokalne

Sekcje można podejrzeć poleceniem `objdump`:
* `$ g++ main.cpp`
* `$ objdump a.out`

<p align="center">
  <img width="200" height = auto src = "2022/01/process_memory.jpg">
</p>

---

### Stos

* Bardzo szybki dostęp
  * W rejestrze procesora znajduje się wskaźnik stosu (gdzie aktualnie jesteśmy)
  * Dorzucając coś na stosu - dekrementacja wskaźnika
  * Zdejmując coś ze stosu wskaźnik się inkrementuje
* Limitowane miejsce (zależy od OS)
* Ciągły obszar pamięci (niepofragmentowany)
* Automatycznie zarządzany przez procesor

Inne:
* Stos składa się z ramek stosu, czyli w przypadku C++, to pojedynczy zakres `{ }`
* Zawrtość ramki określa ABI (`Application Binary Interface`) w zależności od architektury na którą kompilujemy, ale najczęściej jest to:
  * argumenty przekazywane do funkcji
  * adres powortu do miejsca w funkcji wywołującej
  * miejsca na zmienne lokalne

---

### Sterta

* Wolniejszy dostęp
* Pamięć pofragmentowana
* Bez limitów pamięci (OS może ustawić limit)
  * Limit RAM chyba że włączony jest swap (plik wymiany)
* Ręczne zarządzanie pamięcią

Alokacja na stercie to:
* Alokacja wskaźnika na stosie
* Alokacja `sizeof(T)` bajtów na stercie
* Wywołanie konstruktora `T`
* Przypisanie adresu do wskaźnika

```cpp
// C++
int* i = new int(5);  // operator new
delete i;

// C
int* i;
i = (int*)malloc(sizeof(int));
*i = 5;
free(i);
```

---

### Operator new

Operator `new` występuje może przyjmować:
1. Liczbę bajtów
2. Liczbę bajtów i `const std::nothrow_t& tag`
  * Jeśli nie uda się zaalokować pamięci, zamiast `std::bad_alloc` otrzymamy `nullptr`
3. Liczbę bajtów i dodatkowy parametr (np. wskaźnik), który definiuje gdzie chcemy zaalokować pamięć
  * Wektor używa takiego alokowania bo ma na samym starcie już "wstępnie" zaalokowaną pamięć (`capacity()`) chce alokować w tym obszarze

---

## Problemy z pamięcią

1. Wyciek pamięci
  * Niezwolnienie zaalokowanej pamięci (np. poprzez nadpisanie wskaźnika)
2. Dostęp do pamięci poza zakresem
3. Wiszący wskaźnik lub referencja (dangling pointer/reference)
  * Dalsze korzystanie ze wskaźnika, który wskazuje na zwolnioną już pamięć
4. Podwójne zwalnianie pamięci (`delete`)
5. Dereferencja `nullptr`
6. Zwalnianie pamięci zaalokowanej na stosie
7. Zwalnianie pamięci niewłaściwym operatorem (`delete`/`delete[]`)

Wycieki pamięci powodują stale zwiększającą się "konsumcję" pamięci, pozostałe to niezdefiniowane zachowanie (UB - *Undefined Behaviour*)

---

Narzędzia do wykrywania problemów z pamięcią
* ASAN (*Address Sanitizer*)
  * Wbudowany w kompilator
  * Trzeba do kompilacji dodać flagi:
    * `-fsanitize=address`
    * `-g`
* Valgrind
  * Oddzielny program
  * `valgrind --leak-check=full ./a.out`
