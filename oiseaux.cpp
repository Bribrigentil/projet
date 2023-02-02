#include<iostream>
#include"oiseaux.h"
#include<time.h>
#include"fonctions.h"
#include<ostream>
#include<cmath>

using namespace std;

oiseau::oiseau(double R, double T, double A, double M, double vgroupe,  double Taillesurfacex, double Taillesurfacey) : obstacle() {
  initialisegraine();
  positioninitiale(Taillesurfacex, Taillesurfacey);
  vitesseinitiale(vgroupe);
  comportement(R, T, A, M); 
}

oiseau::~oiseau() {
}

void oiseau::initialisegraine() {
  graine = time(NULL);
  srand(graine);
}


void oiseau::positioninitiale(double Taillesurfacex, double Taillesurfacey) {
  x = Taillesurfacex * double(drand48());
  y = Taillesurfacey * double(drand48());
}

void oiseau::vitesseinitiale(double vgroupe) {
  double variancevitesse = vgroupe/10, normvitesse;
  vx = rejetgaussien(vgroupe, variancevitesse);
  vy = rejetgaussien(vgroupe, variancevitesse);
  normvitesse = sqrt(vx*vx+vy*vy);
  vx = vgroupe * vx/normvitesse;
  vy = vgroupe * vy/normvitesse;
}

void oiseau::comportement(double R, double T, double A, double M) {
  Rayonvision = R;
  Tempsreaction = T;
  anglevue = A;
  memoireangle = M;
}

void oiseau::taille() {
  obstacle::taille();
}


void oiseau::adaptationvitesse(vector<oiseau> nuee, double dt, double vgroupe, double Taillesurfacex, double Taillesurfacey) {
  double vitessegroupex = 0;
  double vitessegroupey = 0;
  double positiongroupex = 0;
  double positiongroupey = 0;
  for (int i = 0; i < nuee.size(); i++) {
    if ((nuee[i].x*nuee[i].x+nuee[i].y*nuee[i].y)-(x*x+y*y) != 0) {
      vitessegroupex += nuee[i].vx;
      vitessegroupey += nuee[i].vy;
      positiongroupex += nuee[i].x;
      positiongroupey += nuee[i].y;
    }
  }
  
  vitessegroupex = vitessegroupex/(nuee.size()-1);
  vitessegroupey = vitessegroupey/(nuee.size()-1);
  positiongroupex = positiongroupex/(nuee.size()-1);
  positiongroupey = positiongroupey/(nuee.size()-1);
  
  if (positiongroupex - x < -Taillesurfacex/2)
    positiongroupex += Taillesurfacex;
  else if (positiongroupex - x > Taillesurfacex/2)
    positiongroupex -= Taillesurfacex;
  if (positiongroupey - y < -Taillesurfacey/2)
    positiongroupey += Taillesurfacey;
  else if (positiongroupey - y > Taillesurfacey/2)
    positiongroupey -= Taillesurfacey;

  double normvitesse = sqrt(vx*vx+vy*vy);
  double normvitessegroupe = sqrt(vitessegroupex*vitessegroupex+vitessegroupey*vitessegroupey);
  double normposition = sqrt((x-positiongroupex)*(x-positiongroupex) + (y-positiongroupey)*(y-positiongroupey));
  vx = vgroupe*(0.999*vx/normvitesse + 0.001*vitessegroupex/normvitessegroupe + 0.003*(positiongroupex-x)/normposition);
  vy = vgroupe*(0.999*vy/normvitesse + 0.001*vitessegroupey/normvitessegroupe  + 0.003*(positiongroupey-y)/normposition);
}
  
ostream& operator<< (ostream& out, const oiseau& O) {
  out << O.x << "   " << O.y << "   " << O.vx << "   " << O.vy;
  return out;
}
