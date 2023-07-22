---
layout: post
title: Argument-Dependent Lookup (ADL)
categories: [post]
date: 2023-07-22
permalink: /adl
---

# Argument-Dependent Lookup (ADL)

---

## Co to jest i do czego służy?

* Cecha C++, która pozwala na automatyczne rozszerzenie przestrzeni nazw, w których kompilator szuka definicji wywołanych funkcji lub operatorów, gdy znajdują się ona poza bieżącą przestrzenią nazw
  * Kompilator dodatkowo przeszukuje namespace'y w których:
    * Zdefiniowane są typy argumentów przekazanych do funkcji
    * Zdefiniowany jest typ obiektu na którym został wywołany jego operator
* Standardowo kompilator poszukuje tych definicji w bieżącej przestrzeni nazw oraz w przestrzeniach rodziców
* Nazywany również *Koenig Lookup* (ale Andrew Koening go nie stworzył)
  * Andrew Koening - programista Bell Labs, który pracował z Bjarne Stroustrup'em

## Zalety

* ADL upraszcza pisanie kodu, nie trzeba wielokrotnie powtarzać namespace'a lub nadużywać słowa kluczowego *using*

```cpp
// Przykład 1:

std::cout << "Test\n";  // Nie ma zdefiniowanego operatora << w bieżącej przestrzeni nazw,
                        // ale ADL sprawdza także przestrzeń stl bo lewy argument stamtąd pochodzi
                        // I rzeczywiście, w przestrzeni std znajduje się:
                        // std::ostream& std::operator<<(std::ostream&, const char*)

operator<<(std::cout, "Test\n"); // Zapis alternatywny

// Przykład 2:

namespace A {
    struct Entity {};

    void foo(Entity e) { }
}

int main() {
    A::Entity e;
    foo(e);    // ADL - nie trzeba pisać A::foo
}
```

## Wady

* W niektórych przypadkach konieczne jest dokładne wskazanie funkcji o którą nam chodzi

```cpp
namespace A {
    struct Entity {};

    void swap(Entity& lhs, Entity& rhs) {
        std::cout << "A::Entity::swap function\n";
    }

    void foo(Entity& lhs, Entity& rhs) {
        using std::swap;
        swap(lhs, rhs);  // wywoła A::swap zamiast std::swap
    }
}

int main() {
    A::Entity e1;
    A::Entity e2;

    foo(e1, e2);
}
```

### Inne ciekawe

* Dodawania deklaracji lub definicji funkcji do przestrzeni nazw *std* to niezdefiniowane zachowanie (poza pewnymi wyjątkami - [klik](https://en.cppreference.com/w/cpp/language/extending_std))

---

## Bibliografia

* [CppReference - Argument-dependent lookup](https://en.cppreference.com/w/cpp/language/adl)
* [C++ Weekly - Ep 160 - Argument Dependent Lookup (ADL)](https://www.youtube.com/watch?v=agS-h_eaLj8)
* [StackOverflow](https://stackoverflow.com/questions/8111677/what-is-argument-dependent-lookup-aka-adl-or-koenig-lookup)
