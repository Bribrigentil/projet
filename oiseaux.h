#ifndef oiseau_H
#define oiseau_H
class oiseau
{
public:
  double x;  //position selon x
  double y;  // position selon y
  double vx;  //vitesse selon x
  double vy;  //vitesse selon y
  double R;  //champ de vision
  
  void initialiser(double X, double Y, double VX, double VY);
  void afficher();
  void alea(); //initialiser la position des oiseaux aléatoirement et la vitesse avec une distrib gaussienne
};
#endif
