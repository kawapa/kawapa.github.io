---
layout: post
title: Mateusz Adamski - Kurs algorytmów
permalink: /kurs-algorytmow
date: 2024-04-01
draft: true
---

# Złożoność obliczeniowa 1

## Złożoność obliczeniowa - notacja dużego O

* Metoda określania złożoności danego algorytmu, nazywana oszacowaniem z góry (złożoność nie będzie nigdy gorsza niż jakaś funkcja)
  * Stałe i mniejsze rzędy wielkości pomijamy
* Mierzy się ją w stosunkiem liczby potrzebnych operacji (lub wymaganej pamięci) do wielkości zbioru wejściowego
* Rozróżniamy żlożoność obliczeniową i pamięciową
  * Czasem, kiedy zależy nam na szybkości, nie dbamy o pamięć. Przykład: złożoność obliczeniowa sortowania przez scalanie to *O(log(n))*, a pamięciowa to *O(n)*

## Szacowanie złożoności obliczeniowej danego algorytmu

1 Ilość pętli
  * 1 to najczęściej zlożoność liniowa (chyba że występuje rekurencja)
  * pętla w pętli - n^2
  * pętla w pętli w pętli - n^3
  * Petle for wystepujace po sobie to dalej zlozonosc liniowa
    * 
```
for {

}
for {

}
for {

}
// zlozonosc n + n +n  = 3n - ale przy okreslaniu zlozonosci odrzucamy wszystkie stale (bo one drastycznie nie zmieniaja  
// zlozonosci przy wiekszej ilosci danych)

ale

// zlozonosc stala bo niezaleznie od ilosci danych petla wykoona sie 10 razy
void foo() {
  for (int i = 0; i < 10; ++i)
  {

  }
}
```

2 Jak długo pętla się wykonuje
  * jesli w petli jest wywolanie rekurencyjne (samej siebie)
  * wewnatrz kodu jest wywolanie funkcji w ktorej sa petle
  * jakie dane (przypadek najlepszy, nagorszy i sredni)
    * jesli przed petla sprawdzany jest warunek to moze sie okazac ze nie wchodzimy do petli i mamy zlozonosc O(1)
3 Czy wystepuja wywoalani reekurencyjne (latwo zauwazyc), uzycie stosu lub kolejki
  * Stos jest często wykorzystywany do symulacji wywołań rekurencyjych (std::stack)
  * Kolejka jest zazwyczaj liniowa, w przypadku grafów może coś być


---
OFF
  (* Są 2 typy wywołań rekurencyjnych: rozgałęziające i nierozglałęziające)

// nierozglaeziajaca
void foo();
{
   foo()
}

// rozglaleziaace
void foo()
{
  foo();
  foo();
}
-----

4. Ile dana funkcja wykonuje wywołań rekurencyjnych

* Obliczanie n-tej liczby ciagu Fibbonacciego w sposob rekurencyjny to najgorsze mozliwe rozwiazanie
  * Lepiej: zapisywac posrednie winiki w wektorze (jesli chcemy miec wszystkie) lub 2 zmienne tymczasowe (jesli zalezy nam tylko na tej jednej konkretnej)
  * Najlepiej: Obecnie na n-ty liczbe ciagu fib jest wzor

## Szacowanie złożoności pamięciowej

1. Czy algorytm kopiuje dane wejściowe
  * jesli tak to zlozonosc liniowa (jak vector<vector> to kwadratowa)
2. Jakie struktury pomocnicze są tworzone, czy odpowiadają one rozmiarowi kolekcji, a może są od niej większe
  * W grafach często potrzebne sa tablice odwiedzin, 
3. Czy pętle, lub rekurencje tworzą dodatkowe zmienne tymczasowe i jakie są ich rozmiary
  * Samo zastosowanie rekurencji wskazuje na zlozonosc liniowa bo wkaźniki na funkcje powrotu 

W DALSZEJ CZĘŚCI mówiąć zlożoność będziemy mieli na myśli złożoność obliczeniową (chyba że określono inaczej)

### Złożoność stała

* Ilość operacji zależy od wielkości danych wielkości
* Przykład: suma ciągu artymetycznego
  * Nie trzeba iterować po zbiorze, żeby coś obliczyć, bo istnieje np. wzór matematyczny, który to liczy

Usuwanie elementu z wektora
* Jesli nie zalezy nam na kolejnosci elementów - mozna zamienic miejscami element do usuniecia z ostatnim i wywolac v.pop() - zlozonosc O(1)
  * jesli wykonamy zwykle usuwanie (remove-erase) to przesuwamy wszystkie leementy przed ten do usuniecia i usuwamy ostatni


Kompilator konwertuje niejawnie funkcję constexpr na inline, dlatego warty aby definiować je w pliku nagłówkowym, gdyż możemy otrzymać infomacje o undefined reference.

### Złożoność logarytmiczna

O(logn)

* Występuje przy zastosowaniu techniki Divide and conquer czyli dziel i rządź (odrzucanie w każdym kroku (mniej więcej) połowy zbioru - przykład: przeszukiwanie binarne)
  * mapy i sety to drzewa binarne (czerwono - czarne), wezel zawiera klucz albo klucz i wartosc
* Logarytm o podstawie 2
* binary_sarch odrzuca polowej tablicy dlatego O(logn) ale ternary_search odrzuca 2/3 tablicy O(log3(n)) - jesli podstawa logytnu to 2 to jej nie zapisujemy

int ternamy_search(int l, int r, int) {
  if (r >= 1) {
    int mid1 = l + (r-l) / 3;
    int mid2 = r - (r-l) / 3;

    if (ar[mid])
  }
}


  ## Złożonośc pierwiastkowa 

  * Bardzo żądko występująca, np. wyznaczanie liczb pierwszycch ()
  Sprawdzanie liczby pierwszej
  - dzielimy na 2 i sprawdzamy od jakiejs wartosci az do polowy do tej co poszukujemy (a w zasadzie do pierwiastka)

  albo przy przeszukiwaniu ...

  * pierwiastkowa jest duzo wolniejsza od logarytmicznej

  ## Złożoność liniowa

  * Najpopularniejsza wśród algorytmóœ STL
  * Jeśli algorytm w najgorszym przypadku musi przez przez wszystkie elementy
  * Najłatwiej odkryć po pętli for iterującą po całym zakresie
  * Samo skopiowanie kontenera to złozoność obliczeniowa n

  ## Złożoność O(n*log(n))

* Wszystkie algorytmy związane mapy 
* Występuje gdy mamy do czynienia z odrzucaniem, na przykład połowy wartości, lecz musimy to wykonać n razy

  Przykład: dodanie n elementów do struktury drzewiastej (mapy lub setu): każda operacja zajmuje O(logn) ale musimy to wykonać n razy, stąd O(n*log(n))


  * Sortowanie przez scalanie (dzielenie tablicy na 2 do momentu aż zostanie jeden element -> wtedy rozpoczynamy scalanie)
  * QUicksort - log(n) razy partycjonujemy (które zajmuje O(n))
  * Sortowanie przez kopiec (umieszczanie elementów na kolejce priorytetowej (która jest strukturą drzewiasto-podobną))


  for (int i = ; x < max; ++x) {
    // O(n)
    for (int y = 0; y < x; y /= 2)
    {
      // log(n)
    }
  }

  ## Złożoność kwadratowa O(n^2)

  * Popularna
  * Operacje na macierzach (wszystkie operacje maja zlozonosc obliczeniowa O(n^2))
  * Alokowanie maicerzy kwadratowej to też O(n^2)
* Metody brute-force

  * Grafy można przekonwertować do tablicy (kosztem pamięci), ale można dzieki temu można szybsze algorytmy zastosować


  ## Złożoność O(n^3)

  * 3 petle lub tablice trójwymiarowe (silniki graficzne 3d) lub niektóre problemy związane z grafami
    * Algorytm Floyda-Warshall'a - wyznaczanie najkrótszych ścieżek w grafie ważonym dla wszystkich węzłów (konwertujemy graf do tablicy) - O(n^3)

    * Alokacja trójwymiarowej tablicy to też O(n^3)

    # Złożoność wykładnicza O(2^n)

    * Odwrotność log(n)
    * Problem wieży Hanoi
    * Każda funkcja wywołuje sma siebie dwa razy dekrementując tm licznik o jeden
    * Niektóre problemy zwiżane z grafami
    * Obliczanie n-tego wyrazu ciągu Fib metoda rekurencyjna ma zlozonosc O(2^n) choć można to wykonać nawet w czasie O(1)


    Algorytmy zachłanne rozwiązują problemy o złożoności wykładniczej w sposób przybliżony.
    (problem wydawania reszty)


    ## Złożoność O(n!)

    * Sprawdzenie wszystkich permutacji (problem Chińskiego listonosza, Komiwojażera)

    ## Złożoność O(n*n!)

    * Bogosort, sprawdzamy wszystkie permutacje wektora i sprawdzamy za każdym razem czy jest kontener posortowany


    void BogoSort(const std::vector& v) {
      while (!std::is_sorted(v.begin(), v.end()) {
        std::shuffle(v.begin(), v.end(), egenerator);
      }
    }

# Zlozonosc obliczeniowa 2

# Różne
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

## Sortowanie




## Złożoność obliczeniowa

### Definicja

* Służy do szacowania czasu wykonania algorytmu
* Mierzy się ją w stosunkiem liczby potrzebnych operacji do wielkości zbioru wejściowego

### Notacja dużego O

* Oszacowaniem z góry (nie będzie nigdy gorzej niż jakaś funkcja)
  * Stałe i mniejsze rzędy wielkości pomijamy

### Złożoność stała

* Nie zależy od wielkości danych wielkości
* Przykład: suma ciągu artymetycznego
  * Nie trzeba iterować po zbiorze, żeby coś obliczyć, bo istnieje np. wzór matematyczny, który to liczy

### Złożoność logarytmiczna

* 


# Rekurencja

# Rekurencja

* Jedna z podstawowych technik do rozwiązywania dużej części problemów
* Derekursywacja algorytmów, na przykład przy użyciu stosuz
* Rozbicie problemu na mniejsze podproblemy i skłamy wyniki w większe rozwiązanie

Przykład zadania: wypisanie wszystkich permutacji dla liczb 1234

12 | 34
   | 43

13 | 24
   | 42

14 | 23
   | 32

21 | 34
   | 43

23 | 14
   | 41

24 | 31
   | 13

* Najpopularniejsza funkcja rekurencjyna: silnia


* Rekurencja składa się z dwóch elementów:
    * Warunek brzegowy (czasem określany jako końćowy) (najmniejszy podproblem dla którego znane jest rozwiązanie) kończący rekurencję
    * Wywołanie rekurencyjne (tej samej funkcji z innymi arguemntami)

    int factorial(int num) {
        if (num < 2) {
            return 1;
        }

        return factorial(num -1) * 1; 
     }

* Rozwiązywanie problemu w sposób rekurencyjny polega na zredukowaniu problemu do warunku początkowego, a następnie powrót wywołań rekurencyjnych "ku górze" (korzystamy ze stosu)

## Zagrożenia

1. Pomyłka w impementacji polegająća na tym, że wywołanie (albo więcej niż jedno) nigdy nie osiągnie warunku przegowego -  przepełnienie stosu
2. Również przepełnienie stosu, ale z powodu rozmiaru problemu - program utworzy np. miliony wywołań rekurencyjnych, ale nim dotrzemy do warunku brzegowego nastąpi przepełnienie stosu

W rekurencjyne oblicznaie ciągu Fibbonacciego wielokrotnie obliczamy te same warotsci, w przypadku dużych liczb jest to bardzo kosztowne.
Rozwiązanie: programowanie dynamiczne polegające na przechowywaniu już obliczonych wyników tymczasowej tablicy (gdy potrzebny będzie jakiś wynik, w pierwszej kolejnosci zagladamy do tablicy)

Flagi O2 i O3 spowoduje 
Kompilator wykrywa rekurencje przy optymalizacji O2 lub O3 (wykrywa proste wywoływania rekurencjyna i zamieni na iteracyjne )

## Derekursywacja - Notacja RPN

* Jak zmienić rozwiązanie rekurencjyjne w rozwizanie iteracyjne

## Przykład: Kalkulator dla odwrotnej notacji Polskiej (ONP - > ang. RPN (Reversed Polish Notation))

* Odwrotna notacja polska (ONP, ang. reverse Polish notation, RPN) – sposób zapisu wyrażeń arytmetycznych, w którym znak wykonywanej operacji umieszczony jest po operandach (zapis postfiksowy), a nie:
    *  pomiędzy nimi jak w konwencjonalnym zapisie algebraicznym (zapis infiksowy) lub
    *  przed operandami jak w zwykłej notacji polskiej (zapis prefiksowy)
* Użycie ONP ten pozwala na całkowitą rezygnację z użycia nawiasów w wyrażeniach, jako że jednoznacznie określa kolejność wykonywanych działań.


Zapis zwykły: (((((8 + 7)/3) * 2) + 4) * 2)
Zapis w ONP: 8 7 + 3 / 2 * 4 + 2 *


* Jak rozwiązać dany problem bez rekurencji? Wystarczy użyć stosu. Każdorwazowo będziemy odkładać na stos kolejne wartości
    * Jeśli okaże się , że mamy do czynienia z operandem, pobierzemym dwie górne wartości ze stosu i wykonay na nich operację i wynik umieścimy z powrotem na stosie

Ponieważ stos działa na zasadzie żę ostatnia dodana wartość jest ściagana jako pierwsza, będziemy wykonywac kolejne operacje z naszej notacji w kolejnosci odwortnej (jest to istotne dla dzielenia które nie jest przemieną operacją)

## Przykład: Wieża Hanoi

Przesunięcie krążków z pierwszego słupka na trzeci
* Nie można położyć krążka o większej średnicy na krążku o mniejszej średnicy
* Można pobrać maksymalnie jeden krążek

Rozwiązanie za pomocą dwóch wywołań rekurencyjnych

* Sprowadzenie do przypadku brzegowego, czyli w tym przypadku sytuacja kiedy mamy 3 krążki i robimy to:

Rozwiązanie iteracyjne


Przejście po drzewie metodą in-order i umożliwia wypisanie drzewa w sposób posortowany.
Wypisywanie drzew: przejscie do najbardziej skrajnego lewego dziecka, potem wezel rodzica, i wezel prawy.

Ogolnie sa przejscia: pre-order, post-order, inverse-order.


Zad. Rekurecnyjny rysunek
Zad. Rozpis