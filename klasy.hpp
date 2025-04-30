/*
Damian Rutkowski 203304
Aleksander Stachurski 207394

Plik z klasami, funkcjami, wektorami itp.
*/

#ifndef GRA_H
#define GRA_H
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <random>
#include <future>
#include <chrono>
#include <locale>
#include <cassert>
using namespace std;

// Klasa do kolorowego tekstu w konsoli
class Kolorowanie {
private:
    // Kody ANSI do kolorów
    const string reset = "\033[0m";   // Reset koloru
    const string red = "\033[31m";    // Czerwony
    const string green = "\033[32m";  // Zielony
    const string yellow = "\033[33m"; // Żółty
    const string blue = "\033[34m";   // Niebieski

public:
    // Metody do ustawiania kolorów
    string resetuj() const { return reset; }
    string czerwony() const { return red; }
    string zielony() const { return green; }
    string zolty() const { return yellow; }
    string niebieski() const { return blue; }
};

// Struktura reprezentująca pojedynczą kartę
struct Karta {
    int wartosc;
    int kolor;

    // Zwraca ładną nazwę karty
    string nazwa() const {
        const string figury[] = { "2","3","4","5","6","7","8","9","10","W","Q","K","A" };
        const string kolory[] = { " Karo"," Trefl"," Pik"," Kier" };
        return figury[wartosc - 2] + kolory[kolor];
    }

    // Porównuje karty po wartości
    bool operator>(const Karta& druga) const {
        return wartosc > druga.wartosc;
    }
};

// Główna klasa gry
class Gra {
private:
    vector<Karta> talia;           // Cała talia kart
    queue<Karta> gracz1, gracz2;   // Karty graczy
    vector<Karta> rozgrywka_teraz; // Karty aktualnie na stole
    Kolorowanie kolor;             // Do kolorowego wyświetlania

    // Tasowanie talii
    vector<Karta> tasujTalie(vector<Karta> talia) {
        srand(time(0));            
        random_device rd;
        mt19937 g(rd());
        shuffle(talia.begin(), talia.end(), g);
        return talia;
    }

    // Rozdaje karty graczom na zmianę
    void rozdajKarty() {
        for (size_t i = 0; i < talia.size(); i++) {
            if (i % 2) { // Nieparzyste indeksy - gracz 2
                gracz2.push(talia[i]);
            }
            else {       // Parzyste indeksy - gracz 1
                gracz1.push(talia[i]);
            }
        }
    }

    // Obsługa wojny (gdy karty równe)
    void wojna(bool& stop) {
        // Sprawdź czy gracze mają dość kart
        if (gracz1.size() < 2 || gracz2.size() < 2) {
            stop = true; // Koniec gry
            cout << kolor.czerwony() << "Jeden z graczy nie ma wystarczająco kart do wojny!\n" << kolor.resetuj();

            // Rozdaj karty graczowi z więcej kartami
            while (!rozgrywka_teraz.empty()) {
                if (gracz1.size() > gracz2.size()) {
                    gracz1.push(rozgrywka_teraz.back());
                }
                else {
                    gracz2.push(rozgrywka_teraz.back());
                }
                rozgrywka_teraz.pop_back();
            }
            return;
        }

        // Dobierz karty do wojny (po 2)
        Karta wojna_gracz1 = gracz1.front();
        Karta wojna_gracz2 = gracz2.front();
        for (int i = 0; i < 2; i++) {
            if (!gracz1.empty()) {
                rozgrywka_teraz.push_back(gracz1.front());
                wojna_gracz1 = gracz1.front();
                gracz1.pop();
            }
            if (!gracz2.empty()) {
                rozgrywka_teraz.push_back(gracz2.front());
                wojna_gracz2 = gracz2.front();
                gracz2.pop();
            }
        }

        // Wyświetl info o wojnie
        cout << "WOJNA! Karty na stole: " << rozgrywka_teraz.size() / 2;
        if (((rozgrywka_teraz.size() / 2) % 5) == 0) {
            cout << " par\n";
        }
        else {
            cout << " pary\n";
        }

        // sprawdzanie kto wygrał wojnę
        if (wojna_gracz1 > wojna_gracz2) {
            cout << "Wygrał wojnę gracz 1: ";
            cout << kolor.zielony() << wojna_gracz1.nazwa() << kolor.resetuj();
            cout << " VS ";
            cout << kolor.czerwony() << wojna_gracz2.nazwa() << kolor.resetuj();
            // Gracz 1 zabiera karty
            for (size_t i = 0; i < rozgrywka_teraz.size(); i += 2) {
                gracz1.push(rozgrywka_teraz[i]);
            }
            for (size_t i = 1; i < rozgrywka_teraz.size(); i += 2) {
                gracz1.push(rozgrywka_teraz[i]);
            }
        }
        else if (wojna_gracz2 > wojna_gracz1) {
            cout << "Wygrał wojnę gracz 2: ";
            cout << kolor.czerwony() << wojna_gracz1.nazwa() << kolor.resetuj();
            cout << " VS ";
            cout << kolor.zielony() << wojna_gracz2.nazwa() << kolor.resetuj();
            // Gracz 2 zabiera karty
            for (size_t i = 0; i < rozgrywka_teraz.size(); i += 2) {
                gracz2.push(rozgrywka_teraz[i]);
            }
            for (size_t i = 1; i < rozgrywka_teraz.size(); i += 2) {
                gracz2.push(rozgrywka_teraz[i]);
            }
        }
        else {
            //warunek remisu
            cout << "Remis: ";
            cout << kolor.zolty() << wojna_gracz1.nazwa() << kolor.resetuj();
            cout << " VS ";
            cout << kolor.zolty() << wojna_gracz2.nazwa() << kolor.resetuj();
            cout << "\nWojna kolejny raz\n";
            wojna(stop); // rekurencja gdy kolejna wojna
        }
        cout << endl;
    }

public:
    // tworzenie talii
    vector<Karta> stworzTalie() {
        vector<Karta> nowa_talia;
        for (int w = 2; w <= 14; w++)
        {
            for (int k = 0; k < 4; k++)
            {
                nowa_talia.push_back({ w, k });
            }
                
        }
            
        return nowa_talia;
    }

    // Ustawianie koloru tekstu
    void ustawKolor(const string& kod) {
        cout << kod;
    }

    // tasowanie i rozdanie
    void przygotujGre() {
        auto przyszlaTalia = async(launch::async, [this] {
            auto t = this->stworzTalie();
            // tasowanie kilka razy
            for (int i = 0; i < 8; i++) {
                t = this->tasujTalie(t);
            }
            return t;
            });
        talia = przyszlaTalia.get(); // Pobieranie talii
        rozdajKarty();
    }

    // główna pętla gry
    void rozpocznijGre() {
        int rundy = 0;
        bool stop = false;

        // gra się toczy póki ktoś nie zostanie bez kart
        while (!gracz1.empty() && !gracz2.empty() && !stop) {
            rundy++;
            cout << "\nRunda " << rundy << ":\n";

            // wykładanie po karcie
            Karta k1 = gracz1.front();
            Karta k2 = gracz2.front();
            gracz1.pop();
            gracz2.pop();
            rozgrywka_teraz = { k1, k2 };

            // Porywanie kart
            if (k1 > k2) {
                // Gracz 1 wygrywa
                for (size_t i = rozgrywka_teraz.size(); i-- > 0; ) {
                    gracz1.push(rozgrywka_teraz[i]);
                }
                cout << "Wygrywa gracz 1: ";
                cout << kolor.zielony() << k1.nazwa() << kolor.resetuj();
                cout << " VS ";
                cout << kolor.czerwony() << k2.nazwa() << kolor.resetuj();
                cout << endl;
            }
            else if (k2 > k1) {
                // Gracz 2 wygrywa
                for (size_t i = 0; i < rozgrywka_teraz.size(); i++) {
                    gracz2.push(rozgrywka_teraz[i]);
                }
                cout << "Wygrywa gracz 2: ";
                cout << kolor.czerwony() << k1.nazwa() << kolor.resetuj();
                cout << " VS ";
                cout << kolor.zielony() << k2.nazwa() << kolor.resetuj();
                cout << endl;
            }
            else {
                // Remis - wojna
                cout << kolor.zolty() << k1.nazwa() << kolor.resetuj();
                cout << " VS ";
                cout << kolor.zolty() << k2.nazwa() << kolor.resetuj() << endl;
                wojna(stop);
            }

            // Wyświetl stan gry
            cout << "(Gracz 1: " << gracz1.size() << " | Gracz 2: " << gracz2.size() << ")\n";
            if (stop == true) {
                break;
            }
        }

        // Koniec gry - wyświetl wynik
        cout << "\n\nKoniec gry po " << rundy << " rundach!\n";
        if (gracz1.size() > gracz2.size()) {
            cout << "Zwycięzca: Gracz 1" << endl;
        }
        else {
            cout << "Zwycięzca: Gracz 2" << endl;
        }
        cout << "\nNaciśnij enter aby zakończyć program..." << endl;
        cin.get();
    }
};
#endif