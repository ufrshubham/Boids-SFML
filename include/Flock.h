#pragma once

#include <vector>

#include "Boid.h"

// Brief description of Flock Class:
// This file contains the class needed to create a flock of boids. It utilizes
// the boids class and initializes boid flocks with parameters that can be
// specified. This class will be utilized in main.

class Flock
{
public:
    std::vector<Boid> flock;
    //Constructors
    Flock() {}
    // Accessor functions
    int getSize();
    Boid getBoid(int i);
    // Mutator Functions
    void addBoid(const Boid &b);
    void flocking();
};
