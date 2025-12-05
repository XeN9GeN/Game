#include "Enemy.h"
#include "Character.h"
#include <string>
#include "Card.h"
#include <random>
#include <algorithm>

Enemy::Enemy(std::string name, int health, int armor, int mana) : name(name), Character(health, armor, mana) {}

void Enemy::drawCard() {
    if (enemy_deck.empty()) return;

    static std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution<std::size_t> dist(0, enemy_deck.size() - 1);
    std::size_t ran_ind = dist(rng);

    enemy_hand.push_back(enemy_deck[ran_ind]);
    enemy_deck.erase(enemy_deck.begin() + static_cast<std::ptrdiff_t>(ran_ind));
}

void Enemy::addCardToDeck(std::shared_ptr<Card> card) {
    enemy_deck.push_back(card);
}


void Enemy::playTurn(Character&player){
    drawCard();

    std::cout << "[ENEMY] " << name << " turn\n";

    int currentMana = getMana();

    if (enemy_hand.empty()) {
        int base_dmg = 2;
        std::cout << "[ENEMY] " << name << " performs basic attack for " << base_dmg << " dmg\n";
        player.getAttacked(base_dmg);
        return;
    }

    


    

}