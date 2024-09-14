#include "Flock.h"

Flock::Flock(float windowWidth, float windowHeight)
    : m_windowWidth(windowWidth),
      m_windowHeight(windowHeight)
{
    // Randomly place boids in the world.
    for (int i = 0; i < 200; i++)
    {
        m_boids.emplace_back(rand() % (int)m_windowWidth + 1, rand() % (int)m_windowHeight + 1);
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
        sf::Vector2f acceleration;
        acceleration += boid.Coh(m_boids, sumOfPosition);
        acceleration += boid.Sep(m_boids);
        acceleration += boid.Ali(m_boids, sumOfVelocities);
        boid.Accelerate(acceleration);

        boid.Update(dt);
        boid.Borders(m_windowWidth, m_windowHeight, false);
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
