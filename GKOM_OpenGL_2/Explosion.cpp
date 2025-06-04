#include "Explosion.h"

bool Explosion::togglePause()
{
    return paused = !paused;
}

void Explosion::updateTime(float deltaTime) {
    if (!paused) {
        explosionTime += deltaTime * simulationSpeed;
    }
}