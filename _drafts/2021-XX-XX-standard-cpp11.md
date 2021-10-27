---
layout: post
title: "Wyrażenia regularne w C++"
date: 2021-XX-XX 17:00:00
categories: 
---



## Nowe elementy języka

### Wskaźnik `nullptr`

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

### Aliasy `using`

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

### Slowo kluczowe `auto`

* Oznacza, żeby kompilator sam wydedukował typ na podstawie wyrażenia po prawej stronie
* `auto` istniało wcześniej, ale przed C++11 oznaczało zmienna zaalokowaną na stosie
* Przydaje się żeby nie pisać długich typów, np. `std::vector<int>::iterator`
* Umożliwia wygodną iterację po kontenerach

for (const auto& object : objects) {
    // ...
}

#### Mechanizm dedukcji typu

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