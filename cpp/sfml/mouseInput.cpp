#include <SFML/Graphics.hpp>
#include <iostream>

int main() 
{
  sf::ContextSettings settings;
  settings.antiAliasingLevel = 4;

  // mouse button state
  bool isLeftPressed  = false,
       isRightPressed = false;

  // mouse on screen
  bool cursorOnScreen = false;

  // colors
  sf::Color colors[] = {
    {155, 47 , 171}, // purple
    {170, 255, 0  }, // green
    {0  , 170, 255}  // blue
  };
  int colors_index = 0,
      colors_n = sizeof(colors) / sizeof(colors[0]);

  // create window
  sf::RenderWindow window(sf::VideoMode({800,600}), "SFML", sf::State::Windowed, settings);

  // hide cursor visibility
  //window.setMouseCursorVisible(false);

  // create shapes
  sf::RectangleShape shape;

  // lambda function draw rectangle
  auto DrawBox = [&] (sf::Vector2f dimensions, sf::Vector2f position, sf::Color color) 
  {
    shape.setOrigin(shape.getGeometricCenter());
    shape.setSize(dimensions);
    shape.setPosition(position);
    shape.setFillColor(color);
    window.draw(shape);
  };

  // keep window open
  while (window.isOpen()) 
  {
    // handle events
    while (std::optional event = window.pollEvent())
    {
      if (event->is<sf::Event::Closed>())
      {
        window.close();
      } 
      else if (event->is<sf::Event::Resized>())
      {
        sf::View view(sf::FloatRect({0.f,0.f}, sf::Vector2f(window.getSize())));
        window.setView(view);
      }
      else if (auto* mouse = event->getIf<sf::Event::MouseWheelScrolled>())
      {
        if (mouse->wheel == sf::Mouse::Wheel::Vertical)
        {
          if (mouse->delta > 0)
            std::cout << "Sroll Up\n";
          else  
            std::cout << "Scroll Down\n";
        }
        if (mouse->wheel == sf::Mouse::Wheel::Horizontal)
        {
          if (mouse->delta > 0)
            std::cout << "Sroll Right\n";
          else  
            std::cout << "Scroll Left\n";
        }
      }
      else if (event->is<sf::Event::MouseEntered>())
        cursorOnScreen = true;
      else if (event->is<sf::Event::MouseLeft>())
        cursorOnScreen = false;
    }


    // mouse button
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
      if (! isLeftPressed) 
      {
        std::cout << "Left Click Pressed\n";
        if (colors_index < colors_n - 1)
          colors_index++;
      }
      isLeftPressed = true;
    }
    else 
    {
      if (isLeftPressed)
        std::cout << "Left Click Released\n";
      isLeftPressed = false;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
    {
      if (! isRightPressed) 
      {
        std::cout << "Right Click Pressed\n";
        if (colors_index > 0)
          colors_index--;
      }
      isRightPressed = true;
    }
    else 
    {
      if (isRightPressed)
        std::cout << "Right Click Released\n";
      isRightPressed = false;
    }

    // window size
    float window_w   = window.getView().getSize().x,
          window_h   = window.getView().getSize().y,
          window_min = std::min(window_w, window_h);
    
    // parameters
    sf::Vector2i position = sf::Mouse::getPosition(window);
    float size = window_min * 0.1f;

    // clear
    window.clear(sf::Color(39,39,39));

    // draw
    if (cursorOnScreen)
      DrawBox({size, size}, sf::Vector2f(position), colors[colors_index]);

    // display
    window.display();
  }
  return 0;
}
