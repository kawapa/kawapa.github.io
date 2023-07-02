---
layout: post
title: Idiomy w C++
permalink: /idiomy-cpp
---

# Idiomy w C++
{: .no_toc }

---

https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms

W przeciwieństwie do wzorców projektowych dotyczą one konkretnego języka programowania (tego jak należy pisać kod) lub platformy. Przykłady:

- Wskaźniki i szablony w C++
- Słowo kluczowe `finally` w językach gdzie istnieje *garbage collector* (Java)
  - `finally` używa się z blokiem `try-catch`, żeby "posprzątać" ale uniknąć duplikacji kodu
- Dopasownie do wzorców w językach funkcyjnych takich jak Haskel lub Scala

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

## PIMPL

* *Pointer to implementataion*
* Pomaga zminimalizować ilość zewnętrznych zależności w treści implementacji klasy

Zalety:

- Redukcja czasu kompilacji

## copy-and-swap idiom

```cpp
    // user-defined copy assignment (copy-and-swap idiom)
    A& operator=(A other)
    {
        std::cout << "copy assignment of A\n";
        std::swap(n, other.n);
        std::swap(s1, other.s1);
        return *this;
    }
```

## erase-remove