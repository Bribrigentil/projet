#include<iostream>
#include<time.h>
#include<ostream>
#include<cmath>
#include"fonctions.h"
#include"oiseaux3.h"

using namespace std;

oiseau::oiseau(double R, double R1, double R2, double vgroupe,  double Taillesurfacex, double Taillesurfacey, vector<cercle> obst) : obstacle() {
  initialisegraine();
  positioninitiale(Taillesurfacex, Taillesurfacey, obst);
  vitesseinitiale(vgroupe);
  comportement(R, R1, R2); 
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


void oiseau::comportement(double R, double R1, double R2) {
  Rayonvision = R;
  Taille = R1;
  Taille2 = R2;
}


void oiseau::taille() {
  obstacle::taille();
}


void oiseau::adaptationvitesse(vector<oiseau> nuee, double vgroupe, double Taillesurfacex, double Taillesurfacey) {
  double vitessegroupex = 0;
  double vitessegroupey = 0;
  double positiongroupex1 = 0, positiongroupex2 = 0;
  double positiongroupey1 = 0, positiongroupey2 = 0;
  double normpositiongroupe1, normpositiongroupe2;
  int k1 = 0, k2 = 0;
  double dx, dy;
  double dmin = 3000, dxmin = 0, dymin = 0, Fuite = 0;

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
      vitessegroupex += nuee[i].vx;
      vitessegroupey += nuee[i].vy;
      positiongroupex1 += nuee[i].x;
      positiongroupey1 += nuee[i].y;
    }

    else if ((norm(dx, dy) != 0) && (norm(dx, dy) <= Taille)) {
      k2 += 1;
      vitessegroupex += nuee[i].vx;
      vitessegroupey += nuee[i].vy;
      positiongroupex2 += nuee[i].x;
      positiongroupey2 += nuee[i].y;
    }

    if ((norm(dx, dy) < dmin) && (norm(dx, dy) > 0)) {
      dmin = norm(dx, dy);
      dxmin = dx;
      dymin = dy;
    }
  }

  
  if (k1 > 0) {
         
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

    normpositiongroupe1 = norm(x-positiongroupex1, y-positiongroupey1);
  }

  else {
    positiongroupex1 = x;
    positiongroupey1 = y;

    normpositiongroupe1 = 1;
  }


  if (k2 > 0) {
       
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

    normpositiongroupe2 = norm(x-positiongroupex2, y-positiongroupey2);
  }

  else {
    positiongroupex2 = x;
    positiongroupey2 = y;

    normpositiongroupe2 = 1;
  }


  if (k1+k2 > 0) {
    vitessegroupex = vitessegroupex/(k1+k2);
    vitessegroupey = vitessegroupey/(k1+k2);
  }

  else {
    vitessegroupex = vx;
    vitessegroupey = vy;
  }

  if (dmin < Taille2) {
    Fuite = 0.02;
  }

  double normvitesse = norm(vx, vy);
  double normvitessegroupe = norm(vitessegroupex, vitessegroupey);
  vx = vgroupe * (0.998*vx/normvitesse + 0.002*vitessegroupex/normvitessegroupe + 0.001*(positiongroupex1-x)/normpositiongroupe1 - 0.01*(positiongroupex2-x)/normpositiongroupe2 - Fuite*dxmin/dmin);
  vy = vgroupe * (0.998*vy/normvitesse + 0.002*vitessegroupey/normvitessegroupe + 0.001*(positiongroupey1-y)/normpositiongroupe1 - 0.01*(positiongroupey2-y)/normpositiongroupe2 - Fuite*dymin/dmin);
}



  
ostream& operator<< (ostream& out, const oiseau& O) {
  out << O.x << "   " << O.y << "   " << O.vx << "   " << O.vy;
  return out;
}
