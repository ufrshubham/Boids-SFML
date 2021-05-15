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
    void HandleInput();
    void Update(const sf::Time &dt);
    void Render();

private:
    sf::RenderWindow m_window;
    int m_windowWidth;
    int m_windowHeight;

    Flock m_flock;
    float m_boidSize;

    bool m_paused;
};
