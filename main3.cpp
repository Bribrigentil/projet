#include<iostream>
#include<time.h>
#include<math.h>
#include<vector>
#include<string>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include "fonctions.h"
#include "oiseaux3.h"
#include "cercle.h"

using namespace std;

int main()
{
  srand48(time(NULL));
  sf::Font font;
  font.loadFromFile("Roboto-Black.ttf");
  double parametre;

  double Rayonvision = 100, Taille = 20, Taille2 = 5, vgroupe = 3; //propriétés, comportement des oiseaux
  
  double Taillesurfacex = 1600., Taillesurfacey = 900.; //taille de l'interface SFML sur laquelle les oiseaux vont se déplacer
  
  int N = 100; //Nombre d'oiseaux dans la nuée

  double dt = 0.1; //intervalle de temps entre chaque itération

  vector<cercle> obst;
  vector<oiseau> nuee; //Notre nuée d'oiseaux est définie comme un vecteur d'oiseaux
  /*cercle C(800, 450, 200);
  obst.push_back(C);
  cercle C1(150, 150, 100);
  obst.push_back(C1);
  cercle C2(1450, 150, 100);
  obst.push_back(C2);
  cercle C3(800, 750, 100);
  obst.push_back(C3);*/

  for(int i = 0; i < N; i++) { //initialisation de la nuée d'oiseaux
    oiseau O(Rayonvision, Taille, Taille2, vgroupe, Taillesurfacex, Taillesurfacey, obst);
    nuee.push_back(O);
  }
  
  for(int i = 0; i < N; i++) //facultatif: affichage des positions et vitesses initiales des oiseaux de la nuée
    cout << nuee[i] << endl;;
  
  sf::RenderWindow window(sf::VideoMode(Taillesurfacex, Taillesurfacey), "Nuee d'etourneaux", sf::Style::Default);
    // on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
    while (window.isOpen()) {
      
      // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
      sf::Event event;
      while (window.pollEvent(event)) {
	
	// évènement "fermeture demandée" : on ferme la fenêtre en appuyant sur close
	if (event.type == sf::Event::Closed)
	  window.close();
      }
      
      // effacement de la fenêtre en noir
      window.clear(sf::Color::Black);

      double barycentreX=0,barycentreY=0;      

      // création d'un tableau de 3 vertex définissant un triangle
      for (int i = 0; i < N; i++) {

	barycentreX+=nuee[i].x/N;
	barycentreY+=nuee[i].y/N;	
	sf::VertexArray oiseau(sf::Triangles, 3);

	
	// on dessine les oiseaux en utilisant leur vitesse pour savoir vers où ils se dirigent
	double norme_vitesse = norm(nuee[i].vx, nuee[i].vy);
	
	oiseau[0].position = sf::Vector2f(nuee[i].x + 10*nuee[i].vx/(2*norme_vitesse), nuee[i].y + 10*nuee[i].vy/(2*norme_vitesse));
	
	oiseau[1].position = sf::Vector2f(nuee[i].x - 10*(nuee[i].vx/(4*norme_vitesse) + nuee[i].vy/(4*norme_vitesse)), nuee[i].y - 10*(nuee[i].vy/(4*norme_vitesse) - nuee[i].vx/(4*norme_vitesse)));
	
	oiseau[2].position = sf::Vector2f(nuee[i].x - 10*(nuee[i].vx/(4*norme_vitesse) - nuee[i].vy/(4*norme_vitesse)), nuee[i].y - 10*(nuee[i].vy/(4*norme_vitesse) + nuee[i].vx/(4*norme_vitesse)));

	// on définit la couleur des sommets du triangle
	oiseau[0].color = sf::Color::Red;
        oiseau[1].color = sf::Color::Green;
	oiseau[2].color = sf::Color::Green;

	//On dessine les oiseaux un par un
	window.draw(oiseau);	

	/*	// Champ de vision oiseau
  
	sf::CircleShape cercle(Rayonvision);
	cercle.setOutlineThickness(1.f);
	cercle.setFillColor(sf::Color::Transparent);
	cercle.setPosition(nuee[i].x-Rayonvision,nuee[i].y-Rayonvision);
	window.draw(cercle);

	sf::CircleShape cercle2(Taille);
	cercle2.setOutlineThickness(1.f);
	cercle2.setOutlineColor(sf::Color(250, 150, 100));
	cercle2.setFillColor(sf::Color::Transparent);
	cercle2.setPosition(nuee[i].x-Taille,nuee[i].y-Taille);
	window.draw(cercle2);

	sf::CircleShape cercle3(Taille2);
	cercle3.setOutlineThickness(1.f);
	cercle3.setOutlineColor(sf::Color::Red);
	cercle3.setFillColor(sf::Color::Transparent);
	cercle3.setPosition(nuee[i].x-Taille2,nuee[i].y-Taille2);
	window.draw(cercle3);

	// Barycentre de chaque oiseau
	sf::CircleShape point(2.f);
	point.setFillColor(sf::Color(199,71,191));
	point.setPosition(nuee[i].barycentrex-1.f,nuee[i].barycentrey-5.f);
	window.draw(point);	*/
      }

      for (unsigned int i = 0; i < obst.size(); i++) {
        sf::CircleShape cercle(obst[i].Rayon);
        cercle.setPosition(sf::Vector2f(obst[i].x - obst[i].Rayon, obst[i].y - obst[i].Rayon));
        cercle.setFillColor(sf::Color::Blue);
	window.draw(cercle);
      }

      /*      //On dessine LE centre de masse total
      sf::CircleShape shape(5.f);
      shape.setFillColor(sf::Color::Red);
      shape.setPosition(barycentreX-5.f,barycentreY-5.f);
      window.draw(shape);   */   

      
      //affichage du paramètre d'ordre sur la fenêtre SFML
      sf::Text text;  //déclaration de la variable texte
      ostringstream s;   //déclaration du fux à afficher
      s << "parametre d'ordre = " << parametre;  //on remplit le flux
      text.setFont(font);  //on définit la police du texte
      text.setString(s.str());   //on remplit le texte avec le flux convertit en string
      text.setCharacterSize(10);
      text.setPosition(1300.f,800.f);
      window.draw(text);

      //synchronisation des FPS SFML avec l'écran d'ordinateur
      window.setVerticalSyncEnabled(true); 
      // fin de la frame courante, affichage de tout ce qu'on a dessiné
      window.display();
      

      for (int i = 0; i < N; i++) //mise à jour de la vitesse des oiseaux à l'intant t+dt
	nuee[i].adaptationvitesse(nuee, vgroupe, Taillesurfacex, Taillesurfacey);
      for (unsigned int i = 0; i < obst.size(); i++)
	obst[i].contournement(&nuee, vgroupe);
      
      
      for (int i = 0; i < N; i++) { //mise à jour de la position des oiseaux	
	nuee[i].x = nuee[i].x + nuee[i].vx*dt; //position selon x
	nuee[i].y = nuee[i].y + nuee[i].vy*dt; //position selon y
	
	if (nuee[i].x < 0) //condition périodique de la surface SFML selon x
	  nuee[i].x += Taillesurfacex;
	else if (nuee[i].x > Taillesurfacex)
	  nuee[i].x -= Taillesurfacex;
	
	if (nuee[i].y < 0) //condition périodique de la surface SFML selon y
	  nuee[i].y += Taillesurfacey;
	else if (nuee[i].y > Taillesurfacey)
	  nuee[i].y -= Taillesurfacey;
      }

      //Calcul paramètre d'ordre 
      double vx_tot = 0.0;
      double vy_tot = 0.0;
      double norme_i = 0.0;
      double norme_i_tot = 0.0;
      for(unsigned int i = 0; i < nuee.size();i++) {
      	vx_tot = vx_tot + nuee[i].vx;  //Composante vx totale
      	vy_tot = vy_tot + nuee[i].vy;  //Composante vy totale
      	norme_i = norm(nuee[i].vx, nuee[i].vy);  //norme de la vitesse de l'oiseau i
      	norme_i_tot = norme_i_tot + norme_i;   // somme des normes
      }
      parametre = norm(vx_tot, vy_tot)/norme_i_tot;
    }

    return 0;
}
