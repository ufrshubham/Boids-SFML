#include "Flock.h"

// =============================================== //
// ======== Flock Functions from Flock.h ========= //
// =============================================== //

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
        boid.borders();
    }
}

void Flock::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const auto &boid : m_boids)
    {
        target.draw(boid);
    }
}

int Flock::getSize()
{
    return m_boids.size();
}

Boid Flock::getBoid(int i)
{
    return m_boids[i];
}

void Flock::addBoid(const Boid &b)
{
    m_boids.push_back(std::move(b));
}
