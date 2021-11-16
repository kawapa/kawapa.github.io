---
layout: post
title: "Jedno makro dla funkcji przyjmującej różną liczbę argumentów"
date: 2021-08-30 17:55:00
permalink: /jedno-makro-dla-funkcji
---

# Jedno makro dla funkcji przyjmującej różną liczbę argumentów

Makro to instrukcja dla preprocesora, który przetwarza i przygotowuje kod źródłowy programu do kompilacji. Gdy preprocesor napotyka na zdefiniowane wcześniej makro, podmienia je na zdefiniowane wcześniej wyrażenie lub instrukcję. Używanie makr w nowoczesnym kodzie jest mocno kontrowersyjne (może oprócz Embedded), ale często spotyka się je w projektach legacy.

## Tytułowy problem

Mamy w projekcie klasę do zrzucania/zapisywania logów. Może one przyjmować (w zależności od typu zdarzenia) różne argumenty np.: tekst, liczby/enum'y (które określają na przykład typ i klasę zdarzenia). Co zrobić by móc wygodnie korzystać z przeciążonej funkcji `log()` (na przykład poprzez `LOG(...)`, która przyjmie wszystkie możliwe formy argumentów)?

{% gist 292f8a2d65db9388b7aac565d4bc76d6 %}

## Rozwiązanie

{% gist e5a62e16ad8a790cd728a3dc85f258ad %}

## Bibliografia

* [Stack Overflow - Overloading Macro on Number of Arguments](https://stackoverflow.com/questions/11761703/overloading-macro-on-number-of-arguments)
