#include<iostream>
#include<time.h>
#include<math.h>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
#include <SFML/Graphics.hpp>
#include "fonctions.h"
#include "oiseaux3.h"
#include "cercle.h"

using namespace std;

int main() {
  //Initialisation de la graine des processus aléatoires
  srand48(time(NULL));

  //Import d'une police d'écriture pour l'interface SFML
  sf::Font font;
  font.loadFromFile("Roboto-Black.ttf");

  //Déclaration d'un paramètre d'ordre
  double parametre, paralocal, parametremax=0;

  //Définition des propriétés des oiseaux
  double Rayonvision = 200, Taille = 20, Taille2 = 10, Anglevue = 2*M_PI, vgroupe = 3;

  //Taille de l'interface SFML sur laquelle les oiseaux vont se déplacer
  double Taillesurfacex = 1600., Taillesurfacey = 900.;

  //Nombre d'oiseaux dans la nuée
  int N = 80;

  //intervalle de temps entre chaque itération
  double dt = 0.1;

  //Définition des obstacles circulaires que les oiseaux doivent éviter
  vector<cercle> obst;
  vector<oiseau> nuee; //Notre nuée d'oiseaux est définie comme un vecteur d'oiseaux
  /*cercle C(800, 450, 200);
  obst.push_back(C);
  cercle C1(150, 150, 25);
  obst.push_back(C1);
  cercle C2(1450, 150, 100);
  obst.push_back(C2);
  cercle C3(800, 750, 75);
  obst.push_back(C3);*/


  //Initialisation de la nuée d'oiseaux
  for(int i = 0; i < N; i++) {
    oiseau O(Rayonvision, Taille, Taille2, vgroupe, Anglevue,  Taillesurfacex, Taillesurfacey, obst);
    nuee.push_back(O);
  }

  //On stocke dans un tableau les barycentres des oiseaux pour les dessiner sur l'interface SFML
  vector<double> barycentre(2, 0);
  vector<vector<double>> nuee_barycentre(N, barycentre);

  /*  //facultatif: affichage des positions et vitesses initiales des oiseaux de la nuée
  for(int i = 0; i < N; i++)
  cout << nuee[i] << endl;; */


  //Ouverture de la fenêtre SFML
  sf::RenderWindow window(sf::VideoMode(Taillesurfacex, Taillesurfacey), "Nuee d'etourneaux", sf::Style::Default);

  //On ouvre un fichier pour stocker des informations sur le programme
  fstream fich;
  fich.open("Resultats.csv", ios::out);
  fich <<  "temps parametre x y vx vy barycentrex barycentrey"<< endl;
  //On définit un compteur pour le nombre d'itérations effectuées
  int compteur = 0;
  
  //On fait tourner le programme jusqu'à ce que la fenêtre soit fermée
    while (window.isOpen()) {

      compteur += 1;
      
      //On inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
      sf::Event event;
      while (window.pollEvent(event)) {
	
	//Evènement "fermeture demandée" : on ferme la fenêtre en appuyant sur close
	if (event.type == sf::Event::Closed)
	  window.close();
      }
      
      //Effacement de la fenêtre en noir
      window.clear(sf::Color(0,0,0));
      
      //Définition du Barycentre de tous les oiseaux (juste esthétique)
      double barycentreX=0,barycentreY=0;      

      //1ere boucle sur tous les oiseaux de la nuée
      for (int i = 0; i < N; i++) {

	//Définition du barycentre local d'un oiseau
	barycentreX+=nuee[i].x/N;
	barycentreY+=nuee[i].y/N;

	// création d'un tableau de 3 vertex définissant un triangle
	sf::VertexArray oiseau(sf::Triangles, 3);
	
	// on dessine les oiseaux en utilisant leur vitesse pour savoir vers où ils se dirigent
	double norme_vitesse = norm(nuee[i].vx, nuee[i].vy);
	
	oiseau[0].position = sf::Vector2f(nuee[i].x + 10*nuee[i].vx/(2*norme_vitesse), nuee[i].y + 10*nuee[i].vy/(2*norme_vitesse));
	
	oiseau[1].position = sf::Vector2f(nuee[i].x - 10*(nuee[i].vx/(4*norme_vitesse) + nuee[i].vy/(4*norme_vitesse)), nuee[i].y - 10*(nuee[i].vy/(4*norme_vitesse) - nuee[i].vx/(4*norme_vitesse)));
	
	oiseau[2].position = sf::Vector2f(nuee[i].x - 10*(nuee[i].vx/(4*norme_vitesse) - nuee[i].vy/(4*norme_vitesse)), nuee[i].y - 10*(nuee[i].vy/(4*norme_vitesse) + nuee[i].vx/(4*norme_vitesse)));

	// on définit la couleur des sommets du triangle
	if (i == 0) {
	  oiseau[0].color = sf::Color::Red;
	  oiseau[1].color = sf::Color::Red;
	  oiseau[2].color = sf::Color::Red;
	}

	else {
	  oiseau[0].color = sf::Color::White;
	  oiseau[1].color = sf::Color::Green;
	  oiseau[2].color = sf::Color::Green;
	}


	//On dessine les oiseaux un par un
	window.draw(oiseau);	

	//On dessine le champ de vision oiseau, ainsi que ses différentes tailles
	/*sf::CircleShape cercle(Rayonvision);
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
	window.draw(cercle3);*/

	//On dessine le barycentre de chaque oiseau
	sf::CircleShape point(1);
	point.setFillColor(sf::Color(199,71,191));
	point.setPosition(nuee_barycentre[i][0], nuee_barycentre[i][1]);
	window.draw(point);
      }

      //On dessine les obstacles circulaires
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
      s << "parametre d'ordre = " << parametre << endl << "paramètre local = " << paralocal << endl << "temps = " << compteur/240 << " s";  //on remplit le flux
      text.setFont(font);  //on définit la police du texte
      text.setString(s.str());   //on remplit le texte avec le flux convertit en string
      text.setCharacterSize(10);
      text.setPosition(1300.f,800.f);
      window.draw(text);

      if (parametre > parametremax) {
	parametremax = parametre;
      }

      //synchronisation des FPS SFML avec l'écran d'ordinateur
      window.setFramerateLimit(200);
      // fin de la frame courante, affichage de tout ce qu'on a dessiné
      window.display();
      
      double barx = nuee_barycentre[0][0], bary = nuee_barycentre[0][1];
      //Mise à jour de la vitesse des oiseaux à l'intant t+dt
      for (int i = 0; i < N; i++)
	nuee_barycentre[i] = nuee[i].adaptationvitesse(nuee, vgroupe, Taillesurfacex, Taillesurfacey);
      //Adaptation de la vitesse des oiseaux pour éviter les obstacles
      for (unsigned int i = 0; i < obst.size(); i++)
	obst[i].contournement(&nuee, vgroupe);

      //Mise à jour de la position des oiseaux
      for (int i = 0; i < N; i++) {
	nuee[i].x = nuee[i].x + nuee[i].vx*dt; //position selon x
	nuee[i].y = nuee[i].y + nuee[i].vy*dt; //position selon y

	//condition périodique de la surface SFML selon x
	if (nuee[i].x < 0)
	  nuee[i].x += Taillesurfacex;
	else if (nuee[i].x > Taillesurfacex)
	  nuee[i].x -= Taillesurfacex;

	//condition périodique de la surface SFML selon y
	if (nuee[i].y < 0)
	  nuee[i].y += Taillesurfacey;
	else if (nuee[i].y > Taillesurfacey)
	  nuee[i].y -= Taillesurfacey;
      }

      //Calcul paramètre d'ordre global
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
      
      //Calcul du paramètre de cohésion local
      double distbar = norm(barx-nuee[0].x, bary-nuee[0].y);
      paralocal = norm(nuee_barycentre[0][0]-barx, nuee_barycentre[0][1]-bary)/distbar;


      //Pour écrire dans un fichier, on récupère des données.
      if (compteur % 60 == 0) {

	//On enregistre 4 fois par seconde dans l'ordre: temps, paramètre d'ordre, x, y, vx, vy, barycentre_x et barycentre_y de l'oiseau 0 de la nuée
	fich <<  compteur/240. << " " <<  parametre << " " << nuee[0].x << " " << nuee[0].y << " " <<  nuee[0].vx << " " << nuee[0].vy << " " <<  nuee_barycentre[0][0] << " " << nuee_barycentre[0][1] <<  endl;
	}
    }

    fich.close();

    return 0;
}
