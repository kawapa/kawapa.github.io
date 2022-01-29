---
layout: post
title: STL - Kontenery
date: 2022-01-29 17:00:00
permalink: /kontenery
---

# STL - Biblioteka standardowa
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

* Przechowują dane określonego typu i same zarządza pamięcią - kiedy `std::vector` przestaje istnieć, sam usuwa dane z pamięci
* Zalecane jest używanie metod/algorytmów dedykowanych konkretnemu kontenerowi. Metody globalne są mniej zoptymalizowane i przez to mogą być wolniejsze
* `std::begin(vec)` i `std::end(vec)` jest bardziej uniwersalne bo działa też dla zwykłych tablic z C
* Nie należy dziedzczyć po kontenerach z biblioteki STL bo nie mają one wirtualnych destruktorów
	* Lepiej zastosować mechanizm agregacji

---

## Kontenery sekwencyjne

Kontener sekwencyjny - elementy są przechowywane dokładnie w takiej kolejności w jakiej są wrzucane.

<p align="center">
  <img src = "2022/sequence_containers.png">
</p>

| Kontener | Wstawianie | Dostęp | Usuwanie | Wyszukiwanie |
|:---------|:-----------|:-------|:---------|:-------------|
| `array` | - | O(1) |  | - | O(n) |
| `vector` | Na koniec: O(1)<br> Na pocz.: O(n) | O(1) | Z końca: O(1)<br> Inne: O(n) | Posortowany: O(log n)<br> Inne: O(n) |
| `deque` | Na koniec: O(1)<br> Na pocz.: O(n) | O(1) | Z końca: O(1)<br> Inne: O(n) | Posortowany: O(log n)<br> Inne: O(n) |
| `list`/`forward_list` | Pocz./koniec: O(1)<br> Z it:: O(1)<br> W miejsce: O(n) | Pocz./koniec: O(1)<br> Z it: O(1)<br> W miejsce: O(n) | Pocz./koniec: O(1)<br> Z it: O(1)<br> W miejsce: O(n) | O(n) |

## Wspólne 

| Metoda | Opis |
|:-------------|:------------------|
| `front` |  |
| `empty` |  |
| `max_size` |  |
| `begin(), end()` |  |
| `cbegin(), cend()` |  |
| `swap()` |  |

### `std::array`

* Tablica o stałym rozmiarze
* **Cache-friendly** bo:
  * Elementy leżą kolejno w pamięci
  * Podczas iterowana po kontenerze kolejne jego elementy będą ładowane do pamięci podręcznej procesora z wyprzedzeniem
* Alokowany na stosie
* Dostęp do n-tego elementu - O(1)
* Żeby funkcja mogła przyjmować jako argument `std::array` trzeba zrobić z niej funkcję szablonową:

```cpp
template <size_t T>
void print(const std::array<int, T>& array) {
  for (int i = i; i < T, ++i) {
    std::cout << array[i] << "\n";
  }
}
```

| Metoda | Opis |
|:-------------|:------------------|
| Wstawianie | - |
| Dostęp | **O(1)** bo elementy ułożone ciągiem w pamięci |
| Usuwanie | - |
| Wyszukiwanie | O(n)<br> **O(log n)** jeśli posortowany) |

### `std::vector`

* **Chache-friendly** bo:
  * Elementy leżą kolejno w pamięci
  * Podczas iterowana po kontenerze kolejne jego elementy będą ładowane do pamięci podręcznej procesora z wyprzedzeniem
* Alokowany dynamicznie na stercie
* Implementacja
  * Stos: zazwyczaj 3 wskaźniki: `begin`, `end`, `capacity`
  * Sterta: elementy
* Zjawisko inwalidacji iteratorów
* `reserve()` przygotowuje *capacity*
* `shrink_to_fit()` zwalnia wolną pamięć
* Realokacja kiedy `size() == capacity()`

| Metoda | Opis |
|:-------------|:------------------|
| Wstawianie | Na koniec: **O(1)** bo wiemy gdzie jest `end`<br> Jeśli trzeba będzie realokować: **O(n)**<br> Na początek/środek: **O(n)** bo trzeba przesunąć wszystkie pozostałe |
| Dostęp | **O(1)** bo elementy ułożone ciągiem w pamięci |
| Usuwanie | **O(n)** bo trzeba przesunąć wszystkie pozostałe<br> Końcowy element: **O(1)** |
| Wyszukiwanie | **O(n)**<br> **O(log n)** jeśli posortowany |

### `std::list`

* Lista dwukierunkowa
* Elementy porozrzucane po pamięci
* Implementacja
  * Stos: 3 wskaźniki: `begin`, `end`, `size`
  * Sterta: elementy
* Każdy element oprócz danych ma 2 dodatkowe wskaźniki: *poprzedni* i *następny*
* Ma własną funkcję sortującą
* Nie występuje inwalidacja iteratorów

| Metoda | Opis |
|:-------------|:------------------|
| Wstawianie | **O(1)** bo to tylko przypisanie wskaźników |
| Dostęp | **O(n)** bo trzeba iterować od początku |
| Usuwanie | **O(1)** bo to tylko przypisanie wskaźników |
| Wyszukiwanie | **O(n)** bo trzeba iterować od początku<br> Na posortowanej liście też **O(n)** |

#### Kiedy `std::list` a kiedy `std::vector`?

* Jeśli chcemy mieć szybki dostęp do n-tego  elementu -> `std::vector`
* Jeśli często potrzebujesz dodawać i usuwać elementy -> `std::list`

### `std::forward_list`

* Lista jednokierunkowa
* Elementy porozrzucane po pamięci
* Implementacja
  * Stos: 1 wskaźniki: `begin`
  * Sterta: elementy
* Każdy element oprócz danych ma 1 dodatkowy wskaźniki: *następny*
* Jeśli potrzebujesz listy, preferuj `std::forward_list` (oszczędność pamięci) chyba, że potrzebujesz iterować od końca albo potrzebujesz mieć dostęp do `size()` - wtedy `std::list`

| Metoda | Opis |
|:-------------|:------------------|
| Wstawianie | **O(1)** bo to tylko przypisanie wskaźników |
| Dostęp | **O(n)** bo trzeba iterować od początku |
| Usuwanie | **O(1)** bo to tylko przypisanie wskaźników |
| Wyszukiwanie | **O(n)** bo trzeba iterować od początku<br> Na posortowanej liście też **O(n)** |

### `std::deque`

* Kolejka dwukierunkowa
  * Hybryda wektora i listy
* Alokowany w nieciągłym kawałku pamięci
  * Fragmentami (*chunks*) elementy leżą kolejno w pamięci
    * Dane załadowane z jednego kawałka są cache-friendly
  * Kawałki są tej samej długości
* Implementacja
  * Stos: wskaźniki `begin`, `end`, `size` na tablicę z adresami kawałków
  * Sterta: wektor wskaźników na wszystkie kawałki oraz same *chunki* 
* Przykład zastosowania: kolejka FIFO

| Metoda | Opis |
|:-------------|:------------------|
| Wstawianie | Na początek/koniec: **O(1)** bo wiemy gdzie są `begin` oraz `end`<br> W środku: **O(n)** bo trzeba przenieść pozostałe |
| Dostęp | **O(1)** bo elementy w *chunkach* są ułożone ciągiem w pamięci |
| Usuwanie | Początkowego/końcowego: **O(1)** bo wiemy gdzie są `begin` oraz `end`<br> Z środka: **O(n)** bo trzeba przenieść pozostałe |
| Wyszukiwanie | **O(n)** bo trzeba iterować od początku<br> Na posortowanej liście też **O(n)** |

<p align="center">
  <img src = "2022/deque.png">
</p>
