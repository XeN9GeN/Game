#pragma once
#include <vector>
#include <memory>
#include "Character.h"
#include <string>
#include "Statuses.h"

class Card;

class Enemy : public Character {
	std::string	name;
public:
	Enemy(std::string name, int health, int armor, int mana);
	void autoEnemyTurn(Character& player);
};

