---
layout: post
title: Wielowątkowość w C++ - część 1
categories: [post]
date: 2021-12-24
permalink: /wielowatkowosc
nav_exclude: true
---

**Prawo Moore'a** - Liczba tranzystorów w procesorze podwaja się co 2 lata. Częstotliwość taktowania zegarów procesora przestała rosnąć około roku 2004 (zatrzymała się na ~ 3GHz). Obecnie trend jest taki, że dokłada się kolejne rdzenie i idzie się w kierunku równoległości.

**Free lunch** - Zjawisko kiedy programiści nie martwią się o wydajność swoich programów tylko czekają aż na rynku pojawi się szybszy sprzęt.

**Prawo Amdahla** - mówi ile potencjalnie może wzrosnąć "prędkość" wykonywania programu jeśli użyjemy wielowątkowości (prawo to ilustruje wykres liczby procesorów od wzorstu szybkosći). Maksymalne przyspieszenie, które można osiągnąć to 20-krotne - więcej się nie da przez konieczność podziału zadań i synchronizacji wątków.

---

## Wątek i proces

**Wątek**

* Część programu wykonywana współbieżnie w obrębie jednego procesu (zwany także *lekkim procesem*)
   * W jednym procesie może istnieć wiele wątków
* Wątki w obrębie jednego procesu dzielą przestrzeń adresową oraz zasoby systemowe

**Proces**

* Egzemplarz wykonywanego programu
* W celu wykonania programu system operacyjny przydziela mu zasoby i jeżli wymagane jest wykonywanie pewnych czynności współbieżnie - **tworzone są wątki**
* Każdy proces otrzymuje unikatowy numer (`PID`)

|              | Wątki             | Procesy |
|:-------------|:------------------|:--------|
| Stosy        | Osobne            | Osobne  |
| Sterty       | Wspólne           | Osobne  |
| Komunikacja  | Szybka przez wspólną przestrzeń adresową (stertę) | Wolniejsza przez systemowe mechanizmy IPC (gniazda, pliki, sygnały, potoki, pamięć współdzielona) |

---

## Współbieżność, a równoległość

Współbieżność (*concurrency*) - wykonywanie wielu zadań jednocześnie (nawet na jednym procesorze). Iluzja równoległości osiągana jest przez szybkie przełączanie kontekstu (zadań).

Równoległość (*parallelism*) - rodzaj przetwarzania, w którym kilka obliczeń jest realizowanych w tym samym czasie (np. na wielu procesorach) w celu zwiększenia prędkości obliczeniowej.

---

## Kiedy stosować współbieżność?

* Podział zagadnień
* Zwiększenie wydajności
  * Zrównoleglenie zadań (podział zadania na części)
  * Zrównoleglenie danych (wykonywanie tych samych zadań na różnych fragmentach danych)

---

## Kiedy nie stosować współbieżności?

* Gdy zbyt wiele wątków może obniżyć wydajność zamiast ją zwiększyć (koszt uruchomienia wątku, koszt zasobów - każdy wątek zajmuje pamięć)
* Gdy wzrost wydajności nie jest proporcjonalny do włożonego wysiłku: złożoność kodu i koszt jego utrzymywania

---

## Tworzenie nowego wątku - przykłady

* Żeby pomyślnie utworzyć wątek należy przekazać mu: funkcję, funktor (obiekt funkcyjny - jest on kopiowany do wątku), lambdę... `std::thread name(function)`

```cpp
#include <thread>
#include <iostream>

struct Bar1 {
    void operator()() { std::cout << "Hello World!"; }
};

struct Bar2 {
    void foo() { std::cout << "Hello World!"; }
};

void foo() {
    std::cout << "Hello World!";
}

class Car {
    int production_year;
    std::string model_name;

public:
    void setData(int year, const std::string& model) {
        production_year = year;
        model_name = model;
    }
}

int main() {
    std::thread t1([]() { std:: cout << "Hello World!"; });

    std::thread t2(foo);
    // przekazanie funkcji

    std::thread t3(&foo);
    // przekazanie referencji do funkcji

    Bar1 bar1;
    std::thread t4(bar1);
    // przekazanie funktora (obiekt funkcyjny)

    std::thread t5(*foo);
    // przekazanie wskaźnika do funkcji

    Bar2 bar2;
    std::thread t6(&Bar2::foo, &bar2);

    Car toyota;
    // każda funkcja klasy jest "pod spodem" tłumaczona przez kompilator
    // na normalną funkcję przyjmującą wskaźnik na obiekt (this)
    // dlatego tutaj trzeba przekazać &toyota
    std::thread t7(&Car::setData, &toyota, 2015, "Corolla");
    // "Corolla" nie wymaga `std::ref()` bo to obiekt tymczasowy
    // (można podpiąć pod `const &`)

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
}
```

---

## Podstawowe operacje na wątkach

* Jeśli wątek nie dostanie żadnej funkcji, `std::thread::joinable()` zwróci false
* Jeśli przed końcem programu nie wywołamy na wątku `join()` lub `detach()`, otrzymamy `std::terminate`
    * Analogicznie jeśli wywołane zostaną obie funkcje
* Kopiowanie wątku jest zabronione, możliwe jest natomiast przenoszenie (`std::move`) oraz zwracanie kopii wątku z funkcji
  * Kompilator zoptymalizuje kod i "wyrzuci" zbędne kopiowanie (*RVO* - *Return Value Optimisation*)
* Jeśli podczas wykonywania programu wyskoczy wyjątek, nie będzie możliwe złączenie wątku dlatego należy korzystać z RAII

```cpp
class ThreadGuard {
    std::thread &t;

public:
    explicit ThreadGuard(std::thread& t_) : t(t_) {
        if (!t.joinable()) {
            throw std::logic_error("Not a thread");
        }
    }

    ~ThreadGuard() {
        if (t.joinable()) {
            t.join();
        }
    }

    ThreadGuard(const ThreadGuard &) = delete;
    ThreadGuard(ThreadGuard &&) = default;
    ThreadGuard& operator=(const ThreadGuard &) = delete;
    ThreadGuard& operator=(ThreadGuard &&) = default;
};

void fun() { }

int main() {
    std::thread t(fun);
    ThreadGuard g(t);
    // lub ThreadGuard(std::thread(fun));
}
```

---

`std::thread::joinable()`

* Zwraca `true` jeśli można zrobić `join()` lub `detach()`

--- 

`std::thread::join()`

* Jeśli chcemy poczekać aż wątek zakończy wszystkie swoje obliczenia i chcemy go zsynchronizować w jakimś miejscu
  * Program nie pójdzie dalej póki wątek nie zakończy pracy
* Wywołanie `join()` na wątku który nie został zainicjalizowany żadną funkcją zakończy się wyjątkiem `std::system_error`

---

`std::thread::detach()`

* Nie czekamy na wątek tylko idziemy dalej
* Tracimy nad nim kontrolę, ale on dalej pracuje i zwróci wynik jak skończy (o ile `main()` nie zakończy się szybciej)
* Każdy wątek posiada odrębny stos (adres powrotu z funkcji oraz zmienne lokalne). Wywołując `detach()` wszystko się zwija

---

`std::thread::hardware_concurrency()`

* Zwraca ile procesor ma wątków sprzętowych które może obsługiwać jednocześnie
* Utworzenie większej liczby wątków jest możliwe i nazywa się *oversubscription*. Efekty przełączania kontekstu mogą mieć jednak negatywny wpływ na wydajność

---

`std::this_thread::get_id()`

* Zwraca id wątku
* `std::thread::id this_id = std::this_thread::get_id()`

---

## Przekazywanie argumentów do funkcji w wątku

### Przekazywanie przez wartość

* O ile wątki nie pracują na dużych porcjach danych, **zawsze preferowane jest kopiowanie**

```cpp
Struct SomeStruct { };

void bar(int x, std::string str, SomeStruct obj) { }

int main() {
    std::thread t(bar, 10, "String", SomeStruct{});
    t.join();
}
```

### Przekazywanie przez referencję

Jeśli funkcja przyjmuje referencję, a przekażemy zmienną "tak jak zawsze" to nowy wątek dostanie referencję do kopii zmiennej, którą chcieliśmy zmodyfikować. Rozwiązaniem problemu jest zastosowanie *wrapper'a* `std::ref` (lub `std::cref()` dla referencji stałych).

```cpp

void bar(int& x, int* y) {
    std::cout << "Inside fun: = " << x << " | y = " << *y << std::endl;
    x = 20;
    *y = 30;
}

int main() {
    int x = 10;
    int y = 10;
    std::thread t(bar, std::ref(x), &y);
    t.join();
    std::cout << "Outside fun: x = " << x << " | y = " << y << std::endl;

    return 0;
}
```

#### Problem wiszącej referencji

* Długość życia referencji lub wskaźnika, który otrzymuje wątek musi być dłuższa niż długość życia samego wątku

```cpp
#include <thread>

void do_sth([[maybe_unused]] int i) { /* ... */ }

struct A {
    int& ref_;
    A(int& a) : ref_(a) {}
    void operator()() {
        do_sth(ref_); // potential access to
                      // a dangling reference
    }
};

std::thread create_thread() {
    int local = 0;
    A worker(local);
    std::thread t(worker);
    return t;
} // local is destroyed, reference in worker is dangling

int main() {
    auto t = create_thread();  // Undefined Behavior
    auto t2 = create_thread(); // Undefined Behavior
    t.join();
    t2.join();

    return 0;
}
```

#### Problem niejawnej konwersji

* Tworzenie wątku t
* Przekazanie do wątku funkcji `f()`, `3` oraz `buffer`
    * Funkcja `f()` przyjmuje `std::string`, w związku z tym dochodzi tu do niejawnej konwersji z `char[]` na `std::string`
    * Zaraz po stworzeniu wątku wywoływane jest `detach()` - **konwersja może nie zdążyć się zakończyć**

Rozwiązanie: przygotowanie łańcucha znaków wcześniej: `std::thread t(f, 3, std::string(buffer));`

```cpp
void f(int i, std::string const& s);

void oops(int arg) {
    char buffer[1024];
    sprintf(buffer, "%i", arg);
    std::thread t(f, 3, buffer);
    t.detach();
}
```

* **Jeśli przy przekazywaniu argumentów do wątku istnieje ryzyko niejawnej konwersji, należy przekonwertować wymagany argument wcześniej**

---

## Przekazywanie wyniku obliczeń do funkcji main()

* Nie da się tego zrobić przez `return`, można użyć:
    * Zmiennej globalnej (niezalecane)
    * **Dodatkowej zmiennej, którą przekazujemy przez referencję do funkcji - w niej zostanie zapisany wynik**

---

## Wyjątki w wątkach

* Aby przechwycić wyjątek rzucony z innego wątku należy użyć wskaźnika na wyjątek `std::exception_ptr`
    * Wątek rzucający wyjątek przypisuje do niego `std::current_exception()`
    * Wątek, który chce złapać wyjątek sprawdza czy `std::current_expection() != 0)`. Jeśli tak, bieżący wątek rzuca dany wyjątek ponownie poprzez `std::rethrow_exception()`

```cpp
#include <iostream>
#include <thread>
#include <exception>
#include <stdexcept>

int main() {
    std::exception_ptr thread_exception = nullptr;
    std::thread t([](std::exception_ptr & te) {
        try {
            throw std::runtime_error("WTF");
        } catch (...) {
            te = std::current_exception();
        }
    }, std::ref(thread_exception));     // tu przekazanie referencji
    t.join();

    if (thread_exception) {
        try {
            std::rethrow_exception(thread_exception);
        } catch (const std::exception & ex) {
            std::cout << "Thread exited with an exception: "
                      << ex.what() << "\n";
        }
    }
    return 0;
}
```

## Współdzielenie danych

Strumień wyjściowy cout jest jeden. Jeśli więcej niż jeden wątek wysyła do cout, te operacje mogą się przeplatać.

### Współdzielenie danych do odczytu

* Wiele wątków czytających to samo miejsce w pamięci nie wymaga żadnych działań

### Współdzielenie danych z modyfikacją

* Wymagana jest synchronizacja
* Przykładowo: jeden wątek iteruje po liście dwukierunkowej, a drugi usuwa element ze środka
  * Efekty mogą być różne w zależności od momentu, w którym dwa wątki 
    * Zjawisko to nosi nazwę wyścigów (race conditions) - Undefined behaviour 

---

## Niebezpieczeństwa podczas używania wielowątkowości

### Deadlock

* Sytuacja, w której conajmniej dwa różne wątki czekają na siebie i żadna nie może pójść dalej
* Występuje losowo przy niektórych uruchomieniach programu 
* Zalecane użycie `std::scoped_lock` do rozwiązania problemu zakleszczenia
* Operacja czekania na wątek nie blokuje procesora

```cpp
#include <thread>
#include <mutex>

using namespace std;

class X {

    mutable mutex mtx_;
    int value_ = 0;

public:
    explicit X(int v) : value(v) {}

    bool operator< (const X & other) const {
        lock_guard<mutex> ownGuard(mtx_);
        locK_guard<mutex> otherGuard(other.mtx_);
        // Rozwiazanie:
        // std::scoped_lock l(mtx_, other.mtx_);

        return value_ < other.value_;
    }
};

int main() {

    X x1(5);
    X x2(6);

    thread t1([&](){ x1 < x2; });
    thread t2([&](){ x2 < x1; });

    t1.join();
    t2.join();

    return 0;
}
```

* Słowo kluczowe `mutable` przy mutexie oznacza tyle, że nawet w przypadku metody `const` stan mutexu `mtx_` może zostać zmieniony (wywoływanie `lock()` i `unlock()` to w pewnym sensie jego modyfikacja)
* Słowo kluczowe `explicit` przy konstruktorze blokuje niejawne konwersje
    * Więcej informacji o `explicit`:
        * https://www.youtube.com/watch?v=Rr1NX1lH3oE

### Race conditions

* Sytuacja, w której dwa lub więcej procesów wykonuje operację na zasobach dzielonych, a ostateczny wynik tej operacji jest zależny od momentu jej realizacji
* Wyścig = undefined behaviour
* Aby zapobiec warunkom wyścigu należy stworzyć mechanizm zabraniający więcej niż jednemu wątkowi dostępu do zasobów dzielonych w tym samym czasie
* Nieporządane skutki uboczne zazwyczaj nie występują podczas większości uruchomień danej funkcji
  * Najczęściej jeśli procesor nie jest obciążony, wszystko działa jak należy. Im bardziej obciążony jest procesor, tym większa jest ryzyko innej kolejności dostępu do danych (takie sytuacje trudno jest zreprodukować)
* Problem wyścigów jest krytyczny czasowo i może być nie do wychwycenia przy użyciu debuggera. Debugger spowalnia wykonywanie operacji 
* Do wykrywania tego zjawiska służy tzw. Thread Sanitizer (*TSan*, *Data race detector* wbudowany g++ oraz clang)

```cpp
void abc(int &a) { a = 2; }
void def(int &a) { a = 3; }

int main()
{
    int x = 1;
    std::thread t1(abc, std::ref(x));
    std::thread t2(def, std::ref(x));

    t1.join();
    t2.join();

    std::cout << x << std::endl;
}
```

### Data races

* Wyścig na danych, wartość zmiennej będzie zależeć od tego jak zostaną zakolejkowane wątki i może być różna przy różnych uruchomieniach programu

### Zagłodzenie wątku

Sytuacja, w której przynajmniej jeden wątek nigdy nie dostanie wszystkich wymaganych zasobów

### Live lock

* Podobny do Deadlock przy czym stan dwóch procesów związanych z blokadą zmienia się w stosunku do drugiego procesu
* Deadlock powoduje nieskończone oczekiwanie podczas gdy Livelock, jest szczególnym przypadkiem deadlocka, który powoduje marnowanie cykli procesora

## Wykrywanie problemów związanych z wielowątkowością

### Thread sanitizer

`>> g++ 1.cpp -lpthread -fsanitize=thread -O2 -g`

`>> ./a.out`

`-g` - informacja dla debuggera
`-O2` - optymalizacje - warto włączyć bo często problemy pojawiają się dopiero przy optymalizacji (klient dostaje często program zoptymalizowany)

Jeśli nie ma "niebezpieczeństw", *thread sanitizer* nie pokaże "raportu".

### Debugger

`>> g++ 1.cpp -lpthread -g`

`>> gdb --tui ./a.out`

Komenda | Opis
------------ | -------------
`b 5` | Ustawia breakpoint w 5 linii
`watch x` | Obserwowanie zmian zmiennej x (debugger zatrzyma się gdy nastąpi jej modyfikacja)
`c` | Kontynuowanie debugowania
`info threads` | Informacje o wątkach
`thread 3` | Przełączenie na wątek 3
`n` | Następna instrukcja
`fin` | Wykonanie wszystkiego do końca bieżącej funkcji
`up` | Przejście do wyższej ramki stosu
`down` | Przejście do niższej ramki stosu
`del br` | Usunięcie wszystkich breakpointów
CTRL + L | Odświeżenie widoku

---

## Mutexy

### `std::mutex`

* Blokuje jednoczesny dostęp do tzw. sekcji krytycznej
  * Dobrą praktyką jest wydzielenie sekcji krytycznej do osobnej funkcji
* Preferowane jest użycie `lock_guard` i zablokowanie całej funkcji, a nie pojedynczych linii
  * W przypadku wystąpienia wyjątku `std::mutex` nie zostanie odblokowany i inne wątki nigdy nie skończą pracy. Stąd zalecane jest użycie ktoregoś z menadżerów blokad RAII
* Czas trwania blokady musi być możliwie jak najkrótszy
* Nie blokujemy instrukcji `sleep_for()`
* Zamiast wypisywać `std::cout << "Hello" << " World";` warto skleić stringa wcześniej za pomocą `std::stringstream`
* Preferowane wykorzystanie jako składnik w klasie
* W przypadku stałych (`const`) nie ma potrzby stosowania blokad

Funkcja | Opis
------------ | -------------
`void lock()` | {::nomarkdown}<ul><li> Zablokowanie mutexu </li><li> Operacja blokująca - jeśli mutex jest zablokowany przez inny wątek to oczekujemy na odblokowanie</li></ul>{:/} |
`void unlock()` | {::nomarkdown}<ul><li> Odblokowanie mutexu</li></ul>{:/} |
`bool try_lock()` | {::nomarkdown}<ul><li> Próba zablokowania mutexu (zwraca `true` jeśli udało się zablokować i blokuje, `false` jeśli mutex zajęty i nie udało się go zablokować)</li><li> Operacja nieblokująca - w przypadku nieudanej próby zajęcia mutexu możemy wykonać inne czynności</li></ul>{:/} |

```cpp
#include <vector>
#include <thread>
#include <chrono>
#include <iostream>
#include <mutex>

void do_work(int id)
{
    this_thread::sleep_for(100ms);
    m.lock();
    cout << ss.rdbuf();
    m.unlock();
}

int main()
{
    std::mutex m;
    std::vector<std::thread> threads;

    for (int i = 0; i < 20; i++)
        threads.emplace_back(thread(do_work, i));

    for (auto && t : threads)
        t.join();

    return 0;
}
```

---

### `std::timed_mutex`

* W porównaniu z podstawowym `std::mutex`, udostępnia on dwie dodatkowe metody:
  * `bool try_lock_until(timeout_time)` - spróbuj zablokować do jakiegoś punktu w czasie (zwraca true jak się udało, false jeśli nie)
  * `bool try_lock_for(timeout_duration)` - spróbuj zablokować na jakiś czas (zwraca true jak się udało, false jeśli nie)

---

### `std::recursive_mutex`

* Ten sam wątek może wielokrotnie pozyskać mutex poprzez wywołanie metody `lock()` lub `try_lock`
* Aby zwolnić mutex wątek musi taką samą ilość razy go odblokować
* Zazwyczaj stosowany w algorytmach rekurencyjnych

---

### `std::recursive_timed_mutex`

* Połączenie `std::timed_mutex` oraz `std::recursive_mutex`

---

### `std::shared_mutex`

* Problem producenta i konsumenta lub problem czytelników i pisarzy
  * Wiele wątków jednocześnie czyta, ale np. jeden potrzebuje zapisać
* Możliwość pozyskiwania blokad współdzielonych przy pomocy
  * `void lock_shared()` (do wspólnego odczytu)
  * `bool try_lock_shared()`
  * `bool try_lock_shared_for(real_time)`
  * `bool try_lock_shared_until(abs_time)`
  * `void unlock_shared()`

---

## Menadżery blokad

### `std::lock_guard`

* Najprostszy, główny wybór
* Nie ma funkcji odblokowania, blokuje tak długo jak żyje
* Blokuje w konstruktorze, odblokowuje w destruktorze
* Przyjmuje dodatkowy patarametr
* Niekopiowalny

```cpp
#include <vector>
#include <thread>
#include <chrono>
#include <iostream>
#include <mutex>
#include <sstream>

void do_work(int id, mutex& m) {
    this_thread::sleep_for(100ms);

    stringstream ss;
    ss << "Thread [" << id << "]: " << "Job done!" << std::endl;

    lock_guard<mutex> lock(m);

    cout << ss.rdbuf();
    // Tak naprawdę nie trzeba tutaj mutexa bo to pojedyncza operacja
    // Nie da się jej "zakłócić"
}

int main() {
    std::mutex m;
    std::vector<std::thread> threads;

    for (int i = 0; i < 20; i++)
        threads.emplace_back(thread(do_work, i, std::ref(m)));

    for (auto && t : threads)
        t.join();

    return 0;
}
```

---

### `std::unique_lock`

* Opóźnione blokowanie
* Próby zablokowania ograniczone czasowo
* Blokowanie rekursywne
* Podejmowanie nieblokujących prób pozyskania blokady - `try_lock()`
* Obsługa `std::timed_mutex>`
* Korzystanie ze zmiennych warunkowych (condition variable)
* Niekopiowalny, ale przenoszalny
* Przyjmuje dodatkowy patarametr

---

### `std::scoped_lock`

* Przyjmuje różne mutexy
* Blokuje kilka mutexów
* Zapobiega zakleszczeniom (deadlock)
* Konstruktor blokuje wszystkie mutexy w bezpiecznej kolejności unikając blokad
  * Destruktor odblokowuje je w kolejności odwrotnej
* Niekopiowalny

```cpp
#include <iostream>
#include <mutex>
#include <thread>

class X {
    mutable std::mutex mtx_;
    int value_ = 0;

public:
    explicit X(int v) : value_(v) {}

    bool operator<(const X & other) const {
        std::scoped_lock l(mtx_, other.mtx_);
        return value_ < other.value_;
    }
};

int main() {

    X x1(5);
    X x2(6);

    std::thread t1([&] {
        if (x1 < x2)
            std::cout << "x1 is less" << std::endl;
    });

    std::thread t2([&] {
        if (x2 < x1)
            std::cout << "x2 is less" << std::endl;
    });

    t1.join();
    t2.join();

    return 0;
}
```

---

### `std::shared_lock<shared_mutex>`

* Menadżer współdzielonych blokad do odczytu
* Kilka wątków może współdzielić blokadę
* Wątki czytające muszą pozyskać blokadę `shared_lock<shared_mutex>`
* Wątki zapisujące muszą pozyskać wyłączną blokadę (`std::lock_guard` lub `std::unique_lock`)
* Te same własności co `std::unique_lock`
* Przyjmuje dodatkowy patarametr

---

### Dodatkowe parametry dla `std::lock_guard`, `std::unique_lock` oraz `std::shared_lock`

* W/w blokady przyjmują opcjonalny dodatkowy parametr w postaci `std::defer_lock` lub `std::adopt_lock`
  * `std::defer_lock`
    * Nie blokuje w momencie utworzenia tylko oczekuje na operację `std::lock()`
    * Stanowi to alternatywę dla `std::scope_lock`, który pojawił się w C++17
  * `std::adopt_lock`
    * Informacja dla konstruktora, że otrzyma on już zablokowane mutexy (wcześniej pojawia się `std::lock()`)
    * Działanie przeciwne do `std::defer_lock`

```cpp
// defer_lock
bool operator<(const X & other) const {
    std::unique_lock<std::mutex> l1(mtx_, defer_lock);
    std::unique_lock<std::mutex> l2(other.mtx_, defer_lock);
    std::lock(l1, l2);

    return value_ < other.value_;
}

// adopt_lock
bool operator<(const X & other) const {
    std::lock(mtx_, other.mtx_);
    std::lock_guard<std::mutex> l1(mtx_, adopt_lock);
    std::lock_guard<std::mutex> l2(other.mtx_, adopt_lock);

    return value_ < other.value_;
}
```

**Funkcja `std::lock()` gwarantuje zablokowanie wszystkich mutexów bez zakleszczenia niezależnie od kolejności ich pozyskania.**
