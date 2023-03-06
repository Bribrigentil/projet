#include<iostream>
#include"fonctions.h"
#include"cercle.h"

using namespace std;

cercle::cercle(double xo, double yo, double Ro) : obstacle() {
  positioninitiale(xo, yo);
  defRayon(Ro);
}

cercle::~cercle() {
}

void cercle::positioninitiale(double xo, double yo) {
  x = xo;
  y = yo;
}

void cercle::defRayon(double Ro) {
  Rayon = Ro;
}

void cercle::contournement(vector<oiseau>* nuee, double vgroupe) {
  for (unsigned int i = 0; i < (*nuee).size(); i++) {
    if((norm((*nuee)[i].x-x, (*nuee)[i].y-y) > Rayon) && (norm((*nuee)[i].x-x, (*nuee)[i].y-y) < Rayon+(*nuee)[i].Taille)) {
      double d = norm((*nuee)[i].x-x, (*nuee)[i].y-y);
      (*nuee)[i].vx = (*nuee)[i].vx + 0.02*vgroupe*((*nuee)[i].x-x)/(d-Rayon);
      (*nuee)[i].vy = (*nuee)[i].vy + 0.02*vgroupe*((*nuee)[i].y-y)/(d-Rayon);
    }
  }
}

