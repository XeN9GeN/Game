#pragma once
#include "Character.h"
#include "Enemy.h"
#include "Card.h"
#include <fstream>
#include <sstream>
#include <memory>
#include <string>

class DeckLoader {
public:
    // Загружает колоду игрока из файла
    static bool loadPlayerDeck(Character& player, const std::string& filename);


    // Создает карту из строки описания
    static std::shared_ptr<Card> createCardFromString(const std::string& line);

};