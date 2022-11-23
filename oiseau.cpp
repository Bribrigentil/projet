#include<iostream>
#include<time.h>
#include<vector>
#include "oiseaux.h"

using namespace std;

int main()
{
  int N = 10; //Nombre d'oiseaux dans la nuée
  srand48(time(NULL));
  std::vector<oiseau> nuee;
  double t = drand48();
  oiseau O;
  for(int i = 0; i < N; i++) {
    O.initialiser(drand48(), drand48(), drand48(), drand48());
    nuee.push_back(O);
  }
  for(int i = 0; i < N; i++)
    nuee[i].afficher();
  return 1;
}
