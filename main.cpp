#include<iostream>
#include<time.h>
#include<math.h>
#include<vector>
#include <SFML/Graphics.hpp>
#include "oiseaux.h"

using namespace std;

int main()
{
  srand48(time(NULL));

  double Rayonvision = 3, Tempsreaction = 1, Anglevue = 0, Memoireangle = 1; //propriétés, comportement des oiseaux
  
  int Taillesurfacex = 1600, Taillesurfacey = 900; //taille de l'interface SFML sur laquelle les oiseaux vont se déplacer
  
  int N = 30; //Nombre d'oiseaux dans la nuée

  double dt = 0.1; //intervalle de temps entre chaque itération
  
  vector<oiseau> nuee; //Notre nuée d'oiseaux est définie comme un vecteur d'oiseaux

  for(int i = 0; i < N; i++) { //initialisation de la nuée d'oiseaux
    oiseau O(Rayonvision, Tempsreaction, Anglevue, Memoireangle, Taillesurfacex, Taillesurfacey);
    nuee.push_back(O);
  }
  
  for(int i = 0; i < N; i++) //facultatif: affichage des positions et vitesses initiales des oiseaux de la nuée
    cout << nuee[i] << endl;;

  
  sf::RenderWindow window(sf::VideoMode(Taillesurfacex, Taillesurfacey), "Image initiale", sf::Style::Default);
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
      for (int i = 0; i < N; i++) {
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

	// pas de coordonnées de texture ici, nous verrons ça plus tard

	//On dessine les oiseaux un par un
	window.draw(oiseau);
      }

      // fin de la frame courante, affichage de tout ce qu'on a dessiné
      window.display();

      for (int i = 0; i < N; i++) { //mise à jour de la position des oiseaux à l'intant t+dt
	
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
