---
layout: post
title: Słowa kluczowe w C++
date: 2021-11-28 17:00:00
permalink: /XXX
search_exclude: true
---


alignas
alignof
default
explicit
extern
inline
friend
mutable
noexcep
static
volatile

TO WSZYSTKIE?









## `volatile`

Informuje kompilator, że wartość zmiennej może zmienić się *z zewnątrz* dlatego kompilator powinien zrezygnować z agresywnej optymalizacji i przy każdym odwołaniu do tej zmiennej wczytać nową wartość z komórki pamięci.

## `static`

 przed zmiennymi w funkcji lub w klasie
W przypadku zmiennej `static` wewnątrz funkcji, pamięć dla zmiennej jest zaalokowana na cały okres uruchomienia programu. Zmienna, mimo że jest zadeklarowana wewnątrz funkcji (i inkrementowana), będzie pamiętać swój stan nawet po kilku uruchomieniach funkcji.

```cpp
void demo() {  
    static int count = 0;           // zmienna nie jest deklarowana na nowo
    std::cout << count << " ";      // przy każdym wywołaniu funkcji
    count++;
}

int main() {
    for (int i=0; i<5; i++)
        demo();
    return 0;
}
```
Output: `0 1 2 3 4`

### `static` w kontekście obiektów i metod klasy

W przypadku zmiennej `static` wewnątrz klasy, zmienna ta jest wspólna dla wszystkich obiektów danej klasy. **Zmienna ta nie może być inicjalizowana za pomocą konstruktora.**

```cpp
class GfG {
public:
    static int i;
    GfG() {};
};

int GfG::i = 1;             // musi być zadeklarowana globalnie

int main() {
    GfG obj;
    std::cout << obj.i;     // lub GfG::i
}
```
Output: `1`

Zasięg obiektu `static`:

```cpp
class GfG {
    int i = 0;
    public:
    GfG() {
        i = 0;
        std::cout << "Inside Constructor\n";
    }
    ~GfG() { std::cout << "Inside Destructor\n"; }
};

int main() {
    int x = 0;
    if (x == 0) {
        static GfG obj;
        std::cout << obj.i;
    }
    std::cout << "End of main\n";
}
```

Output:<br>
`Inside Constructor`<br>
`End of main`<br>
`Inside Destructor`

Można wywołać metodę `static` bez tworzenia obiektu poprzez `GfG::printMsg()`. **Metody statyczne mają dostęp tylko do statycznych elementów klasy, nie można używać wskaźnika `this`.**

```cpp
class GfG {
public:
    static void printMsg() { std::cout << "Welcome to GfG!"; }
};

int main() {
    GfG::printMsg();
}
```
Output:

`Welcome to GfG!`




## `explicit`

* Zabrania niejawnej konwersji i przy jednoargumentowych konstruktorach.

```cpp
class Foo {
    int number_;

public:
    explicit Foo(int number)
        : number_(number) { }
    void printNum(){ std::cout << number_ << '\n'; }
};

void bar(Foo foo) {
    foo.printNum();
}

int main() {
    Foo foo(5);
    bar(foo);

    bar(10); // to już nie zadziała bo jest explicit
}
```




## Bibliografia

* http://home.agh.edu.pl/~glowacki/docs/matwykl/O-o/_ProgObiekt-C++14-Rozsz.pdf
