#include<iostream>
#include"fonctions.h"
#include"cercle.h"

using namespace std;

//Constructeur d'un obstacle circulaire
cercle::cercle(double xo, double yo, double Ro) : obstacle() {
  positioninitiale(xo, yo);
  defRayon(Ro);
}

//Destrcuteur d'un obstacle circulaire
cercle::~cercle() {
}

//Défintion de la position de l'obstacle
void cercle::positioninitiale(double xo, double yo) {
  x = xo;
  y = yo;
}

//Définition de la taille de l'obstacle
void cercle::defRayon(double Ro) {
  Rayon = Ro;
}

//Fonction qui force les oiseaux à contourner les obstacles
void cercle::contournement(vector<oiseau>* nuee, double vgroupe) {
  for (unsigned int i = 0; i < (*nuee).size(); i++) {
    //Si l'oiseau s'approche suffisamment proch de l'obstacle:
    if((norm((*nuee)[i].x-x, (*nuee)[i].y-y) > Rayon) && (norm((*nuee)[i].x-x, (*nuee)[i].y-y) < Rayon+3*(*nuee)[i].Taille)) {

      //alors l'oiseau fuit l'obstacle
      double d = norm((*nuee)[i].x-x, (*nuee)[i].y-y);
      (*nuee)[i].vx = (*nuee)[i].vx + 0.005*vgroupe*((*nuee)[i].x-x)/(d-Rayon);
      (*nuee)[i].vy = (*nuee)[i].vy + 0.005*vgroupe*((*nuee)[i].y-y)/(d-Rayon);
    }
  }
}

