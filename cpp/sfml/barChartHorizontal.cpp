#include <SFML/Graphics.hpp>
#include <algorithm>

int main() {
  // data
  int data[]   = {1, 2, 3, 4, 5}, 
      data_n   = 5, 
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
    float size = 0.6f * window_h / data_n;
    float scale = 0.9f * window_w / data_max;
    float space = window_h / data_n;


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
    bar.setOrigin({0.f, size/2});
    for (int i = 0; i<5; i++) {
      bar.setSize({data[i] * scale, size});
      bar.setPosition({0.f, (i + 0.5f) * space});
      window.draw(bar);
    }
    
    // display
    window.display();
  }
  return 0;
}
