#include "klasy.h"
int main() {
    setlocale(LC_ALL, "Polish");

    Gra gra;

    gra.przygotujGre();
    gra.wyswietlRozdanie();
    gra.rozpocznijGre();
    return 0;
}