#include<iostream>
#include<time.h>
#include<vector>
#include "oiseaux.h"

using namespace std;

int main()
{
  double R = 3, T = 1, A = 0, M = 1; //comportement des oiseaux
  int Taillesurface = 500;
  int N = 10; //Nombre d'oiseaux dans la nuée
  srand48(time(NULL));
  vector<oiseau> nuee;
  double t = drand48();
  for(int i = 0; i < N; i++) {
    oiseau O(R, T, A, M, Taillesurface);
    nuee.push_back(O);
  }
  for(int i = 0; i < N; i++)
    cout << nuee[i] << endl;;
  return 0;
}
