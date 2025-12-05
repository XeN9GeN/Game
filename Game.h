#pragma once
#include <string>
#include "Character.h"
#include "Enemy.h"

class Game {
private:
    Character player;
    Enemy enemy;
public:
	Game(Character p, Enemy e) : player(p), enemy(e) {}
    Game();
    void playerTurn();
    void enemyTurn();
    void startBattle();
    void autoPlayerTurn();
};

