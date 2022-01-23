---
layout: post
title: Testy jednostkowe. Zasady, praktyki i wzorce
date: 2021-11-28 17:00:00
permalink: /testy-jednostkowe-zasady-praktyki-i-wzorce
search_exclude: true
---

# Testy jednostkowe. Zasady, praktyki i wzorce

Poniższy wpis to moje osobiste notatki i przemyślenia z najciekawszych (dla mnie) fragmentów lektury. Zachęcam do sięgnięcia po źródło oryginalne.
{: .fs-6 .fw-300 }

<details open markdown="block">
  <summary>
    Spis treści
  </summary>
  {: .text-delta }
1. TOC
{:toc}
</details>

## Cel testowania jednostkowego

* Umożliwienie **zrównoważonego** rozwoju projektu
  * Łatwo tworzy się projekt na początku, ponieważ nic nie spowalnia, nie podjęto też jeszcze żadnych złych decyzji co do architektury
  * W miarę upływu czasu rośnie liczba godzin, jakie musisz poświęcić, by wykazywać to samo tempo postępu co początkowo
  * W końcu prędkość rozwijania oprogramowania znacząco spada, a w skrajnych przypadkach postęp w ogóle przestaje być możliwy
* Zapewnienie pewnego rodzaju sieci bezpieczeństwa zapewniająca ochronę przed regresją (istniejąca funkcjonalność aplikacji dalej działa po wprowadzeniu zmian lub refaktoryzacji)

### Czym się charakteryzują dobre testy?

* Nie dają wyników fałszywie negatywnych
* Wychwytują regresję
* Są szybkie
* Łatwo je dostosować w przypadku zmiany kodu produkcyjnego

## Wskaźnika pokrycia kodu testami

* Inaczej **pokrycie testowe**
* Iloraz liczby wykonanych linii kodu (przynajmniej przez jeden test) przez łączną ilość linii
  * Łatwo manipulować wartością wskaźnika - im bardziej zwięzły kod, tym lepsze wskaźniki pokrycia, ponieważ weryfikacji podlega liczba linii

Przykład: pokrycie kodu wynosi 4/5 = 80%

{% highlight cpp %}
bool isEven(int number)
{
  if (number % 2 == 0)
    return true
  return false
}
// ...
ASSERT_TRUE(isEven(2));
{% endhighlight %}

Przykład: pokrycie kodu wynosi 3/3 = 100%

{% highlight cpp %}
bool isEven(int number)
{
  return number % 2 == 0;
}
// ...
ASSERT_TRUE(isEven(2));
{% endhighlight %}

##### 1.2.2 Wskaźnika pokrycia gałęzi

* Dokładniejszy niż wskaźnik pokrycia kodu (nie można go aż tak zmanipulować)
* Iloraz ( liczba trawersowanych gałęzi ) / ( łączna liczba gałęzi )
* Nie sprawdza czy testy weryfikujące wszystkie możliwe ścieżki wykonania mają asercje
* Kod wykonany uznaje za przetestowany - nawet jeśli nie kończy się asercją (test bezużyteczny)

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

<br>
<br>
<br>
<br>
<br>

## Bibliografia

* [Vladimir Khorikov - Testy jednostkowe. Zasady, praktyki i wzorce](https://helion.pl/ksiazki/testy-jednostkowe-zasady-praktyki-i-wzorce-vladimir-khorikov,tejeza.htm#format/d)
