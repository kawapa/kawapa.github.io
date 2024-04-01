---
layout: post
title: Wzorce projektowe - Singleton
permalink: /singleton
date: 2024-04-01
draft: true
---

# Wzorce projektowe - Singleton
{: .no_toc }

<details closed markdown="block">
  <summary>
    Spis treści
  </summary>
  {: .text-delta }
1. TOC
{:toc}
</details>

---

## Kiedy używać

* Kiedy w programie potrzebna jest tylko jedna instancja danej klasy (wszystkie klasy korzystają z tego jednego obiektu)
  * Przykłady:
    * Dostęp do bazy danych
    * Fabryka obiektów
    * Jakakolwiek inna klasa, której stworzenie obiektu bądź równoległe używanie więcej niż jednego jest kosztowne pod względem zasobów

### Przykładowe implementacje

* Zablokuj tworzenie i robienie kopii
  * Prywatny konstruktor (nie można wywołać `new`)
  * Usuń konstruktor kopiujący oraz kopiujący operator przypisania (`delete`)
* Utworzyć statyczną metodę `getInstance()` zwracająca referencję (do statycznego obiektu) lub wskaźnik (do obiektu utworzonego na stercie) utworzonego wewnątrz metody `getInstance()`

#### Implementacja 1

```cpp
class Singleton
{
protected:
    Singleton()
    {
    }

public:
    Singleton(const Singleton &other) = delete;
    void operator=(const Singleton &other) = delete;

    static Singleton& getInstance();
};

Singleton& Singleton::getInstance()
{
    // 1) lazy initialization
    // 2) thread-safe
    static Singleton singleton;
    return singleton;
}
```

#### Implementacja 2

```cpp
class Singleton
{
private:
    static inline std::unique_ptr<Singleton> m_instance;
    static inline std::mutex m_mutex;

protected:
    Singleton()
    {
    }

public:
    Singleton(const Singleton &other) = delete;
    void operator=(const Singleton &other) = delete;

    static Singleton* getInstance();
};

Singleton* Singleton::getInstance()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_instance == nullptr)
    {
        m_instance = std::make_unique<Singleton>();
    }
    return m_instance.get();
}
```

### Problemy ze wzorcem Singleton

* Problematyczne jest testowanie klas/metod korzystających z Singleton'a (**jak przetestować klasę UserFinder z przykładu poniżej?**)
  * Nie można na potrzeby testów podmienić klasy zapewniającej na przykład dostęp do bazy inną klasą (testowana klasa jest silnie sprzeżona z Singleton'em)
  * Jedyne co można zrobić to napisać test, podczas którego nastąpi połączenie z prawdziwą bazą - **taki test nie jest już testem jednostkowym, a testem integracyjnym**

```cpp
class SingletonDatabase {
    SingletonDatabase() {
        std::ifstream ifs("./users.txt");

        std::string s, s2;
        while (getline(ifs, s)) {
            getline(ifs, s2);
            int pop = boost::lexical_cast<int>(s2);
            users[s] = pop;
        }
    }

    std::map<std::string, int> users;

public:
    SingletonDatabase(SingletonDatabase const&) = delete;
    void operator=(SingletonDatabase const&) = delete;

    static SingletonDatabase& get() {
        static SingletonDatabase db;
        return db;
    }

    int getUserId(const std::string& mail) {
        return users[mail];
    }
};

class UserFinder {
public:
    int getUserId(const std::string& mail) {
        return SingletonDatabase::get().getUserId(mail);
    }
};
```

### Rozwiązanie problemu

Zastosowanie Dependency Injection (DI):
1. Utwórz interfejs, który implementuje Singleton (metody czysto wirtualne zwracające konkretne wartości zamiast statycznego `getInstance()` (nie można dziedziczyć statycznych pól klasy))
   * Klasy wymagające dostępu do danego zasobu (w zastosowanym przykładzie - do bazy danych) otrzymają w konstruktorze referencję/wskaźnik do klasy wykonującej zapytania do bazy
2. Przygotowując klasę do testów, przekaż do konstruktora zaślepkę/mocka która będzie zwracać w testach z góry określone wartości



## Inne ciekawe

> When discussing which patterns to drop, we found that we still love them all. (Not really—I'm in favor of dropping Singleton. Its use is almost always a design smell). Erich Gamma

## 5. Bibliografia

- [Dmitri Nesteruk - Design Patterns in Modern C++ (Udemy)](https://www.udemy.com/course/patterns-cplusplus/)




#include <boost/lexical_cast.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class SingletonDatabase {
    SingletonDatabase() {
        std::ifstream ifs("./users.txt");

        std::string s, s2;
        while (getline(ifs, s)) {
            getline(ifs, s2);
            int pop = boost::lexical_cast<int>(s2);
            users[s] = pop;
        }
    }

    std::map<std::string, int> users;

public:
    SingletonDatabase(SingletonDatabase const&) = delete;
    void operator=(SingletonDatabase const&) = delete;

    static SingletonDatabase& get() {
        static SingletonDatabase db;
        return db;
    }

    int getUserId(const std::string& mail) {
        return users[mail];
    }
};

class UserFinder {
public:
    int getUserId(const std::string& mail) {
        return SingletonDatabase::get().getUserId(mail);
    }
};

main() {
    // std::string city = "abc@yahoo.com";
    // std::cout << SingletonDatabase::get().getUserId(city)
    //           << std::endl;

    UserFinder uf;
    std::cout << uf.getUserId("abc@yahoo.com");

    return 0;
}