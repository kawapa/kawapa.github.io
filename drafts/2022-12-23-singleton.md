---
layout: post
title: Wzorce projektowe - Singleton
permalink: /singleton
---

# Wzorce projektowe - Singleton
{: .no_toc }

<details closed markdown="block">
  <summary>
    Spis treści
  </summary>
  {: .text-delta }
1. TOC
{:toc}
</details>

---

## Kiedy używać

* Kiedy w programie potrzebna jest tylko jedna instancja danej klasy (wszystkie klasy korzystają z tego jednego obiektu)
  * Przykłady:
    * Dostęp do bazy danych
    * Fabryka obiektów
    * Jakakolwiek inna klasa, której stworzenie obiektu bądź równoległe używanie więcej niż jednego jest kosztowne pod względem zasobów

### Przykładowe implementacje

* Zablokuj tworzenie i robienie kopii
  * Prywatny konstruktor (nie można wywołać `new`)
  * Usuń konstruktor kopiujący oraz kopiujący operator przypisania (`delete`)
* Utworzyć statyczną metodę `getInstance()` zwracająca referencję (do statycznego obiektu) lub wskaźnik (do obiektu utworzonego na stercie) utworzonego wewnątrz metody `getInstance()`

#### Implementacja 1

{% gist 5b9682b75ae42d134836a08d0befb481 %}

#### Implementacja 2

{% gist 25e987c6a8a598a6c1247565bf9d7d56 %}

### Problemy ze wzorcem Singleton

* Problematyczne jest testowanie klas/metod korzystających z Singleton'a (**jak przetestować klasę UserFinder z przykładu poniżej?**)
  * Nie można na potrzeby testów podmienić klasy zapewniającej na przykład dostęp do bazy inną klasą (testowana klasa jest silnie sprzeżona z Singleton'em)
  * Jedyne co można zrobić to napisać test, podczas którego nastąpi połączenie z prawdziwą bazą - **taki test nie jest już testem jednostkowym, a testem integracyjnym**

{% gist bf127f3644bb5499b21f0b75e98792f7 %}

### Rozwiązanie problemu

Zastosowanie Dependency Injection (DI):
1. Utwórz interfejs, który implementuje Singleton (metody czysto wirtualne zwracające konkretne wartości zamiast statycznego `getInstance()` (nie można dziedziczyć statycznych pól klasy))
   * Klasy wymagające dostępu do danego zasobu (w zastosowanym przykładzie - do bazy danych) otrzymają w konstruktorze referencję/wskaźnik do klasy wykonującej zapytania do bazy
2. Przygotowując klasę do testów, przekaż do konstruktora zaślepkę/mocka która będzie zwracać w testach z góry określone wartości



## Inne ciekawe

> When discussing which patterns to drop, we found that we still love them all. (Not really—I'm in favor of dropping Singleton. Its use is almost always a design smell). Erich Gamma

## 5. Bibliografia

- [Dmitri Nesteruk - Design Patterns in Modern C++ (Udemy)](https://www.udemy.com/course/patterns-cplusplus/)