#ifndef KATYRPY_HH
#define KATYRPY_HH

#include <cmath>

#include "Wektor3D.hh"
#include "Macierz.hh"

/**
 * \brief Klasa modelująca macierz o wymiarach 4x4.
 * 
 * Klasa jest instancją klasy Macierz, której rozmiar został określony jako 4x4, a typ przechowywanych współrzędnych jako double.
 */
typedef Macierz <4, double> Macierz4X4;

/**
 * \brief Funkcja wypełniająca Macierz4x4, tak aby umożliwiała wykonanie operacji obrotu o kąty RPY i transformacji o podany wektor.
 */
void Wypelnij(Macierz4X4 &macierz, double alpha, double beta, double gamma, const Wektor3D &translacja);

#endif