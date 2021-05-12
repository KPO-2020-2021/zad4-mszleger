#include "../include/Scena.hh"

Scena::Scena()
{
  lacze.DodajNazwePliku("../datasets/temp_scena.dat",PzG::RR_Ciagly,2);
  lacze.ZmienTrybRys(PzG::TR_3D);
  lacze.UstawZakresY(-70,70);
  lacze.UstawZakresX(-70,70);
  lacze.UstawZakresZ(-70,70);
}

bool Scena::wczytajObiekt(const std::string &nazwaPliku)
{
  std::fstream plik;
  ParametryObliektu wczytywanyObiekt;

  wczytywanyObiekt.macierzObrotuGlobalna(0, 0) = 1;
  wczytywanyObiekt.macierzObrotuGlobalna(1, 1) = 1;
  wczytywanyObiekt.macierzObrotuGlobalna(2, 2) = 1;

  wczytywanyObiekt.macierzObrotuLokalna(0, 0) = 1;
  wczytywanyObiekt.macierzObrotuLokalna(1, 1) = 1;
  wczytywanyObiekt.macierzObrotuLokalna(2, 2) = 1;



  plik.open(nazwaPliku);                                           // Otwieranie pliku
  if(plik.is_open() == false)                                      // Sprawdzanie czy udało się otworzyć plik - zwracanie false jeśli nie
    return false;
  plik >> wczytywanyObiekt.wektorTranslacji;
  for(unsigned int x = 0; x < 8; ++x)
  {
    plik >> wczytywanyObiekt.obiekt[x];
  }
  if(plik.fail() == true)              // Sprawdzanie czy wystąpił błąd podczas próby odczyt lub punkty nie są równe
  {
    plik.close();                                                // Zamykanie pliku
    return false;
  }
  plik.close();                                                    // Zamykanie pliku
  obiektZParametrami.push_back(wczytywanyObiekt);
  return true;
}

bool Scena::przesun(unsigned int numerObiektu, const Wektor3D &wektorTranslacji)
{
  if(numerObiektu >= obiektZParametrami.size())
    throw(400);
  if(wektorTranslacji.modul() == 0)
    return false;
  this->obiektZParametrami[numerObiektu].wektorTranslacji = this->obiektZParametrami[numerObiektu].wektorTranslacji + wektorTranslacji;
  return true;
}

bool Scena::obrocGlobalnie(unsigned int numerObiektu, const MacierzObrotu &macierzObrotu)
{
  if(numerObiektu >= obiektZParametrami.size())
    throw(400);
  this->obiektZParametrami[numerObiektu].macierzObrotuGlobalna = this->obiektZParametrami[numerObiektu].macierzObrotuGlobalna * macierzObrotu;
  return true;
}

bool Scena::obrocLokalnie(unsigned int numerObiektu, const MacierzObrotu &macierzObrotu)
{
  if(numerObiektu >= obiektZParametrami.size())
    throw(400);
  this->obiektZParametrami[numerObiektu].macierzObrotuLokalna = this->obiektZParametrami[numerObiektu].macierzObrotuLokalna * macierzObrotu;
  return true;
}

bool Scena::wyswietl()
{
  std::fstream plik;
  plik.open("../datasets/temp_scena.dat", std::fstream::out);                        // Otwieranie pliku
  if(plik.is_open() == false)                                      // Sprawdzanie czy udało się otworzyć plik - zwracanie false jeśli nie
    return false;
  
  unsigned int opisScian[6][4] = {{0, 1, 2, 3}, {2, 3, 4, 5}, {4, 5, 6, 7}, {6, 7, 0, 1}, {1, 3, 7, 5}, {0, 2, 6, 4}}; // Zapisuje numery wierzchołków w odpowiedniej kolejności, z których będą tworzone ściany wyświetlanej bryły

  for(unsigned int numerObiektu = 0; numerObiektu < this->obiektZParametrami.size(); ++numerObiektu) // Zapisywanie wszystkich obiektów do zapisu
  {
    for(unsigned int numerSciany = 0; numerSciany < 6; ++numerSciany)
    {
      for(unsigned int numerWierzcholka = 0; numerWierzcholka < 4; ++numerWierzcholka)
      {
        plik << (this->obiektZParametrami[numerObiektu].macierzObrotuLokalna * this->obiektZParametrami[numerObiektu].obiekt[opisScian[numerSciany][numerWierzcholka]]) + (this->obiektZParametrami[numerObiektu].macierzObrotuGlobalna * this->obiektZParametrami[numerObiektu].wektorTranslacji) << std::endl;
        if(numerWierzcholka == 1)
          plik << std::endl;
      }
      plik << std::endl << std::endl;
    }
  }

  if(plik.fail())                                                  // Sprawdzanie czy wystąpił błąd podczas zapisywania
  {
    plik.close();                                                // Zamykanie pliku
    return false;
  }
  plik.close();                                                    // Zamykanie pliku

  lacze.Rysuj();
  return true;
}

bool Scena::sprawdzBoki(unsigned int numerObiektu, std::ostream &strumien)
{

  unsigned int zestawyKrawedzi[3][8] = {{0, 1, 2, 3, 4, 5, 6, 7}, {0, 2, 1, 3, 7, 5, 6, 4}, {0, 6, 1, 7, 3, 5, 2, 4}};
  bool czyRowne = true;
  double tmpModul = 0;

  for(unsigned int zestawKrawedzi = 0; zestawKrawedzi < 3; ++zestawKrawedzi)
  {
    czyRowne = true;
    // Sprawdzanie równości długości krawędzi w danym zestawie
    for(unsigned int numerPary = 0; numerPary < 4; ++numerPary)
    {
      if(numerPary == 0)
        tmpModul = (this->obiektZParametrami[numerObiektu].obiekt[zestawyKrawedzi[zestawKrawedzi][2 * numerPary]] - this->obiektZParametrami[numerObiektu].obiekt[zestawyKrawedzi[zestawKrawedzi][2 * numerPary + 1]]).modul();
      else
        if(tmpModul != (this->obiektZParametrami[numerObiektu].obiekt[zestawyKrawedzi[zestawKrawedzi][2 * numerPary]] - this->obiektZParametrami[numerObiektu].obiekt[zestawyKrawedzi[zestawKrawedzi][2 * numerPary + 1]]).modul())
          czyRowne = false;
    }
    if(czyRowne)
      strumien << ":) Zestaw krawędzi numer " << zestawKrawedzi + 1 << " jest sobie równy." << std::endl;
    else
      strumien << ":O Zestaw krawędzi numer " << zestawKrawedzi + 1 << " nie jest sobie równy." << std::endl;
    strumien << std::setw(15) << std::fixed << std::setprecision(20) <<  "Dlugosc pierwszego boku: " << (this->obiektZParametrami[numerObiektu].obiekt[zestawyKrawedzi[zestawKrawedzi][0]] - this->obiektZParametrami[numerObiektu].obiekt[zestawyKrawedzi[zestawKrawedzi][1]]).modul() << std::endl;
    strumien << std::setw(15) << std::fixed << std::setprecision(20) <<  "  Dlugosc drugiego boku: " << (this->obiektZParametrami[numerObiektu].obiekt[zestawyKrawedzi[zestawKrawedzi][2]] - this->obiektZParametrami[numerObiektu].obiekt[zestawyKrawedzi[zestawKrawedzi][3]]).modul() << std::endl;
    strumien << std::setw(15) << std::fixed << std::setprecision(20) <<  " Dlugosc trzeciego boku: " << (this->obiektZParametrami[numerObiektu].obiekt[zestawyKrawedzi[zestawKrawedzi][4]] - this->obiektZParametrami[numerObiektu].obiekt[zestawyKrawedzi[zestawKrawedzi][5]]).modul() << std::endl;
    strumien << std::setw(15) << std::fixed << std::setprecision(20) <<  " Dlugosc czwartego boku: " << (this->obiektZParametrami[numerObiektu].obiekt[zestawyKrawedzi[zestawKrawedzi][6]] - this->obiektZParametrami[numerObiektu].obiekt[zestawyKrawedzi[zestawKrawedzi][7]]).modul() << std::endl;
  }
  return true;
}