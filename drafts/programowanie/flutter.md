#





## Instalacja rozszerzeń

* Flutter (zawiera wtyczkę obługującą język Dart)
* [FF] Flutter Files - wspomaga generowanie template'ów, które służą do zarządzania stanem aplikacji
* ADB Interfae for VSCode - jeśli używasz fizycznego urządzenia i obługujesz go terminalem, wtyczka umożliwia wydawanie komend bezpośrednio z VSC
* bloc - auomatycznie generuje boilerplate wymagany w każdym Blocs'u i Cubit'sie
* Build Runner - wtyczka ułatwiająca generowanie kodu w Dart'cie (dodaje skórty klawiszowe i funkcje w VSC)
* Dart Data Class Generator - generowanie definicji klas, której główna funkcją jest przetrzymywanie danych używanych przez inne klasy
* dart-import
* Error Lens
* Flutter Intl
* Freezed
* freezed_bloc
* Json to Dart Model
* Path Intellisense
* Pubspec Assist
* REST Client / Thunder Client
* TabOut
* Todo Tree
* Version Lens
* YAML

## Zmienne const / final / var

Podstawowymi typami zmiennych są typy określające czy daną zmienną można zmieniać po przypisaniu są:
* `var` - typ obiektu jest dedukowany przez kompilator, ale jest on stały - nie da się przypisać wartości innego typu
* `dynamic`
    * kolejne przypisania do zmiennej zezwalają na zmianę typu
    *  Sam w sobie nie jest typem. Wykorzystanie słowa `dynamic` wyłącza sprawdzanie typów przez kompilator. Dobra praktyka - wszędzie gdzie znamy typ powinniśmy korzystać z typu `Object`.
    * Jedyne praktycznie wykorzystanie to sytuacja jeśli jakieś dane pobieramy z internetu i nie wiemy jakiego one są typu.
* `Object` - oznacza nieokreślony typ

Do tworzenia stałych służą słowa kluczowe:
* final - stała na etapie działania programu (może być pusta przy uruchomieniu aplikacji, ale po pierwszym przypisaniu nie może być już zmieniona)
* const - stała na etapie kompilacji (musi być zainicjalizowana przed kompilacją)


* Właściwość `runtimeType` zwraca typ obiektu
```dart
var p1 = 1;
var p2 = "Text";

print(p1.runtimeType);
print(p2.runtimeType);
```

## Typy

### Liczbowe

* Dart jest językiem z inferencją typu (sam rozpoznaje typ obiektu)
* Dobrą praktyką jest jawne podawanie typów 

`num` - liczba całkowite i zmiennoprzecinkowe
`int` - liczby całkowite
`double` - liczby zmiennoprzecinkowe lub całkowite, które chcemy żeby zostały skonwertowane do zmiennoprzecinkowej
`bool` - 
`String` - tekst, można używać zarówno `" "` oraz `' '`



## Testowanie

assert([WYRAŻENIE])