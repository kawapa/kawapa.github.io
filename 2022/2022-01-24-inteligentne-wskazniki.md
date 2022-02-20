---
layout: post
title: Inteligentne wskaźniki
date: 2022-01-24 17:00:00
permalink: /inteligentne-wskazniki
---

# Inteligentne wskaźniki
{: .no_toc }

<details close markdown="block">
  <summary>
    Spis treści
  </summary>
  {: .text-delta }
1. TOC
{:toc}
</details>

---

## Wstęp

* Obiekty klas wprowadzonych w standardzie C++11 udoskonalające działanie wskaźników (wymaga `#include <memory>`)
* Ułatwiają zarządzanie pamięcią - programista nie musi pamiętać o zwolnieniu pamięci (`delete`) - dzieje się to automatycznie. Nowsze wersje języka C++ zwalniają nawet z pisania `new`
    * W bardziej skomplikowanym kodzie, z kilkoma instrukcjami warunkowymi, w każdej możliwej ścieżce musimy mieć kod, który poprawnie zwolni pamięć

Używając tradycyjnych RAW pointerów można przez przypadek:
* Usunąć wskaźnik nie zwalniając pamięci na którą on wskazuje (jeśli żaden inny wskaźnik nie wskazuje na ten obszar to nie mamy już dostępu do tych danych)
* Zwolnić ten sam obszar pamięci kilkakrotnie
* Zdereferencjonować wskaźniki null

To wszystko wysypie program.

*Smart pointer* to obiekt, który zachowuje się jak wskaźnik:
* Operator `*` wysłuskuje dane
* Operator `->` zwraca referencję na dane
* Można przypisać do niego `nullptr`
* Można sprawdzić czy zawiera nie-nullową wartość (`if (ptr) { }`)

## std::unique_ptr

* Może istnieć tylko 1 obiekt wskazujący na dane miejsce w pamięci (posiada on prawo właności do przechowywanej wartości)
* Możliwe przenoszenie (`std::move`)
* Niemożliwe kopiowanie
    * Dozwolone jest tylko przesyłanie jego referencji do funkcji (jako argument)
* Brak narzutu pamięciowego i czasu wykonania
* Wskaźnik, który w momencie wyjścia poza zakres (lub po wywołaniu metody `reset`), sam się usuwa i zwalnia pamięć
* Korzysta się z nich tak samo jak z RAW pointerów. Różni się jedynie ich tworzenie
* Możliwy własny deleter
    * `std::unique_ptr` nie musi zarządzać pamięcią, może czymś innym (np. zamykać plik)
    * Własny deleter zwiększa rozmiar `std::unique_ptr` bo nie ma on bloku kontrolnego
* W C++11 co prawda nie ma `std::make_unique` ale możemy sobie zami stworzy szablon wariadyczny, który będzie przyjmowal w konstruktorze arguemnty i zwróci utworzony `std::unique_ptr`

```cpp
// TWORZENIE
auto entity = std::make_unique<Entity>(); // działa od C++14
std::unique_ptr<Entity> entity(new Entity()); // druga opcja, mniej polecana

// PRZENOSZENIE
std::unique_ptr<Entity> p1();
std::unique_ptr<Entity> p2 = std::move(p1); // p1 = nullptr

// WYSYŁANIE DO FUNKCJI
void process(std::unique_ptr<Entity> obj);

auto p = std::make_unique<Entity>();
process(p);                 // ŹLE!
proecss(std::move(p));      // DOBRZE

// WSTAWIANIE DO KOLEKCJI
auto p = std::make_unique<Entity>();
std::vector<std::unique_ptr<Entity>> v;

v.push_back(p);             // ŹLE!
v.push_back(std::move(p));  // DOBRZE

ptr.reset(new X);   // zwolnienie obecnej pamieci i przypisanie do nowego elementu
ptr.reset();    // zwolnienie pamięci i przypisanie nullptr

X* raw = ptr.release(); // wyciąganie wskaźnika z rezygnacja z wlasnosci
X* raw = ptr.get(); // wyciągnięcie gołego wskaźnika z **utrzymaniem prawa własności**
```

## std::shared_ptr

```cpp
auto sharedEntity = std::make_shared<Entity>();
std::shared_ptr<Entity> entity(new Entity());
```

* Możliwe przenoszenie
* Możliwe kopiowanie
* Rekomendowane tworzenie wskaźnika poprzez `std::make_shared`
    * Brak użycia używamy operatora `new`
    * Brak powtórzeń typu w kodzie (`std::shared_ptr<T>{new T}`)
    * Lepsze ułożenie w pamięci: blog kontrolny i dane użytkownika są w 1 bloku w pamięci (**cache-friendly** oraz zajmuje mniej pamięci)
        * Alokując za pomocą `new` mamy 2 osobne bloki
    * Bezpieczene w przypadku wystąpienia wyjątku

```cpp
foo(std::shared_ptr<T>{new T}, function_that_throws(), std::shared_ptr<T>{new T});

// kompilator nie gwarantuje kolejności wykonania, a możliwe że 
// nastąpi przeplot operacji. Zawołanie operatora new to:
// * Alokacja pamięci na stercie
// * Wywołanie konstruktora
// * Przypisanie adresu pamięci do wskaźnika
```

* Wprowadza narzut pamięci i czasu wykonania (inkrementacja licznika musi być bezpieczna wielowątkowo, wiele wątków nie może jednocześnie pisać do tego samego miejsca w pamięci)
* Trzeba uważać na cykle: sytuacja jeśli mamy `std::shared::ptr` wskazujące na 2 struktury przechowujące `std::shared_ptr`, które wskazują na siebie na wzajem). Pamięć nigdy nie będzie zwolniona (wyciek pamięci).

```cpp
struct S {
    S() { std::cout << "Constructor\n"; }
    ~S() { std::cout << "Destructor\n"; }

    std::shared_ptr<S> p_;
};

int main() {
    std::shared_ptr<S> p1(new S);
    std::shared_ptr<S> p2(new S);

    p1->p_ = p2;
    p2->p_ = p1;
}
```

> `Constructor`<br>
> `Constructor`

* Blok na dane + blok kontrolny
* Bloku kontrolny
    * Licznik `std::shared_ptr` (`std::atomic<int>`)
    * Licznik `std::weak_ptr` (`std::atomic<int>`)
    * Deleter (domyślnie `detele`, może być własna funkcja, funktor lub lambda)
        * Chcąc skorzystać z własnego deletera nie można skorzystać z konstrukcji `std::make_shared`
        * W celu zapewnienia, że dane użytkownika i blok kontrolny trafią do jednego bloku w pamięci należy zastosować `allocate_shared` ale wymaga to zdefiniowania własnego allokatora.
* Destruktor
    * `shared-refcount`--
    * Usuwa obiekt gdy `shared-refcount == 0`
    * Usuwa blok kontrolny gdy `shared-refcount == 0` oraz `weak-refcount == 0`

* Po zniszczeniu ostatniej, dopiero wtedy następuje zwolnienie pamięci.
* Rekomendowane przekazywane do funkcji `std::shared_ptr` jako `const&`

```cpp
void foo(const std::shared_ptr<Entity>& p);
```

## std::weak_ptr

* W celu stworzenia `std::weak_ptr` trzeba mu przekazać do konstruktora `std::shared_ptr`-a
* Stosuje się go wraz z `std::shared_ptr`, ale nie inkrementuje to licznika referencji

```cpp
std::shared_ptr<S> sp(new S);
std::weak_ptr<S> wp(sp);

std::cout << sp.use_count() << std::endl;   // Wyświetla 1
```

* Żeby dostać się do wartości na którą wskazuje `std::weak_ptr` należy zablokować zasób `lock()`. Jeśli to się uda `lock()` zwróci `std::shared_ptr`. Jeśli zasób na który wskazywał `std::weak_ptr` został już zwolniony, `lock()` zwróci nullptr.

```cpp
std::shared_ptr<S> p1(new S);
std::weak_ptr<S> p2(p1);

auto p = p2.lock();
if (p) {
    std::cout << p->i;
}
```
* Destruktor
    * `weak-refcount`--
    * Usuwa blok kontrolny gdy `shared-refcount == 0` oraz `weak-refcount == 0`
* Rozwiązanie problemu cyklów

```cpp
struct S {
    S() { std::cout << "Constructor\n"; }
    ~S() { std::cout << "Destructor\n"; }

    std::weak_ptr<S> p_;        // zamiast std::shared_ptr
};

int main() {
    std::shared_ptr<S> p1(new S);
    std::shared_ptr<S> p2(new S);

    p1->p_ = p2;
    p2->p_ = p1;
}
```

> `Constructor`<br>
> `Constructor`<br>
> `Desctuctor`<br>
> `Desctuctor`
