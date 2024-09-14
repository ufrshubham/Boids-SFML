#include "Boid.h"

#include "SFML/Window/VideoMode.hpp"

#include <cstdlib>
#include <cmath>

const sf::Color Boid::s_boidColor = sf::Color(235, 234, 233);

Boid::Boid() : CircleShape(8, 3)
{
    setPosition(0.f, 0.f);
    setOutlineColor(sf::Color(0, 255, 0));
    setFillColor(s_boidColor);
    setOutlineColor(sf::Color::Black);
    setOutlineThickness(2);
    setRadius(3.f);
}

Boid::Boid(float x, float y)
    : CircleShape(8, 3), m_velocity(rand() % (int)x, rand() % (int)y)
{
    setPosition(x, y);
    setOutlineColor(sf::Color(0, 255, 0));
    setFillColor(s_boidColor);
    setOutlineColor(sf::Color::Black);
    setOutlineThickness(2);
    setRadius(3.f);
}

void Boid::Update(const sf::Time &dt)
{
    const float magSquared = ((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
    if ((magSquared) > (m_speedLimit * m_speedLimit))
    {
        const auto mag = std::sqrt(magSquared);
        m_velocity.x /= mag;
        m_velocity.y /= mag;
    }

    move(m_velocity * dt.asSeconds());

    // Still need to check this math.
    float angle = (float)(std::atan2(m_velocity.x, -m_velocity.y) * 57.295778);
    this->setRotation(angle);
}

void Boid::Borders(const float &w_width, const float &w_height, bool wrap)
{
    const auto &position = this->getPosition();
    sf::Vector2f newPosition(position);
    if (position.x < 0)
    {
        if (wrap)
        {
            newPosition.x += w_width;
        }
        else
        {
            m_velocity.x = -m_velocity.x;
        }
    }
    if (position.y < 0)
    {
        if (wrap)
        {
            newPosition.y += w_height;
        }
        else
        {
            m_velocity.y = -m_velocity.y;
        }
    }
    if (position.x > w_width)
    {
        if (wrap)
        {
            newPosition.x -= w_width;
        }
        else
        {
            m_velocity.x = -m_velocity.x;
        }
    }
    if (position.y > w_height)
    {
        if (wrap)
        {
            newPosition.y -= w_height;
        }
        else
        {
            m_velocity.y = -m_velocity.y;
        }
    }
    this->setPosition(newPosition);
}

const sf::Vector2f &Boid::GetVelocity() const
{
    return m_velocity;
}

void Boid::SetVelocity(const sf::Vector2f &velocity)
{
    m_velocity.x = velocity.x;
    m_velocity.y = velocity.y;
}

void Boid::Accelerate(const sf::Vector2f &velocity)
{
    SetVelocity(GetVelocity() + velocity);
}

sf::Vector2f Boid::Sep(const std::vector<Boid> &boids)
{
    const auto &myPosition = this->getPosition();
    sf::Vector2f acceleration;

    for (const auto &boid : boids)
    {
        // Ignore self.
        if (this != &boid)
        {
            const auto &otherPosition = boid.getPosition();

            const auto &distanceVector = otherPosition - myPosition;
            float squaredDistance = ((distanceVector.x) * (distanceVector.x) + (distanceVector.y) * (distanceVector.y));

            if (squaredDistance < 400)
            {
                acceleration = acceleration - (boid.getPosition() - this->getPosition());
            }
        }
    }
    return acceleration * 1.5f;
}

sf::Vector2f Boid::Coh(const std::vector<Boid> &boids, const sf::Vector2f &sumOfPosition)
{
    const auto &myPosition = this->getPosition();
    auto cg = (sumOfPosition - myPosition);
    cg.x /= (boids.size() - 1);
    cg.y /= (boids.size() - 1);

    auto acceleration = (cg - this->getPosition());
    acceleration.x /= 100;
    acceleration.y /= 100;
    return acceleration * 0.2f;
}

sf::Vector2f Boid::Ali(const std::vector<Boid> &boids, const sf::Vector2f &sumOfVelocities)
{
    const auto &myVelocity = this->GetVelocity();

    auto cg = (sumOfVelocities - myVelocity);
    cg.x /= (boids.size() - 1);
    cg.y /= (boids.size() - 1);

    auto acceleration = (cg - this->GetVelocity());
    acceleration.x /= 50;
    acceleration.y /= 50;
    return acceleration * 0.1f;
}
