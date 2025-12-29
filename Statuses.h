#pragma once
#include <iostream>
#include <string>
#include "Colors.h"

struct StatusesType {
	int poison = 0;     // урон ядом за ход (не зависит от брони)
	int poison_duration = 0;

	int bleed = 0;      // урон кровотечением за ход (сначала бьёт по броне)
	int bleed_duration = 0;

	// 1 — эффект активен, 0 — отключен
	int weak = 0;       // снижает исходящий урон персонажа на 25%
	int weak_duration = 0;

	int vulnerable = 0; // повышает входящий урон по персонажу на 50%
	int vulnerable_duration = 0;

	int fragile = 0;    // броня работает вполовину эффективности
	int fragile_duration = 0;



	int strength = 0;          // +50% урона
	int strength_duration = 0;

	int regeneration = 0;      // heal per turn
	int regeneration_duration = 0;

	int dexterity = 0;         // шанс уклонения (%)
	int dexterity_duration = 0;

	int haste = 0;             // -2 mana cost
	int haste_duration = 0;
};


class Statuses {
private:
	StatusesType status;

public:

	int getPoison() const { return status.poison; }
	int getBleed() const { return status.bleed; }
	int getWeak() const { return status.weak; }
	int getVulnerable() const { return status.vulnerable; }
	int getFragile() const { return status.fragile; }
	
	int getPoisonDuration() const { return status.poison_duration; }
	int getBleedDuration() const { return status.bleed_duration; }
	int getWeakDuration() const { return status.weak_duration; }
	int getVulnerableDuration() const { return status.vulnerable_duration; }
	int getFragileDuration() const { return status.fragile_duration; }


	int getStrength() const { return status.strength; }
	int getRegeneration() const { return status.regeneration; }
	int getDexterity() const { return status.dexterity; }
	int getHaste() const { return status.haste; }

	int getStrengthDuration() const { return status.strength_duration; }
	int getRegenerationDuration() const { return status.regeneration_duration; }
	int getDexterityDuration() const { return status.dexterity_duration; }
	int getHasteDuration() const { return status.haste_duration; }



	void addPoison(int dmg, int duration) {
		if (status.poison == 0)
			status.poison = dmg;

		status.poison_duration += duration;
	}
	void addBleed(int dmg, int duration) {
		if (status.bleed == 0)
			status.bleed = dmg;
		status.bleed_duration += duration;
	}
	void addWeak(int duration) {
		if (status.weak == 0)
			status.weak = 1; // включаем флаг, если эффекта ещё не было
		status.weak_duration += duration;
	}
	void addVulnerable(int duration) {
		if (status.vulnerable == 0)
			status.vulnerable = 1;
		status.vulnerable_duration += duration;
	}
	void addFragile(int duration) {
		if (status.fragile == 0)
			status.fragile = 1;
		status.fragile_duration += duration;
	}




	void addStrength(int duration) {
		status.strength = 1;
		status.strength_duration += duration;
	}

	void addRegeneration(int heal, int duration) {
		status.regeneration = heal;
		status.regeneration_duration += duration;
	}

	void addDexterity(int duration) {
		status.dexterity = 20; // %
		status.dexterity_duration += duration;
	}

	void addHaste(int duration) {
		status.haste = 1;
		status.haste_duration += duration;
	}




	void showStatuses() const {
		std::cout << Color::WHITE;

		if (status.poison_duration > 0)
			std::cout << Color::PURPLE << "- Poison: " << Color::GREEN
			<< status.poison << Color::RESET << " dmg/turn " << Color::DARK_GRAY
			<< "(" << status.poison_duration << " turns)" << Color::RESET << "\n";

		if (status.bleed_duration > 0)
			std::cout << Color::RED << "- Bleed: " << Color::GREEN
			<< status.bleed << Color::RESET << " dmg/turn " << Color::DARK_GRAY
			<< "(" << status.bleed_duration << " turns)" << Color::RESET << "\n";

		if (status.weak_duration > 0)
			std::cout << Color::YELLOW << "- Weak " << Color::DARK_GRAY
			<< "(" << status.weak_duration << " turns, "
			<< Color::YELLOW << "25% dmg reduction" << Color::DARK_GRAY << ")" << Color::RESET << "\n";

		if (status.vulnerable_duration > 0)
			std::cout << Color::RED << "- Vulnerable " << Color::DARK_GRAY
			<< "(" << status.vulnerable_duration << " turns, "
			<< Color::RED << "+50% incoming dmg" << Color::DARK_GRAY << ")" << Color::RESET << "\n";

		if (status.fragile_duration > 0)
			std::cout << Color::YELLOW << "- Fragile " << Color::DARK_GRAY
			<< "(" << status.fragile_duration << " turns, "
			<< Color::YELLOW << "armor halved" << Color::DARK_GRAY << ")" << Color::RESET << "\n";



		if(status.strength_duration > 0)
			std::cout << Color::GREEN << "- Strength " << Color::DARK_GRAY
			<< "(" << status.strength_duration << " turns, "
			<< Color::GREEN << "+50% dmg" << Color::DARK_GRAY << ")" << Color::RESET << "\n";

		if(status.regeneration_duration > 0)
			std::cout << Color::GREEN << "- Regeneration: " << Color::GREEN
			<< status.regeneration << Color::RESET << " heal/turn " << Color::DARK_GRAY
			<< "(" << status.regeneration_duration << " turns)" << Color::RESET << "\n";

		if(status.dexterity_duration > 0)
			std::cout << Color::CYAN << "- Dexterity " << Color::DARK_GRAY
			<< "(" << status.dexterity_duration << " turns, "
			<< Color::CYAN << status.dexterity << "% evasion" << Color::DARK_GRAY << ")" << Color::RESET << "\n";

		if (status.haste_duration > 0)
			std::cout << Color::BLUE << "- Haste " << Color::DARK_GRAY
			<< "(" << status.haste_duration << " turns, "
			<< Color::BLUE << "-2 mana cost" << Color::DARK_GRAY << ")" << Color::RESET << "\n";



		if (status.poison_duration == 0 && status.bleed_duration == 0 &&
			status.weak_duration == 0 && status.vulnerable_duration == 0 &&
			status.fragile_duration == 0 && status.strength_duration==0 && status.regeneration_duration
			&& status.haste_duration==0 && status.dexterity_duration==0)
		{
			std::cout << Color::DARK_GRAY << "No statuses." << Color::RESET << "\n";
		}
	}

	void updateStatuses() {
		if (status.poison_duration > 0) {
			status.poison_duration--;
			if (status.poison_duration == 0)
				status.poison = 0;
		}

		if (status.bleed_duration > 0) {
			status.bleed_duration--;
			if (status.bleed_duration == 0)
				status.bleed = 0;
		}

		if (status.weak_duration > 0) {
			status.weak_duration--;
			if (status.weak_duration == 0)
				status.weak = 0;
		}

		if (status.vulnerable_duration > 0) {
			status.vulnerable_duration--;
			if (status.vulnerable_duration == 0)
				status.vulnerable = 0;
		}

		if (status.fragile_duration > 0) {
			status.fragile_duration--;
			if (status.fragile_duration == 0)
				status.fragile = 0;
		}




		if (status.strength_duration > 0) {
			status.strength_duration--;
			if (status.strength_duration == 0)
				status.strength = 0;
		}

		if (status.regeneration_duration > 0) {
			status.regeneration_duration--;
			if (status.regeneration_duration == 0)
				status.regeneration = 0;
		}

		if (status.dexterity_duration > 0) {
			status.dexterity_duration--;
			if (status.dexterity_duration == 0)
				status.dexterity = 0;
		}

		if (status.haste_duration > 0) {
			status.haste_duration--;
			if (status.haste_duration == 0)
				status.haste = 0;
		}
	}
};