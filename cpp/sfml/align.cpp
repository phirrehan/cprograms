#include <SFML/Graphics.hpp>

int main() {
  // create window
  sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML");

  // create rectangles and set their origins
  sf::RectangleShape topLeft({50.f,50.f});
  sf::RectangleShape topRight({50.f,50.f});
  topRight.setOrigin({50.f,0.f});
  sf::RectangleShape bottomLeft({50.f,50.f});
  bottomLeft.setOrigin({0.f,50.f});
  sf::RectangleShape bottomRight({50.f,50.f});
  bottomRight.setOrigin({50.f,50.f});
  sf::RectangleShape top({50.f,50.f});
  top.setOrigin({25.f,0.f});
  sf::RectangleShape bottom({50.f,50.f});
  bottom.setOrigin({25.f,50.f});
  sf::RectangleShape middleLeft({50.f,50.f});
  middleLeft.setOrigin({0.f,25.f});
  sf::RectangleShape middleRight({50.f,50.f});
  middleRight.setOrigin({50.f,25.f});
  sf::RectangleShape center({50.f,50.f});
  center.setOrigin({25.f,25.f});

  // set rectangle color
  topLeft.setFillColor(sf::Color(155,46,169));
  topRight.setFillColor(sf::Color(155,46,169));
  bottomLeft.setFillColor(sf::Color(155,46,169));
  bottomRight.setFillColor(sf::Color(155,46,169));
  top.setFillColor(sf::Color(155,46,169));
  bottom.setFillColor(sf::Color(155,46,169));
  middleLeft.setFillColor(sf::Color(155,46,169));
  middleRight.setFillColor(sf::Color(155,46,169));
  center.setFillColor(sf::Color(155,46,169));

  // keep window open
  while (window.isOpen()) {

    // check for event
    while (std::optional event = window.pollEvent()) {
      // close window
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      // update view
      else if (event->is<sf::Event::Resized>()) {
        sf::View view(sf::FloatRect({0.f,0.f}, sf::Vector2f(window.getSize())));
        window.setView(view);

        float window_w = static_cast<float>(window.getSize().x);
        float window_h = static_cast<float>(window.getSize().y);
        // set positions
        topRight      .setPosition({window_w  , 0.f        });
        bottomLeft    .setPosition({0.f       , window_h   });
        bottomRight   .setPosition({window_w  , window_h   });
        top           .setPosition({window_w/2, 0.f        });
        bottom        .setPosition({window_w/2, window_h   });
        middleLeft    .setPosition({0.f       , window_h/2 });
        middleRight   .setPosition({window_w  , window_h/2 });
        center        .setPosition({window_w/2, window_h/2 });
      }
    }

    window.clear(sf::Color(127,127,127));

    // draw
    window.draw(topLeft);
    window.draw(topRight);
    window.draw(bottomLeft);
    window.draw(bottomRight);
    window.draw(top);
    window.draw(bottom);
    window.draw(middleLeft);
    window.draw(middleRight);
    window.draw(center);

    // display
    window.display();

  }
  return 0;
}
