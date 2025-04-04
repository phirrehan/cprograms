#include <SFML/Graphics.hpp>
#include <algorithm>

int main() {
  // data
  int data[]   = {1, 1, 2, 3, 5, 8, 13, 21}, 
      data_n   = sizeof(data) / sizeof(int), 
      data_max = *std::max_element(data, data+data_n);

  // create window
  sf::RenderWindow window(sf::VideoMode({800,600}), "Bar Chart", sf::Style::Default);

  // bar
  sf::RectangleShape bar({data[0] * 100.f,40.f});
  bar.setFillColor(sf::Color(155,46,170));

  // keep window open
  while (window.isOpen()) {
    // window size
    float window_w = static_cast<float>(window.getSize().x);
    float window_h = static_cast<float>(window.getSize().y);

    // parameters
    float size = 0.6f * window_w / data_n;
    float scale = 0.9f * window_h / data_max;
    float space = window_w / data_n;


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
    bar.setOrigin({size/2, 0.f});
    bar.setScale({1.f,-1.f});
    for (int i = 0; i < data_n; i++) {
      bar.setSize({size, data[i] * scale});
      bar.setPosition({(i + 0.5f) * space, window_h});
      window.draw(bar);
    }
    
    // display
    window.display();
  }
  return 0;
}
