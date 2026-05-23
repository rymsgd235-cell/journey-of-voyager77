#pragma once
#include "raylib.h"

class ResourceManager {
public:
    Texture2D coded[26];
    Texture2D nonCoded[26];
    Texture2D sky;  //parachute image
    Texture2D finalGameBg; // Background for final game 1 (Sound Code)
    Texture2D finalGame2Bg; // Background for final game 2 (Light Code)
    Texture2D finalGame2BgOn; // Background for final game 2 with light on
    Texture2D bgGeneral; // Background for progress, level select, minigame menu, study mode
    Texture2D bgDefuse; // Background for defuse protocol minigame
    Texture2D bgTimeAttack; // Background for time attack minigame
    Texture2D bgParachute; // Background for parachute drop and test mode
    Font font;
    Sound sndDot;
    Sound sndDash;
    Sound sndSuccess;
    Sound sndExplosion;
    Music bgMusic;

    void LoadAll();
    void UnloadAll();
};

