---
layout: post
title: "Valgrind - wprowadzenie"
permalink: /XXX
search_exclude: true
---

Memcheck - sprawdzanie poprawności dynamicznego zarządzania pamięcią
Ptrcheck - śledzenie wskaźników
Helgrind - sprawdzanie aplikacji wielowątkowych
Callgrind - profilowanie aplikacji




## 1. Valgrind

Valgrind to debugger pod Linuxa. Jego główną funkcją jest wykrywanie problemów z zarządzaniem pamięcią (wykrywa na przykłąd wycieki pamięci). Domyslnie valgrind odpala moduł `memcheck`.

* Valgrind posiada jeszcze moduł do wielowątkowości (`helgrind`), który wykrywa wyścigi (data races)

### 1.1 Działanie

> `g++ main.cpp -g`<br>
> `valgrind ./a.out`

Dodatkowo, Valrind może wskazać w której linii pojawia się wyciek:
> `valgrind --leak-check=full ./a.out`





## Bibliografia

* http://home.agh.edu.pl/~glowacki/docs/matwykl/O-o/_ProgObiekt-C++14-Rozsz.pdf
