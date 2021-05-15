#pragma once

#include <vector>

#include "Boid.h"

#include "SFML/System/Time.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderStates.hpp"

class Flock : public sf::Drawable
{
public:
    Flock(float windowWidth, float windowHeight);

    void Update(const sf::Time &dt);
    void CreateBoidAt(float x, float y);

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::vector<Boid> m_boids;
    float m_windowWidth;
    float m_windowHeight;
};
