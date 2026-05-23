#include "PlayerManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

void PlayerManager::LoadDatabase() 
{
    userDatabase.clear();
    std::ifstream file("users.dat");
    if (file) {
        std::string line;
        while (std::getline(file, line)) 
        {
            if (line.empty()) continue;
            
            UserData temp;
            std::stringstream ss(line);
            std::string name, rankTitle;
            
            // Read all fields separated by tabs
            std::getline(ss, name, '\t');
            strncpy(temp.name, name.c_str(), sizeof(temp.name) - 1);
            temp.name[sizeof(temp.name) - 1] = '\0';
            
            ss >> temp.currentLetterIdx;
            ss.ignore(); // Skip tab
            ss >> temp.xp;
            ss.ignore();
            
            std::getline(ss, rankTitle, '\t');
            strncpy(temp.rankTitle, rankTitle.c_str(), sizeof(temp.rankTitle) - 1);
            temp.rankTitle[sizeof(temp.rankTitle) - 1] = '\0';
            
            ss >> temp.timeAttackBest;
            ss.ignore();
            ss >> temp.defusePassed;
            ss.ignore();
            ss >> temp.timeAttackBestReverse;
            ss.ignore();
            ss >> temp.defusePassedReverse;
            ss.ignore();
            ss >> temp.reverseLevelIdx;
            ss.ignore();
            ss >> temp.finalLevelsCompleted;
            
            userDatabase.push_back(temp);
        }
        file.close();
    }
}

void PlayerManager::SaveDatabase() {
    std::ofstream file("users.dat");
    for (const auto& user : userDatabase) {
        file << user.name << '\t'
             << user.currentLetterIdx << '\t'
             << user.xp << '\t'
             << user.rankTitle << '\t'
             << user.timeAttackBest << '\t'
             << (user.defusePassed ? 1 : 0) << '\t'
             << user.timeAttackBestReverse << '\t'
             << (user.defusePassedReverse ? 1 : 0) << '\t'
             << user.reverseLevelIdx << '\t'
             << user.finalLevelsCompleted << '\n';
    }
    file.close();
}

std::string PlayerManager::GetRankTitle(int level) {
    // Level ranges: 0-25 (Letter→Morse), 26-27 (Mini-games), 28-53 (Morse→Letter), 54-55 (Reverse Mini-games), 56-57 (Final)
    if (level >= 58) return "★ THE CONDUIT ★";        // Completed everything
    if (level >= 56) return "FINAL PROTOCOL";          // Final levels (56-57)
    if (level >= 54) return "REVERSE SPECIALIST";      // Completed reverse mini-games (54-55)
    if (level >= 48) return "DUAL MASTER";             // Advanced morse→letter (48-53)
    if (level >= 40) return "MIRROR OPERATIVE";        // Mid morse→letter (40-47)
    if (level >= 32) return "REVERSE DECODER";         // Early morse→letter (32-39)
    if (level >= 28) return "CIPHER INVERTER";         // Started morse→letter (28-31)
    if (level >= 26) return "GATEKEEPER";              // Passed mini-games (26-27)
    if (level >= 22) return "SIGNAL MASTER";           // Advanced letter→morse (22-25)
    if (level >= 18) return "CODE SPECIALIST";         // Upper-mid letter→morse (18-21)
    if (level >= 14) return "CIPHER TECH";             // Mid letter→morse (14-17)
    if (level >= 10) return "MORSE OPERATOR";          // Lower-mid letter→morse (10-13)
    if (level >= 6)  return "RADIO APPRENTICE";        // Early letter→morse (6-9)
    if (level >= 3)  return "SIGNAL TRAINEE";          // Beginner letter→morse (3-5)
    return "SIGNAL CADET";                             // Starting out (0-2)
}

LoginStatus PlayerManager::AttemptLogin(const char* name) {
    LoadDatabase(); // Refresh from disk
    
    for (const auto& user : userDatabase) {
        if (strcmp(user.name, name) == 0) {
            activeUser = user;
            return LOGIN_SUCCESS;
        }
    }
    return LOGIN_NOT_FOUND;
}

void PlayerManager::CreateUser(const char* name) {
    strncpy(activeUser.name, name, sizeof(activeUser.name) - 1);
    activeUser.name[sizeof(activeUser.name) - 1] = '\0';
    activeUser.currentLetterIdx = 0;
    activeUser.xp = 0;
    activeUser.timeAttackBest = 0.0f;
    activeUser.defusePassed = false;
    activeUser.timeAttackBestReverse = 0.0f;
    activeUser.defusePassedReverse = false;
    activeUser.reverseLevelIdx = 0;
    activeUser.finalLevelsCompleted = 0;
    std::string rank = GetRankTitle(0); // Pass level 0
    strcpy(activeUser.rankTitle, rank.c_str());
    
    userDatabase.push_back(activeUser);
    SaveDatabase();
}

void PlayerManager::SaveProgress() {
    // Calculate overall level and update rank
    int actualLevel = GetOverallLevel();
    
    // Update active user in local database vector
    bool found = false;
    std::string rank = GetRankTitle(actualLevel);
    strcpy(activeUser.rankTitle, rank.c_str());

    for (auto& user : userDatabase) {
        if (strcmp(user.name, activeUser.name) == 0) {
            user = activeUser;
            found = true;
            break;
        }
    }
    
    if (!found) userDatabase.push_back(activeUser);
    
    SaveDatabase();
}

void PlayerManager::AddXP(int amount) {
    activeUser.xp += amount;
    SaveProgress();
}

int PlayerManager::GetOverallLevel() {
    // Calculate actual level (0-57) from game progress
    // Level breakdown:
    // 0-25:  Letter→Morse (currentLetterIdx 0-25)
    // 26-27: Mini-games (defusePassed, timeAttackBest > 0)
    // 28-53: Morse→Letter (reverseLevelIdx 0-25)
    // 54-55: Reverse mini-games (defusePassedReverse, timeAttackBestReverse > 0)
    // 56-57: Final levels (finalLevelsCompleted)
    
    int level = activeUser.currentLetterIdx;
    
    // Add mini-game completion levels (26-27)
    if (activeUser.currentLetterIdx >= 26) {
        if (activeUser.defusePassed) level++; // Level 26
        if (activeUser.timeAttackBest > 30) level++; // Level 27
        
        // Add reverse letter levels (28-53)
        if (level >= 28 || activeUser.reverseLevelIdx > 0) 
        {
            level = 28 + activeUser.reverseLevelIdx;
            
            // Add reverse mini-game completion (54-55)
            if (activeUser.reverseLevelIdx >= 26) {
                if (activeUser.defusePassedReverse) level++; // Level 54
                if (activeUser.timeAttackBestReverse > 20) level++; // Level 55
                
                // Add final levels (56-57)
                if (level >= 56 || activeUser.finalLevelsCompleted > 0) 
                    level = 56 + activeUser.finalLevelsCompleted;
                
            }
        }
    }
    
    return level;
}
