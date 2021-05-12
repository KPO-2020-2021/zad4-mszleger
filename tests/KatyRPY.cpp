#include "./doctest/doctest.h"
#include "KatyRPY.hh"


/**
 * \brief Sprawdzanie poprawnego działania operatora porównania dwóch wektorów.
 */
TEST_CASE("test Wypełnianie macierzy RPY 1"){
  double parametry1[] = {1, 2, 3};
  double parametry2[] = {1, 0, 0, 1, 0, 1, 0, 2, 0, 0, 1, 3, 0, 0, 0, 1};
  Wektor3D wektor(parametry1);
  Macierz4X4 macierz1;
  Macierz4X4 macierz2(parametry2);
  Wypelnij(macierz1, 0, 0, 0, wektor);
  CHECK(macierz1 == macierz2);
}