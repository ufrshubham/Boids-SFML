# The Boids Algorithm

Originally developed by Craig Reynolds in 1986, the Boids model is an artificial life program, simulating the flocking behavior of birds.

The simulation revolves around three simple rules applied to individual Boids:

## 1. Separation (Avoidance)
Boids steer to avoid crowding local flockmates. 
In the codebase, this is handled by checking a local visual threshold (e.g., squared distances below a fixed bound). For any close neighboring boids, a repulsive force scaling inversely with distance acts as acceleration pushing the boid away. See `Boid::Sep()`.

## 2. Alignment (Copying)
Boids steer towards the average heading of local flockmates. 
In our application, `Boid::Ali()` calculates the center velocity (`sumOfVelocities`) excluding the Boid itself, then generates an acceleration force dragging the individual Boid's local velocity towards that average direction vector.

## 3. Cohesion (Centering)
Boids steer to move towards the average position (center of mass) of local flockmates.
`Boid::Coh()` pulls the position sum of the flock and derives a point of attraction. The individual Boid adjusts its velocity linearly towards this center of mass to act as a glued swarming entity.

## Simulation Physics & Bounding
Boids update their position with Simple Euler Integration natively over time (`p = p + v * dt`). Furthermore, artificial borders are constructed utilizing coordinate clamping to wrap/bounce boids properly enforcing visual continuity.
