#include "EffectsManager.h"

void EffectsManager::Explode(Vector2 position, Color color) {
    for (int i = 0; i < 60; i++) {
        Particle p;
        p.position = position;
        p.speed = { (float)GetRandomValue(-500, 500) / 100.0f, (float)GetRandomValue(-500, 500) / 100.0f };
        p.radius = (float)GetRandomValue(2, 6);
        p.alpha = 1.0f;
        p.color = color;
        particles.push_back(p);
    }
    shakeIntensity = 10.0f; // Trigger screen shake
}

void EffectsManager::UpdateAndDraw() {
    // Handle Screen Shake logic for the camera later
    if (shakeIntensity > 0) shakeIntensity -= 0.5f;

    for (int i = particles.size() - 1; i >= 0; i--) {
        particles[i].position.x += particles[i].speed.x;
        particles[i].position.y += particles[i].speed.y;
        particles[i].alpha -= 0.02f;

        if (particles[i].alpha <= 0) {
            particles.erase(particles.begin() + i);
        } else {
            DrawCircleV(particles[i].position, particles[i].radius, Fade(particles[i].color, particles[i].alpha));
        }
    }
}

float EffectsManager::GetShake() 
{
     return shakeIntensity; 
}
