#pragma once
// Display.h
#pragma once
#include "Character.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

namespace Display {
    const int SIDE_WIDTH = 50;
    const int TOTAL_WIDTH = 155;
    const int COLUMN_WIDTH = 35;

    void printAsciiArt(const std::string& art, bool isLeft = true);
    void printCharacterStatus(const Character& character, const std::string& name, bool isLeft = true);
    void printBattleScreen(const Character& player, const Character& enemy);
    void printSimpleBattle(const Character& player, const Character& enemy, int turn);
}