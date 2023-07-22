

## Uruchamianie testów musi być proste

* ... inaczej nikt nie będzie ich używał
* Uruchamianie jedną komendą
* Najpopularniejsze biblioteki do testowania: Google Test, Catch2, doctest, Boost.Test
* ctest to taki CMake'owy uruchamiacz testów (działa z każdym frameworkiem)
    * Wystarczy dodać do CMakeLists add_test

## Korzystaj z automatycznego budowania

GitLab, GitHub Actions, Appveyor, Travis

* Szybsze budowanie i testownie na wielu platformach
* Oddzielne testowanie wersji Debug i Release
* Testowanie konkretnych konfiguracji, na różnych kompilatorach
    * Testowanie w kontekście kompilowania i uruchamiania, a nie testowanie jako takiego

## Korzystaj z rygorystyczych flag kompilatora

* -Wall i -Wextra to tylko podstawowe flagi
* Rekomendowane użcie -Wpedantic (gcc/clang) lub /permissive- (MSCS)
* -Werror - wszystkie warningi traktowane są jak errory
* Opis flag kompilacji gcc: https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html

## Korzystaj ze statycznej analizy kodu

* Analiza kodu przed kompilacją i uruchomieniem
* cppcheck oraz clang-tidy (zaszywa się je w CMakeu)

## Korzystaj z sanitizeroóœ

* Sanitizers działją w runtime, są one wbudowane w GCC, clanga i MSVC

* Address Sanitizer (ASan)
* Undefined Behavior (UBSan)
* Thread
* DataFlow

* Rekomendowane użycie przynajmniej ASan i UBSan
* W przypadku wykrycia nieprawidłowego zachowania, sanitizer generuje raport i (często) sugestie jak naprawić problem
* Przykład użycia: `gcc -fsanitize=address,undefined <filetocompile>`
* Sanitizery muszą być też być "obecne" podczas linkowania

## Naucz się innego języka 

* Korzystającego z innego paradygmatu (funkcyjny na przykład), z inną składnią

## Oznacz jako const wszystko co nie jest constexpr

STRONA 18