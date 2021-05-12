#include <iostream>
#include <limits>

#include "Scena.hh"
#include "KatyRPY.hh"
#include "Wektoryzacja.hh"

// Wyświtla opcje obsługiwane przez menu
void wyswietlMenu()
{
  std::cout << std::endl;
  std::cout << "o - obrót bryły o zadaną sekwencję kątów" << std::endl;
  std::cout << "t - powtórzenie poprzedniego obrotu" << std::endl;
  std::cout << "r - wyświetlenie macierzy rotacji" << std::endl;
  std::cout << "p - przesunięcie bryły o zadany wektor" << std::endl;
  std::cout << "w - wyświetlenie współrzędnych wierzchołków" << std::endl;
  std::cout << "s - sprawdzenie długości przeciwległych bokow" << std::endl;
  std::cout << "m - wyświetl menu" << std::endl;
  std::cout << "k - koniec działania programu" << std::endl;
  std::cout << std::endl;
}

void pobiezNumerObiektu(Scena &scena, unsigned int &numerObiektu)
{
  if(scena.zwrocIloscObiektow() == 1)                                // Jeśli w scenie znajduje się tylko jeden obiekt, automatycznie jest wybierany
  {
    numerObiektu = 1;
    return;
  }
  bool powtorz = false;
  do
  {
    std::cout << "Podaj numer obiektu, na którym chesz wykonać operację [1, " << scena.zwrocIloscObiektow() << "]: ";
    std::cin >> numerObiektu;
    if(std::cin.fail() || (numerObiektu > scena.zwrocIloscObiektow()) || (numerObiektu == 0))
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
      std::cout << "Podano nieprawidłowy numer obiektu!" << std::endl;
      powtorz = true;
    }else{
      --numerObiektu;                                                    // Zmiana na numerację zaczynającą się od 0 zamiast od 1
      powtorz = false;
    }
  } while (powtorz);
}

int main()
{
  Scena scena;
  Wektor3D wektor;
  MacierzObrotu tempMacierzObrotu;
  MacierzObrotu generatorMacierzyObrotu;
  double inicjatorMacierzyJednostkowej[] = {1,0,0,0,1,0,0,0,1};
  char wczytanyZnak;
  char oznaczenieOsi;
  double kat = 0;
  int iloscPowtorzen = 0;
  unsigned int numerObiektu = 1;
  bool wprowadzPonownie;
  if(numerObiektu == 10)
    return 0;

  if(scena.wczytajObiekt("../datasets/obiekt1.dat") == false)
    std::cout << "Nie udało się wczytać" << std::endl;

  if(scena.wczytajObiekt("../datasets/obiekt2.dat") == false)
    std::cout << "Nie udało się wczytać" << std::endl;

  if(scena.wczytajObiekt("../datasets/obiekt3.dat") == false)
    std::cout << "Nie udało się wczytać" << std::endl;

  if(scena.wczytajObiekt("../datasets/obiekt4.dat") == false)
    std::cout << "Nie udało się wczytać" << std::endl;

  if(scena.wczytajObiekt("../datasets/obiekt5.dat") == false)
    std::cout << "Nie udało się wczytać" << std::endl;

  if(scena.wczytajObiekt("../datasets/obiekt6.dat") == false)
    std::cout << "Nie udało się wczytać" << std::endl;

  /*
  Macierz4X4 macierz4x4;
  double dane[] = {1, 2, 3};
  Wektor3D wektorTest(dane);
  Wypelnij(macierz4x4, 0, 0, 0, wektorTest);
  std::cout << macierz4x4 << std::endl << std::endl;
  */

  // Sprawdzenie długości boków wczytanych obiektów
  std::cout << std::endl;
  for(unsigned int numerBryly = 0; numerBryly < scena.zwrocIloscObiektow(); ++numerBryly)
  {
    std::cout << "Sprawdzanie boków bryły nr. " << numerBryly + 1 << ":" << std::endl << std::endl;
    scena.sprawdzBoki(numerBryly, std::cout);
    std::cout << std::endl;
  } 



  scena.wyswietl();                                                                                // Wyświetlenie wczytanych obiektów w gnuplocie
  wyswietlMenu();                                                                                  // Wyświetlenie menu
  while(true)                                                                                      // Pętla główna programu
  {
    std::cout << "Twoj wybor? (m - menu) > ";                                                      // Pobranie od użytkownika kodu operacji, którą chce wykonać
    std::cin >> wczytanyZnak;
    if(std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
      wczytanyZnak = ' ';      
    }
    switch (wczytanyZnak)                                                                          // Wykonywanie wybranej operacji
    {
      case 'o':                                                                                    //  Obrót bryły o zadaną sekwencję kątów
        tempMacierzObrotu.ustaw(inicjatorMacierzyJednostkowej);
        pobiezNumerObiektu(scena, numerObiektu);
        std::cout << "Podaj sekwencje oznaczen osi oraz katy obrotu w stopniach:" << std::endl;
        while(true)
        {
          wprowadzPonownie = false;
          do {                                                                                     // Wprowadzanie oznaczenia osi obrotu
            std::cin >> oznaczenieOsi;
            if(((oznaczenieOsi != 'x') && (oznaczenieOsi != 'y') && (oznaczenieOsi != 'z') && (oznaczenieOsi != '.')) || std::cin.fail())
            {
              std::cin.clear();
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
              std::cout << ":( Bledne oznaczenie osi. Dopuszczalne znaki to: x y z." << std::endl;
              std::cout << ":( Sprobuj jeszcze raz." << std::endl;
              wprowadzPonownie = true;
            }else{
              wprowadzPonownie = false;
            }
          } while(wprowadzPonownie);
          if(oznaczenieOsi == '.')                                                                 // Kończenie wprowadzania jeśli użytkownik wprowadził '.'
            break;
          do {
            std::cin >> kat;
            if(std::cin.fail())
            {
              std::cin.clear();
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); 
              std::cout << "Błędny format kąta obrotu. Wprowadź wartość kąta ponownie." << std::endl;
              wprowadzPonownie = true;
            }else{
              wprowadzPonownie = false;
            }
          } while(wprowadzPonownie);

          switch (oznaczenieOsi)                                                                   // Generowanie macierzy obrotu
          {
          case 'x':
            generujMacierzObrotu(generatorMacierzyObrotu, kat, OX);
            break;
          case 'y':
            generujMacierzObrotu(generatorMacierzyObrotu, kat, OY);
            break;
          case 'z':
            generujMacierzObrotu(generatorMacierzyObrotu, kat, OZ);
            break;
          }
          tempMacierzObrotu = tempMacierzObrotu * generatorMacierzyObrotu;                         // Składanie macierzy obrotu
        }

        do {
          std::cout << "Ile razy operacja obrotu ma byc powtorzona?" << std::endl;
          std::cin >> iloscPowtorzen;
          if(std::cin.fail() || (iloscPowtorzen < 0))
          {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); 
            std::cout << "Błędny format ilości powtórzeń obrotu. Wprowadź wartość ponownie." << std::endl;
            wprowadzPonownie = true;
          }else{
            wprowadzPonownie = false;
          }
        } while(wprowadzPonownie);

        for(int x = 0; x < iloscPowtorzen; ++x)
        {
          scena.obrocGlobalnie(numerObiektu, tempMacierzObrotu);
          scena.obrocLokalnie(numerObiektu, tempMacierzObrotu);
          scena.ustawMacierzPoprzedniegoObrotu(numerObiektu, tempMacierzObrotu);
        }
        scena.wyswietl();
        scena.sprawdzBoki(numerObiektu, std::cout);
        break;
      case 't':                                                                                    // Powtórzenie poprzedniego obrotu
        pobiezNumerObiektu(scena, numerObiektu);
        // Sprawdzanie czy wybrany obiekt był obracany
        try {
          if(scena.zwrocMacierzPoprzedniegoObrotu(numerObiektu).obliczWyznacznik() == 0)
          {
            std::cout << "Wybrany obiekt nie był jeszcze obracany" << std::endl;
            break;
          }
        }
        catch(int errorCode) {
          std::cout << "Wybrany obiekt nie był jeszcze obracany" << std::endl;
          break;
        }
        scena.obrocGlobalnie(numerObiektu, scena.zwrocMacierzPoprzedniegoObrotu(numerObiektu));
        scena.obrocLokalnie(numerObiektu, scena.zwrocMacierzPoprzedniegoObrotu(numerObiektu));
        scena.wyswietl();
        scena.sprawdzBoki(numerObiektu, std::cout);
        break;
      case 'r':                                                                                    // Wyświetlenie macierzy rotacji wybranej bryły
        pobiezNumerObiektu(scena, numerObiektu);
        std::cout << scena.zwrocMacierzObrotu(numerObiektu) << std::endl;
        break;
      case 'p':                                                                                    // Przesunięcie wybranej bryły o zadany wektor
        pobiezNumerObiektu(scena, numerObiektu);
        do {
          std::cout << "Podaj wektor translacji: ";
          std::cin >> wektor;
          if(std::cin.fail())
          {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Wprowadzono wektor w nieprawidłowym formacie. Prawidłowy format to: x y z" << std::endl;
            wprowadzPonownie = true;
          }else{
            wprowadzPonownie = false;
          }
        } while(wprowadzPonownie);
        scena.przesun(numerObiektu, wektor);
        scena.wyswietl();
        break;
      case 'w':                                                                                    // Wyświetlenie wspólrzędnych wierzchołków wybranej bryły
        pobiezNumerObiektu(scena, numerObiektu);
        scena.wyswietlWspolrzedne(numerObiektu, std::cout);
        break;
      case 's':                                                                                    //  sprawdzenie dlugosci przeciwleglych bokow
        pobiezNumerObiektu(scena, numerObiektu);
        scena.sprawdzBoki(numerObiektu, std::cout);
        break;
      case 'm':                                                                                    // Wyświetl menu
        wyswietlMenu();
        break;
      case 'k':                                                                                    // Koniec działania programu
        std::cout << std::endl << "Koniec dzialania programu" << std::endl << std::endl;
        return 0;
        break;
      default:                                                                                     // Wprowadzono nieprawidłowy kod funkcji
        std::cout << "Wprowadzono nieprawidłowy kod funkcji" << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        break;
    }
  }
}
