---
layout: post
title: Wzorzec projektowy Singleton
date: 2021-11-28 17:00:00
permalink: /XXX
search_exclude: true
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




## Bibliografia

* http://home.agh.edu.pl/~glowacki/docs/matwykl/O-o/_ProgObiekt-C++14-Rozsz.pdf











---
layout: post
title: Wzorce projektowe - Singleton
date: 2021-12-17 17:00:00
permalink: /singleton
---

# Wzorce projektowe - Singleton
{: .no_toc }

<details close markdown="block">
  <summary>
    Spis treści
  </summary>
  {: .text-delta }
1. TOC
{:toc}
</details>

## Kiedy u�ywa�?

* Kiedy w programie potrzebna jest tylko jedna instancja danej klasy (wszystkie klasy korzystaj� z tego jednego obiektu). Przyk�ady:
  * Dost�p do bazy danych
  * Fabryka obiekt�w
  * Jakakolwiek klasa, kt�rej stworzenie b�d� r�wnoleg�e u�ywanie wi�cej ni� jednego obiektu **jest kosztowne pod wzgl�dem zasob�w**

## Przyk�adowe implementacje

### Singleton Meyers'a

### Singleton z u�yciem mutex�w

* Zablokuj tworzenie i robienie kopii
  * Uczy� konstruktor prywatnym
  * Usu� konstruktor kopiuj�cy oraz kopiuj�cy operator przypisania (`= delete`)
* Rozwa� p�n� inicjalizacj� (stworzenie obiektu dopiero w momencie pierwszego u�ycia)
* Zabezpiecz moment tworzenia obiektu mutex'em
* Zabezpiecz zasoby kt�rymi dysponuje ORAZ zasoby, kt�rymi dysponuje Singleton przy u�yciu mutex'�w (je�li aplikacja jest wielow�tkowa)

### Singleton z u�yciem call_once


* Utw�rz statyczn� metod� np. `getInstance()` zwracaj�ca statyczny obiekt (przez referencj� lub wska�nik)

## Problemy ze wzorce Singleton

* Utrudnione (b�d� niemo�liwe) jest testowanie klas/metod korzystaj�cych z Singleton'a
  * Nie mo�na na potrzeby test�w podmieni� klasy zapewniaj�cej na przyk�ad dost�p do bazy inn� klas� (testowana klasa jest silnie sprze�ona z Singleton'em)
    * Jedyne co mo�na zrobi� to napisa� test, podczas kt�rego nast�pi po��czenie z prawdziw� baz� - **taki test nie jest ju� testem jednostkowym, a testem integracyjnym**

## Rozwi�zanie problemu

* Zastosowanie Dependency Injection (DI)
  * Utw�rz interfejs  interfejsu naszemu Singletonowi, b�dzie zawiera� on tylko czysto wirtualne metody faktycznie zwracaj�ce konkretne warto�ci (a nie `getInstance()`)

## Rzeczy, kt�re wa

Nie mo�na dziedziczy� statycznych p�l klasy;.

## 5. Bibliografia

- [Dmitri Nesteruk - Design Patterns in Modern C++ (Udemy)](https://www.udemy.com/course/patterns-cplusplus/)
