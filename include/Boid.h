#pragma once

#include "Pvector.h"
#include "Boid.h"

#include <vector>

#include "SFML/System/Time.hpp"
#include "SFML/Graphics/CircleShape.hpp"

class Boid : public sf::CircleShape
{
public:
    Boid();
    Boid(float x, float y);

    void Update(const sf::Time &dt);

    const sf::Vector2f &GetVelocity() const;
    void SetVelocity(const sf::Vector2f &velocity);
    void Accelerate(const sf::Vector2f &velocity);
    void Borders(const float &w_width, const float &w_height);

    void Sep(const std::vector<Boid> boids);
    void Coh(const std::vector<Boid> boids, const sf::Vector2f &sumOfPosition);
    void Ali(const std::vector<Boid> boids, const sf::Vector2f &sumOfVelocities);

private:
    sf::Vector2f m_velocity;
    const float speedLimit = 400.f;
};
