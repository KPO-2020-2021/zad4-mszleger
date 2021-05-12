#include "./doctest/doctest.h"
#include "Wektoryzacja.hh"

/**
 * \brief Sprawdzanie poprawnego działania funkcji Wymnoz.
 */
TEST_CASE("test Wymnoz 1"){
  double zestawDanych[] = {2, 4};
  double zestawDanychWzorcowych[] = {6, 12};
  double wspolczynnik = 3;
  bool rowne = true;

  Wymnoz(wspolczynnik, zestawDanych);
  // Sprawdzanie czy tablice zestawDanych i zestawDanychWzorcowych zawierają te same wartości.
  for(unsigned int x = 0; x < 2; ++x)
    if(zestawDanych[x] != zestawDanychWzorcowych[x])
      rowne = false;
  CHECK(rowne);
}

/**
 * \brief Sprawdzanie poprawnego działania funkcji Dodaj.
 */
TEST_CASE("test Dodaj 1"){
  double zestawDanych[] = {2, 4};
  double zestawDanychWzorcowych[] = {5, 7};
  double wspolczynnik = 3;
  bool rowne = true;

  Dodaj(wspolczynnik, zestawDanych);
  // Sprawdzanie czy tablice zestawDanych i zestawDanychWzorcowych zawierają te same wartości.
  for(unsigned int x = 0; x < 2; ++x)
    if(zestawDanych[x] != zestawDanychWzorcowych[x])
      rowne = false;
  CHECK(rowne);
}