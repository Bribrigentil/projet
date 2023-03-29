#include<iostream>
#include<time.h>
#include<ostream>
#include<cmath>
#include"fonctions.h"
#include"oiseaux3.h"

using namespace std;

//Constructeur de la classe oiseau
oiseau::oiseau(double R, double R1, double R2, double A, double vgroupe,  double Taillesurfacex, double Taillesurfacey, vector<cercle> obst) : obstacle() {
  positioninitiale(Taillesurfacex, Taillesurfacey, obst);
  vitesseinitiale(vgroupe);
  comportement(R, R1, R2, A); 
}


//Destructeur de la classe oiseau
oiseau::~oiseau() {
}


//On initialise les positions initiales des oiseaux
void oiseau::positioninitiale(double Taillesurfacex, double Taillesurfacey, vector<cercle> obst) {
  if (obst.size() == 0) {
    //Distribution uniforme de la position des oiseaux si il n'y a pas d'obstacle
    x = Taillesurfacex * double(drand48());
    y = Taillesurfacey * double(drand48());
  }
  else {
    unsigned int k = 0;
    //Si il y a des obstacles, on recommence le tirage uniforme jusqu'à ce que l'oiseau se génère hors d'un obstacle
    while(k < obst.size()) {
      k = 0;
      x = Taillesurfacex * double(drand48());
      y = Taillesurfacey * double(drand48());
      for (unsigned int i=0; i < obst.size(); i++) {
	//On compte le nombre d'obstacles auxquels l'oiseau ne fait pas partie pour compléter la condition d'arrêt de la boucle while
	if (norm(x-obst[i].x, y-obst[i].y) > obst[i].Rayon + Taille)
	  k += 1;
      }
    }
  }
}


//On initialise les vitesses initiales des oiseaux
void oiseau::vitesseinitiale(double vgroupe) {
  double variancevitesse = vgroupe/10, normvitesse;

  //La distribution initiale des vitesses et gaussiennes pour choisir la direction de l'oiseau aléatoirement
  vx = rejetgaussien(0, variancevitesse);
  vy = rejetgaussien(0, variancevitesse);
  normvitesse = norm(vx, vy);

  //On normalise la vitesse initiale à la vitesse du groupe
  vx = vgroupe * vx/normvitesse;
  vy = vgroupe * vy/normvitesse;
}


//On définit les propriétés des oiseaux
void oiseau::comportement(double R, double R1, double R2, double A) {
  Rayonvision = R;
  Taille = R1;
  Taille2 = R2;
  anglevue = A;
}

//Fonction centrale du programme qui met à jour la vitesse des oiseaux à chaque instant, on y définit leurs intéractions
vector<double> oiseau::adaptationvitesse(vector<oiseau> nuee, double vgroupe, double Taillesurfacex, double Taillesurfacey) {
  double vitessegroupex = 0;
  double vitessegroupey = 0;
  double positiongroupex1 = 0, positiongroupex2 = 0;
  double positiongroupey1 = 0, positiongroupey2 = 0;
  double normpositiongroupe1, normpositiongroupe2;
  int k1 = 0, k2 = 0;
  double dx, dy;
  double dmin = 3000, dxmin = 0, dymin = 0, Fuite = 0;


  //On définit quel est le chemin le plus court entre deux oiseaux (si il faut traverser un bord de l'interface SFML par exemple) pour avoir des conditions aux bords périodiques
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
	dy = nuee[i].y+Taillesurfacey-y;
    }
    else {
      if (abs(nuee[i].y-y) < abs(nuee[i].y-Taillesurfacey-y))
	dy = nuee[i].y - y;
      else
	dy = nuee[i].y-Taillesurfacey-y;
    }


    //On décompte les oiseaux "pas trop proches" dont il voudra se rapprocher : cohésion du groupe
    if ((norm(dx, dy) != 0) && (norm(dx, dy) <= Rayonvision) && (norm(dx, dy) > Taille) && (visible(x, y, vx, vy, nuee[i], anglevue))) {
      k1 += 1;
      vitessegroupex += nuee[i].vx;
      vitessegroupey += nuee[i].vy;
      positiongroupex1 += x+dx;
      positiongroupey1 += y+dy;
    }

    //On décompte les oiseaux les plus proches dont il voudra s'éloigner :  pas de collision
    else if ((norm(dx, dy) != 0) && (norm(dx, dy) <= Taille)  && (visible(x, y, vx, vy, nuee[i], anglevue))) {
      k2 += 1;
      vitessegroupex += nuee[i].vx;
      vitessegroupey += nuee[i].vy;
      positiongroupex2 += x+dx;
      positiongroupey2 += y+dy;
    }

    //On identifie le plus proche voisin de notre oiseau
    if ((norm(dx, dy) < dmin) && (norm(dx, dy) > 0) && (visible(x, y, vx, vy, nuee[i], anglevue))) {
      dmin = norm(dx, dy);
      dxmin = dx;
      dymin = dy;
    }
  }


  //On calcule la position du barycentre des oiseaux "pas trop proches", c'est vers ce barycentre qu'il se dirige
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
  
  //Si l'oiseau ne voit aucun voisin "pas trop proche", le barycentre en question sera lui-même. Ce terme n'aura aucune influence sur sa vitesse
  else {
    positiongroupex1 = x;
    positiongroupey1 = y;

    normpositiongroupe1 = 1;
  }

  //On calcule la position du barycentre des oiseaux les plus proches, c'est ce barycentre qu'il fuit
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

  //Si l'oiseau ne voit aucun voisin très proche, le barycentre en question sera lui-même. Ce terme n'aura aucune influence sur sa vitesse
  else {
    positiongroupex2 = x;
    positiongroupey2 = y;

    normpositiongroupe2 = 1;
  }

  //Tous les voisins que l'oiseau peut voir, "pas trop proche" ou très proche sont pris en compte ici. L'oiseau veut aligner sa vitesse avec la leur
  if (k1+k2 > 0) {
    vitessegroupex = vitessegroupex/(k1+k2);
    vitessegroupey = vitessegroupey/(k1+k2);
  }

  //Si l'oiseau n'a aucun voisin, sa vitesse restera la même
  else {
    vitessegroupex = vx;
    vitessegroupey = vy;
  }

  //Si le plus proche voisin de l'oiseau est suffisamment proche, ils vont se repousser en urgence
  if (dmin < Taille2) {
    Fuite = 0.08;
  }

  //Mise à jour de la vitesse de l'oiseau, proche de vgroupe mais légèrement différente pour que les oiseaux forment des groupes
  double normvitesse = norm(vx, vy);
  double normvitessegroupe = norm(vitessegroupex, vitessegroupey);

  //on ajoute ici un terme de bruit afin d'étudier son effet sur la nuée.
  double vxaleatoire = rejetgaussien(0, 10), vyaleatoire = rejetgaussien(0, 10);
  
  vx = vgroupe*(0.995*vx/normvitesse + 0.005*vitessegroupex/normvitessegroupe + 0.015*vxaleatoire + 0.008*(positiongroupex1-x)/normpositiongroupe1 - 0.008*(positiongroupex2-x)/normpositiongroupe2 - Fuite*dxmin/dmin);
  vy = vgroupe*(0.995*vy/normvitesse + 0.005*vitessegroupey/normvitessegroupe + 0.015*vyaleatoire + 0.008*(positiongroupey1-y)/normpositiongroupe1 - 0.008*(positiongroupey2-y)/normpositiongroupe2 -  Fuite*dymin/dmin);

  //La fonction renvoie les coordonées du barycentre de l'oiseau pour les dessiner sur l'interfacec SFML
  vector<double> barycentre(2,0);
  barycentre[0] = positiongroupex1;
  barycentre[1] = positiongroupey1;
  return barycentre;
}


//Fonction facilitant l'affichage d'un oiseau  
ostream& operator<< (ostream& out, const oiseau& O) {
  out << O.x << "   " << O.y << "   " << O.vx << "   " << O.vy;
  return out;
}
