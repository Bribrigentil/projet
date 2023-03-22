#include<iostream>
#include<fstream>
#include<time.h>
#include<math.h>
#include"fonctions.h"
#include<vector>
#include<string>
#include <SFML/Graphics.hpp>
#include "oiseaux.h"

using namespace std;


int main()
{
  
   
  srand(time(NULL));
  
  
  double Rayonvision = 200, Tempsreaction = 1, Anglevue = M_PI*4/5., Memoireangle = 1, vgroupe = 2,TailleOiseau=Rayonvision/10; //propriétés, comportement des oiseaux
  
  int Taillesurfacex = 1750, Taillesurfacey = 950; //taille de l'interface SFML sur laquelle les oiseaux vont se déplacer
  
  int N = 100; //Nombre d'oiseaux dans la nuée

  double dt = 0.1; //intervalle de temps entre chaque itération
  
  vector<oiseau> nuee; //Notre nuée d'oiseaux est définie comme un vecteur d'oiseaux
  for(int i = 0; i < N; i++) { //initialisation de la nuée d'oiseaux
    oiseau O(Rayonvision, Tempsreaction, Anglevue, Memoireangle, vgroupe, Taillesurfacex, Taillesurfacey,TailleOiseau);
    nuee.push_back(O);
  }
  
  sf::RenderWindow window(sf::VideoMode(Taillesurfacex, Taillesurfacey), "Image initiale", sf::Style::Default);

    window.setFramerateLimit(240); //nombre maximal d'images par secondes

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

      // création d'un tableau de 3 vertex définissant un triangle
      double barycentreX=0,barycentreY=0;
      for (int i = 0; i < N; i++) {
    barycentreX+=nuee[i].x/N;
    barycentreY+=nuee[i].y/N;
	sf::VertexArray oiseau(sf::Triangles, 3);

	// on définit la position des sommets du triangle
  
	double norme_vitesse = sqrt(nuee[i].vx*nuee[i].vx + nuee[i].vy*nuee[i].vy);
  
	oiseau[0].position = sf::Vector2f(nuee[i].x + 10*nuee[i].vx/(2*norme_vitesse), nuee[i].y + 10*nuee[i].vy/(2*norme_vitesse));
	oiseau[1].position = sf::Vector2f(nuee[i].x - 10*(nuee[i].vx/(4*norme_vitesse) + nuee[i].vy/(4*norme_vitesse)), nuee[i].y - 10*(nuee[i].vy/(4*norme_vitesse) - nuee[i].vx/(4*norme_vitesse)));
	oiseau[2].position = sf::Vector2f(nuee[i].x - 10*(nuee[i].vx/(4*norme_vitesse) - nuee[i].vy/(4*norme_vitesse)), nuee[i].y - 10*(nuee[i].vy/(4*norme_vitesse) + nuee[i].vx/(4*norme_vitesse)));

	// on définit la couleur des sommets du triangle
  
	oiseau[0].color = sf::Color::Green;
  oiseau[1].color = sf::Color::White;
	oiseau[2].color = sf::Color::White;
  window.draw(oiseau);
  // Champ de vision oiseau
  /*
    sf::CircleShape cercle(Rayonvision);
    cercle.setOutlineThickness(1.f);
    cercle.setFillColor(sf::Color::Transparent);
    cercle.setPosition(nuee[i].x-Rayonvision,nuee[i].y-Rayonvision);
    window.draw(cercle);

    sf::CircleShape cercle2(TailleOiseau);
    cercle2.setOutlineThickness(1.f);
    cercle2.setOutlineColor(sf::Color(250, 150, 100));
    cercle2.setFillColor(sf::Color::Transparent);
    cercle2.setPosition(nuee[i].x-TailleOiseau,nuee[i].y-TailleOiseau);
    window.draw(cercle2);

    sf::CircleShape cercle3(TailleOiseau/3);
    cercle3.setOutlineThickness(1.f);
    cercle3.setOutlineColor(sf::Color::Red);
    cercle3.setFillColor(sf::Color::Transparent);
    cercle3.setPosition(nuee[i].x-TailleOiseau/3,nuee[i].y-TailleOiseau/3);
    window.draw(cercle3);
	// pas de coordonnées de texture ici, nous verrons ça plus tard

	//On dessine les oiseaux un par un
	*/

  // Barycentre de chaque oiseau
  sf::CircleShape point(2.f);
  point.setFillColor(sf::Color(199,71,191));
  point.setPosition(nuee[i].barycentrex-1.f,nuee[i].barycentrey-5.f);
  window.draw(point);
 
      }

//On dessine LE centre de masse total
  sf::CircleShape shape(5.f);
  shape.setFillColor(sf::Color::Red);
  shape.setPosition(barycentreX-5.f,barycentreY-5.f);
 
  window.draw(shape);

  

  // fin de la frame courante, affichage de tout ce qu'on a dessiné
  window.display();

      for (int i = 0; i < N; i++) //mise à jour de la position des oiseaux à l'intant t+dt
	nuee[i].adaptationvitesse(nuee, dt, vgroupe, Taillesurfacex, Taillesurfacey);

      for (int i = 0; i < N; i++) {
	
	nuee[i].x = nuee[i].x + nuee[i].vx*dt; //position selon x
	
	if (nuee[i].x < 0) //condition périodique de la surface SFML selon x
	  nuee[i].x += Taillesurfacex;
	else if (nuee[i].x > Taillesurfacex)
	  nuee[i].x -= Taillesurfacex;
	
	nuee[i].y = nuee[i].y + nuee[i].vy*dt; //position selon y 
	
	if (nuee[i].y < 0) //condition périodique de la surface SFML selon y
	  nuee[i].y += Taillesurfacey;
	else if (nuee[i].y > Taillesurfacey)
	  nuee[i].y -= Taillesurfacey;
      }
    }

    return 0;
}
