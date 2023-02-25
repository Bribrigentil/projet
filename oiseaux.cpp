#include<iostream>
#include"oiseaux.h"
#include<time.h>
#include"fonctions.h"
#include<ostream>
#include<cmath>

using namespace std;

oiseau::oiseau(double R, double T, double A, double M, double vgroupe,  double Taillesurfacex, double Taillesurfacey,double TailleOiseau) : obstacle() {
  //initialisegraine();
  positioninitiale(Taillesurfacex, Taillesurfacey);
  vitesseinitiale(vgroupe);
  comportement(R, T, A, M,TailleOiseau); 
}

oiseau::~oiseau() {
}
/**
void oiseau::initialisegraine() {
  graine = time(NULL);
  srand(graine);
}
*/

void oiseau::positioninitiale(double Taillesurfacex, double Taillesurfacey) {
  x = Taillesurfacex * double((rand()%1000)/1001.);
  y = Taillesurfacey * double((rand()%1000)/1001.);

  barycentrex=x; //Si l'oiseau est seul, barycentre des oiseaux visibles sur lui meme
  barycentrey=y;

}

void oiseau::vitesseinitiale(double vgroupe) {
  double variancevitesse = vgroupe/10, normvitesse;
  vx = rejetgaussien(vgroupe, variancevitesse);
  vy = rejetgaussien(vgroupe, variancevitesse);
  normvitesse = sqrt(vx*vx+vy*vy);
  vx = vgroupe * vx/normvitesse;
  vy = vgroupe * vy/normvitesse;
}

void oiseau::comportement(double R, double T, double A, double M,double TailleOiseau) {
  Rayonvision = R;
  Tempsreaction = T;
  anglevue = A;
  memoireangle = M;
  tailleO=TailleOiseau; //test de condition d'eloignement
}

void oiseau::taille() {
  obstacle::taille();
}


void oiseau::adaptationvitesse(vector<oiseau> nuee, double dt, double vgroupe, double Taillesurfacex, double Taillesurfacey) {
  double vitessegroupex = 0;
  double vitessegroupey = 0;
  double positiongroupex = 0;
  double positiongroupey = 0;

  int compteur1=0,compteur2=0; //On compte le nombre d'oiseaux qu'il voit (compteur1) et le nombre d'oiseaux trop proches (compteur2)
  double xfuite=0,yfuite=0; //Barycentre des oiseaux trop proches avec lequel il veut guarder ses distances
  double A=0,B=0,C=0,D=0;//coeffs pour prendre en compte l'eloignement
  double xcrit,ycrit,dcrit=tailleO/3;

  for (int i = 0; i < nuee.size(); i++) {
    double distance=sqrt((nuee[i].x-x)*(nuee[i].x-x)+(nuee[i].y-y)*(nuee[i].y-y));
    
    if ((distance!=0) && (distance-Rayonvision<=0)){
      //cout<<(sqrt((nuee[i].x-x)*(nuee[i].x-x)+(nuee[i].y-y)*(nuee[i].y-y))-Rayonvision<=0)<<endl;
      compteur1++;
      vitessegroupex += nuee[i].vx;
      vitessegroupey += nuee[i].vy;
      positiongroupex += nuee[i].x;
      positiongroupey += nuee[i].y;
    
    if (distance<tailleO){
      compteur2++;
      xfuite+=nuee[i].x; //position moyenes des oiseaux trop proches
      yfuite+=nuee[i].y;

      if (distance<dcrit){
        xcrit=nuee[i].x;
        ycrit=nuee[i].y;
        dcrit=distance;
      }
    }
    
    }
  }
  //Si il voit des oiseaux il modifie sa trajectoire
  if (compteur1>0){
    
    vitessegroupex = vitessegroupex/compteur1;
    vitessegroupey = vitessegroupey/compteur1;
    positiongroupex = positiongroupex/compteur1;
    positiongroupey = positiongroupey/compteur1;

    barycentrex=positiongroupex; //pour l'affichache du barycentre des oiseaux dans son champ de vision
    barycentrey=positiongroupey;

    /**
    if (positiongroupex - x < -Taillesurfacex/2)
      positiongroupex += Taillesurfacex;
    else if (positiongroupex - x > Taillesurfacex/2)
      positiongroupex -= Taillesurfacex;
    if (positiongroupey - y < -Taillesurfacey/2)
      positiongroupey += Taillesurfacey;
    else if (positiongroupey - y > Taillesurfacey/2)
      positiongroupey -= Taillesurfacey;
  */
    double normvitesse = sqrt(vx*vx+vy*vy);
    double normvitessegroupe = sqrt(vitessegroupex*vitessegroupex+vitessegroupey*vitessegroupey);
    double normposition = sqrt((x-positiongroupex)*(x-positiongroupex) + (y-positiongroupey)*(y-positiongroupey));

    //Si des oiseaux sont trop proches, il cherche à s'eloigner de maniere gaussienne
    if (compteur2>0){
    xfuite=xfuite/compteur2-x; //distance au barycentre de fuite
    yfuite=yfuite/compteur2-y;
    A=-xfuite/fabs(xfuite);
    B=-yfuite/fabs(yfuite);
    if (dcrit<tailleO/3){
      C=xcrit-x;D=ycrit-y;
      C=-C/fabs(C);D=-D/fabs(D);
    }
    }

  //avec un eloignement gaussien
    vx = vgroupe*(0.99*vx/normvitesse + 0.01*vitessegroupex/normvitessegroupe + 0.008*(positiongroupex-x)/normposition + A*0.008*gaussienne(xfuite,3*tailleO)+C*0.08/***gaussienne(xcrit,3*tailleO)*/);
    vy = vgroupe*(0.99*vy/normvitesse + 0.01*vitessegroupey/normvitessegroupe + 0.008*(positiongroupey-y)/normposition+ B*0.008*gaussienne(yfuite,3*tailleO)+D*0.08/***gaussienne(ycrit,3*tailleO)*/);
    

    //vx = vgroupe*(0.988*vx/normvitesse +/* 0.004*vitessegroupex/normvitessegroupe*/ + 0.008*(positiongroupex-x)/normposition + A*0.1*gaussienne(xfuite,tailleO)/**+C*10*gaussienne(xcrit,3*tailleO)*/);
    //vy = vgroupe*(0.988*vy/normvitesse +/* 0.004*vitessegroupey/normvitessegroupe*/ + 0.008*(positiongroupey-y)/normposition+ B*0.1*gaussienne(yfuite,tailleO)/**+D*10*gaussienne(ycrit,3*tailleO)*/);
    
  }
  else
  {
    barycentrex=x;
    barycentrey=y;
  }
  
}
  
ostream& operator<< (ostream& out, const oiseau& O) {
  out << O.x << "," << O.y << "," << O.vx << "," << O.vy;
  return out;
}
