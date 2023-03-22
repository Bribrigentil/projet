#ifndef _FONCTIONS_H
#define _FONCTONS_H
#include"oiseaux.h"
double rejetgaussien(double moyenne, double variance);
double gaussienne(double x,double variance);
double lorentzienne(double x,double variance);
double distance(double x, double y);
bool visible(double x,double y,double vx,double vy,oiseau O2,double rayon,double anglevue);
#endif
