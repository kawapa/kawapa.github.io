---
layout: post
title: Wyrażenia regularne w C++
date: 2021-11-28 17:00:00
permalink: /XXX
search_exclude: true
---

Regular expressions
https://www.youtube.com/results?search_query=c%2B%2B+regular+expression

Wyrażenia regularne umożliwiają szybkie wyszukiwanie konkretnego wzorca w tekście.


Implementacja wyrażeń regularnych obecna w bibliotece standardowej języka C++ zgodna z wyrażeniami regularnymi języka PERL oraz dokumentacją biblioteki boost::regex.

## Wyrażenia regularne - podstawy

Opis:

* `w` - dowolna litera lub litera w
* `d` - dowolna cyfra lub litera d
  * Dopiero dodanie `\` przed `w` lub `d` oznacza, że chodzi o dowolną literę lub dowolną cyfrę

Przykład 1: polski kod pocztowy `\d\d-\d\d\d`

Powyższy sposób jest **poprawny**, ale niezbyt wygodny bo w długim wzorcu nie widać na pierwszy rzut oka czy napisaliśmy 5 czy 6 kolejno występujących dowolnych cyfr dlatego stosuje się zapis:

`\d{2}-\d{3}`

* {2} - Dokładnie 2 wystąpienia znaku ostatnio określonego znaku

* Jeśli jakaś część wzorca jest opcjonalna to trzeba podzielić cały wzorzez na części poprzez ujęcie je nawiasami okrągłymi `( )`

Przykład 2: załóżmy na chwilę, że polski kod pocztowy ma na końcu 2 opcjonalne litery poprzedzone myślnikiem. Wtedy podzielony wzorzec wyglądał by tak:

`(\d{2}-\d{3})(-\w{2})`

Żeby wskazać że ostatnia część jest opcjonalna należy użyć znaku alternatywy `|` lub znaku `?` oznaczającego coś opcjonalnego. Można zatem zastosować 2 zapisy:

`(\d{2}-\d{3})|(\d{2}-\d{3}-\w{2})` lub `(\d{2}-\d{3})(-\w{2})?`

* Jeśli nie używamy znaku specjalnego w stosunku do zgrupowanej części wzorca, nawiasy `( )` można pominąć. Zatem wersja z `?` będzie wyglądać tak:

`\d{2}-\d{3}(-\w{2})?`

* Spację można zapisać jako ` ` lub jako `\s`

* Zero lub więcej danego znaku oznaczamy przyrostkiem `*`
  * Przyrostek wstawiany jest za znakiem, którego on dotyczy
  * Przedrostek wstawiany jest przed znakiem, którego on dotyczy


* UWAGA: przy zapisywaniu wzorców w literałach łańcuchowych należy pamiętać o konieczności wstawiania ukośnika wstecznego `\` przed każdym znakiem specjalnym (mogącym oznaczać dla kompilatora koniec ciągu tekstowego).
    * Można zapisać tak:
      * `const char* pattern = "`\\d{2}-\\d{3}(-\\w{2})?`" lub tak R"(`\d{2}-\d{3}(-\w{2})?`)"

## Użycie wyrażeń regularnych w C++

* `#include <regex>`

Przykład zainicjalizowanego wzorca:

{% highlight cpp %}
regex pat {R"(`\d{2}-\d{3}(-\w{2})?`)"}
{% endhighlight %}

* W celu zastosowania wzorca wobec jakiegoś ciągu tekstu robimy:

{% highlight cpp %}
smatch matches;
if (std::regex_search(text, matches, pat)) {
    std::cout << "Wzorzec znaleziony!";
}
{% endhighlight %}

* Zmienna `matches` to wektor poddopasowań typu `std::string`, który przechowuje wszystko co pasuje do wzorca `pat` oraz zwraca `false` jeśli nic nie znaleziono
  * Można sprawdzić `matches.size()`


{% highlight cpp %}

{% endhighlight %}



## 5. Bibliografia

- [Bjarne Stroustrup - Programowanie. Teoria i praktyka z wykorzystaniem C++](https://helion.pl/ksiazki/programowanie-teoria-i-praktyka-z-wykorzystaniem-c-wydanie-iii-bjarne-stroustrup,pcppt3.htm#format/d)






## Bibliografia

* http://home.agh.edu.pl/~glowacki/docs/matwykl/O-o/_ProgObiekt-C++14-Rozsz.pdf
