#include "Card.h"
#include <iostream>
#include "Character.h"
#include <string>
#include <random>
#include "Statuses.h"


void Attack_card::apply(Character& self, Character& target) {
	target.getAttacked(dmg);
};
void Attack_card::printCard() {
	std::cout << "[Attack][" << name << "]["
		<< effect_d << "][Cost:" << mana_cost
		<< "][DMG:" << dmg << "]\n";
};


void Defense_card::apply(Character& self, Character& target) {
	self.setArm(self.getArmor() + armor);
};
void Defense_card::printCard() {
	std::cout << "[Defense][" << name << "][" << effect_d << "][Cost:" << mana_cost << "][ARMOR:" << armor << "]\n";
};


void Heal_card::apply(Character& self, Character& target) {
	self.setHp(self.getHealth() + heal_amount);
};
void Heal_card::printCard() {
	std::cout << "[Heal][" << name << "][" << effect_d << "][Cost:" << mana_cost << "][HEAL:" << heal_amount << "]\n";
};


void Buff_card::apply(Character& self, Character& target) {
	switch (rand() % 3) {
	case 0:
		self.setArm(self.getArmor() + 1);
		printf("Buff applied: +1 Armor\n");
		break;
	case 1:
		self.setHp(self.getHealth() + 1);
		printf("Buff applied: +1 Health\n");
		break;
	case 2:
		self.setMana(self.getMana() + 1);
		printf("Buff applied: +1 Mana\n");
		break;
	}
};
void Buff_card::printCard() {
	std::cout << "[Buff][" << name << "][" << effect_d << "][Cost:" << mana_cost << "]\n";
};


void Debuff_card::apply(Character& self, Character& target) {
	switch (statusType) {
		//вывод эффекта дебаффа
	case StatusType::Poison:
		target.getStatuses().addPoison(value,duration);
		std::cout << "Applied Poison: Deals " << value
			<< " true damage each turn." << duration << "\n";
		break;

	case StatusType::Bleed:
		target.getStatuses().addBleed(value,duration);
		std::cout << "Applied Bleed: Deals " << value
			<< " damage each turn (reduced by armor)."<< duration <<"\n";
		break;

	case StatusType::Weak:
		target.getStatuses().addWeak(duration);
		std::cout << "Applied Weak: Enemy deals 25% less damage "
			<< "(duration: " << duration << " turns).\n";
		break;

	case StatusType::Vulnerable:
		target.getStatuses().addVulnerable(duration);
		std::cout << "Applied Vulnerable: Enemy receives 50% more damage "
			<< "(duration: " << duration << " turns).\n";
		break;

	case StatusType::Fragile:
		target.getStatuses().addFragile(duration);
		std::cout << "Applied Fragile: Armor works at half efficiency "
			<< "(duration: " << duration << " turns).\n";
		break;
	}
}
void Debuff_card::printCard() {// вывод информации о дебафф карты(в руке)
	std::cout << "[Debuff][" << name << "][" << effect_d << "][Cost:" << mana_cost << "] ";

	switch (statusType) {
	case StatusType::Poison:     cout << "(Poison " << value << ")"; break;
	case StatusType::Bleed:      cout << "(Bleed " << value << ")"; break;
	case StatusType::Weak:       cout << "(Weak " << value << ")"; break;
	case StatusType::Vulnerable: cout << "(Vulnerable " << value << ")"; break;
	case StatusType::Fragile:    cout << "(Fragile " << value << ")"; break;
	}

	cout << "\n";
}

