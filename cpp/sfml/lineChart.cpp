#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#define PI 3.141593

int main() {
  // data
  int data[] = {1, 3, 2, 5, 4, 7},
      data_n = sizeof(data) / sizeof(int),
      data_max = *std::max_element(data, data + data_n);

  // create window
  sf::ContextSettings settings;
  settings.antiAliasingLevel = 4;
  sf::RenderWindow window(sf::VideoMode({800,600}), "SFML", sf::State::Windowed, settings);

  // dot
  sf::CircleShape dot;
  dot.setFillColor(sf::Color(154,46,177));

  // line
  sf::RectangleShape line;
  line.setFillColor(sf::Color(154,46,177));

  // keep window open
  while (window.isOpen()) {
    float window_w = static_cast<float>(window.getSize().x), 
          window_h = static_cast<float>(window.getSize().y),
          window_min = std::min(window_w, window_h),
          space = window_w / data_n,
          scale = 0.9f * window_h / data_max,
          radius = 0.02f * window_min,
          line_w = radius / 2;

    // handle events
    while (std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      } else if(event->is<sf::Event::Resized>()) {
        sf::View view(sf::FloatRect({0.f,0.f}, sf::Vector2f(window.getSize())));
        window.setView(view);
      }
    }

    dot.setRadius(radius);
    dot.setOrigin({radius,radius});
    dot.setPosition({window_w/2, window_h/2});
    line.setOrigin({0.f, line_w / 2});

    // clear
    window.clear(sf::Color(127,127,127));
    
    // draw
    for (int i = 0; i < data_n; i++) {
      // dot
      float x = (i + 0.5f) * space,
            y = window_h - data[i] * scale,
            x_old, y_old;
      dot.setPosition({x,y});
      window.draw(dot);

      // line
      if (i > 0) {
        float dx = x_old - x,
              dy = y_old - y,
              length = std::sqrt(std::pow(dy,2) + std::pow(dx,2)),
              angle= std::atan2(dy, dx);
        line.setSize({length, line_w});
        line.setPosition({x,y});
        line.setRotation(sf::radians(angle));
        window.draw(line);
      }

      // store previous values
      x_old = x;
      y_old = y;
    }
    
    // display
    window.display();
  }
  return 0;
}
