#pragma once

#include "Flock.h"

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/CircleShape.hpp"

class Game
{
public:
    Game();
    void Run();

private:
    sf::RenderWindow window;
    int window_width;
    int window_height;

    Flock flock;
    float boidsSize;
    std::vector<sf::CircleShape> shapes;

    void Render();
    void HandleInput();
};
