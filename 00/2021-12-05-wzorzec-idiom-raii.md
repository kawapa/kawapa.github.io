---
layout: post
title: Wzorzec projektowy / Idiom RAII
date: 2021-11-28 17:00:00
permalink: /XXX
search_exclude: true
---

* Resource Acquisition is Initialization q
* Każdy zasób (pamięć, plik, mutex) powinien mieć konkretny handler
* Pozyskanie w konstruktorze
* Zwolnienie w destruktorze
    * Jeśli wystąpi wyjątek to automatycznie wołany jest destruktor (zwijanie stosu)


* Resource Acquisition is Initialization
* Każdy zasób (pamięć, plik, mutex) powinien mieć konkretny handler
* Pozyskanie w konstruktorze
* Zwolnienie w destruktorze
    * Jeśli wystąpi wyjątek to automatycznie wołany jest destruktor (zwijanie stosu)


## Bibliografia

* http://home.agh.edu.pl/~glowacki/docs/matwykl/O-o/_ProgObiekt-C++14-Rozsz.pdf
