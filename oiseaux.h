#ifndef oiseau_H
#define oiseau_H

#include<ostream>
#include"obstacle.h"
using namespace std;

class oiseau : public obstacle
{
public:
  double Rayonvision;
  double Tempsreaction;
  double anglevue; 
  double memoireangle;  
  double graine; //graine utilisée uniquement pour l'initialisation aléatoire

  oiseau(double R, double T, double A, double M,  double Taillesurface);
  //constructeur qui initialise avec une distribution uniforme la position et avec une distribution  gaussienne la vitesse des oiseaux
  ~oiseau();
  void taille() override;
  void initialisegraine();
  void position(double Taillesurface);
  void vitesse(double Taillesurface);
  void comportement(double R, double T, double A, double M);
  void afficher();

  friend ostream& operator<< (ostream& out, const oiseau& O);
};

#endif
