#include <SFML/Graphics.hpp>
#include <iostream>

int main() {

  bool isMouseOverButton = false;

  // anti aliasing
  sf::ContextSettings settings;
  settings.antiAliasingLevel = 4;

  // create window
  sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML",
                          sf::State::Windowed, settings);
  // create shape of button
  sf::RectangleShape shape;

  auto DrawButton = [&](sf::Vector2f dimensions, sf::Vector2f position) {
    shape.setOrigin(shape.getGeometricCenter());
    shape.setPosition(position);
    shape.setSize(dimensions);
    window.draw(shape);
  };

  // keep window open
  while (window.isOpen()) {
    // handle events
    while (std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      } else if (event->is<sf::Event::Resized>()) {
        sf::View view(
            sf::FloatRect({ 0.f, 0.f }, sf::Vector2f(window.getSize())));
        window.setView(view);
      }
    }

    // window size
    float window_w = window.getView().getSize().x,
          window_h = window.getView().getSize().y,
          window_min = std::min(window_w, window_h);

    // parameters
    float size = 0.1f * window_min;
    auto mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));

    // when left click is pressed
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
      shape.setFillColor(sf::Color(0, 255, 90));
    else
      shape.setFillColor(sf::Color(155, 47, 171));

    // when mouse is over button
    if (shape.getGlobalBounds().contains(mouse_position)) {

      // on mouse entered
      if (!isMouseOverButton)
        std::cout << "Entered\n";

      isMouseOverButton = true;
    } else {
      shape.setFillColor(sf::Color(127, 127, 127));

      // if mouse is moved outside
      if (isMouseOverButton)
        std::cout << "Left\n";

      isMouseOverButton = false;
    }

    // fill window with color
    window.clear(sf::Color(39, 39, 39));

    // draw
    DrawButton({ size * 2.5f, size * 0.8f }, { window_w / 2, window_h / 2 });

    // display
    window.display();
  }
  return 0;
}
