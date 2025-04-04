#include <SFML/Graphics.hpp>

int main() {
  // create window
  sf::RenderWindow window(sf::VideoMode({800,600}), "SFML", sf::Style::Default);

  // keep window open
  while (window.isOpen()) {
    // handle events
    while (std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      } else if(event->is<sf::Event::Resized>()) {
        sf::View view(sf::FloatRect({0.f,0.f}, sf::Vector2f(window.getSize())));
        window.setView(view);
      }
    }

    // clear
    window.clear(sf::Color(127,127,127));
    
    // draw
    //window.draw();
    
    // display
    window.display();
  }
  return 0;
}
