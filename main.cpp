#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include <ctime>

#include "Character.h"
#include "Enemy.h"
#include "Card.h"
#include "Game.h"
using namespace std;

bool turn_over = false;
int steps = 0;
void printCaracterStatus(const Character& character, const string& name) {
	std::cout << "-------------------------\n";
    std::cout << name << " - HP: " << character.getHealth() << ", Armor: " << character.getArmor() << ", Mana: " << character.getMana() << std::endl;
    character.showStatuses();
}
void printEnemyStatus(const Enemy& enemy) {
    std::cout << "-------------------------\n";
    std::cout << "Enemy - HP: " << enemy.getHealth() << ", Armor: " << enemy.getArmor() << ", Mana: " << enemy.getMana() << std::endl;
    enemy.showStatuses();
}
static std::mt19937 make_rng() {
    static std::random_device rd;
    return std::mt19937(static_cast<unsigned>(std::time(nullptr)) ^ rd());
}


void Game::autoPlayerTurn() {
    std::cout << "[AUTO] Player turn...\n";

    int currentMana = player.getMana();
    auto& hand = player.getAllCards();

    int bestIndex = -1;
    int bestCost = -1;

    // найти лучшую карту в руке
    for (int i = 0; i < hand.size(); ++i) {
        auto& c = hand[i];
        if (!c) continue;
        int cost = c->getManaCost();
        if (cost <= currentMana && cost > bestCost) {
            bestCost = cost;
            bestIndex = i;
        }
    }
    play_log.clear();

    if (bestIndex != -1) {
        auto card = hand[bestIndex];
        std::cout << "[AUTO] Player uses card: " << card->getName() << "\n";
        logPlay(card->getName());
        card->apply(player, enemy);
        player.setMana(currentMana - card->getManaCost());
        hand.erase(hand.begin() + bestIndex);
        std::cout << "-------------------------\n";
        printPlayLog();
        return;
    }

    int dmg = 2;
    enemy.getAttacked(dmg);
    std::cout << "[AUTO] Player attacks for " << dmg << " damage\n";
    logPlay(std::string("Basic attack: ") + std::to_string(dmg) + " dmg");

    std::cout << "-------------------------\n";
    printPlayLog();
    std::cout << "\n\n\n";
  
}



int main() {
    auto rng = make_rng();
    Character player(30, 5, 10); // HP, Armor, Mana
    Enemy enemy("Armored Goblin", 20, 10, 10);
    Game game(player, enemy);
    enemy.addCardToDeck(make_shared<Attack_card>("Slash", "Simple strike", 2, 3));
    enemy.addCardToDeck(make_shared<Attack_card>("Heavy Blow", "Hard hit", 4, 5));
    enemy.addCardToDeck(make_shared<Defense_card>("Shield", "Block", 2, 2));
    enemy.addCardToDeck(make_shared<Heal_card>("Bandage", "Heal small", 3, 3));
    enemy.addCardToDeck(make_shared<Buff_card>("Rage", "Random buff", 1));
    enemy.addCardToDeck(make_shared<Debuff_card>("Curse", "Random debuff", 1));

    player.addCardToDeck(make_shared<Attack_card>("Strike", "Basic attack", 2, 4));
    player.addCardToDeck(make_shared<Defense_card>("Block", "Increase armor", 2, 3));
    player.addCardToDeck(make_shared<Heal_card>("First Aid", "Restore health", 3, 5));
    player.addCardToDeck(make_shared<Buff_card>("Inspiration", "Random buff", 1));
    player.addCardToDeck(make_shared<Debuff_card>("Hex", "Random debuff", 1));
    player.addCardToDeck(make_shared<Debuff_card>("Deadly Venom", "Applies poison", 1, StatusType::Poison, 4));
    player.addCardToDeck(make_shared<Debuff_card>("Bleeding Strike", "Causes bleeding", 1, StatusType::Bleed, 3));
    player.addCardToDeck(make_shared<Debuff_card>("Intimidate", "Weakens enemy", 1, StatusType::Weak, 2));


    auto drawCard = [&](Character& ch) {
        auto& deck = ch.getDeck();
        auto& hand = ch.getAllCards();

        if (!deck.empty()) {
            std::uniform_int_distribution<size_t> dist(0, deck.size() - 1);
            size_t index = dist(rng);
            hand.push_back(deck[index]);
            deck.erase(deck.begin() + index);
        }
    };

    drawCard(player);
    drawCard(player);
    drawCard(player);
    drawCard(player);

    std::cout << "Battle Start!" << endl;

    int turn = 1;
    while (player.getHealth() > 0 && enemy.getHealth() > 0) {
        std::cout << "\n\n\n\n";
        std::cout << "\n--- Turn " << turn << " ---\n";

        player.setMana(turn);
        enemy.setMana(turn);

        game.autoPlayerTurn();  //автоматический ход игрока
        enemy.playTurn(player); //автоматический ход врага

        printCaracterStatus(player, "Player");
        printEnemyStatus(enemy);

        turn++;
    }
}


