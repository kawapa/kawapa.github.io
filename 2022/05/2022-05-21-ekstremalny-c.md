---
layout: post
title: Ekstremalny kod w języku C
date: 2022-05-21 09:00:00
permalink: /ekstremalny-c
---

# Bycie efektywnym członkiem zespołu
Notatki z książki "Ekstremalny kod w języku C. Współbieżność i programowanie zorientowane obiektowo".
{: .fs-6 .fw-300 }
---

## Funkcje podstawowe

### Preprocesor

* Nie ma w innych językach programowania wyższego rzędu
* Umożliwia dopracowanie (zmodyfikowanie) kodu źródłowego przed przekazaniem go do kompilatora
  * Preprocessing to dodatkowy krok kompilacji
* Zachowaniem preprocesora C można sterować za pomocą dyrektyw rozpoczynających się od `#` (makra, instrukcje warunkowe itp.)
* Starsze kompilatory nie miały żadnych informacji o makrach i istnieniu preprocesora. **Obecnie, nowoczesne kompilatory C mają już informację o kodzie źródłowym sprzed etapu preprocessingu**.
  * Przykładowo jeśli w definicji makra jest błąd to kompilator wskaże dokładnie w której linii
* *Rozwinięcie makra* czyli zmiana kodu źródłowego pod wpływem zdefiniowanego wcześniej makra
* *Jednostka translacji* (jednostka kompilacji) czyli kod po zakończeniu etapu działania preprocesora

#### Makra

Plotki przeciw:

* Kod źródłowy staje się nieczytelny
* Utrudniają debugowanie

Zastosowania makr:

* Definiowanie stałej
* Implementacja funkcji (bez tworzenia prawdziwej funkcji w języku C)
  * Zamiast umieszczać w funkcji często używaną logikę, można ją zdefiniować w postaci makra
    * Mniej funkcji
* Implementacja pętli
* Wartownik nagłówka
* Generator kodu
* Kompilacja warunkowa
* Definiowanie języka specjalizowanego (domain-specific language, DSL) do użycia w konkretnej domenie biznesowej
  * GTest używa własnego DSLa do tworzenia asercji, definiowania oczekiwań i scenariuszy testowych

| Komenda | Opis |
|:-------------|:------------------|
| `#define <NAME> <VALUE>` | Definiowanie makra |
| `#undef <NAME>` | Usunięcie makra |
| Operator `#` |  |
| Operator `##` |  |

```cpp
// Prosta definicja funkcji przy użycie makra
#define ADD(a, b) a + b

int a = 5;
int b = 10;
int c = ADD(a, b);

// Operator # oraz ##
```

**Strona 31**

#### Makra wariadyczne

#### Wady i zalety makr

---

## Bibliografia

* [Kamran Amini - Ekstremalny kod w języku C. Współbieżność i programowanie zorientowane obiektowo](https://helion.pl/ksiazki/ekstremalny-kod-w-jezyku-c-wspolbieznosc-i-programowanie-zorientowane-obiektowo-kamran-amini,ekskod.htm#format/d)
