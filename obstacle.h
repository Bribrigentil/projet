#ifndef obstacle_H
#define obstacle_H

class obstacle
{
public:
  double x;  //position selon x
  double y;  // position selon y
  double vx;  //vitesse selon x
  double vy;  //vitesse selon y
  double vmax; //la norme de la vitesse ne pourra jamais excéder vmax
  double barycentrex;
  double barycentrey;
  obstacle();
  virtual ~obstacle();
  virtual void taille();
};

#endif
