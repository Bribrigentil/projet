#ifndef oiseau_H
#define oiseau_H
class oiseau
{
    public:
    int N;  //Nb de piaf
    double x;  //position selon x
    double y;  // position selon y
    double vx;  //vitesse selon x
    double vy;  //vitesse selon y


    void initialiser();
    void alea(); //initialiser la position des oiseaux avec la méthode du rejet ?
};
#endif