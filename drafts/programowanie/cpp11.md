---
layout: post
title: "Standard C++11"
permalink: /cpp11
---

# Standard C++11
{: .no_toc }

---

atomic operations library
emplace() and other use of rvalue references throughout all parts of the existing library
std::unique_ptr
std::move_iterator
std::initializer_list
stateful and scoped allocators
std::forward_list
chrono library
ratio library
new algorithms:
std::all_of, std::any_of, std::none_of,
std::find_if_not,
std::copy_if, std::copy_n,
std::move, std::move_backward,
std::random_shuffle, std::shuffle,
std::is_partitioned, std::partition_copy, std::partition_point,
std::is_sorted, std::is_sorted_until,
std::is_heap, std::is_heap_until,
std::minmax, std::minmax_element,
std::is_permutation,
std::iota,
std::uninitialized_copy_n
Unicode conversion facets
thread library
std::function
std::exception_ptr
std::error_code and std::error_condition
iterator improvements:
std::begin
std::end
std::next
std::prev
Unicode conversion functions

## std::function

Typ pozwalający przechowywać wynik bindowania, lambdę, funkcję itp.

```cpp
function<float(int x, int y)> foo;

struct int_div {					// take something you can call using ()
	float operator()(int x, int y) const {
		return ((float)x) / y;
	};
};

foo = int_div();					// przypisanie
std::cout << f(5, 3) << endl;		// przykładowe użycie
std::accumulate(b, e, 1, foo);		// zastosowanie z algorytmem
```

`std::function` można stosować z metodami:

```cpp
struct X {
	int foo(int);
};

function<int(X*, int)> f;
f = &X::foo;				// wskaźnik na metodę

X x;
int v = f(&x, 5);			// wywołanie foo() na obiekcie x z argumentem 5

function<int(int)> ff = std::bind(f, &x, _1);	// pierwszy argument dla f to &x
v = ff(5);
```

---


`std::bind`

Wrapper na funkcje, XXX który pozwala ją wywoływać bez konieczności podawania wszystkich argumentów (podaje się je wcześniej podczas bind'owania):

```cpp
int foo(int, char, double);
auto bar = bind(bar, _1, 'c', 1.2);

int x = bar(7);		// oznacza wywołanie foo(7, 'c', 1.2)
```

* `_1` to placeholder na pierwszy argument przy wywołaniu funkcji `ff`
* Analogicznie `_2` lub `_3`, na przykład:

```cpp
int foo(int, char, double);
auto bar = bind(foo, _3, _2, _1);	// wolona kolejność

int x = bar(1.2, 'c', 7);			// oznacza wywołanie foo(7, 'c', 1.2);
```

Nie można bind'ować funkcji przeciążonych, kompilator nie będzie wiedział, którą wywołać:

```cpp
int foo(int);
double foo(double);							// foo() jest przeciążona

auto g1 = bind(g, _1);						// ERROR, nie wiadomo które foo()
auto g2 = bind((double(*)(double))g, _1);	// OK, ale wygląda paskudnie
```



## Bibliografia

- [Repozytorium AnthonyCalandra na GitHub](https://github.com/AnthonyCalandra/modern-cpp-features)
- [Wykład "Programowanie Obiektowo Zorientowane w języku C++11 - Rozszerzenia w rdzeniu języka" z AGH w Krakowie](http://home.agh.edu.pl/~glowacki/docs/matwykl/O-o/_ProgObiekt-C++11-ZmianyWBibliot.pdf)


































# C++11 - nowe elementy języka
{: .no_toc }

Standard C++11 to trzecie wydanie standardu języka wydane we wrześniu 2011 roku. Zastępuje ono edycję C++03 z roku 2003 i stanowi początek tak zwanego nowoczesnego C++.
{: .fs-6 .fw-300 }

<details open markdown="block">
  <summary>
    Spis treści
  </summary>
  {: .text-delta }
1. TOC
{:toc}
</details>


special member functions for move semantics

converting constructors

explicit conversion functions

inline-namespaces

non-static data member initializers

right angle brackets

ref-qualified member functions

trailing return types

char32_t and char16_t

user-defined literals
raw string literals

## Semantyka przenoszenia

Osobny wpis.
## Referencje do r-wartości

Osobny wpis.
## Uniwersalne referencje (forwarding references)

Osobny wpis.

## Wyliczenia silnie typizowane


## Slowo kluczowe `auto`

* Oznacza, żeby kompilator sam wydedukował typ na podstawie wyrażenia po prawej stronie
* `auto` istniało wcześniej, ale przed C++11 oznaczało zmienna zaalokowaną na stosie
* Przydaje się żeby nie pisać długich typów, np. `std::vector<int>::iterator`
* Umożliwia wygodną iterację po kontenerach

for (const auto& object : objects) {
    // ...
}


## Mechanizm dedukcji typu

* Jeśli specyfikator przy `auto` nie jest ani referencją ani wskaźnikiem
    * Jeśli wyrażenie po prawej stronie jest referencją - referencja jest usuwana
    * Usuwanę są modyfikatory `const` i `volatile`
    * Jeśli wyrażenie po prawej stronie to tablica lub funkcja - otrzymujemy wskaźnik

int a = 42;
int& b = a;
const int& c = a;

auto a1 = x; // a1 : int
auto a2 = ref_x; // a2 : int
auto a3 = cref_x; // a3 : int

* Stawiając referencję `&` przy `auto`, wszelkie modifikatory (`const`, `volatile`) zostają zachowane (jeśli nie, są pomijane)

{% highlight cpp %}
auto p1 = 5;    // int
auto& p2 = p1;  // int&
auto p3 = {1};  // std::initializer_list<int>
auto&& p4 = 5;  // int&&
auto&& p5 = p1; // int&

auto p6 = 1, p7 = 2, p8 = 3;    // int, int, int
auto p9 = 2.5, p10 = true;      // ERROR
auto p11;                       // ERROR
{% endhighlight %}



## Słowo kluczowe `noexcept`

```cpp
void boo() noexcept;
```

* Oznacza, że dana funkcja nie rzuca wyjątków
* Kompilator może sobie pozwolić na dodatkowe optymalizacje jeśli funkcja oznaczona jest jako `noexcept`
    * Jeśli taka funkcja mimo wszystko rzuci wyjątek - zostanie zawołane `std::terminate`
* Domyślnie powinno się oznaczać `noexcept`
    * Operacje przenoszenia (konstruktor przenoszący i operator przypisania przenoszący)
    * Operacje wymiany (`swap`)
* Można sprawdzić czy dana funkcja jest noexcept

```cpp
std::cout << noexcept(boo());   // false
```



## Słowo kluczowe auto

* Kompilator sam ma wydedukować typ
* Przydaje się żeby nie pisać długich typów, np. `std::vector<int>::iterator`
* Stawiając referencję `&` przy `auto`, wszelkie modifikatory (`const`, `volatile`) zostają zachowane (jeśli nie, są pomijane)

```cpp
const vector<int> values;
auto v1 = values;           // v1 : vector<int>
auto& v2 = values;          // v2 : const vector<int>&
```

* Tablice:

```cpp
Gadget items[10];
auto g1 = items             // g1 : Gadget*
auto& g2 = items;           // g2 : Gadget(&)[10] - referencja do tamtej tablicy
```

* Przed C++11 `auto` oznaczało zmienną automatyczną tworzoną na stosie (w przeciwieństwie do `new` tworzonej na stercie)

## Aliasy using

* Dobrą praktyką jest używanie w kodzie nazw domenowych, łatwiej zrozumieć kod

```cpp
using Pair = std::pair<float, char>;

typedef std::pair<float, char> Pair;    // odpowiednik z typedef
```

* Przewagą `using` nad `typedef` jest, że `using` można użyć z szablonami

```cpp
template <typename T>
using StrKeyMap = std::map<std::string, T>

StrKeyMap<int> myMap;   // std::map<std::string, int>
```

* Ciekawostka: `typedef` nie ma zdefiniowanej kolejności podawania argumentów dlatego 2 poniższe linijki są równoważne

```cpp
std::pair<float, char> typedef Pair;

typedef std::pair<float, char> Pair;
```

---
* Nowe oznaczenie aliasu typów

{% highlight cpp %}
using Pair = std::pair<float, char>;
{% endhighlight %}

* `using`, w przeciwieństwie do `typedef` można używać z szablonami

{% highlight cpp %}
template <class T>
using Pair = std::pair<int, T>

Pair<char> pair_;   // std::pair<int, char>
{% endhighlight %}

* Dobrą praktyką jest używanie w kodzie nazw domenowych, łatwiej zrozumieć kod
* `typedef` pochodzi z języka C
* `typedef` nie ma zdefiniowanej kolejności podawania argumentów dlatego 2 poniższe linijki są równoważne

{% highlight cpp %}
typedef std::pair<float, char> Pair;    // OK!

std::pair<float, char> typedef Pair;    // OK!
{% endhighlight %}
---


## `nullptr`

* Nie wskazuje na żadną wartość
* Tworząc wskaźnik bez przypisania mu wartości na jaką ma wskazywać, dobrą praktyką jest pisanie wąsatych nawiasów - oznacza to ustawienie wskaźnika na `nullptr`
* Ma specjalny typ `std::nullptr_t`

```cpp
int* p {};  // p = nullptr
```

```cpp
void foo(int);

foo(0);         // zawoła foo(int)
foo(NULL);      // zalezy od kompilatora
foo(nullptr);   // compile-time error
```

---

* Nie wskazuje na żadną wartość
* Ma (nowy) typ `std::nullptr_t`
* Przed C++11 wartość `NULL` była w zależności od kompilatora różnie definiowana (najcześciej jako `0` lub `0L`)
* Na pierwszy rzut oka to samo co `0` i `NULL`

{% highlight cpp %}
int* i = nullptr;
int* j = NULL;
int* k = 0;

ASSERT_EQ(i == j);
ASSERT_EQ(i == k);
{% endhighlight %}

* W przeciwieństwie do `0`, `0L` i `NULL`, `nullptr` **nie konwertuje się do podstawowych typów: `bool` i znakowych i liczbowych**
* Tworząc pusty wskaźnik dobrą praktyką jest zainicjowanie go `{}` co oznacza utawienie go na `nullptr`



## Pętla po zakresie

* Wygodne iterowanie po kontenerach STL, tablicach typu C oraz liście inizjalizacyjnej
* W celu uniknięcia kopiowania w trakcie iteracji trzeba zastosować znak referencji `&`
* Nie nadaje się w sytuacji gdy potrzebny jest dostęp do dwóch elementów jednocześnie albo trzeba przeglądać jednocześnie 2 zakresy
* Żeby iterować po kontenerach zdefiniowanych przez użytkownika trzeba zdefiniować funkcje `begin()` oraz `end()`

{% highlight cpp %}
class Container {
    std::list<int> v_;
public:
    void add(int i) { v_.push_back(i); }
    friend std::list<int>::iterator begin(Container& cont);
    friend std::list<int>::iterator end(Container& cont);
};

std::list<int>::iterator begin(Container& cont) { return cont.v_.begin(); }
std::list<int>::iterator end(Container& cont) { return cont.v_.end(); }

int main() {
    Container cont;
    cont.add(5);
    cont.add(6);

    for(const auto& item : cont) {
        std::cout << item << "\n";
    }
}
{% endhighlight %}

## Lambdy



## Jednolita inicjalizacja

* Od C++11 wszystko można inicjalizować za pomocą klamer `{ }` - np. `std::complex`, `std::vector`
    * Wcześniej za pomocą klamer `{ }` możliwa była tylko inicjalizacja struktur prostych POD (Plain Old Data - same pola, bez funkcji), a na przykład inicjalizując `std::vector` wszystko trzeba było wrzucać stosując `push_back()`
* Klamry `{ }` to tak na prawdę `std::initializer_list`, więc aby móc nim inicjalizować swoje typy, wystarczy napisać konstruktor przyjmujący `std::initializer_list`
    * Wszystkie elementy inicjalizowane za pomocą `std::initializer_list` **muszą być kopiowalne** (przykładowo inicjalizacja `std::unique_ptr` jest niemożliwa)
    * W przeciwieństwie do C++98, C++11 nie zezwala na niejawna konwersję typów - wszystkie elementy muszą być tego samego typu

{% highlight cpp %}
int array[] = {1, 2, 3, 5.5};   // C++98 OK, C++11 ERROR
{% endhighlight %}

## Delegowanie konstruktorów

* Na liście inicjalizacyjnej konstruktora można zawołać inny konstruktor tej samej klasy

{% highlight cpp %}
struct Entity {
    Entity() 
        : Entity(2),
        : y_(10) { }
    Entity(int x)
        : x_(x) { }

    int x_;
    int y_;
};
{% endhighlight %}

## Modyfikator `final`

* Przy klasie/strukturze (`class Entity final`) oznacza, że danej z danej klasy nie można dziedziczyć
* Przy metodzie w klasie oznacza, że danej metody od danego miejsca w hierarchii dziedziczenia nie można przesłaniać w klasach pochodnych



* Blokuje dziedziczenie z danej klasy lub nadpisywanie metod

{% highlight cpp %}
class Entity final
{ };

class Person : public Entity // ERROR!
{ };
{% endhighlight %}

{% highlight cpp %}
class Entity {
public:
    virtual void f() const;
};

class Person : public Entity {
public:
    virtual void f() const final;
};

class Policeman : public Person {
public:
    virtual void f() const; // ERROR!
{% endhighlight %}

## Statyczne asercje

* `static_assert` umożliwia stosowanie asercji, które są wykonywane w czasie kompilacji

{% highlight cpp %}
// Asercje w klasach

template <typename T>
class OnlyCompatibleWithIntegralTypes
{
   static_assert(std::is_integral<T>::value, "T must be integral");
};

OnlyCompatibleWithIntegralTypes<double> test; // błąd kompilacji!
{% endhighlight %}

{% highlight cpp %}
// Asercje w funkcjach

template <typename T, size_t N>
void accepts_arrays_with_size_between_1_and_255(T (&arr)[N])
{
    static_assert((N >= 1) && (N <= 255), "size of array must be in range [1, 255]");
}
{% endhighlight %}

## Szablony wariadyczne

**Niedokończone**
Szablon ze zmienną ilością argumentów

## Atrybuty

 `[[ noreturn ]]` [[carries_dependency]](C++11)

https://stackoverflow.com/questions/10538291/what-is-the-point-of-noreturn

## Słowo kluczowe  `constexpr`

Wyróżniamy:

* Stałe (zmienne)
    * Różni się od `const` (zmienna stała, której nie można zmieniać) tym, że wartość `constexpr` **dodatkowo** może zostać użyta do obliczeń dokonywanych w momencie kompilacji
* Funkcje stałe
    * Jeśli funkcja `constexpr` przyjmuje parametry które są znane w trakcie kompilacji, to kompilator zamiast kodu funkcji wstawi od razu `return X` - **to optymalizacja**

https://infotraining.bitbucket.io/cpp-11/features-for-lib-authors.html#uogolnione-stale-wyrazenia-constexpr

## Słowo kluczowe `decltype`

Umożliwia kompilatorowi określenie zadeklarowanego typu dla podanego jako argument obiektu lub wyrażenia.

```cpp
std::map<std::string, float> coll;

decltype(coll) coll2;               // coll2 has type of coll
decltype(coll)::value_type val;     // val has type float
```

## Słowo kluczowe `virtual` i `override`

Specifies that a virtual function overrides another virtual function. If the virtual function does not override a parent's virtual function, throws a compiler error.


OVERRIDE
* Opcjonalne ale zalecane
* Każe sprawdzić kompilatorowi czy funkcja z klasy bazowej jest przeciążona. Jeśli nie, kod się nie skompiluje.
* Przy np. błędzie (literówce) w nazwie w funkcji pochodnej tworzy się nowa funkcja


## Słowo kluczowe `delete`

* Definiując którąkolwiek z poniższych funkcji samodzielnie, kompilator nie wygeneruje reszty automatycznie. Trzeba napisać ich deklaracje i opatrzyć słowem kluczowym `default`.
    * Destruktor
    * Konstruktor domyślny
    * Konstruktor kopiujący (`Entity(const Entity& other)`)
    * Operator przypisania kopiujący (`Entity& operator=(const Entity& other)`)
    * Konstruktor przenoszący (`Entity(Entity&& object)`)
    * Operator przypisania przenoszący (`Entity& operator=(Entity&& object)`)

jeśli nie zdefiniujemy żadnej z wymienionych funkcji składowych, wszystkie zostaną wygenerowane przez kompilator
jeśli zdefiniujemy dowolny z 3 pierwszych elementów, kompilator nie wygeneruje konstruktora przenoszącego i przenoszącego operatora przypisania
jeśli zdefiniujemy konstruktor przenoszący lub przenoszący operator przypisania, żaden z pozostałych elementów nie zostanie automatycznie wygenerowany

## Funkcje `delete`

* Użycie za funkcją oznacza że użycie danej metody jest zablokowane
    * Działą zarówno dla metod jak i funkcji
* W kontekście zmiennych i tablic alokowanych na stosie oznacza zwolnienie pamięci

```cpp
void a(int a) { std::cout << a; }
void a(double d) = delete;

int main() {
    a(1);           // OK
    short s = 3;
    a(s);           // OK, konwersja short->int
    a(3.12);        // ERROR, próba skorzystania z funkcji delete
}
```

## Funkcje`default`

## Bibliografia

- [Repozytorium AnthonyCalandra na GitHub](https://github.com/AnthonyCalandra/modern-cpp-features)
- [Wykład "Programowanie Obiektowo Zorientowane w języku C++11 - Rozszerzenia w rdzeniu języka" z AGH w Krakowie](http://home.agh.edu.pl/~glowacki/docs/matwykl/O-o/_ProgObiekt-C++11-ZmianyWBibliot.pdf)

https://infotraining.bitbucket.io/cpp-11/

* http://home.agh.edu.pl/~glowacki/docs/matwykl/O-o/_ProgObiekt-C++11-ZmianyWBibliot.pdf
* http://home.agh.edu.pl/~glowacki/docs/matwykl/O-o/_ProgObiekt-C++11-Rozsz.pdf