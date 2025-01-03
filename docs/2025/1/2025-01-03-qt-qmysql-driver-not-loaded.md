---
layout: page
title: Qt - QMYSQL driver not loaded
date: 2025-01-03
permalink: /qt-qmysql-driver-not-loaded
---

# Qt - QMYSQL driver not loaded

The problem occurs when attempting to run a program that uses a MySQL database.

---

## Solution

```bash
$ cd ~/Qt5.12.12/5.12.12/Src/qtbase/src/plugins/sqldrivers/mysql
$ ~/Qt5.12.12/5.12.12/gcc_64/bin/qmake  // not the system qmake!
$ make
$ make install
```

Replace `5.12.12` with the version you have. The libraries will appear in `~/Qt5.12.12/5.12.12/Src/qtbase/src/plugins/sqldrivers/plugins/sqldrivers`.

At the end, copy the sqldrivers directory to the location where the binary is located (or copy the individual library).

---

## Possible issues

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

To handle this:

1. Install `libmysqlclient-dev`, `mysql-client`, and `libssl-dev` (optionally, also `libqt5sql5-mysql`).
2. Delete the `config.cache` file.
3. Repeat the procedure from *Solution*.