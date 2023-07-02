---
layout: post
title: Specjalne funkcje składowe klas
categories: [post]
date: 2022-07-20
permalink: /specjalne-funkcje-skladowe-klasy
---

# Specjalne funkcje składowe klasy
{: .no_toc }

---

1. Destruktor
2. Konstruktor domyślny 
3. Konstruktor kopiujący
4. Kopiujący operator przypisania
* **Żeby zadziałał, obiekt na który kopiujemy musi już istnieć**
* Warto sprawdzić czy nie przypisujemy tego samego obiektu do siebie: *if (this == &other) return;*
5. Konstruktor przenoszący
6. Przenoszący operator przypisania
* **Żeby zadziałał, obiekt na który przenosimy musi już istnieć**
* Warto sprawdzić czy nie przypisujemy tego samego obiektu do siebie: *if (this == &other) return;*

{% gist 3b608e67a63b227ec9fe996ca0620126 %}

## Wymuszanie domyślnej implementacji

{% gist 240d3289b75ac92dbe8be7c82bd8cb1c %}

## Usunięcie wybranej składowej klasy

{% gist 474b8d2e7e0102d14e7ed1341a09caf3 %}
