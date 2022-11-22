#include<iostream>
#include "oiseaux.H"
#include <ctime>
#include <vector>

using namespace std;

void oiseau::initialiser()
{
    std::vector<oiseau> oiseau(N);
}

void oiseau::alea()
{
    srand((unsigned int)time(0));
    for(size_t i =0; i <oiseau.size();i++);
    {
        oiseau[i].x = rand();
        oiseau[i].y = rand();
        oiseau[i].vx = rand();
        oiseau[i].vy = rand();
    }
}