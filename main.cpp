#include<iostream>
#include "oiseaux.h"
#include <time.h>
#include <vector>

using namespace std;

void oiseau::initialiser(double X, double Y, double VX, double VY)
{
  x = X;
  y = Y;
  vx = VX;
  vy = VY;
}

void oiseau::afficher()
{
  cout << x << "   " << y << "   " << vx << "   " << vy << endl;
}
