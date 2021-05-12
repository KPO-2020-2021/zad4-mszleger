#ifndef PROSTOKAT_HH
#define PROSTOKAT_HH

#include "Wektor3D.hh"

/**
 * \brief Klasa modelująca prostopadłościan
 * 
 * Modelowany prostopadłościan jest obiektem składającym się z 8 wierzchołków.
 * Wierzchołki to obiekty klasy wektor, które wskazują położenie wierzchołków względem określonego przez nas środka figury.
 */
class Prostopadloscian {
  private:
    Wektor3D wierzcholki[8];                               // Wektory przechowujące względne położenie wierzchołków prostopadłościanu względem jego środka
  public:
    /**
     * \brief Przeciążenie operatora indeksującego do odczytu wartości wierzchołka o danym indeksie
     * 
     * Metoda zwraca wektor będący wierzchołkiem o danym indeksie.
     */
    Wektor3D  operator [] (unsigned int indeks) const {return wierzcholki[indeks];}

    /**
     * \brief Przeciążenie operatora indeksującego do zapisu nowej wartości wierzchołka o danym indeksie
     * 
     * Metoda zwraca rekurencję na wektor będący wierzchołkiem o danym indeksie.
     */
    Wektor3D& operator [] (unsigned int indeks){return wierzcholki[indeks];}
    
    /**
     * \brief Przeciążenie operatora porównywania dwóch obiektów klasy prostokąt
     * 
     * Przeciążenie zwraca true jeśli wszystkie odpowiadające sobie wierzchołki danego prostopadłościanu są sobie równe.
     * W przeciwnym razie zawraca wartość false.
     */
    bool operator == (const Prostopadloscian &prostopadloscian) const;
    
    /**
     * \brief Przeciążenie zanegowanego operatora porównywania dwóch obiektów klasy prostokąt
     * 
     * Przeciążenie zwraca false jeśli wszystkie odpowiadające sobie wierzchołki danego prostopadłościanu są sobie równe.
     * W przeciwnym razie zawraca wartość true.
     */
    bool operator != (const Prostopadloscian &prostopadloscian) const;
};

/**
 * \brief Przeciążenie operatora wypisywania wierzchołków prostopadłościanu do strumienia
 */
std::ostream& operator << (std::ostream &strumien, const Prostopadloscian &prostopadloscian);

#endif
