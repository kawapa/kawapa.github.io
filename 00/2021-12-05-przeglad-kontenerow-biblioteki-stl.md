---
layout: post
title: Przegląd kontenerów biblioteki STL
date: 2021-11-28 17:00:00
permalink: /XXX
search_exclude: true
---





Kontenerów STL i złożoności obliczeniowej ich operacji




- [Kontenery](#kontenery)
  - [1. Kontenery sekwencyjne](#1-kontenery-sekwencyjne)
    - [`std::array`](#stdarray)
    - [`std::vector`](#stdvector)
    - [`std::deque`](#stddeque)
    - [`std::list`](#stdlist)
    - [`std::forward_list`](#stdforward_list)
  - [2. Kontenery asocjacyjne](#2-kontenery-asocjacyjne)
    - [`std::set` / `std::multiset`](#stdset--stdmultiset)
    - [`std::map` / `std::multimap`](#stdmap--stdmultimap)
    - [`std::unordered_map` / `std::unordered_multimap` / `std::unordered_set` / `std::unordered_multiset`](#stdunordered_map--stdunordered_multimap--stdunordered_set--stdunordered_multiset)
  - [3. Adaptery](#3-adaptery)
    - [`std::stack`](#stdstack)
    - [`std::queue`](#stdqueue)
    - [`std::priority_queue`](#stdpriority_queue)
  - [4. Inne](#4-inne)
    - [`std::wstring`](#stdwstring)
    - [`std::vallaray`](#stdvallaray)
    - [`std::tuple`](#stdtuple)
    - [`std::bitset`](#stdbitset)
- [Bibliografia](#bibliografia)


## Kontenery

* Kontenery przechowują dane określonego typu i same zarządza pamięcią tzn. w momencie jeśli np. wektor przestaje istnieć to on sam usuwa je z pamięci
* Powinno się preferować metody/algorytmy dedykowane konkretnemu kontenerowi nad metody globalne
	* Są one lepiej zoptymalizowane i przez to często szybsze
* `std::begin(vec)` i `std::end(vec)` jest bardziej uniwersalne bo działa też dla zwykłych tablic C
* Nie należy dziedzczyć po kontenerach z biblioteki STL bo nie mają one wirtualnych destruktorów
	* Lepiej zastosować mechanizm agregacji
	* Jeśli nasza klasa coś dodatkowo sobie trzyma to nasz wektor tego nie zwolni i beda wycieki pamieci

### 1. Kontenery sekwencyjne

#### `std::array`

* **Cache-friendly**
* Alokowany na stosie
* Dostęp do n-tego elementu - O(1)
	* Elementy leżą kolejno w pamięci
* Żeby funkcja mogła przyjmować jako argument `std::array` trzeba zrobić z niej funkcję szablonową:

```cpp
template <size_t T>
void print(const std::array<int, T>& a) {
    std::for_each(begin(a), end(a), [&a](int number){ std::cout << number << "\n"; });
}
```

#### `std::vector`

* **Chache-friendly**
* Alokowany dynamicznie na stercie
* Dostęp do n-tego elementu - O(1)
	* Elementy leżą kolejno w pamięci
* Wstawianie na koniec - w zamortyzowanym czasem stałym (O(1))
	* Bo możliwe, że dojdziemy do limitu capacity i będzie trzeba go przenieść gdzieś indziej
* Zjawisko inwalidacji iteratorów

#### `std::deque`

* Double-ended queue (dek)
* Podobny do wektora
* Wstawianie na początek i na koniec w zamortyzowanym czasie stałym (O(1))
* Dostęp do n-tego - O(1)
* Alokowany w NIECIĄGŁYM kawałku pamięci
* W momencie jak kończy się pamięć, rezerowany jest nowa pamięć i jest gdzieś w pamięci tablica wskaźników która przechowuje adresy tych wszystkich "kawałków" (stanowi to dodatkowy narzut)
* Przykład zastosowania: kolejka FIFO

#### `std::list`

* Każda lista ma:
	* Element HEAD, który wskazuje na 1-szy element listy
	* Element TAIL, który wskazuje na ostatni element listy
* Każdy element listy zawiera: dane, wskaźnik na poprzedni oraz wskaźnik na następny
* Dostęp do n-tego - O(n)
* Zalety: czas wstawiania i usuwania (O(1)), iteratory nie są inwalidowane
* Jako jedyny kontener ma swoją funkcję sortującą, wszystkie inne kontenery wymagają użycia algorytmu `std::sort`

**Kiedy `std::list` a kiedy `std::vector`?**

* `std::vector` ma szybki dostęp i modyfikację dowolnego elementu, ale powolne jest usuwanie (po usunięciu trzeba przesunąć wszystkie)
* `std::vector` po przekroczeniu capacity musi zaalokować nowe miejsce w pamięci i przenieść dane
* `std::list` ma wolniejszy dostęp (bo trzeba przeskoczyć X elementów), ale dodawanie i usuwanie nawet dużych ilości elementów jest szybkie

#### `std::forward_list`

* Elementy nie mają wskaźnika poprzedni
* Lista nie ma elementu TAIL
* Dostęp do n-ntego - O(n)
* Wstawianie i usuwanie O(1)

### 2. Kontenery asocjacyjne

Asocjacyjne (kolejność nie jest taka jak kolejność dodawania, służą do szybkiego wyszukiwania danych).

#### `std::set` / `std::multiset`

* Set przechowuje tylko unikalne wartości
* W multiset możliwe wystąpienie tej samej wartości
* Elementy sortowane podczas wstawiania
* Wszystkie elementy są const
* Wyszukiwanie i wstawianie O(logn)
* Dzięki temu że uporządkowany, stosuje się wyszukiwanie binarne

#### `std::map` / `std::multimap`

* Map przechowuje tylko unikalne wartości
* W multimap możliwe wystąpienie tej samej wartości
* Elementy sortowane podczas wstawiania
* Wszystkie elementy są const, można go tylko nadpisać
* Wyszukiwanie i wstawianie O(logn)
* Dzięki temu że uporządkowany, stosuje się wyszukiwanie binarne
* Odwołanie się przez operator [] do klucza (indeksu) który istnieje spowoduje nadpisanie klucza
* Dodanie klucza który istnieje korzystając z insert nic nie zrobi

#### `std::unordered_map` / `std::unordered_multimap` / `std::unordered_set` / `std::unordered_multiset`

* Kontenery nieuporządkowane (hash-mapy)
* Kontener jest zorganizowany w kubełki (buckets)
* Przy wyszukiwaniu lub wstawianiu uruchamiana jest funkcja hash
* Jest funkcja hash która zwraca numer kubełka w którym trzeba szukać danej wartości
	* Funkcja hash to naprzykład reszta z dzielenie. W przypadku %4 mamy 4 kubełki: 0, 1, 2, 3
* Biblioteka standardowa dostarcza funkcje hashujące dla podstawowych typów danych: int, std::string itd. Do typów własnych trzeba taką funkcję napisać samemu.
* W przypadku jeśli zbyt dużo wartości ląduje w jednym kubełku (`load_factor()` jest duży) trzeba wykonać `rehash()` po którym nastąpi nowy podział, np. na więcej kubełków (można ustawić `max_load_factor()` po którym następuje `rehash()`)

### 3. Adaptery

Domyślnie wszystkie adaptery używają kontenera deque.

#### `std::stack`

* Stos (LIFO)
* Operacje: `push()`, `pop()`, `top()`

#### `std::queue`

* kolejka (FIFO))
* Operacje: `pop()`, `push()`, `back()`, `front()`

#### `std::priority_queue`

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



## Bibliografia

* http://home.agh.edu.pl/~glowacki/docs/matwykl/O-o/_ProgObiekt-C++14-Rozsz.pdf
