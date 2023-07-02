---
layout: post
title: Kompilator i kompilacja
categories: [post]
date: 2022-01-09
permalink: /kompilator-i-kompilacja
---
# Kompilator i kompilacja

## Etapy kompilacji

1. Pre-processing
2. Kompilacja
   2.1 Diagnostyka
   2.2 Optymalizacja
   2.3 Wygenerowanie kodu Assembler'a
   2.4 Przetworzenie kodu Assembler'a na kod maszynowy
3. Linkowanie

### Pre-processing

* Rozwiązywanie wszystkich dyrektyw zaczynających się od `#`
* W miejsce include wstawiana treść podanej biblioteki
* Wynik - obrobiony plik źródłowy `*.cpp`
* Flaga `-E` kończy kompilację na typ etapie

### Kompilacja

* Właściwa kompilacja
  * Diagnostyka: sprawdzenie kodu pod kątem poprawności składniowej oraz semantycznej (czy kod ma sens)
  * Optymalizacja: przekształcenia kodu niezmieniające jego zachowania, a pozwalające oszczędzić na zasobach takich jak czas wykonania, zużycie pamięci czy wielkość pliku wynikowego
  * Wygenerowanie kodu Assembler'a
  * Przetworzenie kodu Assembler'a na kod maszynowy zrozumiały dla systemu operacyjnego
* Dla każdego pliku `*.cpp` powstaje plik obiektowy `*.o`
* Flaga `-c` kończy kompilację na typ etapie
  * Alternatywnie można użyć komendy `g++ main.cpp -o NAZWA.o` i samodzielnie nazwać plik obiektowy

Błąd semantyczny

```cpp
int main() {
   std::cout << 4 / 0;
   // Błąd semantyczny: dzielenie przez 0

   int a, b, c;
   a + b = c;
   // Błąd semantyczny: po lewej stronie równania znajduje się wyrażenie
}
```

### Linkowanie

* Połączenie wszystkich plików obiektowych w jeden plik wynikowy
* Wynik - gotowa binarka (`*.exe`, `*.bin`) lub biblioteka (`*.a`, `*.so`, `*.dll`)

---

## Obsluga kompilatora z linii komend

`g++ PLIK -o <PLIK>`<br>
`./<PLIK>`

* Przy kompilacji nie podaje się plików nagłówkowych
   * `g++ main.cpp entity.cpp`<br>
   * `g++ *.cpp`

### Podstawowe flagi

* `-g` - dodaje symbole do debugowania (`Valgrind` też ich potrzebuje)
* `-l` - linkuje z biblioteką
   * `g++ main.cpp -lpthread`
* `-E` - kończy kompilację na etapie pre-processingu
* `-c` - kończy kompilacje na zrobieniu plików obiektowych (nie robi linkowania)

### Flagi ustawiające poziom ostrzeżeń

* `-Wall` - wyświetli dodatkowe ostrzeżenia typu: nigdzie nieużyta zmienna, funkcja nie-void osiągnęła koniec bez zwrócenia wartości
* `-Wextra` - dodatkowe obostrzenia poza `-Wall`
* `-Werror` - traktuje ostrzeżenia jako błędy kompilacji
* `-Wpedantic` - jeszcze bardziej rygorystyczne wymagania
* `-Wconversion` - kompilator wskaże czy nie zachodzą gdzieś niejawne konwersje

### Flagi optymalizacji

* `-OO` - bez optymalizacji, szybsza kompilacja
* `-O1` - optymalizacja wielkości kodu oraz czasu wykonywania (poziom 1)
* `-O2` - optymalizacja wielkości kodu oraz czasu wykonywania (poziom 2)
* `-O3` - optymalizacja wielkości kodu oraz czasu wykonywania (poziom 3)
* `-OFast` - optymalizacja `-O3` z dodatkowymi optymalizacjami obliczeniowymi

### Flagi standardu C++

* `-std=c++17`
* `-std=c++14`
* `-std=c++17`
* `-std=c++20`
