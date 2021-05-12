#include "../include/Prostopadloscian.hh"

bool Prostopadloscian::operator == (const Prostopadloscian &prostopadloscian) const
{
  for(unsigned int x = 0; x < 8; ++x)
    if(this->wierzcholki[x] != prostopadloscian.wierzcholki[x])
      return false;
  return true;
}

bool Prostopadloscian::operator != (const Prostopadloscian &prostopadloscian) const
{
  return !((*this) == prostopadloscian);
}

std::ostream& operator << (std::ostream &strumien, const Prostopadloscian &prostopadloscian)
{
  for(unsigned int x = 0; x < 8; ++x)
    strumien << prostopadloscian[x] << std::endl;
  return strumien;
}