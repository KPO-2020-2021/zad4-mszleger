#ifndef WEKTORYZACJA_HH
#define WEKTORYZACJA_HH


/**
 * \brief Funkcja wymnażająca wszystkie elementy tablicy czynnik_2_tab razy czynnik_1.
 */
template <class typ_wartosci_1, class typ_wartosci_2,  unsigned int rozmiar>
void Wymnoz(typ_wartosci_1 czynnik_1, typ_wartosci_2 (&czynnik_2_tab)[rozmiar])
{
  for (typ_wartosci_2 &czynnik_2 : czynnik_2_tab) czynnik_2 = czynnik_1 * czynnik_2;
}

/**
 * \brief Funkcja dodająca do wszystkich elementów tablicy czynnik_2_tab wartość czynnik_1.
 */
template <class typ_wartosci_1, class typ_wartosci_2, unsigned int rozmiar>
void Dodaj(typ_wartosci_1 skladnik_1, typ_wartosci_2 (&skladnik_2_tab)[rozmiar])
{
  for (typ_wartosci_2 &skladnik_2 : skladnik_2_tab) skladnik_2 = skladnik_1 + skladnik_2;
}

#endif