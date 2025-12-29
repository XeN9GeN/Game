#pragma once
#include <string>
#include <iostream>
#include "Colors.h"
#include "Character.h"

enum class CardType {
	Attack,
	Defense,
	Heal,
	Buff,
	Debuff
};
enum class StatusType {
	Poison,
	Bleed,
	Weak,
	Vulnerable,
	Fragile,

	Strength,
	Regeneration,
	Haste,
	Dexterity
};


class Card
{
protected: 
	std::string name; //1-й
	std::string effect_d; //2-й
	int mana_cost; //3-q
	CardType type; //4-й
	Card(std::string n, std::string e_d, int m_c, CardType t) : name(n), effect_d(e_d), mana_cost(m_c), type(t) {}

public:

	virtual ~Card() = default;
	virtual void apply(Character& self, Character& target) = 0;
	virtual void printCard() = 0;
	virtual void printShort() const {
		std::cout << effect_d;
	}

	const std::string& getName() const { return name; }
	const std::string& getEffectDescription() const { return effect_d; }
	int getManaCost() const { return mana_cost; }
	CardType getType() const { return type; }
};



class Attack_card : public Card {
	int dmg;
public:
	
	Attack_card(std::string n, std::string e_d, int m_c, int type_value) : Card(n, e_d, m_c, CardType::Attack), dmg(type_value) {}
	void apply(Character& self, Character& target) override; 
	void printCard() override;
};


class Defense_card : public Card {
	int armor;
public:
	Defense_card(std::string n, std::string e_d, int m_c, int type_value) : Card(n, e_d, m_c, CardType::Defense), armor(type_value) {}
	void apply(Character& self, Character& target) override;
	void printCard() override;
};


class Heal_card : public Card {
	int heal_amount;
public:
	Heal_card(std::string n, std::string e_d, int m_c, int type_value) : Card(n, e_d, m_c, CardType::Heal), heal_amount(type_value) {}
	void apply(Character& self, Character& target) override;
	void printCard() override;
};




class Buff_card : public Card {
protected:
	StatusType statusType;
	int value;
	int duration;
public:
	Buff_card(std::string n, std::string e_d, int m_c, StatusType st, int val, int dur) :
		//CardType::Debuff не является параметром конструктора, поэтому передаем его явно, ибо в enum class фиксируется конкретный тип карты
		Card(n, e_d, m_c, CardType::Buff), //конструктор базового класса на первые 3 параметра
		statusType(st), // 4-й
		value(val), // 5-й
		duration(dur) {
	}
	void apply(Character& self, Character& target) override = 0;
	void printCard() override = 0;
};


class Strength_card : public Buff_card {
public:
	Strength_card(std::string n, std::string e_d, int m_c, int val, int dur) : Buff_card(n,e_d,m_c, StatusType::Strength, val,dur){}

	void apply(Character& self, Character& target) override;
	void printCard()override;
};

class Regeneration_card : public Buff_card {
public:
	Regeneration_card(std::string n, std::string e_d, int m_c, int val, int dur) : Buff_card(n, e_d, m_c, StatusType::Regeneration, val, dur) {}

	void apply(Character& self, Character& target) override;
	void printCard()override;
};

class Haste_card : public Buff_card {
public:
	Haste_card(std::string n, std::string e_d, int m_c, int val, int dur) : Buff_card(n, e_d, m_c, StatusType::Haste, val, dur) {}

	void apply(Character& self, Character& target) override;
	void printCard()override;
};

class Dexterity_card : public Buff_card {
public:
	Dexterity_card(std::string n, std::string e_d, int m_c, int val, int dur) : Buff_card(n, e_d, m_c, StatusType::Dexterity,val,dur) {}

	void apply(Character& self, Character& target) override;
	void printCard()override;
};



//ЧИСТО ВИРТУАЛЬНЫЙ КЛАСС, ЕГО НЕЛЬЗЯ СОЗДАТЬ С ПОМОЩЬЮ MAKE_SHARED
class Debuff_card : public Card {
protected:
	StatusType statusType;
	int value; // значение эффекта   5-й
	int duration; // длительность эффекта   6-й

public:
	Debuff_card(std::string n, std::string e_d, int m_c, StatusType st, int val, int dur) :
		//CardType::Debuff не является параметром конструктора, поэтому передаем его явно, ибо в enum class фиксируется конкретный тип карты
		Card(n, e_d, m_c, CardType::Debuff), //конструктор базового класса на первые 3 параметра
		statusType(st), // 4-й
		value(val), // 5-й
		duration(dur) {} //6-й

	virtual void apply(Character& self, Character& target) override = 0;
	virtual void printCard() override = 0;
};


//НАСЛЕДНИКИ DEBUFF
class Poison_card : public Debuff_card {
public:
	Poison_card(std::string n, std::string e_d, int m_c, int val, int dur) : Debuff_card(n, e_d, m_c,StatusType::Poison, val,dur) {}

	void apply(Character& self, Character& target) override;
	void printCard()override;
};
class Bleed_card: public Debuff_card{
public:
	Bleed_card(std::string n, std::string e_d, int m_c, int val, int dur) : Debuff_card(n, e_d, m_c, StatusType::Bleed, val, dur) {}

	void apply(Character& self, Character& target) override;
	void printCard() override;
};
class Weak_card : public Debuff_card {
public:
	Weak_card(std::string n, std::string e_d, int m_c, int val, int dur) : Debuff_card(n, e_d, m_c, StatusType::Weak, val, dur) {}
	
	void apply(Character& self, Character& target) override;
	void printCard() override;
};
class Vulnerable_card : public Debuff_card {
public:
	Vulnerable_card(std::string n, std::string e_d, int m_c, int val, int dur) : Debuff_card(n, e_d, m_c, StatusType::Vulnerable, val, dur) {}

	void apply(Character& self, Character& target) override;
	void printCard() override;
};
class Fragile_card : public Debuff_card {
public:
	Fragile_card(std::string n, std::string e_d, int m_c, int val, int dur) : Debuff_card(n, e_d, m_c, StatusType::Fragile, val, dur) {}

	void apply(Character& self, Character& target) override;
	void printCard() override;
};