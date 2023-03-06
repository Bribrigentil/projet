#ifndef oiseau_H
#define oiseau_H

#include<ostream>
#include<vector>
#include"obstacle.h"
#include"cercle.h"

using namespace std;

class cercle;
class oiseau : public obstacle {
public:
  double Rayonvision;
  double Taille;
  double Taille2;
  double graine; //graine utilisée uniquement pour l'initialisation aléatoire

  oiseau(double R, double R1, double R2,  double vgroupe,  double Taillesurfacex, double Taillesurfacey, vector<cercle> obst);
  //constructeur qui initialise avec une distribution uniforme la position et avec une distribution gaussienne la vitesse des oiseaux
  ~oiseau();
  
  void taille() override;
  void initialisegraine();
  //  void positioninitiale(double Taillesurfacex, double Taillesurfacey);
  void positioninitiale(double Taillesurfacex, double Taillesurfacey, vector<cercle> obst);
  void vitesseinitiale(double vgroupe);
  void comportement(double R, double R1, double R2);
  void adaptationvitesse(vector<oiseau> nuee, double vgroupe, double Taillesurfacex, double Taillesurfacey);
  friend ostream& operator<< (ostream& out, const oiseau& O);
};

#endif
