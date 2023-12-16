---
layout: post
title: Testowanie metod prywatnych
categories: [post]
date: 2021-10-10
permalink: /testowanie-metod-prywatnych
nav_exclude: true
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

```cpp
class KlasaWspierajaca;

class KlasaTestowana {
    int oblicz() { return 0; }
    friend KlasaWspierajaca;
};

class KlasaWspierajaca {
public:
    void testuj() {
        KlasaTestowana kt;
        ASSERT_TRUE(kt.oblicz() == 0);
    }
};

int main() {
    KlasaWspierajaca kw;
    kw.testuj();
}
```

## Użycie makra `#define private public`

* Makro `#define private public` wstawiajmy przed include'a z plikiem testowanej klasy

## Oznaczenie metod prywantych jako chronione

* **Integerencja w kod produkcyjny!**
* Klasa testująca dziedziczy po klasie którą mamy przetestować

```cpp
class KlasaTestowana {
protected:
    int oblicz() { return 0; }   
};

class KlasaWspierajaca : KlasaTestowana {
public:
    void testuj() {
        ASSERT_TRUE(oblicz() == 0);
    }
};

int main() {
    KlasaWspierajaca kw;
    kw.testuj();
}
```

## Przeniesienie funkcjonalności do nowej klasy

* Najczystszy sposób, trzymając się tego podejścia tworzymy małe klasy z jasnymi odpowiedzialnościami
* Preferowane przechowywanie wskaźnika lub referencji i użycie DI

```cpp
class Kalkulator {
    int oblicz() { return 0; }
};

class KlasaTestowana {
    Kalkulator kalkulator;
};

class KlasaWspierajaca {
public:
    void testuj() {
        Kalkulator kalkulator;
        ASSERT_TRUE(kalkulator.oblicz() == 0);
    }
};

int main() {
    KlasaWspierajaca kw;
    kw.testuj();
}
```

## Bibliografia

- [Marcell Lipp - How to Unit Test a Private Function in C++](https://www.codeproject.com/Tips/5249547/How-to-Unit-Test-a-Private-Function-in-Cplusplus)
