# Application Architecture

The Boids-SFML project uses an object-oriented design comprised mainly of three classes: **Game**, **Flock**, and **Boid**.

## `Game` Class
The `Game` class encapsulates the SFML window, the main game loop, and handles I/O such as input events processing and rendering. 

* The `Run()` function maintains a fixed timestep loop to decouple physics from framerate natively.
* It handles input via `HandleInput()` and has pausing features, as well as enabling players to click and spawn individual boids via real-time inputs.

## `Flock` Class
The `Flock` class is the manager of the boids. It implements the `sf::Drawable` interface natively, allowing the `Game` to simply call `window.draw(flock)` to render all active boids efficiently.

* `Update(const sf::Time &dt)` queries sums of positions and velocities to provide parameters for localized rules to apply. 
* It's responsible for iterating and performing physical updates to the flock agents natively.

## `Boid` Class
The individual AI agent. It holds local transform states (handled natively inheriting `sf::CircleShape`) and physics vectors (velocity).
* Implement the core rules `Sep` (Separation), `Coh` (Cohesion), `Ali` (Alignment).
* Bound handling wrapped under `Borders` functionality ensures agents remain within space limits efficiently.
