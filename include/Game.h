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
    float m_windowWidth;
    float m_windowHeight;
    Flock m_flock;
    bool m_paused;
    bool m_focused;
};
