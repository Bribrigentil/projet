#include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Image initiale", sf::Style::Default);
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
    sf::VertexArray triangle(sf::Triangles, 3);

    // on définit la position des sommets du triangle
    triangle[0].position = sf::Vector2f(10, 10);
    triangle[1].position = sf::Vector2f(100, 10);
    triangle[2].position = sf::Vector2f(100, 100);

    // on définit la couleur des sommets du triangle
    triangle[0].color = sf::Color::Red
    triangle[1].color = sf::Color::Green;
    triangle[2].color = sf::Color::Green;

    // pas de coordonnées de texture ici, nous verrons ça plus tard

    window.draw(triangle);

    // fin de la frame courante, affichage de tout ce qu'on a dessiné
    window.display();
  }
  return 0;
}
