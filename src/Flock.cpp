#include "Flock.h"

Flock::Flock(float windowWidth, float windowHeight)
    : m_windowWidth(windowWidth),
      m_windowHeight(windowHeight)
{
    for (int i = 0; i < 250; i++)
    {
        m_boids.emplace_back(m_windowWidth / 3, m_windowHeight / 3);
    }
}

void Flock::Update(const sf::Time &dt)
{
    for (auto &boid : m_boids)
    {
        // Runs the run function for every boid in the flock checking against the flock
        // itself. Which in turn applies all the rules to the flock.
        // Run flock() on the flock of boids.
        // This applies the three rules, modifies velocities accordingly, updates data,
        // and corrects boids which are sitting outside of the SFML window
        boid.flock(m_boids);
        boid.Update(dt);
        boid.borders(m_windowWidth, m_windowHeight);
    }
}

void Flock::CreateBoidAt(float x, float y)
{
    m_boids.emplace_back(Boid(x, y, false));
}

void Flock::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const auto &boid : m_boids)
    {
        target.draw(boid);
    }
}
