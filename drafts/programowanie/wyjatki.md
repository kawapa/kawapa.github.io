---
layout: post
title: Wyjątki
permalink: /XXX
search_exclude: true
---


 – poprawne używanie i pisanie własnych wyjątków, znajomość zasad zwijania stosu i kolejności niszczenia obiektów, znajomość zasad łapania wyjątków






## Metody obsługi błędów

### `goto`

* Nie używać, zaburza przepływ programu
* Nowe kompilatory zgłaszają ostrzeżenia, żeby nie używać? SPRAWDZIĆ
* Działa na etykietach

```cpp
#include <iostream>

bool isValid() { /* ... */ }

int main() {
    // ...
    if(!isValid()) {
        goto error;
    }

error:
    std::cerr << "Error occured" << '\n';
    return 1;
}
```

### `errno`

* Koncepcja z języka C tj. "error number"
* Statyczna, współdzielona zmienna, która jest ustawiana na jakąś wartość gdy wystąpi jakiś błąd

```cpp
int main() {
        double not_a_number = std::log(-1.0);
        std::cout << not_a_number << '\n';
        if (errno == EDOM) {
                std::cout << "log(-1) failed: " << std::sterror(errno) << '\n';
                std::setlocate(LC_MESSAGES, "de_DE.utf8");
                std::cout << "Or, in German, " << std::strerror(errno) << '\n';
        }
}
```

### Kody powrotu / kody błędów

* Kody błędów w formie np. `enum class`, np zwracany przez funkcję
* Za każdy razem należy łapać odpowiedź
* Nie można go wszędzie zastosować w:
    * Konstruktorach (nie mogą nic zwracać)
    * Przeciążonego operatory (które mają ściśle zwracany typ)

```cpp
#include <iostream>

enum class ErrorCode { Ok, FailCause1, FailCause2 };
bool isValid() { /* ... */ }

ErrorCode foo() {
    if(!isValid()) {
        return ErrorCode::FailCause1;
    }
    // ...
    return ErrorCode::Ok;
}

int main() {
    if(foo() == ErrorCode::FailCause1) {
        std::cerr << "Error occured" << '\n';
        return 1;
    }
    return 0;
}
```

Przykład z błędami:

```cpp

struct FileWrapper {
    FileWrapper(std::string const& filePath)
            : m_file(fopen(filePath.c_str(), "rw")) {
        /* What if the file did not open? */
    }

    ~FileWrapper() {
        fclose(m_file);
    }

    FileWrapper & operator<<(std::string const& text) {
        /* What if the file did not open? */
        fputs(text.c_str(), m_file);
        return *this;
    }

private:
    FILE* m_file;
};
```


### `throw`

* Można zgłosić (rzucić) wyjątek
* Łapiem w catch
* Jeśli zgłosimy wyjątek w konstruktorze - nie utworzy się (błędny) obiekt


```cpp
struct FileWrapper {
    FileWrapper(std::string const& filePath)
            : m_file(fopen(filePath.c_str(), "rw")) {
        if(!m_file) {
            throw std::runtime_error("File not opened");
        }
    }

    ~FileWrapper() {
        fclose(m_file);
    }

    FileWrapper & operator<<(std::string const& text) {
        /* Not validation needed, invalid object cannot be created */
        fputs(text.c_str(), m_file);
        return *this;
    }

private:
    FILE* m_file;
};
```

```cpp
#include <iostream>
#include <stdexcept>

void foo() { throw std::runtime_error("Error"); }

int main() {
    try {
        foo();
    } catch(std::runtime_error const&) {
        std::cout << "std::runtime_error" << std::endl;
    } catch(std::exception const& ex) {
        std::cout << "std::exception: " << ex.what() << std::endl;
    } catch(...) {      // NIEPOLECANE!
        std::cerr << "unknown exception" << std::endl;
    }
}
```



Co to jest wyjątek

* Każdy obiekt może być wyjątkiem
* `throw 42` - zła praktyka, nie wiadomo co to oznacza
    * Nie rekomendowane używanie typów wbudowanych lub tworzonych klas jako wyjątki
* dobra pratkyka `throw std::runtime_error{"WIADOMOSC!"};`
* Zaleca się aby wyjątki były specjalnymi klasami, które dziedziczą po innych wyjątkach z biblioteki standardowej
    * `std::exception` jest głównym wyjątkiem po którym dziedziczą wyjątki z biblioteki standardowej
* Każdy taki wyjątek może przeciążać funkcję `what()` które będzie zwracać tekst wyjątku


```
struct myException : public std::range_error {
    myException(std::string msg) : std::range_error(msg) {
        // teraz what() będzie działać
    }
}

// ... użycie:

throw myException("Blad!");
```

catch (...) {

}

to to samo co 

catch (std::exception)

... bo wszystkie wyjątki dziedziczą po std::exception. Wyjatki sa polimorficzne dlatego najpierw nalezy łapac wyjatki szczegolowe, pozniej ogolne.


## Jak to działa

```cpp
struct TalkingObject {
    TalkingObject()  { cout << "Constructor" << '\n'; }
    ~TalkingObject() { cout << "Destructor" << '\n'; }
};

void foo() { throw std::runtime_error("Error"); }

int main() {
    TalkingObject outside;
    try {
        TalkingObject inside;
        foo();
    } catch(runtime_error const& ex) {
        cout << "runtime_error: " << ex.what() << '\n';
    } catch(exception const&) {
        cout << "exception" << '\n';
    }
}
```

W przypadku wystapienia wyjatku:
* jesli w obecnym bloku try jest pasująca klauzula `catch` to doperio wtedy i tylko wtedy nastepuje niszczenie obiektów
* niszczone jest wszystko zaalokowane na stosie w odwrotnej kolejnosci jak zostalo stworzone, az do klauzuli try
    * Jest to mechanizm odwijania stosu (stack unwinding mechanism)
* dopiero wtedy jest obslugiwany wyjatek (jest łapany w catch) (wykonywane kod w klauzuli catch)
* wtedy obiekt wyjatku jest niszczony
* **jesli typ wyjatku nie pasuje do zadnej klauzuli catch** odwijanie stosu jest kontynuowane do kolejnego bloku try wcześniej w programie

* Jeśli wyjątek który nie został przechwycony i który wpada po funkcję main powoduje std::terminate

```cpp
struct TalkingObject { /*...*/ };

void foo() { throw std::runtime_error("Error"); }

void bar() {
    try {
        TalkingObject inside;
        foo();
    } catch(std::logic_error const&) {
        std::cout << "std::logic_error" << '\n';
    }
}

int main() {
    TalkingObject outside;
    bar();
}

```
Wynik:
Constructor
Constructor
>> abort() <<

## Nieobsłużony wyjątek 



# Wyjątki

Zazwyczaj obsługę błędów robi się na wyjątkach

* Wymaga `#include <stdexcept>`

```cpp
int foo() {
    inst1();
    auto v = fun();
    if (v < 0) {
//        return -1;
    }
    return v;
}
```

Przy sprawdzeniu warunku, zamiast zwracać magiczną wartość (`return -1`), można rzucić wyjątek

```cpp
int foo() {
    inst1();
    auto v = fun();
    if (v < 0) {
        throw std::logic_error("KOMUNIKAT");
    }
    return v;
}
```

Wyjątek trzeba później złapać, robi się to zwykle w `main()`.
```cpp
int main() {

    try {
        foo();
    } catch (const std::logic_error& le) {
        std::cerr << le.what();
        // exit(-1);
        // można też ubić binarkę
    }
}
```

* Wszystkie wyjątki które dziedziczą po `std::exception` mają metodę `what()` która zwaraca dokładnie to co wpisaliśmy w nawias).



TWORZENIE Klas dziedziczacych po wyjatkach z biblioteki standardowej.

Tworzymy nową klase ktora dziedziczy po konkrentym wyjatku
https://en.cppreference.com/w/cpp/header/stdexcept

Uwaga! Trzeba wywolac (w liscie inicjalizacyjnej konsturktora) konstruktor klasy bazowej!


```cpp
class InvalidCoordinates : public std::invalid_argument { 
    InvalidCOordinates() : std::invalid_argument("Please provide proper coordinates) { }
};

class InsufficientCargo: public std::logic_error {
    InsufficientCargo() : std::logic_error("You dont hhave enough free space") { }
}
```

ZŁE PRAKTYKI

Rzucanie wszystkim, intem stringiem
```cpp
throw 'e';
```

To nie ejst dobre bo nie ma np. e.what(). Uniemozliwia to poprawna obsluge bledów.




## Bibliografia

* http://home.agh.edu.pl/~glowacki/docs/matwykl/O-o/_ProgObiekt-C++14-Rozsz.pdf
