---
layout: post
title: "C++11 - nowe elementy biblioteki standardowej"
date: 2021-11-21 17:00:00
permalink: /cpp11-nowe-elementy-biblioteki-standardowej
search_exclude: true
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
