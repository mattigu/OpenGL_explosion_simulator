#include "Explosion.h"

#include <algorithm>


bool Explosion::togglePause()
{
    return paused = !paused;
}

void Explosion::updateTime(float deltaTime) {
    if (!paused) {
        explosionTime = std::max(0.0f, explosionTime + deltaTime * simulationSpeed);
    }
}