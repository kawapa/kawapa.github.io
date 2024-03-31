---
layout: post
title: Qt - QMYSQL driver not loaded
categories: [post]
date: 2021-12-12
permalink: /qt-qmysql-driver-not-loaded
nav_exclude: true
---

Problem występuje podczas próby uruchomienia programu korzystającego z bazy MySQL. 

## Rozwiązanie

```bash
$ cd ~/Qt5.12.12/5.12.12/Src/qtbase/src/plugins/sqldrivers/mysql
$ ~/Qt5.12.12/5.12.12/gcc_64/bin/qmake    // nie systemowy qmake!
$ make
$ make install
```

* Zamień `5.12.12` na wersję, którą posiadasz
* Biblioteki pojawią się w `~/Qt5.12.12/5.12.12/Src/qtbase/src/plugins/sqldrivers/plugins/sqldrivers`
* Skopiuj katalog `sqldrivers` w miejsce gdzie leży binarka (lub pojedynczą bibliotekę)

---

## Możliwe problemy

```bash
Qt Sql Drivers:
  DB2 (IBM) .............................. no
  InterBase .............................. no
  MySql .................................. no
  OCI (Oracle) ........................... no
  ODBC ................................... no
  PostgreSQL ............................. no
  SQLite2 ................................ no
  SQLite ................................. no
    Using system provided SQLite ......... no
  TDS (Sybase) ........................... no
```

1. Doinstaluj `libmysqlclient-dev`, `mysql-client` i `libssl-dev` (ewentualnie jeszcze `libqt5sql5-mysql`)
2. **Usuń plik `config.cache`**
3. Spróbuj ponownie