---
layout: post
title: Zasady SOLID, DRY, KISS i YAGNI
date: 2022-01-27 17:00:00
permalink: /zasady
search_exclude: true
---

# Zasady SOLID, DRY, KISS i YAGNI
{: .no_toc }

<details open markdown="block">
  <summary>
    Spis treści
  </summary>
  {: .text-delta }
1. TOC
{:toc}
</details>

---

## Zasady SOLID


1. Single Responsibility – Zasada jednej odpowiedzialności
2. Open/Closed – Zasada otwarte-zamknięte
3. Liskov Substitution – Zasada podstawienia Liskov
4. Interface Segregation – Zasada segregacji interfejsów
5. Dependency Inversion – Zasada odwrócenia zależności

### Single Responsibility

* Każda klasa powinna mieć tylko jedną odpowiedzialność, a przez to jeden potencjalny powód do zmiany
### Open/Closed

* Klasa powinna być otwarta na rozbudowę, lecz zamknięta na modyfikację
  * Nie powinno sie modyfikować kodu, który został przetestowany i już wysłany do klientów
### Liskov Substitution

* Jeśli jakaś funkcja przyjmuje wkaźnik lub referencję na klasę bazową, przekazanie jakiejkolwiek klasy pochodnej nie powinno zmieniać spodziewanego zachowania

```cpp
class Rect {
protected:
    int width, height;
public:
    Rect(int w, int h) : width(w), height(h) { }

    virtual void setW(int w) { width = w; }
    int getW() const { return width; }
    virtual void setH(int h) { height = h; }
    int getH() const { return height; }
    int area() const { return width * height; }
};

void process(Rect& r) {
    int w = r.getW();   // zapisujemy szerokość
    r.setH(10);

    // sprawdzamy czy szerokość to 10 * (zapisane w)
    std::cout << "Expected area: " << (w * 10) << ", got: " << r.area() << std::endl;
}

class Sq : public Rect {
public:
    Sq(int s) : Rect{s, s} { }

    void setW(int w) override { width = w; height = w; }
    int getW() const { return width; }
    void setH(int h) { height = h; width = h; }
};

// ... 

Rect r{3, 4};
process(r);

Sq s{5};
process(s);
```

>> Expected area: 30, got: 30
>> Expected area: 50, got: 100

### Interface Segregation

* Wymuszanie na klasach pochodnych żeby implementowały funkcjonalność, której nie potrzebuje
  * Często wtedy klasy pochodne mają pustą implementację `{ }`
  * Lepszym rozwiązaniem są małe interfejsy

### Dependency Inversion

* Wysokopoziomowe moduły nie powinny zależeć od modułów niskopoziomowych - oba powinny zależeć od abstrakcji (intefejsy, klasy abstrakcyjne i klasy bazowe)
  * Przykładowo, jeśli klasa przyjmuje wektor i iteruje sobie po nim i coś robi
  * Jeśli zmieni się implementacja niskopoziomowego modułu, trzeba będzie zmienić implementację tego wysokopoziomowego
* Abstrakcje nie powinny być zależne od implementacji tylko to implementacje powinny być zależne od abstrakcji

## DRY

* *Don’t Repeat Yourself* - nie powtarzaj się
  * Łatwiejsze utrzymywanie kodu

## KISS

* Jak najprosztszych i jak najbardziej zrozumiałych rozwiązań

## YAGNI

* Nie należy tworzyć kodu na przyszłość
* Jeżeli w danym momencie kod jest zbędny, nie należy go pisać ani utrzymywać
