#include "Flock.h"

Flock::Flock(float windowWidth, float windowHeight)
    : m_windowWidth(windowWidth),
      m_windowHeight(windowHeight)
{
    // Randomly place boids in the world.
    for (int i = 0; i < 100; i++)
    {
        m_boids.emplace_back(rand() % (int)m_windowWidth, rand() % (int)m_windowHeight);
    }
}

void Flock::Update(const sf::Time &dt)
{
    // To save looping over all the boids in Boid::Coh() just to
    // figure out the perceived center.
    sf::Vector2f sumOfPosition;
    sf::Vector2f sumOfVelocities;
    for (const auto &boid : m_boids)
    {
        sumOfPosition.x += boid.getPosition().x;
        sumOfPosition.y += boid.getPosition().y;

        sumOfVelocities.x += boid.GetVelocity().x;
        sumOfVelocities.y += boid.GetVelocity().y;
    }

    for (auto &boid : m_boids)
    {
        boid.Coh(m_boids, sumOfPosition);
        boid.Sep(m_boids);
        boid.Ali(m_boids, sumOfVelocities);

        boid.Update(dt);
        boid.Borders(m_windowWidth, m_windowHeight);
    }
}

void Flock::CreateBoidAt(float x, float y)
{
    m_boids.emplace_back(Boid(x, y));
}

void Flock::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const auto &boid : m_boids)
    {
        target.draw(boid);
    }
}
