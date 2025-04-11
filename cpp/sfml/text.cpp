#include <SFML/Graphics.hpp>

int main() {

  // anti aliasing
  sf::ContextSettings settings;
  settings.antiAliasingLevel = 4;

  // create window
  sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML",
                          sf::State::Windowed, settings);

  // load font
  sf::Font font("/usr/share/fonts/TTF/arial.ttf");

  // create text
  sf::Text text(font, "Hello There", 100.f);
  sf::FloatRect bounds = text.getLocalBounds();
  // horizontal allignment
  // left allignment
  // text.setOrigin({bounds.position.x, 0.f});
  // right alignmnet
  // text.setOrigin({bounds.position.x + bounds.size.x, 0.f});
  // right alignmnet
  // text.setOrigin({bounds.position.x + bounds.size.x / 2, 0.f});

  // vertical allignment
  // top allignment
  // text.setOrigin({bounds.position.x + bounds.size.x / 2, bounds.position.y});
  // bottom allignment
  // text.setOrigin({bounds.position.x + bounds.size.x / 2,
  //                static_cast<float>(text.getCharacterSize())});
  // center allignment
  // text.setOrigin(
  //    {bounds.position.x + bounds.size.x / 2,
  //    text.getCharacterSize() * 0.75f});
  // top allignment
  text.setOrigin(
      {bounds.position.x + bounds.size.x / 2, text.getCharacterSize() * 0.75f});
  text.setPosition({400.f, 300.f});
  text.setFillColor(sf::Color(155, 47, 171));
  text.setOutlineThickness(-8.f);
  text.setStyle(sf::Text::Italic | sf::Text::Bold | sf::Text::Underlined);

  // create line
  sf::RectangleShape line({800.f, 2.f});
  line.setOrigin(line.getGeometricCenter());
  line.setPosition({400.f, 300.f});
  line.setFillColor(sf::Color(155, 47, 171));

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
    window.draw(text);
    // line.setRotation(sf::degrees(0.f));
    // window.draw(line);
    // line.setRotation(sf::degrees(90.f));
    // window.draw(line);

    // display
    window.display();
  }
  return 0;
}
