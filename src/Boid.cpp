#include "Boid.h"

#include "SFML/Window/VideoMode.hpp"

#include <cstdlib>
#include <cmath>

#define PI 3.141592635

Boid::Boid() : CircleShape(8, 3)
{
    setPosition(0.f, 0.f);
    setOutlineColor(sf::Color(0, 255, 0));
    setFillColor(sf::Color::Green);
    setOutlineColor(sf::Color::White);
    setOutlineThickness(1);
    setRadius(3.f);
}

Boid::Boid(float x, float y)
    : CircleShape(8, 3), m_velocity(rand() % (int)x, rand() % (int)y)
{
    setPosition(x, y);
    setOutlineColor(sf::Color(0, 255, 0));
    setFillColor(sf::Color::Green);
    setOutlineColor(sf::Color::White);
    setOutlineThickness(1);
    setRadius(3.f);
}

void Boid::Update(const sf::Time &dt)
{
    const float magSquared = ((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
    if ((magSquared) > (speedLimit * speedLimit))
    {
        const auto mag = std::sqrt(magSquared);
        m_velocity.x /= mag;
        m_velocity.y /= mag;
    }

    move(m_velocity * dt.asSeconds());

    // Still need to check this math.
    float angle = (float)(std::atan2(m_velocity.x, -m_velocity.y) * 180 / PI);
    this->setRotation(angle);
}

// Checks if boids go out of the window and if so, wraps them around to
// the other side.
void Boid::Borders(const float &w_width, const float &w_height)
{
    const auto &position = this->getPosition();
    sf::Vector2f newPosition(position);
    if (position.x < 0)
    {
        newPosition.x += w_width;
    }
    if (position.y < 0)
    {
        newPosition.y += w_height;
    }
    if (position.x > w_width)
    {
        newPosition.x -= w_width;
    }
    if (position.y > w_height)
    {
        newPosition.y -= w_height;
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

void Boid::Sep(const std::vector<Boid> boids)
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
    Accelerate(acceleration);
}

void Boid::Coh(const std::vector<Boid> boids, const sf::Vector2f &sumOfPosition)
{
    const auto &myPosition = this->getPosition();
    auto cg = (sumOfPosition - myPosition);
    cg.x /= (boids.size() - 1);
    cg.y /= (boids.size() - 1);

    auto acceleration = (cg - this->getPosition());
    acceleration.x /= 100;
    acceleration.y /= 100;
    Accelerate(acceleration);
}

void Boid::Ali(const std::vector<Boid> boids, const sf::Vector2f &sumOfVelocities)
{
    const auto &myVelocity = this->GetVelocity();

    auto cg = (sumOfVelocities - myVelocity);
    cg.x /= (boids.size() - 1);
    cg.y /= (boids.size() - 1);

    auto acceleration = (cg - this->GetVelocity());
    acceleration.x /= 100;
    acceleration.y /= 100;
    Accelerate(acceleration);
}
