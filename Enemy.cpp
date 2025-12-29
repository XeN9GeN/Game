#include "Enemy.h"
#include "Card.h"
#include <iostream>
#include <algorithm>
#include "Colors.h"

Enemy::Enemy(std::string name, int health, int armor, int mana) : name(name), Character(health, armor, mana) {}
void Enemy::autoEnemyTurn(Character& player) {
    drawCard();

    std::cout << Color::RED << "[ENEMY] " << Color::RESET << name << Color::RED << " turn\n" << Color::RESET;

    int currentMana = getMana();
    // Проверка: отрицательная мана
    if (currentMana < 0) {
        std::cout << Color::YELLOW << "[ENEMY] " << name << ": Negative mana, resetting to 0" << Color::RESET << "\n";
        currentMana = 0;
        setMana(0);
    }

    auto& enemy_hand = getHand();

    if (enemy_hand.empty()) {
        int base_dmg = 2;
        std::cout << Color::RED << "[ENEMY] " << Color::RESET << name
            << Color::RED << " performs basic attack for " << Color::RESET << base_dmg
            << Color::RED << " dmg\n" << Color::RESET;
        player.getAttacked(base_dmg);
        return;
    }

    bool playedSmth = false;
    while (true) {
        int bestind = -1;
        int bestcost = -1;

        for (int i = 0; i < enemy_hand.size(); ++i) {
            auto& c = enemy_hand[i];
            if (!c) {
                std::cout << Color::YELLOW << "[ENEMY] " << name << ": Warning: Null card in hand at index " << i << Color::RESET << "\n";
                continue;
            }

            int cost = c->getManaCost();

            // Проверка: отрицательная стоимость карты
            if (cost < 0) {
                std::cout << Color::YELLOW << "[ENEMY] " << name << ": Card \"" << c->getName()
                    << "\" has negative cost (" << cost << "), treating as 0" << Color::RESET << "\n";
                cost = 0;
            }

            if (cost <= getMana() && cost > bestcost) {
                bestcost = cost;
                bestind = i;
            }
        }
        if (bestind == -1) break;


        auto card = enemy_hand[bestind];
        // Проверка: карта существует
        if (!card) {
            std::cout << Color::RED << "[ENEMY] " << name << ": ERROR: Selected card is null!" << Color::RESET << "\n";
            break;
        }

        std::cout << Color::RED << "[ENEMY] " << Color::RESET << name << Color::RED << " uses: " << Color::RESET
            << card->getName() << Color::RED << " (cost " << Color::RESET
            << card->getManaCost() << Color::RED << ")\n" << Color::RESET;

        card->apply(*this, player); // self = enemy, target = player
        currentMana -= card->getManaCost();
        setMana(currentMana);

        enemy_hand.erase(enemy_hand.begin() + bestind);
        playedSmth = true;

        if (player.getHealth() <= 0) break;
    }

    if (!playedSmth) {
        int baseDmg = 2;
        std::cout << Color::RED << "[ENEMY] " << Color::RESET << name
            << Color::RED << " performs basic attack for " << Color::RESET << baseDmg
            << Color::RED << " dmg\n" << Color::RESET;
        player.getAttacked(baseDmg);
    }


}