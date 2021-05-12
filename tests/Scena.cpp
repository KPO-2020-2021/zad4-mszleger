#include "./doctest/doctest.h"

#include <sstream>

#include "Scena.hh"

/**
 * \brief Sprawdzanie poprawnego działania metody zwracającej ilość obiektów w scenie.
 */
TEST_CASE("test Metoda zwracająca ilość obiektów 1"){
  unsigned int wzorcowyWynik = 2;
  Scena scena;
  scena.wczytajObiekt("../datasets/obiekt4.dat");
  scena.wczytajObiekt("../datasets/obiekt5.dat");
  CHECK(scena.zwrocIloscObiektow() == wzorcowyWynik);
}

/**
 * \brief Sprawdzanie poprawnego działania metod ustawiającej i zwracającej macierz poprzedniego obrotu.
 */
TEST_CASE("test Metoda zwracająca ilość obiektów 1"){
  double parametry[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  MacierzObrotu macierz;
  Scena scena;
  macierz.ustaw(parametry);
  scena.wczytajObiekt("../datasets/obiekt1.dat");
  scena.ustawMacierzPoprzedniegoObrotu(0, macierz);
  CHECK(scena.zwrocMacierzPoprzedniegoObrotu(0) == macierz);
}

/**
 * \brief Sprawdzanie poprawnego działania metody wczytującej obiekt z pliku i wypisującej współrzędne wierzchołków
 */
TEST_CASE("test Metoda wczytująca i wypisująca 1"){
  std::stringstream strumien;
  std::string wzorcowyWynik = "   40.0000000000  -10.0000000000  -10.0000000000\n\
   60.0000000000  -10.0000000000  -10.0000000000\n\
   40.0000000000   10.0000000000  -10.0000000000\n\
   60.0000000000   10.0000000000  -10.0000000000\n\
   40.0000000000   10.0000000000   10.0000000000\n\
   60.0000000000   10.0000000000   10.0000000000\n\
   40.0000000000  -10.0000000000   10.0000000000\n\
   60.0000000000  -10.0000000000   10.0000000000\n";
  Scena scena;
  scena.wczytajObiekt("../datasets/obiekt1.dat");
  scena.wyswietlWspolrzedne(0, strumien);
  CHECK(strumien.str() == wzorcowyWynik);
}

/**
 * \brief Sprawdzanie poprawnego działania metody przesuwającej obiekt o zadany wektor
 */
TEST_CASE("test Translacja 1"){
  std::stringstream strumien;
  std::string wzorcowyWynik = "  140.0000000000  190.0000000000  290.0000000000\n\
  160.0000000000  190.0000000000  290.0000000000\n\
  140.0000000000  210.0000000000  290.0000000000\n\
  160.0000000000  210.0000000000  290.0000000000\n\
  140.0000000000  210.0000000000  310.0000000000\n\
  160.0000000000  210.0000000000  310.0000000000\n\
  140.0000000000  190.0000000000  310.0000000000\n\
  160.0000000000  190.0000000000  310.0000000000\n";
  Scena scena;
  double parametry[] = {100, 200, 300};
  Wektor3D wektor(parametry);
  scena.wczytajObiekt("../datasets/obiekt1.dat");
  scena.przesun(0, wektor);
  scena.wyswietlWspolrzedne(0, strumien);
  CHECK(strumien.str() == wzorcowyWynik);
}

/**
 * \brief Sprawdzanie poprawnego działania metody obracającej obiekt względem środka układu współrzędnych
 */
TEST_CASE("test Obrót globalny 1"){
  std::stringstream strumien;
  std::string wzorcowyWynik = "   40.0000000000  -35.0000000000   33.3012701892\n\
   60.0000000000  -35.0000000000   33.3012701892\n\
   40.0000000000  -15.0000000000   33.3012701892\n\
   60.0000000000  -15.0000000000   33.3012701892\n\
   40.0000000000  -15.0000000000   53.3012701892\n\
   60.0000000000  -15.0000000000   53.3012701892\n\
   40.0000000000  -35.0000000000   53.3012701892\n\
   60.0000000000  -35.0000000000   53.3012701892\n";
  Scena scena;
  MacierzObrotu macierz;
  generujMacierzObrotu(macierz, 30, OX);
  scena.wczytajObiekt("../datasets/obiekt4.dat");
  scena.obrocGlobalnie(0, macierz);
  scena.wyswietlWspolrzedne(0, strumien);
  CHECK(strumien.str() == wzorcowyWynik);
}

/**
 * \brief Sprawdzanie poprawnego działania metody obracającej obiekt względem środka jej lokalnego układu współrzędnych
 */
TEST_CASE("test Obrót lokalny 1"){
  std::stringstream strumien;
  std::string wzorcowyWynik = "   40.0000000000   -3.6602540378  -13.6602540378\n\
   60.0000000000   -3.6602540378  -13.6602540378\n\
   40.0000000000   13.6602540378   -3.6602540378\n\
   60.0000000000   13.6602540378   -3.6602540378\n\
   40.0000000000    3.6602540378   13.6602540378\n\
   60.0000000000    3.6602540378   13.6602540378\n\
   40.0000000000  -13.6602540378    3.6602540378\n\
   60.0000000000  -13.6602540378    3.6602540378\n";
  Scena scena;
  MacierzObrotu macierz;
  generujMacierzObrotu(macierz, 30, OX);
  scena.wczytajObiekt("../datasets/obiekt1.dat");
  scena.obrocLokalnie(0, macierz);
  scena.wyswietlWspolrzedne(0, strumien);
  CHECK(strumien.str() == wzorcowyWynik);
}

/**
 * \brief Sprawdzanie poprawnego działania metody zwracającej macierz obrotu globalnego
 */
TEST_CASE("test Obrót globalny 1"){
  Scena scena;
  MacierzObrotu macierz;
  generujMacierzObrotu(macierz, 30, OX);
  scena.wczytajObiekt("../datasets/obiekt1.dat");
  scena.obrocGlobalnie(0, macierz);
  CHECK(scena.zwrocMacierzObrotu(0) == macierz);
}

/**
 * \brief Sprawdzanie poprawnego działania metody sprawdzającej równość odpowiednich krawędzi prosotpadłościanu
 */
TEST_CASE("test Sprawdzanie boków 1"){
  std::stringstream strumien;
  std::string wzorcowyWynik = ":) Zestaw krawędzi numer 1 jest sobie równy.\n\
Dlugosc pierwszego boku: 20.00000000000000000000\n\
  Dlugosc drugiego boku: 20.00000000000000000000\n\
 Dlugosc trzeciego boku: 20.00000000000000000000\n\
 Dlugosc czwartego boku: 20.00000000000000000000\n\
:) Zestaw krawędzi numer 2 jest sobie równy.\n\
Dlugosc pierwszego boku: 20.00000000000000000000\n\
  Dlugosc drugiego boku: 20.00000000000000000000\n\
 Dlugosc trzeciego boku: 20.00000000000000000000\n\
 Dlugosc czwartego boku: 20.00000000000000000000\n\
:) Zestaw krawędzi numer 3 jest sobie równy.\n\
Dlugosc pierwszego boku: 20.00000000000000000000\n\
  Dlugosc drugiego boku: 20.00000000000000000000\n\
 Dlugosc trzeciego boku: 20.00000000000000000000\n\
 Dlugosc czwartego boku: 20.00000000000000000000\n";
  Scena scena;
  scena.wczytajObiekt("../datasets/obiekt1.dat");
  scena.sprawdzBoki(0, strumien);
  CHECK(strumien.str() == wzorcowyWynik);
}