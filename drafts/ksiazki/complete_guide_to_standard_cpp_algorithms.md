
* C++17 wprowadził opcję współbieżnego wykonywania algorytmów STL poprzez przekazanie odpowiedniej "policy"

```cpp
std::atomic<int> cnt = 0, sum = 0;
std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9};
std::for_each(std::execution::par_unseq,
data.begin(), data.end(),
[&](int el) {
cnt++;
sum += el;
});
// cnt == 9, sum == 45
```

Operacje wykonywane przez wątki muszą być atomowe lub dane na których wykonywane są działania muszą być chronione mutexami.

* C++20 wprowadza ranges oraz views
  * Algorytmy otrzymują swoją nową wersję std::ranges::for_each

```cpp
int cnt = 0, sum = 0;
std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9};
std::ranges::for_each(data, [&](int el) {
cnt++;
sum += el;
});
// cnt == 9, sum == 45
```

* Algorytmy operują na strukturach danych, a iteratory oraz ranges służą zapewnieniu że szczegóły implementacyjne każdej struktury danych zostają prywatne, tym samym sturktura ale jak ukryć szczegóły implementacyjne struktur danych bystruktury że


* Iteratory umożliwiają enkapsulację szczegółów implementacyjnych poruszania się po danej strukturze danych oraz jednocześnie, dzięki temu, umożliwiają algorytmom STL operowanie na nich
* Każdy range jest zdefiniowany jako para iteratorów lub, od C++20, jako iterator oraz sentintel (wartownik
* Range zdefiniowany jako [it1, it2) obejmuje elementy od it1 do ostatniego elementu przed it2