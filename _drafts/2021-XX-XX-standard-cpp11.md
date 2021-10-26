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

