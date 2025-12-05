#pragma once
#include <vector>
#include <string>
#include <memory>

class Card;


struct Statuses {
	int poison = 0;     // наносит урон в начале хода, обходя броню
	int bleed = 0;      // наносит урон в начале хода, учитывая броню
	int weak = 0;       // уменьшает урон атакующего на 25%
	int vulnerable = 0; // увеличивает входящий урон на 50%
	int fragile = 0;    // уменьшает эффективность брони (напр. броня дает вдвое меньше защиты)
};


class Character
{
private:
	int hp;
	int armor;
	int mana;
	Statuses status;

	std::vector<std::shared_ptr<Card>> player_deck;
	std::vector<std::shared_ptr<Card>> player_hand;

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


	void addPoison(int value) { status.poison += value; }
	void addBleed(int value) { status.bleed += value; }
	void addWeak(int turns) { status.weak += turns; }
	void addVulnerable(int turns) { status.vulnerable += turns; }
	void addFragile(int turns) { status.fragile += turns; }
	void showStatuses() const;


	std::vector<std::shared_ptr<Card>>& getAllCards() { return player_hand; }
	void addCard(std::shared_ptr<Card>card) { player_hand.push_back(card); }
	std::vector<std::shared_ptr<Card>>& getDeck() { return player_deck; }
	void addCardToDeck(std::shared_ptr<Card> card) { player_deck.push_back(card); }



	void startTurn();
	void endTurn();


	Statuses getStatuses() const { return status; }
};

