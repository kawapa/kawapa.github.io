---
layout: post
title: "Kiedy alokować na stosie, a kiedy na stercie"
permalink: /stos-czy-sterta
search_exclude: true
---

# Kiedy alokować na stosie, a kiedy na stercie
{: .no_toc }

---

## Jaka jest różnica między stosem a stertą?

* Czym różni się alokacja pamięci na stosie od alokacji pamięci na stercie?
* Która pamięć jest szybsza?

### Stos

Stos jest miejscem, gdzie wstawia się dane w sposób uporządkowany (obok siebie). Do stosu jest szybki dostęp, a pamięć (ograniczona z góry przez OS) jest zwalniana automatycznie gdy zmienna wychodzi poza swój zakres. Na stosie przechowywane są:
* chwilowe rejestry procesora
* zmienne lokalne
* argumenty wywołania funkcji
* wartość zwracana przez funkcję

### Sterta

Sterta jest miejscem, gdzie alokujesz pamięć, gdzie tylko jest ona wolna (przez co dostęp jest wolniejszy).
* Alokowanie na stercie daje większą elastyczność (limit pamięci nie jest ograniczony przez OS) – np. rozmiar tablicy nie musi być znany w trakcie działania programu.
* Należy pamiętać o zwolnieniu pamięci, żeby zapobiec tzw. wyciekom pamięci.
* Na stercie przechowywane są:
* dynamicznie tworzone struktury danych
* dynamicznie przydzialne obszary pamięci

---

## Kiedy alokować na stosie?

If you are working with relatively small variables that are only required until the function using them is alive. Then you need to use the stack, which is faster and easier.

---

## Kiedy alokować na stercie?

You should use heap when you require to allocate a large block of memory. For example, you want to create a large size array or big structure to keep that variable around a long time then you should allocate it on the heap.

## Bibliografia

* https://www.guru99.com/stack-vs-heap.html
* https://www.geeksforgeeks.org/stack-vs-heap-memory-allocation/
* https://www.codeproject.com/Articles/76153/Six-important-NET-concepts-Stack-heap-value-types
