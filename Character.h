#pragma once
#include "Statuses.h"
#include <memory>
#include <vector>
#include <string>

class Card;

class Character
{
private:
	int hp;
	int armor;
	int mana;

	std::vector<std::shared_ptr<Card>> player_deck;
	std::vector<std::shared_ptr<Card>> player_hand;

	Statuses status;

public:
	Character(int h, int arm, int mana) : hp(h), armor(arm),mana(mana) {}
	Character() : hp(30), armor(0), mana(0) {}

	int getHealth() const { return hp; }
	int getArmor() const { return armor; }
	int getMana() const { return mana; }
	

	void setHp(int h) { 
		//Проверка на макс hp
		if (h > 30) {
			h = 30;
			std::cout << Color::BLUE << "Health capped at maximum (" << 30 << ")" << Color::RESET << "\n";
			return;
		}
		else {
			hp = h;
		}
	}
	void setArm(int arm) {
		//Проверка на - армор
		if (arm < 0) {
			armor = 0;
			std::cout << Color::YELLOW << "Armor cannot be negative! Set to 0." << Color::RESET << "\n";
			return;
		}
		else {
			armor = arm;
		}
	
	}
	void setMana(int m) {
		//Проверка на - ману
		if (m < 0) {
			mana = 0;
			std::cout << Color::BLUE << "Mana cannot be negative! Set to 0." << Color::RESET << "\n";
			return;
		}
		else {
			mana = m;
		}
	}
	int getEffectiveCardCost(const Card& card) const;


	void getAttacked(int dmg);
	void applyPhysicalDamageToArmor(int dmg);


	std::vector<std::shared_ptr<Card>>& getHand() { return player_hand; }
	std::vector<std::shared_ptr<Card>>& getDeck() { return player_deck; }
	const std::vector<std::shared_ptr<Card>>& getHand() const { return player_hand; }
	const std::vector<std::shared_ptr<Card>>& getDeck() const { return player_deck; }
	
	void addCardToDeck(std::shared_ptr<Card> card) { player_deck.push_back(card); }
	void drawCard();

	void takesPeriodDmgAtStartTurn();
	void printCharacterStatus(const Character& character, const std::string& name)
	{
		std::cout << "-------------------------\n";
		std::cout << name << " - HP: " << character.getHealth() << ", Armor: " << character.getArmor() << ", Mana: " << character.getMana() << std::endl;
		character.getStatuses().showStatuses();// вывод активных статусов персонажа
	}

	Statuses& getStatuses() { return status; } // возвращает ссылку на статусы персонажа
	const Statuses& getStatuses() const { return status; }
};
