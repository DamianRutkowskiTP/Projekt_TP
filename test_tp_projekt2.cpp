#include "klasy.h"
#include <cassert>
#include <iostream>

void test_stworzenie_talii() {
    Gra gra;
    auto talia = gra.stworzTalie();
    assert(talia.size() == 52);
    cout << "[OK] test_stworzenie_talii\n";
}

void test_sortowanie_kart() {
    Karta k1{10, 1};  // 10 Trefl
    Karta k2{12, 2};  // Q Pik
    assert(k2 > k1);
    assert(!(k1 > k2));
    cout << "[OK] test_sortowanie_kart\n";
}

void test_nazwa_karty() {
    Karta k{14, 3};  // A Kier
    assert(k.nazwa() == "A Kier");
    cout << "[OK] test_nazwa_karty\n";
}

int main() {
    test_stworzenie_talii();
    test_sortowanie_kart();
    test_nazwa_karty();
    cout << "Wszystkie testy zakończone sukcesem.\n";
    setlocale(LC_ALL, "Polish");

    return 0;
}
