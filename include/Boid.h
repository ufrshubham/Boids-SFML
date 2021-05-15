#pragma once

#include "Pvector.h"
#include "Boid.h"

#include <vector>

#include "SFML/System/Time.hpp"
#include "SFML/Graphics/CircleShape.hpp"

// The Boid Class
//
// Attributes
//  bool predator: flag that specifies whether a given boid is a predator.
//  Pvector location: Vector that specifies a boid's location.
//  Pvector velocity: Vector that specifies a boid's current velocity.
//  Pvector acceleration: Vector that specifies a boid's current acceleration.
//  float maxSpeed: Limits magnitude of velocity vector.
//  float maxForce: Limits magnitude of acceleration vector. (F = m*a!)
//
// Methods
//  applyForce(Pvector force): Adds the given vector to acceleration
//
//  Pvector Separation(vector<Boid> Boids): If any other boids are within a
//      given distance, Separation computes a a vector that distances the
//      current boid from the boids that are too close.
//
//  Pvector Alignment(vector<Boid> Boids): Computes a vector that causes the
//      velocity of the current boid to match that of boids that are nearby.
//
//  Pvector Cohesion(vector<Boid> Boids): Computes a vector that causes the
//      current boid to seek the center of mass of nearby boids.

class Boid : public sf::CircleShape
{
public:
    Boid();
    Boid(float x, float y);
    Boid(float x, float y, bool predCheck);

    void Update(const sf::Time &dt);

    void applyForce(const Pvector &force);
    
    // Three Laws that boids follow
    Pvector Separation(const std::vector<Boid> &Boids);
    Pvector Alignment(const std::vector<Boid> &Boids);
    Pvector Cohesion(const std::vector<Boid> &Boids);
    
    //Functions involving SFML and visualisation linking
    Pvector seek(const Pvector &v);

    void flock(const std::vector<Boid> &v);
    void borders(const float &w_width, const float &w_height);
    float angle(const Pvector &v);

private:
    bool predator;
    
    Pvector location;
    Pvector velocity;
    Pvector acceleration;
    
    float maxSpeed;
    float maxForce;
};
