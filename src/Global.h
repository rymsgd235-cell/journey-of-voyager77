#pragma once

#include "raylib.h"
#include <string>
#include <vector>

// UI Colors (Neon/Cyberpunk theme for high engagement)
#define COLOR_BACKGROUND  (Color){ 15, 15, 25, 255 }
#define COLOR_ACCENT      (Color){ 0, 228, 255, 255 } // Cyan
#define COLOR_GOLD        (Color){ 255, 203, 0, 255 }
#define COLOR_SUCCESS     (Color){ 50, 255, 126, 255 }

enum GameState { 
      LOGIN_SCREEN,
      PROGRESS_SCREEN,
      LEVEL_SELECT, 
      STUDY_MODE, 
      TEST_MODE, 
      LEVEL_UP, 
      STAGE_TEST, 
      MINI_GAME, 
      REVERSE_STUDY, 
      REVERSE_TEST, 
      REVERSE_LEVEL_UP, 
      REVERSE_STAGE_TEST, 
      MINIGAME_MENU, 
      MINIGAME_GATE, 
      MINIGAME_GATE_REVERSE, 
      FINAL_GAME_1, 
      FINAL_GAME_2, 
      ABOUT_SCREEN, 
      CREDITS_SCREEN };

enum MiniGameType { 
    MINIGAME_NONE,
    MINIGAME_DEFUSE,
    MINIGAME_TIME_ATTACK,
    MINIGAME_PARACHUTE
};

struct MiniGameData {
    MiniGameType type;
    bool active;
    float timer;
    char targetLetter;
    std::string targetWord;
    int score;
    bool letterVisible;

    // Defuse Protocol
    float bombTimer;           // running timer for the mini-game
    float bombCountdown;       // seconds remaining before explosion
    float bombInitialCountdown; // initial countdown value for this round
    std::vector<char> defuseLetters; // letters to encode to defuse
    int defuseIndex;          // current target index in defuseLetters
    bool bombActive;          // whether the bomb is active
    int defuseRounds;         // total rounds in the session
    int defuseRoundIndex;     // current round (0-based)
    float roundPauseTimer;    // short pause between rounds
    float pendingSuccessTimer; // delay before playing success beep
    bool defuseUsesLetterInput; // when true, defuse shows morse and expects letter keys
    int defuseWrongAttempts;   // wrong letter attempts for current defuse target
    
    // Time Attack
    float timeAttackTimer;     // countdown timer for time attack
    float timeAttackDuration;  // duration of time attack (30, 60, or 90 seconds)
    int timeAttackScore;       // score during time attack
    std::string timeAttackInput; // current input for time attack
    char timeAttackTarget;     // current target letter for time attack
    bool timeAttackReverseMode; // true = morse→letter, false = letter→morse
    
    // Final Game 1: Beeps and Baaps
    int beepsPhase;            // 0 = letters, 1 = words
    int beepsRound;            // current round number
    int beepsCorrectCount;     // total correct answers
    std::string beepsUserInput; // user's answer
    bool beepsIsPlaying;       // true when playing morse code
    float beepsSoundTimer;     // timer for morse code playback
    int beepsSoundIndex;       // current index in morse code string
    float beepsDelay;          // delay before next sound
    char beepsTargetLetter;    // target letter for current round
    std::string beepsTargetWord; // target word for current round
    int beepsWrongAttempts;    // wrong attempts for current question
    bool beepsReady;           // user ready to hear next morse code
    bool beepsShowAnswer;      // show answer after 3 wrong attempts
    
    // Parachute Drop
    std::string parachuteWord; // current word to type
    int parachuteMatchIdx;     // current matching index
    Vector2 parachutePosition; // position of falling word
    float parachuteSpeed;      // fall speed
    bool parachuteActive;      // whether a word is falling
    int parachuteMissed;       // count of missed drops
    int parachuteScore;        // successful catches
    int parachuteTotalDrops;   // total drops spawned
    bool parachuteReverseMode; // true = morse→letter, false = letter→morse
    
    // Final Game 2: Light Code
    int lightCodePhase;        // 0 = letters (15), 1 = famous signals (5)
    char lightCodeTarget;      // target letter to show in morse light
    std::string lightCodeMorse; // morse code for current target
    std::string lightCodeTargetSignal; // target signal name for phase 1
    int lightCodeIndex;        // current position in morse string
    float lightCodeTimer;      // timer for light blink duration
    bool lightCodeOn;          // whether light is currently on
    float lightCodeDelay;      // delay between morse elements
    bool lightCodePlaying;     // whether morse is currently playing
    std::string lightCodeInput; // user's input
    int lightCodeRound;        // current round number
    int lightCodeCorrect;      // correct answers
    int lightCodeWrong;        // wrong attempts for current letter
    bool lightCodeReady;       // user ready to see next pattern
};

struct Particle {
    Vector2 position;
    Vector2 speed;
    float radius;
    float alpha;
    Color color;
};

struct UserData {
    char name[32];
    int currentLetterIdx; // 0 to 25
    int xp;
    char rankTitle[32]; // For persistent rank
    
    // Mini-games progress
    float timeAttackBest;      // best letters per minute in time attack
    bool defusePassed;         // passed defuse protocol
    float timeAttackBestReverse; // best LPM in reverse time attack
    bool defusePassedReverse;  // passed reverse defuse protocol
    
    // Reverse mode progress
    int reverseLevelIdx;       // progress in morse→letter levels (0-25)
    
    // Final levels
    int finalLevelsCompleted;  // 0-2 final levels completed
    
    // Save state
    int lastGameState;         // last game state for Continue feature
};

struct FallingWord {
    std::string word;
    int currentMatchIdx;
    Vector2 position;
    float speed;
    bool active;
};

