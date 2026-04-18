# Boids-SFML Documentation

Welcome to the documentation for the Boids-SFML project! This repository implements Craig Reynolds' flocking algorithm using C++ and the Simple and Fast Multimedia Library (SFML).

## Table of Contents

- [Architecture Overview](architecture.md)
- [Boids Algorithm Details](algorithm.md)

## Building the Project

This project uses CMake. You can build it by pulling down the repository and using the standard CMake workflow:

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

Make sure you've properly checked out any submodules if SFML is included natively via `vendors/`.
