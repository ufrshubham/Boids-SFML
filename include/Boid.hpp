#pragma once

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
    void Borders(const float &w_width, const float &w_height, bool wrap);

    sf::Vector2f Sep(const std::vector<Boid> &boids);
    sf::Vector2f Coh(const std::vector<Boid> &boids, const sf::Vector2f &sumOfPosition);
    sf::Vector2f Ali(const std::vector<Boid> &boids, const sf::Vector2f &sumOfVelocities);

private:
    sf::Vector2f m_velocity;
    const float m_speedLimit = 400.f;
    static const sf::Color s_boidColor;
};
