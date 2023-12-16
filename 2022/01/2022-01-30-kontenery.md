---
layout: post
title: STL - Kontenery
categories: [post]
date: 2022-01-30
permalink: /kontenery
nav_exclude: true
---

# STL - Kontenery
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
  <img src = "2022/01/sequence_containers.png">
</p>

---

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

---

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

---

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

#### Kiedy wybrać listę, a kiedy wektor?
{: .no_toc }

* Jeśli chcemy mieć szybki dostęp do n-tego  elementu -> `std::vector`
* Jeśli często potrzebujesz dodawać i usuwać elementy -> `std::list`

---

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

---

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
  <img src = "2022/01/deque.png">
</p>

---

## Kontenery asocjacyjne

* Elementy są przechowywane w **określonej** kolejności
  * Nie są asocjacyjne bo wg definicji kontener asocjacyjny to taki który mapuje elementy jednego typu na drugi. W STL, `set<T>` niczego nie kojarzy...

### Kontenery uporządkowane (posortowane)

* Zaimplementowane jako drzewa binarne
  * Są samobalansujące czyli po wstawianiu i usuwaniu będą się one zmieniać
* Zjawisko unieważniania iteratorów, ale tylko tego który jest usuwany
* Żeby kluczem mógł być typ użytkownika, należy zdefiniować **operator mniejszości**

```cpp
struct Point {
    int a;

    // Opcja 1: wewnątrz klasy (musi być const)
    bool operator<(const Point& other) const { return a < other.a; }
    Point(int a) : a(a) { }
};

// Opcja 2: na zewnątrz klasy (bez const)
bool operator<(const Point& lhs, const Point& rhs) {
    return lhs.a < rhs.a;
}

// Opcja 3: jako funktor, który trzeba przekazać przy tworzeniu
struct Comparator {
  bool operator<(const Point& lhs, const Point& rhs) {
    return lhs.a < rhs.a;
}

std::map<Point, std::string, Comparator>

// Opcja 4: jako lambdę, którą trzeba przekazać (z zastosowaniem decltype)
auto comparator = [](auto& lhs, auto& rhs){ return lhs.a < rhs.a; }

std::map<Point, std::string, decyltype(comparator)>
};

// Opcja 5: napisać specjalizację std::less
// Nie trzeba wtedy niczego przekazywać do mapy podczas tworzenia

namespace std {
    template<>
    struct less<Point> {
       bool operator()(const Point& lhs, const Point& rhs) const {
           return lhs.a < rhs.a;
       }
    };
}
```

| Metoda | Opis |
|:-------------|:------------------|
| Wstawianie | **O(log n)** bo trzeba wyszukać miejsce |
| Dostęp | **O(log n)** |
| Usuwanie | **O(log n)** bo trzeba znaleźć element |
| Wyszukiwanie | **O(log n)** |

#### `std::set` i `std::multiset`

* Duplikaty:
  * `std::set` -> Nie
  * `std::multiset` -> Tak

#### `std::map` i `std::multimap`

* Duplikaty:
  * `std::map` -> Nie
  * `std::multimap` -> Tak
* Idealne do częstego wyszukiwania i **rzadkiego dodawania i usuwania** (nie są *cache-friendly*)
  * Alternatywy żeby uzyskać *cache-friendly*:
    * Dla `std::map` -> `std::vector<pair<Key, Value>>`
    * Dla `std::multimap` -> `std::vector<std::pair<Key, std::vector<Value>>`
* Implementacja:
  * Sterta: (ilość elementów) * (rozmiar pary + (2 wskaźniki: el. mniejszy i większy))
  * Stos: 3 wskaźniki: `root`, komparator i alokator

### Kontenery nieuporządkowane

* Zaimplementowane jako mapy hashujące (tablice hashujące)
* Mogą, ale nie muszą być *cache-friendly* (często są implementowane jako hybryda `std::vector` i `std::list`)
* Skoro szybsze niż uporządkowane to po co ich używać?
  * Kontenery nieuporządkowane mają gorszą złożoność pesymistycznego przypadku (`O(n)`)
* Dla każdej wartości którą wrzucamy obliczana jest tzw. funkcja skrótu
  * Dla niektórych elementów może ona dać taki sam rezultat, oznacza to że trafią do tego samego kubełka (*bucket'a*)
  * Każdy element, który wchodzi do kubełka ma wskaźnik na następny element
* Żeby kluczem mógł być typ użytkownika, należy zdefiniować **funkcję haszującą** i **operator porównania**

```cpp
struct Point {
    int a;

    Point(int a) : a(a) { }

    // Operator porównania, opcja 1: Operator wewnątrz klasy (const)
    // bool operator==(const Point& other) const {
    //     return a == other.a;
    // }
};

// Operator porównania, opcja 2: Operator na zewnątrz klasy (bez const)
bool operator==(const Point& lhs,const  Point& rhs) {
    return lhs.a == rhs.a;
}

// Hash, opcja 1: napisać swój własny funktor
struct MyHash {
    std::size_t operator()(const Point& point) const {
        std::size_t h1 = std::hash<int>{}(point.a);
        return h1;

        // Mając 2 pola można:
        // std::size_t h2 = std::hash<int>{}(point.a);
        // return h1 ^ h2;
    }

};

// Hash, opcja 2: napisać specjalizację dla std::hash
namespace std {
    template<>
    struct hash<Point> {
        std::size_t operator()(const Point& point) const {
          return std::size_t h1 = std::hash<int>{}(point.a);
        }
    };
}
```

| Metoda | Opis |
|:-------------|:------------------|
| Wstawianie | **O(1)** |
| Dostęp | **O(1)** |
| Usuwanie | **O(1)** |
| Wyszukiwanie | **O(1)** |

* Najgorszy przypadek to **O(n)** jeśli funkcja skrótu jest nienajlepsza

#### Buckety i funkcja haszująca

* Funkcja haszująca - funkcja która z dowolnego obiektu generuje indeks w tablicy haszującej
  * Dobra funkcja haszująca powoduje zmianę bitów wejściowych o około 50% przy zmianie tylko jednego bita wejściowego

Wrzucenie elementu do kontenera:

1. Obliczenie funkcji skrótu (`hash`)
2. Wyznaczenie kubełka do którego należy wstawić element: `hash % (liczba_kubełków`
3. Wstawienie elementu

* Jeśli jeden kubełek ma wyraźnie więcej elementów niż pozostałe, to ogólna złożoność obliczeniowa dla wyszukiwania dąży do przeciążony złożoność obliczeniowa dąży do O(n)
* Implementacja sama zarządza tym w jaki sposób są dane zorganizowane, ale można podejrzeć pewne wartości (można wtedy postarać się o lepszą funkcję haszującą) lub **ręcznie wywołać metodę** `rehash()`
  * Jeśli `load_factor()` > `max_load_factor()` to następuje `rehash()` (zwiększana jest liczba kubełków)

| Metoda | Opis |
|:-------------|:------------------|
| `bucket_count` | **O(1)** |
| `max_load_factor()` | **O(1)** |
| `load_factor()` | Średnie obciążenie dla kubełka |

#### `std::unordered_set` i `std::unordered_multiset`

* Duplikaty:
  * `std::unordered_set` -> Nie
  * `std::unordered_multiset` -> Tak
* Implementacja:
  * Sterta: (ilość elementów) * (rozmiar obiektu + wskaźnik na kolejny element) + (pamięć na kubełki)
  * Stos: Wskaźniki na: wektor z bucketami, `begin`, `end`, `size`, `hash`, alokator...
 
#### `std::unordered_map` i `std::unordered_multimap`

* Duplikaty:
  * `std::unordered_map` -> Nie
  * `std::unordered_multimap` -> Tak

---

## Adaptery

Domyślnie wszystkie adaptery używają kontenera deque.

### `std::stack`

* Stos (LIFO)
* Operacje: `push()`, `pop()`, `top()`

### `std::queue`

* kolejka (FIFO))
* Operacje: `pop()`, `push()`, `back()`, `front()`

### `std::priority_queue`

* Kolejka priorytetowa
* Ściąga zawsze top (element z najwyższą wartością)
* Można to zmienić przy tworzeniu kolejki i funkcji `std::greater`
	* `std::prioritity_queue<int, std::vector<int>, std::greater<int>>`
* Operacje
  * `pop()` - ściąga z góry
  * `push()` - przy wstawianiu są elementy są sortowane, największa wartość trafia na górę

### 4. Inne

#### `std::wstring`

* Widestring
* Zajmuje 2 razy więcej miejsca od `std::string` - 16 bajtów

#### `std::vallaray`

* Specjalna tablica do której wrzuca się liczby, na której od razu wykonywane są jakieś działania

#### `std::tuple`

* Krotka
* Kontener na struktury, przechowuje typy.
* `std::tuple<int, std::string, double> t` i wtedy `t = {1, "hello", 2.25};
* Dostep do wartości przez `t[0]`, t[1]`
* `std::pair` to szczególny przypadek `std::tuple`

#### `std::bitset`

* Pole bitowe
* Alokowany na stosie
