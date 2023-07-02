---
layout: post
title: Advanced Design Patterns Design Principles
permalink: /stos-czy-sterta
search_exclude: true
---

# Advanced Design Patterns Design Principles
{: .no_toc }

---




## Design principles

* Rady i wskazówki, a nie bezwzględne zasady do przestrzegania
* Zdefiniowane na podstawie wieloletnich doświadczeń
* Pozwalają uniknąć złego designu

### Symptomy złego designu

* Trudno modyfikowalne, na przykład ze względu na:
    * Zależności
    * Zmiana w jednym miejscu powoduje konieczność zmiany kodu w wielu miejscach
* Fragility
    * Zmiana kodu w jednym miejscu powoduje "zepsucie" kodu w innym
* Nie da użyć tego samego kodu w innym miejscu/projekcie

## Design principles

Nie istnieje żaden ogólny katalog dobrych praktyk w kontekście projektowania. Programiści często znają te dobre praktyki, które dotyczą ich domeny lub technologii. 

1. Enkapsuluj to co zmienne
2. Preferuj kompozycję nad dziedziczenie
3. Niech Twoje programy opierają się interfejsach, nie konkretnych implementacjach
4. Dbaj o Loose coupling (luźne powiązanie pomiędzy obiektami, które ze sobą współpracują)
5. SOLID
    5.1 Single responsibility - klasa powinna mieć tylko jeden powód do zmiany
    5.2 Open / Closed
    5.3 Liskow substitution principle
    5.4 Interface segregation
    5.5 Dependency inversion

## Design principles, a wzorce projektowe

* Design principles to ogólne, abstrakcyjne zasady/rady, które można zastosować tworząc obiektową architekturę aplikacji
* Wzorce projektowe to rozwiązania konkretnych problemów architektonicznych, w formie diagramów które można zaadoptować we własnej aplikacji 

### Enkapsuluj to, co zmienne

* Zidentyfikuj te aspekty swojej aplikacji, które są zmienne i odseparuj je od tych które są stałe
    * Jeśli jakaś część architektury zmienia się z każdym nowo-dodanym ficzerem - odseparuj ją od reszty! Dzięki temu, jak następnym razem będziesz modyfikował tę część, zrobisz to nie dotykając reszty kodu

#### Przykład złego kodu

Problemy z tym kodem:
    // ta czesc kodu bedzie sie zmieniac (beda dochodzic nowe nalesniki)
    // klauzula if jest w tej samej klasie i pliku jak inny wazny kod, ktory dotyczy 
    // przygotowywania nalesnikow

```cpp
unique_ptr<Pancake> orderPancake(string type) {
    unique_ptr<Pancake> pancake;

    if (type == "classic") {
        pancake = make_unique<classicPancake>;
    } else if (type == "blueberry") {
        pancake = make_unique<BlueberryPancake>();
    } else if (type == "banana") {
        pancake = make_unique<BananPancake>();
    }

    pancake.cook();
    pancake.plate();
    pancake.addButter();

    return pancake;
}
```

https://www.codeproject.com/Articles/1131770/Factory-Patterns-Simple-Factory-Pattern

#### Przykład usprawnienia

* Prosta fabryka
* Każda zmiana menu nie wymusza zmiany kodu w kodzie odpowiedzialnym za przygotowanie naleśnika

```cpp
    class PancakeFactory {
    public:
        unique_ptr<Pancake> createPancake(string type) {
            unique_ptr<Pancake> pancake;

            if (type == "classic") {
            pancake = make_unique<classicPancake>;
            } else if (type == "blueberry") {
                pancake = make_unique<BlueberryPancake>();
            } else if (type == "banana") {
                pancake = make_unique<BananPancake>();
            }

            return pancake;
        }
    };

    // ...

    unique_ptr<Pancake> orderPancake(string type) {
        PancakeFactory pf;
        unique_ptr<Pancake> pancake = pf.createPancake(type);

        pancake.cook();
        pancake.plate();
        pancake.addButter();

        return pancake;
    }
```


## Bibliografia

* https://www.guru99.com/stack-vs-heap.html
* https://www.geeksforgeeks.org/stack-vs-heap-memory-allocation/
* https://www.codeproject.com/Articles/76153/Six-important-NET-concepts-Stack-heap-value-types
