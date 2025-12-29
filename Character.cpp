#include "Character.h"
#include <iostream>   // ��� cout
#include <random>  
#include "Card.h"
static std::mt19937 make_rng() {
    static std::random_device rd;
    return std::mt19937(static_cast<unsigned>(std::time(nullptr)) ^ rd());
}



int Character::getEffectiveCardCost(const Card& card) const {
    int cost = card.getManaCost();

    if (status.getHasteDuration() > 0) {
        cost -= 2;
    }

    return std::max(0, cost);
}


void Character::applyPhysicalDamageToArmor(int dmg) { // снимает урон сначала с брони
    armor -= dmg;
    if (armor < 0) armor = 0;
} 
void Character::getAttacked(int dmg) {
    // Проверка на неотрицательный урон
    if (dmg < 0) {
        std::cout << Color::YELLOW << "Warning: Negative damage value!" << Color::RESET << "\n";
        dmg = 0;
    }

	if (hp <= 0) return;

	int incoming_dmg = dmg;

    if (status.getDexterityDuration() > 0) {
		int dodge_chance = status.getDexterity(); // Получаем шанс уклонения из статуса
		int roll = rand() % 100; // Генерируем случайное число от 0 до 99
        if (roll < dodge_chance) {
            std::cout << Color::CYAN << "Dodged!" << Color::RESET << "\n";
            return;
        }
    }
	//Apply Strength status: увеличивает наносимый урон атакующего на 50%
    if (status.getStrength() > 0) {
        incoming_dmg = static_cast<int>(incoming_dmg * 1.5);
    }

	// Apply Vulnerable status: увеличивает входящий урон
    if(status.getVulnerable() > 0) {
        incoming_dmg = static_cast<int>(incoming_dmg * 1.5);
	}
    
	// Apply Weak status: ослабляет эффективность брони цели
	int effective_armor = armor;
    if(status.getWeak() > 0) {
        effective_armor /= 2;
    }
     
	// Damage calculation after armor
	int dmg_after_armor = incoming_dmg - effective_armor; // сколько урона пройдет по здоровью
    if(dmg_after_armor < 0) {
        dmg_after_armor = 0;
	}

	applyPhysicalDamageToArmor(incoming_dmg);// Reduce armor first
	hp -= dmg_after_armor;// Apply damage to health
	if (hp < 0)  hp = 0;
   
}


void Character::takesPeriodDmgAtStartTurn() {

    if (status.getPoison() > 0) {
        hp -= status.getPoison();
        std::cout << "Poison deals " << status.getPoison() << " damage!\n";
		if (hp < 0) hp = 0;
    }

    if (status.getBleed() > 0) {
        int effective_armor = armor;
        if (status.getFragile() > 0) { effective_armor /= 2; }

        int dmg_after_armor = status.getBleed() - effective_armor;
        if (dmg_after_armor < 0) { dmg_after_armor = 0; }
        
		applyPhysicalDamageToArmor(status.getBleed());
        hp -= dmg_after_armor;
		if (hp < 0) hp = 0;

		std::cout << "Bleed deals " << dmg_after_armor << " damage after armor!\n";
    }

}

void Character::drawCard() {
    // Проверка: не превышен ли лимит карт в руке
    const int MAX_HAND_SIZE = 10;
    if (player_hand.size() >= MAX_HAND_SIZE) {
        std::cout << Color::YELLOW << "Hand is full! Cannot draw more cards." << Color::RESET << "\n";
        return;
    }

    if (player_deck.empty()) return;
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, player_deck.size() - 1);
    size_t index = dist(rng);
    player_hand.push_back(player_deck[index]);
    player_deck.erase(player_deck.begin() + index);
}
