#pragma once

#include "raylib.h"
#include <vector>
#include <cmath>
#include <cstdlib>

class Synthesizer {
public:
    // Generates a simple sine wave beep
    static Sound GenerateMorseSound(float duration, float frequency = 500.0f) 
    {
        int sampleRate = 44100;
        int frameCount = (int)(sampleRate * duration);
        
        // Allocate memory for samples
        float *samples = (float *)malloc(frameCount * sizeof(float));

        for (int i = 0; i < frameCount; i++) {
            // Basic sine wave: sin(2 * PI * freq * time)
            samples[i] = sinf(2.0f * PI * frequency * i / sampleRate);
            
            // Apply a tiny fade-out (envelope) to prevent "clicks" at the end
            if (i > frameCount - 1000) {
                float fade = (float)(frameCount - i) / 1000.0f;
                samples[i] *= fade;
            }
        }

        Wave wave = { (unsigned int)frameCount, (unsigned int)sampleRate, 32, 1, samples };

        Sound snd = LoadSoundFromWave(wave);
        UnloadWave(wave); // Free raw data, Sound keeps the hardware buffer
        return snd;
    }
};

