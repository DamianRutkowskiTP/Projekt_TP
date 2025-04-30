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

class Koloryy {
private:
    const string reset = "\033[0m";
    const string red = "\033[31m";
    const string green = "\033[32m";
    const string yellow = "\033[33m";
    const string blue = "\033[34m";

public:
    string resetuj() const { return reset; }
    string czerwony() const { return red; }
    string zielony() const { return green; }
    string zolty() const { return yellow; }
    string niebieski() const { return blue; }
};


struct Karta {
    int wartosc;
    int kolor;

    string nazwa() const {
        const string figury[] = { "2","3","4","5","6","7","8","9","10","W","Q","K","A" };
        const string kolory[] = { " Karo"," Trefl"," Pik"," Kier" };
        return figury[wartosc - 2] + kolory[kolor];
    }

    bool operator>(const Karta& druga) const {
        return wartosc > druga.wartosc;
    }
};

class Gra {
private:
    vector<Karta> talia;
    queue<Karta> gracz1, gracz2;
    vector<Karta> rozgrywka_teraz;
    Koloryy kolorys;



    vector<Karta> tasujTalie(vector<Karta> talia) {
        srand(time(0));
        random_device rd;
        mt19937 g(rd());
        shuffle(talia.begin(), talia.end(), g);
        return talia;
    }

    void wyswietlKartyGracza(const queue<Karta>& gracz, int numer) {
        queue<Karta> kopia = gracz;
        cout << "\nKarty Gracza " << numer << " (" << kopia.size() << "):\n";
        while (!kopia.empty()) {
            cout << kopia.front().nazwa() << ", ";
            kopia.pop();
        }
    }

    void rozdajKarty() {
        for (size_t i = 0; i < talia.size(); i++)
            (i % 2 ? gracz2 : gracz1).push(talia[i]);
    }

    void wojna(bool& stop) {

        if (gracz1.size() < 2 || gracz2.size() < 2) {
            stop = true;
            cout << kolorys.czerwony() << "Jeden z graczy nie ma wystarczająco kart do wojny!\n" << kolorys.resetuj();

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
        cout << "WOJNA! Karty na stole: " << rozgrywka_teraz.size() / 2;
        if (((rozgrywka_teraz.size() / 2) % 5) == 0)
        {
            cout << " par\n";
        }
        else
        {
            cout << " pary\n";
        }

        if (wojna_gracz1 > wojna_gracz2)
        {
            cout << "Wygrał wojnę gracz 1: ";
            cout << kolorys.zielony() << wojna_gracz1.nazwa() << kolorys.resetuj();
            cout << " VS ";
            cout << kolorys.czerwony() << wojna_gracz2.nazwa() << kolorys.resetuj();
            for (size_t i = 0; i < rozgrywka_teraz.size(); i += 2)
            {
                gracz1.push(rozgrywka_teraz[i]);
            }
            for (size_t i = 1; i < rozgrywka_teraz.size(); i += 2)
            {
                gracz1.push(rozgrywka_teraz[i]);
            }
        }
        else if (wojna_gracz2 > wojna_gracz1)
        {
            cout << "Wygrał wojnę gracz 2: ";
            cout << kolorys.czerwony() << wojna_gracz1.nazwa() << kolorys.resetuj();
            cout << " VS ";
            cout << kolorys.zielony() << wojna_gracz2.nazwa() << kolorys.resetuj();
            for (size_t i = 0; i < rozgrywka_teraz.size(); i += 2)
            {
                gracz2.push(rozgrywka_teraz[i]);
            }
            for (size_t i = 1; i < rozgrywka_teraz.size(); i += 2)
            {
                gracz2.push(rozgrywka_teraz[i]);
            }
        }
        else
        {
            cout << "Remis: ";
            cout << kolorys.zolty() << wojna_gracz1.nazwa() << kolorys.resetuj();
            cout << " VS ";
            cout << kolorys.zolty() << wojna_gracz2.nazwa() << kolorys.resetuj();
            cout << "\nWojna kolejny raz\n";

            wojna(stop);
        }
        cout << endl;
    }


public:

    vector<Karta> stworzTalie() {
        vector<Karta> nowa_talia;
        for (int w = 2; w <= 14; w++)
            for (int k = 0; k < 4; k++)
                nowa_talia.push_back({ w, k });
        return nowa_talia;
    }

    void ustawKolor(const string& kod) {
        cout << kod;
    }

    void wyswietlRozdanie() {
        wyswietlKartyGracza(gracz1, 1);
        wyswietlKartyGracza(gracz2, 2);
    }

    void przygotujGre() {
        auto przyszlaTalia = async(launch::async, [this] {
            auto t = this->stworzTalie();
            t = this->tasujTalie(t);
            t = this->tasujTalie(t);
            t = this->tasujTalie(t);
            t = this->tasujTalie(t);
            t = this->tasujTalie(t);
            t = this->tasujTalie(t);
            t = this->tasujTalie(t);
            t = this->tasujTalie(t);
            return this->tasujTalie(t);
            });
        talia = przyszlaTalia.get();
        rozdajKarty();
    }

    void rozpocznijGre() {
        int rundy = 0;
        bool stop = false;
        while (!gracz1.empty() && !gracz2.empty()) {
            rundy++;
            cout << "\nRunda " << rundy << ":\n";

            Karta k1 = gracz1.front();
            Karta k2 = gracz2.front();
            gracz1.pop();
            gracz2.pop();
            rozgrywka_teraz = { k1, k2 };

            if (k1 > k2) {
                for (size_t i = rozgrywka_teraz.size(); i-- > 0; ) {
                    gracz1.push(rozgrywka_teraz[i]);
                }

                cout << "Wygrywa gracz 1: ";
                cout << kolorys.zielony() << k1.nazwa() << kolorys.resetuj();
                cout << " VS ";
                cout << kolorys.czerwony() << k2.nazwa() << kolorys.resetuj();
                cout << endl;
            }
            else if (k2 > k1) {
                for (size_t i = 0; i < rozgrywka_teraz.size(); i++) {
                    gracz2.push(rozgrywka_teraz[i]);
                }
                cout << "Wygrywa gracz 2: ";
                cout << kolorys.czerwony() << k1.nazwa() << kolorys.resetuj();
                cout << " VS ";
                cout << kolorys.zielony() << k2.nazwa() << kolorys.resetuj();
                cout << endl;
            }
            else {
                wojna(stop);
            }

            cout << "(Gracz 1: " << gracz1.size() << " | Gracz 2: " << gracz2.size() << ")\n";
            if (stop == true)
            {
                break;
            }
        }

        cout << "\n\n Koniec gry po " << rundy << " rundach!\n";

        cout << "Zwycięzca: " << (gracz1.size() > gracz2.size() ? "Gracz 1" : "Gracz 2") << endl;
    }
};
#endif