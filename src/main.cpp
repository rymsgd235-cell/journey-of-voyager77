#include "raylib.h"
#include "GameEngine.h"


int main() {
    
    // 1. Raylib Setup
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "MORSE Master");
    SetExitKey(KEY_NULL); // Disable ESC to close window
    InitAudioDevice();
    SetTargetFPS(60);
    // 2. Initialize Engine
    GameEngine engine;
    engine.Init();

    // 3. Main Loop
    while (!WindowShouldClose())
    {
         // Toggle fullscreen with F11 key
    if (IsKeyPressed(KEY_F11))
        ToggleFullscreen();
    
        engine.Update();
        engine.Draw();
    }

    // 4. closing
    engine.Unload();
    CloseAudioDevice();
    CloseWindow();

    return 0;
}