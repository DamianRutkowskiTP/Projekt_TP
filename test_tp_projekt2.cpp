/*
Damian Rutkowski 203304
Aleksander Stachurski 207394

Plik z testami itp.
*/

#include "klasy.hpp"
#include <cassert>
#include <iostream>

// Test tworzenia talii
void test_stworzenie_talii() { 
    Gra gra;
    auto talia = gra.stworzTalie();
    assert(talia.size() == 52);
    cout << "[OK] test_stworzenie_talii\n";
}

// Test sortowania kart
void test_sortowanie_kart() {
    Karta k1{ 10, 1 };
    Karta k2{ 12, 2 };
    assert(k2 > k1);
    assert(!(k1 > k2));
    cout << "[OK] test_sortowanie_kart\n";
}

// Test poprawnego nazywania kart
void test_nazwa_karty() {
    Karta k{14, 3};
    assert(k.nazwa() == "A Kier");
    cout << "[OK] test_nazwa_karty\n";
}

int main() {
    test_stworzenie_talii();
    test_sortowanie_kart();
    test_nazwa_karty();
    cout << "Wszystkie testy zakończone sukcesem.\n";
    return 0;
}
