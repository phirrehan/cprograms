#include <SFML/Graphics.hpp>

int main() {

  // anti aliasing
  sf::ContextSettings settings;
  settings.antiAliasingLevel = 4;

  // create window
  sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML",
                          sf::State::Windowed, settings);

  // keep window open
  while (window.isOpen()) {
    // handle events
    while (std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      } else if (event->is<sf::Event::Resized>()) {
        sf::View view(
            sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize())));
        window.setView(view);
      }
    }

    // window size
    float window_w = window.getView().getSize().x,
          window_h = window.getView().getSize().y,
          window_min = std::min(window_w, window_h);

    // parameters

    // fill window with color
    window.clear(sf::Color(39, 39, 39));

    // draw

    // display
    window.display();
  }
  return 0;
}
