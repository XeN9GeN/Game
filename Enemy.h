#pragma once
#include <vector>
#include <memory>
#include "Character.h"
class Card;

class Enemy : public Character {
	std::string	name;
	std::vector < std::shared_ptr<Card>> enemy_deck;
	std::vector < std::shared_ptr<Card>> hand;
public:
	Enemy(std::string name, int health, int armor, int mana);

	void drawCard();
	void addCardToDeck(std::shared_ptr<Card> card);
	void playTurn(Character&player);


};

