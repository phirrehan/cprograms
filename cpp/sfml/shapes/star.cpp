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
  int   points  = 5 * 2; // increase first number to get desired number of points
  float radius = 200.f,
        angle  = 360.f / points, // angle is central angle of regular polygon
        offset = 90.f;
  shape.setPointCount(points);
  for (int i = 0; i < points; i++) {
    if (i % 2 == 0) {
      shape.setPoint(i, sf::Vector2f(  radius, sf::degrees(angle * i - offset)));
    } else {
      shape.setPoint(i, sf::Vector2f(radius/2, sf::degrees(angle * i - offset)));
    }
  }

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
