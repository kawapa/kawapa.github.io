---
layout: post
title: Testowanie metod prywatnych
categories: [post]
date: 2021-10-10
permalink: /testowanie-metod-prywatnych
---

# Testowanie metod prywatnych
{: .no_toc }

<details open markdown="block">
  <summary>
    Spis treści
  </summary>
  {: .text-delta }
1. TOC
{:toc}
</details>

Istnieją różne opinie na temat tego czy należy testować prywatne metody klas. Z jednej strony, jeśli testy metod publicznych "przechodzą", znaczy to że poprawnie działa też część prywatna. Z drugiej strony metody prywatne są często bardzo skomplikowane i przetestowanie wszystkich warunków przegowych tylko przez publiczny interfejs klasy jest trudne. Czasem też po prostu trzeba to zrobić bo zespół ma narzucony KPI w postaci procentowego pokrycia kodu testami.

Jeśli musimy przetestować prywatną cześć klasy, trzeba najpierw zdobyć do niej dostęp. Oto cztery sposoby:

1. Stworzenie klasy zaprzyjaźnionej
2. Użycie makra `#define private public`
3. Oznaczenie metod prywantych jako chronione
4. Przeniesienie funkcjonalności do nowej klasy

## Stworzenie klasy zaprzyjaźnionej

* **Integerencja w kod produkcyjny** ...chyba że skorzystamy z tak zwanej kompilacji warunkowej (*conditional compilation*) i w wersji *Release* usuniemy deklarację zaprzyjaźnionych klas

{% gist 6879f0bed792953707705c74cd4bc1d7 %}

## Użycie makra `#define private public`

* Makro `#define private public` wstawiajmy przed include'a z plikiem testowanej klasy

## Oznaczenie metod prywantych jako chronione

* **Integerencja w kod produkcyjny!**
* Klasa testująca dziedziczy po klasie którą mamy przetestować

{% gist b1f1fff7054c6614f5dd870d9ef305c2 %}

## Przeniesienie funkcjonalności do nowej klasy

* Najczystszy sposób, trzymając się tego podejścia tworzymy małe klasy z jasnymi odpowiedzialnościami
* Preferowane przechowywanie wskaźnika lub referencji i użycie DI

{% gist 666a4a7a87f4ecb2b323a48c749c77e7 %}

## Bibliografia

- [Marcell Lipp - How to Unit Test a Private Function in C++](https://www.codeproject.com/Tips/5249547/How-to-Unit-Test-a-Private-Function-in-Cplusplus)
