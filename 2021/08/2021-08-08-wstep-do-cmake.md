---
layout: post
title: Wstęp do CMake
categories: [post]
date: 2021-08-08
permalink: /wstep-do-cmake
nav_exclude: true
---

# Wstęp do CMake
{: .no_toc }

<details open markdown="block">
  <summary>
    Spis treści
  </summary>
  {: .text-delta }
1. TOC
{:toc}
</details>

---

CMake to narzędzie do automatyzacji procesu budowania programów napisanych w C/C++ poprzez generowanie plików `Makefile` (`CMake` sam w sobie nie jest system budowania). Nazwa `CMake` to z angielskiego *cross-platform Make*.

## Główne cechy

* Domyślna konfiguracja w pliku `CMakeLists.txt`
  * Można podać inny, ale wymaga to podania dodatkowej flagi przy budowaniu
* Dobrze napisany `CMakeLists.txt` daje niezależność od platformy na której budowana jest aplikacja
* Jeśli nie było zmian w jakichś plikach - szybsza ponowna kompilacja

---

## Minimalny CMakeLists

```cmake
cmake_minimum_required(VERSION 3.10)
project(ProjectName)

add_executable(<NAZWA_PLIKU_WYNIKOWEGO> main.cpp)
```

---

## Budowanie

```sh
$ mkdir <KATALOG>
$ cd <KATALOG>
$ cmake ..          // generowanie plików Makefile
$ cmake --build .   // budowanie
```

* Budowanie przy pomocy `cmake --build .` jest uniwersalne, ale można użyć `make` (lub `make -j`) jeśli wiemy, że budujemy na podstawie plików `Makefile`<br>
* Skrócona wersja bez konieczności wchodzenia do katalogu:

```sh
$ cmake -B <KATALOG>
$ cmake --build <KATALOG> --parallel
```

---

## Tworzenie zmiennych

Zastosowanie zmiennych umożliwia:
* Wielokrotne wykorzystanie tych samych nazw w projekcie
* Uniknięcie duplikacji w przypadku podawania tych samych plików źródłowych lub flag kompilacji dla wielu plików binarnych

**UWAGA!** W przypadku zapisania do zmiennej wszystkich plików źródłowych, a następnie podanie ich w `add_executable`, nie unikniemy wielokrotnej kompilacji tych samych plików. Lepszym wyborem jest stworzenie biblioteki, a następnie zlinkowanie jej z plikami wykonywalnymi.

```cmake
# Konwencja - UPPERCASE_WITH_UNDERSCORE
set(VARIABLE value)

# Przykład
set(NAME TheGreatestProject)
```

* `project(ProjectName)` tworzy zmienną `PROJECT_NAME` o wartości `ProjectName`
* Do zmiennych odwołujemy się poprzez `${NAZWA_ZMIENNEJ}`
* Czasem `CMake` nie wykrywa wersji kompilatora i trzeba ją podać samodzielnie

```cmake
set(CMAKE_CXX_COMPILER g++-10)
# Niezalecane jest nadpisywanie predefiniowanych zmiennych w ten sposób
```

---

## Tworzenie binarki (plik aplikacji lub testy)

```cmake
add_executable(<name> [source1] [source2 ...])

# Przykład
add_executable(${NAME} main.cpp)
```

* W `add_executable` nie można podać `*.cpp` jako "wszystkie pliki `cpp`"
* Jeśli pliki `*.hpp` są w innej lokalizacji to trzeba dodać `include_directories(inc1/ inc2/)`
* Więcej informacji w [dokumentacji](https://cmake.org/cmake/help/latest/command/add_executable.html)

---

## Tworzenie bibliotek

* Biblioteka to zestaw wielu plików `cpp` bez funkcji `main()` (z tego powodu biblioteki nie można uruchomić)

```cmake
add_library(${PROJECT_NAME}-lib [STATIC | SHARED | MODULE] functions.cpp modules.cpp)
```

* `STATIC` oznacza, że biblioteka jest kopiowana do pliku wykonywalnego

Dla przypomnienia:

**Biblioteka statyczna**

* Używana przez program podczas procesu kompilacji
* Wszystkie potrzebne symbole są w czasie kompilacji kopiowane do jego z plików, pozwalając programowi na samodzielne działanie (**zwiększone zapotrzebowanie na pamięć**)
* Jeśli jakiekolwiek zmiany zostaną wprowadzone w bibliotece po czasie kompilacji, program ten będzie musiał zostać ponownie skompilowany w celu aktualizacji
* Rozszerzenie `*.a`

**Biblioteka dynamiczna**

* Program wymaga tylko referencji do biblioteki (**oszczędność pamięci**)
* Jeśli biblioteka nie jest dostępna, możliwe że program nie będzie działał poprawnie
* W przypadku zmian w bibliotece nie jest wymagana powtórna kompilacja (linkowanie odbywa się w czasie działania programu)
* Rozszerzenie `*.so`

---

### Linkowanie bibliotek
{: .no_toc }

* Biblioteki linkujemy z binarką (**lub inną biblioteką**) poprzez:

```cmake
target_link_libraries(<target> ... <item>... ...)
```

* `target` - nazwa z `add_executable`
* `<item>` - konkretna biblioteka

Przykład:

```cmake
add_library(lib STATIC functions.cpp modules.cpp)
add_executable(main main.cpp)
add_executable(ut tests.cpp)
target_link_libraries(main lib)
target_link_libraries(ut lib)
```

---

## Podsumowanie

```cmake
add_library(${PROJECT_NAME}-lib STATIC functions.cpp modules.cpp)
add_executable(${PROJECT_NAME} main.cpp functions.cpp modules.cpp)
add_executable(${PROJECT_NAME}-ut test.cpp functions.cpp modules.cpp)
```

---

## Dodawanie flag kompilacji

* `target_compile_option` pozwala na ustawianie różnych flag dla różnych binarek
    * Flagi kompilacji można wrzucić też najpierw do zmiennej, a później zmienną do `target_compile_options`
* `add_compile_options()` umożliwia ustawienie flag dla wszystkich plików wynikowych zdefiniowanych w obrębie danego pliku `CMakeLists.txt` (niezalecane)
* **Do tworzenia bibliotek też można ustawiać flagi kompilacji**

```cmake
target_compile_options(<target> [BEFORE]
                                <INTERFACE|PUBLIC|PRIVATE> [items1...]
                                [<INTERFACE|PUBLIC|PRIVATE> [items2...]
                                ...])
# Przykład
add_executable(${PROJECT_NAME} main.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)                                
```

---

## Włączanie standardu C++17

```cmake
# Przykład 1 - może nie działać z MVC
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Przykład 2 - można ustawić inny standard dla każdego targetu
set_target_properties(${PROJECT_NAME} PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED ON)

# Przykład 3
add_executable(${PROJECT_NAME} main.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
```

---

## Budowanie w trybie Debug / Release

```cmake
# Debug
> cmake -D CMAKE_BUILD_TYPE=Debug ..

# Release
> cmake -D CMAKE_BUILD_TYPE=Release ..
```

* Wersja Debug używa flag `-O0` (optymalizacja czasu kompilacji) oraz z `-g` (z symbolami do debugowania)
* Wersja Release używa flagi `-O3` (optymalizacja wielkości kodu oraz czasu wykonywania)
* Podczas uruchamiania CMake'a można nadpisać każdą flagę poprzez:

```sh
$ mkdir buildDebug
$ cd buildDebug
$ cmake -DCMAKE_BUILD_TYPE=Debug ..
$ cmake --build
```

* Jeśli chcemy wspierać budowanie w dwóch trybach: Debug i Release zalecane jest stworzenie dla nich oddzielnych katalogów z rezultatami budowania

---

## CTest

* `CTest` to moduł `CMake` - aplikacja do uruchamiania testów
* Normalnie należy uruchomić binarkę z testami, `CTest` umożliwia uruchomienie wszystkich testów jedną komendą - `ctest`

```cmake
enable_testing()
add_test(NAME <name> COMMAND <command> [<arg>...])

# Przykład
enable_testing()
add_test(NAME someTests COMMAND ./${PROJECT_NAME}-ut)
```

### Uruchamianie testów z CTest
{: .no_toc }

* `ctest` - uruchomienie wszystkich testów (ze skróconymi wynikami)
* `ctest -V` - uruchomienie wszystkich testów + szczegółowy output z testów
* Więcej informacji po wpisaniu `ctest --help`

---

## Bibliografia

- [Coders School - Moduł Cmake](https://github.com/coders-school/cmake)
- [Mateusz Szychowski - CMake - from zero to something](https://muttleyxd.github.io/)
- [Introduction to Modern CMake](https://cliutils.gitlab.io/modern-cmake/)
- [Dokumentacja CMake](https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html)