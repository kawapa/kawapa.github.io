---
layout: post
title: "Jedno makro dla funkcji przyjmującej różną liczbę argumentów"
date: 2021-08-30 17:55:00
categories: 
---

Makro to instrukcja dla preprocesora, który przetwarza i przygotowuje kod źródłowy programu do kompilacji. Gdy preprocesor napotyka na zdefiniowane wcześniej makro, podmienia je na zdefiniowane wcześniej wyrażenie lub instrukcję. Używanie makr w nowoczesnym kodzie jest mocno kontrowersyjne (może oprócz Embedded), ale często spotyka się je w projektach legacy.

## Tytułowy problem

Mamy w projekcie klasę do zrzucania/zapisywania logów. Może one przyjmować (w zależności od typu zdarzenia) różne argumenty np.: tekst, liczby/enum'y (które określają na przykład typ i klasę zdarzenia). Co zrobić by móc wygodnie korzystać z przeciążonej funkcji `log()` (na przykład poprzez `LOG(...)`, która przyjmie wszystkie możliwe formy argumentów)?

{% highlight cpp %}
class Logger {
public:
    void log(const char* text);
    void log(const char* text, int type);
    void log(const char* text, int type, Sentry::severity s);
// ...
};
{% endhighlight %}

## Rozwiązanie

{% highlight cpp %}
#define GET_MACRO(_0,_1,_2,NAME,...) log
#define LOG(...) GET_MACRO(__VA_ARGS__, LOG3, LOG2, LOG1)(__VA_ARGS__)
{% endhighlight %}

## Bibliografia

* [Stack Overflow - Overloading Macro on Number of Arguments](https://stackoverflow.com/questions/11761703/overloading-macro-on-number-of-arguments)
