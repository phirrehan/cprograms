#include <SFML/Graphics.hpp>

int main() {
  // create window
  sf::RenderWindow window(sf::VideoMode({800,600}), "SFML", sf::Style::Default);

  // create shape
  sf::ConvexShape shape;
  shape.setFillColor(sf::Color(154,47,171));
  shape.setOutlineColor(sf::Color(127,38,139));
  shape.setOutlineThickness(20.f);
  shape.setPosition({400.f, 300.f});

  // set points
  float width  = 400.f,
        height = 300.f;
  shape.setPointCount(4);
  shape.setPoint(0, {-width/2, 0        });
  shape.setPoint(1, { 0      , -height/2});
  shape.setPoint(2, { width/2, 0        });
  shape.setPoint(3, { 0      , height/2 });

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
    window.draw(shape);
    
    // display
    window.display();
  }
  return 0;
}
