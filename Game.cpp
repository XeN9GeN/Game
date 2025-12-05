#include "Game.h"
#include <iostream>
#include <memory>
#include "Card.h"
#include "Character.h"
#include "Enemy.h"

void Enemy::playTurn(Character& player) {
    drawCard();

    // Выбрать карту с наибольшей стоимостью, не превышающей текущую ману
    int currentMana = getMana();
    if (currentMana <= 0 || hand.empty()) return;

    int bestIndex = -1;
    int bestCost = -1;
    for (int i = 0; i < hand.size(); ++i) {
        auto& c = hand[i];
        if (!c) continue;
        int cost = c->getManaCost();
        if (cost <= currentMana && cost > bestCost) {
            bestCost = cost;
            bestIndex = i;
        }
    }

    if (bestIndex != -1) {
        auto card = hand[bestIndex];
        if (card) {
            card->apply(*this, player);
            setMana(currentMana - card->getManaCost());
        }
        hand.erase(hand.begin() + bestIndex);
    }
}

