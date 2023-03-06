#include<iostream>
#include<time.h>
#include<ostream>
#include<cmath>
#include"oiseaux.h"
#include"fonctions.h"
#include"cercle.h"

using namespace std;

/*oiseau::oiseau(double R, double R1, double vgroupe,  double Taillesurfacex, double Taillesurfacey) : obstacle() {
  initialisegraine();
  positioninitiale(Taillesurfacex, Taillesurfacey);
  vitesseinitiale(vgroupe);
  comportement(R, R1); 
  }*/


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


/*void oiseau::positioninitiale(double Taillesurfacex, double Taillesurfacey) {
    x = Taillesurfacex * double(drand48());
    y = Taillesurfacey * double(drand48());
    }*/


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
  double vitessegroupex = 0;
  double vitessegroupey = 0;
  double positiongroupex = 0;
  double positiongroupey = 0;
  int k1 = 0;
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
      
    if ((norm(dx, dy) != 0) && (norm(dx, dy) <= Rayonvision)) {
      k1 += 1;
      vitessegroupex += nuee[i].vx;
      vitessegroupey += nuee[i].vy;
      positiongroupex += nuee[i].x;
      positiongroupey += nuee[i].y;
    }
  }

  
  if (k1 > 0) {
    
    vitessegroupex = vitessegroupex/k1;
    vitessegroupey = vitessegroupey/k1;      
    positiongroupex = positiongroupex/k1;
    positiongroupey = positiongroupey/k1;

    if (positiongroupex - x < -Taillesurfacex/2)
      positiongroupex += Taillesurfacex;
    else if (positiongroupex - x > Taillesurfacex/2)
      positiongroupex -= Taillesurfacex;
    if (positiongroupey - y < -Taillesurfacey/2)
      positiongroupey += Taillesurfacey;
    else if (positiongroupey - y > Taillesurfacey/2)
      positiongroupey -= Taillesurfacey;
    

    double normvitesse = norm(vx, vy);
    double normvitessegroupe = norm(vitessegroupex, vitessegroupey);
    double normposition = norm(x-positiongroupex, y-positiongroupey);
    vx = vgroupe*(0.998*vx/normvitesse + 0.002*vitessegroupex/normvitessegroupe + 0.005*(positiongroupex-x)/normposition);
    vy = vgroupe*(0.998*vy/normvitesse + 0.002*vitessegroupey/normvitessegroupe + 0.005*(positiongroupey-y)/normposition);

  }

  double dmin = 3000, dxmin = 0, dymin = 0;

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

    if ((norm(dx, dy) < dmin) && (norm(dx, dy) > 0)) {
      dmin = norm(dx, dy);
      dxmin = dx;
      dymin = dy;
    }
  }

  if (dmin < Taille) {
    double normvitesse = norm(vx, vy);
    vx = vgroupe*(vx/normvitesse - 0.015*dxmin/dmin);
    vy = vgroupe*(vy/normvitesse - 0.015*dymin/dmin);
  }   
}



  
ostream& operator<< (ostream& out, const oiseau& O) {
  out << O.x << "   " << O.y << "   " << O.vx << "   " << O.vy;
  return out;
}
