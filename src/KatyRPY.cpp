#include "KatyRPY.hh"

void Wypelnij(Macierz4X4 &macierz, double alpha, double beta, double gamma, const Wektor3D &translacja)
{
  alpha = alpha * M_PI / 180;
  beta  = beta  * M_PI / 180;
  gamma = gamma * M_PI / 180;
  double parametry[] = {cos(alpha)*cos(beta), cos(alpha)*sin(beta)*sin(gamma)-sin(alpha)*cos(gamma), cos(alpha)*sin(beta)*cos(gamma)+sin(alpha)*sin(gamma), translacja[0],
                        sin(alpha)*cos(beta), sin(alpha)*sin(beta)*sin(gamma)+cos(alpha)*cos(gamma), sin(alpha)*sin(beta)*cos(gamma)-cos(alpha)*sin(gamma), translacja[1],
                        -sin(beta),           cos(beta)*sin(gamma),                                  cos(beta)*cos(gamma),                                  translacja[2],
                        0,                    0,                                                     0,                                                     1};
  macierz.ustaw(parametry);
}