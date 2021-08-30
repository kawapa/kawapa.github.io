---
layout: post
title: "Książka: Testy jednostkowe. Zasady, praktyki i wzorce"
date: 2021-10-03 09:00:00
categories: 
---

**Poniższy wpis to moje osobiste notatki i przemyślenia z najciekawszych (dla mnie) fragmentów lektury.<br>
Zachęcam do sięgnięcia po źródło oryginalne (link na końcu wpisu).**<br><br>

### Rozdział 1. Cel testowania jednostkowego

* Umożliwienie **zrównoważonego** rozwoju projektu opartego na wytwarzaniu oprogramowania
  * Dość łatwo buduje się projekt od początku, ponieważ nic Cię nie spowalnia, nie podjęto jeszcze żadnych złych decyzji co do architektury
  * W miarę upływu czasu rośnie liczba godzin, jakie musisz poświęcić, by wykazywać to samo tempo postępu co początkowo
  * W końcu prędkość rozwijania oprogramowania znacząco spada, a w skrajnych przypadkach postęp w ogóle przestaje być możliwy
* Zapewnienie pewnego rodzaju sieci bezpieczeństwa zapewniająca ochronę przed regresją (istniejąca funkcjonalność aplikacji dalej działa po wprowadzeniu zmian lub refaktoryzacji)

#### 1.1 Co czyni test dobrym?

* Nie dają wyników fałszywie negatywnych
* Wychwytują regresję
* Są szybkie
* Łatwość zaadoptowania kodu testu gdy zmienia się kod produkcyjny

#### 1.2 Wskaźniki pokrycia testami

> Wskaźnik pokrycia testami jest dobrą miarę tego, że kod jest zły, ale kiepską miarą tego, jak jest on dobry.

##### 1.2.1 Wskaźnika pokrycia kodu

* Inaczej **pokrycie testowe**
* Iloraz ( liczba wykonanych linii kodu przynajmniej przez jeden test ) / ( łączna ilość linii)

##### 1.2.2 Wskaźnika pokrycia gałęzi

<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>

1.3.3. Problemy z pokryciem gałęzi 27<br>
1.3.4. Wymaganie procentowej wartości pokrycia 30<br>
1.4. Właściwości dobrego zestawu testowego 31<br>
1.4.1. Integracja z cyklem wytwarzania oprogramowania 31<br>
1.4.2. Koncentracja na najważniejszych częściach kodu 31<br>
1.4.3. Maksymalna wartość przy minimalnych kosztach 32<br>
1.5. Czego nauczysz się z tej książki 33<br>
Podsumowanie 34<br>
<br>
Rozdział 2. Co to jest test jednostkowy? 37<br>
<br>
2.1. Definicja testu jednostkowego 38<br>
2.1.1. Izolacja - podejście londyńskie 38<br>
2.1.2. Izolacja - podejście klasyczne 44<br>
2.2. Klasyczna i londyńska szkoła testów jednostkowych 47<br>
2.2.1. Obsługa zależności według szkoły londyńskiej i klasycznej 47<br>
2.3. Zestawienie podejść - klasycznej i londyńskiej szkoły testowania jednostkowego 51<br>
2.3.1. Testowanie jednostkowe jednej klasy na raz 51<br>
2.3.2. Testowanie jednostkowe dużej mapy wzajemnie łączących się klas 52<br>
2.3.3. Dokładne wskazywanie źródła błędów 52<br>
2.3.4. Inne różnice między podejściem klasycznym a londyńskim 53<br>
2.4. Testy integracyjne według dwóch szkół 54<br>
2.4.1. Testy systemowe to podzbiór testów integracyjnych 55<br>
Podsumowanie 57<br>
<br>
Rozdział 3. Anatomia testu jednostkowego 59<br>
<br>
3.1. Struktura testu jednostkowego 60<br>
3.1.1. Zastosowanie wzorca AAA 60<br>
3.1.2. Unikanie wielokrotnych sekcji przygotuj, zrób, sprawdź 61<br>
3.1.3. Unikanie warunków w testach 62<br>
3.1.4. Optymalna wielkość sekcji 63<br>
3.1.5. Liczba weryfikacji w sekcji asercji 65<br>
3.1.6. Sekwencja końcowa 65<br>
3.1.7. Zróżnicowanie systemu poddawanego testom 65<br>
3.1.8. Usunięcie komentarzy na temat sekcji z testów 66<br>
3.2. Omówienie biblioteki testowej xUnit 67<br>
3.3. Wielokrotne wykorzystanie jarzma testowego 68<br>
3.3.1. Silne wiązania między testami - antywzorzec 69<br>
3.3.2. Użycie konstruktora zmniejsza czytelność 70<br>
3.3.3. Lepszy sposób wielokrotnego wykorzystania jarzma testowego 70<br>
3.4. Nazewnictwo testów jednostkowych 72<br>
3.4.1. Nazewnictwo testów jednostkowych - wytyczne 74<br>
3.4.2. Przykład: zmiana nazwy testu zgodnie z wytycznymi 74<br>
3.5. Zamiana na testy parametryzowane 76<br>
3.5.1. Generowanie danych dla testów parametryzowanych 78<br>
3.6. Biblioteka asercji i dalsze poprawianie czytelności testów 80<br>
Podsumowanie 81<br>
<br>
CZĘŚĆ II. TESTY, KTÓRE PRACUJĄ DLA CIEBIE 83<br>
<br>
Rozdział 4. Cztery filary dobrego testu jednostkowego 85<br>
<br>
4.1. Cztery filary dobrego testu jednostkowego 86<br>
4.1.1. Filar pierwszy: ochrona przed regresją 86<br>
4.1.2. Filar drugi: odporność na zmiany 87<br>
4.1.3. Co powoduje wyniki obarczone błędem pierwszego rodzaju 89<br>
4.1.4. Skup się na końcowym wyniku, a nie szczegółach implementacyjnych 92<br>
4.2. Nierozerwalny związek między pierwszą a drugą cechą 94<br>
4.2.1. Zwiększanie dokładności testów 94<br>
4.2.2. Waga wyników fałszywie dodatnich i fałszywie ujemnych - dynamika 96<br>
4.3. Filary trzeci i czwarty: szybka informacja zwrotna i utrzymywalność 97<br>
4.4. W poszukiwaniu idealnego testu 98<br>
4.4.1. Czy możliwe jest stworzenie idealnego testu 99<br>
4.4.2. Przypadek skrajny nr 1: test systemowy 99<br>
4.4.3. Przypadek skrajny nr 2: testy trywialne 100<br>
4.4.4. Przypadek skrajny nr 3: niestabilne testy 101<br>
4.4.5. W poszukiwaniu idealnego testu - wyniki 102<br>
4.5. Omówienie dobrze znanych pojęć z zakresu testów automatycznych 105<br>
4.5.1. Poziomy piramidy testów 105<br>
4.5.2. Wybór między testowaniem czarno- i białoskrzynkowym 107<br>
Podsumowanie 108<br>
<br>
Rozdział 5. Atrapy i stabilność testów 111<br>
<br>
5.1. Rozróżnienie między atrapami a zaślepkami 112<br>
5.1.1. Rodzaje dublerów testowych 112<br>
5.1.2. Atrapa (narzędzie) kontra atrapa (dubler testowy) 113<br>
5.1.3. Nie poddawaj asercjom interakcji z zaślepkami 114<br>
5.1.4. Używanie atrap i zaślepek razem 116<br>
5.1.5. Związek atrap i zaślepek z poleceniami i zapytaniami 116<br>
5.2. Zachowanie dające się zaobserwować a szczegóły implementacyjne 117<br>
5.2.1. Dające się zaobserwować zachowanie to nie publiczny interfejs API 118<br>
5.2.2. Wyciekające szczegóły implementacyjne - przykład z operacją 119<br>
5.2.3. Dobrze zaprojektowany interfejs API i enkapsulacja 122<br>
5.2.4. Wyciekające szczegóły implementacyjne - przykład ze stanem 123<br>
5.3. Związek między atrapami a niestabilnością testów 125<br>
5.3.1. Architektura heksagonalna 125<br>
5.3.2. Komunikacja wewnątrzsystemowa i międzysystemowa 129<br>
5.3.3. Komunikacja wewnątrzsystemowa i międzysystemowa - przykład 130<br>
5.4. Klasyczna i londyńska szkoła testowania jednostkowego - raz jeszcze 133<br>
5.4.1. Nie wszystkie zewnętrzne zależności należy zastępować atrapami 133<br>
5.4.2. Wykorzystanie atrap do weryfikowania zachowania 135<br>
Podsumowanie 135<br>
<br>
Rozdział 6. Style testowania jednostkowego 139<br>
<br>
6.1. Trzy style testowania jednostkowego 140<br>
6.1.1. Styl oparty na rezultatach - definicja 140<br>
6.1.2. Styl oparty na stanach - definicja 141<br>
6.1.3. Styl oparty na komunikacji - definicja 142<br>
6.2. Trzy style testowania jednostkowego - porównanie 143<br>
6.2.1. Porównanie stylów pod względem ochrony przed regresją i szybkości informacji zwrotnej 144<br>
6.2.2. Porównanie stylów pod względem odporności na zmiany 144<br>
6.2.3. Porównanie stylów pod względem utrzymywalności 145<br>
6.2.4. Porównanie stylów - wyniki 147<br>
6.3. Architektura funkcyjna 148<br>
6.3.1. Czym jest programowanie funkcyjne? 148<br>
6.3.2. Czym jest architektura funkcyjna? 151<br>
6.3.3. Porównanie architektury funkcyjnej i heksagonalnej 153<br>
6.4. Przejście do architektury funkcyjnej i testowania opartego na rezultatach 154<br>
6.4.1. System audytowania - wprowadzenie 154<br>
6.4.2. Wykorzystanie atrap w celu oddzielenia testu od systemu plików 157<br>
6.4.3. Przejście do architektury funkcyjnej 160<br>
6.4.4. Potencjalne dalsze kroki 164<br>
6.5. Wady architektury funkcyjnej 165<br>
6.5.1. Zasadność stosowania architektury funkcyjnej 165<br>
6.5.2. Wady pod względem wydajności 167<br>
6.5.3. Wady pod względem rozmiaru bazy kodu 167<br>
Podsumowanie 168<br>
<br>
Rozdział 7. Zmiany ku bardziej wartościowym testom jednostkowym 171<br>
<br>
7.1. Określenie kodu podlegającego refaktoryzacji 172<br>
7.1.1. Cztery typy kodu 172<br>
7.1.2. Wykorzystanie wzorca Skromny Obiekt do podziału przeszacowanego kodu 175<br>
7.2. Zmiany ku bardziej wartościowym testom 178<br>
7.2.1. System zarządzania kontaktami z klientami - wprowadzenie 178<br>
7.2.2. Próba nr 1: ujawnienie zależności 180<br>
7.2.3. Próba nr 2: wprowadzenie warstwy usług aplikacji 180<br>
7.2.4. Próba nr 3: usunięcie złożoności z usługi aplikacji 182<br>
7.2.5. Próba nr 4: wprowadzenie nowej klasy Company 184<br>
7.3. Analiza optymalnego pokrycia testami jednostkowymi 186<br>
7.3.1. Testowanie warstwy domeny i kodu pomocniczego 187<br>
7.3.2. Testowanie kodu z pozostałych części diagramu 188<br>
7.3.3. Czy powinno się testować warunki wstępne? 188<br>
7.4. Obsługa logiki warunkowej w kontrolerach 189<br>
7.4.1. Wykorzystanie wzorca Polecenie 191<br>
7.4.2. Wykorzystanie zdarzeń domeny do śledzenia zmian w modelu domeny 194<br>
7.5. Wnioski 197<br>
Podsumowanie 199<br>
<br>
CZĘŚĆ III. TESTY INTEGRACYJNE 203<br>
<br>
Rozdział 8. Po co testy integracyjne? 205<br>
<br>
8.1. Test integracyjny - definicja 206<br>
8.1.1. Rola testów integracyjnych 206<br>
8.1.2. Piramida testów - jeszcze raz 207<br>
8.1.3. Testy integracyjne kontra szybka reakcja 208<br>
8.2. Które zewnętrzne zależności testować bezpośrednio 209<br>
8.2.1. Dwa typy zależności poza kontrolą procesu 210<br>
8.2.2. Obsługa zarządzanych i niezarządzanych zależności 211<br>
8.2.3. Co, jeśli nie możesz wykorzystać prawdziwej bazy danych w testach integracyjnych? 212<br>
8.3. Testy integracyjne - przykład 213<br>
8.3.1. Jakie scenariusze przetestować? 214<br>
8.3.2. Klasyfikacja bazy danych i szyny danych 214<br>
8.3.3. Co z testami systemowymi? 215<br>
8.3.4. Test integracyjny - próba pierwsza 216<br>
8.4. Stosowanie interfejsów do abstrakcji zależności 217<br>
8.4.1. Interfejsy i luźne wiązania 217<br>
8.4.2. Po co używać interfejsów dla zewnętrznych zależności? 218<br>
8.4.3. Stosowanie interfejsów dla wewnętrznych zależności 219<br>
8.5. Najlepsze praktyki testów integracyjnych 220<br>
8.5.1. Jasno oznacz granice modelu domeny 220<br>
8.5.2. Zmniejszaj liczbę warstw 220<br>
8.5.3. Usuwaj zapętlone zależności 222<br>
8.5.4. Użycie wielu sekcji działania w teście 224<br>
8.6. Jak testować zapisywanie logów 225<br>
8.6.1. Czy w ogóle powinno się testować pisanie logów 225<br>
8.6.2. Jak testować pisanie logów 226<br>
8.6.3. Ile logowania wystarczy 231<br>
8.6.4. Jak przekazywać instancje mechanizmu logowania 232<br>
8.7. Wnioski 233<br>
Podsumowanie 233<br>
<br>
Rozdział 9. Najlepsze praktyki modelowania za pomocą atrap 237<br>
<br>
9.1. Maksymalizowanie wartości atrap 237<br>
9.1.1. Weryfikacja interakcji na obrzeżach systemu 240<br>
9.1.2. Zastępowanie atrap agentami 243<br>
9.1.3. Co z interfejsem IDomainLogger 245<br>
9.2. Najlepsze praktyki modelowania za pomocą atrap 246<br>
9.2.1. Atrapy służą tylko do testów integracyjnych 246<br>
9.2.2. Wiele atrap w jednym teście 246<br>
9.2.3. Weryfikacja liczby żądań 247<br>
9.2.4. Modeluj tylko typy, które sam utworzyłeś 247<br>
Podsumowanie 248<br>
<br>
Rozdział 10. Testowanie bazy danych 251<br>
<br>
10.1. Warunki umożliwiające testowanie bazy danych 252<br>
10.1.1. Przechowywanie bazy danych w systemie kontroli wersji 252<br>
10.1.2. Dane referencyjne to część schematu bazy danych 253<br>
10.1.3. Oddzielne instancje dla każdego programisty 254<br>
10.1.4. Stanowe i migracyjne podejście do dostarczania bazy danych 254<br>
10.2. Zarządzanie transakcjami w bazie danych 256<br>
10.2.1. Zarządzanie transakcjami w kodzie produkcyjnym 256<br>
10.2.2. Zarządzanie transakcjami w testach integracyjnych 263<br>
10.3. Cykl życia danych testowych 265<br>
10.3.1. Równoległe i sekwencyjne wykonanie testów 265<br>
10.3.2. Sprzątanie danych pomiędzy wykonaniami testów 266<br>
10.3.3. Unikanie baz danych operujących w pamięci 267<br>
10.4. Wielokrotne wykorzystanie kodu w sekcjach 268<br>
10.4.1. Wielokrotne użycie kodu w sekcji przygotowań 268<br>
10.4.2. Wielokrotne użycie kodu w sekcji działania 271<br>
10.4.3. Wielokrotne użycie kodu w sekcji asercji 271<br>
10.4.4. Czy test tworzy zbyt wiele transakcji do bazy danych 272<br>
10.5. Często zadawane pytania na temat testowania baz danych 273<br>
10.5.1. Czy testować operacje odczytu? 273<br>
10.5.2. Czy testować repozytoria? 275<br>
10.6. Wnioski 276<br>
Podsumowanie 276<br>
<br>
CZĘŚĆ IV. ANTYWZORCE TESTOWANIA JEDNOSTKOWEGO 279<br>
<br>
Rozdział 11. Antywzorce testowania jednostkowego 281<br>
<br>
11.1. Testowanie jednostkowe prywatnych metod 282<br>
11.1.1. Metody prywatne i niestabilność testów 282<br>
11.1.2. Metody prywatne i niedostateczne pokrycie 282<br>
11.1.3. Kiedy testowanie metod prywatnych jest akceptowalne 283<br>
11.2. Udostępnianie stanu prywatnego 285<br>
11.3. Przenikanie wiedzy domenowej do testów 286<br>
11.4. Zanieczyszczanie kodu 288<br>
11.5. Modelowanie za pomocą atrap konkretnych klas 290<br>
11.6. Praca z czasem 293<br>
11.6.1. Czas jako kontekst środowiskowy 293<br>
11.6.2. Czas jako jawna zależność 294<br>
11.7. Wnioski 295<br>
Podsumowanie 295<br>
<br>

## Bibliografia

* [Vladimir Khorikov - Testy jednostkowe. Zasady, praktyki i wzorce](https://helion.pl/ksiazki/testy-jednostkowe-zasady-praktyki-i-wzorce-vladimir-khorikov,tejeza.htm#format/d)
