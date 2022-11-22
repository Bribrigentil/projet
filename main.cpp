#include<iostream>
using namespace std;
#include "oiseaux.H"
#include<vector>

int main()
{
oiseau oiseau;
oiseau.initialiser();
oiseau.alea();

for(size_t i = 0; i <oiseau.size(); i++)
{
    cout << oiseau[i] <<endl;
}

return 0;

}