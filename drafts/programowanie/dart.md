#

Typ `dynamic` pozwala na zmianę typu obiektu przy kolejnych przypisaniach
`dynamic` sam w sobie nie jest typem - to wyłączenie sprawdzania typów
Jeśli chcemy mieć zmienną o "zmiennym typie" (ale ten typ będzie zmieniał się zawsze w obrębie typów języka Dart) - **zalecane jest korzystanie z typu `Object`**
`dynamic` powinien być wykorzystywany tylko z konieczności, na przykłąd jeśli dostajemy jakieś dane z internetu
`const` - stała na etapie kompilacji - musi być od razu zainicjalizowana
`final` - stała na etapie działania programu - na początku może być pusta, ale po pierwszym przypisaniu nie może zostać zmieniona
Typy wbudowane Dart udostępniają właściwość `.runtimeType` , która zwraca nazwę typu
## Typy
Dart jest językiem z inferencją typów czyli sam potrafi rozpoznać typ zmiennej
Czasem przydaje się jawne pisanie typów - od razu wiadomo czego można użyć
Typ | Opis
--- | ---
`num` | Typ całkowity i zmiennoprzecinkowy
`int` |
`double` | Liczby zmiennoprzecinkowe lub całkowite, które chcemy zrzutować na zmiennoprzecinkowe
`bool` |
`String` | Ciąg znaków
```dart
// Konkatenacja
print(text1 + text2 + text3);
// Interpolacja
print('$text1   +   $text2   +   $text3')
```
Łączenie Stringów:
Konkatenacja (użycie `+`) - nie uwzględnia pustych znaków
Interpolacja
Inne o Stringach
Multiline
```dart
String multiline = """
multi
line
"""
```
Raw String
```dart
String text = r'This is \n description';
```
```dart
void printList(List list) {
print("All elements: ${list}");
}
void main() {
var list = [1, 3, 5, 8];
var stringList = ['one', 'three', 'five', 'eight'];
print("Length: ${list.length}");
printList(list);
list.add(10);
printList(list);
// Miksowanie list o różnych typach
// spread-operator (...)
var mixedList = [...list, ...stringList];
printList(mixedList);
print(mixedList.runtimeType);
// Typ listy mieszanej to JSArray<Object>
// Pojawia się JSArray bo ten kod kompiluje DartPad
// Istotny jest typ Object - czyli typ dowolny
}
```
## Set
# Nieprzerobione
# Flutter
Sound null safety - analizator kodu przed uruchominieme programu sprawdza czy nie będzie nulli. Potem
Kotlin używany w Androidzie
Dart używany praktycznie tylko we Flutterze.
Wcześniej było coś takiego jak "Angular Dart", ale projekt został zamknięty
## Paczki i pluginy
Czym się różni paczka od pluginu
Plugin np. na Androida/Windowsa - używa natywnego kodu np. w Androidzie i Windowsie
Paczka dart ffi (umożliwia wykorzystanie kodu C/C++ w kodzie Darta
fluent_ui - umożliwia użycie kontrolek z Windowsa (domyslnie Flutter dostarcza kontrolki Andorid/iOS)
Dart się interpoluje z innymi językami (np. ze Swiftem)
*
## Efective Dart
Dobre praktyki



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