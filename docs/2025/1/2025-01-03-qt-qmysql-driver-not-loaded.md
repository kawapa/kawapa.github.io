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


{% gist 025f37d57b5952c9b5227b2ea1476b60 solution.sh %}

Replace `5.12.12` with the version you have. The libraries will appear in `~/Qt5.12.12/5.12.12/Src/qtbase/src/plugins/sqldrivers/plugins/sqldrivers`.

At the end, copy the sqldrivers directory to the location where the binary is located (or copy the individual library).

---

## Possible issues

{% gist 025f37d57b5952c9b5227b2ea1476b60 possible_issues.sh %}

 To handle this:

1. Install `libmysqlclient-dev`, `mysql-client`, and `libssl-dev` (optionally, also `libqt5sql5-mysql`).
2. Delete the `config.cache` file.
3. Repeat the procedure from *Solution*.