#pragma once

#include "Global.h"
#include "ResourceManager.h"
#include "PlayerManager.h"
#include "Synthesizer.h"
#include "EffectsManager.h"
#include <map>
#include <algorithm>
#include <random>

class GameEngine {
private:
    ResourceManager res;
    PlayerManager player;
    EffectsManager fx;
    
    GameState state = LOGIN_SCREEN;
    std::map<char, std::string> morseTable;
    std::string currentInput = "";
    char loginInput[20] = "";
    bool showSignupPrompt = false;
        
    // Pause Menu Variables

    bool isPaused = false;
    int pauseMenuSelection = 0; // 0 = Continue, 1 = Return to Menu
    GameState stateBeforePause = LOGIN_SCREEN;
    
    // Progress Screen Variables
    int progressScreenSelection = 0; // 0 = Continue, 1 = Level Select, 2 = Minigames
    int bottomButtonSelection = -1; // -1 = none, 0 = Switch User, 1 = About, 2 = Credits
    int levelSelectIndex = 0; // For level selection screen
    int minigameMenuSelection = 0; // For minigame menu selection (0=Time Attack, 1=Defuse Protocol)
    
    // Time Attack Configuration
    int timeAttackDurationSelection = 0; // 0=30s, 1=60s, 2=90s
    int timeAttackModeSelection = 0; // 0=Letter→Morse, 1=Morse→Letter
    int timeAttackConfigStep = 0; // 0=duration, 1=mode, 2=ready
    
    // Defuse Protocol Configuration
    int defuseModeSelection = 0; // 0=Morse→Letter, 1=Letter→Morse
    int defuseConfigStep = 0; // 0=mode selection
    
    // Parachute Drop Configuration
    int parachuteModeSelection = 0; // 0=Letter→Morse, 1=Morse→Letter
    int parachuteConfigStep = 0; // 0=mode selection
    
    // Minigame Gate
    int minigameGateSelection = 0; // 0=Time Attack, 1=Defuse Protocol, 2=Proceed (when unlocked)
    int minigameGateReverseSelection = 0; // For reverse gate (morse→letter mode)
    GameState minigameLaunchedFrom = MINIGAME_MENU; // Track where minigame was launched from
    
    float keyPressTime = 0.0f;
    bool isKeyPressed = false;
    float bounceTimer = 0.0f;
    int wrongAttempts = 0;
    std::vector<char> levelSequence;
    
    // Stage Test Variables
    std::vector<int> stageTestQueue; // Keeps track of how many words to spawn
    int stageTestCurrentIdx = 0;
    bool isStageCleared = false;
    FallingWord activeFallingWord = { "", 0, {0,0}, 0, false };
    int stageTestFailures = 0;
    int currentStageStartIdx = 0;
    bool lastMiniGameFailed = false; // set when a mini-game (e.g. Defuse) fails
    
    // Reverse Level Variables
    bool isReverseMode = false;
    
    // Temporary level tracking (for replaying levels without resetting progress)
    int tempLevelIdx = -1; // -1 means use actual progress
    int tempReverseLevelIdx = -1;

    std::vector<std::string> wordDictionary;
    std::string GetRandomWordForLevel(int maxIndex);

    // Mini-Game Variables
    MiniGameData activeMiniGame;
    int miniGameCounter = 0;
    
    void StartMiniGame(MiniGameType type);
    // Draw helper: center text horizontally by measured width
    void DrawTextCentered(const std::string &txt, float y, float fontSize, int spacing, Color color);
    void UpdatePauseMenu();
    void DrawPauseMenu();

public:
    void Init();
    void Update();
    void UpdateLogin();
    void UpdateProgressScreen();
    void UpdateLevelSelect();
    void UpdateMinigameMenu();
    void UpdateMinigameGate();
    void UpdateMinigameGateReverse();
    void UpdateStudy();
    void UpdateTest();
    void UpdateLevelUp();
    void UpdateStageTest();
    void UpdateMiniGame();
    void UpdateReverseStudy();
    void UpdateReverseTest();
    void UpdateReverseLevelUp();
    void UpdateReverseStageTest();
    void UpdateFinalGame1();
    void UpdateFinalGame2();
    void UpdateAboutScreen();
    void UpdateCreditsScreen();
    
    int currentMiniGameIdx = 0;
    bool isMusicMuted = false;
    int currentIdx = 0;
    // int currentreverseIdx = 0;

    void Draw();
    void DrawLoginGUI();
    void DrawProgressScreenGUI();
    void DrawLevelSelectGUI();
    void DrawMinigameMenuGUI();
    void DrawMinigameGateGUI();
    void DrawMinigameGateReverseGUI();
    void DrawAboutScreenGUI();
    void DrawCreditsScreenGUI();
    void DrawStudyGUI(Vector2 offset);
    void DrawTestGUI(Vector2 offset);
    void DrawLevelUpGUI();
    void DrawStageTestGUI(Vector2 offset);
    void DrawMiniGame();
    void DrawReverseStudyGUI(Vector2 offset);
    void DrawReverseTestGUI(Vector2 offset);
    void DrawReverseLevelUpGUI();
    void DrawReverseStageTestGUI(Vector2 offset);
    void DrawFinalGame1GUI();
    void DrawFinalGame2GUI();
    void Unload();
};

