#ifndef SCENA_HH
#define SCENA_HH

#include <vector>
#include <fstream>

#include "Wektor3D.hh"
#include "MacierzObrotu.hh"
#include "Prostopadloscian.hh"
#include "Wektoryzacja.hh"
#include "lacze_do_gnuplota.hh"

/**
 * \brief Struktura przechowująca dane o danym obiekcie, jego aktualnym położeniu i obrocie 
 */
struct ParametryObliektu {
  Prostopadloscian obiekt;               // Przechowuje wzorcową figurę geometryczną
  MacierzObrotu poprzedniObrot;          // Przechowuje macierz obrotu poprzedniego globalnego obrotu
  MacierzObrotu macierzObrotuGlobalna;   // Opisuje obrót obiektu względem globalnego układu współrzędnych
  MacierzObrotu macierzObrotuLokalna;    // Opisuje obrót obiektu względem lokalnego układu współrzędnych
  Wektor3D wektorTranslacji;             // Opisuje wektor translacji układu lokalnego w układzie globalnym
};

/**
 * \brief Klasa opisuje przestrzeń, w której znajdują się dane obiekty
 * 
 * Klasa umożliwia wczytywanie obiektów, manipulowanie nimi w przestrzeni i wyświetlanie położenia obiektów w przestrzeni za pomocą programu gnuplot.
 * Klasa rzuca wyjątek o kodzie 400, jeśli operacje (np. obrotu lub translacji) zostaną wywołane dla nieistniejącego obiektu.
 */
class Scena {
  private:
    PzG::LaczeDoGNUPlota  lacze;                           // Struktura za pomocą której odbywa się komunikacja z programem gnuplot
    std::vector <ParametryObliektu> obiektZParametrami;    // Kontener przechowujący wczytywane obiekty
  public:

    /**
     * \brief Konstruktor bezparametryczny
     * 
     * Inicjuje pracę gnuplota.
     */
    Scena();

    /**
     * \brief Metoda wczytuje obiekt z pliku o danej nazwie
     * 
     * Sposób zapisu obiektu (prostopadłościanu w pliku):
     * wektor przesunięcia figury względem środka globalnego układu współrzędnych
     * wektory przesunięcia poszczególnych wierzchołków figury względem środka jej lokalnego układu współrzędnych
     */
    bool wczytajObiekt(const std::string &nazwaPliku);

    /**
     * \brief Metoda przesówa obiekt o dany wektor
     */
    bool przesun(unsigned int numerObiektu, const Wektor3D &wektorTranslacji);

    /**
     * \brief Metoda obraca dany obiekt wokół środka globalnego układu współrzędnych
     */
    bool obrocGlobalnie(unsigned int numerObiektu, const MacierzObrotu &macierzObrotu);

    /**
     * \brief Metoda obraca dany obiekt wokół środka jego lokalnego układu współrzędnych
     */
    bool obrocLokalnie(unsigned int numerObiektu, const MacierzObrotu &macierzObrotu);

    /**
     * \brief Metoda aktualizuje wyświetlany obraz obiektów
     * 
     * Metoda jest wywoływana po operacjach obrotu lub translacji, aby umieścić obiekty w odpowiednich nowych położeniach.
     */
    bool wyswietl();

    /**
     * \brief Metoda przekazuje do wskazanego strumienia współrzędne wierzchołków obiektu o danym numerze
     */
    void wyswietlWspolrzedne(unsigned int numerObiektu, std::ostream &strumien)
    {
      if(numerObiektu >= obiektZParametrami.size())
        throw(400);
      for(unsigned int numerWierzcholka = 0; numerWierzcholka < 8; ++numerWierzcholka)
      {
        strumien << (this->obiektZParametrami[numerObiektu].macierzObrotuLokalna * this->obiektZParametrami[numerObiektu].obiekt[numerWierzcholka]) + (this->obiektZParametrami[numerObiektu].macierzObrotuGlobalna * this->obiektZParametrami[numerObiektu].wektorTranslacji) << std::endl; 
      }
    }

    /**
     * \brief Metoda ustawia macierz poprzedniego obrotu wartościami z podanej macierzy
     */
    void ustawMacierzPoprzedniegoObrotu(unsigned int numerObiektu, MacierzObrotu &macierz)
    {
      if(numerObiektu >= obiektZParametrami.size())
        throw(400);
      this->obiektZParametrami[numerObiektu].poprzedniObrot = macierz;
    }

    /**
     * \brief Metoda zwraca macierz ostatniego obrotu wykonanego na figurze
     */
    MacierzObrotu zwrocMacierzPoprzedniegoObrotu(unsigned int numerObiektu)
    {
      if(numerObiektu >= obiektZParametrami.size())
        throw(400);
      return obiektZParametrami[numerObiektu].poprzedniObrot;
    }

    /**
     * \brief Metoda zwraca złożoną macierz wszystkich obrotów danego obiektu względem środka globalnego układu współrzędnych
     */
    MacierzObrotu zwrocMacierzObrotu(unsigned int numerObiektu)
    {
      if(numerObiektu >= obiektZParametrami.size())
        throw(400);
      return obiektZParametrami[numerObiektu].macierzObrotuGlobalna; 
    }

    /**
     * \brief Metoda zwraca ilość wczytanych obiektów
     */
    unsigned int zwrocIloscObiektow()
    {
      return this->obiektZParametrami.size();
    }

    /**
     * \brief Metoda sprawdza równość odpowiednich krawędzi prostopadłościanu i wyświetla odpowiednie komunikaty
     */
    bool sprawdzBoki(unsigned int numerObiektu, std::ostream &strumien);

};

#endif