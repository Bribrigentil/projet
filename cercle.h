#ifndef cercle_H
#define cercle_H

#include<iostream>
#include<ostream>
#include<vector>
#include"obstacle.h"
#include"oiseaux.h"
using namespace std;

class oiseau;
class cercle : public obstacle {
public:
  double Rayon;
  
  cercle(double xo, double yo, double Ro);
  ~cercle();
  void positioninitiale(double xo, double yo);
  void defRayon(double Ro);
  void contournement(vector<oiseau>* nuee, double vgroupe);

};
#endif
