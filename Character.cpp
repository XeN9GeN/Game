#include "Character.h"
#include "Card.h"
#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include <ctime>
#include "Enemy.h"
#include "Statuses.h"

static std::mt19937 make_rng() {
    static std::random_device rd;
    return std::mt19937(static_cast<unsigned>(std::time(nullptr)) ^ rd());
}


void Character::applyPhysicalDamageToArmor(int dmg) {// проверка на ломание полного щита
    armor -= dmg;
    if (armor < 0) armor = 0;
} 
void Character::getAttacked(int dmg) {
	if (hp <= 0) return;

	int incoming_dmg = dmg;

	// Apply Vulnerable status    more dmg
    if(status.getVulnerable() > 0) {
        incoming_dmg = static_cast<int>(incoming_dmg * 1.5);
	}
    
	// Apply Weak status    defShred
	int effective_armor = armor;
    if(status.getWeak() > 0) {
        effective_armor /= 2;
    }
     
	//Damage calculation after armor
	int dmg_after_armor = incoming_dmg - effective_armor;// дмг который должен пройти по хп
    if(dmg_after_armor < 0) {
        dmg_after_armor = 0;
	}

	applyPhysicalDamageToArmor(incoming_dmg);// Reduce armor first
	hp -= dmg_after_armor;// Apply damage to health
	if (hp < 0)  hp = 0;
   
}


void Character::startTurn() {

    if (status.getPoison() > 0) {
        hp -= status.getPoison();
        cout << "Poison deals " << status.getPoison() << " damage!\n";
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

		cout << "Bleed deals " << dmg_after_armor << " damage after armor!\n";
    }

}


void printCaracterStatus(const Character& character, const std::string& name) {
    std::cout << "-------------------------\n";
    std::cout << name << " - HP: " << character.getHealth() << ", Armor: " << character.getArmor() << ", Mana: " << character.getMana() << std::endl;
	character.getStatuses().showStatuses();// char->getStatuses() - возврат ссылки на объект статусов -> status.showStatuses() - вывод статусов
}
void Character::drawCard() {
    if (player_deck.empty()) return;
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, player_deck.size() - 1);
    size_t index = dist(rng);
    player_hand.push_back(player_deck[index]);
    player_deck.erase(player_deck.begin() + index);
}
