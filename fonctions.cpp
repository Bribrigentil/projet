#include<iostream>
#include<math.h>
#include"fonctions.h"

using namespace std;

double rejetgaussien(double moyenne, double variance) { // Fournit valeur alea. de densite gaussienne
  double x, y, ecarttype = sqrt(variance); // avec variance var et moyenne 0.
  do { // On prend x dans l'intervalle [-5sigma,5sigma], on suppose que la
    x = 10.*ecarttype * drand48() - 5.*ecarttype; // gaussienne est nulle ailleurs.
    y = drand48();
  } while(y > exp(-(x-moyenne)*(x-moyenne)/(2.*variance)));
  return x;
}

double gaussienne(double x, double moyenne, double variance){
  return sqrt(2*variance/M_PI)*exp(-((x-moyenne)*(x-moyenne))/(2*variance));
}

double norm(double x, double y) {
  double n = sqrt(x*x+y*y);
  return n;
}

class oiseau;
bool visible(double x,double y,double vx,double vy,oiseau O2,double anglevue) {
  double normV=norm(vx,vy);
  double ecart=norm(x-O2.x,y-O2.y);
  double vision=vx*(O2.x-x)+vy*(O2.y-y); vision/=normV*ecart;
  return (cos(anglevue)-vision<=0);
}
