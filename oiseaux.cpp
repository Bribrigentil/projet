#include<iostream>
#include "oiseaux.H"
#include <time.h>
#include <vector>

using namespace std;

void oiseau::initialiser()
{
    std::vector<oiseau> oiseau(N);
}

void oiseau::alea()
{
    srand48(time(NULL));
    for(size_t i =0; i <oiseau.size();i++);
    {
        oiseau[i].x = drand48();
        oiseau[i].y = drand48);
        oiseau[i].vx = drand48();
        oiseau[i].vy = drand48();
    }
}
