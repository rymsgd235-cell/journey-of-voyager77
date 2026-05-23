#pragma once

#include "Global.h"
#include <vector>

class EffectsManager {
private:
    std::vector<Particle> particles;
    float shakeIntensity = 0.0f;

public:
    void Explode(Vector2 position, Color color);
    void UpdateAndDraw();
    float GetShake();
};

