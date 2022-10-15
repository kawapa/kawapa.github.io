---
layout: post
title: Pytania z rozmów kwalifikacyjnych
date: 2021-11-28 17:00:00
permalink: /XXX
search_exclude: true
---

W odcinkach po 3 pytania na jeden.

Różnica między wskaźnikiem a referencją. Czy referencja może pokazywać na zniszczony obiekt.
https://pl.gadget-info.com/difference-between-pointer#:~:text=%22Wska%C5%BAnik%22%20i%20%22odno%C5%9Bnik%22,kt%C3%B3ra%20jest%20do%20niej%20przypisana.
https://pl.wikibooks.org/wiki/C%2B%2B/Referencje#:~:text=Referencja%20w%20swym%20dzia%C5%82aniu%20przypomina,r%C3%B3%C5%BCni%20od%20u%C5%BCywania%20zwyk%C5%82ej%20zmiennej.
https://forum.pasja-informatyki.pl/28593/referencja-a-wskaznik
http://lublin.webd.pl/crayze/cpp-winapi/cpp9.html
Jaka jest roznica miedzy new a malloc?
Od czego zalezy rozmiar klasy/struktury.



# Pytania z rozmów

---

<details>
<summary>Jaka jest różnica między interfejsem, a klasą abstrakcyjną?</summary>
<p>
<ul><li>Interfejs to klasa abstrakcyjna która ma tylko i wyłącznie metody czysto wirtualne i nie ma żadnych pól</li><li>Klasa abstrakcyjna może zawierać również metody zdefiniowane</li>
<li>Rozszerzając klasę abstrakcyjną klasa może uczestniczyć jedynie w jednej hierarchii, natomiast używając interfejsów klasa może uczestniczyć w wielu typach hierarchii</li>
<li>Wszystkie zadeklarowane metody w interfejsie są publiczne, natomiast metody zadeklarowane w klasach abstrakcyjnych mogą być publiczne lub chronione</li> </ul>
</p>
</details>

---

<details>
<summary>Czym różni się alokacja pamięci na stosie od alokacji pamięci na stercie? Kiedy stosować jedno, a kiedy drugie?</summary>
<p>

<b>Stos</b> jest miejscem, gdzie wstawia się dane w sposób uporządkowany (obok siebie). Do stosu jest szybki dostęp, a pamięć (ograniczona z góry przez OS) jest zwalniana automatycznie gdy zmienna wychodzi poza swój zakres. Na stosie przechowywane są:
<ul><li>chwilowe rejestry procesora</li><li>zmienne lokalne</li><li>argumenty wywołania funkcji</li><li>wartość zwracana przez funkcję</li></ul>

<b>Sterta</b> jest miejscem, gdzie alokujesz pamięć, gdzie tylko jest ona wolna (przez co dostęp jest wolniejszy). Alokowanie na stercie daje większą elastyczność (limit pamięci nie jest ograniczony przez OS) – np. rozmiar tablicy nie musi być znany w trakcie działania programu. Należy pamiętać o zwolnieniu pamięci, żeby zapobiec tzw. wyciekom pamięci. Na stercie przechowywane są:
<ul><li>dynamicznie tworzone struktury danych</li><li>dynamicznie przydzialne obszary pamięci</li></ul>
</p>
</details>

---

<details>
<summary>Jak stworzyć klasę, której obiekty można inicjalizować tylko na stercie?</summary>
<p>

```cpp
class A {
public:
   ~A() = delete;
};
```

</p>
</details>

---

<details>
<summary>Przykład programu poprawnego składniowo w C, a niepoprawnego w C++</summary>
<p>

W C zapis `void fun()` oznacza funkcję o nieokreślonej liczbie parametrów, a `void fun(void)` oznacza funkcję nieprzyjmującą żadnych parametrów. W związku z tym poniższy program skompiluje się w C, a nie skompiluje się w C++.

```cpp
void func() { }

int main() {
   func("ala", "ma", 42, "koty");
}
```

W C możliwe jest wywołanie funkcji przed miejscem jej zadeklarowania. W C++ wymagana jest wcześniej przynajmniej deklaracja.

```cpp
int main() { 
   foo();
}  

int foo() { 
   printf("Hello"); 
   return 0;  
}
```

W C możliwe jest zadelarowanie zmiennej stałej bez zainicjowania jej wartości. W C++ nie jest to możliwe.

```cpp
int main() { 
    const int a;
    return 0; 
}
```

</p>
</details>

---



---

<details>
<summary>Czym się różni referencja od wskaźnika?</summary>
<p>

<ul><li>Referencje są stałe i nie można zmienić obiektu na który wskazuje</li><li>Nie można zaincjalizować pustej referencji, trzeba od razu wskazać na co ma wskazywać</li></ul>

</p>
</details>

---

<details>
<summary>Czym się różni wprowadzanie za pomocą <code>std::cin</code> a <code>getline</code>?</summary>
<p>

<ul><li><code>std::cin</code> za koniec łańcucha przyjmuje spację, tabulator lub enter.</li><li><code>getline(std::cin, variable)</code> umożliwia wczytywanie do <code>std::string</code> całych wierszów, a za koniec łańcucha uważa enter lub ustalony limit znaków <code>std::string</code></li></ul>

</p>
</details>

---

<details>
<summary>Co to jest metoda czysto wirtualna?</summary>
<p>

<ul><li>Kiedy metoda ma ` = 0 `. Nie ma implementacji, klasy pochodne będą **musiały** zaimplmenetować je same.</li><li>Nie można stworzyć obiektu klasy zawierającą przynajmniej jedną metodę wirutalną</li><li>Brak implementacji funkcji czysto wirtualnej to błąd linkera*</li></ul>

</p>
</details>

---

<details>
<summary>Co to jest klasa abstrakcyjna?</summary>
<p>

<ul><li>Klasa mająca zarówno zwykłe metody składowe i pole jak i metody czysto wyritualne</li><li>Nie można utworzyć obiektu takiej klasy (ma metody czysto wirutalne)</li><li>Można stworzyć wskaźnik na typ tej klasy</li><li>Dopiero obiekt klasy pochodnej, która zaimplementuje wszystkie brakujące metody, może zostać utworzony</li></ul>

</p>
</details>

---

<details>
<summary>Co to jest interfejs?</summary>
<p>

<ul><li>Klasa zawierająca jedynie czysto wirtualne metody publiczne (klasy dziedziczące muszą zaimplementować je sobie same)</li><li>Dobrą praktyką są komentarze w klasie pochodnej, że przesłaniamy (bądź implementujemy) metodę z klasy bazowej</li><li><code>override</code> jest opcjonalne, ale to dobra praktyka bo kompilator zgłosi problem przy ewentualnej literówce/błędzie w definicji</li></ul>

</p>
</details>

---

<details>
<summary>Cechy stałego wskaźnika <code>int* const ptr</code></summary>
<p>

<ul><li>Można zmienić zmienną (<code>*ptr += 2</code>)</li><li>Nie można przypisać do niego innego adresu</li></ul>

</p>
</details>

---

<details>
<summary>Cechy wskaźnika na stałą <code>const int* ptr</code></summary>
<p>

<ul><li>Nie można zmodyfikować wartości na którą wskazuje wskaźnik</li><li>Można przypisać do wskaźnika inny adres</li></ul>

</p>
</details>

---

<details>
<summary>Cechy stałego wskaźnika na stałą <code>const int * const ptr</code></summary>
<p>

<ul><li>Nie można zmodyfikować warotści na którą wskazuje wskaźnik</li><li>Nie można przypisać do wskaźnika innego adresu</li></ul>

</p>
</details>

---


<details>
<summary>W jakim miejscu nie można zastąpić słowa <code>class</code> słowem <code>struct</code>`?</summary>
<p>

W szablonach.

```cpp
template <class T>      // OK
(...)

template <typename T>   // OK
(...)

template <struct T>     // ERROR
```

</p>
</details>

---

---

---


---

<details>
<summary>Co tak naprawdę dzieje się wywołując operator <code>new</code>?</summary>
<p>

* Alokacja pamięci na stercie
* Wywołanie konstruktora klasy
* Przypisanie adresu tej pamięci do wskaźnika p

```cpp
auto p = new Data;
```

* `malloc` z języka C tylko alokuje pamięć, trzeba konstruktor wywołać ręcznie (`free` zwalnia pamięć)

</p>
</details>

---

<details>
<summary>Co to jest inwalidacja iteratorów?</summary>
<p>

Jeśli ustawimy iterator w jakiejś miejsce to w momencie wstawienia nowego elementu, jeśli kontener zmieni swoje miejsce w pamięci w celu zwiększenia objętości, iterator przestanie wskazywać nawet na kontener. W przypadku listy nie ma tego zjawiska.

</p>
</details>

---

---

<details>
<summary>Co to są white-boxy i black-boxy?</summary>
<p>

White-box
* Testowaniu oprogramowania z uwzględnieniem jego wewnętrznej struktury
* Używana zarówno przez testerów, jak i programistów
* Pozwala im zrozumieć, które linijki kodu są wykonane prawidłowo, a które nie
* Wymagana jest do tego podstawowa wiedza na temat programowania

Black-box
* Osoba testująca nie posiada dostępu do kodu źródłowego ani informacji na temat budowy programu, który testuje
* Znacznie większą szansę wykrycia błędów, jednak nie dają możliwości zweryfikowania ich źródła

</p>
</details>

Czego nie dziedziczymy C++
Pól statycznych.. CZEGO JESZCZE?





## Bibliografia

* http://home.agh.edu.pl/~glowacki/docs/matwykl/O-o/_ProgObiekt-C++14-Rozsz.pdf
