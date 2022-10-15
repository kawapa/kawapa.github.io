# Adapter

## Zastosowanie

* Umożliwia współdziałanie obiektów o niekompatybilnych interfejsach.

## Użycie

* Sprawdź jakie API oferuje obiekt A, który masz do dyspozycji
* Sprawdź jakie API jest wymagane przez obiekt B
* Stwórz nową klasę, która agreguje obiekt A (np. poprzez referencję) ale implementuje interfejs wymagany przez obiekt B
* Uwaga! Liczba adapterów w dużym projekcie może być duża, stąd zalecane jest cache'owanie lub inne optymalizacje

## Odmiany adaptera

### Adapter obiektu

* Adapter trzyma jako pole w klasie obiekt, którego interfejs jest niekompatybilny

### Adapter klasy

* Adapter dziedziczy zarówno po klasie, która ma wymagany interfejs jak i klasie, której interfejs jest niekompatybilny
* Wielodziedziczenie nie jest możliwe w niektórych językach programowania (np. Javie)

## Referencje

* [Refactoring Guru - Adapter](https://refactoring.guru/pl/design-patterns/adapter)