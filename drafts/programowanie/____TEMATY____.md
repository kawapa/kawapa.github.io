* Operacje bitowe
    * https://www.youtube.com/watch?v=KXwRt7og0gI
    * https://www.youtube.com/watch?v=HoQhw6_1NAA
* Zasada GRASP
* Cppcheck
* clang-tidy
    * https://www.danielsieger.com/blog/2021/12/21/clang-tidy-cmake.html
* Boost DI
    * https://boost-ext.github.io/di/tutorial.html
    * https://www.youtube.com/watch?v=8HmjM3G8jhQ
    * https://www.youtube.com/watch?v=yVogS4NbL6U
* Implementacja różnych operatorów
    * Których nie można przeciążyć?
* Kata
    * https://github.com/kjendrzyca/TDD-Katas
    * https://github.com/gamontal/awesome-katas
    * http://codekata.com/
* Object Calisthenics
    * https://williamdurand.fr/2013/06/03/object-calisthenics/
    * https://noti.st/pawel-lewtak/O3UGnP#sKr0Ow1
    * https://www.cs.helsinki.fi/u/luontola/tdd-2009/ext/ObjectCalisthenics.pdf
* Refaktoryzacja
    * https://blog.ndepend.com/code-smell-primitive-obsession-and-refactoring-recipes/
* Wzorzec Adapter
    * https://caiorss.github.io/C-Cpp-Notes/cpp-design-patterns.html#org356cb36
    * https://www.youtube.com/watch?v=j9arNRRoPe8
    * https://pl.wikipedia.org/wiki/Adapter_(wzorzec_projektowy)#:~:text=Do%20stworzenia%20adaptera%20klasowego%20wykorzystywane,przekierowywane%20do%20bazowej%20klasy%20adaptowanej.
    * https://en.wikipedia.org/wiki/Adapter_pattern
    * http://ima.udg.edu/~sellares/EINF-ES1/AdapterToni.pdf
    * https://stackoverflow.com/questions/5467005/adapter-pattern-class-adapter-vs-object-adapter
    * https://stackoverflow.com/questions/9978477/difference-between-object-adapter-pattern-and-class-adapter-pattern
* Notatki z wykładu Anthony'ego Williamsa - https://www.youtube.com/watch?v=iUKxvEg0zdk
* https://www.codeproject.com/Articles/1169105/Cplusplus-std-thread-Event-Loop-with-Message-Queue
    * https://github.com/endurodave/StdWorkerThread
* Looper: https://m-peko.github.io/craft-cpp/posts/expanding-on-standard-threads/
* Dobre praktyki / błędy początkujących
    * https://www.youtube.com/watch?v=i_wDa2AS_8w
* Testowanie
    * Film coders school
        * https://builtin.com/software-engineering-perspectives/mock-vs-stub
    * Google Test / Google Mock tutoriale
        * https://stackoverflow.com/questions/31989040/can-gmock-be-used-for-stubbing-c-functions
        * https://google.github.io/googletest/gmock_cook_book.html
        * https://alexott.net/en/cpp/CppTestingIntro.html
        * https://www.samouczekprogramisty.pl/testy-jednostkowe-z-uzyciem-mock-i-stub/
        * 10 minutowy film o GMock
        * https://m.youtube.com/watch?v=vxCH4AuVRgo
        * https://infotraining.bitbucket.io/cpp-tdd/index.html
* Wyjątki
    * https://www.youtube.com/watch?v=0ojB8c0xUd8
    * https://medium.com/@manojddesilva/some-useful-facts-to-know-when-using-c-exceptions-2b614492be0
* 12 przykładów jak korzystać wydajnie z biblioteki STL oraz połączyć ją z programowaniem funkcyjnym. Omówione zostaną także pułapki wydajnościowe, które wbrew naszym oczekiwaniom mogą spowolnić, a nie przyspieszyć wykonywanie programu.
* Fold expression
* Biblioteka filesystem - jak napisać kod, który może operować na plikach/katalogach na różnych systemach (Linux/MacOS/Windows)
* Nowości dodane w C++20 (span/multiple destructors/operator <=>/new sytax for lambdas/designed initializer/bit functions/Uniform erasure/consteval/etc...).
* Integracja zewnętrznych bibliotek na przykładzie boost oraz ranges_v3. Jak poprawnie dodać je do projektu, jak z nich korzystać (boost ma całą masę bibliotek wykorzystywanych przy programowaniu sieciowym natomiast ranges_v3 zawiera szereg metod niedostępnych w standardzie C++20).
* Jak pisać wydajne i praktyczne funkcje, które wykonywane są w czasie kompilacji. Zwieńczeniem tego będzie projekt, w którym dokonamy parsowania dowolnie złożonych operacji matematycznych. Wykorzystamy tu polimorfizm, dziedziczenie, alokację itd... a to wszystko w czasie kompilacji! Tak da się to zrobić, jak się Wie jak :)
* Jak zabezpieczyć swój kod przed niewłaściwym użyciem na przykładzie nowego mechanizmu dodanego w C++20, czyli koncepty.
* Jak wydajne i wygodnie operować na plikach. Jak zapisać obiekt do pliku, jak go wczytać. Jak zrobić to dla całych kolekcji, wykorzystując jedynie iteratory oraz algorytm std::copy. Dodatkowo pokaże Wam, jak można wygodnie pisać metody typu 'pretty print'.
* Jak stworzyć własny logger, który bezpiecznie zaloguje nam dane do pliku w środowisku wielowątkowym z uwzględnieniem informacji o nazwie funkcji, parametrach (w tym także szablonu) numerze linii, czasie oraz numerze wątku.
* Bufor cykliczny, jak zaimplementować i po co nam taki twór (pokaże też jak wykorzystać gotową implementację z biblioteki boost).
* Programowanie wielowątkowe/ wzorzec producer-consumer/ programowanie wysokopoziomowe przy użyciu async i package_task/ Jak napisać pule wątków/ Jak zrównoleglić algorytmy/
* Na sam koniec zrobimy duży projekt wielowątkowej aplikacji, która samodzielnie będziecie mogli rozwijać przez kolejne tygodnie/miesiące. Jej zadaniem będzie strumieniowanie danych na wiele odbiorników przy wykorzystaniu protokołu UDP.
