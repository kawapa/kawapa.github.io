---
layout: post
title: Optymalizacje
categories: [post]
date: 2022-06-18
permalink: /optymalizacje
---

# Optymalizacje
{: .no_toc }

<details close markdown="block">
  <summary>
    Spis treści
  </summary>
  {: .text-delta }
1. TOC
{:toc}
</details>

---

## const correctness

Świadome korzystanie ze słowa kluczowego `const` (na przykład przy przekazywaniu argumentów do funkcji) jeśli nie chcemy aby obiekt był modifikowany.

Zalety:

* Uniemożliwia przypadkową edycję obiektu, a także przypisanie czegoś do niego
* Umożliwia kompilatorowi optymalizację kodu bo stan obiektu jest znany w każdym momencie działania programu
* Sposób na dokumentowanie kodu kodu. Korzystanie z const correctness uniemożliwia użycie kodu w niewłaściwy sposób
* Umożliwia szybkie wykrycie: `const int x = 0; if (x = y) { ... }`

Uwagi:
* `const` można znieść korzystając z `const_cast` lub słowa kluczowego mutable (funkcje `const` będą mogły zmieniać stan obiektu, który jest `const`)

class Entity {
public:
    auto& getThing() const { return thing; }
    // Typ zwracany: const Thing&
    // Pomimo tego, że typ zwracany to auto&

    auto& getThing() { return thing; }
    // Typ zwracany: Thing&
private:
    Thing thing;
};

## Przekazywanie przez referencję

## Rozmieszczenie danych w pamięci

## Google benchmark

## Copy elision

## RVO, NRVO

* Zwracając obiekt lokalny zadziała RVO lub NRVO, w innym przypadku trzeba należy przypisywać do referencji do *r-value*
	* Na przykład jeśli metoda zwraca składową klasy (getter)

## Pamięć cache

## Cache locality

## False sharing
