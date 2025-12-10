#pragma once
#include "Statuses.h"      // требуется: тип Statuses доступен
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


	void setHp(int h) { hp = h; }
	void setArm(int arm) { armor = arm; }
	void setMana(int m) { mana = m; }


	void getAttacked(int dmg);
	void applyPhysicalDamageToArmor(int dmg);


	std::vector<std::shared_ptr<Card>>& getHand() { return player_hand; }
	std::vector<std::shared_ptr<Card>>& getDeck() { return player_deck; }
	void addCardToDeck(std::shared_ptr<Card> card) { player_deck.push_back(card); }
	void drawCard();

	void startTurn();
	void printCharacterStatus(const Character& character, const std::string& name)
	{
		std::cout << "-------------------------\n";
		std::cout << name << " - HP: " << character.getHealth() << ", Armor: " << character.getArmor() << ", Mana: " << character.getMana() << std::endl;
		character.getStatuses().showStatuses();// char->getStatuses() - возврат ссылки на объект статусов -> status.showStatuses() - вывод статусов
	}

	Statuses& getStatuses() { return status; }//возврат ссылки на объект статусов
	const Statuses& getStatuses() const { return status; }
};
