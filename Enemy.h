#pragma once
#include "Character.h"
#include <string>

class Card;

class Enemy : public Character {
	std::string	name;
public:
	Enemy(std::string name, int health, int armor, int mana);
	void autoEnemyTurn(Character& player);
};

