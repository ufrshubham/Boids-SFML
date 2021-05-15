#pragma once

#include <vector>

#include "Boid.h"

#include "SFML/System/Time.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderStates.hpp"

// Brief description of Flock Class:
// This file contains the class needed to create a flock of boids. It utilizes
// the boids class and initializes boid flocks with parameters that can be
// specified. This class will be utilized in main.

class Flock : public sf::Drawable
{
public:
    Flock(float windowWidth, float windowHeight);

    void Update(const sf::Time &dt);
    void CreateBoidAt(float x, float y);

public:
    std::vector<Boid> m_boids;

    // Accessor functions
    int getSize();
    Boid getBoid(int i);
    // Mutator Functions
    void addBoid(const Boid &b);

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    float m_windowWidth;
    float m_windowHeight;
};
