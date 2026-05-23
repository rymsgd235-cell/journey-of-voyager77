#include "ResourceManager.h"

void ResourceManager::LoadAll() {
    for (int i = 0; i < 26; i++) {
        char ltr = 'A' + i;
        coded[i] = LoadTexture(TextFormat("data/letters/coded/%c.png", ltr));
        SetTextureFilter(coded[i], TEXTURE_FILTER_BILINEAR);
        nonCoded[i] = LoadTexture(TextFormat("data/letters/non_coded/%c.png", ltr));
        SetTextureFilter(nonCoded[i], TEXTURE_FILTER_BILINEAR);
    }
    sky = LoadTexture("data/sky.png");
    finalGameBg = LoadTexture("data/back/Sound Code.png");
    finalGame2Bg = LoadTexture("data/back/Light Code.png");
    finalGame2BgOn = LoadTexture("data/back/Light Code on.png");
    bgGeneral = LoadTexture("data/back/general.png");
    bgDefuse = LoadTexture("data/back/Diffuse protocol.png");
    bgTimeAttack = LoadTexture("data/back/Time attack.png");
    bgParachute = LoadTexture("data/back/Parachute drop.png");
    font = LoadFontEx("data/font.ttf", 96, 0, 0); 
    SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);

    // Load explosion sound
    sndExplosion = LoadSound("data/explosion.mp3");

    // Load background music
    bgMusic = LoadMusicStream("data/Project IGI - menu.mp3");
    SetMusicVolume(bgMusic, 1.f);

}

void ResourceManager::UnloadAll() {
    for (int i = 0; i < 26; i++) {
        UnloadTexture(coded[i]);
        UnloadTexture(nonCoded[i]);
    }
    UnloadTexture(sky);
    UnloadTexture(finalGameBg);
    UnloadTexture(finalGame2Bg);
    UnloadTexture(finalGame2BgOn);
    UnloadTexture(bgGeneral);
    UnloadTexture(bgDefuse);
    UnloadTexture(bgTimeAttack);
    UnloadTexture(bgParachute);
    UnloadFont(font);
    UnloadSound(sndDot);
    UnloadSound(sndDash);
    UnloadSound(sndSuccess);
    UnloadSound(sndExplosion);
    UnloadMusicStream(bgMusic);
}
