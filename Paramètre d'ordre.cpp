#include<string>

//Calcul paramètre d'ordre 
double vx_tot = 0.0;
double vy_tot = 0.0;
double norme_i = 0.0;
double norme_i_tot = 0.0;
double pmax= 0;  //On recupere le paramètre d'ordre max
for(int i = 0; i < nuee.size();i++)
{
    vx_tot = vx_tot + nuee[i].vx;  //Composante vx totale
    vy_tot = vy_tot + nuee[i].vy;  //Composante vy totale
    norme_i = sqrt(nuee[i].vx*nuee[i].vx + nuee[i].vy*nuee[i].vy);  //norme de la vitesse de l'oiseau i 
    norme_i_tot = norme_i_tot + norme_i;   // somme des normes
}
double parametre = sqrt(vx_tot*vx_tot + vy_tot*vy_tot)/norme_i_tot



//test 1 
sf::Text text;
text.setFont(font);
text.setString("Paramètre d'ordre = ", parametre);
text.setCharacterSize(60);
text.setPosition(1500.f,800.f)
window.draw(text)


//test 2
while (window.isOpen())
    {
        std::cout << "Paramètre d'ordre = " << parametre << std::endl;
    }

//test 3

sf::String PO(parametre,50);
PO.move(1500.f,800.f)
Window.Draw(PO);

//test 4 
std::stringstream parametre;
parametre.precision(3);
std::string par = parametre.str();
sf::String po(par,Arial, 50);
po.move(1500.f,800.f)
App.Draw(po)




// taux de rafraichissement de l'écran, placer après la création de l'écran
window.setVerticalSyncEnabled(true); 

