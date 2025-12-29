#pragma once
#include <string>
#include <vector>
#include "Character.h"
#include "Enemy.h"

class Game {
private:
    Character &player;
    Enemy &enemy;
    std::vector<std::string> play_log; // логи хода 

public:
    Game(Character&p,Enemy&e);
    void PlayerTurn();
    void autoPlayerTurn();
    void clearPlayLog() { play_log.clear(); }

    void logPlay(const std::string& entry);
    void printPlayLog() const;

   
};

