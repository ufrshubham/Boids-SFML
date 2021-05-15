#include "Game.h"

#include "SFML/Window/Event.hpp"

// Construct window using SFML
Game::Game()
    : m_window(sf::VideoMode::getDesktopMode(), "Boids-SFML", sf::Style::None),
      m_windowWidth(m_window.getSize().x),
      m_windowHeight(m_window.getSize().y),
      m_flock(),
      m_boidSize(3.f),
      m_paused(false)
{
    for (int i = 0; i < 250; i++)
    {
        Boid b(m_windowWidth / 3, m_windowHeight / 3);
        m_flock.addBoid(b);
    }
}

void Game::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    static const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

    while (m_window.isOpen())
    {
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TIME_PER_FRAME)
        {
            timeSinceLastUpdate -= TIME_PER_FRAME;
            HandleInput();
            if (!m_paused)
            {
                Update(TIME_PER_FRAME);
            }
        }
        Render();
    }
}

void Game::HandleInput()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_window.close();
            break;
        default:
            break;
        }
    }

    // Real-time inputs.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        m_window.close();
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        const auto &mouseCoords = sf::Mouse::getPosition(m_window);
        Boid b((float)mouseCoords.x, (float)mouseCoords.y, false);
        m_flock.addBoid(b);
    }
}

void Game::Update(const sf::Time &dt)
{
    m_flock.Update(dt);
}

void Game::Render()
{
    m_window.clear();
    m_window.draw(m_flock);
    m_window.display();
}
