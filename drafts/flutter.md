---
layout: post
title: Flutter
# categories: [post]
# date: 2023-07-22
permalink: /flutter
---

# Flutter
{: .no_toc }

<details closed markdown="block">
  <summary>
    Spis treści
  </summary>
  {: .text-delta }
1. TOC
{:toc}
</details>

---

* Roadmap - https://github.com/olexale/flutter_roadmap
* FVM - Flutter Version Manager (Management) - umożliwia użycia odmiennej wersji Fluttera dla każdego projektu

## Instalacja

1. Zainstaluj Brew
   
`/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)`

2. Zaktualizuj zmienną `PATH` żeby można było używać komendy `brew`
   
`echo '# Set PATH, MANPATH, etc., for Homebrew.' >> /home/pae/.profile`
`echo 'eval "$(/home/linuxbrew/.linuxbrew/bin/brew shellenv)"' >> /home/pae/.profile`
`eval "$(/home/linuxbrew/.linuxbrew/bin/brew shellenv)`
  
3. `brew tap leoafarias/fvm`
4. `brew install fvm`

- Od teraz można korzystać z komendy `fwm`
- Samo fvm wyświetli listę możliwych komend
  - `fvm --version`
  - `fvm config` - wyświetla plik ustawień dla fvm

5. Zainstaluj Fluttera

- Ostatnia stabilna: `fvm install stable`
- Konkretna wersja, na przykład `fvm install 3.0.5`

6. `fvm global 3.0.5` - ustawienie tej wersji jako globalnej - czyli tej która będzie używana domyślnie

- Możliwe ostrzeżenie, że trzeba dodać Fluttera do zmiennej PATH: `export PATH=$PATH:"/home/pae/fvm/default/bin`

7. Sprawdź czy wszystko jest: `fvm flutter doctor`

- Jeśli ChromiuM zamiast Chrome: `export CHROME_EXECUTABLE=/var/lib/flatpak/exports/bin/org.chromium.Chromium`

8. Pobierz Flutter SDK - https://docs.flutter.dev/development/tools/sdk/releases?tab=linux

9. Rozpakuj, Utwórz nowy projekt w VSC i wskaż ścieżkę do Flutter SDK: `flutter_linux_3.3.9-stable/flutter/bin`

## Przydatne rozszerzenia VSC

* Flutter (zawiera wtyczkę obługującą język Dart)
* [FF] Flutter Files - wspomaga generowanie template'ów, które służą do zarządzania stanem aplikacji
* ADB Interface for VSCode - jeśli używasz fizycznego urządzenia i obsługujesz go terminalem, wtyczka umożliwia wydawanie komend bezpośrednio z VSC
* bloc - automatycznie generuje boilerplate wymagany w każdym Blocs'u i Cubit'sie
* Build Runner - wtyczka ułatwiająca generowanie kodu w Dart'cie (dodaje skróty klawiszowe i funkcje w VSC)
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
