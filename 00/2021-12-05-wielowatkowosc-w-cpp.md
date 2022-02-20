---
layout: post
title: Wielowątkowość w C++
date: 2021-11-28 17:00:00
permalink: /XXX
search_exclude: true
---

Prosta pula wątków
https://github.com/changkun/ThreadPool

## Zmienne atomowe

### 12. Model pamięci

* Najmniejsza jednostka – 1 bajt
* Każdy bajt ma unikalny adres w pamięci
* Synchronizacja **nie jest potrzebna** jeśli zapisujemy coś wielowątkowo **do różnych obszarów pamięci**

```cpp
std::vector<int> v(10, 0);

for (int = 0; i < 10; i++)
    std::thread t([&]{ v[i] = i; });
```

* Synchronizacja **jest potrzebna** jeśli zapisujemy coś wielowątkowo **do tych samych obszarów pamięci**

```cpp
std::vector<int> v;

for (int = 0; i < 10; i++)
    std::thread t([&]{ v.emplace_back(i); });
```

* Synchronizacja jest potrzebna jeśli conajmniej jeden wątek zapisuje, a inne odczytują ten sam obszar pamięci
* Brak synchronizacji jeśli jest wymagana to *wyścig/undefined behaviour*
* Użycie `const` nie wymaga synchronizacji
* Link do pełnego artykułu - [czytaj](https://en.cppreference.com/w/cpp/language/memory_model)

### 13. Jak synchronizować?

```cpp
int a = 0;
std::mutex m;

std::thread t1([&] {
std::lock_guard<mutex> lg(m);
a = 1;
});

std::thread t2([&] {
std::lock_guard<mute> lg(m);
a = 2;
});
```

Lepsze rozwiązanie, które chroni przed wyścigiem (data-race) to zastosowanie zmiennej atomowej (`std::atomic`). W ten sposób zapewniamy odpowiednie porządkowanie operacji dostępu do pamięci.

```cpp
std::atomic<int> a = 0;
std::thread t1([&]{ a = 1; });
std::thread t2([&]{ a = 2; });
```

### 14. `std::atomic`

`std::atomic` | Opis
------------ | -------------
Cechy | <ul><li> Umożliwiają jednoczesny zapis i odczyt <ul><li> Nie ma potrzeby dodatkowego blokowania </li></ul></li><li> Pozwalają na prostą arytmetykę i operacje bitowe (**te których nie ma w standardzie języka wymagają blokowania mutexem**) </li><li> Wykorzystuje się tylko z typami prostymi (liczby i wskaźniki) </li></ul>
Najważniejsze operacje | <ul><li> `store()` - zapisuje wartość zmiennej atomowej (można podać dodatkowo `std::memory_order`) </li><li> `operator=()` - zapisuje wartość w zmiennej atomowej </li><li> `load()` - odczytuje wartość ze zmiennej atomowej (można podać dodatkowo `std::memory_order`) </li><li> `operator T()` - odczytuje wartość ze zmiennej atomowej</li></ul>

```cpp
// use store() /  load()
#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::vector<int> generateContainer()
{
    std::vector<int> input = {2, 4, 6, 8, 10, 1, 3, 5, 7, 9};
    std::vector<int> output;
    std::vector<std::thread> threads;
    std::mutex m;

    // należy jeszcze wyciągnąć lambdę przed pętlę...
    for (auto i = 0u; i < input.size(); i++) {
        threads.emplace_back([&, i]{
            std::lock_guard<std::mutex> l(m);
            // wstawianie wątków do wektora jest bezpieczne (bo jest sekwencyjne)
            // należy zabezpieczyć wstawianie liczb do wektora
            // bo może być problem z iteratorami
            output.push_back(input[i]);
        });
    }

    // "i" przekazujemy przez kopię
    // 1 powód: jeśli "i" przekażemy przez referencję to wszystkie wątki mogą mieć
    // taką samą wartość "i", np. 5
    // 2 powód: część wstawiania może się odbyć dopiero przed join(), a wtedy
    // zmienna "i" już nie istnieje (dangling reference)

    for (auto && t : threads)
        t.join();

    return output;
}

std::vector<int> generateOtherContainer()
{
    int start {5};
    // nie trzeba std::atomic bo mamy mutex na if oraz else
    std::atomic<bool> add {true};
    std::vector<int> output;
    std::vector<std::thread> threads;
    std::mutex m;

    for (int i = 0; i < 10; i++) {
        threads.emplace_back([&, i]{
            if (add)
            {
                std::lock_guard<std::mutex> l(m);
                output.push_back(start+=i);
            }
            else
            {
                std::lock_guard<std::mutex> l(m);
                output.push_back(start-=i);
            }
            add = !add;
        });
    }

    for (auto && t : threads)
        t.join();

    return output;
}

void powerContainer(std::vector<int>& input)
{
    std::vector<std::thread> threads;

    for (auto i = 0u; i < input.size(); i++)
        threads.emplace_back([&, i]{ input[i]*=input[i]; });
    // nie ma potrzeby stosowania mutexu
    // za każdym razem zapisujemy w inny obszar pamięci

    for (auto && t : threads)
        t.join();
}

void printContainer(const std::vector<int>& c)
{
    for (const auto & value : c)
        std::cout << value << " ";
    std::cout << std::endl;
}

int main() {

    auto container1 = generateContainer();
    printContainer(container1);
    powerContainer(    // należy jeszcze wyciągnąć lambdę przed pętlę...container1);
    printContainer(container1);

    auto container2 = generateOtherContainer();
    printContainer(container2);
    powerContainer(container2);
    printContainer(container2);

    return 0;
}
```

### 15. `std::atomic` i `std::memory_order`

`std::memory_order` pozwala na dodatkową otymalizację i określa on typ synchronizacji. Więcej informacji - [czytaj](https://en.cppreference.com/w/cpp/atomic/memory_order).

Typ `std::memory_order` | Opis
------------ | -------------
`memory_order_relaxed` | <ul><li> Nie ma żadnej synchronizacji (tak jakby nie było `std::atomic`)</li></ul>
`memory_order_consume` | <ul><li> Do odczytu </li><li> Zagwarantowane, że kompilator nie zmieni kolejności operacji przed `load()` i `store()` </li></ul>
`memory_order_acquire` | <ul><li> Do odczytu </li><li> Zagwarantowane, że kompilator nie zmieni kolejności operacji przed `load()` i `store()` </li></ul>
`memory_order_release` | <ul><li> Do zapisu </li><li> Zagwarantowane, że kompilator nie zmieni kolejności operacji **po** `load()` i `store()` </li></ul>
`memory_order_acq_rel` | <ul><li> Do zapisu </li><li> Zagwarantowane, że kompilator nie zmieni kolejności operacji **po** `load()` i `store()` </li></ul> 
`memory_order_seq_cst` | <ul><li> **Domyślny wybór (jeśli nie wybrany inny)** </li><li> Blokowany jednoczesny odczyt i zapis </li></ul>

## Zmienne warunku

### 16. Aktywne czekanie (spinlock)

* Aktywne czekanie (busy waiting) to stan, w którym wątek ciągle sprawdza, czy został spełniony pewien warunek
* Inna nazwa tego problemu to wirująca blokada (spinlock)
* Problem rozwiązuje **zmienna warunku** (condition variable)

```cpp
void saveToFile(StringQueue & sq) {

    ofstream file("/tmp/sth.txt");

    while (file) {
        while (sq.empty()) { /* nop */ }
        
        file << sq.pop() << endl;
    }
}
```

### 17. `std::condition_variable`

`std::condition_variable` | Opis
------------ | -------------
Cechy | <ul><li> Działa tylko z `std::unique_lock` </li><li> Niekopiowalny </li><li> Wymaga `#include <condition_variable>` </li></ul>
Najważniejsze operacje | <ul><li> `wait()` – oczekuje na zmianę / blokuje obecny wątek dopóki nie zostanie on wybudzony </li><ul><li> Wątek który zablokował mutex, trafił na `wait()` ale nie otrzymał ani `notify_one()`, ani `notify_all()` **zwalnia mutex** i jest usypiany. Ponadto, mimo że nie było żadnego `notify()` może się on spontanicznie **wybudzić i (spróbować) zablokować z powrotem mutex by sprawdzić czy był `notify()` oraz (opcjonalnie) czy warunek podany w predykacie został spełniony**</li><li> Wymaga przekazania w argumencie: <ul><li> `std::unique_lock` lub... </li><li> `std::unique_lock` oraz predykat </li></ul></li></ul></li><li> `notify_one()` – wybudza jeden z wątków oczekujących na zmianę <ul><li> Nie mamy kontroli nad tym, który z wątków zostanie powiadomiony  </li><li> Jeśli na zmiennej warunku czeka kilka wątków i każdy ma inny predykat, to jego użycie może spowodować zakleszczenie. Wybudzony może zostać wątek, dla którego warunek nie został spełniony i jeśli żaden inny wątek nie zawoła `nofity_one()` lub `notify_all()` to wszystkie będą czekać </li></ul></li><li> `notify_all()` – wybudza wszystkie wątki czekające na zmianę </li><ul><li> **Preferowanany wybór**  </li><li>  Wątki te mogą konkurować o zasoby </li></ul><li> `wait_for()` - przyjmuje okres czasu po którym naśtąpi wybudzenie </li><ul><li> Opcjonalnie zwraca powód wybudzenia (czy z powodu timeout'u lub nie) </li></ul><li> `wait_until()` - przyjmuje punkt w czasie, w którym nastąpi wybudzenie </li><ul><li> Opcjonalnie zwraca powód wybudzenia (czy z powodu timeout'u lub nie) </li></ul></ul>

* Jeśli wywołamy którąkolwiek z funkcji `notify()`, a żaden wątek nie czeka (`wait()`) to "stracimy" takiego notify'a.

### 18. `std::condition_variable_any`

`std::condition_variable_any` | Opis
------------ | -------------
Cechy | <ul><li> Działa z każdym rodzajem blokad </li><li> Te same właściwości co `std::condition_variable` </li></ul>

### 19. Zagrożenia dla `std::condition_variable` / `std::condition_variable_any`

Zagrożenie | Opis
------------ | -------------
Fałszywe przebudzenie (spurious wakeup) | <ul><li> Wątek czekający na zmiennej warunku cyklicznie co pewien okres czasu wybudza się i sprawdza czy nie przyszła notyfikacja</li><li> W celu oczekiwania na zmiennej warunku wymagana co najmniej blokada `std::unique_lock`, gdyż podczas uśpienia wątek ją odblokowuje, a gdy wybudza się, aby sprawdzić notyfikację blokuje ją ponownie na chwilę, po czym znów ją odblokowuje i śpi dalej </li><li> Predykat dodany do funkcji `wait()` zapobiega fałszywym przebudzeniom, gdyż dodaje dodatkowy warunek, który musi być spełniony, aby wątek się wybudził </li></ul>
Utracona notyfikacja (lost wakeup) | <ul><li> Jeśli notyfikacja została wysłana zanim wątek oczekiwał na zmiennej, to jest ona utracona i nie wybudzi ona wątku </li><li> Problem można obejść, gdy pojawi się fałszywe przebudzenie </li><li> Jeśli wątek oczekiwał na zmiennej warunku z predykatem, to predykat musi być spełniony, inaczej fałszywe przebudzenie nie nastąpi </li></ul>

## Komunikacja jednokierunkowa (`std::future` i `std::promise`)

### 20. Opis

* `std::future` i `std::promise` razem tworzą jednokierunkowy kanał komunikacji między **dwoma wątkami**
* Wątek, który "ma coś zrobić" jako argument oprócz lambdy dostaje też `std::promise`
* Wątek, który ma odebrać wynik obliczeń wywołuje `future.get()`

```cpp
std::promise<int> promise; // typ wyniku
std::future<int> future = promise.get_future(); 
// tworzymy future przez wywołanie get_future() na std::promise
// w ten sposób tworzy się kanał komunikacji
// kolejne wywolanie promise.get_future() rzuci wyjątek

auto function = [](std::promise<int> promise
{
    promise.set_value(10;)
    // ustawiamy promise jakąś wartość
}

std::thread t(function, std::move(promise));
// do osobnego wątku przekazujemy lambdę z promise'm

std::cout << future.get() << std::endl;
// inny wątek woła get() by wyłuskać wartość
// kolejne wywołanie get() rzuci wyjątek

t.join();
```

### 21. Funkcje `std::future`

Funkcja | Opis
------------ | -------------
`get()` | <ul><li> **Służy do synchronizacji wątków** tj. jeden wątek nie pójdzie dalej tylko poczeka do momentu aż inny wątek czegoś nie zrobi<ul><li> `get()` czeka na inny wątek **i pobiera jego wynik** </li></ul></li><li> Można wywołać tylko raz </li><ul><li> Kolejne wywołanie rzuci wyjątek </li></ul></ul>
`valid()` | <ul><li> Zwraca `true` jeśli można go użyć (tzn. można na nim wywołać `get()` lub `wait()` (innymi słowy czy `std::future` nie został już "zużyty")</li></ul>
`wait()` | <ul><li> **Służy do synchronizacji wątków** tj. jeden wątek nie pójdzie dalej tylko poczeka do momentu aż inny wątek czegoś nie zrobi<ul><li> `wait()` nie pobiera wartości tylko czeka aż będzie dostępna </li></ul></li><li> Można wywołać wielokrotnie </li></ul>

### 22. Obsługa wyjątków w `std::promise`

* Na `std::promise` oprócz `set.value()` można wywołać `set.exception()`
* Wywołanie `get()` na "drugim" wątku rzuci wyjątek

```cpp
promise.set_exception(std::make_exception_ptr(e));

try {
// ...
} catch (...) {
promise.set_exception(std::current_exception());
}
```

### 23. `std::shared_future`

* Jeden wątek nadaje, ale wiele odbiera
    * Obiekt `std::promise` tworzymy tylko jeden
* Jedyna różnica w zastosowaniu to taka że zamiast `std::future<int> f = promise.get_future()` piszemy `std::shared_future<int> f = promise.get_future().share()`
    * Każdy wątek powinien utworzyć swój własny obiekt `shared_future`
* Kopiowalny
* Przenoszalny

## Zadania asynchroniczne (`std::assync`)

### 24. Opis

* `std::async` to wysokopoziomowe rozwiązanie, które automatycznie zarządza wywołaniami asynchronicznymi z podstawowymi mechanizmami synchronizacji
* Przykazując funkcję do `std::assync` zwróci on obiekt `std::future` za pomocą którego można się dostać do jego rezultatu (jak tylko będzie on dostępy)
    * Wywołując `get()` przed tym jak zostanie "obliczony" wynik, wątek poczeka na niego...
* Obsługa wyjątków przez `std::promise` i `std::future`
* Wymaga `#include <future>`
```cpp
std::future<int> f = std::assync(function)
std::cout << f.get() << std::endl;
```

### 25. Polityki uruchamiania

Przykład wykorzystania:

```cpp
auto f2 = async(launch::async, []{
        cout << "f2 started\n";
        this_thread::sleep_for(1s);
```

Polityka | Opis
------------ | -------------
`std::launch::async` | <ul><li> Wywołanie asynchroniczne w osobnym wątku</li></ul>
`std::launch::deferred` | <ul><li> Wywołanie funkcji (i obliczenie rezultatu) następuje dopiero po wywołaniu `get()` lub `wait()` </li><li> Wątek wywołujący `get()` lub `wait()` czeka na wątek zwracający wartość (punkt synchronizacji) </li></ul>
`std::launch::async::deferred` | <ul><li> Wywołanie asynchroniczne w osobnym wątku</li></ul>
Bez *launch policy* | <ul><li> **Undefined behaviour** (od C++14 - [czytaj](https://en.cppreference.com/w/cpp/thread/async)) </li></ul>

```cpp
#include <future>
#include <vector>
#include <iostream>
#include <chrono>
using namespace std;

int main()
{
    auto f1 = async([] {
        cout << "f1 started\n";
        this_thread::sleep_for(1s);
        return 42;
    });
    cout << "f1 spawned\n";
    
    auto f2 = async(launch::async, []{
        cout << "f2 started\n";
        this_thread::sleep_for(1s);
        return 2 * 42;
    });
    cout << "f2 spawned\n";
    
    auto f3 = async(launch::deferred, []{
        cout << "f3 started\n";
        this_thread::sleep_for(1s);
        return 3 * 42;
    });
    cout << "f3 spawned\n";

    cout << "Getting f1 result\n";
    auto v1 = f1.get();
    cout << "Got f1 result\n";
    
    cout << "Getting f2 result\n";
    auto v2 = f2.get();
    cout << "Got f2 result\n";
    
    cout << "Getting f3 result\n";
    auto v3 = f3.get();
    cout << "Got f3 result\n";
    
    vector<int> numbers = { v1, v2, v3 };
    for (const auto & item : numbers)
        cout << item << '\n';
    
    return 0;
}

```
Wyjście:
```bash
>> f1 spawned
>> f1 started
>> f2 spawned
>> f3 spawned
>> Getting f1 result
>> f2 started
>> Got f1 result
>> Getting f2 result
>> Got f2 result
>> Getting f3 result
>> f3 started
>> Got f3 result
>> 42
>> 84
>> 126
```

### 26. Problem domyślnej polityki

Nie można sprawdzić w jaki sposób future (`std::async`) został uruchomiony ale korzystając z `wait_for()` i tego że zwraca 1 z 3 statusów:
* `future_status::deferred`
* `future_status::ready`
* `future_status::timeout`

... można tak zdobyć wynik:

```cpp
#include <iostream>
#include <future>
using namespace std;

void f() {
  this_thread::sleep_for(1s);
}

int main() {
    auto fut = async(f);

    if (fut.wait_for(0s) == future_status::deferred) {
        cout << "Scheduled as deffered. Calling wait() to enforce execution\n";
        fut.wait();
    } else {
        while (fut.wait_for(100ms) != future_status::ready) {   
            cout << "Waiting...\n";
        }
        cout << "Finally...\n";
    }
}
```

### 27. `std::packaged_task`

* `std::packaged_task` nie wykonuje się od razu (w odróżnieniu od `std::async`), to użytkownik decyduje kiedy to ma się wykonać
* Przydatne jeśli chcemy do `std::async` przekazać parametry, których jeszcze nie mamy albo inny wątek/funkcja go oblicza
    *  Wtedy wątek tworzymy dopiero jak już mamy obliczone parametry

```cpp
auto globalLambda = [](int a, int b) {
    std::cout << "globalLambda:\n";    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return std::pow(a, b); 
};

// LOKALNE WYWOŁANIE

void localPackagedTask() {
    std::cout << "\nlocalPackagedTask:\n";
    std::packaged_task<int(int,int)> task(globalLambda);
    auto result = task.get_future();
    
    std::cout << "before task execution\n";
    task(2, 9);
    std::cout << "after task execution\n";
 
    std::cout << "getting result:\t" << result.get() << '\n';
}

// WYWOŁANIE W INNYM WĄTKU

void remotePackagedTask() {
    std::cout << "\nremotePackagedTask:\n";
    std::packaged_task<int(int,int)> task(globalLambda);
    auto result = task.get_future();
    
    std::cout << "before task execution\n";
    std::thread t(std::move(task), 2, 9);
    std::cout << "after task execution\n";

    t.detach(); // detach żeby było asynchronicznie (nie join())

    std::cout << "getting result:\t" << result.get() << '\n';
}

// TO SAMO TYLKO KORZYSTAJĄC Z ASYNC

void remoteAsync() {
    std::cout << "\nremoteAsync:\n";
    auto result = std::async(std::launch::async, globalLambda, 2, 9); 
    std::cout << "getting result:\t" << result.get() << '\n';
}

int main() {
    localPackagedTask();
    remotePackagedTask();
    remoteAsync();
}
```
