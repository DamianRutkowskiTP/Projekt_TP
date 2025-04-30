cmake_minimum_required(VERSION 3.10)
project(WojnaGra)

set(CMAKE_CXX_STANDARD 17)

# Dodaj katalog z nagłówkami (jeśli klasy.h jest w tym samym folderze, to wystarczy to)
include_directories(${CMAKE_SOURCE_DIR})

# Kompilacja głównego programu
add_executable(wojna tp_projekt2.cpp)

# Kompilacja testów (jeśli testy używają klasy.h, nie trzeba go tu dodawać osobno)
add_executable(tests test_tp_projekt2.cpp)