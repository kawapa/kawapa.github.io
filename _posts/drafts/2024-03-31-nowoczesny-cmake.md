---
layout: post
title: Nowoczesny CMake
date: 2024-04-01
permalink: cmake
draft: true
---

W każdym katalogu musi być CMakeLists.txt

CMakeLists na najwyższym poziomie:

* Jakie ma dodać katalogi
* Jaki standard
* Wszelkie ogólne rzeczy na najwyższym poziomie abstracji, na przykład sanitizery.

---

Zaciaganie gtesta
1. Git clone i zaciaganie sciezki
2. GIt clone do katalogu projektu
3. uzycie submodule gitowych
4. W Cmake'u uzyc funkcji sciagania zewnetrznych projektow (ExternalProject_Add)

**Od Sep 2019 jest FetchContent module zamiast ExternalProject_ Add ** 

Najlepsze 4: Trudne ale lepsze bo nie trzymasz tego w swoich zrodlach, nie musisz konfigurowac gita - masz wszystko zaszyte w CMakeu


---

Na najwyzszym poziomie projektu dodatkowy katalog "cmake" 
* Wszelkie konfiguracje, gtest, code-coverage, tworzenie dokumentacji
* Tworzac target dokumentacji i w katalogu budowania wpisujesz "make documentation" - cmake wygeneruje np. html-a ...

---

gtest.cmake - plik w którym zamieszczona jest komenda, to co ma byc wykonane (TO CO MA ZROBIĆ)

gtest.in - plik dla komendy (nazwa.cmake (w tym przypadku gtest.cmake)) (JAK MA TO ZROBIĆ)

Konfiguracja gtest.cmake

configure_file(<PLIK_WEJSCIOWY> <PLIK_WYJSCIOWY>)

configure_file(${CMAKE_SOURCE_DIR}/cmake/gtest.in ${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt)

execute_process - CMAKe może wykonać komende Linuxowa/Windowsowa



...

mkdir build
cd build
cmake ..

To co się stało:
* clone gtest gmock
* utworzył Makefile - bedzie biblioteka add, bedzie plik wykonywalny AddUt, z takimi zaleznosciami


---

gtest wymaga biblioteki lpthreads dlatego w głównym CMAKE

find_package(Threads REQUIRED)

* Cmake sam poszuka biblioteki w systemie




make Add
make AddUt


${CMAKE_SOURCE_DIR} - najwyższy katalog (root)
${CMAKE_CURRENT_SOURCE_DIR} - bieżacy katalog


cd ./tests/add
ctest