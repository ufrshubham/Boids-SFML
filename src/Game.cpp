#include "Game.h"

#include "SFML/Window/Event.hpp"

// Construct window using SFML
Game::Game()
    : m_window(sf::VideoMode(1280.f, 720.f), "Boids-SFML", sf::Style::Close),
      m_windowWidth(1280.f),
      m_windowHeight(720.f),
      m_flock(1280.f, 720.f),
      m_paused(false),
      m_focused(true)
{
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
        case sf::Event::GainedFocus:
            m_focused = true;
            break;
        case sf::Event::LostFocus:
            m_focused = false;
            break;
        default:
            break;
        }
    }

    // Real-time inputs.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && m_focused)
    {
        m_window.close();
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_focused)
    {
        const auto &mouseCoords = sf::Mouse::getPosition(m_window);
        m_flock.CreateBoidAt((float)mouseCoords.x, (float)mouseCoords.y);
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
