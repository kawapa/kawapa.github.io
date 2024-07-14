---
layout: post
title: Notatki - październik 2023
date: 2023-10-31
permalink: /pazdziernik2023
---

# vector `push_back` czy `emplace_back`

- `push_back` wstawia istniejący obiekt (nawet tymczasowy) do kontenera
- `emplace_back` tworzy obiekt do razu w kontenerze

Uwaga! Przekazanie do metod `push_back` oraz `emplace_back` obiektu tymczasowego spowoduje wywołanie konstruktora, a następnie konstruktora przenoszącego. Kompilator może sobie poradzić z tą sytuacją i dokonać optymalizacji, ale w sytuacji kiedy nasz vector przechowuje obiekty `std::string` (to nie tylko wskaźnik oraz długość tylko dodatkowy bufor przeznaczony do SSO) to i tak dojdzie do kopiowania.

```cpp
collection.push_back(MyClass(1));     // ŹLE
collection.emplace_back(MyClass(1));  // ŹLE

collection.emplace_back(1);           // OK
```

## Bibliografia

* [Andreas Fertig - push_back vs emplace_back: When to use what](https://andreasfertig.blog/2023/04/push_back-vs-emplace_back-when-to-use-what/)
* [Stack Overflow - SSO](https://stackoverflow.com/questions/10315041/meaning-of-acronym-sso-in-the-context-of-stdstring)