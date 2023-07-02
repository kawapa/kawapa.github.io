---
layout: post
title: Funkcje, funktory i lambdy
categories: [post]
date: 2022-02-05
permalink: /funkcje
---

# Funkcje, funktory i lambdy
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

## Wskaźniki na funkcje

* Nazwa funkcji bez wywołania (operatora `()`) to wskaźnik na tę funkcję
* Wykorzystanie: można przekazać do funkcji inną funkcję jako argument i wywołać wewnątrz
* Rzadko się stosuje bo jest `std::function`
* Zastosowanie
  * Mechanizm *callback* czyli np. można ustawić co ma się stać kiedy funkcja zakończy swoją pracę. Można zmienić zachowanie danej funkcji bez zmiany implementacji (przekazujemy jej w postaci argumentu inną funkcję)
  * Algorytmy STL

```cpp
// można zmienić zachowanie funkcji foo()
// bez zmiany jej implementacji
void foo(int (*bar)(int)) {
  // ...
  bar();
}

// ----------------------------- //

void print(int i) {
  std::cout << i << " ";
}

// ...

std::vector<int> v {1, 2, 3};
std::for_each(begin(v), end(v), print);
```

| Typ wskaźnika | Sygnatura funkcji |
|:-------------|:------------------|
| `void (*foo)()` | `void foo()` |
| `int (*bar)(int)` | `int bar(int)` |
| `int (*bar2)(double, uint)` | `int bar2(double, uint)` |

---

## Obiekt funkcyjny (funktor)

* Klasa lub struktura, która ma zdefiniowany `operator()` - można ją wywołąć jako zwykłą funkcję
* Zastosowanie
  * Przekazywanie do algorytmów STL (wtedy funktor przyjmuje pojedynczy element z zakresu na którym pracuje)

```cpp
class Foo {
public:
  void operator() {
    // ...
  }
};

// ...

Foo foo;
foo();

Foo bar{}();
```

### Różnica między funkcją a funktorem

Funktor to obiekt klasy, więc może on przechowywać jakieś pola. Może to być istotne jeśli chcemy coś zmieniać między kolejnymi wywołaniami funktora.

## Lambdy

* Lambda to obiekt funkcyjny (*funktor*), tworzona najczęściej w miejscu użycia
* Zapisanie lambdy możliwe jest tylko do typu `auto`
  * Typ lambdy to **domknięcie** (*closure*) i jest znany tylko kompilatorowi
* 3 elementy lambdy: lista przechwytująca, lista argumentów, typ zwracany (opcjonalne) i ciało funkcji

`[coPrzechwytujemy](parametry) specyfikatory [[ atrybuty ]] -> typZwracany { treść }`

* `()` opcjonalne

### Lista przechwytująca

* `[]` czyli lista przechwytująca (*capture list*)
* Umożliwia przechycenie zmiennych z lokalnego zakresu  
  * Ciało lambdy to osobny zakres 
* Można definiować nowe zmienne, ale nie podajemy typu (jest `auto`). Przykład: `[value = 1] { }`
  * Nowe zmienne zdefiniowane na liście przechwytującej są zachowane między wywołaniami
* Można przechwytywać przez referencję `[&value]`, kopię (`[value]`), mieszać kopie z referencjami lub przechwycić "wszystko" przez kopię lub referencję (`[=]` lub `[&]`)
* Lambda, jeśli nie przechwytuje niczego jest konwertowalna na wskaźnik na funkcję
  * Jeśli jednak coś przechwytuje, nie jest to możliwe. Rozwiązanie: `std::function`

| Lista przychwytująca | Przechwytujemy |
|:-------------|:------------------|
| `[]` | Nic |
| `[a]` | a przez kopię |
| `[&a]`  | a przez referencję |
| `[a, &b]` | a przez kopię, b przez referencję |
| `[=]` | Wszystko przez kopię |
| `[&]` | Wszystko przez referencję |
| `[&, a]` | a przez kopię, wszystko pozostałe przez referencję |
| `[=, &a]` | a przez referencję, wszystko pozostałe przez kopię |
| `[this]` | Wskaźnik `this` przez referencję (lambda może zmodyfikować obiekt klasy) |
| `[*this]` | (C++17) Wskaźnik `this` przez kopię (tworzona jest kopia obiektu) |

* Pisząc `[=]` lub `[&]` oznacza również przechwycenie `this` (**w obu przypadkach przez referencję!**)

#### Lambda Capture Initializers (C++14)

* W C++11 lambdy umożliwiają przechwycenie obiektów tylko przez kopię i referencję
  * Nie można przechwycić obiektów, które można tylko przenosić (`std::unique_ptr`)
* C++14 dopuszcza przenoszenie

```cpp
std::unique_ptr<int> ptr(new int(10));
auto function = [value = std::move(ptr)] { return *value; };
```

#### `std::function`

* `std::function<TYPY_ARGUMENTÓW>(TYPY PARAMETRÓW)`
* `std::function` posiada operator wywołania (`operator()`), które przekazuje wywołanie do wewnętrznego obiektu
  * Jeśli `std::function` jest puste, ale wywołamy `operator()` -> poleci wyjątek `std::bad_function_call`

### Lista argumentów

* **Opcjonalne, ale nie można ich pominąć jeśli:**
  * Podajemy typ zwracany lambdy (`->`)
  * Używamy specyfikatorów
  * Używamy atrybutów

#### Po co aż 2 sposoby na przekazanie obiektów?

* Lambda może zostać utworzona w jednym zakresie, a wywołana w innym
* Zmienne z lokalnego zakresu są przechwytywane przez listę przechwytującą podczas tworzenia
* Parametry się podaje podczas wywołania

### Specyfikatory

* **Opcjonalne**
* `noexcept` - gwarantuje, że nie rzuca wyjątków (jeśli wystąpi wyjątek -> `std::terminate`)
* `constexpr` - lambda może zostać wywołana w czasie kompilacji i podczas kompilacji program użyje wartości już obliczonej (**niejawnie dodawany od C++17** jeśli lambda zostanie użyta w odpowiednim kontekście)
* `mutable` - Zmienne przechwycone przez wartość (kopię) lub stworzone w liście przechwytującej **nie mogą być modyfikowane wewnątrz lambdy**. Specyfikator `mutable` znosi to ograniczenie.
  * W lambdzie `operator()` jest funkcją `const` co oznacza, że nie może edytować swoich pól składowych
* `consteval` (C++20)

### Atrybuty

* **Opcjonalne**

### Typ zwracany

* **Opcjonalne**  
* `->` czyli typ zwracany
* Można podać w celu wymuszenia konwersji
* Typ zwracany może być czasem potrzebny w przypadku szablonów

### Ciało funkcji

* `{ }` czyli ciało funkcji

## Wiszące referencje

* *Dangling references*
* Lambda jest tworzona jest w miejscu, w którym jest zdefiniowana - na stosie
* Jeśli przechwycimy zmienne przez referencję, a lambda zostanie wywołana później, w innym miejscu, niektóre zmienne lokalne mogą nie być już dostępne. Jest to niezdefiniowane zachowanie

## Generyczne lambdy

* Pod spodem tworzą się funkcje szablonowe

```cpp
auto lambda = [](auto x, auto y){ return x + y; }

struct UnnamedClosureClass {
    template <typename T1, typename T2>
    auto operator()(T1 x, T2 y) const {
        return x + y;
    }
};

auto lambda = UnnamedClosureClass{};
```
