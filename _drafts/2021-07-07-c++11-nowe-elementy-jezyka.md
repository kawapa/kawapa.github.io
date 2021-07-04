---
layout: post
title: "C++11 - nowe elementy języka"
date: 2021-07-04 07:00:00
categories: 
---

Standard C++11 to trzecie wydanie standardu języka wydane we wrześniu 2011 roku. Zastępuje ono edycję C++03 z 2003 roku i stanowi początek tak zwanego nowoczesnego C++.

### Petla po zakresie

* Wygodne iterowanie po kontenerach STL, tablichach typu C oraz liście inizjalizacyjnej
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

### Lambdy

*Anonimowa* funkcja tworzona w miejscu użycia. Wyrażenie lambda składa się z:
- `[ ]` - Lista przechwytująca (*capture list*). Umożliwia korzystanie ze zmiennych użytych wcześniej w kodzie
- `( )` - (**OPCJONALNE**) Lista argumentów np. `mutable` (zmienne przechwycone przez wartość mogą być modyfikowane wewnątrz ciała wyrażenia)
- `->` (**OPCJONALNE**) Typ zwracany
- `{ }` - Ciało funkcji

### Jednolita inicjalizacja

* Od C++11 wszystko można inicjalizować za pomocą klamer `{ }` - np. `std::complex`, `std::vector`
    * Wcześniej za pomocą klamer `{ }` możliwa była tylko inicjalizacja struktur prostych POD (Plain Old Data - same pola, bez funkcji), a na przykład inicjalizując `std::vector` wszystko trzeba było wrzucać stosując `push_back()`
* Klamry `{ }` to tak na prawdę `std::initializer_list`, więc aby móc nim inicjalizować swoje typy, wystarczy napisać konstruktor przyjmujący `std::initializer_list`
    * Wszystkie elementy inicjalizowane za pomocą `std::initializer_list` **muszą być kopiowalne** (przykładowo inicjalizacja `std::unique_ptr` jest niemożliwa)
    * W przeciwieństwie do C++98, C++11 nie zezwala na niejawna konwersję typów - wszystkie elementy muszą być tego samego typu

{% highlight cpp %}
int array[] = {1, 2, 3, 5.5};   // C++98 OK, C++11 ERROR
{% endhighlight %}

### Delegowanie konstruktorów

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

### Modyfikator `final`

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

### Statyczne asercje

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

### Slowo kluczowe `auto`

* Kompilator sam ma wydedukować typ
* Przydaje się żeby nie pisać długich typów, np. `std::vector<int>::iterator`
* Stawiając referencję `&` przy `auto`, wszelkie modifikatory (`const`, `volatile`) zostają zachowane (jeśli nie, są pomijane)

{% highlight cpp %}
const vector<int> values;
auto v1 = values;           // v1 : vector<int>
auto& v2 = values;          // v2 : const vector<int>&
{% endhighlight %}

* Tablice:

{% highlight cpp %}
Gadget items[10];
auto g1 = items             // g1 : Gadget*
auto& g2 = items;           // g2 : Gadget(&)[10] - referencja do tamtej tablicy
{% endhighlight %}

* Przed C++11 `auto` oznaczało zmienną automatyczną tworzoną na stosie (w przeciwieństwie do `new` tworzonej na stercie)

### Wskaznik `nullptr`

* Nie wskazuje na żadną wartość
* Tworząc wskaźnik bez przypisania mu wartości na jaką ma wskazywać, dobrą praktyką jest pisanie wąsatych nawiasów - oznacza to ustawienie wskaźnika na `nullptr`
* Ma specjalny typ `std::nullptr_t`

{% highlight cpp %}
int* p {};  // p = nullptr
{% endhighlight %}

{% highlight cpp %}
void foo(int);

foo(0);         // zawoła foo(int)
foo(NULL);      // zalezy od kompilatora
foo(nullptr);   // compile-time error
{% endhighlight %}

### Szablony wariadyczne

**Niedokończone**
Szablon ze zmienną ilością argumentów

### Aliasy using

* Dobrą praktyką jest używanie w kodzie nazw domenowych, łatwiej zrozumieć kod

{% highlight cpp %}
using Pair = std::pair<float, char>;
throw;

typedef std::pair<float, char> Pair;    // odpowiednik z typedef
{% endhighlight %}

* Przewagą `using` nad `typedef` jest, że `using` można użyć z szablonami

{% highlight cpp %}
template <typename T>
using StrKeyMap = std::map<std::string, T>

StrKeyMap<int> myMap;   // std::map<std::string, int>
{% endhighlight %}

* Ciekawostka: `typedef` nie ma zdefiniowanej kolejności podawania argumentów dlatego 2 poniższe linijki są równoważne

{% highlight cpp %}
std::pair<float, char> typedef Pair;

typedef std::pair<float, char> Pair;
{% endhighlight %}

### Atrybut `[[ noreturn ]]`

https://stackoverflow.com/questions/10538291/what-is-the-point-of-noreturn

### Słowo kluczowe  `constexpr`

https://infotraining.bitbucket.io/cpp-11/features-for-lib-authors.html#uogolnione-stale-wyrazenia-constexpr

### Słowo kluczowe `decltype`

### Słowo kluczowe `virtual` i `override`

### Słowo kluczowe `delete`


### Bibliografia

- [Repozytorium AnthonyCalandra na GitHub](https://github.com/AnthonyCalandra/modern-cpp-features)
- [Wykład "Programowanie Obiektowo Zorientowane w języku C++11 - Rozszerzenia w rdzeniu języka" z AGH w Krakowie](http://home.agh.edu.pl/~glowacki/docs/matwykl/O-o/_ProgObiekt-C++11-ZmianyWBibliot.pdf)