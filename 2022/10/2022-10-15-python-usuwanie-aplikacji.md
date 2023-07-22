---
layout: post
title: "Instalowanie i odinstalowywanie aplikacji python'owych ze źródeł"
categories: [post]
date: 2022-10-15
permalink: /python-usuwanie-aplikacji
---

# Instalowanie i odinstalowywanie aplikacji python'owych ze źródeł
{: .no_toc }

---

## Zalecane podejście

1. Instalacja: `pip install .`
2. Deinstalacja:
    * Szukamy nazwy aplikacji: `pip list installed`
    * Odinstalowujemy: `pip uninstall <NAME>`

---

## Niezalecane podejście

Nie jest zalecane korzystanie z komendy `python setup.py install`. Nie wiadomo jakie pliki zainstalowane zostały w systemie, aczkolwiek można zrobić pewien trick:

`sudo python3 setup.py install --record files.txt`<br>
`sudo xargs rm -rf < files.txt`<br>
`rm files.txt`

---

## Bibliografia

* [Stack Overflow - python setup.py uninstall](https://stackoverflow.com/questions/1550226/python-setup-py-uninstall)
