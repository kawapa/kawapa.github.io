


# 

Iterator - obiekt, który wskazuje na konkretny element w kontenerze.
* W zależności od jego typu - można na nim wykonywać różne operacje
* Iterator to także wzorzec projektowy, który określa obiekt umożliwiający poruszanie się po jakiejś kolekcji


Iteratory na stałe
* Nie można modyfikować danych wskazywanych przez iterator


Hierarchia iteratorów

Od C++17 jest 6 typów iteratoróœ
Od C++20 ta wcześniejsza hierarchia została określona jako legacy, obecnie korzysta się z konceptów lub traitów (w zależności od tego co nam dany itrator umożliwia)


(Każdy kolejny typ itratora zawiera poprzednie tj. udostępnia swoją funkcjonalność + funkcjonalność "poprzedników".


1. Input
2. Output
3. Forward
4. Bidirectional
5. Random access
6. Contiguous


### Input iterator

1. Przykład std::istream (taki jak std;:cin)

* Raz wczytane dane znikają, nie możemy ich ponownie odczytać
* Możliwość przejścia 