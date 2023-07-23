---
layout: post
title: Dart
# categories: [post]
# date: 2023-07-22
permalink: /dart
---

# Dart
{: .no_toc }

<details closed markdown="block">
  <summary>
    Spis treści
  </summary>
  {: .text-delta }
1. TOC
{:toc}
</details>

* Typ `dynamic` pozwala na zmianę typu obiektu przy kolejnych przypisaniach
    * `dynamic` sam w sobie nie jest typem - to wyłączenie sprawdzania typów
    * Jeśli chcemy mieć zmienną o "zmiennym typie" (ale ten typ będzie zmieniał się zawsze w obrębie typów języka Dart) - **zalecane jest korzystanie z typu `Object`**
* `dynamic` powinien być wykorzystywany tylko z konieczności, na przykłąd jeśli dostajemy jakieś dane z internetu
* `const` - stała na etapie kompilacji - musi być od razu zainicjalizowana
* `final` - stała na etapie działania programu - na początku może być pusta, ale po pierwszym przypisaniu nie może zostać zmieniona
* Typy wbudowane Dart udostępniają właściwość `.runtimeType` , która zwraca nazwę typu

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

```dart
// Konkatenacja (nie uwzględnia pustych znaków)
print(text1 + text2 + text3);
// Interpolacja
print('$text1   +   $text2   +   $text3')

// Multiline string
String multiline = """
multi
line
"""

// Raw string
String text = r'This is \n description';
```

## Testowanie

* `assert([WYRAŻENIE])`
