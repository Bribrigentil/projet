#include<iostream>
#include<math.h>
#include"fonctions.h"
#include"oiseaux.h"
using namespace std;

double rejetgaussien(double moyenne, double variance) { // Fournit valeur alea. de densite gaussienne
  double x, y, ecarttype = sqrt(variance); // avec variance var et moyenne 0.
  do { // On prend x dans l'intervalle [-5sigma,5sigma], on suppose que la
    x = 10.*ecarttype * (rand()%1000)/1001. - 5.*ecarttype; // gaussienne est nulle ailleurs.
    y = (rand()%1000)/1001.;
  } while(y > exp(-x*x/(2.*variance)));

  return x;
}

double gaussienne(double x,double variance){
  return sqrt(2*variance/M_PI)*exp(-(x*x)/(2*variance));
}
double lorentzienne(double x,double variance){
  return 1/(1+x*x/variance);
}

double distance(double x, double y){
  return sqrt((x*x+y*y));
}
class oiseau;
bool visible(double x,double y,double vx,double vy,oiseau O2,double rayon,double anglevue){
  double normV=distance(vx,vy);
  double ecart=distance(x-O2.x,y-O2.y);
  double vision=vx*(O2.x-x)+vy*(O2.y-y); vision/=normV*ecart;
  return ((cos(anglevue)-vision<=0)&&(ecart-rayon<=0));
}