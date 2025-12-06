#pragma once
#include <iostream>
#include <string>


struct StatusesType {
	int poison = 0;     // наносит урон в начале хода, обходя броню
	int poison_duration = 0;

	int bleed = 0;      // наносит урон в начале хода, учитывая броню
	int bleed_duration = 0;

	//их значения не важны, важна длительность(1 есть, 0 нет)
	int weak = 0;       // уменьшает урон атакующего на 25%
	int weak_duration = 0;

	int vulnerable = 0; // увеличивает входящий урон на 50%
	int vulnerable_duration = 0;

	int fragile = 0;    // уменьшает эффективность брони (напр. броня дает вдвое меньше защиты)
	int fragile_duration = 0;
};


class Statuses {
private:
	StatusesType status;

public:

	//гетеры для получения значений статусов
	int getPoison() const { return status.poison; }
	int getBleed() const { return status.bleed; }
	int getWeak() const { return status.weak; }
	int getVulnerable() const { return status.vulnerable; }
	int getFragile() const { return status.fragile; }


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
			status.weak = 1;//значение не важно, важна длительность
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


	void showStatuses() const {
		std::cout << "Statuses:\n";

		if (status.poison_duration > 0)
			std::cout << "- Poison: " << status.poison << " dmg/turn ("
			<< status.poison_duration << " turns)\n";

		if (status.bleed_duration > 0)
			std::cout << "- Bleed: " << status.bleed << " dmg/turn ("
			<< status.bleed_duration << " turns)\n";

		if (status.weak_duration > 0)
			std::cout << "- Weak (" << status.weak_duration
			<< " turns, 25% dmg reduction)\n";

		if (status.vulnerable_duration > 0)
			std::cout << "- Vulnerable (" << status.vulnerable_duration
			<< " turns, +50% incoming dmg)\n";

		if (status.fragile_duration > 0)
			std::cout << "- Fragile (" << status.fragile_duration
			<< " turns, armor halved)\n";

		if (status.poison_duration == 0 && status.bleed_duration == 0 &&
			status.weak_duration == 0 && status.vulnerable_duration == 0 &&
			status.fragile_duration == 0)
		{
			std::cout << "No statuses.\n";
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

	}
};