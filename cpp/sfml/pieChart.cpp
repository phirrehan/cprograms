#include <SFML/Graphics.hpp>
#include <cmath>
#include <numeric>

int main() {

  // data
  int data[]   = {1, 2, 3, 4},
      data_n   = sizeof(data) / sizeof(int),
      data_sum = std::accumulate(data, data + data_n, 0);

  // colors
  sf::Color colors[] = {
    sf::Color(153, 221, 255),
    sf::Color(102, 204, 255),
    sf::Color(51 , 187, 255),
    sf::Color(0  , 170, 255)
  };

  sf::ContextSettings settings;
  settings.antiAliasingLevel = 4;
  // create window
  sf::RenderWindow window(sf::VideoMode({800,600}), "Pie Chart", sf::State::Windowed, settings);

  // create sector
  sf::ConvexShape sector;

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
    // window size
    float window_w   = window.getView().getSize().x,
          window_h   = window.getView().getSize().y,
          window_min = std::min(window_w, window_h);

    // parameters
    float radius = 0.4f * window_min,
          start  = -90.f,
          step   = 5.f;

    // clear
    window.clear(sf::Color(127,127,127));

    // draw
    for (int j = 0; j < data_n; j++) {
      float angle  = data[j] * 360.f / data_sum;
      int   n      = std::ceil(angle / step) + 1;
      sector.setFillColor(colors[j]);
      sector.setPosition({window_w/2,window_h/2});
      sector.setPointCount(n + 1);
      for (int i = 0; i < n - 1; i++) {
        sector.setPoint(i, sf::Vector2f(radius, sf::degrees(start + i * step)));
      }
      sector.setPoint(n-1, sf::Vector2f(radius, sf::degrees(start + angle)));
      sector.setPoint(n, {0.f, 0.f});
      window.draw(sector);

      // update
      start += angle;
    }
    
    // display
    window.display();
  }
  return 0;
}
