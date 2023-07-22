# std::variant

* Nowa klasa wariadyczna dostępna od C++17
* Bazuje na boost::variant (2004), różnią się jedynie nazwami metod

## Unie

* Wszystkie pola dzielą tą samą przestrzeń w pamięci
* Zajmuje tyle miejsca w pamięci ile największe pole (to zależy od platformy!)
* Tylko jedna pole jest dostępne (zapisywanie do tego pola czyni je aktywnym)
    * Czytanie innego to UB
* Ciekawe: może posiadać metody niewirtualne (żadko stosowane)

union data1 {
    int var1;
    long var2;
    float var3;
    double var4;
    bool var5;

    int64_t id;
    int list[3];
    char letter;
    Widget *ptr;
}

W zależności od architektury zarówno var2 (long) jak i list (tablica 3 elementowa int) może mieć 64 bit. Wtedy zapisywanie do var2 i czytanie z id jest ok. Ale na niektórych platformach long to 32 bity. 


* Nie ma mechanizmu stwierdzającego które pole rzeczywiście przechowuje jakąś wartość
    * Zazwyczaj trzyma isę tą informację trzymać poza unią


https://www.youtube.com/watch?v=FFZKH7jVjmg
10:11
