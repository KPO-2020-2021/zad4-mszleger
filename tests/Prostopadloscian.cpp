#include "./doctest/doctest.h"

#include <sstream>

#include "Prostopadloscian.hh"

/**
 * \brief Sprawdzanie poprawnego działania operatora porównania dwóch prostopadłościanów.
 */
TEST_CASE("test Operator porównania 1"){
  double parametry[] = {1, 2, 3};
  Prostopadloscian pr1, pr2;
  pr1[0].ustaw(parametry);
  pr2[0].ustaw(parametry);
  CHECK(pr1 == pr2);
}

/**
 * \brief Sprawdzanie poprawnego działania operatora porównania dwóch prostopadłościanów.
 */
TEST_CASE("test Operator porównania 2"){
  double parametry[] = {1, 2, 3};
  Prostopadloscian pr1, pr2;
  pr1[0].ustaw(parametry);
  CHECK_FALSE(pr1 == pr2);
}

/**
 * \brief Sprawdzanie poprawnego działania zanegowanego operatora porównania dwóch prostopadłościanów.
 */
TEST_CASE("test Operator zanegowanego porównania 1"){
  double parametry[] = {1, 2, 3};
  Prostopadloscian pr1, pr2;
  pr1[0].ustaw(parametry);
  pr2[0].ustaw(parametry);
  CHECK_FALSE(pr1 != pr2);
}

/**
 * \brief Sprawdzanie poprawnego działania operatora wpisującego wartości wierzchołków prostopadłościanu do strumienia.
 */
TEST_CASE("test Operator << 1"){
  std::stringstream strumien;
  double parametry1[] = {-1, -1, -1};
  double parametry2[] = { 1, -1, -1};
  double parametry3[] = {-1,  1, -1};
  double parametry4[] = { 1,  1, -1};
  double parametry5[] = {-1,  1,  1};
  double parametry6[] = { 1,  1,  1};
  double parametry7[] = {-1, -1,  1};
  double parametry8[] = { 1, -1,  1};
  std::string oczekiwanyRezultat = "   -1.0000000000   -1.0000000000   -1.0000000000\n\
    1.0000000000   -1.0000000000   -1.0000000000\n\
   -1.0000000000    1.0000000000   -1.0000000000\n\
    1.0000000000    1.0000000000   -1.0000000000\n\
   -1.0000000000    1.0000000000    1.0000000000\n\
    1.0000000000    1.0000000000    1.0000000000\n\
   -1.0000000000   -1.0000000000    1.0000000000\n\
    1.0000000000   -1.0000000000    1.0000000000\n";
  Prostopadloscian pr;
  pr[0].ustaw(parametry1);
  pr[1].ustaw(parametry2);
  pr[2].ustaw(parametry3);
  pr[3].ustaw(parametry4);
  pr[4].ustaw(parametry5);
  pr[5].ustaw(parametry6);
  pr[6].ustaw(parametry7);
  pr[7].ustaw(parametry8);
  strumien << pr;
  CHECK(strumien.str() == oczekiwanyRezultat);
}