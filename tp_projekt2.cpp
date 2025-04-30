/*
Damian Rutkowski 203304
Aleksander Stachurski 207394

Główny plik do uruchomienia
*/
#include "klasy.hpp"
int main() {
    setlocale(LC_ALL, "pl_PL.UTF-8"); //polskie znaki

    Gra gra; // Obiekt gry
    
    gra.przygotujGre();      // Przygotowanie talii
    gra.rozpocznijGre();     // Start rozgrywki
    
    return 0;
}