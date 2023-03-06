#include<iostream>
#include"oiseaux.h"
#include<time.h>
#include"fonctions.h"
#include<ostream>
#include<cmath>
#include"cercle.h"

using namespace std;


oiseau::oiseau(double R, double R1, double vgroupe,  double Taillesurfacex, double Taillesurfacey, vector<cercle> obst) : obstacle() {
  initialisegraine();
  positioninitiale(Taillesurfacex, Taillesurfacey, obst);
  vitesseinitiale(vgroupe);
  comportement(R, R1); 
}


oiseau::~oiseau() {
}


void oiseau::initialisegraine() {
  graine = time(NULL);
  srand(graine);
}


void oiseau::positioninitiale(double Taillesurfacex, double Taillesurfacey, vector<cercle> obst) {
  if (obst.size() == 0) {
    x = Taillesurfacex * double(drand48());
    y = Taillesurfacey * double(drand48());
  }
  else {
    unsigned int k = 0;
    while(k < obst.size()) {
      k = 0;
      x = Taillesurfacex * double(drand48());
      y = Taillesurfacey * double(drand48());
      for (unsigned int i=0; i < obst.size(); i++) {
	if (norm(x-obst[i].x, y-obst[i].y) > obst[i].Rayon + Taille)
	  k += 1;
      }
    }
  }
}


void oiseau::vitesseinitiale(double vgroupe) {
  double variancevitesse = vgroupe/10, normvitesse;
  vx = rejetgaussien(vgroupe, variancevitesse);
  vy = rejetgaussien(vgroupe, variancevitesse);
  normvitesse = norm(vx, vy);
  vx = vgroupe * vx/normvitesse;
  vy = vgroupe * vy/normvitesse;
}


void oiseau::comportement(double R, double R1) {
  Rayonvision = R;
  Taille = R1;
}


void oiseau::taille() {
  obstacle::taille();
}


void oiseau::adaptationvitesse(vector<oiseau> nuee, double vgroupe, double Taillesurfacex, double Taillesurfacey) {
  double vitessegroupex1 = 0, vitessegroupex2 = 0;
  double vitessegroupey1 = 0, vitessegroupey2 = 0;
  double positiongroupex1 = 0, positiongroupex2 = 0;
  double positiongroupey1 = 0, positiongroupey2 = 0;
  int k1 = 0, k2 = 0;
  double dx, dy;

  for (unsigned int i = 0; i < nuee.size(); i++) {
    if (abs(nuee[i].x+Taillesurfacex-x) < abs(nuee[i].x-Taillesurfacex-x)) {
      if (abs(nuee[i].x-x) < abs(nuee[i].x+Taillesurfacex-x))
	dx = nuee[i].x - x;
      else
	dx = nuee[i].x+Taillesurfacex-x;
    }

    else {
      if (abs(nuee[i].x-x) < abs(nuee[i].x-Taillesurfacex-x))
	dx = nuee[i].x - x;
      else
	dx = nuee[i].x-Taillesurfacex-x;
    }

    if (abs(nuee[i].y+Taillesurfacey-y) < abs(nuee[i].y-Taillesurfacey-y)) {
      if (abs(nuee[i].y-y) < abs(nuee[i].y+Taillesurfacey-y))
	dy = nuee[i].y - y;
      else
	dy = nuee[i].y-Taillesurfacey-y;
    }
    else {
      if (abs(nuee[i].y-y) < abs(nuee[i].y-Taillesurfacey-y))
	dy = nuee[i].y - y;
      else
	dy = nuee[i].y-Taillesurfacey-y;
    }
      
    if ((norm(dx, dy) != 0) && (norm(dx, dy) <= Rayonvision) && (norm(dx, dy) > Taille)) {
      k1 += 1;
      vitessegroupex1 += nuee[i].vx;
      vitessegroupey1 += nuee[i].vy;
      positiongroupex1 += nuee[i].x;
      positiongroupey1 += nuee[i].y;
    }

     if ((norm(dx, dy) != 0) && (norm(dx, dy) <= Taille)) {
      k2 += 1;
      vitessegroupex2 += nuee[i].vx;
      vitessegroupey2 += nuee[i].vy;
      positiongroupex2 += nuee[i].x;
      positiongroupey2 += nuee[i].y;
    }    
  }


  if (k1 > 0) {

    vitessegroupex1 = vitessegroupex1/k1;
    vitessegroupey1 = vitessegroupey1/k1;      
    positiongroupex1 = positiongroupex1/k1;
    positiongroupey1 = positiongroupey1/k1;

    if (positiongroupex1 - x < -Taillesurfacex/2)
      positiongroupex1 += Taillesurfacex;
    else if (positiongroupex1 - x > Taillesurfacex/2)
      positiongroupex1 -= Taillesurfacex;
    if (positiongroupey1 - y < -Taillesurfacey/2)
      positiongroupey1 += Taillesurfacey;
    else if (positiongroupey1 - y > Taillesurfacey/2)
      positiongroupey1 -= Taillesurfacey;
    

    double normvitesse = norm(vx, vy);
    double normvitessegroupe = norm(vitessegroupex1, vitessegroupey1);
    double normposition = norm(x-positiongroupex1, y-positiongroupey1);
    vx = vgroupe*(0.998*vx/normvitesse + 0.002*vitessegroupex1/normvitessegroupe + 0.005*(positiongroupex1-x)/normposition);
    vy = vgroupe*(0.998*vy/normvitesse + 0.002*vitessegroupey1/normvitessegroupe + 0.005*(positiongroupey1-y)/normposition);
  }


  if (k2 > 0) {
    
    vitessegroupex2 = vitessegroupex2/k2;
    vitessegroupey2 = vitessegroupey2/k2;      
    positiongroupex2 = positiongroupex2/k2;
    positiongroupey2 = positiongroupey2/k2;
      
    if (positiongroupex2 - x < -Taillesurfacex/2)
      positiongroupex2 += Taillesurfacex;
    else if (positiongroupex2 - x > Taillesurfacex/2)
      positiongroupex2 -= Taillesurfacex;
    if (positiongroupey2 - y < -Taillesurfacey/2)
      positiongroupey2 += Taillesurfacey;
    else if (positiongroupey2 - y > Taillesurfacey/2)
      positiongroupey2 -= Taillesurfacey;
    
    double normvitesse = norm(vx, vy);
    double normvitessegroupe = norm(vitessegroupex2, vitessegroupey2);
    double normposition = norm(x-positiongroupex2, y-positiongroupey2);
    vx = 0.999*vx/normvitesse + 0.001*vitessegroupex2/normvitessegroupe - 0.02*(positiongroupex2-x)/normposition;
    vy = 0.999*vy/normvitesse + 0.001*vitessegroupey2/normvitessegroupe - 0.02*(positiongroupey2-y)/normposition;

    normvitesse = norm(vx, vy);
    vx = vgroupe * (vx/normvitesse);
    vy = vgroupe * (vy/normvitesse);
  }
}


ostream& operator<< (ostream& out, const oiseau& O) {
  out << O.x << "   " << O.y << "   " << O.vx << "   " << O.vy;
  return out;
}

