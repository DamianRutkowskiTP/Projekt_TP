
# Techniki Programowania - projekt 2 - zadanie 4

ACiR 4 - Damian Rutkowski 203304, Aleksander Stachurski 207394

Zadanie 4:
Napisz program symulujący karcianą grę w wojnę. </br>
Opis zasad pod adresem http://pl.wikipedia.org/wiki/Wojna_(gra_karciana)  </br>
Talię kart reprezentuj, jako wektor (vector) STL, którego elementami są karty. Do reprezentacji zbioru kart posiadanych przez każdego z graczy wykorzystaj kolejkę (queue) STL. Gracze wykładają karty na stół, gdzie są one porównywane. 

Wymaganie dodatkowe:
Zdefiniuj strukturę danych do reprezentacji stołu wykorzystując w jej definicji elementy biblioteki STL. Losowanie talii należy przeprowadzić w osobnym wątku i po zakończeniu przekazać karty do graczy (std::future, std::async, std::promise)

tp_projekt2.cpp - Główny plik projektu </br>
klasy.hpp - Wszystkie klasy, funkcje, wektory itp.</br>
test_tp_projekt2.cpp - 3 testy w cmake</br>
CMakeLists.txt - Plik konfiguracyjny CMake</br>
