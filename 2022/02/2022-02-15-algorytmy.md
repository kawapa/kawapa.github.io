---
layout: post
title: Algorytmy STL
categories: [post]
date: 2022-02-15
permalink: /algorytmy
nav_exclude: true
---

# Algorytmy STL
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

* Większość alogytmów przyjmuje `begin()`, `end()` i funkcję/lambdę/funktor

## Wersje algorytmów

* `*_if` - przyjmują przedykat zamiast wartości (`std::find_if`)
* `*_copy` - zapisują wynik w innym kontenerze (`std::reverse_copy`)
* `*_n` - algorytm bierze *n* elementów zamiast iteratora `last`

```cpp
// Przykład std::vector
std::vector<int> v1 {1,2,3};
std::vector<int> v2(3);   // BEZ TEGO NIE ZADZIAŁĄ
std::reverse_copy(begin(v1), end(v1), begin(v2));

for(auto i : v2) {
    std::cout << i << " ";
}

// Przykład std::string
// NIE DZIAŁA
std::string s {"abcde"};
std::string rs;
std::reverse_copy(begin(s), end(s), begin(rs));
```

* Preferowane użycie iteratorów pochodzących z globalnych funkcji `std::begin()` i `std::end()` zamiast tych które pochodzą z metod konkretnych kontenerów `v.begin()` i `v.end()`
  * Globalne funkcje działają też dla tablic z C
  * Krótszy zapis o "kropkę"

---

## Algorytmy niemodyfikujące

### `std::all_of`, `std::any_of`, `std::none_of`

* Operacje logicze na całym kontenerze
* Zwracają `true`/`false`, gdy spełniają określony predykat

### `std::count`, `std::count_if`
  
* Zliczanie wystąpień elementu w kolekcji (`std::count`)
* Zliczanie elementów w kolekcji spełniających kryteria (`std::count_if`)
* Zwraca liczbę

### `std::for_each`

* Odpowiednik zakresowej pętli `for`

### `std::for_each_n`

* Jak `std::for_each` z tą różnicą, że używa jednego iteratora oraz ilości elementów (zamiast końcowego iteratora)

### `std::mismatch`

* Szuka zakresu elementów, a nie pojedynczego elementu;
obą:
* jeśli są identyczne - iteratory przejdą do końca;
* jeśli się różnią - zwróci iter. na różniące się elementy;
 
### Przeszukiwanie

#### `std::find`

* Zwraca iterator na pierwszy element spełniający predykat

#### `std::find_if`
  
* Zwraca iterator na pierwszy napotkany element spełniający kryteria

#### `std::find_first_of`

* Przeszukuje pierwszy zakres w celu znalezienia **któregokolwiek** z elementów w drugim zakresie
* Zwraca iterator na pierwsze wystąpienie w 1 kontenerze

```cpp
std::vector<int> v1 {1,2,6};
std::vector<int> v2 {5,5,5,5,6};

auto it = std::find_first_of(begin(v1), end(v1), begin(v2), end(v2));
if (it != end(v1)) {
  // ...
}
```

#### `std::find_if_not`

* Zwraca iterator na pierwszy napotkany element, który nie spełnia podanego kryterium
		
#### `std::find_end`

* Zwraca iterator na ostatnie występienie elementu (za element można wstawić np mniejszy wektor)

#### `std::search`
  
* **Wyszukiwanie podciągów w danym ciągu**
* Przeszukuje pierwszy zakres w celu znalezienia **pierwszego wystąpienia pełnej sekwencji elementów** z drugiego zakresu
* Zwraca iterator na pierwszy element poszukiwanego podciągu w pierwszym zakresie
  * Analogicznie działa `std::find_end` ale zwraca iterator na **ostatnie wystąpienie pełnej sekwencji elementów** z drugiego zakresu

#### `std::search_n`

* Jak wyżej, ale nie szuka do końca kolekcji (podajemy przez ile elementów ma się odbyć przeszukiwanie)

#### `std::adjacent_find`

* Szuka dwóch elementów, które sąsiadują ze sobą i są identyczne
  * Można podać predykat stwierdzający co oznacza równość
* Zwraca iterator na pierwszy z nich

---

## Algorytmy modyfikujące

### Kopiowanie

#### `std::copy` / `std::copy_if`

* Skopiuje zakres do nowego zakresu lub kontenera
* Kontenery nie muszą być tego samego typu
* `std::copy_if` skopiuje elementy spełniające warunek

#### `std::copy_n`

* Jak `std::copy` ale skopiuje n wartości od begin()

#### `std::copy_backward`

* Kopiowanie w odwrotnej kolejności

### Przenoszenie

#### `std::move`

* Przenosi elementy z jednej kolekcji do drugiej

#### `std::move_backward`
 
* Przenosi elementy z jednej kolekcji do drugiej, ale w odwrotnej kolejności (od końca)

### Tworzenie nowych kontenerów

#### `std::transform` (!)

* Zazwyczaj przyjmuje zakres wejściowy (czasem nawet 2) i zakres wyjściowy
* Może być konieczność użycia odpowiedniego insertera do kontenerów (np. do vectora `std::back_inserter`)

```cpp
// Transform przyjmujące 2 kontenery wejściowe
std::vector<int> v1 {1,2,3,4};
std::vector<int> v2 {5,6,7,8};
std::vector<int> v3(4);
// W tej wersji transform v3 musi być tego samego rozmiaru (nie może być pusty)
std::transform(begin(v1),
               end(v1),
               begin(v2),
               begin(v3),
               [](int a, int b){ return a * b; }
               );

// W tej wersji v3 może być pusty
std::transform(begin(v1),
               end(v1),
               begin(v2),
               std::back_inserter(v3),
               [](int a, int b){ return a * b; }
               );
// ----------------
```

#### `std::generate` i `std::generate_n`

* Nie potrzebuje zakresu wejściowe, on generuje dane
* Przyjmuje zakres wyjściowy i funkcję/funktor/lambdę

```cpp
std::vector<int> v(4);    // TRZEBA zarezerwować miejsce
std::generate(v.begin(), v.end(), [n = 0]() mutable { return n++; });
// bez początkowego zarezerwowania miejsca trzeba użyć std::back_inserter(v)

// zmienne zdefiniowane na liście przechwytującej są zawsze typu auto
// mutable ściąga niejawnego consta ze zmiennych zdefiniowanych na liście przechwytującej

std::vector<int> v2;
std::generate_n(std::back_inserter(v2), 3, [n = 0]() mutable { return n++; });
```

### Usuwanie

#### `std::remove_copy`, `std::remove_copy_if`

* Kopiuje elementy z pominięciem elementów spełniających kryteriów
* Przykładowe użycie: usuwanie spacji ze zmiennej typu std::string

### Podmiana

#### `std::replace`, `std::replace if`

* Zamienia elementy spełniające określone kryterium

#### `std::replace_copy`, `std::replace_copy_if`

* Jak `std::replace` oraz `std::replace_if` tylko kopiują wynik do nowego kontenera

#### `std::swap`

* Podmiana dwóch kontenerów ze sobą (musi być ten sam typ)

#### `std::swap_ranges`

* Zamienia po zakresach
* Mogą być kontenery różnego rodzaju

#### `std::fill`

* Wypełnia każdy element w kontenerze podaną wartością

#### `fill_n`

* Wypełnia n elementów podaną wartością

#### `std::iter_swap`

* Zamień elementy na które pokazują dwa iteratory (mogą być różne kontenery)

### Zamiana kolejności

#### `std::reverse`

* Odwraca zawartość kontenera

#### `std::reverse_copy`

* Analogicznie jak `std::reverse` tylko wynik zapisywany jest w nowym kontenerze

#### `std::rotate`

* Obracanie/przesuwanie kontenera względem elementu na który wskazuje iterator
  * `std::rotate(begin(v), begin(v) + 3, end(v))`
* Ten (środkowy) element będzie potem pierwszy

`1 2 >3< 4 5` -> `>3< 4 5  1 2`

#### `std::shift_left` i `std::shift_right` (C++20)
  
* C++20
* Podobne do `std::rotate`, ale podajemy o ile ma przesunąć i w którą stronę
  * **Te miejsce, w których były wcześniej elementy stają puste**

#### `std::shuffle`

* Mieszanie kolejności elementów w kolekcji

### Próbkowanie (losowanie)

#### `std::sample`

* Wybierz n losowych wartości z naszego kontenera wejściowego

### Usuwanie duplikatów

#### `std::unique`

* Przechodzi przez cały kontener i jeśli napotka dwie lub więcej takich samych wartości **koło siebie** to przesuwa duplikaty na koniec
* **Żeby `std::unique` usunęło bezwzględne wszystkie duplikaty trzeba najpierw posortować kontener**
* Zwraca iterator gdzie zaczynają się duplikaty (można go potem wykorzystać w `erase(it, end(v))`) 

---

## Algorytmy partycjonujące

### `std::partition`

* Dzieli zbiór wejściowy na **2 części**
  * Wszystkie elementy dla których przekazany predykat zwraca `true` są przed elementami dla których zwraca `false`
* Kolejność elementów po partycjonowaniu **NIE jest zachowana**
* Przykład użycia: podział na elementy parzyste i nieparzyste
* Zwraca iterator na pierwszy element zbioru, który **nie spełnia predykatu** 

### `std::stable_partition`

* Partycjonuje jak `std::partition`, ale **zachowuje względną kolejność danych koło siebie**

### `std::parition_copy`

* Partycjonuje ale wyjście zachowuje elementy w dwóch osobnych kontenerach

### `std::partition_point`

* Zwraca iterator na pierwszy element zbioru, który **nie spełnia predykatu** 

### `std::is_partitioned`

* Zwraca `true` lub `false` w zależności od tego czy dany kontener jest spartycjonowany na podstawie przekazanego predykatu

---

## Algorytmy sortujące

### `std::sort`

* Podstawowa funkcja sortująca

### `std::is_sorted`

* Czy dany kontener jest posortowany

### `std::nth_element`

* Przyjmuje `begin`, *element środkowy*, `end`
* Ustawia *element środkowy* w odpowiednie miejsce tak jakby kontener był posortowany (**nie rusza pozostałych elementów**)
  * Na lewo od niego znajdować się będą elementy mniejsze
  * Na prawo od niego znajdować się będą elementy większe

### `std::partial_sort`

* Sortuje pierwsze *n* elementów
* Podajemy ilość elementów do posortowania, resztę elementów pozostawia nieposortowaną
* **Pozostałe elementy mogą mieć zmienioną kolejność!** 

### `std::is_sorted_until`

* Zwraca iterator na ostatni posortowany element

---

## Algorytmy wyszukiwania binarnego


**Algorytmy partycjonujące:**

	* .find jest gotowe w mapie lub w zbiorze;
	* binary search można użyć przy użyciu algorithm
	warunkiem jest posiadanie posortowanego kontenera

* **binary_search:**

W przypadku powtarzających się elementów możemy skorzystać z:

* **lower_bound** oraz **upper_bound**:
* 
	* zwraca odpowiednio:
		* iterator na pierwszy powtarzający się element
		* iterator na element za ostatnim powtarzającym się:
		`1 2* 2 3* 3 4` -> w przypadku liczby 2;

* **equal_range:**
* 
	* zwraca zakres elementów pasujących do podanego klucza;
	* zwraca parę lower i upper bound (first -> lower, second -> upper)
 
---

## Inne operacje na posortowanych zbiorach

* std::merge
* 
	* przyjmuje 2 zakresy i trzeci do którego dane zostaną wstawione;
	* zachowuje kolejność, będzie sortować dane
	(można podać własny komparator);

* **inplace_merge:**
* 
	* dołącza drugi zakres do pierwszego;

---

## Operacje na zbiorach

* **includes**:
* 
	* mówi nam czy jeden zbiór zawiera się w drugim
	(czy występuje część wspólna)

* **set_union:**
* 
	* suma zbiorów -> elementy z jednego i drugiego zbioru:
		* w wyniku działania set_union usunięte zostaną duplikaty;
		* 
* **set_intersection:**
* 
	* zwraca część wspólną zbiorów;
	* 
* **set_difference:**
* 
	* zwraca różnicę pomiędzy zbiorami;
	* kolejność argumentów ma znaczenie;
	* 
* **set_symetric_difference:**

	* suma wszystkiego co nie jest częścią wspólną
	(wyklucza część wspólną);
---

## Operacje na kopcach (heap)

* **push_heap:**

	* dodawanie do kopca;
  
* **pop_heap:**

	* ściąganie z kopca;
  
* **make_heap:**

	* sortowanie, aby elementy odpowiadały strukturze kopca;
  
* **sort_heap:**

	* sortowanie kontenera;
  
* **is_heap:** 

	* czy mamy strukturę kopca w kontenerze;

* **is_heap_until:**

* do kiedy kontener spełnia strukturę kopca;

---

## Operacje znajdujące minimum/maximum

* **min:**

	* zwraca najmniejszą **wartość**

* **max:** 

	* zwraca największą **wartość**
  
* **minmax:**

	* zwraca parę min i max (**wartość**)
  
* **min_element:**

	* zwraca iterator na najmniejszy element

* **max_element:**

	* zwraca iterator na największy element
  
* **minmax_element:**

	* zwraca parę iteratorów na min oraz na max
  
* **clamp:**

* spłaszczenie wartości do podanych granic:
* podajemy wartość min i max (np 3 i 5)
* wszystko mniejsze od 3 -> będzie 3 
* wszystko powyżej 5 -> będzie 5
* wartości pośrednie nie ulegną zmianie

---

## Operacje porównujące

* **lexicographical_compare:**

	* zwraca true jeśli pierwsza permutacja będzie mniejsza od drugiej
	* przykład kolejnych permutacji:  abc, acb, bac, bca, cab, cba

 * **equal:**
  
 	* zwraca wartość logiczną czy dwa zbiory są sobie równe
 	* czy elementy są takie same (np w deque i vectorze)
 	* 
 * **compare_3way:** *(C++20)*
  
* dziś mamy 6 operatorów logicznych:  <, <=, >, >=, ==, !=
* dojdzie 7-my operator 3 way: **<=>** (space ship operator :Ð)
zwróci jedną z 3 wartości:
	* mniejszy od 0 jeśli pierwszy element jest mniejszy
	* 0 jeśli są takie same
	* większy od 0 jeśli drugi element jest mniejszy
 * wykorzystać będzie można **std::compare_3way** lub **operator <=>**

---

## Permutacje

### `std::next_permutation`

* Modyfikuje kontener
* Zwraca `true`/`false` w zależności czy udało się wygenerować kolejną permutację
* Przyjmuje kontener (np. `std::string` lub kontener z liczbami)
* Chcąc sprawdzić wszystkie permutacje należy najpierw posortować kontener

```cpp
std::list<int> list {3, 4, 2}
list.sort();

do {
	/*	*/
} while (std::next_permutation(begin(list), end(list)));
```

### `std::prev_permutation`

* Zwraca poprzednią permutację

---

## Operacje numeryczne

### `std::iota`

* Algorytm generujący ciąg rosnący o 1

```cpp
std::vector<int> v(10);		// reserve nie zadziała
std::iota(begin(v), end(v), 0);
```

### `std::accumulate`

* Sumowanie elementów z kontenera
* Może przyjmować binary operator, który powie, że na przykłąd zamiast sumować elementy powinien je mnożyć (pierwszy argument to wartość początkowa (init))
* sprawdź również **std::reduce**

### `std::inner_product`

* iloczyn skalarny:
`std::vector<int> a{0, 1, 2, 3};`
`std::vector<int> b{5, 4, 2, 3};`
	*output:*  `0*5 + 1*4 + 2*2 + 3*3`

### `std::adjacent_difference`

* różnica pomiędzy sąsiadującymi elementami:
*input*: 	`10,   8,   10,   6`
*output:* 	`10, -2, 2, -4`

### `std::partial_sum`

* Sumuje od początku do elementu na którym jesteśmy
* *input*: `10, 8, 10, 6` 
* *output*: `10, 18, 28, 34`

### `std::reduce`

* Tak jak `std::accumulate`, ale wielowątkowy (`std::execution::par`)

---

## Bibliografia

