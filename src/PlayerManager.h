#pragma once

#include "Global.h"
#include <vector>
#include <string>

enum LoginStatus { 
    LOGIN_SUCCESS,
    LOGIN_NOT_FOUND 
};

class PlayerManager {
private:
    std::vector<UserData> userDatabase;
    std::string GetRankTitle(int level); // Changed from xp to level (0-57)

public:
    UserData activeUser;

    void LoadDatabase();
    void SaveDatabase();
    
    LoginStatus AttemptLogin(const char* name);
    void CreateUser(const char* name);
    void SaveProgress();
    void AddXP(int amount);
    int GetOverallLevel(); // Calculate overall level (0-57) from progress
    
    // Legacy support wrapper
    bool Login(const char* name) { return AttemptLogin(name) == LOGIN_SUCCESS; }
};

