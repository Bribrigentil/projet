#include <SFML/Graphics.hpp>

int main()
{
  sf::ContextSettings settings;  //permet de lisser les bords
  settings.antialiasingLevel = 10;
  
    // création de la fenêtre
  sf::RenderWindow window(sf::VideoMode(1200, 1024), "My window",sf::Style::Default, settings);

    // on fait tourner le programme tant que la fenêtre n'a pas été fermée
    while (window.isOpen())
    {
        // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        sf::Event event;
        while (window.pollEvent(event))
        {
            // fermeture de la fenêtre lorsque l'utilisateur le souhaite
            if (event.type == sf::Event::Closed)
                window.close();
        }

	    // effacement de la fenêtre en noir
	window.clear(sf::Color::Black);
	sf::ConvexShape triangle;
	triangle.setPointCount(3);
        triangle.setPoint(0, sf::Vector2f(50.f, 0.f));
	triangle.setPoint(1, sf::Vector2f(100.f, 60.f));
	triangle.setPoint(2, sf::Vector2f(80.f, 60.f));
	    
	window.draw(triangle);
	window.display();
	  
    }

    return 0;
}
