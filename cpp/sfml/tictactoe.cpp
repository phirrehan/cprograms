#include <SFML/Graphics.hpp>

int main() {

  // state of grid
  char state[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

  // position of cursor
  int cursor_x = 1, cursor_y = 1;

  // turn
  bool is_X_turn = true;

  // winner
  char winner = ' '; // possible values are ' ', 'D', 'X', 'O' where D is draw

  sf::ContextSettings settings;
  settings.antiAliasingLevel = 4;
  // create window
  sf::RenderWindow window(sf::VideoMode({800, 600}), "TicTacToe",
                          sf::State::Windowed, settings);

  // create shapes
  sf::CircleShape circle;
  circle.setPointCount(60);
  sf::RectangleShape line;
  sf::RectangleShape cursor;

  // lambda function draw grid
  auto DrawGrid = [&](float space, float width, float position_x,
                      float position_y) {
    line.setSize({space * 3, width});
    line.setOrigin(line.getGeometricCenter());
    line.setFillColor(sf::Color(128, 128, 128));
    // horizontal
    line.setRotation(sf::degrees(0.f));
    line.setPosition({position_x, position_y - space / 2});
    window.draw(line);
    line.setPosition({position_x, position_y + space / 2});
    window.draw(line);
    // vertical
    line.setRotation(sf::degrees(90.f));
    line.setPosition({position_x - space / 2, position_y});
    window.draw(line);
    line.setPosition({position_x + space / 2, position_y});
    window.draw(line);
  };

  // lambda function draw X
  auto DrawX = [&](float size, float width, float position_x,
                   float position_y) {
    line.setSize({size, width});
    line.setOrigin(line.getGeometricCenter());
    line.setFillColor(sf::Color(0, 255, 90));
    line.setPosition({position_x, position_y});
    line.setRotation(sf::degrees(45.f));
    window.draw(line);
    line.setRotation(sf::degrees(-45.f));
    window.draw(line);
  };

  // lambda function draw O
  auto DrawO = [&](float size, float width, float position_x,
                   float position_y) {
    circle.setRadius(size / 2);
    circle.setOrigin(circle.getGeometricCenter());
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(sf::Color(0, 140, 255));
    circle.setOutlineThickness(-width);
    circle.setPosition({position_x, position_y});
    window.draw(circle);
  };

  // lambda function draw winning line
  auto DrawWinningLine = [&](float size, float width, float position_x,
                             float position_y, float angle, float scale = 1.f) {
    line.setSize({size * scale, width});
    line.setOrigin(line.getGeometricCenter());
    line.setFillColor(sf::Color(241, 197, 85));
    line.setPosition({position_x, position_y});
    line.setRotation(sf::degrees(angle));
    window.draw(line);
  };

  // lambda function draw cursor
  auto DrawCursor = [&](float size, float width, float position_x,
                        float position_y) {
    cursor.setSize({size, size});
    cursor.setOrigin(cursor.getGeometricCenter());
    cursor.setFillColor(sf::Color::Transparent);
    cursor.setOutlineColor(sf::Color(241, 197, 85));
    cursor.setOutlineThickness(-width);
    cursor.setPosition({position_x, position_y});
    window.draw(cursor);
  };

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
      } else if (auto *key = event->getIf<sf::Event::KeyPressed>()) {
        if (winner == ' ') {
          // move cursor with WSAD or arrow keys
          if ((key->scancode == sf::Keyboard::Scancode::A ||
               key->scancode == sf::Keyboard::Scancode::Left) &&
              cursor_x > 0)
            cursor_x--;
          else if ((key->scancode == sf::Keyboard::Scancode::D ||
                    key->scancode == sf::Keyboard::Scancode::Right) &&
                   cursor_x < 2)
            cursor_x++;
          else if ((key->scancode == sf::Keyboard::Scancode::W ||
                    key->scancode == sf::Keyboard::Scancode::Up) &&
                   cursor_y > 0)
            cursor_y--;
          else if ((key->scancode == sf::Keyboard::Scancode::S ||
                    key->scancode == sf::Keyboard::Scancode::Down) &&
                   cursor_y < 2)
            cursor_y++;

          // mark X or O (if empty)
          if (key->scancode == sf::Keyboard::Scancode::Space &&
              state[cursor_y][cursor_x] == ' ') {
            if (is_X_turn)
              state[cursor_y][cursor_x] = 'X';
            else
              state[cursor_y][cursor_x] = 'O';
            is_X_turn = !(is_X_turn);
          }
        }

        // restart if R or Enter is pressed
        if ((key->scancode == sf::Keyboard::Scancode::R ||
             key->scancode == sf::Keyboard::Scancode::Enter) &&
            winner != ' ') {
          for (int j = 0; j < 3; j++)
            for (int i = 0; i < 3; i++)
              state[j][i] = ' ';
          cursor_x = 1;
          cursor_y = 1;
          winner = ' ';
          is_X_turn = true;
        }
      }
    }

    // window size
    float window_w = static_cast<float>(window.getSize().x),
          window_h = static_cast<float>(window.getSize().y),
          window_min = std::min(window_w, window_h);

    // parameters
    float space = 0.3f * window_min, // size of a cell
        size = 0.8f * space,         // size of mark
        width = 0.1f * size;         // width of line

    // fill window with color
    window.clear(sf::Color(39, 39, 39));

    // draw

    // grid
    DrawGrid(space, width / 2, window_w / 2, window_h / 2);

    // loop through rows
    for (int j = 0; j < 3; j++) {
      // loop through columns
      for (int i = 0; i < 3; i++) {
        if (state[j][i] == 'O')
          DrawO(size, width, window_w / 2 + space * (i - 1),
                window_h / 2 + space * (j - 1));
        else if (state[j][i] == 'X')
          DrawX(size, width, window_w / 2 + space * (i - 1),
                window_h / 2 + space * (j - 1));
      }
    }

    // draw winning line
    for (int i = 0; i < 3; i++) {
      // horizontal
      if (state[i][0] != ' ' && state[i][0] == state[i][1] &&
          state[i][1] == state[i][2]) {
        DrawWinningLine(space * 3, width / 2, window_w / 2,
                        window_h / 2 + space * (i - 1), 0.f);
        winner = state[i][0];
      }
      // vertical
      if (state[0][i] != ' ' && state[0][i] == state[1][i] &&
          state[1][i] == state[2][i]) {
        DrawWinningLine(space * 3, width / 2, window_w / 2 + space * (i - 1),
                        window_h / 2, 90.f);
        winner = state[0][i];
      }
    }

    // diagonal 1
    if (state[1][1] != ' ' && state[0][0] == state[1][1] &&
        state[1][1] == state[2][2]) {
      DrawWinningLine(space * 3, width / 2, window_w / 2, window_h / 2, 45.f,
                      1.4f);
      winner = state[1][1];
    }
    // diagonal 2
    if (state[1][1] != ' ' && state[2][0] == state[1][1] &&
        state[1][1] == state[0][2]) {
      DrawWinningLine(space * 3, width / 2, window_w / 2, window_h / 2, -45.f,
                      1.4f);
      winner = state[1][1];
    }

    // check if game has drawed
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 3; i++) {
        if (state[j][i] == ' ')
          goto exit_loop;
        else if (i == 2 && j == 2)
          winner = 'D';
      }
    }
  exit_loop:

    if (winner == ' ')
      DrawCursor(space, width / 2, window_w / 2 + space * (cursor_x - 1),
                 window_h / 2 + space * (cursor_y - 1));

    // display
    window.display();
  }
  return 0;
}
