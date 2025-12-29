#include "Card.h"
#include "Character.h"
#include "Statuses.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>


using namespace std;



void Attack_card::apply(Character& self, Character& target) {
	target.getAttacked(dmg);
};
void Attack_card::printCard() {
	std::cout << Color::CARD_ATTACK << "[Attack][" << name << "]["
		<< effect_d << "][Cost:" << Color::BLUE << mana_cost << Color::CARD_ATTACK
		<< "][DMG:" << Color::RED << dmg << Color::CARD_ATTACK << "]" << Color::RESET << "\n";
};


void Defense_card::apply(Character& self, Character& target) {
	self.setArm(self.getArmor() + armor);
};
void Defense_card::printCard() {
	std::cout << Color::CARD_DEFENSE << "[Defense][" << name << "][" << effect_d
		<< "][Cost:" << Color::BLUE << mana_cost << Color::CARD_DEFENSE
		<< "][ARMOR:" << Color::YELLOW << armor << Color::CARD_DEFENSE << "]" << Color::RESET << "\n";
};


void Heal_card::apply(Character& self, Character& target) {
	self.setHp(self.getHealth() + heal_amount);
};
void Heal_card::printCard() {
	std::cout << Color::GREEN << "[Heal][" << name << "][" << effect_d
		<< "][Cost:" << Color::BLUE << mana_cost << Color::GREEN
		<< "][HEAL:" << heal_amount << "]" << Color::RESET << "\n";
};







void Strength_card::printCard() {
	std::cout << Color::CARD_BUFF << "[Buff][" << name << "]["
		<< effect_d << "][Cost:" << Color::BLUE << mana_cost << Color::CARD_BUFF << "]" << Color::RESET << "\n";
};
void Strength_card::apply(Character& self, Character& target) {
	self.getStatuses().addStrength(duration);
	std::cout << Color::GREEN << "Applied Strength: " << Color::RESET
		<< "Increases damage by 50% for " << duration << " turns.\n";
}

void Regeneration_card::printCard() {
	std::cout << Color::CARD_BUFF << "[Buff][" << name << "]["
		<< effect_d << "][Cost:" << Color::BLUE << mana_cost << Color::CARD_BUFF << "] "
		<< Color::GREEN << "(Heal " << value << " dmg)" << Color::RESET << "\n";
};
void Regeneration_card::apply(Character& self, Character& target) {
	self.getStatuses().addRegeneration(value, duration);
	std::cout << Color::GREEN << "Applied Regeneration: " << Color::RESET
		<< "Heals " << Color::GREEN << value << Color::RESET
		<< " health each turn for " << duration << " turns.\n";
}

void Haste_card::printCard() {
	std::cout << Color::CARD_BUFF << "[Buff][" << name << "]["
		<< effect_d << "][Cost:" << Color::BLUE << mana_cost << Color::CARD_BUFF << "]" << Color::RESET << "\n";
};
void Haste_card::apply(Character& self, Character& target) {
	self.getStatuses().addHaste(duration);
	std::cout << Color::BLUE << "Applied Haste: " << Color::RESET
		<< "Reduces mana cost of all cards by 2 for " << duration << " turns.\n";
}

void Dexterity_card::printCard() {
	std::cout << Color::CARD_BUFF << "[Buff][" << name << "]["
		<< effect_d << "][Cost:" << Color::BLUE << mana_cost << Color::CARD_BUFF << "]" << Color::RESET << "\n";
};
void Dexterity_card::apply(Character& self, Character& target) {
	self.getStatuses().addDexterity(duration);
	std::cout << Color::CYAN << "Applied Dexterity: " << Color::RESET
		<< "Increases evasion by 20% for " << duration << " turns.\n";
}







void Poison_card::apply(Character& self, Character& target) {
	target.getStatuses().addPoison(value, duration);
	std::cout << Color::PURPLE << "Applied Poison: " << Color::RESET
		<< "Deals " << Color::GREEN << value << Color::RESET
		<< " true damage each turn for " << duration << " turns.\n";
}
void Poison_card::printCard() {
	std::cout << Color::CARD_DEBUFF << "[Debuff][" << name << "]["
		<< effect_d << "][Cost:" << Color::BLUE << mana_cost << Color::CARD_DEBUFF << "] "
		<< Color::PURPLE << "(Poison " << value << " dmg)" << Color::RESET << "\n";
}

void Bleed_card::apply(Character& self, Character& target) {
	target.getStatuses().addBleed(value, duration);
	std::cout << Color::RED << "Applied Bleed: " << Color::RESET << "Deals " << Color::GREEN << value << Color::RESET
		<< " damage each turn for " << duration << " turns.\n";
}
void Bleed_card::printCard() {
	std::cout << Color::CARD_DEBUFF << "[Debuff][" << name << "]["
	<< effect_d << "][Cost:" << Color::BLUE << mana_cost << Color::CARD_DEBUFF << "] "
		<< Color::PURPLE << "(Poison " << value << " dmg)" << Color::RESET << "\n";
}

void  Weak_card::apply(Character& self, Character& target)  {
		target.getStatuses().addWeak(duration);
		std::cout << Color::YELLOW << "Applied Weak: " << Color::RESET << "Enemy deals 25% less damage "
			<< "(duration: " << duration << " turns).\n";
	}
void Weak_card::printCard() {
		std::cout << Color::CARD_DEBUFF << "[Debuff][" << name << "]["
			<< effect_d << "][Cost:" << Color::BLUE << mana_cost << Color::CARD_DEBUFF << "] "
			<< Color::PURPLE << "(Weak " << duration << " turns)" << Color::RESET << "\n";
	}

void Vulnerable_card::apply(Character& self, Character& target)  {
		target.getStatuses().addVulnerable(duration);
		std::cout << Color::RED << "Applied Vulnerable: " << Color::RESET << "Enemy receives 50% more damage "
			<< "(duration: " << duration << " turns).\n";
	}
void Vulnerable_card::printCard() {
	std::cout << Color::CARD_DEBUFF << "[Debuff][" << name << "]["
		<< effect_d << "][Cost:" << Color::BLUE << mana_cost << Color::CARD_DEBUFF << "] "
		<< Color::PURPLE << "(Vulnerable " << duration << " turns)" << Color::RESET << "\n";
	}

void Fragile_card::apply(Character& self, Character& target) {
		target.getStatuses().addFragile(duration);
		std::cout << Color::YELLOW << "Applied Fragile: " << Color::RESET << "Armor works at half efficiency "
			<< "(duration: " << duration << " turns).\n";
	}
void Fragile_card::printCard() {
	std::cout << Color::CARD_DEBUFF << "[Debuff][" << name << "]["
		<< effect_d << "][Cost:" << Color::BLUE << mana_cost << Color::CARD_DEBUFF << "] "
		<< Color::PURPLE << "(Fragile " << duration << " turns)" << Color::RESET << "\n";
}