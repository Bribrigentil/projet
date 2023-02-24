#include<iostream>
#include<math.h>
#include"fonctions.h"

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
  return exp(-(x*x)/(2*variance));
}