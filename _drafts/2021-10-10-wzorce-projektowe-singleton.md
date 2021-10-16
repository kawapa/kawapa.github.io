---
layout: post
title: "Wzorce projektowe: Singleton"
date: 2021-10-10 17:00:00
categories: 
---

** OPIS **
** 1. Co to jest wzorzec? **
** 2. Po co się je stosuje, co ułatwiają **

* Wzorzec projektowy to ustandaryzowany sposób rozwiązania jakiegoś problemu projektowego. Dzięki któremu wszyscy wiedzą o co chodzi jeśli pada taka nazwa
* Wzorce projektowe zostały spopularyzowane przez wydaną w 1994 książkę autorstwa "gangu czworga" (w przykładach użyto tam Smalltalk'a i C++)
* Podział wzorców:
  * Wzorce kreacyjne
  * Wzorce strukturalne
  * Wzorce behawioralne

## Wzorzec Singleton

> When discussing which patterns to drop, we found that we still love them all. (Not really—I'm in favor of dropping Singleton. Its use is almost always a design smell). Erich Gamma

### Kiedy używać

* W programie potrzebna jest tylko jedna instancja danej klasy (wszystkie klasy korzystają z tego jednego obiektu)
  * Przykłady: dostęp do bazy danych, fabryka obiektów lub jakakolwiek inna klasa, której stworzenie obiektu bądź równoległe używanie więcej niż jednego jest kosztowne pod względem zasobów

### Implementacja

* Zablokuj tworzenie i robienie kopii
  * Prywatny konstruktor
  * Usuń konstruktor kopiujący oraz kopiujący operator przypisania (`delete`)
* Utworzyć statyczną metodę `getInstance()` zwracająca referencję lub wskaźnik do statycznego obiektu utworzonego wewnątrz metody `getInstance()`

### Problemy ze wzorce Singleton

* Problematyczne jest testowanie klas/metod korzystających z Singleton'a
  * Nie można na potrzeby testów podmienić klasy zapewniającej na przykład dostęp do bazy inną klasą (testowana klasa jest silnie sprzeżona z Singleton'em)
    * Jedyne co można zrobić to napisać test, podczas którego nastąpi połączenie z prawdziwą bazą - **taki test nie jest już testem jednostkowym, a testem integracyjnym**

### Rozwiązanie problemu

* Zastosowanie DI
  * Utworzenie interfejsu naszemu Singletonowi, będzie zawierał on tylko czysto wirtualne metody faktycznie zwracające konkretne wartości (a nie `getInstance()`)



Nie można dziedziczyć statycznych pól klasy;.

## 5. Bibliografia

- [Dmitri Nesteruk - Design Patterns in Modern C++ (Udemy)](https://www.udemy.com/course/patterns-cplusplus/)
