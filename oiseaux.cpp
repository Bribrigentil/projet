#include<iostream>
#include"oiseaux.h"
#include<time.h>
#include"fonctions.h"
#include<ostream>

using namespace std;

oiseau::oiseau(double R, double T, double A, double M, double Taillesurface) : obstacle() {
  initialisegraine();
  position(Taillesurface);
  vitesse(Taillesurface);
  comportement(R, T, A, M); 
}

oiseau::~oiseau() {
}

void oiseau::initialisegraine() {
  graine = time(NULL);
  srand(graine);
}


void oiseau::position(double Taillesurface) {
  x = Taillesurface * double(drand48());
  y = Taillesurface * double(drand48());
}

void oiseau::vitesse(double Taillesurface) {
  double moyennevitesse = Taillesurface/100;
  double variancevitesse = moyennevitesse/10;
  vx = rejetgaussien(moyennevitesse, variancevitesse);
  vy = rejetgaussien(moyennevitesse, variancevitesse);
}

void oiseau::comportement(double R, double T, double A, double M) {
  Rayonvision = R;
  Tempsreaction = T;
  anglevue = A;
  memoireangle = M;
}

void oiseau::taille() {
  obstacle::taille();
}

  
ostream& operator<< (ostream& out, const oiseau& O) {
  out << O.x << "   " << O.y << "   " << O.vx << "   " << O.vy;
  return out;
}
