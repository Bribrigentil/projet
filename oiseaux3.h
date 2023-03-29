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
  double Rayonvision;  //L'oiseau veut se rapprocher de ses copains.
  double Taille;  //rayon dans lequel les oiseaux fuient le barycentre des oiseaux proches
  double Taille2;  //rayon dans lequel l'oiseau fuit son plus proche voisin
  double anglevue;  //L'oiseau ne voit pas ceux qui sont situés derrière lui

  //constructeur qui initialise avec une distribution uniforme la position et avec une distribution gaussienne la vitesse des oiseaux  
  oiseau(double R, double R1, double R2, double A, double vgroupe,  double Taillesurfacex, double Taillesurfacey, vector<cercle> obst);
  ~oiseau();
 
  void comportement(double R, double R1, double R2, double A);
  void positioninitiale(double Taillesurfacex, double Taillesurfacey, vector<cercle> obst);
  void vitesseinitiale(double vgroupe);
  vector<double> adaptationvitesse(vector<oiseau> nuee, double vgroupe, double Taillesurfacex, double Taillesurfacey);
  friend ostream& operator<< (ostream& out, const oiseau& O);
};

#endif
