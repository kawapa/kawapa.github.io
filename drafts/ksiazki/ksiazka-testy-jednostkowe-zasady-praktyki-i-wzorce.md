---
layout: post
title: "Książka: Testy jednostkowe. Zasady, praktyki i wzorce"
date: 2023-01-02 07:00:00
permalink: /testy-jednostkowe
---

# Książka: Testy jednostkowe. Zasady, praktyki i wzorce
{: .no_toc }

Poniższy wpis to moje osobiste notatki i przemyślenia z najciekawszych (dla mnie) fragmentów książki. Zachęcam do sięgnięcia po źródło oryginalne (link na końcu wpisu).
{: .fs-6 .fw-300 }

<details closed markdown="block">
  <summary>
    Spis treści
  </summary>
  {: .text-delta }
1. TOC
{:toc}
</details>

---

## Cel testowania jednostkowego

* Zapewnienie ciągłego, **zrównoważonego** rozwoju aplikacji
  * Aplikacja budowana od zera powstaje dosyć szybko bo nie doskwiera jeszcze nieprawidłowo dobrana architektura oraz poziom skomplikowania dopiero narasta. Wraz z rozwojem projektu coraz więcej czasu potrzeba na wdrożenie nowych funkcjonalności, a w skrajnych przypadkach dalszy rozwijanie aplikacji przestaje być możliwe
* Zapewnienie ochrony przed regresją (po dodaniu nowej funkcjonalności lub refaktoryzacji kodu)

## Co czyni test dobrym?

Dobry test:

* Jest szybki
* Wychwytuje regresję
* Nie daje wyników fałszywie negatywnych
* Daje się łatwo zmodyfikować w przypadku kiedy zmienia się kod produkcyjny 

## Wskaźniki pokrycia testami

> Wskaźnik pokrycia testami jest dobrą miarę tego, że kod jest zły, ale kiepską miarą tego, jak jest on dobry. Vladimir Khorikov

### Wskaźnika pokrycia kodu

* Inaczej **pokrycie testowe**
* Iloraz ( liczba wykonanych linii kodu przynajmniej przez jeden test ) / ( łączna ilość linii )
* Łatwo manipulować wartością wskaźnika pokrycia
  * Im bardziej zwięzły kod, tym lepsze wskaźniki pokrycia ponieważ weryfikacji podlega liczba linii

W poniższym przykładzie pokrycie kodu wynosi 80% (testowane są 4 linie z 5), natomiast w kolejnym przykładzie, który robi dokładnie to samo wskaźnik ten wynosi 100% (3/3):

{% gist bd68a702a936c1ec416004004ad40c0b %}

### Wskaźnika pokrycia gałęzi

* Dokładniejszy niż wskaźnik pokrycia kodu (nie można go aż tak zmanipulować)
* Iloraz ( liczba trawersowanych gałęzi ) / ( łączna liczba gałęzi )
* Nie sprawdza czy testy weryfikujące wszystkie możliwe ścieżki wykonania mają asercje
* Kod wykonany uznaje za przetestowany - nawet jeśli nie kończy się asercją (test bezużyteczny)

W obu poprzednich przykładach były dwie gałęzie, jedna dotyczyła sytuacji kiedy reszta z dzielenia przez 2 wynosiła 0, a druga kiedy ta reszta była różna od zera. Oba


Przykład: 100% pokrycia kodu i 50% pokrycia gałęzi

{% highlight cpp %}
int foo;          // zmienna globalna

bool addOne(int number)
{
  int res += 1;
  foo = res;      // pierwsza wartość wynikowa

  return res;     // druga wartość wynikowa
}
// ...
ASSERT_TRUE(isEven(2));   // test weryfikuje tylko drugą wartość wynikową
{% endhighlight %}





##### 1.3. Właściwości dobrego zestawu testowego

Nie ma zautomatyzowanych sposobów określania czy zestaw test jest dobry, natomiast wiadomo, że:

* Powinien być zintegrowany z cyklem wytwarzania oprogramowania
  * Idealnie gdybyś uruchamiał wszystkie testy przy każdej zmianie kodu
* Powinien koncentrować się na najważniejszych częściach bazy kodu
  * Najwnikliwiej testuj najbardziej istotne obszary (logikę biznesową) a pozostałe obszary powierzchownie
* Powinien dostarczać jak największej wartości przy jak najniższym koszcie jego utrzymania

### Rozdział 2. Co to jest test jednostkowy?

#### 2.1. Definicja testu jednostkowego

Test jednostkowy to automatyczny test, który:
* Weryfikuje niewielki fragment kodu
* Jest szybki
* Robi to w odizolowaniu od pozostałych części systemu

Aspekt izolacji stanowi sedno różnic między klasyczną, a londyńską szkoła testowania jednostkowego.

Szkoła londyńska - wywodzi się ze społeczności programistycznej w Londynie (nazywa się ich mockistami)
Szkoła klasyczna - nazywana czasem szkołą z Detroit lub klasycystycznym podejściem

##### 2.1.1. Izolacja - podejście londyńskie

* Należ izolować testowany system od jego współzależności i konsumentów
  * Wszystko zastąpić testowymi dublerami
* Zalety takiego podejścia:
  * Jest test zwraca wynik negatywny, wiadomo która część kodu zawiera błąd
  * W przypadku skomplikowanej sieci klas, w której każda zależy od innych - można łatwo przerwać łańcuch zależności
  * Pozwala testować wyłącznie jedną klasę na raz (upraszcza to strukturę testów)

2.1.2. Izolacja - podejście klasyczne 44<br>

## Bibliografia

* [Vladimir Khorikov - Testy jednostkowe. Zasady, praktyki i wzorce](https://helion.pl/ksiazki/testy-jednostkowe-zasady-praktyki-i-wzorce-vladimir-khorikov,tejeza.htm#format/d)